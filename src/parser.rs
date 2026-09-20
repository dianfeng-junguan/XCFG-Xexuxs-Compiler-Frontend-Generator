use std::{cmp, collections::HashMap, fmt::{Display, Pointer, format}, format, fs::File, hash::Hash, io::{Read, Write}, path::Path, println, vec, write};

use crate::{CompgenError, Diagnosis, Envs, STAGE_PARSER_CODEGEN, read_from_file, write_to_file};

#[derive(PartialEq, Eq)]
pub enum TermType{
    ParserRuleSet,
    TokenCategory,
    SpecificTokenType,
}
/// a term is a unit to be fetched from the token stream. It can be another rule set which generates an AST node in the end, or a category of token or a single token type.
pub struct Term{
    pub term_type:TermType,
    pub value:String,
    pub should_be_stored:bool,
    /// the name of the struct member to store the scanned value in.
    pub to_store_in:String
}
impl Term {
    pub fn from_fmt(fmt:&str)->Option<Self>{
        if fmt.len()==0 {
            return None;
        }
        let (flag_store,value,store_mem)=if fmt.find("@").is_some() {
            let splitstr=fmt.split_once("@").unwrap();
            (true,splitstr.0,splitstr.1)
        }else {
            (false,fmt,"")
        };
        if value.chars().nth(0).unwrap()=='$' {
            Some(Self{
                term_type: TermType::ParserRuleSet,
                value: (&value[1..]).to_string(),
                should_be_stored: flag_store,
                to_store_in: store_mem.to_string(),
            })
        }else if value.chars().nth(0).unwrap()=='#'||value.chars().nth(0).unwrap()=='~' {
            // a token category
            Some(Self{
                term_type: TermType::TokenCategory,
                value: (&value[1..]).to_string(),
                should_be_stored: flag_store,
                to_store_in: store_mem.to_string(),
            })
        }else {
            Some(Self{
                term_type: TermType::SpecificTokenType,
                value: value.to_string(),
                should_be_stored: flag_store,
                to_store_in: store_mem.to_string(),
            })
        }
    }
}
impl Display for Term {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(match self.term_type {
            TermType::ParserRuleSet=>"$",
            TermType::SpecificTokenType=>"",
            TermType::TokenCategory=>"#/~"
        }).and_then(|_| f.write_str(&self.value)).and_then(|_| 
            if self.should_be_stored {
                write!(f,"@{}",self.to_store_in)
            }else {
                Ok(())
            }
        )
    }
}
#[derive(Clone, Copy, PartialEq, Eq)]
pub enum NodeMemberType {
    Node,
    /// a pointer type to the token.
    Token,
    TokenCategory,
}
pub struct NodeMember{
    pub name:String,
    pub pos_in_recipe:usize,
    pub member_type:NodeMemberType
}
pub struct ParserRule{
    pub name:String,
    pub recipe:Vec<Term>,
    pub struct_members:Vec<NodeMember>,
    is_left_combined:bool
}
impl ParserRule {
    fn get_class_name(&self, ruleset_name:&str)->String{
        format!("{}_{}_t",ruleset_name,self.name)
    }
    fn gen_class_code(&self, ruleset_name:&str, ruleset:&Vec<ParserRuleSet>)->String{
        // generate members
        let mut member_disposal_str=String::new();
        let member_str=self.struct_members.iter().map(|m| {
            match m.member_type {
                NodeMemberType::Token|NodeMemberType::TokenCategory=>format!("token_t *{}=nullptr",m.name),
                NodeMemberType::Node=>{
                    // find the ruleset
                    let rs_name_target=&self.recipe[m.pos_in_recipe].value;
                    let Some(rs)=ruleset.iter().find(|rs| &rs.name==rs_name_target) else {
                        eprintln!("non-existent ruleset {} referenced while generating class of rule {}",rs_name_target, self.name);
                        return String::new();
                    };
                    member_disposal_str.push_str(&format!("delete {};\n",m.name));
                    // get the class name 
                    let rs_class_name=rs.get_class_name();
                    format!("{}* {}=nullptr",rs_class_name,m.name)
                }
            }
        }).collect::<Vec<String>>().join(";\n\t");
        format!("class {}:public {}_t{{
    public:
    {};
    ~{}() override{{
        {}
    }}
    node_type_t get_kind() const override {{return NODE_{}_{};}}
}};",self.get_class_name(ruleset_name),ruleset_name,member_str,self.get_class_name(ruleset_name),member_disposal_str,ruleset_name.to_uppercase(),self.name.to_uppercase())
    }
    fn get_parser_name(&self,ruleset_name:&str)->String {
        format!("parse_{}",self.get_class_name(ruleset_name))
    }
    fn get_parser_name_nostart(&self,ruleset_name:&str)->String {
        format!("parse_{}_nostart",self.get_class_name(ruleset_name))
    }
    fn gen_parser_function(&self, ruleset_name:&str , ruleset:&Vec<ParserRuleSet>)->String{
        self._gen_parser_function(ruleset_name, ruleset, false)
    }
    fn gen_parser_function_nostart(&self, ruleset_name:&str , ruleset:&Vec<ParserRuleSet>)->String{
        self._gen_parser_function(ruleset_name, ruleset, true)
    }
    fn _gen_parser_function(&self, ruleset_name:&str , ruleset:&Vec<ParserRuleSet>, skip_start:bool)->String{
        let iterator=if skip_start {self.recipe[1..].iter()} else {self.recipe.iter()};
        let dealing_str=iterator.map(|t| {
            match t.term_type {
                TermType::ParserRuleSet=>{
                    // find the ruleset we are looking for and get its parser name
                    let Some(rs) = ruleset.iter().find(|rs| {
                        rs.name==t.value
                    }) else {
                        eprintln!("rule {} referenced a non-existent ruleset {}",self.name,t.value);
                        return String::new();
                    };
                    let rs_parser_name=rs.get_parser_name();
                    if t.should_be_stored {
                        format!("if(!(node->{}={}(tokenstream))){{tokenstream->reset();delete node;return nullptr;}}",t.to_store_in,rs_parser_name)
                    }else {
                        format!("if(!({}(tokenstream))){{tokenstream->reset();delete node;return nullptr;}}",rs_parser_name)   
                    }
                }
                TermType::SpecificTokenType=>{
                    // todo need to get token enum by looking up some table
                    if t.should_be_stored {
                        format!("if(!(node->{}=parse_token(tokenstream,TOKEN_{}))){{tokenstream->reset();delete node;return nullptr;}}else{{node->{}=new token_t(*node->{});}}",t.to_store_in,t.value.to_uppercase(),t.to_store_in,t.to_store_in)
                    }else {
                        format!("if(!(parse_token(tokenstream,TOKEN_{}))){{tokenstream->reset();delete node;return nullptr;}}",t.value.to_uppercase())
                    }
                }
                TermType::TokenCategory=>{
                    if t.should_be_stored {
                        format!("if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_{}(tokenstream->peek()->token_type)){{node->{}=new token_t(*tokenstream->consume());}}else{{tokenstream->reset();delete node;return nullptr;}}",t.value.to_uppercase(),t.to_store_in)
                    }else {
                        format!("if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_{}(tokenstream->peek()->token_type)){{tokenstream->consume();}}else{{tokenstream->reset();delete node;return nullptr;}}",t.value.to_uppercase())
                    }
                }
            }
        }).collect::<Vec<String>>().join("\n");
        let parser=if !skip_start {
            String::from("{r}* parse_{r}(tokenstream_t *tokenstream){
    {r}* node=new {r}();
    tokenstream->begin_parsing();
    {}
    tokenstream->end_parsing();
    return node;
}\n").replace("{r}", &self.get_class_name(ruleset_name))
    } else {
        let start_node_str=format!("node->{}=start_node;",&self.recipe.get(0).unwrap().to_store_in);
        String::from("{r}* parse_{r}_nostart({rs}_t* start_node,tokenstream_t *tokenstream){
    {r}* node=new {r}();
    tokenstream->begin_parsing();
    {}
    {first_member}
    tokenstream->end_parsing();
    return node;
}\n").replace("{r}", &self.get_class_name(ruleset_name)).replace("{first_member}", if self.recipe.get(0).unwrap().should_be_stored {
    &start_node_str
    } else {""}
    ).replace("{rs}", ruleset_name)
        
    };
        let parser=parser.replace("{}", &dealing_str);
        parser
    }
}
impl Display for ParserRule {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.name).and_then(|_|
            {
                f.write_str(":");
                self.recipe.iter().for_each(|t|{
                    let _=write!(f,"{} ",t);
                });
                Ok(())
            }
        )
    }
}

impl PartialEq for ParserRule {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
    }
}
impl Eq for ParserRule {
    
}
impl Hash for ParserRule {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.name.hash(state);
    }
}
/// a set of rules to generate one type of node.
pub struct ParserRuleSet{
    pub name:String,
    pub rules:Vec<ParserRule>,
    pub has_left_combined:bool
}
impl ParserRuleSet {
    fn get_class_name(&self)->String {
        format!("{}_t",self.name)
    }
    fn gen_class_code(&self)->String {
        format!("class {}:public ast_node_t{{
    public:
    virtual node_type_t get_kind() const override=0;
    virtual ~{}() = default;
}};",self.get_class_name(),self.get_class_name())
    }
    fn get_parser_name(&self)->String{
        format!("parse_{}",self.get_class_name())
    }
    fn gen_parser_function_decl(&self)->String{
        format!("{} *parse_{}(tokenstream_t *tokenstream);\n",self.get_class_name(),self.get_class_name())
    }
    fn gen_parser_function(&self, rulesets:&Vec<ParserRuleSet>)->String {

        // generate the rule parser funcs. we need them anyway
        let rule_parsers_def=self.rules.iter().map(|r| {
            if !r.is_left_combined {
                r.gen_parser_function(&self.name, rulesets)
            }else{
                r.gen_parser_function_nostart(&self.name, rulesets)
            }
        }).collect::<Vec<String>>().join("\n");

        if self.has_left_combined {
            // template code
            let code=String::from("static {rs}* parse_{rs}_start(tokenstream_t *tokenstream){
        {rs}* node;
        tokenstream->begin_parsing();
        {calling}
        tokenstream->reset();
        return nullptr;
}
{rs}* parse_{rs}(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    {rs}* node = parse_{rs}_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        {rs}* next=nullptr;
        {ifs}
    }
    tokenstream->end_parsing();
    return node;
}").replace("{rs}", &self.get_class_name());
            // generate the callings of rule parsers
            let call_rule_parsers=self.rules.iter().map(|r| {
                if !r.is_left_combined {
                    format!("if((node={}(tokenstream))){{tokenstream->end_parsing();return node;}}",r.get_parser_name(&self.name))
                }else{
                    String::new()
                }
            }).collect::<Vec<String>>().join("\n\t");
            let code=code.replace("{calling}", &call_rule_parsers);
            // generate callings of parsers that does not check the first term of recipe of left-combined rules
            let mut lb_i=0;
            let call_lb_parsers=self.rules.iter().map(|r| {
                /*
                at this stage the first term on the recipe of the left-combined rules has been dealt with. So we provide a nostart version of parser that takes a node as the result of the first term and deal with the rest of its recipe.
                 */
                if r.is_left_combined {
                    lb_i+=1;
                    format!("{}if((next={}(node,tokenstream))){{node=next;continue;}}",if lb_i==1 {""} else {"else "}, r.get_parser_name_nostart(&self.name))
                }else{
                    String::new()
                }
            }).collect::<Vec<String>>().join("\n\t")+"else break;";
            let code=code.replace("{ifs}", &call_lb_parsers);
            rule_parsers_def+&code
        }else {
            // just try parsers
            let calling_parsers=self.rules.iter().map(|r| {
                format!("if((node={}(tokenstream))){{tokenstream->end_parsing();return node;}}",r.get_parser_name(&self.name))
            }).collect::<Vec<String>>().join("\n\t");
            rule_parsers_def+&String::from("\n{rs}* parse_{rs}(tokenstream_t *tokenstream){{
    {rs}* node=nullptr;
    tokenstream->begin_parsing();
    {calling}
    tokenstream->reset();
    return node;
}}\n").replace("{rs}", &self.get_class_name()).replace("{calling}", &calling_parsers)
        }
    }
}
impl Display for ParserRuleSet {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&self.name)?;
        f.write_str("\n")?;
        self.rules.iter().for_each(|r|{
            let _=write!(f,"{}\n",r);
        });
        Ok(())
    }
}
impl PartialEq for ParserRuleSet {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name
    }
}
impl Eq for ParserRuleSet {
    
}
impl Hash for ParserRuleSet {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.name.hash(state);
    }
}
#[test]
fn test_parse_parser_rules(){
    parse_parser_rules(Path::new("parser.rule"));
}
pub fn parse_parser_rules(path:&Path)->Result<Vec<ParserRuleSet>,Diagnosis>{
    let mut diagnosis=Diagnosis::new();

    let Ok(rule_file_text)=read_from_file(path) else {
        diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_PARSING, "failed to read parser file"));
        return Err(diagnosis);
    };

    let rule_lines=rule_file_text.split("\n").collect::<Vec<&str>>();

    let mut rulesets=Vec::new();
    // some patterns prepared
    let node_pat=regex::Regex::new(r"^\$(\w+):$").unwrap();
    let rule_pat=regex::Regex::new(r"^(\w+):([a-zA-Z$#~@_\- \!]+)$").unwrap();
    let term_pat=regex::Regex::new(r"((\$|#|~|!)?([a-zA-Z_\-]+)(@[a-zA-Z_]+)?)").unwrap();
    for (i,line) in rule_lines.into_iter().enumerate() {
        let line=line.trim();
        if line.len()==0 {
            continue;
        }
        if node_pat.is_match(line) {
            if let Some(ruleset_name)=node_pat.captures(line){
                let mtch=ruleset_name.get(1).unwrap();
                let set=ParserRuleSet{
                    name: mtch.as_str().to_string(),
                    rules: vec![],
                    has_left_combined: false,
                };
                rulesets.push(set);
            }else {
                diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "parser generator err: invalid naming"));
                continue;
            }
        }else if rule_pat.is_match(line) {
            if let Some(cap) = rule_pat.captures(line) {
                if cap.len()<3 {
                    diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "parser generator err: a rule needs to have at least a name and a structure"));
                    continue;
                }
                let name=cap.get(1).unwrap().as_str();
                let content=cap.get(2).unwrap().as_str();
                // now go on capturing the terms in the content
                let mut terms=Vec::new();
                let mut cap_start=0;
                let mut members=Vec::new();
                let mut recipe_pos=0;
                while let Some(termcap) = term_pat.captures_at(content,cap_start) {
                    let cap_match=termcap.get(0).unwrap();
                    if {
                        content[cap_start..cap_match.start()].chars().any(|c| !c.is_whitespace())  
                    } {
                        // there are some invalid chars in between
                        diagnosis.push_err(CompgenError::new(i+1, cap_start+1, crate::STAGE_PARSER_PARSING, &format!("parsergen err: invalid chars between col {} and col {}",cap_start,cap_match.start())));
                    }
                    if cap_match.as_str()=="!" {
                        // empty
                        break;
                    }
                    let Some(term)=Term::from_fmt(cap_match.as_str()) else {
                        diagnosis.push_err(CompgenError::new(i+1, cap_start+1, crate::STAGE_PARSER_PARSING, "parser generator err: invalid term grammar"));
                        break;
                    };
                    if term.should_be_stored {
                        let node_member=NodeMember{
                            name: term.to_store_in.clone(),
                            pos_in_recipe:recipe_pos,
                            member_type: match term.term_type {
                                TermType::ParserRuleSet=>NodeMemberType::Node,
                                TermType::SpecificTokenType=>NodeMemberType::Token,
                                TermType::TokenCategory=>NodeMemberType::TokenCategory
                            },
                        };
                        members.push(node_member);
                    }
                    terms.push(term);
                    cap_start=cap_match.start()+cap_match.len();
                    recipe_pos+=1;
                }
                let set_num=rulesets.len();
                if set_num==0 {
                    diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "rule defined before ruleset defined"));
                    continue;
                }
                let Some(set)=rulesets.get_mut(set_num-1) else {
                    diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "rule defined before ruleset defined"));
                    continue;
                };
                // check if the value of the first term equals the ruleset
                let lb=terms.get(0).map_or(false, |t| t.term_type==TermType::ParserRuleSet && t.value==set.name);
                if lb {
                    // has left-combined rule
                    set.has_left_combined=true;
                }
                // create this piece of rule
                let rule=ParserRule{
                    name: name.to_string(),
                    recipe: terms,
                    struct_members:members,
                    is_left_combined: lb,
                };
                // add this rule to the set
                set.rules.push(rule);
            }else {
                diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "parser generator err: failed to parse rule"));
                continue;
            }
        }else {
            diagnosis.push_err(CompgenError::new(i+1, 0, crate::STAGE_PARSER_PARSING, "parser generator err: failed to parse rule"));
        }
    }

    if cfg!(feature="debug") {
        println!("parser:");
        rulesets.iter().for_each(|rs| println!("{}",rs));
    }
    if diagnosis.is_empty() { Ok(rulesets) } else { Err(diagnosis) }
}

#[test]
fn test_generate_parser_source(){
    let envs=Envs::default();
    match parse_parser_rules(Path::new("parser.rule")){
        Ok(parser_rules)=>{
            generate_parser_source(&parser_rules,&envs);
        }
        Err(d)=>{
            d.print_errs();
        }
    }
}
pub struct ParserSource{
    pub parser_cpp:String,
    pub parser_h:String
}
pub fn generate_parser_source(ruleset:&Vec<ParserRuleSet>,envs:&Envs)->Result<ParserSource,Diagnosis>{
    let mut diagnosis=Diagnosis::new();
    let mut src=String::new();
    for rs in ruleset {
        for rule in &rs.rules {
            for term in &rule.recipe {
                if term.term_type == TermType::ParserRuleSet && !ruleset.iter().any(|target| target.name == term.value) {
                    diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_CODEGEN, &format!("rule {} referenced a non-existent ruleset {}", rule.name, term.value)));
                }
            }
        }
    }
    if !diagnosis.is_empty() { return Err(diagnosis); }
    // vector of ruleset class name
    let mut ruleset_classdefs=Vec::new();
    let mut rule_classdefs=Vec::new();
    let mut node_typeenum=Vec::new();


    for rs in ruleset.iter() {
        // generate a base class
        // generate ruleset class name
        ruleset_classdefs.push(rs.gen_class_code()); 
        // generate specific classes
        for (index,rule) in rs.rules.iter().enumerate() {
            let node_type = format!("NODE_{}_{}",rs.name.to_uppercase(),rule.name.to_uppercase());
            node_typeenum.push(node_type);
            // create the ruleclass
            rule_classdefs.push(rule.gen_class_code(&rs.name, &ruleset));
        }
    }

    // now generate parser functions for each rule
    // we need to capture the tokens one by one
    // definitions of all parser functions.
    let mut code_parser_funcs=Vec::new();
    // declarations of all parser functions.
    let mut code_parser_func_decls=Vec::new();
    for rs in ruleset.iter() {
        code_parser_func_decls.push(rs.gen_parser_function_decl());
        code_parser_funcs.push(rs.gen_parser_function(&ruleset));
    }

    let rule_structdef_str=format!("
typedef struct{{
    const char* name;
    ast_node_t* (*parser)(tokenstream_t *ts);
}}parser_rule_t;
");
    // generate rule array
    let mut rule_array_str=String::new();
    // find the reserved top_statement ruleset as make it the top parser that calls all the other parsers 
    if let Some(top_stmt_ruleset) = ruleset.iter().find(|rs| rs.name=="top_statement"){
        rule_array_str.push_str(&format!(
            "{{\"{}\", (ast_node_t* (*)(tokenstream_t*))parse_{}}},\n",top_stmt_ruleset.name,top_stmt_ruleset.get_class_name()
        ));
    }else {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_PARSER_CODEGEN,"parsergen err: cannot find necessary ruleset 'top_statement'"));
        return Err(diagnosis);
    }
    let rule_array_str=format!("
parser_rule_t parser_rules[]={{
{}
}};
    ",rule_array_str);
    let mut header_src=String::new();
    // concat the enum defs
    let mut nodetypeenum_str=String::new();
    node_typeenum.iter().for_each(|en| nodetypeenum_str.push_str(&(en.to_string()+",\n")));
    header_src.push_str(&format!("
typedef enum{{
{}
}}node_type_t;
",nodetypeenum_str));
    header_src.push_str("
#pragma once
#include \"lexer.h\"
class ast_node_t{
public:
    virtual ~ast_node_t() = default;
    virtual node_type_t get_kind() const = 0;
};
typedef struct{
    bool success;
    std::vector<ast_node_t*> ast;
}parser_result_t;
");
    header_src.push_str(&ruleset_classdefs.join("\n"));
    header_src.push('\n');
    header_src.push_str(&rule_classdefs.join("\n"));
    header_src.push('\n');

    src.push_str(&code_parser_func_decls.join("\n"));
    src.push('\n');
    src.push_str(&code_parser_funcs.join("\n"));
    src.push('\n');
    src.push_str(&rule_structdef_str);
    src.push_str(&rule_array_str);

    // prepare paths
    let header_path=envs.output_dir.join("parser.h");
    let src_path=envs.output_dir.join("parser.cpp");
    let template_path=envs.template_dir.join("parser_template.cpp");

    // put generated code into template
    let Ok(mut template_code)=read_from_file(template_path.as_path()) else {
        diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_CODEGEN, "failed to read parser template file"));
        return Err(diagnosis);
    };
    template_code=template_code.replace("{%}", &src);
    src=template_code;

    if cfg!(feature="debug") {
        // generate header file
        if write_to_file(header_path.as_path(),&header_src).is_err() {
            diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_CODEGEN, "failed to write parser.h"));
            return Err(diagnosis);
        }
        // println!("{}",src);
        if let Ok(mut parser_output)=File::create("parser_test.cpp") {
            if parser_output.write_all(src.as_bytes()).is_err() {
                diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_CODEGEN, "failed to write parser_test.cpp"));
            }
        } else {
            diagnosis.push_err(CompgenError::new(0, 0, crate::STAGE_PARSER_CODEGEN, "failed to create parser_test.cpp"));
        }
    }
    let parser_src=ParserSource{
        parser_cpp: src,
        parser_h: header_src,
    };
    if diagnosis.is_empty() { Ok(parser_src) } else { Err(diagnosis) }
}
