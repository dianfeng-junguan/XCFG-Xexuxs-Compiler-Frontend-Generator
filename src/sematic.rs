use std::{fmt::format, fs::File, io::{Read, Write}};

use regex::regex;

use crate::parser::{NodeMemberType, ParserRuleSet, parse_parser_rules};
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
#[derive(Clone)]
struct SematicNodeMember{
    name:String
}
#[derive(Clone)]
struct SematicRule{
    ruleset:String,
    rule:String,
    /// funcs to be called when entering the node
    enter:Vec<SematicFunc>,
    /// nodes to be visited after calling the enter sematic funcs.
    children:Vec<SematicNodeMember>,
    /// funcs to be called before leaving the node.
    leave:Vec<SematicFunc>
}
impl SematicRule {
    fn new(ruleset:&str,rule:&str) -> Self {
        Self { ruleset: ruleset.to_string(), rule: rule.to_string(), enter: Vec::new(), children: Vec::new(), leave: Vec::new() }
    }
}
/// one stage of sematic check.
pub struct SematicPass{
    name:String,
    rules:Vec<SematicRule>
}
pub fn parse_sematic_rules(path:&str, ruleset:&Vec<ParserRuleSet>)->Vec<SematicPass> {
    let mut f=File::open(path).expect("failed to open sematic rule file");
    let mut rule_src=String::new();
    f.read_to_string(&mut rule_src).expect("failed to read sematic rule file");
    let rule_src=rule_src.split("\n").map(|line| line.trim()).collect::<Vec<&str>>();
    let mut passes=Vec::new();

    let pat_pass=regex!(r"^\[([\w_]+)\]$");
    let pat_node=regex!(r"([\w_]+)\.([\w_]+)");
    let pat_enter=regex!(r"^\s*enter\s+([\w_]+)\(([\w_\,]*)\)$");
    let pat_children=regex!(r"^\s*children ([\w_ ]+)");
    let pat_leave=regex!(r"^\s*leave\s+([\w_]+)\(([\w_\, ]*)\)$");

    let mut current_pass="";
    let mut current_rules=Vec::new();
    for (i,&line) in rule_src.iter().enumerate() {
        if let Some(pass_name) = pat_pass.captures(line) {
            if current_pass.len()>0 {
                // store previous pass
                passes.push(SematicPass { name: current_pass.to_string(), rules: current_rules.clone() });
                current_rules.clear();
            }
            current_pass=pass_name.get(1).expect("pat_pass captured the whole but nothing in ()?").as_str();

        }else if let Some(node) = pat_node.captures(line) {
            if current_pass=="" {
                eprintln!("sematic rule file parser err at line {}: node before pass",i);
                continue;
            }
            let ruleset=node.get(1).unwrap().as_str();
            let rule=node.get(2).unwrap().as_str();
            current_rules.push(SematicRule::new(ruleset,rule));
        }else if let Some(enter) = pat_enter.captures(line) {
            let func_name=enter.get(1).unwrap().as_str();
            let args=enter.get(2).map_or(Vec::new(), |t| {
                let t=t.as_str().trim();
                if t.is_empty() {
                    Vec::new()
                }else {
                    t.split(",").map(str::trim).filter(|st| !st.is_empty()).collect()
                }
            });
            // find the types of these arguments
            let curr=current_rules.iter().nth_back(0).unwrap();
            let arg_types=args.iter().map(|a| {
                let rs=ruleset.iter().find(|r| r.name==curr.ruleset).unwrap();
                let r=rs.rules.iter().find(|r| r.name==curr.rule).unwrap();
                r.struct_members.iter().find(|m| &&m.name==a).map_or_else(||{
                        eprintln!("sematicgen err: failed to find member {} in rule {}.{} while generating code.",a,rs.name,r.name);
                        return String::new(); 
                    }
                    ,|m| {
                    match m.member_type {
                        NodeMemberType::Token|NodeMemberType::TokenCategory=>String::from("token_t*"),
                        NodeMemberType::Node=>{
                            format!("{}_t*",r.recipe[m.pos_in_recipe].value)
                        }
                    }
                })
            }).collect::<Vec<String>>();
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                current_rule.enter.push(SematicFunc { name: func_name.to_string(), arguments: args.iter().enumerate().map(|(index,s)| 
                    SematicFuncArgument { name: s.to_string(), typestr: arg_types.get(index).unwrap().clone() }
                ).collect() });
            }else {
                eprintln!("sematic rule file parser err at line {}: node rule before node",i);
                continue;
            }
        }else if let Some(children) = pat_children.captures(line) {
            // collect member names
            let mut members_resolved=true;
            let members=children.get(1).map_or(Vec::new(), |t| {
                let argraw=t.as_str().split(" ").map_while(|memname|
                    // check if this member really exists
                    if ruleset.iter().any(|rs| rs.rules.iter().any(|r| r.struct_members.iter().any(|mem| mem.name==memname))) {
                        Some(SematicNodeMember { name: memname.to_string() })
                    }else {
                        eprintln!("sematic file parse err at line {}: struct member {} not found",i,memname);
                        members_resolved=false;
                        None
                    }
                ).collect();
                argraw
            });
            if !members_resolved {
                continue;
            }
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                current_rule.children.extend(members);
            }else {
                eprintln!("sematic rule file parser err at line {}: node rule before node",i);
                continue;
            }
        }else if let Some(leave) = pat_leave.captures(line) {
            let func_name=leave.get(1).unwrap().as_str();
            let args=leave.get(2).map_or(Vec::new(), |t| {
                let t=t.as_str().trim();
                if t.is_empty() {
                    Vec::new()
                }else {
                    t.split(",").map(str::trim).filter(|st| !st.is_empty()).collect()
                }
            });
            // find the types of these arguments
            let curr=current_rules.iter().nth_back(0).unwrap();
            let arg_types=args.iter().map(|a| {
                let rs=ruleset.iter().find(|r| r.name==curr.ruleset).unwrap();
                let r=rs.rules.iter().find(|r| r.name==curr.rule).unwrap();
                r.struct_members.iter().find(|m| &&m.name==a).map_or_else(||{
                        eprintln!("sematicgen err: failed to find member {} in rule {}.{} while generating code.",a,rs.name,r.name);
                        return String::new(); 
                    }
                    ,|m| {
                    match m.member_type {
                        NodeMemberType::Token|NodeMemberType::TokenCategory=>String::from("token_t*"),
                        NodeMemberType::Node=>{
                            format!("{}_t*",r.recipe[m.pos_in_recipe].value)
                        }
                    }
                })
            }).collect::<Vec<String>>();
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                current_rule.leave.push(SematicFunc { name: func_name.to_string(), arguments: args.iter().enumerate().map(|(index,s)| 
                    SematicFuncArgument { name: s.to_string(), typestr: arg_types.get(index).unwrap().clone() }
                ).collect() });
            }else {
                eprintln!("sematic rule file parser err at line {}: node rule before node",i);
                continue;
            }
        }else {
            println!("sematic file parse err: invalid line {}",i);
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
                r.enter.iter().for_each(|e| println!("enter {}({})",e.name,e.arguments.iter().map(|a| a.name.clone()).collect::<Vec<String>>().join(",")));
                if r.children.len()>0 {
                    print!("children ");
                    r.children.iter().for_each(|c| print!("{} ",c.name));
                    println!("");
                }
                r.leave.iter().for_each(|e| println!("leave {}({})",e.name,e.arguments.iter().map(|a| a.name.clone()).collect::<Vec<String>>().join(",")));
            }
        }
    }
    passes
}
pub fn generate_sematic_code(passes:&Vec<SematicPass>)->Option<String>{
    let mut src=String::new();
    // collect checker funcs
    let checkers={
        let mut chks: Vec<String>=Vec::new();
        for p in passes.iter() {
            for r in p.rules.iter() {
                let enters=r.enter.iter().map_while(|e| 
                    // remove duplicates
                    if chks.iter().find(|&c| *c==e.name).is_some() {
                        None
                    }else {
                        Some(format!("{}({})",e.name,{
                            let mut combined_arglist=e.arguments.clone();
                            combined_arglist.insert(0, SematicFuncArgument { name: String::from("node"), typestr: String::from("ast_node_t*") });
                            combined_arglist.push(SematicFuncArgument { name: String::from("context"), typestr: String::from("sematic_context_t*") });
                            combined_arglist.iter().map(|arg| arg.connect()).collect::<Vec<String>>().join(",")
                        }))
                    }
                    ).collect::<Vec<String>>();
                let leaves=r.leave.iter().map_while(|e| {
                    if chks.iter().find(|&c| *c==e.name).is_some() {
                        None
                    }else {
                        Some(format!("{}({})",e.name,{
                            let mut combined_arglist=e.arguments.clone();
                            combined_arglist.insert(0, SematicFuncArgument { name: String::from("node"), typestr: String::from("ast_node_t*") });
                            combined_arglist.push(SematicFuncArgument { name: String::from("context"), typestr: String::from("sematic_context_t*") });
                            combined_arglist.iter().map(|arg| arg.connect()).collect::<Vec<String>>().join(",")
                        }))
                }
            }).collect::<Vec<String>>();
                chks.extend(enters);
                chks.extend(leaves);
            }
        }
        chks
    };
    // put decls
    src.push_str(&checkers.iter().map(|c| format!("bool {};\n",c)).collect::<Vec<String>>().join(""));
    // stage by stage
    let mut stage_code=Vec::new();
    for stg in passes.iter() {
        let infix=&stg.name;
        let mut check_funcs=Vec::new();
        let mut check_func_code=Vec::new();
        // branchs of switch of the checker of the stage
        let mut stage_switch_branches=Vec::new();
        for rule in stg.rules.iter() {
            let enter_calls=rule.enter.iter().map(|e| {
                format!("{}(node,{},context);",e.name,e.arguments.iter().map(|arg| format!("node->{}",arg.name)).collect::<Vec<String>>().join(","))
            }).collect::<Vec<String>>().join("\n\t");
            let children_visits=rule.children.iter().map(|c| {
                format!("visit(node->{},context);",c.name)
            }).collect::<Vec<String>>().join("\n\t");
            let leave_calls=rule.leave.iter().map(|e| {
                format!("{}(node,{},context);",e.name,e.arguments.iter().map(|arg| format!("node->{}",arg.name)).collect::<Vec<String>>().join(","))
            }).collect::<Vec<String>>().join("\n\t");
            // generate the whole func
            let func_name=format!("check_{}_{}_{}",infix,rule.ruleset,rule.rule);
            let func_code=format!("bool {}({}_{}_t *node,sematic_context_t *context){{
    {}
    {}
    {}
}}",func_name,rule.ruleset,rule.rule,enter_calls,children_visits,leave_calls);
            check_funcs.push(func_name.clone());
            check_func_code.push(func_code);
            // generate the switch branch
            // node enum
            let nodetype_enum=format!("NODE_{}_{}",rule.ruleset.to_uppercase(),rule.rule.to_uppercase());
            let branch=format!("
    case {}:
        return {}(node,context);
        break;",nodetype_enum,func_name);
            stage_switch_branches.push(branch);
        }
        // one array of checker funcs for each stage
        // TODO 改成一个大函数根据get_kind switch调用节点对应的检查函数
        let stgarr=format!("bool {}_check(ast_node_t* node,sematic_context_t* context){{
    switch(node->get_kind()){{
    {}
    }}
    return false;
}};",stg.name,stage_switch_branches.join("\n"));
        

        stage_code.push(check_func_code.join("\n"));
        stage_code.push(stgarr);
    }
    src.push_str(&stage_code.join("\n"));
    // then put defs of checkers
    src.push_str(&checkers.iter().map(|chk| {
        format!("bool {}{{\n\t\n}}",chk)
    }).collect::<Vec<String>>().join("\n"));
    src.push_str(&format!("
bool (*passes)(ast_node_t*,sematic_context_t*)[]={{
    {}
}};",passes.iter().map(|p| format!("{}_check",p.name)).collect::<Vec<String>>().join(",\n\t")));
    // read template
    let mut temp=File::open("sematic_template.cpp").expect("failed to open sematic_template.cpp");
    let mut template_code=String::new();
    temp.read_to_string(&mut template_code).expect("failed to read sematic_template.cpp");
    let final_code=template_code.replace("{%}", &src);
    if cfg!(feature="debug") {
        let mut out=File::create("sematic_test.cpp").expect("failed to create sematic_test.cpp");
        out.write_all(final_code.as_bytes()).expect("failed to write sematic_test.cpp");
    }
    Some(final_code)
}
#[test]
fn test_parser_sematic_rules(){
    let ruleset=parse_parser_rules("parser.rule");
    parse_sematic_rules("sematic.rule", &ruleset);
}
#[test]
fn test_generate_sematic_source() {
    let ruleset=parse_parser_rules("parser.rule");
    let passes=parse_sematic_rules("sematic.rule", &ruleset);
    let _ = generate_sematic_code(&passes);
}