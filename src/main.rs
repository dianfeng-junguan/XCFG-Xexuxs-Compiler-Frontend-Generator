use std::{eprint, fs::File, io::{Error, Read, Write}, println, process};

use crate::{ir::{generate_ir_source, parse_ir_rule}, lexer::{generate_lexer_source, parse_lexer_rules}, parser::{generate_parser_source, parse_parser_rules}, sematic::{generate_sematic_code, parse_sematic_rules}};

pub mod lexer;
pub mod parser;
pub mod sematic;
pub mod ir;
#[derive(Debug)]
pub struct CompgenError{
    line:usize,
    column:usize,
    stage:String,
    message:String
}
impl CompgenError {
    pub fn new(line:usize,column:usize,stage:&str,msg:&str) -> Self {
        Self { line, column, stage: stage.to_string(), message: msg.to_string() }
    }
}
impl ToString for CompgenError {
    fn to_string(&self) -> String {
        format!("{} error at line {}, column {}:{}",self.stage,self.line,self.column,self.message)
    }
}
pub const STAGE_LEXER_PARSING:&str="lexer rule parsing";
pub const STAGE_LEXER_CODEGEN:&str="lexer codegen";
pub const STAGE_PARSER_PARSING:&str="parser rule parsing";
pub const STAGE_PARSER_CODEGEN:&str="parser codegen";
pub const STAGE_SEMATIC_PARSING:&str="sematic rule parsing";
pub const STAGE_SEMATIC_CODEGEN:&str="sematic codegen";

#[derive(Debug)]
pub struct Diagnosis{
    errs:Vec<CompgenError>
}
impl Diagnosis {
    pub fn new() -> Self {
        Self { errs: Vec::new() }
    }
    pub fn push_err(&mut self,err:CompgenError) {
        self.errs.push(err);
    }
    pub fn print_errs(&self) {
        print!("{}",self.errs_str());
    }
    pub fn errs_str(&self)->String {
        self.errs.iter().map(|err| err.to_string()).collect::<Vec<String>>().join("\n")
    }
    pub fn is_empty(&self) -> bool {
        self.errs.is_empty()
    }
}
pub fn write_to_file(path:&str,text:&str)->Result<(),Error> {
    let mut file=File::create(path)?;
    file.write_all(text.as_bytes())
}
pub fn read_from_file(path:&str)->Result<String,Error>{
    let mut file =File::open(path)?;
    let mut text=String::new();
    file.read_to_string(&mut text)?;
    Ok(text)
}
pub fn read_to_lines(path:&str)->Result<Vec<String>,Error>{
    let text=read_from_file(path)?;
    Ok(text.split("\n").map(|s| s.to_string()).collect())
}
fn main() {
    println!("Reading lexer.rule");
    let lexer_rules=parse_lexer_rules("lexer.rule");
    if lexer_rules.is_err() {
        print!("{}",lexer_rules.unwrap_err().errs_str());
        return;
    }
    let parser_rules=match parse_parser_rules("parser.rule") {
        Ok(rules) => rules,
        Err(d) => { d.print_errs(); return; }
    };
    let lexer_rules=lexer_rules.unwrap();
    let passes=match parse_sematic_rules("sematic.rule", &parser_rules) {
        Ok(passes) => passes,
        Err(d) => { d.print_errs(); return; }
    };
    if let Err(d)=generate_lexer_source(lexer_rules) { d.print_errs(); return; }
    if let Err(d)=generate_parser_source(&parser_rules) { d.print_errs(); return; }
    if let Err(d)=generate_sematic_code(&passes, &parser_rules) { d.print_errs(); return; }
}
#[test]
fn test_flow() {
    let lexer_rules=parse_lexer_rules("lexer.rule");
    if lexer_rules.is_err() {
        print!("{}",lexer_rules.unwrap_err().errs_str());
        return;
    }
    let parser_rules=match parse_parser_rules("parser.rule") {
        Ok(rules) => rules,
        Err(d) => { d.print_errs(); return; }
    };
    let lexer_rules=lexer_rules.unwrap();
    let passes=match parse_sematic_rules("sematic.rule", &parser_rules) {
        Ok(passes) => passes,
        Err(d) => { d.print_errs(); return; }
    };
    if let Err(d)=generate_lexer_source(lexer_rules) { d.print_errs(); return; }
    if let Err(d)=generate_parser_source(&parser_rules) { d.print_errs(); return; }
    if let Err(d)=generate_sematic_code(&passes, &parser_rules) { d.print_errs(); return; }
    let output=process::Command::new("g++").args(vec!["-std=c++17","-c","-I.","lexer_test.cpp","parser_test.cpp","sematic_test.cpp","sematic_test_user.cpp"]).output().unwrap();
    let _=process::Command::new("rm").args(vec!["lexer_test.o","parser_test.o","sematic_test.o","sematic_test_user.o"]).output();
    let out=String::from_utf8(output.stdout).unwrap();
    let err=String::from_utf8(output.stderr).unwrap();
    println!("{}\n{}",out,err);
    assert!(output.status.success())
}