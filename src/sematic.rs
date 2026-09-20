use std::{fmt::format, fs::{File, OpenOptions}, io::{Read, Write}};

use regex::regex;

use crate::{CompgenError, Diagnosis, Envs, STAGE_SEMATIC_CODEGEN, STAGE_SEMATIC_PARSING, parser::{NodeMemberType, ParserRuleSet, parse_parser_rules}, read_from_file, write_to_file};
#[derive(Clone)]
struct SematicFuncArgument{
    name:String,
    typestr:String
}
impl SematicFuncArgument {
    fn connect(&self)->String {
        self.typestr.clone()+" "+&self.name
    }
}
#[derive(Clone)]
struct SematicFunc{
    name:String,
    arguments:Vec<SematicFuncArgument>,
}
impl SematicFunc {
    fn name_with_args(&self)->String {
        format!("{}({})",self.name,{
            let mut combined_arglist=self.arguments.clone();
            combined_arglist.insert(0, SematicFuncArgument { name: String::from("node"), typestr: String::from("ast_node_t*") });
            combined_arglist.push(SematicFuncArgument { name: String::from("context"), typestr: String::from("sematic_context_t*") });
            combined_arglist.iter().map(|arg| arg.connect()).collect::<Vec<String>>().join(",")})
    }
    fn name_arg_ret(&self)->String{
        format!("bool {}",self.name_with_args())
    }
    fn signature(&self)->String {
        let mut combined_arglist=self.arguments.clone();
        combined_arglist.insert(0, SematicFuncArgument { name: String::from("node"), typestr: String::from("ast_node_t*") });
        combined_arglist.push(SematicFuncArgument { name: String::from("context"), typestr: String::from("sematic_context_t*") });
        let args=combined_arglist.iter().map(|arg| arg.typestr.clone()).collect::<Vec<String>>().join(",");
        format!("bool {}({})",self.name,args)
    }
    /*
    generate argument list adding `node` in the front and `context` at the back separated by commas.
     */
    fn argument_list_with_comma(&self)->String {
        let mut all_args=vec![String::from("node")];
        all_args.extend(self.arguments.iter().map(|arg| format!("node->{}",arg.name)).collect::<Vec<String>>());
        all_args.push(String::from("context"));
        all_args.join(",")
    }
}
#[derive(Clone)]
struct SematicNodeMember{
    name:String
}
#[derive(Clone)]
enum SematicStep {
    Call(SematicFunc),
    Visit(SematicNodeMember)
}
#[derive(Clone)]
struct SematicRule{
    ruleset:String,
    rule:String,
    steps:Vec<SematicStep>,
}
impl SematicRule {
    fn new(ruleset:&str,rule:&str) -> Self {
        Self { ruleset: ruleset.to_string(), rule: rule.to_string(), steps: Vec::new() }
    }
    fn checker_name(&self, stage:&SematicPass)->String {
        format!("check_{}_{}_{}",stage.name,self.ruleset,self.rule)
    }
    fn signature(&self, stage:&SematicPass)->String{
        format!("bool {}({}_{}_t* node, sematic_context_t* context)",self.checker_name(stage),self.ruleset,self.rule)
    }
}
/// one stage of sematic check.
pub struct SematicPass{
    name:String,
    rules:Vec<SematicRule>
}
impl SematicPass {
    fn signature(&self)->String {
        format!("bool {}_check(ast_node_t* node,sematic_context_t* context)",self.name)
    }
}
pub fn parse_sematic_rules(path:&str, ruleset:&Vec<ParserRuleSet>)->Result<Vec<SematicPass>,Diagnosis> {
    let mut diagnosis=Diagnosis::new();
    let mut f=match File::open(path) {
        Ok(file) => file,
        Err(_) => {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_PARSING, "failed to open sematic rule file"));
            return Err(diagnosis);
        }
    };
    let mut rule_src=String::new();
    if f.read_to_string(&mut rule_src).is_err() {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_PARSING, "failed to read sematic rule file"));
        return Err(diagnosis);
    }
    let rule_src=rule_src.split("\n").map(|line| line.trim()).collect::<Vec<&str>>();
    let mut passes=Vec::new();

    let pat_pass=regex!(r"^\[([\w_]+)\]$");
    let pat_node=regex!(r"^([\w_]+)\.([\w_]+):$");
    let pat_step=regex!(r"^([\w_]+)\(([\w_\,]*)\)$");

    let mut current_pass="";
    let mut current_rules=Vec::new();
    for (i,&line) in rule_src.iter().enumerate() {
        // skip empty lines
        if line.len()==0 {
            continue;
        }
        if let Some(pass_name) = pat_pass.captures(line) {
            if current_pass.len()>0 {
                // store previous pass
                passes.push(SematicPass { name: current_pass.to_string(), rules: current_rules.clone() });
                current_rules.clear();
            }
            current_pass=pass_name.get(1).map_or("", |m| m.as_str());

        }else if let Some(node) = pat_node.captures(line) {
            if current_pass=="" {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, "sematic rule file parser err: node before pass"));
                continue;
            }
            let node_ruleset=node.get(1).map_or("", |m| m.as_str());
            let node_rule=node.get(2).map_or("", |m| m.as_str());
            let valid_rule=ruleset.iter().any(|rs| rs.name==node_ruleset && rs.rules.iter().any(|r| r.name==node_rule));
            if !valid_rule {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, &format!("sematic rule file parser err: unknown node rule {}.{}", node_ruleset, node_rule)));
                continue;
            }
            current_rules.push(SematicRule::new(node_ruleset,node_rule));
        }else if let Some(calling) = pat_step.captures(line) {
            let func_name=calling.get(1).map_or("", |m| m.as_str());
            let args=calling.get(2).map_or(Vec::new(), |t| {
                let t=t.as_str().trim();
                if t.is_empty() {
                    Vec::new()
                }else {
                    t.split(",").map(str::trim).filter(|st| !st.is_empty()).collect()
                }
            });
            // find the types of these arguments
            let Some(curr)=current_rules.last() else {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, "sematic rule file parser err: action before node"));
                continue;
            };
            let Some(rs)=ruleset.iter().find(|r| r.name==curr.ruleset) else { continue; };
            let Some(r)=rs.rules.iter().find(|r| r.name==curr.rule) else { continue; };
            let mut arg_types=Vec::new();
            let mut args_valid=true;
            for a in &args {
                let Some(member)=r.struct_members.iter().find(|m| &m.name==a) else {
                    diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, &format!("sematicgen err: failed to find member {} in rule {}.{} while generating code.",a,rs.name,r.name)));
                    args_valid=false;
                    continue;
                };
                arg_types.push(match member.member_type {
                    NodeMemberType::Token|NodeMemberType::TokenCategory=>String::from("token_t*"),
                    NodeMemberType::Node=>format!("{}_t*",r.recipe[member.pos_in_recipe].value),
                });
            }
            if !args_valid { continue; }
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                let args: Vec<SematicFuncArgument>=args.iter().enumerate().map(|(index,s)| 
                    SematicFuncArgument { 
                        name: s.to_string(), 
                        typestr: arg_types[index].clone()
                    }).collect();
                if func_name=="visit" {
                    if args.len()!=1 {
                        diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, &format!("sematicgen err: visit() requires 1 argument but {} are/is provided",args.len())));
                        continue;
                    }else if args.get(0).unwrap().typestr=="token_t*" {
                        diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, "sematicgen err: visit() cannot visit token_t"));
                        continue;
                    }else {
                        current_rule.steps.push(SematicStep::Visit(SematicNodeMember { name: args.get(0).unwrap().name.clone() }));
                    }
                }else {
                    current_rule.steps.push(
                        SematicStep::Call(
                            SematicFunc { 
                                name: func_name.to_string(), 
                                arguments: args
                            }
                        ));
                }
            }else {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, "sematic rule file parser err: node rule before node"));
                continue;
            }
        }else {
            diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_SEMATIC_PARSING, "sematic file parse err: invalid line"));
        }
    }
    // store last pass
    if current_pass.len()>0 {
        passes.push(SematicPass { name: current_pass.to_string(), rules: current_rules.clone() });
        current_rules.clear();
    }
    if cfg!(feature="debug") {
        for p in passes.iter() {
            println!("[{}]",p.name);
            for r in p.rules.iter() {
                println!("{}.{}:",r.ruleset,r.rule);
                r.steps.iter().for_each(|step| {
                    let (func_name,func_args)=match step{
                        SematicStep::Call(e)=>{
                            (e.name.clone(),
                            e.arguments.iter().map(|a| a.name.clone()).collect::<Vec<String>>().join(","))
                        },
                        SematicStep::Visit(mem)=>{
                            (String::from("visit"),
                            mem.name.clone())
                        }
                    };
                    println!("{}({})",func_name,func_args);
                });
            }
        }
    }
    if diagnosis.is_empty() { Ok(passes) } else { Err(diagnosis) }
}
pub struct SematicSource{
    pub sematic_h:String,
    pub sematic_cpp:String,
    pub sematic_user_cpp:String
}
pub fn generate_sematic_code(passes:&Vec<SematicPass>,ruleset:&Vec<ParserRuleSet>,envs:&Envs)->Result<SematicSource,Diagnosis>{
    let mut diagnosis=Diagnosis::new();
    let mut src=String::new();
    // collect checker funcs
    let checkers={
        let mut chks: Vec<String>=Vec::new();
        for p in passes.iter() {
            for r in p.rules.iter() {
                r.steps.iter().for_each(|step| 
                    // remove duplicates
                    if let SematicStep::Call(e) = step {
                        if !chks.contains(&e.signature()) {
                            chks.push(e.signature());
                        }
                    }
                );
            }
        }
        chks
    };
    // put decls
    src.push_str(&checkers.iter().map(|c| format!("{};\n",c)).collect::<Vec<String>>().join(""));
    // stage by stage
    let mut stage_code=Vec::new();

    for stg in passes.iter() {
        let mut recorded_rules=Vec::new();
        let infix=&stg.name;
        // these are funcs that check one node calling checker funcs defined in the rule file
        let mut check_funcs=Vec::new();
        let mut check_func_code=Vec::new();
        // branchs of switch of the checker of the stage
        let mut stage_switch_branches=Vec::new();
        for rule in stg.rules.iter() {
            recorded_rules.push((&rule.ruleset,&rule.rule));
            let calls=rule.steps.iter().map(|step| {
                let (func_name,func_args)=match step {
                    SematicStep::Call(e)=>
                    (e.name.clone(),e.argument_list_with_comma()),
                    SematicStep::Visit(e)=>
                    (String::from("visit"),format!("node->{},context",e.name))
                };
                format!("if(!{}({}))return false;",func_name,func_args)
            }).collect::<Vec<String>>().join("\n\t");
            // generate the whole func
            let func_name=rule.checker_name(stg);
            let func_code=format!("{}{{
    {}
    return true;
}}",rule.signature(stg),calls);
            check_funcs.push(func_name.clone());
            check_func_code.push(func_code);
            // generate the switch branch
            // node enum
            let nodetype_enum=format!("NODE_{}_{}",rule.ruleset.to_uppercase(),rule.rule.to_uppercase());
            let branch=format!("
    case {}:
        return {}(static_cast<{}_{}_t*>(node),context);
        break;",nodetype_enum,func_name,rule.ruleset,rule.rule);
            stage_switch_branches.push(branch);
        }
        // generate branches for those rules not manually given checkers so we know to visit their children
        for rs in ruleset.iter() {
            for r in rs.rules.iter() {
                if recorded_rules.iter().any(|(rus,ru)| rus==&&rs.name&&ru==&&r.name) {
                    continue;
                }
                let nodetype_enum=format!("NODE_{}_{}",rs.name.to_uppercase(),r.name.to_uppercase());
                let branch=format!("
    case {}:
        {}
        return true;",
        nodetype_enum,
        r.struct_members.iter().filter_map(|m| 
            if m.member_type==NodeMemberType::Node {
                Some(format!("if(!visit(static_cast<{}_{}_t*>(node)->{},context))return false;",rs.name,r.name,m.name))
            }else {
                None
            }
        ).collect::<Vec<String>>().join("\n")
    );
                stage_switch_branches.push(branch);
            }
        }
        // one array of checker funcs for each stage
        let stgarr=format!("{}{{
    switch(node->get_kind()){{
    {}
    }}
    return false;
}};",stg.signature(),stage_switch_branches.join("\n"));
        stage_code.push(check_func_code.join("\n"));
        stage_code.push(stgarr);
    }
    src.push_str(&stage_code.join("\n"));
    // then put defs of checkers
    let user_fill_template_src=String::from("#include \"parser.h\"\n#include \"sematic.h\"\n")+&checkers.iter().map(|chk| {
        format!("{}{{\n\treturn true;\n}}",chk)
    }).collect::<Vec<String>>().join("\n");
    src.push_str(&format!("
bool (*passes[])(ast_node_t*,sematic_context_t*)={{
    {}
}};",passes.iter().map(|p| format!("{}_check",p.name)).collect::<Vec<String>>().join(",\n\t")));
    let template_cpp_path=envs.template_dir.join("sematic_template.cpp");
    let src_path=envs.output_dir.join("sematic.cpp");
    let src_test_path=envs.output_dir.join("sematic_test.cpp");
    let src_test_user_path=envs.output_dir.join("sematic_test_user.cpp");
    let header_template_path=envs.output_dir.join("sematic_template.h");
    let header_path=envs.output_dir.join("sematic.h");

    // read template
    let template_code=match read_from_file(&template_cpp_path) {
        Ok(code) => code,
        Err(_) => {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_CODEGEN, "failed to read sematic_template.cpp"));
            return Err(diagnosis);
        }
    };
    let header_src=match read_from_file(&header_template_path) {
        Ok(code) => code,
        Err(_) => {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_CODEGEN, "failed to read sematic_template.h"));
            return Err(diagnosis);
        }
    };
    let final_code=template_code.replace("{%}", &src);
    if cfg!(feature="debug") {
        // put them in a separate file for users to fill them without getting replaced
        if write_to_file(&src_test_user_path,&user_fill_template_src).is_err() {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_CODEGEN, "failed to write sematic_test_user.cpp"));
        }
        if write_to_file(&src_test_path,&final_code).is_err() {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_CODEGEN, "failed to write sematic_test.cpp"));
        }
        if write_to_file(&header_path,&header_src).is_err() {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_SEMATIC_CODEGEN, "failed to write sematic.h"));
        }
    }
    let sematic_src=SematicSource{
        sematic_h: header_src,
        sematic_cpp: final_code,
        sematic_user_cpp: user_fill_template_src,
    };
    if diagnosis.is_empty() { Ok(sematic_src) } else { Err(diagnosis) }
}
#[test]
fn test_parser_sematic_rules(){
    let ruleset=parse_parser_rules("parser.rule").unwrap();
    parse_sematic_rules("sematic.rule", &ruleset).unwrap();
}
#[test]
fn test_generate_sematic_source() {
    let envs=Envs::default();
    let ruleset=parse_parser_rules("parser.rule").unwrap();
    let passes=parse_sematic_rules("sematic.rule", &ruleset).unwrap();
    let _ = generate_sematic_code(&passes,&ruleset,&envs);
}
