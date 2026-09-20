#pragma once
#include "sematic.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
class label_t{
public:
    int id;
    std::string name;
};

class tempvar_t{
public:
    int id;
    tempvar_t(int id):id(id){}
    static tempvar_t empty(){
        return tempvar_t(-1);
    }
};
enum class ir_type_t{
    temp,
    cast,
    visit,
    visit_ref,
    store,
    load,
    call,
    call_value,
    alloc,
    yield,
    yield_none,
    do_return,
    do_return_none,
    if_else,
    do_goto,
    label,

    assign,
    add,
    sub,
    mul,
    div,
    mod,
    do_bitand,
    do_bitor,
    bitxor,
    bitnot,
    shl,
    shr,
    do_and,
    do_or,
    negate,
    minus,
    deref,
    eq,
    neq,
    lt,
    lte,
    gt,
    gte
};
class ir_t{
public:
    ir_type_t type;
    std::vector<void*> args;
    bool is_terminator(){
        switch(type){
            case ir_type_t::do_return:
            case ir_type_t::do_return_none:
            case ir_type_t::if_else:
            case ir_type_t::do_goto:
                return true;
            default:
                return false;
        }
    }
    bool is_rule_ending(){
        switch(type){
            case ir_type_t::yield:
            case ir_type_t::yield_none:
                return true;
            default:
                return false;
        }
    }
};
class ir_temp_t:public ir_t{
public:
    tempvar_t tempvar;
    ir_temp_t(tempvar_t tempvar):tempvar(tempvar){
        type=ir_type_t::temp;
    }
};

class ir_assign_t:public ir_t{
public:
    tempvar_t dst;
    tempvar_t src;
    ir_assign_t(tempvar_t dst, tempvar_t src):dst(dst),src(src){
        type=ir_type_t::assign;
    }
};

class ir_cast_t:public ir_t{
public:
    conversion_t* conversion;
    tempvar_t src;
    tempvar_t dst;
    ir_cast_t(conversion_t* conversion, tempvar_t src, tempvar_t dst):conversion(conversion),src(src),dst(dst){
        type=ir_type_t::cast;
    }
};

class ir_visit_t:public ir_t{
public:
    std::string node;
    tempvar_t result;
    ir_visit_t(std::string node, tempvar_t result):node(node),result(result){
        type=ir_type_t::visit;
    }
};

class ir_visit_ref_t:public ir_t{
public:
    std::string node;
    tempvar_t result;
    ir_visit_ref_t(std::string node, tempvar_t result):node(node),result(result){
        type=ir_type_t::visit_ref;
    }
};

class ir_store_t:public ir_t{
public:
    tempvar_t address;
    tempvar_t dest;
    ir_store_t(tempvar_t address, tempvar_t dest):address(address),dest(dest){
        type=ir_type_t::store;
    }
};

class ir_load_t:public ir_t{
public:
    tempvar_t address;
    tempvar_t from;
    ir_load_t(tempvar_t address, tempvar_t from):address(address),from(from){
        type=ir_type_t::load;
    }
};

class ir_call_t:public ir_t{
public:
    std::string function;
    std::vector<tempvar_t> args;
    tempvar_t result;
    ir_call_t(std::string function, std::vector<tempvar_t> args, tempvar_t result):function(function),args(args),result(result){
        type=ir_type_t::call;
    }
};

class ir_call_value_t:public ir_t{
public:
    tempvar_t function;
    std::vector<tempvar_t> args;
    tempvar_t result;
    ir_call_value_t(tempvar_t function, std::vector<tempvar_t> args, tempvar_t result):function(function),args(args),result(result){
        type=ir_type_t::call_value;
    }
};

class ir_alloc_t:public ir_t{
public:
    symbol_t* symbol;
    tempvar_t address;
    ir_alloc_t(symbol_t* symbol, tempvar_t address):symbol(symbol),address(address){
        type=ir_type_t::alloc;
    }
};

class ir_yield_t:public ir_t{
public:
    tempvar_t value;
    ir_yield_t(tempvar_t value):value(value){
        type=ir_type_t::yield;
    }
};

class ir_yield_none_t:public ir_t{
public:
    ir_yield_none_t(){
        type=ir_type_t::yield_none;
    }
};

class ir_return_t:public ir_t{
public:
    tempvar_t value;
    ir_return_t(tempvar_t value):value(value){
        type=ir_type_t::do_return;
    }
};

class ir_return_none_t:public ir_t{
public:
    ir_return_none_t(){
        type=ir_type_t::do_return_none;
    }
};

class ir_if_t:public ir_t{
public:
    tempvar_t condition;
    label_t true_label;
    label_t false_label;
    ir_if_t(tempvar_t condition, label_t true_label, label_t false_label):condition(condition),true_label(true_label),false_label(false_label){
        type=ir_type_t::if_else;
    }
};

class ir_goto_t:public ir_t{
public:
    label_t label;
    ir_goto_t(label_t label):label(label){
        type=ir_type_t::do_goto;
    }
};

class ir_label_t:public ir_t{
public:
    label_t label;
    ir_label_t(label_t label):label(label){
        type=ir_type_t::label;
    }
};

class ir_add_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_add_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::add;
    }
};

class ir_sub_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_sub_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::sub;
    }
};

class ir_mul_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_mul_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::mul;
    }
};

class ir_div_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_div_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::div;
    }
};

class ir_mod_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_mod_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::mod;
    }
};

class ir_shl_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_shl_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::shl;
    }
};

class ir_shr_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_shr_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::shr;
    }
};

class ir_bitand_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_bitand_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::do_bitand;
    }
};

class ir_bitor_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_bitor_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::do_bitor;
    }
};

class ir_bitxor_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_bitxor_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::bitxor;
    }
};

class ir_and_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_and_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::do_and;
    }
};

class ir_or_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_or_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::do_or;
    }
};

class ir_equ_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_equ_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::eq;
    }
};

class ir_neq_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_neq_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::neq;
    }
};

class ir_gt_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_gt_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::gt;
    }
};

class ir_lt_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_lt_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::lt;
    }
};

class ir_ge_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_ge_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::gte;
    }
};

class ir_le_t:public ir_t{
public:
    tempvar_t op1;
    tempvar_t op2;
    tempvar_t dst;
    ir_le_t(tempvar_t op1, tempvar_t op2, tempvar_t dst):op1(op1),op2(op2),dst(dst){
        type=ir_type_t::lte;
    }
};

class ir_bitnot_t:public ir_t{
public:
    tempvar_t op;
    tempvar_t dst;
    ir_bitnot_t(tempvar_t op, tempvar_t dst):op(op),dst(dst){
        type=ir_type_t::bitnot;
    }
};

class ir_negate_t:public ir_t{
public:
    tempvar_t op;
    tempvar_t dst;
    ir_negate_t(tempvar_t op, tempvar_t dst):op(op),dst(dst){
        type=ir_type_t::negate;
    }
};

class ir_minus_t:public ir_t{
public:
    tempvar_t op;
    tempvar_t dst;
    ir_minus_t(tempvar_t op, tempvar_t dst):op(op),dst(dst){
        type=ir_type_t::minus;
    }
};

class ir_deref_t:public ir_t{
public:
    tempvar_t op;
    tempvar_t dst;
    ir_deref_t(tempvar_t op, tempvar_t dst):op(op),dst(dst){
        type=ir_type_t::deref;
    }
};
using basic_block_id_t = int;
class basic_block_t{
public:
    label_t label;
    int id;
    std::vector<basic_block_id_t> successors;
    std::vector<basic_block_id_t> predecessors;
    std::vector<std::unique_ptr<ir_t>> instructions;
    basic_block_t(int id):id(id){}
    void push_ir(ir_t *ir){
        if(ir->is_terminator() && !instructions.empty() && instructions.back()->is_terminator()){
            throw std::runtime_error("Cannot add a terminator instruction to a basic block that already has a terminator.");
        }else if(!instructions.empty() && instructions.back()->is_rule_ending()){
            throw std::runtime_error("Cannot add an instruction to a basic block that already has a rule-ending instruction.");
        }
        instructions.push_back(std::unique_ptr<ir_t>(ir));
    }
};
class ir_graph_t{
public:
    std::vector<std::unique_ptr<basic_block_t>> blocks;
    basic_block_id_t entry=0;
    basic_block_id_t current_block=0;
    int next_block_id=1;
    basic_block_id_t create_block(){
        blocks.push_back(std::make_unique<basic_block_t>(next_block_id++));
        return blocks.back().get()->id;
    }
    basic_block_t *get_block(basic_block_id_t id){
        for (const auto& block : blocks) {
            if (block->id == id) {
                return block.get();
            }
        }
        throw std::runtime_error("Block ID not found.");
    }
    void connect(basic_block_id_t from, basic_block_id_t to){
        basic_block_t *from_block = nullptr;
        basic_block_t *to_block = nullptr;
        for (const auto& block : blocks) {
            if (block->id == from) {
                from_block = block.get();
            } else if (block->id == to) {
                to_block = block.get();
            }
        }
        if (!from_block || !to_block) {
            throw std::runtime_error("Invalid block ID for connection.");
        }
        from_block->successors.push_back(to_block->id);
        to_block->predecessors.push_back(from_block->id);
    }
    void add_ir(ir_t *ir){
        if(current_block==0){
            throw std::runtime_error("Cannot add an instruction to a null current block.");
        }
        get_block(current_block)->push_ir(ir);
    }
    void set_current_block(basic_block_id_t block){
        current_block=block;
    }
    basic_block_id_t get_current_block(){
        return current_block;
    }
    void set_current_label(label_t label){
        if(current_block==0){
            throw std::runtime_error("Cannot set label of a null current block.");
        }
        get_block(current_block)->label=label;
    }
};
class ir_typedef_t{
public:
    symbol_t* symbol;
    type_t* type;
    ir_typedef_t(symbol_t* symbol, type_t* type):symbol(symbol),type(type){}
};
class ir_global_t{
public:
    symbol_t* symbol;
    ast_node_t* initializer;
    ir_global_t(symbol_t* symbol, ast_node_t* initializer):symbol(symbol),initializer(initializer){}
};
class ir_module_t{
public:
    std::vector<std::unique_ptr<ir_graph_t>> functions;
    // typedefs such as structs, enums, and type aliases
    std::vector<std::unique_ptr<ir_typedef_t>> typedefs;
    // global variables
    std::vector<std::unique_ptr<ir_global_t>> globals;
};
class ir_context_t{
public:
    sematic_context_t sematic_context;
    ir_module_t module;
    int next_tempvar_id=0;
    symbol_t *get_symbol(ast_node_t* node){
        return sematic_context.get_symbol(node);
    }
    conversion_t* get_conversion(ast_node_t* node){
        return sematic_context.get_conversion(node);
    }
    tempvar_t create_tempvar(){
        tempvar_t tempvar(next_tempvar_id++);
        tempvars.push_back(tempvar);
        return tempvar;
    }
    void push_visit(){
        visit_stack.push_back(false);
    }
    void push_visit_ref(){
        visit_stack.push_back(true);
    }
    void pop_visit(){
        if(visit_stack.empty()){
            throw std::runtime_error("Visit stack underflow.");
        }
        visit_stack.pop_back();
    }
    void pop_visit_ref(){
        if(visit_stack.empty()){
            throw std::runtime_error("Visit stack underflow.");
        }
        visit_stack.pop_back();
    }
    bool is_visit_ref(){
        if(visit_stack.empty()){
            throw std::runtime_error("Visit stack is empty.");
        }
        return visit_stack.back();
    }
private:
    std::vector<bool> visit_stack;
    int next_label_id=0;
    std::vector<tempvar_t> tempvars;
};