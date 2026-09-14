use std::{eprint, println};

use crate::{lexer::{generate_lexer_source, parse_lexer_rules}, parser::{generate_parser_source, parse_parser_rules}};

pub mod lexer;
pub mod parser;
pub mod sematic;
fn main() {
    println!("Reading lexer.rule");
    let lexer_rules=parse_lexer_rules("lexer.rule");
    if lexer_rules.is_none() {
        eprintln!("failed to do lexing");
        return;
    }
    let parser_rules=parse_parser_rules("parser.rule");
    let lexer_rules=lexer_rules.unwrap();
    let lexer_code=generate_lexer_source(lexer_rules);
    let parser_code=generate_parser_source(parser_rules);
}
