use std::{eprint, println};

use crate::lexer::{generate_lexer_source, parse_lexer_rules};

pub mod lexer;
fn main() {
    println!("Reading lexer.rule");
    let lexer_rules=parse_lexer_rules("lexer.rule");
    if lexer_rules.is_none() {
        eprintln!("failed to do lexing");
        return;
    }
    let lexer_rules=lexer_rules.unwrap();
    let lexer_code=generate_lexer_source(lexer_rules);
}
