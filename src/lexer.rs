use std::{format, fs::{File, OpenOptions}, io::{Read, Write}, println};
use regex;

use crate::{CompgenError, Diagnosis, STAGE_LEXER_CODEGEN, STAGE_LEXER_PARSING, lexer};

#[derive(Clone, Debug)]
pub struct LexerRule{
    name:String,
    pattern_str:String,
    pattern:regex::Regex,
}
impl LexerRule {
    pub fn new(name:&str,pattern_str:&str)->Self{
        Self { name: name.to_string(), pattern_str: pattern_str.to_string(), pattern: regex::Regex::new(pattern_str).expect("failed to compile regex") }
    }
}
#[derive(Clone, Debug)]
pub enum LexerCategory{
    /// A category where rules are defined
    LexerRuleCategory{
        name:String,
        rules:Vec<LexerRule>
    },
    /// A category used simply to put some rules into a category.
    LexerRefCategory{
        name:String,
        refed_rules:Vec<String>,
    }
}
pub fn parse_lexer_rules(path:&str)->Result<Vec<LexerCategory>,Diagnosis>{
    let mut diagnosis=Diagnosis::new();
    let Ok(mut lexer_file) = OpenOptions::new().read(true).open(path) else {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_PARSING, "failed to open lexer file"));
        return Err(diagnosis);
    };

    let mut lexer_file_text=String::new();
    let Ok(_) = lexer_file.read_to_string(&mut lexer_file_text) else {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_PARSING, "failed to read lexer file"));
        return Err(diagnosis);
    };
    
    let lexer_lines=lexer_file_text.split("\n").collect::<Vec<&str>>();

    let mut lexer_categories=Vec::new();
    // start parsing lexer rules
    for (i,line) in lexer_lines.into_iter().enumerate() {
        let line=line.trim();
        if line.len()==0 {
            // empty line
            continue;
        }
        if let Some((name,pat))=line.split_once(":"){
            
            // test compile the pattern
            if regex::Regex::new(pat).is_err(){
                diagnosis.push_err(CompgenError::new(i+1,0,STAGE_LEXER_PARSING,"failed to compile regex"));
                continue;
            }
            let one_rule=LexerRule::new(name, pat);
            
            let category_num=lexer_categories.len();
            if category_num==0 {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_LEXER_PARSING, "lexer rule file parsing err: rule defined before category definition"));
                continue;
            }
            if let Some(current_cat) = lexer_categories.get_mut(category_num-1) {
                match current_cat {
                    // add it to the category
                    LexerCategory::LexerRefCategory { name, refed_rules }=>{
                        refed_rules.push(one_rule.name.to_string());
                    },
                    LexerCategory::LexerRuleCategory { name, rules }=>{
                        // check if this pattern matches empty string, which is not allowed
                        if regex::Regex::new(pat).unwrap().find("").map_or(false, |m| m.start()==0 && m.end()==0) {
                            diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_LEXER_PARSING, "lexer rule file parsing err: empty regex string or regex string that can match empty string"));
                            continue;
                        }
                        rules.push(one_rule);
                    }
                }
            }else {
                diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_LEXER_PARSING, "lexer rule file parsing err: rule defined before category definition"));
                continue;
            }

        }else if line.len()>0 && line.chars().nth(0).unwrap()=='#' {
            // it is a rule category
            let cat_name=&line[1..];
            let cat=LexerCategory::LexerRuleCategory { name: cat_name.to_string(), rules: vec![] };
            lexer_categories.push(cat);
        }else if line.len()>0 && line.chars().nth(0).unwrap()=='~' {
            // it is a ref category
            let cat_name=&line[1..];
            let cat=LexerCategory::LexerRefCategory { name: cat_name.to_string(), refed_rules: vec![] };
            lexer_categories.push(cat);
        }else {
            diagnosis.push_err(CompgenError::new(i+1, 0, STAGE_LEXER_PARSING, "lexer rule file parsing err: failed to parse lexer rule"));
            continue;
        }
    }
    if cfg!(feature="debug") {
        lexer_categories.iter().for_each(|cat|{
            match cat {
                LexerCategory::LexerRefCategory { name, refed_rules }=>{
                    println!("~{}",name);
                    refed_rules.iter().for_each(|rule_name|{
                        println!("{}",rule_name);
                    });
                },
                LexerCategory::LexerRuleCategory { name, rules }=>{
                    println!("#{}",name);
                    rules.iter().for_each(|rule|{
                        println!("{}:{}",rule.name,rule.pattern_str);
                    });
                }
            }
        });
    }
    if diagnosis.is_empty() { Ok(lexer_categories) } else { Err(diagnosis) }
}

pub fn generate_lexer_source(lexer_cats:Vec<LexerCategory>)->Result<String,Diagnosis>{
    let mut diagnosis=Diagnosis::new();
    let mut src=String::from("
    ");
    /*
    A token type enum is defined. For every category, a macro is defined to check if a token type belongs to the category.
     */
    
    let mut cat_check_macros=String::new();
    let mut token_types_collected=Vec::new();
    // collect token types
    for cat in lexer_cats.iter() {
        match cat {
            LexerCategory::LexerRuleCategory { name, rules }=>{
                rules.iter().for_each(|r|{
                    token_types_collected.push(&r.name);
                });
            },
            _=>{}
        }
    }
    // generate token type enum
    let mut token_type_enum=String::new();
    for tt in token_types_collected.iter() {
        token_type_enum.push_str("TOKEN_");
        token_type_enum.push_str(&tt.to_uppercase());
        token_type_enum.push_str(",\n");
    }
    let token_type_enum=format!("
typedef enum{{
{}
}}token_type_t;
    ",token_type_enum);
    // generate category check macro
    for cat in lexer_cats.iter() {
        let mut containing_token_types=Vec::new();
        let cat_name=match cat {
            LexerCategory::LexerRefCategory { name, refed_rules }=>{
                refed_rules.iter().for_each(|name|{
                    containing_token_types.push(name);
                });
                name
            },
            LexerCategory::LexerRuleCategory { name, rules }=>{
                rules.iter().for_each(|rule|{
                    containing_token_types.push(&rule.name);
                });
                name
            }
        };
        let mut check_str=String::new();
        containing_token_types.iter().enumerate().for_each(|(i,toktype)|{
            check_str.push_str("toktype==TOKEN_");
            check_str.push_str(&toktype.to_uppercase());
            if i<containing_token_types.len()-1 {
                check_str.push_str("||");
            }
        });
        let cat_str=format!("
#define BELONGS_TO_CATEGORY_{}(toktype) ({})
        ",cat_name.to_uppercase(),check_str);
        cat_check_macros.push_str(&cat_str);
    }
    // put the token_type enum definition to the header file
    let Ok(mut lexer_header_reader)=File::open("lexer_template.h")else{
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to open lexer header template file"));
        return Err(diagnosis);
    };
    let mut lexer_header_code=String::new();
    let Ok(_)=lexer_header_reader.read_to_string(&mut lexer_header_code) else{
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to read lexer header template file"));
        return Err(diagnosis);
    };
    // merge strs
    let mut temp_str_merge=token_type_enum.clone();
    temp_str_merge.push_str(&cat_check_macros);
    lexer_header_code=lexer_header_code.replace("{%}", &temp_str_merge);
    // generate header file 
    let mut lexer_header_gen = match File::create("lexer.h") {
        Ok(file) => file,
        Err(_) => {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to create or open lexer.h"));
            return Err(diagnosis);
        }
    };
    if lexer_header_gen.write_all(lexer_header_code.as_bytes()).is_err() {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to write to lexer.h"));
        return Err(diagnosis);
    }
    
    // define rule array
    let mut rules_array=String::new();
    let mut rules_num=0;
    for cat in lexer_cats.iter() {
        match cat {
            LexerCategory::LexerRuleCategory { name, rules }=>{
                for rule in rules.iter() {
                    let dealt_pat=rule.pattern_str.replace("\\", "\\\\").replace("\"", "\\\"").replace("\'", "\\\'");
                    rules_array.push_str(&format!("{{\"{}\", \"{}\", TOKEN_{}}},\n",rule.name,dealt_pat,rule.name.to_uppercase()));
                    rules_num+=1;
                }
            },
            _=>{}
        }
    }
    let rules_array=format!("
#define LEXER_RULES_LEN {}
lexer_rule_t lexer_rules[]={{
    {}
}};
",rules_num,rules_array);
    src.push_str(&rules_array);

    let mut template_file=match OpenOptions::new().read(true).open("lexer_template.cpp") {
        Ok(file) => file,
        Err(_) => {
            diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to open lexer template file"));
            return Err(diagnosis);
        }
    };
    let mut template_str=String::new();
    if template_file.read_to_string(&mut template_str).is_err() {
        diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to read lexer template file"));
        return Err(diagnosis);
    }
    src = template_str.replace("{%}", &src);

    if cfg!(feature="debug") {
        println!("{}",src);
        match OpenOptions::new().create(true).write(true).truncate(true).open("lexer_test.cpp") {
            Ok(mut file) => {
                if file.write_all(src.as_bytes()).is_err() {
                    diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to write lexer_test.cpp"));
                }
            }
            Err(_) => diagnosis.push_err(CompgenError::new(0, 0, STAGE_LEXER_CODEGEN, "failed to create lexer_test.cpp")),
        }
    }
    if diagnosis.is_empty() { Ok(src) } else { Err(diagnosis) }
}
#[test]
fn test_generate_lexer_source(){
    let lexer_rules = parse_lexer_rules("lexer.rule").unwrap();
    generate_lexer_source(lexer_rules).unwrap_or_else(|d| {
        print!("{}",d.errs_str());
        String::new()
    });
}
