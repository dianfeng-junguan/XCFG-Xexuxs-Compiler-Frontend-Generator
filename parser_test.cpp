#include <vector>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
token_t* parse_token(tokenstream_t *tokenstream, token_type_t token_type){
    token_t *token=tokenstream->peek();
    if(token==NULL){
        return NULL;
    }
    if(token->token_type==token_type){
        tokenstream->next();
        return token;
    }
    return NULL;
}
factor_t *parse_factor_t(tokenstream_t *tokenstream);

glued_factor_t *parse_glued_factor_t(tokenstream_t *tokenstream);

single_op_factor_t *parse_single_op_factor_t(tokenstream_t *tokenstream);

power_factor_t *parse_power_factor_t(tokenstream_t *tokenstream);

term_t *parse_term_t(tokenstream_t *tokenstream);

shift_expr_t *parse_shift_expr_t(tokenstream_t *tokenstream);

bitand_expr_t *parse_bitand_expr_t(tokenstream_t *tokenstream);

bitor_expr_t *parse_bitor_expr_t(tokenstream_t *tokenstream);

expr_t *parse_expr_t(tokenstream_t *tokenstream);

logic_expr_and_t *parse_logic_expr_and_t(tokenstream_t *tokenstream);

logic_expr_or_t *parse_logic_expr_or_t(tokenstream_t *tokenstream);

logic_expr_eq_t *parse_logic_expr_eq_t(tokenstream_t *tokenstream);

assign_expr_t *parse_assign_expr_t(tokenstream_t *tokenstream);

ultimate_expr_t *parse_ultimate_expr_t(tokenstream_t *tokenstream);

lvalue_noproperty_t *parse_lvalue_noproperty_t(tokenstream_t *tokenstream);

lvalue_t *parse_lvalue_t(tokenstream_t *tokenstream);

composed_type_t *parse_composed_type_t(tokenstream_t *tokenstream);

definition_t *parse_definition_t(tokenstream_t *tokenstream);

else_t *parse_else_t(tokenstream_t *tokenstream);

elseif_t *parse_elseif_t(tokenstream_t *tokenstream);

elseif_else_t *parse_elseif_else_t(tokenstream_t *tokenstream);

if_t *parse_if_t(tokenstream_t *tokenstream);

while_t *parse_while_t(tokenstream_t *tokenstream);

structmembers_t *parse_structmembers_t(tokenstream_t *tokenstream);

struct_t *parse_struct_t(tokenstream_t *tokenstream);

declaration_t *parse_declaration_t(tokenstream_t *tokenstream);

statement_t *parse_statement_t(tokenstream_t *tokenstream);

statements_nonempty_t *parse_statements_nonempty_t(tokenstream_t *tokenstream);

statements_t *parse_statements_t(tokenstream_t *tokenstream);

func_returntype_t *parse_func_returntype_t(tokenstream_t *tokenstream);

parameter_list_nonempty_t *parse_parameter_list_nonempty_t(tokenstream_t *tokenstream);

parameter_list_t *parse_parameter_list_t(tokenstream_t *tokenstream);

argument_list_nonempty_t *parse_argument_list_nonempty_t(tokenstream_t *tokenstream);

argument_list_t *parse_argument_list_t(tokenstream_t *tokenstream);

function_t *parse_function_t(tokenstream_t *tokenstream);

top_statement_t *parse_top_statement_t(tokenstream_t *tokenstream);

factor_num_t* parse_factor_num_t(tokenstream_t *tokenstream){
    factor_num_t* node=new factor_num_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_NUMBER(tokenstream->peek()->token_type)){node->value=new token_t(*tokenstream->consume());}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_ch_t* parse_factor_ch_t(tokenstream_t *tokenstream){
    factor_ch_t* node=new factor_ch_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_CHAR(tokenstream->peek()->token_type)){node->value=new token_t(*tokenstream->consume());}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_str_t* parse_factor_str_t(tokenstream_t *tokenstream){
    factor_str_t* node=new factor_str_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_STRING(tokenstream->peek()->token_type)){node->value=new token_t(*tokenstream->consume());}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_t* parse_factor_t(tokenstream_t *tokenstream){{
    factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_factor_num_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_factor_ch_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_factor_str_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

glued_factor_paren_t* parse_glued_factor_paren_t(tokenstream_t *tokenstream){
    glued_factor_paren_t* node=new glued_factor_paren_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_call_t* parse_glued_factor_call_t(tokenstream_t *tokenstream){
    glued_factor_call_t* node=new glued_factor_call_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_argument_list_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_lvalue_t* parse_glued_factor_lvalue_t(tokenstream_t *tokenstream){
    glued_factor_lvalue_t* node=new glued_factor_lvalue_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_value_t* parse_glued_factor_value_t(tokenstream_t *tokenstream){
    glued_factor_value_t* node=new glued_factor_value_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_t* parse_glued_factor_t(tokenstream_t *tokenstream){{
    glued_factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_glued_factor_paren_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_call_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_lvalue_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_value_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

single_op_factor_bitnot_t* parse_single_op_factor_bitnot_t(tokenstream_t *tokenstream){
    single_op_factor_bitnot_t* node=new single_op_factor_bitnot_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITNOT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_neg_t* parse_single_op_factor_neg_t(tokenstream_t *tokenstream){
    single_op_factor_neg_t* node=new single_op_factor_neg_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_ref_t* parse_single_op_factor_ref_t(tokenstream_t *tokenstream){
    single_op_factor_ref_t* node=new single_op_factor_ref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITAND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_deref_t* parse_single_op_factor_deref_t(tokenstream_t *tokenstream){
    single_op_factor_deref_t* node=new single_op_factor_deref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_not_t* parse_single_op_factor_not_t(tokenstream_t *tokenstream){
    single_op_factor_not_t* node=new single_op_factor_not_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_NOT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_none_t* parse_single_op_factor_none_t(tokenstream_t *tokenstream){
    single_op_factor_none_t* node=new single_op_factor_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_glued_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_t* parse_single_op_factor_t(tokenstream_t *tokenstream){{
    single_op_factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_single_op_factor_bitnot_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_neg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_ref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_deref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_not_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

power_factor_pow_t* parse_power_factor_pow_t_nostart(power_factor_t* start_node,tokenstream_t *tokenstream){
    power_factor_pow_t* node=new power_factor_pow_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITXOR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

power_factor_none_t* parse_power_factor_none_t(tokenstream_t *tokenstream){
    power_factor_none_t* node=new power_factor_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static power_factor_t* parse_power_factor_t_start(tokenstream_t *tokenstream){
        power_factor_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_power_factor_none_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
power_factor_t* parse_power_factor_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    power_factor_t* node = parse_power_factor_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        power_factor_t* next=nullptr;
        if((next=parse_power_factor_pow_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
term_mul_t* parse_term_mul_t_nostart(term_t* start_node,tokenstream_t *tokenstream){
    term_mul_t* node=new term_mul_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

term_div_t* parse_term_div_t_nostart(term_t* start_node,tokenstream_t *tokenstream){
    term_div_t* node=new term_div_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_SLASH))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

term_mod_t* parse_term_mod_t_nostart(term_t* start_node,tokenstream_t *tokenstream){
    term_mod_t* node=new term_mod_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_PERCENT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

term_factor_t* parse_term_factor_t(tokenstream_t *tokenstream){
    term_factor_t* node=new term_factor_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static term_t* parse_term_t_start(tokenstream_t *tokenstream){
        term_t* node;
        tokenstream->begin_parsing();
        
	
	
	if((node=parse_term_factor_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
term_t* parse_term_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    term_t* node = parse_term_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        term_t* next=nullptr;
        if((next=parse_term_mul_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_term_div_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_term_mod_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
shift_expr_shiftleft_t* parse_shift_expr_shiftleft_t_nostart(shift_expr_t* start_node,tokenstream_t *tokenstream){
    shift_expr_shiftleft_t* node=new shift_expr_shiftleft_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_SHIFTLEFT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

shift_expr_shiftright_t* parse_shift_expr_shiftright_t_nostart(shift_expr_t* start_node,tokenstream_t *tokenstream){
    shift_expr_shiftright_t* node=new shift_expr_shiftright_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_SHIFTRIGHT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

shift_expr_expr_t* parse_shift_expr_expr_t(tokenstream_t *tokenstream){
    shift_expr_expr_t* node=new shift_expr_expr_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static shift_expr_t* parse_shift_expr_t_start(tokenstream_t *tokenstream){
        shift_expr_t* node;
        tokenstream->begin_parsing();
        
	
	if((node=parse_shift_expr_expr_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
shift_expr_t* parse_shift_expr_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    shift_expr_t* node = parse_shift_expr_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        shift_expr_t* next=nullptr;
        if((next=parse_shift_expr_shiftleft_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_shift_expr_shiftright_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
bitand_expr_bitand_t* parse_bitand_expr_bitand_t_nostart(bitand_expr_t* start_node,tokenstream_t *tokenstream){
    bitand_expr_bitand_t* node=new bitand_expr_bitand_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITAND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_shift_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

bitand_expr_shift_t* parse_bitand_expr_shift_t(tokenstream_t *tokenstream){
    bitand_expr_shift_t* node=new bitand_expr_shift_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_shift_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static bitand_expr_t* parse_bitand_expr_t_start(tokenstream_t *tokenstream){
        bitand_expr_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_bitand_expr_shift_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
bitand_expr_t* parse_bitand_expr_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    bitand_expr_t* node = parse_bitand_expr_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        bitand_expr_t* next=nullptr;
        if((next=parse_bitand_expr_bitand_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
bitor_expr_bitor_t* parse_bitor_expr_bitor_t_nostart(bitor_expr_t* start_node,tokenstream_t *tokenstream){
    bitor_expr_bitor_t* node=new bitor_expr_bitor_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITOR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitand_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

bitor_expr_bitand_t* parse_bitor_expr_bitand_t(tokenstream_t *tokenstream){
    bitor_expr_bitand_t* node=new bitor_expr_bitand_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_bitand_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static bitor_expr_t* parse_bitor_expr_t_start(tokenstream_t *tokenstream){
        bitor_expr_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_bitor_expr_bitand_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
bitor_expr_t* parse_bitor_expr_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    bitor_expr_t* node = parse_bitor_expr_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        bitor_expr_t* next=nullptr;
        if((next=parse_bitor_expr_bitor_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
expr_add_t* parse_expr_add_t_nostart(expr_t* start_node,tokenstream_t *tokenstream){
    expr_add_t* node=new expr_add_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_ADD))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

expr_sub_t* parse_expr_sub_t_nostart(expr_t* start_node,tokenstream_t *tokenstream){
    expr_sub_t* node=new expr_sub_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

expr_term_t* parse_expr_term_t(tokenstream_t *tokenstream){
    expr_term_t* node=new expr_term_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static expr_t* parse_expr_t_start(tokenstream_t *tokenstream){
        expr_t* node;
        tokenstream->begin_parsing();
        
	
	if((node=parse_expr_term_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
expr_t* parse_expr_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    expr_t* node = parse_expr_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        expr_t* next=nullptr;
        if((next=parse_expr_add_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_expr_sub_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
logic_expr_and_and_t* parse_logic_expr_and_and_t_nostart(logic_expr_and_t* start_node,tokenstream_t *tokenstream){
    logic_expr_and_and_t* node=new logic_expr_and_and_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_AND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_and_none_t* parse_logic_expr_and_none_t(tokenstream_t *tokenstream){
    logic_expr_and_none_t* node=new logic_expr_and_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static logic_expr_and_t* parse_logic_expr_and_t_start(tokenstream_t *tokenstream){
        logic_expr_and_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_logic_expr_and_none_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
logic_expr_and_t* parse_logic_expr_and_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    logic_expr_and_t* node = parse_logic_expr_and_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        logic_expr_and_t* next=nullptr;
        if((next=parse_logic_expr_and_and_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
logic_expr_or_or_t* parse_logic_expr_or_or_t_nostart(logic_expr_or_t* start_node,tokenstream_t *tokenstream){
    logic_expr_or_or_t* node=new logic_expr_or_or_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_and_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_or_none_t* parse_logic_expr_or_none_t(tokenstream_t *tokenstream){
    logic_expr_or_none_t* node=new logic_expr_or_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_and_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static logic_expr_or_t* parse_logic_expr_or_t_start(tokenstream_t *tokenstream){
        logic_expr_or_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_logic_expr_or_none_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
logic_expr_or_t* parse_logic_expr_or_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    logic_expr_or_t* node = parse_logic_expr_or_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        logic_expr_or_t* next=nullptr;
        if((next=parse_logic_expr_or_or_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
logic_expr_eq_eq_t* parse_logic_expr_eq_eq_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_eq_t* node=new logic_expr_eq_eq_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_EQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_neq_t* parse_logic_expr_eq_neq_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_neq_t* node=new logic_expr_eq_neq_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_UNEQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_gt_t* parse_logic_expr_eq_gt_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_gt_t* node=new logic_expr_eq_gt_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_GREATERTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_lt_t* parse_logic_expr_eq_lt_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_lt_t* node=new logic_expr_eq_lt_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LESSTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_ge_t* parse_logic_expr_eq_ge_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_ge_t* node=new logic_expr_eq_ge_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_GREATEREQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_le_t* parse_logic_expr_eq_le_t_nostart(logic_expr_eq_t* start_node,tokenstream_t *tokenstream){
    logic_expr_eq_le_t* node=new logic_expr_eq_le_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LESSEQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_none_t* parse_logic_expr_eq_none_t(tokenstream_t *tokenstream){
    logic_expr_eq_none_t* node=new logic_expr_eq_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_bitor_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static logic_expr_eq_t* parse_logic_expr_eq_t_start(tokenstream_t *tokenstream){
        logic_expr_eq_t* node;
        tokenstream->begin_parsing();
        
	
	
	
	
	
	if((node=parse_logic_expr_eq_none_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
logic_expr_eq_t* parse_logic_expr_eq_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    logic_expr_eq_t* node = parse_logic_expr_eq_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        logic_expr_eq_t* next=nullptr;
        if((next=parse_logic_expr_eq_eq_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_logic_expr_eq_neq_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_logic_expr_eq_gt_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_logic_expr_eq_lt_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_logic_expr_eq_ge_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_logic_expr_eq_le_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
assign_expr_assign_t* parse_assign_expr_assign_t(tokenstream_t *tokenstream){
    assign_expr_assign_t* node=new assign_expr_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_plus_assign_t* parse_assign_expr_plus_assign_t(tokenstream_t *tokenstream){
    assign_expr_plus_assign_t* node=new assign_expr_plus_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ADDASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_minus_assign_t* parse_assign_expr_minus_assign_t(tokenstream_t *tokenstream){
    assign_expr_minus_assign_t* node=new assign_expr_minus_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MINUSASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_mul_assign_t* parse_assign_expr_mul_assign_t(tokenstream_t *tokenstream){
    assign_expr_mul_assign_t* node=new assign_expr_mul_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MULASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_div_assign_t* parse_assign_expr_div_assign_t(tokenstream_t *tokenstream){
    assign_expr_div_assign_t* node=new assign_expr_div_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_DIVASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_mod_assign_t* parse_assign_expr_mod_assign_t(tokenstream_t *tokenstream){
    assign_expr_mod_assign_t* node=new assign_expr_mod_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MODASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_bitand_assign_t* parse_assign_expr_bitand_assign_t(tokenstream_t *tokenstream){
    assign_expr_bitand_assign_t* node=new assign_expr_bitand_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITANDASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_bitor_assign_t* parse_assign_expr_bitor_assign_t(tokenstream_t *tokenstream){
    assign_expr_bitor_assign_t* node=new assign_expr_bitor_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITORASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_shiftleft_assign_t* parse_assign_expr_shiftleft_assign_t(tokenstream_t *tokenstream){
    assign_expr_shiftleft_assign_t* node=new assign_expr_shiftleft_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTLEFTASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_shiftright_assign_t* parse_assign_expr_shiftright_assign_t(tokenstream_t *tokenstream){
    assign_expr_shiftright_assign_t* node=new assign_expr_shiftright_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTRIGHTASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_logic_expr_t* parse_assign_expr_logic_expr_t(tokenstream_t *tokenstream){
    assign_expr_logic_expr_t* node=new assign_expr_logic_expr_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_t* parse_assign_expr_t(tokenstream_t *tokenstream){{
    assign_expr_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_assign_expr_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_plus_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_minus_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_mul_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_div_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_mod_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_bitand_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_bitor_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_shiftleft_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_shiftright_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_logic_expr_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

ultimate_expr_def_t* parse_ultimate_expr_def_t(tokenstream_t *tokenstream){
    ultimate_expr_def_t* node=new ultimate_expr_def_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

ultimate_expr_t* parse_ultimate_expr_t(tokenstream_t *tokenstream){{
    ultimate_expr_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_ultimate_expr_def_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

lvalue_noproperty_parened_t* parse_lvalue_noproperty_parened_t(tokenstream_t *tokenstream){
    lvalue_noproperty_parened_t* node=new lvalue_noproperty_parened_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_deref_t* parse_lvalue_noproperty_deref_t(tokenstream_t *tokenstream){
    lvalue_noproperty_deref_t* node=new lvalue_noproperty_deref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->derefee=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_id_t* parse_lvalue_noproperty_id_t(tokenstream_t *tokenstream){
    lvalue_noproperty_id_t* node=new lvalue_noproperty_id_t();
    tokenstream->begin_parsing();
    if(!(node->id=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->id=new token_t(*node->id);}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_t* parse_lvalue_noproperty_t(tokenstream_t *tokenstream){{
    lvalue_noproperty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_lvalue_noproperty_parened_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_lvalue_noproperty_deref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_lvalue_noproperty_id_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

lvalue_prop_t* parse_lvalue_prop_t_nostart(lvalue_t* start_node,tokenstream_t *tokenstream){
    lvalue_prop_t* node=new lvalue_prop_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_PROPERTY))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->right=new token_t(*node->right);}
    node->left=start_node;
    tokenstream->end_parsing();
    return node;
}

lvalue_noprop_t* parse_lvalue_noprop_t(tokenstream_t *tokenstream){
    lvalue_noprop_t* node=new lvalue_noprop_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_lvalue_noproperty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static lvalue_t* parse_lvalue_t_start(tokenstream_t *tokenstream){
        lvalue_t* node;
        tokenstream->begin_parsing();
        
	if((node=parse_lvalue_noprop_t(tokenstream))){tokenstream->end_parsing();return node;}
        tokenstream->reset();
        return nullptr;
}
lvalue_t* parse_lvalue_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    lvalue_t* node = parse_lvalue_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        lvalue_t* next=nullptr;
        if((next=parse_lvalue_prop_t_nostart(node,tokenstream))){node=next;continue;}
	else break;
    }
    tokenstream->end_parsing();
    return node;
}
composed_type_raw_type_t* parse_composed_type_raw_type_t(tokenstream_t *tokenstream){
    composed_type_raw_type_t* node=new composed_type_raw_type_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_TYPEKW(tokenstream->peek()->token_type)){node->inner_type=new token_t(*tokenstream->consume());}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_paren_t* parse_composed_type_paren_t(tokenstream_t *tokenstream){
    composed_type_paren_t* node=new composed_type_paren_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->inner_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_ptr_t* parse_composed_type_ptr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_ptr_t* node=new composed_type_ptr_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
    node->pointer_type=start_node;
    tokenstream->end_parsing();
    return node;
}

composed_type_sizedarr_t* parse_composed_type_sizedarr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_sizedarr_t* node=new composed_type_sizedarr_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->array_size=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    node->element_type=start_node;
    tokenstream->end_parsing();
    return node;
}

composed_type_nsizedarr_t* parse_composed_type_nsizedarr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_nsizedarr_t* node=new composed_type_nsizedarr_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    node->element_type=start_node;
    tokenstream->end_parsing();
    return node;
}
static composed_type_t* parse_composed_type_t_start(tokenstream_t *tokenstream){
        composed_type_t* node;
        tokenstream->begin_parsing();
        if((node=parse_composed_type_raw_type_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_composed_type_paren_t(tokenstream))){tokenstream->end_parsing();return node;}
	
	
	
        tokenstream->reset();
        return nullptr;
}
composed_type_t* parse_composed_type_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    composed_type_t* node = parse_composed_type_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        composed_type_t* next=nullptr;
        
	
	if((next=parse_composed_type_ptr_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_composed_type_sizedarr_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_composed_type_nsizedarr_t_nostart(node,tokenstream))){node=next;continue;}else break;
    }
    tokenstream->end_parsing();
    return node;
}
definition_deftype_t* parse_definition_deftype_t(tokenstream_t *tokenstream){
    definition_deftype_t* node=new definition_deftype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

definition_defntype_t* parse_definition_defntype_t(tokenstream_t *tokenstream){
    definition_defntype_t* node=new definition_defntype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

definition_t* parse_definition_t(tokenstream_t *tokenstream){{
    definition_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_definition_deftype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_definition_defntype_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

else_default_t* parse_else_default_t(tokenstream_t *tokenstream){
    else_default_t* node=new else_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_ELSE))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

else_t* parse_else_t(tokenstream_t *tokenstream){{
    else_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_else_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

elseif_default_t* parse_elseif_default_t(tokenstream_t *tokenstream){
    elseif_default_t* node=new elseif_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_ELSE))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_IF))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_t* parse_elseif_t(tokenstream_t *tokenstream){{
    elseif_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_elseif_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

elseif_else_onlyelse_t* parse_elseif_else_onlyelse_t(tokenstream_t *tokenstream){
    elseif_else_onlyelse_t* node=new elseif_else_onlyelse_t();
    tokenstream->begin_parsing();
    if(!(node->else_block=parse_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_else_chain_t* parse_elseif_else_chain_t(tokenstream_t *tokenstream){
    elseif_else_chain_t* node=new elseif_else_chain_t();
    tokenstream->begin_parsing();
    if(!(node->elseif_block=parse_elseif_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(node->rest_block=parse_elseif_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_else_empty_t* parse_elseif_else_empty_t(tokenstream_t *tokenstream){
    elseif_else_empty_t* node=new elseif_else_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

elseif_else_t* parse_elseif_else_t(tokenstream_t *tokenstream){{
    elseif_else_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_elseif_else_onlyelse_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_elseif_else_chain_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_elseif_else_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

if_default_t* parse_if_default_t(tokenstream_t *tokenstream){
    if_default_t* node=new if_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_IF))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->rest_block=parse_elseif_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

if_t* parse_if_t(tokenstream_t *tokenstream){{
    if_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_if_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

while_default_t* parse_while_default_t(tokenstream_t *tokenstream){
    while_default_t* node=new while_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_WHILE))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

while_t* parse_while_t(tokenstream_t *tokenstream){{
    while_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_while_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

structmembers_multimem_t* parse_structmembers_multimem_t(tokenstream_t *tokenstream){
    structmembers_multimem_t* node=new structmembers_multimem_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COMMA))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

structmembers_singmem_t* parse_structmembers_singmem_t(tokenstream_t *tokenstream){
    structmembers_singmem_t* node=new structmembers_singmem_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

structmembers_empty_t* parse_structmembers_empty_t(tokenstream_t *tokenstream){
    structmembers_empty_t* node=new structmembers_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

structmembers_t* parse_structmembers_t(tokenstream_t *tokenstream){{
    structmembers_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_structmembers_multimem_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_structmembers_singmem_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_structmembers_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

struct_default_t* parse_struct_default_t(tokenstream_t *tokenstream){
    struct_default_t* node=new struct_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STRUCT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

struct_t* parse_struct_t(tokenstream_t *tokenstream){{
    struct_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_struct_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

declaration_varntype_t* parse_declaration_varntype_t(tokenstream_t *tokenstream){
    declaration_varntype_t* node=new declaration_varntype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_var_t* parse_declaration_var_t(tokenstream_t *tokenstream){
    declaration_var_t* node=new declaration_var_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_COLON))){tokenstream->reset();delete node;return nullptr;}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_fn_t* parse_declaration_fn_t(tokenstream_t *tokenstream){
    declaration_fn_t* node=new declaration_fn_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_FN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_parameter_list_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_func_returntype_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_struct_t* parse_declaration_struct_t(tokenstream_t *tokenstream){
    declaration_struct_t* node=new declaration_struct_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STRUCT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_t* parse_declaration_t(tokenstream_t *tokenstream){{
    declaration_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_declaration_varntype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_var_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_fn_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_struct_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

statement_expr_t* parse_statement_expr_t(tokenstream_t *tokenstream){
    statement_expr_t* node=new statement_expr_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_definition_t* parse_statement_definition_t(tokenstream_t *tokenstream){
    statement_definition_t* node=new statement_definition_t();
    tokenstream->begin_parsing();
    if(!(node->def=parse_definition_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_if_t* parse_statement_if_t(tokenstream_t *tokenstream){
    statement_if_t* node=new statement_if_t();
    tokenstream->begin_parsing();
    if(!(node->if_stmt=parse_if_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_while_t* parse_statement_while_t(tokenstream_t *tokenstream){
    statement_while_t* node=new statement_while_t();
    tokenstream->begin_parsing();
    if(!(node->while_stmt=parse_while_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_declaration_t* parse_statement_declaration_t(tokenstream_t *tokenstream){
    statement_declaration_t* node=new statement_declaration_t();
    tokenstream->begin_parsing();
    if(!(node->decl_stmt=parse_declaration_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_break_t* parse_statement_break_t(tokenstream_t *tokenstream){
    statement_break_t* node=new statement_break_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BREAK))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_continue_t* parse_statement_continue_t(tokenstream_t *tokenstream){
    statement_continue_t* node=new statement_continue_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_CONTINUE))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_return_sth_t* parse_statement_return_sth_t(tokenstream_t *tokenstream){
    statement_return_sth_t* node=new statement_return_sth_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_RETURN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_return_empty_t* parse_statement_return_empty_t(tokenstream_t *tokenstream){
    statement_return_empty_t* node=new statement_return_empty_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_RETURN))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_t* parse_statement_t(tokenstream_t *tokenstream){{
    statement_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_statement_expr_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_definition_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_if_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_while_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_declaration_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_break_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_continue_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_return_sth_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_return_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

statements_nonempty_multistmt_t* parse_statements_nonempty_multistmt_t(tokenstream_t *tokenstream){
    statements_nonempty_multistmt_t* node=new statements_nonempty_multistmt_t();
    tokenstream->begin_parsing();
    if(!(node->stmt=parse_statement_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_stmts=parse_statements_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statements_nonempty_stmt_t* parse_statements_nonempty_stmt_t(tokenstream_t *tokenstream){
    statements_nonempty_stmt_t* node=new statements_nonempty_stmt_t();
    tokenstream->begin_parsing();
    if(!(node->stmt=parse_statement_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statements_nonempty_t* parse_statements_nonempty_t(tokenstream_t *tokenstream){{
    statements_nonempty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_statements_nonempty_multistmt_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statements_nonempty_stmt_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

statements_hasstatements_t* parse_statements_hasstatements_t(tokenstream_t *tokenstream){
    statements_hasstatements_t* node=new statements_hasstatements_t();
    tokenstream->begin_parsing();
    if(!(node->statements=parse_statements_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statements_empty_t* parse_statements_empty_t(tokenstream_t *tokenstream){
    statements_empty_t* node=new statements_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

statements_t* parse_statements_t(tokenstream_t *tokenstream){{
    statements_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_statements_hasstatements_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statements_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

func_returntype_hastype_t* parse_func_returntype_hastype_t(tokenstream_t *tokenstream){
    func_returntype_hastype_t* node=new func_returntype_hastype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_GREATERTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

func_returntype_void_t* parse_func_returntype_void_t(tokenstream_t *tokenstream){
    func_returntype_void_t* node=new func_returntype_void_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

func_returntype_t* parse_func_returntype_t(tokenstream_t *tokenstream){{
    func_returntype_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_func_returntype_hastype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_func_returntype_void_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

parameter_list_nonempty_multiarg_t* parse_parameter_list_nonempty_multiarg_t(tokenstream_t *tokenstream){
    parameter_list_nonempty_multiarg_t* node=new parameter_list_nonempty_multiarg_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(node->arg_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COMMA))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_args=parse_parameter_list_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

parameter_list_nonempty_singarg_t* parse_parameter_list_nonempty_singarg_t(tokenstream_t *tokenstream){
    parameter_list_nonempty_singarg_t* node=new parameter_list_nonempty_singarg_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(node->arg_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

parameter_list_nonempty_t* parse_parameter_list_nonempty_t(tokenstream_t *tokenstream){{
    parameter_list_nonempty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_parameter_list_nonempty_multiarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_parameter_list_nonempty_singarg_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

parameter_list_hasarg_t* parse_parameter_list_hasarg_t(tokenstream_t *tokenstream){
    parameter_list_hasarg_t* node=new parameter_list_hasarg_t();
    tokenstream->begin_parsing();
    if(!(node->args=parse_parameter_list_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

parameter_list_empty_t* parse_parameter_list_empty_t(tokenstream_t *tokenstream){
    parameter_list_empty_t* node=new parameter_list_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

parameter_list_t* parse_parameter_list_t(tokenstream_t *tokenstream){{
    parameter_list_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_parameter_list_hasarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_parameter_list_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

argument_list_nonempty_multiarg_t* parse_argument_list_nonempty_multiarg_t(tokenstream_t *tokenstream){
    argument_list_nonempty_multiarg_t* node=new argument_list_nonempty_multiarg_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COMMA))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_args=parse_argument_list_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

argument_list_nonempty_singarg_t* parse_argument_list_nonempty_singarg_t(tokenstream_t *tokenstream){
    argument_list_nonempty_singarg_t* node=new argument_list_nonempty_singarg_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

argument_list_nonempty_t* parse_argument_list_nonempty_t(tokenstream_t *tokenstream){{
    argument_list_nonempty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_argument_list_nonempty_multiarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_argument_list_nonempty_singarg_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

argument_list_hasarg_t* parse_argument_list_hasarg_t(tokenstream_t *tokenstream){
    argument_list_hasarg_t* node=new argument_list_hasarg_t();
    tokenstream->begin_parsing();
    if(!(node->args=parse_argument_list_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

argument_list_empty_t* parse_argument_list_empty_t(tokenstream_t *tokenstream){
    argument_list_empty_t* node=new argument_list_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

argument_list_t* parse_argument_list_t(tokenstream_t *tokenstream){{
    argument_list_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_argument_list_hasarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_argument_list_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

function_default_t* parse_function_default_t(tokenstream_t *tokenstream){
    function_default_t* node=new function_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_FN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}else{node->name=new token_t(*node->name);}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_parameter_list_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_func_returntype_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->stmts=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

function_t* parse_function_t(tokenstream_t *tokenstream){{
    function_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_function_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

top_statement_func_def_t* parse_top_statement_func_def_t(tokenstream_t *tokenstream){
    top_statement_func_def_t* node=new top_statement_func_def_t();
    tokenstream->begin_parsing();
    if(!(node->func=parse_function_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_decl_t* parse_top_statement_decl_t(tokenstream_t *tokenstream){
    top_statement_decl_t* node=new top_statement_decl_t();
    tokenstream->begin_parsing();
    if(!(node->decl=parse_declaration_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_var_def_t* parse_top_statement_var_def_t(tokenstream_t *tokenstream){
    top_statement_var_def_t* node=new top_statement_var_def_t();
    tokenstream->begin_parsing();
    if(!(node->def=parse_definition_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_structdef_t* parse_top_statement_structdef_t(tokenstream_t *tokenstream){
    top_statement_structdef_t* node=new top_statement_structdef_t();
    tokenstream->begin_parsing();
    if(!(node->structdef=parse_struct_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_t* parse_top_statement_t(tokenstream_t *tokenstream){{
    top_statement_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_top_statement_func_def_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_decl_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_var_def_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_structdef_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}


typedef struct{
    const char* name;
    ast_node_t* (*parser)(tokenstream_t *ts);
}parser_rule_t;

parser_rule_t parser_rules[]={
{"top_statement", (ast_node_t* (*)(tokenstream_t*))parse_top_statement_t},

};
    
parser_result_t do_parse(tokenstream_t *tokenstream){
    std::vector<ast_node_t*> nodes;
    bool success=true;
    while(!tokenstream->eof()){
        bool flag=false;
        for(int i=0;i<sizeof(parser_rules)/sizeof(parser_rule_t);i++){
            ast_node_t *node;
            if(node=parser_rules[i].parser(tokenstream)){
                nodes.push_back(node);
                flag=true;
                break;
            }
        }
        if(!flag){
            success=false;
            printf("parser error: failed to parse token at line %d, column %d\n",tokenstream->peek()->line+1,tokenstream->peek()->column+1);
            tokenstream->begin_parsing();
            tokenstream->next();
            tokenstream->end_parsing();
        }
    }
    return parser_result_t{success, nodes};
}