use std::{env::join_paths, eprint, fs::File, io::{Error, Read, Write}, path::{Path, PathBuf}, println, process};

use clap::Parser;

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
pub fn write_to_file(path:&Path,text:&str)->Result<(),Error> {
    let mut file=File::create(path)?;
    file.write_all(text.as_bytes())
}
pub fn read_from_file(path:&Path)->Result<String,Error>{
    let mut file =File::open(path)?;
    let mut text=String::new();
    file.read_to_string(&mut text)?;
    Ok(text)
}
pub fn read_to_lines(path:&Path)->Result<Vec<String>,Error>{
    let text=read_from_file(path)?;
    Ok(text.split("\n").map(|s| s.to_string()).collect())
}
#[derive(clap::Parser,Debug)]
#[command(version,about,long_about)]
struct Args{
    #[arg(short,long,default_value_t=String::from("template"))]
    template_dir:String,
    #[arg(short,long,default_value_t=String::from("."))]
    output_dir:String,
    #[arg(short,long,default_value_t=String::from("rule"))]
    rules_dir:String,
}
pub struct Envs{
    template_dir:PathBuf,
    output_dir:PathBuf,
    rules_dir:PathBuf,
}
impl Default for Envs {
    fn default() -> Self {
        Self { template_dir: PathBuf::from("template"), output_dir: PathBuf::from("."), rules_dir: PathBuf::from("rule") }
    }
}
fn main() {
    let args=Args::parse();
    let envs=Envs{
        template_dir: PathBuf::from(args.template_dir),
        output_dir: PathBuf::from(args.output_dir),
        rules_dir: PathBuf::from(args.rules_dir),
    };
    let lexerr=envs.rules_dir.join("lexer.rule");
    let parserr= envs.rules_dir.join("parser.rule");
    let sematicr=envs.rules_dir.join("sematic.rule");
    println!("Reading lexer.rule");

    let lexer_rules=parse_lexer_rules(&lexerr);
    if lexer_rules.is_err() {
        print!("{}",lexer_rules.unwrap_err().errs_str());
        return;
    }
    let parser_rules=match parse_parser_rules(&parserr) {
        Ok(rules) => rules,
        Err(d) => { d.print_errs(); return; }
    };
    let lexer_rules=lexer_rules.unwrap();
    let passes=match parse_sematic_rules(&sematicr, &parser_rules) {
        Ok(passes) => passes,
        Err(d) => { d.print_errs(); return; }
    };
    let lexer_code=match generate_lexer_source(lexer_rules,&envs) { 
        Err(d)=>{d.print_errs(); return; }
        Ok(code)=>code
    };
    let parser_code=match generate_parser_source(&parser_rules,&envs) { 
        Err(d)=>{d.print_errs(); return; }
        Ok(code)=>code
    };
    let sematic_code=match generate_sematic_code(&passes, &parser_rules,&envs) {  
        Err(d)=>{d.print_errs(); return;}
        Ok(code)=>code 
    };

    let lexer_cpp=envs.output_dir.join("lexer.cpp");
    let lexer_h=envs.output_dir.join("lexer.h");
    let parser_cpp= envs.output_dir.join("parser.cpp");
    let parser_h= envs.output_dir.join("parser.h");
    let sematic_cpp=envs.output_dir.join("sematic.cpp");
    let sematic_user_cpp=envs.output_dir.join("sematic_user.cpp");
    let sematic_h=envs.output_dir.join("sematic.h");
    if write_to_file(&lexer_cpp, &lexer_code.lexer_cpp).is_err(){
        eprintln!("output err: failed to write lexer.cpp");
    }
    if write_to_file(&lexer_h, &lexer_code.lexer_h).is_err(){
        eprintln!("output err: failed to write lexer.h");
    }
    if write_to_file(&parser_cpp, &parser_code.parser_cpp).is_err(){
        eprintln!("output err: failed to write parser.cpp");

    }
    if write_to_file(&parser_h, &parser_code.parser_h).is_err(){
        eprintln!("output err: failed to write parser.h");

    }
    if write_to_file(&sematic_cpp, &sematic_code.sematic_cpp).is_err(){
        eprintln!("output err: failed to write sematic.cpp");

    }
    if write_to_file(&sematic_h, &sematic_code.sematic_h).is_err(){
        eprintln!("output err: failed to write sematic_user.cpp");

    }
    if write_to_file(&sematic_user_cpp, &sematic_code.sematic_user_cpp).is_err(){
        eprintln!("output err: failed to write sematic.h");

    }

}
#[test]
fn test_flow() {
    let envs=Envs::default();
    let lexer_rules=parse_lexer_rules(Path::new("lexer.rule"));
    if lexer_rules.is_err() {
        print!("{}",lexer_rules.unwrap_err().errs_str());
        return;
    }
    let parser_rules=match parse_parser_rules(Path::new("parser.rule")) {
        Ok(rules) => rules,
        Err(d) => { d.print_errs(); return; }
    };
    let lexer_rules=lexer_rules.unwrap();
    let passes=match parse_sematic_rules(Path::new("sematic.rule"), &parser_rules) {
        Ok(passes) => passes,
        Err(d) => { d.print_errs(); return; }
    };
    if let Err(d)=generate_lexer_source(lexer_rules,&envs) { d.print_errs(); return; }
    if let Err(d)=generate_parser_source(&parser_rules,&envs) { d.print_errs(); return; }
    if let Err(d)=generate_sematic_code(&passes, &parser_rules,&envs) { d.print_errs(); return; }
    let output=process::Command::new("g++").args(vec!["-std=c++17","-c","-I.","lexer_test.cpp","parser_test.cpp","sematic_test.cpp","sematic_test_user.cpp"]).output().unwrap();
    let _=process::Command::new("rm").args(vec!["lexer_test.o","parser_test.o","sematic_test.o","sematic_test_user.o"]).output();
    let out=String::from_utf8(output.stdout).unwrap();
    let err=String::from_utf8(output.stderr).unwrap();
    println!("{}\n{}",out,err);
    assert!(output.status.success())
}