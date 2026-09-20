#![allow(dead_code)]

use std::path::{Path, PathBuf};

use regex::regex;

use crate::{parser::{NodeMemberType, ParserRuleSet, parse_parser_rules}, read_from_file, write_to_file};

enum TempVarType {
    Value,
    Address,
    Logical
}
#[allow(dead_code)]
struct TempVar{
    name:String,
    vartype:TempVarType
}
impl TempVar {
    fn new(name:&str, vartype:TempVarType) -> Self {
        Self { name: name.to_string(), vartype }
    }
    fn var_name(&self)->String {
        format!("temp_{}",self.name)
    }
}
struct ConversionPos{
    member_name:String,
    node_type_str:String
}
impl ConversionPos {
    fn new(member_name:&str, node_type_str:&str) -> Self {
        Self { member_name: member_name.to_string(), node_type_str: node_type_str.to_string() }
    }
}
struct Label{
    name:String,
}
impl Label {
    fn new(name:&str) -> Self {
        Self { name: name.to_string() }
    }
    fn var_name(&self)->String {
        format!("label_{}",self.name)
    }
}
enum IRInstruction {
    Temp(TempVar),
    Alloc{symbol:String,address:TempVar},
    Cast{conversion_pos:ConversionPos,src:TempVar,dst:TempVar},
    Visit{node:String,result:TempVar},
    VisitRef{node:String,result:TempVar},
    Store{address:TempVar,dest:TempVar},
    Load{address:TempVar,from:TempVar},
    Call{function:String, args:Vec<TempVar>, result:TempVar},
    CallValue{function:TempVar, args:Vec<TempVar>, result:TempVar},
    Yield(TempVar),
    YieldNone,
    Return(TempVar),
    ReturnNone,
    If{condition:TempVar,true_label:Label,false_label:Label},
    Goto(Label),
    Label(Label),
    DeclLabel(Label),

    Add{op1:TempVar,op2:TempVar, dst:TempVar},
    Sub{op1:TempVar,op2:TempVar, dst:TempVar},
    Mul{op1:TempVar,op2:TempVar, dst:TempVar},
    Div{op1:TempVar,op2:TempVar, dst:TempVar},
    Mod{op1:TempVar,op2:TempVar, dst:TempVar},
    Shl{op1:TempVar,op2:TempVar, dst:TempVar},
    Shr{op1:TempVar,op2:TempVar, dst:TempVar},
    Bitand{op1:TempVar,op2:TempVar, dst:TempVar},
    Bitor{op1:TempVar,op2:TempVar, dst:TempVar},
    Bitxor{op1:TempVar,op2:TempVar, dst:TempVar},
    And{op1:TempVar,op2:TempVar, dst:TempVar},
    Or{op1:TempVar,op2:TempVar, dst:TempVar},
    Equ{op1:TempVar,op2:TempVar, dst:TempVar},
    Neq{op1:TempVar,op2:TempVar, dst:TempVar},
    Gt{op1:TempVar,op2:TempVar, dst:TempVar},
    Lt{op1:TempVar,op2:TempVar, dst:TempVar},
    Ge{op1:TempVar,op2:TempVar, dst:TempVar},
    Le{op1:TempVar,op2:TempVar, dst:TempVar},
    Bitnot{op:TempVar, dst:TempVar},
    Negate{op:TempVar, dst:TempVar},
    Minus{op:TempVar, dst:TempVar},
    Deref{op:TempVar, dst:TempVar},
}
impl IRInstruction {
    fn generate_code(&self,rule:&IRRule)->String{
        let mut code=String::new();
        match self {
            IRInstruction::Temp(var)=>{
                code.push_str(&format!("tempvar_t {}=context->create_tempvar();\n",var.var_name()));
            },
            IRInstruction::Cast { conversion_pos, src, dst }=>{
                // Keep the conversion name visible in the generated C++ so later lowering can resolve it.

                code.push_str(&format!("
    graph->add_ir(new ir_cast_t(context->get_conversion(node->{}), {}, {}));\n",conversion_pos.member_name,src.var_name(),dst.var_name()));
            }
            IRInstruction::Visit { node, result }=>{
                code.push_str(&format!("{}=visit(static_cast<{}_{}_t*>(node)->{},graph,context);\n",result.var_name(),rule.ruleset,rule.rule,node));
            }
            IRInstruction::VisitRef { node, result }=>{
                code.push_str(&format!("{}=visit_ref(static_cast<{}_{}_t*>(node)->{},graph,context);\n",result.var_name(),rule.ruleset,rule.rule,node));
            }
            IRInstruction::Store { address, dest }=>{
                code.push_str(&format!("graph->add_ir(new ir_store_t({},{}));\n",address.var_name(),dest.var_name()));
            }
            IRInstruction::Load { address, from }=>{
                code.push_str(&format!("graph->add_ir(new ir_load_t({},{}));\n",address.var_name(),from.var_name()));
            }
            IRInstruction::Call { function, args, result }=>{
                let args_str=args.iter().map(|t| t.var_name()).collect::<Vec<String>>().join(",");
                if result.name.is_empty() {
                    code.push_str(&format!("graph->add_ir(new ir_call_t(\"{}\",{{{}}}, tempvar_t::empty()));\n",function,args_str));
                } else {
                    code.push_str(&format!("graph->add_ir(new ir_call_t(\"{}\",{{{}}}, {}));\n",function,args_str,result.var_name()));
                }
            }
            IRInstruction::CallValue { function, args, result }=>{
                let args_str=args.iter().map(|t| t.var_name()).collect::<Vec<String>>().join(",");
                if result.name.is_empty() {
                    code.push_str(&format!("graph->add_ir(new ir_call_value_t({},{{{}}}, tempvar_t::empty()));\n",function.var_name(),args_str));
                } else {
                    code.push_str(&format!("graph->add_ir(new ir_call_value_t({},{{{}}}, {}));\n",function.var_name(),args_str,result.var_name()));
                }
            }
            IRInstruction::Alloc { symbol, address }=>{
                code.push_str(&format!("graph->add_ir(new ir_alloc_t(context->get_symbol(node), {}));\n",address.var_name()));
            }
            IRInstruction::Yield(value)=>{
                code.push_str(&format!("return {};\n",value.var_name()));
            }
            IRInstruction::YieldNone=>code.push_str("return tempvar_t::empty();\n"),
            IRInstruction::ReturnNone=>code.push_str("graph->add_ir(new ir_return_none_t());\n"),
            IRInstruction::Return(value)=>code.push_str(&format!("graph->add_ir(new ir_return_t({}));\n",value.var_name())),
            IRInstruction::DeclLabel(label)=>{
                code.push_str(&format!("basic_block_id_t {}=graph->create_block();\n",label.var_name()));
            }
            IRInstruction::Goto(label)=>{
                code.push_str(&format!("graph->connect(graph->get_current_block(),{});\n",label.var_name()));
                code.push_str(&format!("graph->add_ir(new ir_goto_t(context->create_or_get_label(\"{}\")));\n",label.var_name()));
            }
            IRInstruction::Label(label)=>{
                code.push_str(&format!("graph->set_current_block({});\n",label.var_name()));
            }
            IRInstruction::If { condition, true_label, false_label }=>{
                let codes=stringify!(
    graph->connect(graph->get_current_block(),{1});
    graph->connect(graph->get_current_block(),{2});
            ).replace("{1}", &true_label.var_name())
            .replace("{2}", &false_label.var_name());
                code.push_str(&codes);
                code.push_str(&format!("graph->add_ir(new ir_if_t({},{},{}));\n",condition.var_name(),true_label.var_name(),false_label.var_name()));
            }
            IRInstruction::Add { op1, op2, dst }|
            IRInstruction::Sub { op1, op2, dst }|
            IRInstruction::Mul { op1, op2, dst }|
            IRInstruction::Div { op1, op2, dst }|
            IRInstruction::Mod { op1, op2, dst }|
            IRInstruction::Shl { op1, op2, dst }|
            IRInstruction::Shr { op1, op2, dst }|
            IRInstruction::Bitand { op1, op2, dst }|
            IRInstruction::Bitor { op1, op2, dst }|
            IRInstruction::Bitxor { op1, op2, dst }|
            IRInstruction::And { op1, op2, dst }|
            IRInstruction::Or { op1, op2, dst }|
            IRInstruction::Equ { op1, op2, dst }|
            IRInstruction::Neq { op1, op2, dst }|
            IRInstruction::Gt { op1, op2, dst }|
            IRInstruction::Lt { op1, op2, dst }|
            IRInstruction::Ge { op1, op2, dst }|
            IRInstruction::Le { op1, op2, dst }=>{
                let op_name = match self {
                    IRInstruction::Add { .. } => "Add",
                    IRInstruction::Sub { .. } => "Sub",
                    IRInstruction::Mul { .. } => "Mul",
                    IRInstruction::Div { .. } => "Div",
                    IRInstruction::Mod { .. } => "Mod",
                    IRInstruction::Shl { .. } => "Shl",
                    IRInstruction::Shr { .. } => "Shr",
                    IRInstruction::Bitand { .. } => "Bitand",
                    IRInstruction::Bitor { .. } => "Bitor",
                    IRInstruction::Bitxor { .. } => "Bitxor",
                    IRInstruction::And { .. } => "And",
                    IRInstruction::Or { .. } => "Or",
                    IRInstruction::Equ { .. } => "Equ",
                    IRInstruction::Neq { .. } => "Neq",
                    IRInstruction::Gt { .. } => "Gt",
                    IRInstruction::Lt { .. } => "Lt",
                    IRInstruction::Ge { .. } => "Ge",
                    IRInstruction::Le { .. } => "Le",
                    _ => unreachable!(),
                };
                code.push_str(&format!("graph->add_ir(new ir_{}_t({}, {}, {}));\n",op_name.to_lowercase(),op1.var_name(),op2.var_name(),dst.var_name()));
            }
            IRInstruction::Bitnot { op, dst }|
            IRInstruction::Negate { op, dst }|
            IRInstruction::Minus { op, dst }|
            IRInstruction::Deref { op, dst }=>{
                let op_name = match self {
                    IRInstruction::Bitnot { .. } => "Bitnot",
                    IRInstruction::Negate { .. } => "Negate",
                    IRInstruction::Minus { .. } => "Minus",
                    IRInstruction::Deref { .. } => "Deref",
                    _ => unreachable!(),
                };
                code.push_str(&format!("graph->add_ir(new ir_{}_t({}, {}));\n",op_name.to_lowercase(),op.var_name(),dst.var_name()));
            }
        }
        code
    }
}
#[allow(dead_code)]
pub struct IRRule{
    ruleset:String,
    rule:String,
    irs:Vec<IRInstruction>
}
impl IRRule {
    fn new(ruleset:&str, rule:&str, irs:Vec<IRInstruction>) -> Self {
        Self { ruleset: ruleset.to_string(), rule: rule.to_string(), irs }
    }
}
fn parse_named_temp(token:&str, line_index:usize, role:&str, vartype:TempVarType) -> Result<TempVar, String> {
    let name = token.strip_prefix('%').ok_or_else(|| {
        format!("ir rule parsing err at line {}: {} must start with % but got {}", line_index + 1, role, token)
    })?;
    if name.is_empty() {
        return Err(format!("ir rule parsing err at line {}: {} is empty", line_index + 1, role));
    }
    Ok(TempVar::new(name, vartype))
}

fn parse_symbol_name(token:&str, line_index:usize, role:&str) -> Result<String, String> {
    let name = token.strip_prefix('$').ok_or_else(|| {
        format!("ir rule parsing err at line {}: {} must start with $ but got {}", line_index + 1, role, token)
    })?;
    if name.is_empty() {
        return Err(format!("ir rule parsing err at line {}: {} is empty", line_index + 1, role));
    }
    Ok(name.to_string())
}

fn parse_label_name(token:&str, line_index:usize, role:&str) -> Result<Label, String> {
    let name = token.strip_prefix('#').ok_or_else(|| {
        format!("ir rule parsing err at line {}: {} must start with # but got {}", line_index + 1, role, token)
    })?;
    if name.is_empty() {
        return Err(format!("ir rule parsing err at line {}: {} is empty", line_index + 1, role));
    }
    Ok(Label::new(name))
}

fn parse_conversion_pos(token:&str, line_index:usize) -> Result<ConversionPos, String> {
    let token = token.strip_prefix('$').ok_or_else(|| {
        format!("ir rule parsing err at line {}: cast conversion must start with $ but got {}", line_index + 1, token)
    })?;
    let (node_type_str, member_part) = token.split_once('(').ok_or_else(|| {
        format!("ir rule parsing err at line {}: invalid cast conversion syntax {}", line_index + 1, token)
    })?;
    let member_name = member_part.strip_suffix(')').ok_or_else(|| {
        format!("ir rule parsing err at line {}: invalid cast conversion syntax {}", line_index + 1, token)
    })?;
    if node_type_str.is_empty() || member_name.is_empty() {
        return Err(format!("ir rule parsing err at line {}: invalid cast conversion syntax {}", line_index + 1, token));
    }
    Ok(ConversionPos::new(member_name, node_type_str))
}

fn parse_optional_result_temp(token: Option<&str>, line_index:usize, instr:&str) -> Result<TempVar, String> {
    match token {
        None => Ok(TempVar::new("", TempVarType::Value)),
        Some(tok) if tok == "=" => Ok(TempVar::new("", TempVarType::Value)),
        Some(tok) => {
            let tok = tok.strip_prefix('=').unwrap_or(tok);
            if tok.is_empty() {
                Ok(TempVar::new("", TempVarType::Value))
            } else {
                parse_named_temp(tok, line_index, instr, TempVarType::Value)
            }
        }
    }
}

fn render_temp(temp:&TempVar) -> String {
    if temp.name.is_empty() {
        String::new()
    } else {
        format!("%{}", temp.name)
    }
}

fn render_label(label:&Label) -> String {
    format!("#{}", label.var_name())
}

fn render_ir_instruction(ins:&IRInstruction) -> String {
    match ins {
        IRInstruction::Temp(temp) => format!("temp {}", render_temp(temp)),
        IRInstruction::Alloc { symbol, address } => format!("alloc ${} {}", symbol, render_temp(address)),
        IRInstruction::Cast { conversion_pos, src, dst } => format!("cast ${}({}) {} {}", conversion_pos.node_type_str, conversion_pos.member_name, render_temp(src), render_temp(dst)),
        IRInstruction::Visit { node, result } => format!("visit {} {}", node, render_temp(result)),
        IRInstruction::VisitRef { node, result } => format!("visit_ref {} {}", node, render_temp(result)),
        IRInstruction::Store { address, dest } => format!("store {} {}", render_temp(address), render_temp(dest)),
        IRInstruction::Load { address, from } => format!("load {} {}", render_temp(address), render_temp(from)),
        IRInstruction::Call { function, args, result } => {
            let mut pieces = vec![function.clone()];
            pieces.extend(args.iter().map(render_temp));
            if result.name.is_empty() {
                pieces.push("=".to_string());
            } else {
                pieces.push(format!("={}", render_temp(result)));
            }
            format!("call {}", pieces.join(" "))
        }
        IRInstruction::CallValue { function, args, result } => {
            let mut pieces = vec![render_temp(function)];
            pieces.extend(args.iter().map(render_temp));
            if result.name.is_empty() {
                pieces.push("=".to_string());
            } else {
                pieces.push(format!("={}", render_temp(result)));
            }
            format!("call_value {}", pieces.join(" "))
        }
        IRInstruction::Yield(temp) => format!("yield {}", render_temp(temp)),
        IRInstruction::YieldNone => String::from("yield_none"),
        IRInstruction::Return(temp) => format!("return {}", render_temp(temp)),
        IRInstruction::ReturnNone => String::from("return_none"),
        IRInstruction::If { condition, true_label, false_label } => format!("if {} {} {}", render_temp(condition), render_label(true_label), render_label(false_label)),
        IRInstruction::Goto(label) => format!("goto {}", render_label(label)),
        IRInstruction::DeclLabel(label) => format!("decllabel {}", render_label(label)),
        IRInstruction::Label(label) => format!("label {}", render_label(label)),
        IRInstruction::Add { op1, op2, dst } => format!("add {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Sub { op1, op2, dst } => format!("sub {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Mul { op1, op2, dst } => format!("mul {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Div { op1, op2, dst } => format!("div {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Mod { op1, op2, dst } => format!("mod {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Shl { op1, op2, dst } => format!("shl {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Shr { op1, op2, dst } => format!("shr {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Bitand { op1, op2, dst } => format!("bitand {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Bitor { op1, op2, dst } => format!("bitor {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Bitxor { op1, op2, dst } => format!("bitxor {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::And { op1, op2, dst } => format!("and {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Or { op1, op2, dst } => format!("or {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Equ { op1, op2, dst } => format!("equ {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Neq { op1, op2, dst } => format!("neq {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Gt { op1, op2, dst } => format!("gt {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Lt { op1, op2, dst } => format!("lt {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Ge { op1, op2, dst } => format!("ge {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Le { op1, op2, dst } => format!("le {} {} {}", render_temp(op1), render_temp(op2), render_temp(dst)),
        IRInstruction::Bitnot { op, dst } => format!("bitnot {} {}", render_temp(op), render_temp(dst)),
        IRInstruction::Negate { op, dst } => format!("negate {} {}", render_temp(op), render_temp(dst)),
        IRInstruction::Minus { op, dst } => format!("minus {} {}", render_temp(op), render_temp(dst)),
        IRInstruction::Deref { op, dst } => format!("deref {} {}", render_temp(op), render_temp(dst)),
    }
}

pub fn parse_ir_rule(path:&str)->Result<Vec<IRRule>,String>{
    let mut rules: Vec<IRRule> = Vec::new();
    let text=read_from_file(Path::new(path)).map_err(|e| format!("failed to read ir rule file: {}", e))?;
    let lines=text.split('\n').collect::<Vec<&str>>();

    let pat_node=regex!(r"^([\w_]+)\.([\w_]+):$");
    let mut current_rule: Option<IRRule> = None;
    let mut debug_dump=String::new();

    for (i,raw_line) in lines.into_iter().enumerate() {
        let line=raw_line.trim();
        if line.is_empty() {
            continue;
        }

        if let Some(nodecap) = pat_node.captures(line) {
            // Flush the previous rule before starting a new one.
            if let Some(rule) = current_rule.take() {
                rules.push(rule);
            }
            let ruleset=nodecap.get(1).unwrap().as_str();
            let rule=nodecap.get(2).unwrap().as_str();
            if cfg!(feature="debug") {
                debug_dump.push_str(&format!("{}.{}:\n", ruleset, rule));
            }
            current_rule=Some(IRRule::new(ruleset, rule, vec![]));
            continue;
        }

        let Some(rule)=current_rule.as_mut() else {
            eprintln!("ir rule parsing err at line {}: instruction before any rule header", i + 1);
            return Err(format!("ir parsing err at line {}", i + 1));
        };

        let tokens=line.split_whitespace().collect::<Vec<&str>>();
        if tokens.is_empty() {
            continue;
        }

        let instr=tokens[0];
        let instruction=match instr {
            "temp" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: temp expects 1 argument", i + 1));
                }
                IRInstruction::Temp(parse_named_temp(tokens[1], i, "temp", TempVarType::Value)?)
            }
            "alloc" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: alloc expects 2 arguments", i + 1));
                }
                let symbol=parse_symbol_name(tokens[1], i, "alloc symbol")?;
                let address=parse_named_temp(tokens[2], i, "alloc address", TempVarType::Address)?;
                IRInstruction::Alloc { symbol, address }
            }
            "cast" => {
                if tokens.len()!=4 {
                    return Err(format!("ir rule parsing err at line {}: cast expects 3 arguments", i + 1));
                }
                let conversion_pos=parse_conversion_pos(tokens[1], i)?;
                let src=parse_named_temp(tokens[2], i, "cast src", TempVarType::Value)?;
                let dst=parse_named_temp(tokens[3], i, "cast dst", TempVarType::Value)?;
                IRInstruction::Cast { conversion_pos, src, dst }
            }
            "visit" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: visit expects 2 arguments", i + 1));
                }
                IRInstruction::Visit { node: tokens[1].to_string(), result: parse_named_temp(tokens[2], i, "visit result", TempVarType::Value)? }
            }
            "visit_ref" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: visit_ref expects 2 arguments", i + 1));
                }
                IRInstruction::VisitRef { node: tokens[1].to_string(), result: parse_named_temp(tokens[2], i, "visit_ref result", TempVarType::Address)? }
            }
            "store" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: store expects 2 arguments", i + 1));
                }
                IRInstruction::Store { address: parse_named_temp(tokens[1], i, "store address", TempVarType::Address)?, dest: parse_named_temp(tokens[2], i, "store dest", TempVarType::Value)? }
            }
            "load" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: load expects 2 arguments", i + 1));
                }
                IRInstruction::Load { address: parse_named_temp(tokens[1], i, "load address", TempVarType::Address)?, from: parse_named_temp(tokens[2], i, "load result", TempVarType::Value)? }
            }
            "call" => {
                if tokens.len()<2 {
                    return Err(format!("ir rule parsing err at line {}: call expects a function name", i + 1));
                }
                let function=tokens[1].to_string();
                let result_pos=tokens.iter().enumerate().skip(2).find(|(_,tok)| tok.starts_with('='));
                let args_end=result_pos.map(|(idx,_)| idx).unwrap_or(tokens.len());
                let args=tokens[2..args_end]
                    .iter()
                    .map(|tok| parse_named_temp(tok, i, "call arg", TempVarType::Value))
                    .collect::<Result<Vec<_>, _>>()?;
                let result=parse_optional_result_temp(result_pos.map(|(_,tok)| *tok), i, "call result")?;
                IRInstruction::Call { function, args, result }
            }
            "call_value" => {
                if tokens.len()<2 {
                    return Err(format!("ir rule parsing err at line {}: call_value expects a function temp", i + 1));
                }
                let function=parse_named_temp(tokens[1], i, "call_value function", TempVarType::Value)?;
                let result_pos=tokens.iter().enumerate().skip(2).find(|(_,tok)| tok.starts_with('='));
                let args_end=result_pos.map(|(idx,_)| idx).unwrap_or(tokens.len());
                let args=tokens[2..args_end]
                    .iter()
                    .map(|tok| parse_named_temp(tok, i, "call_value arg", TempVarType::Value))
                    .collect::<Result<Vec<_>, _>>()?;
                let result=parse_optional_result_temp(result_pos.map(|(_,tok)| *tok), i, "call_value result")?;
                IRInstruction::CallValue { function, args, result }
            }
            "yield" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: yield expects 1 argument", i + 1));
                }
                IRInstruction::Yield(parse_named_temp(tokens[1], i, "yield value", TempVarType::Value)?)
            }
            "yield_none" => {
                if tokens.len()!=1 {
                    return Err(format!("ir rule parsing err at line {}: yield_none takes no arguments", i + 1));
                }
                IRInstruction::YieldNone
            }
            "return" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: return expects 1 argument", i + 1));
                }
                IRInstruction::Return(parse_named_temp(tokens[1], i, "return value", TempVarType::Value)?)
            }
            "return_none" => {
                if tokens.len()!=1 {
                    return Err(format!("ir rule parsing err at line {}: return_none takes no arguments", i + 1));
                }
                IRInstruction::ReturnNone
            }
            "if" => {
                if tokens.len()!=4 {
                    return Err(format!("ir rule parsing err at line {}: if expects 3 arguments", i + 1));
                }
                IRInstruction::If {
                    condition: parse_named_temp(tokens[1], i, "if condition", TempVarType::Logical)?,
                    true_label: parse_label_name(tokens[2], i, "if true label")?,
                    false_label: parse_label_name(tokens[3], i, "if false label")?,
                }
            }
            "goto" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: goto expects 1 argument", i + 1));
                }
                IRInstruction::Goto(parse_label_name(tokens[1], i, "goto label")?)
            }
            "label" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: label expects 1 argument", i + 1));
                }
                IRInstruction::Label(parse_label_name(tokens[1], i, "label name")?)
            }
            "decllabel" => {
                if tokens.len()!=2 {
                    return Err(format!("ir rule parsing err at line {}: decllabel expects 1 argument", i + 1));
                }
                IRInstruction::DeclLabel(parse_label_name(tokens[1], i, "decllabel name")?)
            }
            "add" | "sub" | "mul" | "div" | "mod" | "shl" | "shr" | "bitand" | "bitor" | "bitxor" | "and" | "or" | "equ" | "neq" | "gt" | "lt" | "ge" | "le" => {
                if tokens.len()!=4 {
                    return Err(format!("ir rule parsing err at line {}: {} expects 3 arguments", i + 1, instr));
                }
                let op1=parse_named_temp(tokens[1], i, &format!("{} op1", instr), TempVarType::Value)?;
                let op2=parse_named_temp(tokens[2], i, &format!("{} op2", instr), TempVarType::Value)?;
                let dst_type=if matches!(instr, "and" | "or" | "equ" | "neq" | "gt" | "lt" | "ge" | "le") { TempVarType::Logical } else { TempVarType::Value };
                let dst=parse_named_temp(tokens[3], i, &format!("{} dst", instr), dst_type)?;
                match instr {
                    "add" => IRInstruction::Add { op1, op2, dst },
                    "sub" => IRInstruction::Sub { op1, op2, dst },
                    "mul" => IRInstruction::Mul { op1, op2, dst },
                    "div" => IRInstruction::Div { op1, op2, dst },
                    "mod" => IRInstruction::Mod { op1, op2, dst },
                    "shl" => IRInstruction::Shl { op1, op2, dst },
                    "shr" => IRInstruction::Shr { op1, op2, dst },
                    "bitand" => IRInstruction::Bitand { op1, op2, dst },
                    "bitor" => IRInstruction::Bitor { op1, op2, dst },
                    "bitxor" => IRInstruction::Bitxor { op1, op2, dst },
                    "and" => IRInstruction::And { op1, op2, dst },
                    "or" => IRInstruction::Or { op1, op2, dst },
                    "equ" => IRInstruction::Equ { op1, op2, dst },
                    "neq" => IRInstruction::Neq { op1, op2, dst },
                    "gt" => IRInstruction::Gt { op1, op2, dst },
                    "lt" => IRInstruction::Lt { op1, op2, dst },
                    "ge" => IRInstruction::Ge { op1, op2, dst },
                    "le" => IRInstruction::Le { op1, op2, dst },
                    _ => unreachable!(),
                }
            }
            "bitnot" | "negate" | "minus" | "deref" => {
                if tokens.len()!=3 {
                    return Err(format!("ir rule parsing err at line {}: {} expects 2 arguments", i + 1, instr));
                }
                let op=parse_named_temp(tokens[1], i, &format!("{} op", instr), TempVarType::Value)?;
                let dst=parse_named_temp(tokens[2], i, &format!("{} dst", instr), TempVarType::Value)?;
                match instr {
                    "bitnot" => IRInstruction::Bitnot { op, dst },
                    "negate" => IRInstruction::Negate { op, dst },
                    "minus" => IRInstruction::Minus { op, dst },
                    "deref" => IRInstruction::Deref { op, dst },
                    _ => unreachable!(),
                }
            }
            other => {
                return Err(format!("ir rule parsing err at line {}: unknown instruction {}", i + 1, other));
            }
        };

        // Keep a canonical text dump so debug mode can show exactly what was decoded.
        if cfg!(feature="debug") {
            debug_dump.push_str("    ");
            debug_dump.push_str(&render_ir_instruction(&instruction));
            debug_dump.push('\n');
        }

        rule.irs.push(instruction);
    }

    // Flush the final rule after the loop ends.
    if let Some(rule) = current_rule.take() {
        rules.push(rule);
    }

    if cfg!(feature="debug") {
        println!("{}", debug_dump);
    }

    Ok(rules)
}
pub fn generate_ir_source(rules:&Vec<IRRule>, parser_ruleset:&Vec<ParserRuleSet>)->Result<String,String>{
    let mut code=read_from_file(Path::new("ir_template.cpp")).expect("failed to read ir_template.cpp");
    let branches={
        let mut b=vec![];
        for rs in parser_ruleset.iter() {
            for r in rs.rules.iter() {
                let br=format!("\tcase NODE_{}_{}:\n\ttemp_result=ir_{}_{}(static_cast<{}_{}_t*>(node),graph,context);\n\tbreak;\n",rs.name.to_uppercase(),r.name.to_uppercase(),rs.name,r.name,rs.name,r.name);
                b.push(br);
            }
        }
        b.join("\n\t")
    };
    code=code.replace("{%}", &branches);
    let mut funcs=String::new();
    let mut gened=vec![];
    for rule in rules.iter(){
        let mut inside_code=String::new();
        rule.irs.iter().for_each(|ir| {
            let ins=ir.generate_code(rule); 
            inside_code.push_str(&ins);
        });
        let func=format!("
tempvar_t ir_{}_{}({}_{}_t* node,ir_graph_t* graph,ir_context_t* context){{
    {}
}}
        ",rule.ruleset,rule.rule,rule.ruleset,rule.rule,inside_code);
        funcs.push_str(&func);
        gened.push((&rule.ruleset,&rule.rule));
    }
    // generate default handler for other nodes
    for rs in parser_ruleset.iter() {
        for r in rs.rules.iter() {
            if !gened.contains(&(&rs.name,&r.name)) {
                // need to add
                let access_members=r.struct_members.iter().filter_map(|m| if m.member_type==NodeMemberType::Node {
                        Some(format!("visit(node->{},graph,context);",m.name))
                    }else {
                        None
                    }
                ).collect::<Vec<String>>().join("\n\t");
                let func=format!("
tempvar_t ir_{}_{}({}_{}_t* node,ir_graph_t* graph,ir_context_t* context){{
    {}
    return tempvar_t::empty();
}}
",rs.name,r.name,rs.name,r.name,access_members);
                funcs.push_str(&func);
            }
        }
    }
    code=code.replace("{funcs}", &funcs);
    if cfg!(feature="debug") {
        write_to_file(Path::new("ir_test.cpp"), &code).unwrap();
    }
    Ok(code)
}
#[test]
pub fn test_parse_ir_rules(){
    parse_ir_rule("ir.rule").unwrap();
}
#[test]
pub fn test_generate_ir_source() {
    let parser_rules=parse_parser_rules(Path::new("parser.rule")).unwrap();
    let irr=parse_ir_rule("ir.rule").unwrap();
    generate_ir_source(&irr,&parser_rules).unwrap();
}
