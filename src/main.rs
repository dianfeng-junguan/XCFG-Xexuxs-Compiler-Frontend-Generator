use std::{eprint, fs::File, io::{Error, Read, Write}, println};

use crate::{ir::{generate_ir_source, parse_ir_rule}, lexer::{generate_lexer_source, parse_lexer_rules}, parser::{generate_parser_source, parse_parser_rules}, sematic::{generate_sematic_code, parse_sematic_rules}};

pub mod lexer;
pub mod parser;
pub mod sematic;
pub mod ir;
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
    if lexer_rules.is_none() {
        eprintln!("failed to do lexing");
        return;
    }
    let parser_rules=parse_parser_rules("parser.rule");
    let lexer_rules=lexer_rules.unwrap();
    let passes=&parse_sematic_rules("sematic.rule", &parser_rules);
    let ir_rules=parse_ir_rule("ir.rule").unwrap();
    let lexer_code=generate_lexer_source(lexer_rules);
    let parser_code=generate_parser_source(&parser_rules);
    let sematic_code=generate_sematic_code(passes, &parser_rules).unwrap();
    let ir_code=generate_ir_source(&ir_rules).unwrap();
}
