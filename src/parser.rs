use std::{cmp, collections::HashMap, eprintln, fmt::{Display, Pointer, format}, format, fs::File, hash::Hash, io::{Read, Write}, println, vec, write};

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
    struct_members:Vec<NodeMember>,
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
                NodeMemberType::Token|NodeMemberType::TokenCategory=>format!("token_t *{}",m.name),
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
                    format!("{}* {}",rs_class_name,m.name)
                }
            }
        }).collect::<Vec<String>>().join(";\n\t");
        format!("class {}:public {}_t{{
    public:
    {};
    ~{}() override{{
        {}
    }}
    node_type_t get_kind(){{return NODE_{};}}
}};",self.get_class_name(ruleset_name),ruleset_name,member_str,self.get_class_name(ruleset_name),member_disposal_str,ruleset_name.to_uppercase())
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
                        format!("if(!(node->{}=parse_token(tokenstream,TOKEN_{}))){{tokenstream->reset();delete node;return nullptr;}}",t.to_store_in,t.value.to_uppercase())
                    }else {
                        format!("if(!(parse_token(tokenstream,TOKEN_{}))){{tokenstream->reset();delete node;return nullptr;}}",t.value.to_uppercase())
                    }
                }
                TermType::TokenCategory=>{
                    if t.should_be_stored {
                        format!("if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_{}(tokenstream->peek()->token_type)){{node->{}=tokenstream->consume();}}else{{tokenstream->reset();delete node;return nullptr;}}",t.value.to_uppercase(),t.to_store_in)
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
    {first_member}
    {}
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
    name:String,
    rules:Vec<ParserRule>,
    has_left_combined:bool
}
impl ParserRuleSet {
    fn get_class_name(&self)->String {
        format!("{}_t",self.name)
    }
    fn gen_class_code(&self)->String {
        format!("class {}:ast_node_t{{
    public:
    virtual node_type_t get_kind()=0;
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
        {rs}* next=nullptrptr;
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
    parse_parser_rules("parser.rule");
}
pub fn parse_parser_rules(path:&str)->Vec<ParserRuleSet>{
    let mut rule_file_text=String::new();
    let mut rule_file=File::open(path).unwrap();
    rule_file.read_to_string(&mut rule_file_text).expect("failed to read lexer file");

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
                    if {
                        content[cap_start..cap_match.start()].chars().any(|c| !c.is_whitespace())  
                    } {
                        // there are some invalid chars in between
                        eprintln!("parsergen err: invalid chars between col {} and col {}, line {}",cap_start,cap_match.start(),i+1);
                    }
                    if cap_match.as_str()=="!" {
                        // empty
                        break;
                    }
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
                let set_num=rulesets.len();
                if set_num==0 {
                    eprintln!("rule defined before ruleset defined");
                    continue;
                }
                let Some(set)=rulesets.get_mut(set_num-1) else {
                    eprintln!("rule defined before ruleset defined");
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
            let node_type = String::from("NODE_")+&rs.name.to_uppercase();
            // create the ruleclass
            rule_classdefs.push(rule.gen_class_code(&rs.name, &ruleset));
            if !node_typeenum.contains(&node_type) {
                node_typeenum.push(node_type);
            }
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
    char* name;
    ast_node_t* (*parser)(tokenstream_t *ts);
}}parser_rule_t;
");
    // generate rule array
    let mut rule_array_str=String::new();
    // find the reserved top_statement ruleset as make it the top parser that calls all the other parsers 
    if let Some(top_stmt_ruleset) = ruleset.iter().find(|rs| rs.name=="top_statement"){
        rule_array_str.push_str(&format!(
            "{{.name=\"{}\", .parser=(ast_node_t* (*)(tokenstream_t*))parse_{}}},\n",top_stmt_ruleset.name,top_stmt_ruleset.get_class_name()
        ));
    }else {
        eprintln!("parsergen err: cannot find necessary ruleset 'top_statement'");
        return String::new();
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
    src.push_str(&ruleset_classdefs.join("\n"));
    src.push('\n');
    src.push_str(&rule_classdefs.join("\n"));
    src.push('\n');
    src.push_str(&code_parser_func_decls.join("\n"));
    src.push('\n');
    src.push_str(&code_parser_funcs.join("\n"));
    src.push('\n');
    src.push_str(&rule_structdef_str);
    src.push_str(&rule_array_str);

    // put generated code into template
    let mut template_reader=File::open("parser_template.cpp").expect("failed to read parser template file");
    let mut template_code=String::new();
    template_reader.read_to_string(&mut template_code).expect("failed to read parser template file");
    template_code=template_code.replace("{%}", &src);
    src=template_code;
    if cfg!(feature="debug") {
        // println!("{}",src);
        let mut parser_output=File::create("parser_test.cpp").unwrap();
        parser_output.write_all(src.as_bytes()).unwrap();
    }
    src
}