use std::{cmp, collections::HashMap, eprintln, fmt::{Display, Pointer}, format, fs::File, hash::Hash, io::{Read, Write}, println, vec, write};

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
#[derive(Clone, Copy)]
pub enum NodeMemberType {
    Node,
    /// a pointer type to the token.
    Token,
    TokenCategory,
}
pub struct NodeMember{
    name:String,
    pos_in_recipe:usize,
    member_type:NodeMemberType
}
pub struct ParserRule{
    name:String,
    recipe:Vec<Term>,
    struct_members:Vec<NodeMember>
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
    name:String,
    rules:Vec<ParserRule>,
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
    parse_parser_rules("parser.rule");
}
pub fn parse_parser_rules(path:&str)->Vec<ParserRuleSet>{
    let mut rule_file_text=String::new();
    let mut rule_file=File::open(path).unwrap();
    rule_file.read_to_string(&mut rule_file_text).expect("failed to read lexer file");

    let rule_lines=rule_file_text.split("\n").collect::<Vec<&str>>();

    let mut rulesets=Vec::new();
    // some patterns prepared
    let node_pat=regex::Regex::new(r"\$(\w+):").unwrap();
    let rule_pat=regex::Regex::new(r"(\w+):([a-zA-Z$#~@_\- ]+)").unwrap();
    let term_pat=regex::Regex::new(r"((\$|#|~)?([a-zA-Z_\-]+)(@[a-zA-Z_]+)?)").unwrap();
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
                };
                rulesets.push(set);
            }else {
                eprintln!("parser generator err at line {}: invalid naming",i);
                continue;
            }
        }else if rule_pat.is_match(line) {
            if let Some(cap) = rule_pat.captures(line) {
                if cap.len()<3 {
                    eprintln!("parser generator err at line {}: a rule needs to have at least a name and a structure", i);
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
                    let term=Term::from_fmt(cap_match.as_str()).expect(&format!("parser generator err at line {}: invalid term grammar",i));
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
                // create this piece of rule
                let rule=ParserRule{
                    name: name.to_string(),
                    recipe: terms,
                    struct_members:members
                };
                // add this rule to the set
                let set_num=rulesets.len();
                if set_num==0 {
                    eprintln!("rule defined before ruleset defined");
                    continue;
                }
                let Some(set)=rulesets.get_mut(set_num-1) else {
                    eprintln!("rule defined before ruleset defined");
                    continue;
                };
                set.rules.push(rule);
            }else {
                eprintln!("parser generator err at line {}: failed to parse rule", i);
                continue;
            }
        }
    }

    if cfg!(feature="debug") {
        println!("parser:");
        rulesets.iter().for_each(|rs| println!("{}",rs));
    }
    rulesets
}

#[test]
fn test_generate_parser_source(){
    let parser_rules=parse_parser_rules("parser.rule");
    generate_parser_source(parser_rules);
}

pub fn generate_parser_source(ruleset:Vec<ParserRuleSet>)->String{
    let mut src=String::new();
    // generate node class definitions
    let mut ruleset_classdefs=String::new();
    let mut rule_classdefs=String::new();
    let mut node_typeenum=Vec::new();
    let mut max_recipe_size=0;
    // this table is used to record the class names of rulesets in generated code
    let mut ruleset_typename_table=HashMap::new();
    // to record the class names of rules in generated code
    let mut rule_typename_table=HashMap::new();
    for rs in ruleset.iter() {
        // generate a base class
        // generate ruleset class name
        let ruleset_class_name = format!("{}_t",rs.name);
        ruleset_typename_table.insert(rs, ruleset_class_name.clone());
        ruleset_classdefs.push_str(&format!("
class {}:public ast_node_t{{
public:
virtual node_type_t get_kind()=0;
}};
",ruleset_class_name)); 
        // generate specific classes
        for rule in rs.rules.iter() {
            let node_type = String::from("NODE_")+&rs.name.to_uppercase();
            // generate members
            let mut member_str=String::new();
            max_recipe_size=max_recipe_size.max(rule.recipe.len());
            rule.struct_members.iter().for_each(|m|{
                let memtypstr=match m.member_type {
                    NodeMemberType::Node=>{
                        let term=&rule.recipe.get(m.pos_in_recipe).unwrap();
                        // we use the general pointer(ruleset node pointer) here
                        &format!("{}_t*",term.value)
                    },
                    NodeMemberType::Token|NodeMemberType::TokenCategory=>"token_t*"
                };
                member_str.push_str(&format!(
                    "{} {};\n",memtypstr,m.name
                ));
            });
            // generate rule class name 
            let rule_class_name=format!("{}_{}_t",rs.name,rule.name);
            // add it to the table
            rule_typename_table.insert(rule, rule_class_name.clone());
            rule_classdefs.push_str(&format!("
class {}:public {}{{
public:
{}
node_type_t get_kind(){{return {};}}
}};
",rule_class_name,ruleset_class_name,member_str,node_type));
            if !node_typeenum.contains(&node_type) {
                node_typeenum.push(node_type);
            }
        }
    }


    // now generate parser functions for each rule
    // we need to capture the tokens one by one
    let mut code_parser_funcs=String::new();
    for rs in ruleset.iter() {
        let mut code_call_rule_func=String::new();
        for rule in rs.rules.iter() {
            /*
            we want code like:
            if(!parse_token(tokenstream, TOKEN_XXX,NULL))return -1;
            if(!(node.member1=parse_token(tokenstream, TOKEN_XX)))return -1;
            if(BELONGS_TO_CATEGORY_XXX(peek_token(tokenstream)->type)){
                node.member2=consume_token(tokenstream);
            }else{return -1;}
            end_parsing(token_steam); // to make pointer actually move
            return 0;
             */
            // we assume the passed class to be filled is called `node`
            let mut code_parsing_lines=String::new();
            for t in rule.recipe.iter() {
                let parsing_line_code=match t.term_type {
                    TermType::SpecificTokenType=>{
                        let token_type_str=format!("TOKEN_{}",t.value.to_uppercase());
                        
                        if t.should_be_stored {
                            format!("
    if(!(node->{}=parse_token(tokenstream,{}))){{tokenstream->reset();delete node;return NULL;}}
",t.to_store_in,token_type_str)
                        } else {
                            format!("
    if(!parse_token(tokenstream,{})){{tokenstream->reset();delete node;return NULL;}}
",token_type_str)
                        }
                    },
                    TermType::TokenCategory=>{
                        format!("
    if(BELONGS_TO_CATEGORY_{}(tokenstream->peek()->token_type)){{
        node->{} = tokenstream->consume();
    }}else{{tokenstream->reset();delete node;return NULL;}}
",t.value.to_uppercase(), t.to_store_in)
                    },
                    TermType::ParserRuleSet=>{
                        // just generate the name of the called function
                        format!("
    if(!(node->{}=parse_{}(tokenstream))){{tokenstream->reset();delete node;return NULL;}}
",t.to_store_in,t.value)

                    }
                };
                code_parsing_lines.push_str(&parsing_line_code);
                code_parsing_lines.push_str("\n");
            }
            // now one parsing func is done
            let ruleset_class_name=format!("{}_{}",rs.name,rule.name);
            code_parser_funcs.push_str(&format!("
{}_t* parse_{}(tokenstream_t *tokenstream){{
    {}_t* node=new {}_t();
    {}
    tokenstream->end_parsing();
    return node;
}}
            ",ruleset_class_name, ruleset_class_name, ruleset_class_name, ruleset_class_name, code_parsing_lines));
            code_call_rule_func.push_str(&format!("
if(node=parse_{}_{}(tokenstream)){{return node;}}
",rs.name,rule.name));
        }
        // now create a ruleset parser_function for calling
        code_parser_funcs.push_str(&format!("
{}_t* parse_{}(tokenstream_t *tokenstream){{
    {}_t* node;
    {}
    return NULL;
}}
",rs.name,rs.name,rs.name,code_call_rule_func));
    }


    let rule_structdef_str=format!("
typedef struct{{
    char* name;
    int (*parser)(tokenstream_t *ts, void* dest);
}}parser_rule_t;
");
    // generate rule array
    let mut rule_array_str=String::new();
    for rs in ruleset.iter() {
        rule_array_str.push_str(&format!(
            "{{.name=\"{}\", .parser=parse_{}}},\n",
            rs.name, rs.name
        ));
    }
    let rule_array_str=format!("
parser_rule_t parser_rules[]={{
{}
}};
    ",rule_array_str);
    // concat the enum defs
    let mut nodetypeenum_str=String::new();
    node_typeenum.iter().for_each(|en| nodetypeenum_str.push_str(&(en.to_string()+",\n")));
    src.push_str(&format!("
typedef enum{{
{}
}}node_type_t;
",nodetypeenum_str));
    src.push_str(&ruleset_classdefs);
    src.push_str(&rule_classdefs);
    src.push_str(&code_parser_funcs);
    src.push_str(&rule_structdef_str);
    src.push_str(&rule_array_str);

    // put generated code into template
    let mut template_reader=File::open("parser_template.cpp").expect("failed to read parser template file");
    let mut template_code=String::new();
    template_reader.read_to_string(&mut template_code).expect("failed to read parser template file");
    template_code=template_code.replace("{%}", &src);
    src=template_code;
    if cfg!(feature="debug") {
        println!("{}",src);
        let mut parser_output=File::create("parser_test.cpp").unwrap();
        parser_output.write_all(src.as_bytes()).unwrap();
    }
    src
}