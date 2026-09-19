#pragma once
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
    std::string name;
    tempvar_t(std::string name):name(name){}
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
    std::string conversion;
    tempvar_t src;
    tempvar_t dst;
    ir_cast_t(std::string conversion, tempvar_t src, tempvar_t dst):conversion(conversion),src(src),dst(dst){
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
    std::string symbol;
    tempvar_t address;
    ir_alloc_t(std::string symbol, tempvar_t address):symbol(symbol),address(address){
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

class basic_block_t{
public:
    label_t label;
    std::vector<basic_block_t*> successors;
    std::vector<basic_block_t*> predecessors;
    std::vector<ir_t> instructions;
    void push_ir(ir_t ir){
        if(ir.is_terminator() && !instructions.empty() && instructions.back().is_terminator()){
            throw std::runtime_error("Cannot add a terminator instruction to a basic block that already has a terminator.");
        }
        instructions.push_back(ir);
    }
};
class ir_graph_t{
public:
    std::vector<basic_block_t> blocks;
    basic_block_t* entry=nullptr;
    basic_block_t* current_block=nullptr;
    basic_block_t* create_block(label_t label){
        blocks.push_back(basic_block_t{label});
        return &blocks.back();
    }
    void connect(basic_block_t* from, basic_block_t* to){
        from->successors.push_back(to);
        to->predecessors.push_back(from);
    }
    void add_ir(ir_t ir){
        if(current_block==nullptr){
            throw std::runtime_error("Cannot add an instruction to a null current block.");
        }
        current_block->push_ir(ir);
    }
    void set_current_block(basic_block_t* block){
        current_block=block;
    }
    basic_block_t* get_current_block(){
        return current_block;
    }
    void set_current_label(label_t label){
        if(current_block==nullptr){
            throw std::runtime_error("Cannot set label of a null current block.");
        }
        current_block->label=label;
    }
};
class ir_context_t{
public:
    ir_graph_t graph;
    label_t create_label(std::string name){
        label_t label;
        label.id=next_label_id++;
        label.name=name;
        return label;
    }
    label_t create_or_get_label(std::string name){
        for(auto& block:graph.blocks){
            if(block.label.name==name){
                return block.label;
            }
        }
        return create_label(name);
    }
    tempvar_t create_tempvar(std::string name){
        tempvar_t tempvar(name);
        tempvars.push_back(tempvar);
        return tempvar;
    }
private:
    int next_label_id=0;
    std::vector<tempvar_t> tempvars;
};