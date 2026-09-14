use std::{fs::File, io::Read};

use regex::regex;

use crate::parser::{ParserRuleSet, parse_parser_rules};
#[derive(Clone)]
struct SematicFunc{
    name:String,
    arguments:Vec<String>,

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
struct SematicPass{
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
            let args=enter.get(2).map_or(Vec::new(), |t| t.as_str().split(",").collect());
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                current_rule.enter.push(SematicFunc { name: func_name.to_string(), arguments: args.iter().map(|s| s.to_string()).collect() });
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
            let args=leave.get(2).map_or(Vec::new(), |t| t.as_str().split(",").collect());
            // push it to the last node (current)
            if let Some(current_rule) = current_rules.iter_mut().nth_back(0){
                current_rule.leave.push(SematicFunc { name: func_name.to_string(), arguments: args.iter().map(|t| t.to_string()).collect() });
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
                r.enter.iter().for_each(|e| println!("enter {}({})",e.name,e.arguments.join(",")));
                if r.children.len()>0 {
                    print!("children ");
                    r.children.iter().for_each(|c| print!("{} ",c.name));
                    println!("");
                }
                r.leave.iter().for_each(|e| println!("leave {}({})",e.name,e.arguments.join(",")));
            }
        }
    }
    passes
}
pub fn generate_sematic_code(passes:&Vec<SematicPass>)->Option<String>{
    let mut src=String::new();
    Some(src)
}
#[test]
fn test_parser_sematic_rules(){
    let ruleset=parse_parser_rules("parser.rule");
    parse_sematic_rules("sematic.rule", &ruleset);
}