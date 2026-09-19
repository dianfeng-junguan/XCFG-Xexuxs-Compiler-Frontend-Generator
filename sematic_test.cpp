#include "lexer.h"
#include "parser.h"
#include "sematic.h"
#include <vector>
bool visit(ast_node_t* node,sematic_context_t* context);
bool predeclare_function(ast_node_t*,token_t*,arglist_t*,func_returntype_t*,sematic_context_t*);
bool predeclare_struct(ast_node_t*,token_t*,sematic_context_t*);
bool enter_function_scope(ast_node_t*,sematic_context_t*);
bool predeclare_parameters(ast_node_t*,arglist_t*,sematic_context_t*);
bool leave_scope(ast_node_t*,sematic_context_t*);
bool enter_struct_scope(ast_node_t*,sematic_context_t*);
bool predeclare_members(ast_node_t*,structmembers_t*,sematic_context_t*);
bool enter_block_scope(ast_node_t*,sematic_context_t*);
bool enter_loop_scope(ast_node_t*,sematic_context_t*);
bool declare_parameters(ast_node_t*,arglist_t*,sematic_context_t*);
bool declare_members(ast_node_t*,structmembers_t*,sematic_context_t*);
bool declare_variable(ast_node_t*,token_t*,composed_type_t*,sematic_context_t*);
bool declare_inferred_variable(ast_node_t*,token_t*,ultimate_expr_t*,sematic_context_t*);
bool declare_variable(ast_node_t*,token_t*,sematic_context_t*);
bool resolve_function_signature(ast_node_t*,token_t*,arglist_t*,func_returntype_t*,sematic_context_t*);
bool resolve_struct_signature(ast_node_t*,token_t*,structmembers_t*,sematic_context_t*);
bool resolve_symbol(ast_node_t*,token_t*,sematic_context_t*);
bool resolve_member(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*);
bool resolve_arguments(ast_node_t*,arglist_t*,sematic_context_t*);
bool resolve_member(ast_node_t*,lvalue_noproperty_t*,token_t*,sematic_context_t*);
bool enter_function_context(ast_node_t*,token_t*,func_returntype_t*,sematic_context_t*);
bool check_function_type(ast_node_t*,arglist_t*,func_returntype_t*,sematic_context_t*);
bool leave_function_context(ast_node_t*,sematic_context_t*);
bool enter_struct_context(ast_node_t*,token_t*,sematic_context_t*);
bool leave_struct_context(ast_node_t*,sematic_context_t*);
bool require_valid_variable_type(ast_node_t*,composed_type_t*,sematic_context_t*);
bool check_assignable(ast_node_t*,composed_type_t*,ultimate_expr_t*,sematic_context_t*);
bool infer_variable_type(ast_node_t*,token_t*,ultimate_expr_t*,sematic_context_t*);
bool require_valid_parameter_type(ast_node_t*,composed_type_t*,sematic_context_t*);
bool require_valid_member_type(ast_node_t*,composed_type_t*,sematic_context_t*);
bool require_modifiable_lvalue(ast_node_t*,lvalue_t*,sematic_context_t*);
bool check_assignable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,lvalue_t*,sematic_context_t*);
bool check_addable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_minusable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_mulable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_divable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_modable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_bitandable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_bitorable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_shiftleftable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool check_shiftrightable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,logic_expr_eq_t*,sematic_context_t*);
bool check_equalable(ast_node_t*,logic_expr_or_t*,logic_expr_eq_t*,sematic_context_t*);
bool set_boolean_type(ast_node_t*,sematic_context_t*);
bool check_nequalable(ast_node_t*,logic_expr_or_t*,logic_expr_eq_t*,sematic_context_t*);
bool check_comparable(ast_node_t*,logic_expr_or_t*,logic_expr_eq_t*,sematic_context_t*);
bool require_boolean(ast_node_t*,logic_expr_and_t*,sematic_context_t*);
bool require_boolean(ast_node_t*,logic_expr_or_t*,sematic_context_t*);
bool require_boolean(ast_node_t*,expr_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,expr_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,logic_expr_and_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,logic_expr_or_t*,sematic_context_t*);
bool check_addable(ast_node_t*,term_t*,expr_t*,sematic_context_t*);
bool infer_binary_result_type(ast_node_t*,term_t*,expr_t*,sematic_context_t*);
bool check_minusable(ast_node_t*,term_t*,expr_t*,sematic_context_t*);
bool check_mulable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool infer_binary_result_type(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_divable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_modable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_bitandable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_bitorable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_shiftleftable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool check_shiftrightable(ast_node_t*,power_factor_t*,term_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,power_factor_t*,sematic_context_t*);
bool require_numeric(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool require_numeric(ast_node_t*,power_factor_t*,sematic_context_t*);
bool infer_binary_result_type(ast_node_t*,single_op_factor_t*,power_factor_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool require_lvalue(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool infer_pointer_type(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool require_pointer(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool infer_pointee_type(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool require_boolean(ast_node_t*,single_op_factor_t*,sematic_context_t*);
bool require_pointer(ast_node_t*,lvalue_t*,sematic_context_t*);
bool infer_pointee_type(ast_node_t*,lvalue_t*,sematic_context_t*);
bool require_lvalue(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool propagate_symbol_type(ast_node_t*,token_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,lvalue_noproperty_t*,sematic_context_t*);
bool require_callable(ast_node_t*,lvalue_t*,sematic_context_t*);
bool check_argument_count(ast_node_t*,lvalue_t*,arglist_t*,sematic_context_t*);
bool check_argument_types(ast_node_t*,lvalue_t*,arglist_t*,sematic_context_t*);
bool infer_call_result_type(ast_node_t*,lvalue_t*,sematic_context_t*);
bool check_member_access(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*);
bool propagate_member_type(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*);
bool check_member_access(ast_node_t*,lvalue_noproperty_t*,token_t*,sematic_context_t*);
bool propagate_member_type(ast_node_t*,lvalue_noproperty_t*,token_t*,sematic_context_t*);
bool set_number_type(ast_node_t*,token_t*,sematic_context_t*);
bool set_char_type(ast_node_t*,token_t*,sematic_context_t*);
bool set_string_type(ast_node_t*,token_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,factor_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,term_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,glued_factor_t*,sematic_context_t*);
bool propagate_type(ast_node_t*,assign_expr_t*,sematic_context_t*);
bool check_valid_type(ast_node_t*,composed_type_t*,sematic_context_t*);
bool resolve_type_name(ast_node_t*,token_t*,sematic_context_t*);
bool set_named_type(ast_node_t*,token_t*,sematic_context_t*);
bool require_integer(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool require_constant_expression(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool require_positive(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool require_function_context(ast_node_t*,sematic_context_t*);
bool check_empty_return_type(ast_node_t*,sematic_context_t*);
bool check_match_return_type(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool require_boolean(ast_node_t*,ultimate_expr_t*,sematic_context_t*);
bool begin_definite_function(ast_node_t*,sematic_context_t*);
bool mark_parameters_initialized(ast_node_t*,arglist_t*,sematic_context_t*);
bool end_definite_function(ast_node_t*,sematic_context_t*);
bool mark_initialized(ast_node_t*,token_t*,sematic_context_t*);
bool mark_uninitialized(ast_node_t*,token_t*,sematic_context_t*);
bool push_write_access(ast_node_t*,sematic_context_t*);
bool pop_access_mode(ast_node_t*,sematic_context_t*);
bool mark_lvalue_initialized(ast_node_t*,lvalue_t*,sematic_context_t*);
bool push_read_access(ast_node_t*,sematic_context_t*);
bool push_address_access(ast_node_t*,sematic_context_t*);
bool require_initialized_if_read(ast_node_t*,token_t*,sematic_context_t*);
bool begin_optional_init(ast_node_t*,sematic_context_t*);
bool end_optional_init(ast_node_t*,sematic_context_t*);
bool begin_conditional_init(ast_node_t*,sematic_context_t*);
bool begin_init_branch(ast_node_t*,sematic_context_t*);
bool end_init_branch(ast_node_t*,sematic_context_t*);
bool end_conditional_init(ast_node_t*,sematic_context_t*);
bool record_implicit_init_branch(ast_node_t*,sematic_context_t*);
bool save_init_condition_fallthrough(ast_node_t*,sematic_context_t*);
bool begin_loop_init(ast_node_t*,sematic_context_t*);
bool end_loop_init(ast_node_t*,sematic_context_t*);
bool require_all_paths_return(ast_node_t*,statements_t*,sematic_context_t*);
bool check_control_flow(ast_node_t*,ultimate_expr_t*,statements_t*,elseif_else_t*,sematic_context_t*);
bool check_control_flow(ast_node_t*,ultimate_expr_t*,statements_t*,sematic_context_t*);
bool leave_loop_scope(ast_node_t*,sematic_context_t*);
bool require_loop_context(ast_node_t*,sematic_context_t*);
bool set_terminating_flow(ast_node_t*,sematic_context_t*);
bool set_return_flow(ast_node_t*,sematic_context_t*);
bool set_fallthrough_flow(ast_node_t*,sematic_context_t*);
bool propagate_flow(ast_node_t*,if_t*,sematic_context_t*);
bool propagate_flow(ast_node_t*,while_t*,sematic_context_t*);
bool propagate_flow(ast_node_t*,statement_t*,sematic_context_t*);
bool check_unreachable(ast_node_t*,statement_t*,statements_t*,sematic_context_t*);
bool combine_sequential_flow(ast_node_t*,statement_t*,statements_t*,sematic_context_t*);
bool propagate_flow(ast_node_t*,statements_t*,sematic_context_t*);
bool propagate_flow(ast_node_t*,else_t*,sematic_context_t*);
bool combine_branch_flow(ast_node_t*,elseif_t*,elseif_else_t*,sematic_context_t*);
bool check_predeclare_declaration_fn(declaration_fn_t* node, sematic_context_t* context){
    if(!predeclare_function(node,node->name,node->args,node->return_type,context))return false;
    return true;
}
bool check_predeclare_declaration_struct(declaration_struct_t* node, sematic_context_t* context){
    if(!predeclare_struct(node,node->name,context))return false;
    return true;
}
bool check_predeclare_function_default(function_default_t* node, sematic_context_t* context){
    if(!predeclare_function(node,node->name,node->args,node->return_type,context))return false;
	if(!enter_function_scope(node,context))return false;
	if(!predeclare_parameters(node,node->args,context))return false;
	if(!visit(node->stmts,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_predeclare_struct_default(struct_default_t* node, sematic_context_t* context){
    if(!predeclare_struct(node,node->name,context))return false;
	if(!enter_struct_scope(node,context))return false;
	if(!predeclare_members(node,node->members,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_predeclare_if_default(if_default_t* node, sematic_context_t* context){
    if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
	if(!visit(node->rest_block,context))return false;
    return true;
}
bool check_predeclare_while_default(while_default_t* node, sematic_context_t* context){
    if(!enter_loop_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_predeclare_else_default(else_default_t* node, sematic_context_t* context){
    if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_predeclare_elseif_default(elseif_default_t* node, sematic_context_t* context){
    if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool predeclare_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_DECLARATION_FN:
        return check_predeclare_declaration_fn(static_cast<declaration_fn_t*>(node),context);
        break;

    case NODE_DECLARATION_STRUCT:
        return check_predeclare_declaration_struct(static_cast<declaration_struct_t*>(node),context);
        break;

    case NODE_FUNCTION_DEFAULT:
        return check_predeclare_function_default(static_cast<function_default_t*>(node),context);
        break;

    case NODE_STRUCT_DEFAULT:
        return check_predeclare_struct_default(static_cast<struct_default_t*>(node),context);
        break;

    case NODE_IF_DEFAULT:
        return check_predeclare_if_default(static_cast<if_default_t*>(node),context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_predeclare_while_default(static_cast<while_default_t*>(node),context);
        break;

    case NODE_ELSE_DEFAULT:
        return check_predeclare_else_default(static_cast<else_default_t*>(node),context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_predeclare_elseif_default(static_cast<elseif_default_t*>(node),context);
        break;

    case NODE_FACTOR_ID:
        
        return true;

    case NODE_FACTOR_NUM:
        
        return true;

    case NODE_FACTOR_CH:
        
        return true;

    case NODE_FACTOR_STR:
        
        return true;

    case NODE_GLUED_FACTOR_PAREN:
        if(!visit(static_cast<glued_factor_paren_t*>(node)->expr,context))return false;
        return true;

    case NODE_GLUED_FACTOR_DEF:
        if(!visit(static_cast<glued_factor_def_t*>(node)->left,context))return false;
        return true;

    case NODE_GLUED_FACTOR_VALUE:
        if(!visit(static_cast<glued_factor_value_t*>(node)->value,context))return false;
        return true;

    case NODE_GLUED_FACTOR_CALL:
        if(!visit(static_cast<glued_factor_call_t*>(node)->left,context))return false;
if(!visit(static_cast<glued_factor_call_t*>(node)->args,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        if(!visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NEG:
        if(!visit(static_cast<single_op_factor_neg_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_REF:
        if(!visit(static_cast<single_op_factor_ref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        if(!visit(static_cast<single_op_factor_deref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NOT:
        if(!visit(static_cast<single_op_factor_not_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NONE:
        if(!visit(static_cast<single_op_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_POWER_FACTOR_POW:
        if(!visit(static_cast<power_factor_pow_t*>(node)->left,context))return false;
if(!visit(static_cast<power_factor_pow_t*>(node)->right,context))return false;
        return true;

    case NODE_POWER_FACTOR_NONE:
        if(!visit(static_cast<power_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_TERM_MUL:
        if(!visit(static_cast<term_mul_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mul_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_DIV:
        if(!visit(static_cast<term_div_t*>(node)->left,context))return false;
if(!visit(static_cast<term_div_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_MOD:
        if(!visit(static_cast<term_mod_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mod_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITAND:
        if(!visit(static_cast<term_bitand_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitand_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITOR:
        if(!visit(static_cast<term_bitor_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitor_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTLEFT:
        if(!visit(static_cast<term_shiftleft_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftleft_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTRIGHT:
        if(!visit(static_cast<term_shiftright_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftright_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_FACTOR:
        if(!visit(static_cast<term_factor_t*>(node)->expr,context))return false;
        return true;

    case NODE_EXPR_ADD:
        if(!visit(static_cast<expr_add_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_add_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_SUB:
        if(!visit(static_cast<expr_sub_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_sub_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_TERM:
        if(!visit(static_cast<expr_term_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_AND:
        if(!visit(static_cast<logic_expr_and_and_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_and_and_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_NONE:
        if(!visit(static_cast<logic_expr_and_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_OR:
        if(!visit(static_cast<logic_expr_or_or_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_or_or_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_NONE:
        if(!visit(static_cast<logic_expr_or_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_EQ:
        if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GT:
        if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LT:
        if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GE:
        if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LE:
        if(!visit(static_cast<logic_expr_eq_le_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_le_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NONE:
        if(!visit(static_cast<logic_expr_eq_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_ASSIGN:
        if(!visit(static_cast<assign_expr_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        if(!visit(static_cast<assign_expr_div_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_div_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_LOGIC_EXPR:
        if(!visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_ULTIMATE_EXPR_DEF:
        if(!visit(static_cast<ultimate_expr_def_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_PARENED:
        if(!visit(static_cast<lvalue_noproperty_parened_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        if(!visit(static_cast<lvalue_noproperty_deref_t*>(node)->derefee,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_ID:
        
        return true;

    case NODE_LVALUE_PROP:
        if(!visit(static_cast<lvalue_prop_t*>(node)->left,context))return false;
        return true;

    case NODE_LVALUE_NOPROP:
        if(!visit(static_cast<lvalue_noprop_t*>(node)->expr,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_RAW_TYPE:
        
        return true;

    case NODE_COMPOSED_TYPE_PAREN:
        if(!visit(static_cast<composed_type_paren_t*>(node)->inner_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_PTR:
        if(!visit(static_cast<composed_type_ptr_t*>(node)->pointer_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        if(!visit(static_cast<composed_type_nsizedarr_t*>(node)->element_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        if(!visit(static_cast<composed_type_sizedarr_t*>(node)->element_type,context))return false;
if(!visit(static_cast<composed_type_sizedarr_t*>(node)->array_size,context))return false;
        return true;

    case NODE_DEFINITION_DEFTYPE:
        if(!visit(static_cast<definition_deftype_t*>(node)->def_type,context))return false;
if(!visit(static_cast<definition_deftype_t*>(node)->value,context))return false;
        return true;

    case NODE_DEFINITION_DEFNTYPE:
        if(!visit(static_cast<definition_defntype_t*>(node)->value,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_ONLYELSE:
        if(!visit(static_cast<elseif_else_onlyelse_t*>(node)->else_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_CHAIN:
        if(!visit(static_cast<elseif_else_chain_t*>(node)->elseif_block,context))return false;
if(!visit(static_cast<elseif_else_chain_t*>(node)->rest_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_EMPTY:
        
        return true;

    case NODE_STRUCTMEMBERS_SINGMEM:
        if(!visit(static_cast<structmembers_singmem_t*>(node)->def_type,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_MULTIMEM:
        if(!visit(static_cast<structmembers_multimem_t*>(node)->def_type,context))return false;
if(!visit(static_cast<structmembers_multimem_t*>(node)->other_members,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_EMPTY:
        
        return true;

    case NODE_DECLARATION_VARNTYPE:
        
        return true;

    case NODE_DECLARATION_VAR:
        if(!visit(static_cast<declaration_var_t*>(node)->def_type,context))return false;
        return true;

    case NODE_STATEMENT_EXPR:
        if(!visit(static_cast<statement_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_STATEMENT_DEFINITION:
        if(!visit(static_cast<statement_definition_t*>(node)->def,context))return false;
        return true;

    case NODE_STATEMENT_IF:
        if(!visit(static_cast<statement_if_t*>(node)->if_stmt,context))return false;
        return true;

    case NODE_STATEMENT_WHILE:
        if(!visit(static_cast<statement_while_t*>(node)->while_stmt,context))return false;
        return true;

    case NODE_STATEMENT_DECLARATION:
        if(!visit(static_cast<statement_declaration_t*>(node)->decl_stmt,context))return false;
        return true;

    case NODE_STATEMENT_BREAK:
        
        return true;

    case NODE_STATEMENT_CONTINUE:
        
        return true;

    case NODE_STATEMENT_RETURN_EMPTY:
        
        return true;

    case NODE_STATEMENT_RETURN_STH:
        if(!visit(static_cast<statement_return_sth_t*>(node)->value,context))return false;
        return true;

    case NODE_STATEMENTS_STMT:
        if(!visit(static_cast<statements_stmt_t*>(node)->stmt,context))return false;
        return true;

    case NODE_STATEMENTS_MULTISTMT:
        if(!visit(static_cast<statements_multistmt_t*>(node)->stmt,context))return false;
if(!visit(static_cast<statements_multistmt_t*>(node)->other_stmts,context))return false;
        return true;

    case NODE_STATEMENTS_EMPTY:
        
        return true;

    case NODE_FUNC_RETURNTYPE_HASTYPE:
        if(!visit(static_cast<func_returntype_hastype_t*>(node)->return_type,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_VOID:
        
        return true;

    case NODE_ARGLIST_NONEMPTY_SINGARG:
        if(!visit(static_cast<arglist_nonempty_singarg_t*>(node)->arg_type,context))return false;
        return true;

    case NODE_ARGLIST_NONEMPTY_MULTIARG:
        if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->arg_type,context))return false;
if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->other_args,context))return false;
        return true;

    case NODE_ARGLIST_HASARG:
        if(!visit(static_cast<arglist_hasarg_t*>(node)->args,context))return false;
        return true;

    case NODE_ARGLIST_EMPTY:
        
        return true;

    case NODE_TOP_STATEMENT_FUNC_DEF:
        if(!visit(static_cast<top_statement_func_def_t*>(node)->func,context))return false;
        return true;

    case NODE_TOP_STATEMENT_DECL:
        if(!visit(static_cast<top_statement_decl_t*>(node)->decl,context))return false;
        return true;

    case NODE_TOP_STATEMENT_VAR_DEF:
        if(!visit(static_cast<top_statement_var_def_t*>(node)->def,context))return false;
        return true;

    case NODE_TOP_STATEMENT_STRUCTDEF:
        if(!visit(static_cast<top_statement_structdef_t*>(node)->structdef,context))return false;
        return true;
    }
    return false;
};
bool check_resolve_function_default(function_default_t* node, sematic_context_t* context){
    if(!enter_function_scope(node,context))return false;
	if(!declare_parameters(node,node->args,context))return false;
	if(!visit(node->return_type,context))return false;
	if(!visit(node->stmts,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_resolve_struct_default(struct_default_t* node, sematic_context_t* context){
    if(!enter_struct_scope(node,context))return false;
	if(!declare_members(node,node->members,context))return false;
	if(!visit(node->members,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_resolve_definition_deftype(definition_deftype_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!visit(node->value,context))return false;
	if(!declare_variable(node,node->name,node->def_type,context))return false;
    return true;
}
bool check_resolve_definition_defntype(definition_defntype_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!declare_inferred_variable(node,node->name,node->value,context))return false;
    return true;
}
bool check_resolve_declaration_varntype(declaration_varntype_t* node, sematic_context_t* context){
    if(!declare_variable(node,node->name,context))return false;
    return true;
}
bool check_resolve_declaration_var(declaration_var_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!declare_variable(node,node->name,node->def_type,context))return false;
    return true;
}
bool check_resolve_declaration_fn(declaration_fn_t* node, sematic_context_t* context){
    if(!visit(node->args,context))return false;
	if(!visit(node->return_type,context))return false;
	if(!resolve_function_signature(node,node->name,node->args,node->return_type,context))return false;
    return true;
}
bool check_resolve_declaration_struct(declaration_struct_t* node, sematic_context_t* context){
    if(!visit(node->members,context))return false;
	if(!resolve_struct_signature(node,node->name,node->members,context))return false;
    return true;
}
bool check_resolve_factor_id(factor_id_t* node, sematic_context_t* context){
    if(!resolve_symbol(node,node->value,context))return false;
    return true;
}
bool check_resolve_glued_factor_def(glued_factor_def_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!resolve_member(node,node->left,node->right,context))return false;
    return true;
}
bool check_resolve_glued_factor_call(glued_factor_call_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->args,context))return false;
	if(!resolve_arguments(node,node->args,context))return false;
    return true;
}
bool check_resolve_lvalue_prop(lvalue_prop_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!resolve_member(node,node->left,node->right,context))return false;
    return true;
}
bool check_resolve_lvalue_noproperty_id(lvalue_noproperty_id_t* node, sematic_context_t* context){
    if(!resolve_symbol(node,node->id,context))return false;
    return true;
}
bool check_resolve_if_default(if_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
	if(!visit(node->rest_block,context))return false;
    return true;
}
bool check_resolve_while_default(while_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!enter_loop_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_resolve_else_default(else_default_t* node, sematic_context_t* context){
    if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_resolve_elseif_default(elseif_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!enter_block_scope(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_resolve_statement_definition(statement_definition_t* node, sematic_context_t* context){
    if(!visit(node->def,context))return false;
    return true;
}
bool check_resolve_statement_expr(statement_expr_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
    return true;
}
bool check_resolve_statement_declaration(statement_declaration_t* node, sematic_context_t* context){
    if(!visit(node->decl_stmt,context))return false;
    return true;
}
bool check_resolve_statement_if(statement_if_t* node, sematic_context_t* context){
    if(!visit(node->if_stmt,context))return false;
    return true;
}
bool check_resolve_statement_while(statement_while_t* node, sematic_context_t* context){
    if(!visit(node->while_stmt,context))return false;
    return true;
}
bool check_resolve_statement_return_sth(statement_return_sth_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
    return true;
}
bool resolve_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_resolve_function_default(static_cast<function_default_t*>(node),context);
        break;

    case NODE_STRUCT_DEFAULT:
        return check_resolve_struct_default(static_cast<struct_default_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFTYPE:
        return check_resolve_definition_deftype(static_cast<definition_deftype_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFNTYPE:
        return check_resolve_definition_defntype(static_cast<definition_defntype_t*>(node),context);
        break;

    case NODE_DECLARATION_VARNTYPE:
        return check_resolve_declaration_varntype(static_cast<declaration_varntype_t*>(node),context);
        break;

    case NODE_DECLARATION_VAR:
        return check_resolve_declaration_var(static_cast<declaration_var_t*>(node),context);
        break;

    case NODE_DECLARATION_FN:
        return check_resolve_declaration_fn(static_cast<declaration_fn_t*>(node),context);
        break;

    case NODE_DECLARATION_STRUCT:
        return check_resolve_declaration_struct(static_cast<declaration_struct_t*>(node),context);
        break;

    case NODE_FACTOR_ID:
        return check_resolve_factor_id(static_cast<factor_id_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_DEF:
        return check_resolve_glued_factor_def(static_cast<glued_factor_def_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_CALL:
        return check_resolve_glued_factor_call(static_cast<glued_factor_call_t*>(node),context);
        break;

    case NODE_LVALUE_PROP:
        return check_resolve_lvalue_prop(static_cast<lvalue_prop_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_ID:
        return check_resolve_lvalue_noproperty_id(static_cast<lvalue_noproperty_id_t*>(node),context);
        break;

    case NODE_IF_DEFAULT:
        return check_resolve_if_default(static_cast<if_default_t*>(node),context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_resolve_while_default(static_cast<while_default_t*>(node),context);
        break;

    case NODE_ELSE_DEFAULT:
        return check_resolve_else_default(static_cast<else_default_t*>(node),context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_resolve_elseif_default(static_cast<elseif_default_t*>(node),context);
        break;

    case NODE_STATEMENT_DEFINITION:
        return check_resolve_statement_definition(static_cast<statement_definition_t*>(node),context);
        break;

    case NODE_STATEMENT_EXPR:
        return check_resolve_statement_expr(static_cast<statement_expr_t*>(node),context);
        break;

    case NODE_STATEMENT_DECLARATION:
        return check_resolve_statement_declaration(static_cast<statement_declaration_t*>(node),context);
        break;

    case NODE_STATEMENT_IF:
        return check_resolve_statement_if(static_cast<statement_if_t*>(node),context);
        break;

    case NODE_STATEMENT_WHILE:
        return check_resolve_statement_while(static_cast<statement_while_t*>(node),context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_resolve_statement_return_sth(static_cast<statement_return_sth_t*>(node),context);
        break;

    case NODE_FACTOR_NUM:
        
        return true;

    case NODE_FACTOR_CH:
        
        return true;

    case NODE_FACTOR_STR:
        
        return true;

    case NODE_GLUED_FACTOR_PAREN:
        if(!visit(static_cast<glued_factor_paren_t*>(node)->expr,context))return false;
        return true;

    case NODE_GLUED_FACTOR_VALUE:
        if(!visit(static_cast<glued_factor_value_t*>(node)->value,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        if(!visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NEG:
        if(!visit(static_cast<single_op_factor_neg_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_REF:
        if(!visit(static_cast<single_op_factor_ref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        if(!visit(static_cast<single_op_factor_deref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NOT:
        if(!visit(static_cast<single_op_factor_not_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NONE:
        if(!visit(static_cast<single_op_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_POWER_FACTOR_POW:
        if(!visit(static_cast<power_factor_pow_t*>(node)->left,context))return false;
if(!visit(static_cast<power_factor_pow_t*>(node)->right,context))return false;
        return true;

    case NODE_POWER_FACTOR_NONE:
        if(!visit(static_cast<power_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_TERM_MUL:
        if(!visit(static_cast<term_mul_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mul_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_DIV:
        if(!visit(static_cast<term_div_t*>(node)->left,context))return false;
if(!visit(static_cast<term_div_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_MOD:
        if(!visit(static_cast<term_mod_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mod_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITAND:
        if(!visit(static_cast<term_bitand_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitand_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITOR:
        if(!visit(static_cast<term_bitor_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitor_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTLEFT:
        if(!visit(static_cast<term_shiftleft_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftleft_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTRIGHT:
        if(!visit(static_cast<term_shiftright_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftright_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_FACTOR:
        if(!visit(static_cast<term_factor_t*>(node)->expr,context))return false;
        return true;

    case NODE_EXPR_ADD:
        if(!visit(static_cast<expr_add_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_add_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_SUB:
        if(!visit(static_cast<expr_sub_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_sub_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_TERM:
        if(!visit(static_cast<expr_term_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_AND:
        if(!visit(static_cast<logic_expr_and_and_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_and_and_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_NONE:
        if(!visit(static_cast<logic_expr_and_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_OR:
        if(!visit(static_cast<logic_expr_or_or_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_or_or_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_NONE:
        if(!visit(static_cast<logic_expr_or_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_EQ:
        if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GT:
        if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LT:
        if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GE:
        if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LE:
        if(!visit(static_cast<logic_expr_eq_le_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_le_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NONE:
        if(!visit(static_cast<logic_expr_eq_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_ASSIGN:
        if(!visit(static_cast<assign_expr_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        if(!visit(static_cast<assign_expr_div_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_div_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_LOGIC_EXPR:
        if(!visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_ULTIMATE_EXPR_DEF:
        if(!visit(static_cast<ultimate_expr_def_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_PARENED:
        if(!visit(static_cast<lvalue_noproperty_parened_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        if(!visit(static_cast<lvalue_noproperty_deref_t*>(node)->derefee,context))return false;
        return true;

    case NODE_LVALUE_NOPROP:
        if(!visit(static_cast<lvalue_noprop_t*>(node)->expr,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_RAW_TYPE:
        
        return true;

    case NODE_COMPOSED_TYPE_PAREN:
        if(!visit(static_cast<composed_type_paren_t*>(node)->inner_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_PTR:
        if(!visit(static_cast<composed_type_ptr_t*>(node)->pointer_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        if(!visit(static_cast<composed_type_nsizedarr_t*>(node)->element_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        if(!visit(static_cast<composed_type_sizedarr_t*>(node)->element_type,context))return false;
if(!visit(static_cast<composed_type_sizedarr_t*>(node)->array_size,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_ONLYELSE:
        if(!visit(static_cast<elseif_else_onlyelse_t*>(node)->else_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_CHAIN:
        if(!visit(static_cast<elseif_else_chain_t*>(node)->elseif_block,context))return false;
if(!visit(static_cast<elseif_else_chain_t*>(node)->rest_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_EMPTY:
        
        return true;

    case NODE_STRUCTMEMBERS_SINGMEM:
        if(!visit(static_cast<structmembers_singmem_t*>(node)->def_type,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_MULTIMEM:
        if(!visit(static_cast<structmembers_multimem_t*>(node)->def_type,context))return false;
if(!visit(static_cast<structmembers_multimem_t*>(node)->other_members,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_EMPTY:
        
        return true;

    case NODE_STATEMENT_BREAK:
        
        return true;

    case NODE_STATEMENT_CONTINUE:
        
        return true;

    case NODE_STATEMENT_RETURN_EMPTY:
        
        return true;

    case NODE_STATEMENTS_STMT:
        if(!visit(static_cast<statements_stmt_t*>(node)->stmt,context))return false;
        return true;

    case NODE_STATEMENTS_MULTISTMT:
        if(!visit(static_cast<statements_multistmt_t*>(node)->stmt,context))return false;
if(!visit(static_cast<statements_multistmt_t*>(node)->other_stmts,context))return false;
        return true;

    case NODE_STATEMENTS_EMPTY:
        
        return true;

    case NODE_FUNC_RETURNTYPE_HASTYPE:
        if(!visit(static_cast<func_returntype_hastype_t*>(node)->return_type,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_VOID:
        
        return true;

    case NODE_ARGLIST_NONEMPTY_SINGARG:
        if(!visit(static_cast<arglist_nonempty_singarg_t*>(node)->arg_type,context))return false;
        return true;

    case NODE_ARGLIST_NONEMPTY_MULTIARG:
        if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->arg_type,context))return false;
if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->other_args,context))return false;
        return true;

    case NODE_ARGLIST_HASARG:
        if(!visit(static_cast<arglist_hasarg_t*>(node)->args,context))return false;
        return true;

    case NODE_ARGLIST_EMPTY:
        
        return true;

    case NODE_TOP_STATEMENT_FUNC_DEF:
        if(!visit(static_cast<top_statement_func_def_t*>(node)->func,context))return false;
        return true;

    case NODE_TOP_STATEMENT_DECL:
        if(!visit(static_cast<top_statement_decl_t*>(node)->decl,context))return false;
        return true;

    case NODE_TOP_STATEMENT_VAR_DEF:
        if(!visit(static_cast<top_statement_var_def_t*>(node)->def,context))return false;
        return true;

    case NODE_TOP_STATEMENT_STRUCTDEF:
        if(!visit(static_cast<top_statement_structdef_t*>(node)->structdef,context))return false;
        return true;
    }
    return false;
};
bool check_typecheck_function_default(function_default_t* node, sematic_context_t* context){
    if(!enter_function_context(node,node->name,node->return_type,context))return false;
	if(!visit(node->args,context))return false;
	if(!visit(node->return_type,context))return false;
	if(!check_function_type(node,node->args,node->return_type,context))return false;
	if(!visit(node->stmts,context))return false;
	if(!leave_function_context(node,context))return false;
    return true;
}
bool check_typecheck_struct_default(struct_default_t* node, sematic_context_t* context){
    if(!enter_struct_context(node,node->name,context))return false;
	if(!visit(node->members,context))return false;
	if(!leave_struct_context(node,context))return false;
    return true;
}
bool check_typecheck_definition_deftype(definition_deftype_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!require_valid_variable_type(node,node->def_type,context))return false;
	if(!visit(node->value,context))return false;
	if(!check_assignable(node,node->def_type,node->value,context))return false;
    return true;
}
bool check_typecheck_definition_defntype(definition_defntype_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!infer_variable_type(node,node->name,node->value,context))return false;
    return true;
}
bool check_typecheck_declaration_var(declaration_var_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!require_valid_variable_type(node,node->def_type,context))return false;
    return true;
}
bool check_typecheck_declaration_fn(declaration_fn_t* node, sematic_context_t* context){
    if(!visit(node->args,context))return false;
	if(!visit(node->return_type,context))return false;
	if(!check_function_type(node,node->args,node->return_type,context))return false;
    return true;
}
bool check_typecheck_declaration_struct(declaration_struct_t* node, sematic_context_t* context){
    if(!visit(node->members,context))return false;
    return true;
}
bool check_typecheck_arglist_nonempty_singarg(arglist_nonempty_singarg_t* node, sematic_context_t* context){
    if(!visit(node->arg_type,context))return false;
	if(!require_valid_parameter_type(node,node->arg_type,context))return false;
    return true;
}
bool check_typecheck_arglist_nonempty_multiarg(arglist_nonempty_multiarg_t* node, sematic_context_t* context){
    if(!visit(node->arg_type,context))return false;
	if(!require_valid_parameter_type(node,node->arg_type,context))return false;
	if(!visit(node->other_args,context))return false;
    return true;
}
bool check_typecheck_structmembers_singmem(structmembers_singmem_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!require_valid_member_type(node,node->def_type,context))return false;
    return true;
}
bool check_typecheck_structmembers_multimem(structmembers_multimem_t* node, sematic_context_t* context){
    if(!visit(node->def_type,context))return false;
	if(!require_valid_member_type(node,node->def_type,context))return false;
	if(!visit(node->other_members,context))return false;
    return true;
}
bool check_typecheck_assign_expr_assign(assign_expr_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_assignable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_plus_assign(assign_expr_plus_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_addable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_minus_assign(assign_expr_minus_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_minusable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_mul_assign(assign_expr_mul_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_mulable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_div_assign(assign_expr_div_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_divable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_mod_assign(assign_expr_mod_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_modable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_bitand_assign(assign_expr_bitand_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_bitandable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_bitor_assign(assign_expr_bitor_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_bitorable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_shiftleft_assign(assign_expr_shiftleft_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_shiftleftable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_shiftright_assign(assign_expr_shiftright_assign_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_modifiable_lvalue(node,node->left,context))return false;
	if(!check_shiftrightable(node,node->left,node->right,context))return false;
	if(!propagate_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_assign_expr_logic_expr(assign_expr_logic_expr_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_eq(logic_expr_eq_eq_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_equalable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_neq(logic_expr_eq_neq_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_nequalable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_gt(logic_expr_eq_gt_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_comparable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_lt(logic_expr_eq_lt_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_comparable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_ge(logic_expr_eq_ge_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_comparable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_le(logic_expr_eq_le_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_comparable(node,node->left,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_or_or(logic_expr_or_or_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_boolean(node,node->left,context))return false;
	if(!require_boolean(node,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_and_and(logic_expr_and_and_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_boolean(node,node->left,context))return false;
	if(!require_boolean(node,node->right,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_logic_expr_and_none(logic_expr_and_none_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_logic_expr_or_none(logic_expr_or_none_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_logic_expr_eq_none(logic_expr_eq_none_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_expr_add(expr_add_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_addable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_expr_sub(expr_sub_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_minusable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_mul(term_mul_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_mulable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_div(term_div_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_divable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_mod(term_mod_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_modable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_bitand(term_bitand_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_bitandable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_bitor(term_bitor_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_bitorable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_shiftleft(term_shiftleft_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_shiftleftable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_shiftright(term_shiftright_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!check_shiftrightable(node,node->left,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_term_factor(term_factor_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_power_factor_pow(power_factor_pow_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->right,context))return false;
	if(!require_numeric(node,node->left,context))return false;
	if(!require_numeric(node,node->right,context))return false;
	if(!infer_binary_result_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_bitnot(single_op_factor_bitnot_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_numeric(node,node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_neg(single_op_factor_neg_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_numeric(node,node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_ref(single_op_factor_ref_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_lvalue(node,node->expr,context))return false;
	if(!infer_pointer_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_deref(single_op_factor_deref_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_pointer(node,node->expr,context))return false;
	if(!infer_pointee_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_not(single_op_factor_not_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_boolean(node,node->expr,context))return false;
	if(!set_boolean_type(node,context))return false;
    return true;
}
bool check_typecheck_lvalue_noproperty_deref(lvalue_noproperty_deref_t* node, sematic_context_t* context){
    if(!visit(node->derefee,context))return false;
	if(!require_pointer(node,node->derefee,context))return false;
	if(!infer_pointee_type(node,node->derefee,context))return false;
    return true;
}
bool check_typecheck_lvalue_noproperty_parened(lvalue_noproperty_parened_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!require_lvalue(node,node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_lvalue_noproperty_id(lvalue_noproperty_id_t* node, sematic_context_t* context){
    if(!propagate_symbol_type(node,node->id,context))return false;
    return true;
}
bool check_typecheck_lvalue_noprop(lvalue_noprop_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_glued_factor_call(glued_factor_call_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!visit(node->args,context))return false;
	if(!require_callable(node,node->left,context))return false;
	if(!check_argument_count(node,node->left,node->args,context))return false;
	if(!check_argument_types(node,node->left,node->args,context))return false;
	if(!infer_call_result_type(node,node->left,context))return false;
    return true;
}
bool check_typecheck_glued_factor_def(glued_factor_def_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!check_member_access(node,node->left,node->right,context))return false;
	if(!propagate_member_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_lvalue_prop(lvalue_prop_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!check_member_access(node,node->left,node->right,context))return false;
	if(!propagate_member_type(node,node->left,node->right,context))return false;
    return true;
}
bool check_typecheck_factor_id(factor_id_t* node, sematic_context_t* context){
    if(!propagate_symbol_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_factor_num(factor_num_t* node, sematic_context_t* context){
    if(!set_number_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_factor_ch(factor_ch_t* node, sematic_context_t* context){
    if(!set_char_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_factor_str(factor_str_t* node, sematic_context_t* context){
    if(!set_string_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_glued_factor_value(glued_factor_value_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!propagate_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_glued_factor_paren(glued_factor_paren_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_expr_term(expr_term_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_power_factor_none(power_factor_none_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_single_op_factor_none(single_op_factor_none_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_ultimate_expr_def(ultimate_expr_def_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!propagate_type(node,node->expr,context))return false;
    return true;
}
bool check_typecheck_composed_type_paren(composed_type_paren_t* node, sematic_context_t* context){
    if(!visit(node->inner_type,context))return false;
	if(!check_valid_type(node,node->inner_type,context))return false;
    return true;
}
bool check_typecheck_composed_type_raw_type(composed_type_raw_type_t* node, sematic_context_t* context){
    if(!resolve_type_name(node,node->inner_type,context))return false;
	if(!set_named_type(node,node->inner_type,context))return false;
    return true;
}
bool check_typecheck_composed_type_ptr(composed_type_ptr_t* node, sematic_context_t* context){
    if(!visit(node->pointer_type,context))return false;
	if(!check_valid_type(node,node->pointer_type,context))return false;
    return true;
}
bool check_typecheck_composed_type_nsizedarr(composed_type_nsizedarr_t* node, sematic_context_t* context){
    if(!visit(node->element_type,context))return false;
	if(!check_valid_type(node,node->element_type,context))return false;
    return true;
}
bool check_typecheck_composed_type_sizedarr(composed_type_sizedarr_t* node, sematic_context_t* context){
    if(!visit(node->element_type,context))return false;
	if(!visit(node->array_size,context))return false;
	if(!check_valid_type(node,node->element_type,context))return false;
	if(!require_integer(node,node->array_size,context))return false;
	if(!require_constant_expression(node,node->array_size,context))return false;
	if(!require_positive(node,node->array_size,context))return false;
    return true;
}
bool check_typecheck_statement_return_empty(statement_return_empty_t* node, sematic_context_t* context){
    if(!require_function_context(node,context))return false;
	if(!check_empty_return_type(node,context))return false;
    return true;
}
bool check_typecheck_statement_return_sth(statement_return_sth_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!require_function_context(node,context))return false;
	if(!check_match_return_type(node,node->value,context))return false;
    return true;
}
bool check_typecheck_if_default(if_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!require_boolean(node,node->condition,context))return false;
	if(!visit(node->statements,context))return false;
	if(!visit(node->rest_block,context))return false;
    return true;
}
bool check_typecheck_elseif_default(elseif_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!require_boolean(node,node->condition,context))return false;
	if(!visit(node->statements,context))return false;
    return true;
}
bool check_typecheck_while_default(while_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!require_boolean(node,node->condition,context))return false;
	if(!visit(node->statements,context))return false;
    return true;
}
bool typecheck_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_typecheck_function_default(static_cast<function_default_t*>(node),context);
        break;

    case NODE_STRUCT_DEFAULT:
        return check_typecheck_struct_default(static_cast<struct_default_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFTYPE:
        return check_typecheck_definition_deftype(static_cast<definition_deftype_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFNTYPE:
        return check_typecheck_definition_defntype(static_cast<definition_defntype_t*>(node),context);
        break;

    case NODE_DECLARATION_VAR:
        return check_typecheck_declaration_var(static_cast<declaration_var_t*>(node),context);
        break;

    case NODE_DECLARATION_FN:
        return check_typecheck_declaration_fn(static_cast<declaration_fn_t*>(node),context);
        break;

    case NODE_DECLARATION_STRUCT:
        return check_typecheck_declaration_struct(static_cast<declaration_struct_t*>(node),context);
        break;

    case NODE_ARGLIST_NONEMPTY_SINGARG:
        return check_typecheck_arglist_nonempty_singarg(static_cast<arglist_nonempty_singarg_t*>(node),context);
        break;

    case NODE_ARGLIST_NONEMPTY_MULTIARG:
        return check_typecheck_arglist_nonempty_multiarg(static_cast<arglist_nonempty_multiarg_t*>(node),context);
        break;

    case NODE_STRUCTMEMBERS_SINGMEM:
        return check_typecheck_structmembers_singmem(static_cast<structmembers_singmem_t*>(node),context);
        break;

    case NODE_STRUCTMEMBERS_MULTIMEM:
        return check_typecheck_structmembers_multimem(static_cast<structmembers_multimem_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_ASSIGN:
        return check_typecheck_assign_expr_assign(static_cast<assign_expr_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        return check_typecheck_assign_expr_plus_assign(static_cast<assign_expr_plus_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        return check_typecheck_assign_expr_minus_assign(static_cast<assign_expr_minus_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        return check_typecheck_assign_expr_mul_assign(static_cast<assign_expr_mul_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        return check_typecheck_assign_expr_div_assign(static_cast<assign_expr_div_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        return check_typecheck_assign_expr_mod_assign(static_cast<assign_expr_mod_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        return check_typecheck_assign_expr_bitand_assign(static_cast<assign_expr_bitand_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        return check_typecheck_assign_expr_bitor_assign(static_cast<assign_expr_bitor_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        return check_typecheck_assign_expr_shiftleft_assign(static_cast<assign_expr_shiftleft_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        return check_typecheck_assign_expr_shiftright_assign(static_cast<assign_expr_shiftright_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_LOGIC_EXPR:
        return check_typecheck_assign_expr_logic_expr(static_cast<assign_expr_logic_expr_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_EQ:
        return check_typecheck_logic_expr_eq_eq(static_cast<logic_expr_eq_eq_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        return check_typecheck_logic_expr_eq_neq(static_cast<logic_expr_eq_neq_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_GT:
        return check_typecheck_logic_expr_eq_gt(static_cast<logic_expr_eq_gt_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_LT:
        return check_typecheck_logic_expr_eq_lt(static_cast<logic_expr_eq_lt_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_GE:
        return check_typecheck_logic_expr_eq_ge(static_cast<logic_expr_eq_ge_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_LE:
        return check_typecheck_logic_expr_eq_le(static_cast<logic_expr_eq_le_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_OR_OR:
        return check_typecheck_logic_expr_or_or(static_cast<logic_expr_or_or_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_AND_AND:
        return check_typecheck_logic_expr_and_and(static_cast<logic_expr_and_and_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_AND_NONE:
        return check_typecheck_logic_expr_and_none(static_cast<logic_expr_and_none_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_OR_NONE:
        return check_typecheck_logic_expr_or_none(static_cast<logic_expr_or_none_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_EQ_NONE:
        return check_typecheck_logic_expr_eq_none(static_cast<logic_expr_eq_none_t*>(node),context);
        break;

    case NODE_EXPR_ADD:
        return check_typecheck_expr_add(static_cast<expr_add_t*>(node),context);
        break;

    case NODE_EXPR_SUB:
        return check_typecheck_expr_sub(static_cast<expr_sub_t*>(node),context);
        break;

    case NODE_TERM_MUL:
        return check_typecheck_term_mul(static_cast<term_mul_t*>(node),context);
        break;

    case NODE_TERM_DIV:
        return check_typecheck_term_div(static_cast<term_div_t*>(node),context);
        break;

    case NODE_TERM_MOD:
        return check_typecheck_term_mod(static_cast<term_mod_t*>(node),context);
        break;

    case NODE_TERM_BITAND:
        return check_typecheck_term_bitand(static_cast<term_bitand_t*>(node),context);
        break;

    case NODE_TERM_BITOR:
        return check_typecheck_term_bitor(static_cast<term_bitor_t*>(node),context);
        break;

    case NODE_TERM_SHIFTLEFT:
        return check_typecheck_term_shiftleft(static_cast<term_shiftleft_t*>(node),context);
        break;

    case NODE_TERM_SHIFTRIGHT:
        return check_typecheck_term_shiftright(static_cast<term_shiftright_t*>(node),context);
        break;

    case NODE_TERM_FACTOR:
        return check_typecheck_term_factor(static_cast<term_factor_t*>(node),context);
        break;

    case NODE_POWER_FACTOR_POW:
        return check_typecheck_power_factor_pow(static_cast<power_factor_pow_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        return check_typecheck_single_op_factor_bitnot(static_cast<single_op_factor_bitnot_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_NEG:
        return check_typecheck_single_op_factor_neg(static_cast<single_op_factor_neg_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_REF:
        return check_typecheck_single_op_factor_ref(static_cast<single_op_factor_ref_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        return check_typecheck_single_op_factor_deref(static_cast<single_op_factor_deref_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_NOT:
        return check_typecheck_single_op_factor_not(static_cast<single_op_factor_not_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        return check_typecheck_lvalue_noproperty_deref(static_cast<lvalue_noproperty_deref_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_PARENED:
        return check_typecheck_lvalue_noproperty_parened(static_cast<lvalue_noproperty_parened_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_ID:
        return check_typecheck_lvalue_noproperty_id(static_cast<lvalue_noproperty_id_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROP:
        return check_typecheck_lvalue_noprop(static_cast<lvalue_noprop_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_CALL:
        return check_typecheck_glued_factor_call(static_cast<glued_factor_call_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_DEF:
        return check_typecheck_glued_factor_def(static_cast<glued_factor_def_t*>(node),context);
        break;

    case NODE_LVALUE_PROP:
        return check_typecheck_lvalue_prop(static_cast<lvalue_prop_t*>(node),context);
        break;

    case NODE_FACTOR_ID:
        return check_typecheck_factor_id(static_cast<factor_id_t*>(node),context);
        break;

    case NODE_FACTOR_NUM:
        return check_typecheck_factor_num(static_cast<factor_num_t*>(node),context);
        break;

    case NODE_FACTOR_CH:
        return check_typecheck_factor_ch(static_cast<factor_ch_t*>(node),context);
        break;

    case NODE_FACTOR_STR:
        return check_typecheck_factor_str(static_cast<factor_str_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_VALUE:
        return check_typecheck_glued_factor_value(static_cast<glued_factor_value_t*>(node),context);
        break;

    case NODE_GLUED_FACTOR_PAREN:
        return check_typecheck_glued_factor_paren(static_cast<glued_factor_paren_t*>(node),context);
        break;

    case NODE_EXPR_TERM:
        return check_typecheck_expr_term(static_cast<expr_term_t*>(node),context);
        break;

    case NODE_POWER_FACTOR_NONE:
        return check_typecheck_power_factor_none(static_cast<power_factor_none_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_NONE:
        return check_typecheck_single_op_factor_none(static_cast<single_op_factor_none_t*>(node),context);
        break;

    case NODE_ULTIMATE_EXPR_DEF:
        return check_typecheck_ultimate_expr_def(static_cast<ultimate_expr_def_t*>(node),context);
        break;

    case NODE_COMPOSED_TYPE_PAREN:
        return check_typecheck_composed_type_paren(static_cast<composed_type_paren_t*>(node),context);
        break;

    case NODE_COMPOSED_TYPE_RAW_TYPE:
        return check_typecheck_composed_type_raw_type(static_cast<composed_type_raw_type_t*>(node),context);
        break;

    case NODE_COMPOSED_TYPE_PTR:
        return check_typecheck_composed_type_ptr(static_cast<composed_type_ptr_t*>(node),context);
        break;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        return check_typecheck_composed_type_nsizedarr(static_cast<composed_type_nsizedarr_t*>(node),context);
        break;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        return check_typecheck_composed_type_sizedarr(static_cast<composed_type_sizedarr_t*>(node),context);
        break;

    case NODE_STATEMENT_RETURN_EMPTY:
        return check_typecheck_statement_return_empty(static_cast<statement_return_empty_t*>(node),context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_typecheck_statement_return_sth(static_cast<statement_return_sth_t*>(node),context);
        break;

    case NODE_IF_DEFAULT:
        return check_typecheck_if_default(static_cast<if_default_t*>(node),context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_typecheck_elseif_default(static_cast<elseif_default_t*>(node),context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_typecheck_while_default(static_cast<while_default_t*>(node),context);
        break;

    case NODE_ELSE_DEFAULT:
        if(!visit(static_cast<else_default_t*>(node)->statements,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_ONLYELSE:
        if(!visit(static_cast<elseif_else_onlyelse_t*>(node)->else_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_CHAIN:
        if(!visit(static_cast<elseif_else_chain_t*>(node)->elseif_block,context))return false;
if(!visit(static_cast<elseif_else_chain_t*>(node)->rest_block,context))return false;
        return true;

    case NODE_ELSEIF_ELSE_EMPTY:
        
        return true;

    case NODE_STRUCTMEMBERS_EMPTY:
        
        return true;

    case NODE_DECLARATION_VARNTYPE:
        
        return true;

    case NODE_STATEMENT_EXPR:
        if(!visit(static_cast<statement_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_STATEMENT_DEFINITION:
        if(!visit(static_cast<statement_definition_t*>(node)->def,context))return false;
        return true;

    case NODE_STATEMENT_IF:
        if(!visit(static_cast<statement_if_t*>(node)->if_stmt,context))return false;
        return true;

    case NODE_STATEMENT_WHILE:
        if(!visit(static_cast<statement_while_t*>(node)->while_stmt,context))return false;
        return true;

    case NODE_STATEMENT_DECLARATION:
        if(!visit(static_cast<statement_declaration_t*>(node)->decl_stmt,context))return false;
        return true;

    case NODE_STATEMENT_BREAK:
        
        return true;

    case NODE_STATEMENT_CONTINUE:
        
        return true;

    case NODE_STATEMENTS_STMT:
        if(!visit(static_cast<statements_stmt_t*>(node)->stmt,context))return false;
        return true;

    case NODE_STATEMENTS_MULTISTMT:
        if(!visit(static_cast<statements_multistmt_t*>(node)->stmt,context))return false;
if(!visit(static_cast<statements_multistmt_t*>(node)->other_stmts,context))return false;
        return true;

    case NODE_STATEMENTS_EMPTY:
        
        return true;

    case NODE_FUNC_RETURNTYPE_HASTYPE:
        if(!visit(static_cast<func_returntype_hastype_t*>(node)->return_type,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_VOID:
        
        return true;

    case NODE_ARGLIST_HASARG:
        if(!visit(static_cast<arglist_hasarg_t*>(node)->args,context))return false;
        return true;

    case NODE_ARGLIST_EMPTY:
        
        return true;

    case NODE_TOP_STATEMENT_FUNC_DEF:
        if(!visit(static_cast<top_statement_func_def_t*>(node)->func,context))return false;
        return true;

    case NODE_TOP_STATEMENT_DECL:
        if(!visit(static_cast<top_statement_decl_t*>(node)->decl,context))return false;
        return true;

    case NODE_TOP_STATEMENT_VAR_DEF:
        if(!visit(static_cast<top_statement_var_def_t*>(node)->def,context))return false;
        return true;

    case NODE_TOP_STATEMENT_STRUCTDEF:
        if(!visit(static_cast<top_statement_structdef_t*>(node)->structdef,context))return false;
        return true;
    }
    return false;
};
bool check_definite_init_function_default(function_default_t* node, sematic_context_t* context){
    if(!begin_definite_function(node,context))return false;
	if(!mark_parameters_initialized(node,node->args,context))return false;
	if(!visit(node->stmts,context))return false;
	if(!end_definite_function(node,context))return false;
    return true;
}
bool check_definite_init_definition_deftype(definition_deftype_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!mark_initialized(node,node->name,context))return false;
    return true;
}
bool check_definite_init_definition_defntype(definition_defntype_t* node, sematic_context_t* context){
    if(!visit(node->value,context))return false;
	if(!mark_initialized(node,node->name,context))return false;
    return true;
}
bool check_definite_init_declaration_varntype(declaration_varntype_t* node, sematic_context_t* context){
    if(!mark_uninitialized(node,node->name,context))return false;
    return true;
}
bool check_definite_init_declaration_var(declaration_var_t* node, sematic_context_t* context){
    if(!mark_uninitialized(node,node->name,context))return false;
    return true;
}
bool check_definite_init_assign_expr_assign(assign_expr_assign_t* node, sematic_context_t* context){
    if(!push_write_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
	if(!mark_lvalue_initialized(node,node->left,context))return false;
    return true;
}
bool check_definite_init_assign_expr_plus_assign(assign_expr_plus_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_minus_assign(assign_expr_minus_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_mul_assign(assign_expr_mul_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_div_assign(assign_expr_div_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_mod_assign(assign_expr_mod_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_bitand_assign(assign_expr_bitand_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_bitor_assign(assign_expr_bitor_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_shiftleft_assign(assign_expr_shiftleft_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_assign_expr_shiftright_assign(assign_expr_shiftright_assign_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->left,context))return false;
	if(!pop_access_mode(node,context))return false;
	if(!visit(node->right,context))return false;
    return true;
}
bool check_definite_init_single_op_factor_ref(single_op_factor_ref_t* node, sematic_context_t* context){
    if(!push_address_access(node,context))return false;
	if(!visit(node->expr,context))return false;
	if(!pop_access_mode(node,context))return false;
    return true;
}
bool check_definite_init_single_op_factor_deref(single_op_factor_deref_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->expr,context))return false;
	if(!pop_access_mode(node,context))return false;
    return true;
}
bool check_definite_init_lvalue_noproperty_deref(lvalue_noproperty_deref_t* node, sematic_context_t* context){
    if(!push_read_access(node,context))return false;
	if(!visit(node->derefee,context))return false;
	if(!pop_access_mode(node,context))return false;
    return true;
}
bool check_definite_init_factor_id(factor_id_t* node, sematic_context_t* context){
    if(!require_initialized_if_read(node,node->value,context))return false;
    return true;
}
bool check_definite_init_lvalue_noproperty_id(lvalue_noproperty_id_t* node, sematic_context_t* context){
    if(!require_initialized_if_read(node,node->id,context))return false;
    return true;
}
bool check_definite_init_logic_expr_and_and(logic_expr_and_and_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!begin_optional_init(node,context))return false;
	if(!visit(node->right,context))return false;
	if(!end_optional_init(node,context))return false;
    return true;
}
bool check_definite_init_logic_expr_or_or(logic_expr_or_or_t* node, sematic_context_t* context){
    if(!visit(node->left,context))return false;
	if(!begin_optional_init(node,context))return false;
	if(!visit(node->right,context))return false;
	if(!end_optional_init(node,context))return false;
    return true;
}
bool check_definite_init_if_default(if_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!begin_conditional_init(node,context))return false;
	if(!begin_init_branch(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!end_init_branch(node,context))return false;
	if(!visit(node->rest_block,context))return false;
	if(!end_conditional_init(node,context))return false;
    return true;
}
bool check_definite_init_elseif_else_onlyelse(elseif_else_onlyelse_t* node, sematic_context_t* context){
    if(!begin_init_branch(node,context))return false;
	if(!visit(node->else_block,context))return false;
	if(!end_init_branch(node,context))return false;
    return true;
}
bool check_definite_init_elseif_else_chain(elseif_else_chain_t* node, sematic_context_t* context){
    if(!visit(node->elseif_block,context))return false;
	if(!visit(node->rest_block,context))return false;
    return true;
}
bool check_definite_init_elseif_else_empty(elseif_else_empty_t* node, sematic_context_t* context){
    if(!record_implicit_init_branch(node,context))return false;
    return true;
}
bool check_definite_init_elseif_default(elseif_default_t* node, sematic_context_t* context){
    if(!begin_init_branch(node,context))return false;
	if(!visit(node->condition,context))return false;
	if(!save_init_condition_fallthrough(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!end_init_branch(node,context))return false;
    return true;
}
bool check_definite_init_while_default(while_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!begin_loop_init(node,context))return false;
	if(!visit(node->statements,context))return false;
	if(!end_loop_init(node,context))return false;
    return true;
}
bool definite_init_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_definite_init_function_default(static_cast<function_default_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFTYPE:
        return check_definite_init_definition_deftype(static_cast<definition_deftype_t*>(node),context);
        break;

    case NODE_DEFINITION_DEFNTYPE:
        return check_definite_init_definition_defntype(static_cast<definition_defntype_t*>(node),context);
        break;

    case NODE_DECLARATION_VARNTYPE:
        return check_definite_init_declaration_varntype(static_cast<declaration_varntype_t*>(node),context);
        break;

    case NODE_DECLARATION_VAR:
        return check_definite_init_declaration_var(static_cast<declaration_var_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_ASSIGN:
        return check_definite_init_assign_expr_assign(static_cast<assign_expr_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        return check_definite_init_assign_expr_plus_assign(static_cast<assign_expr_plus_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        return check_definite_init_assign_expr_minus_assign(static_cast<assign_expr_minus_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        return check_definite_init_assign_expr_mul_assign(static_cast<assign_expr_mul_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        return check_definite_init_assign_expr_div_assign(static_cast<assign_expr_div_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        return check_definite_init_assign_expr_mod_assign(static_cast<assign_expr_mod_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        return check_definite_init_assign_expr_bitand_assign(static_cast<assign_expr_bitand_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        return check_definite_init_assign_expr_bitor_assign(static_cast<assign_expr_bitor_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        return check_definite_init_assign_expr_shiftleft_assign(static_cast<assign_expr_shiftleft_assign_t*>(node),context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        return check_definite_init_assign_expr_shiftright_assign(static_cast<assign_expr_shiftright_assign_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_REF:
        return check_definite_init_single_op_factor_ref(static_cast<single_op_factor_ref_t*>(node),context);
        break;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        return check_definite_init_single_op_factor_deref(static_cast<single_op_factor_deref_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        return check_definite_init_lvalue_noproperty_deref(static_cast<lvalue_noproperty_deref_t*>(node),context);
        break;

    case NODE_FACTOR_ID:
        return check_definite_init_factor_id(static_cast<factor_id_t*>(node),context);
        break;

    case NODE_LVALUE_NOPROPERTY_ID:
        return check_definite_init_lvalue_noproperty_id(static_cast<lvalue_noproperty_id_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_AND_AND:
        return check_definite_init_logic_expr_and_and(static_cast<logic_expr_and_and_t*>(node),context);
        break;

    case NODE_LOGIC_EXPR_OR_OR:
        return check_definite_init_logic_expr_or_or(static_cast<logic_expr_or_or_t*>(node),context);
        break;

    case NODE_IF_DEFAULT:
        return check_definite_init_if_default(static_cast<if_default_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_ONLYELSE:
        return check_definite_init_elseif_else_onlyelse(static_cast<elseif_else_onlyelse_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_CHAIN:
        return check_definite_init_elseif_else_chain(static_cast<elseif_else_chain_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_EMPTY:
        return check_definite_init_elseif_else_empty(static_cast<elseif_else_empty_t*>(node),context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_definite_init_elseif_default(static_cast<elseif_default_t*>(node),context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_definite_init_while_default(static_cast<while_default_t*>(node),context);
        break;

    case NODE_FACTOR_NUM:
        
        return true;

    case NODE_FACTOR_CH:
        
        return true;

    case NODE_FACTOR_STR:
        
        return true;

    case NODE_GLUED_FACTOR_PAREN:
        if(!visit(static_cast<glued_factor_paren_t*>(node)->expr,context))return false;
        return true;

    case NODE_GLUED_FACTOR_DEF:
        if(!visit(static_cast<glued_factor_def_t*>(node)->left,context))return false;
        return true;

    case NODE_GLUED_FACTOR_VALUE:
        if(!visit(static_cast<glued_factor_value_t*>(node)->value,context))return false;
        return true;

    case NODE_GLUED_FACTOR_CALL:
        if(!visit(static_cast<glued_factor_call_t*>(node)->left,context))return false;
if(!visit(static_cast<glued_factor_call_t*>(node)->args,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        if(!visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NEG:
        if(!visit(static_cast<single_op_factor_neg_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NOT:
        if(!visit(static_cast<single_op_factor_not_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NONE:
        if(!visit(static_cast<single_op_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_POWER_FACTOR_POW:
        if(!visit(static_cast<power_factor_pow_t*>(node)->left,context))return false;
if(!visit(static_cast<power_factor_pow_t*>(node)->right,context))return false;
        return true;

    case NODE_POWER_FACTOR_NONE:
        if(!visit(static_cast<power_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_TERM_MUL:
        if(!visit(static_cast<term_mul_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mul_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_DIV:
        if(!visit(static_cast<term_div_t*>(node)->left,context))return false;
if(!visit(static_cast<term_div_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_MOD:
        if(!visit(static_cast<term_mod_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mod_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITAND:
        if(!visit(static_cast<term_bitand_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitand_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITOR:
        if(!visit(static_cast<term_bitor_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitor_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTLEFT:
        if(!visit(static_cast<term_shiftleft_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftleft_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTRIGHT:
        if(!visit(static_cast<term_shiftright_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftright_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_FACTOR:
        if(!visit(static_cast<term_factor_t*>(node)->expr,context))return false;
        return true;

    case NODE_EXPR_ADD:
        if(!visit(static_cast<expr_add_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_add_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_SUB:
        if(!visit(static_cast<expr_sub_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_sub_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_TERM:
        if(!visit(static_cast<expr_term_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_NONE:
        if(!visit(static_cast<logic_expr_and_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_NONE:
        if(!visit(static_cast<logic_expr_or_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_EQ:
        if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GT:
        if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LT:
        if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GE:
        if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LE:
        if(!visit(static_cast<logic_expr_eq_le_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_le_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NONE:
        if(!visit(static_cast<logic_expr_eq_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_LOGIC_EXPR:
        if(!visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_ULTIMATE_EXPR_DEF:
        if(!visit(static_cast<ultimate_expr_def_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_PARENED:
        if(!visit(static_cast<lvalue_noproperty_parened_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_PROP:
        if(!visit(static_cast<lvalue_prop_t*>(node)->left,context))return false;
        return true;

    case NODE_LVALUE_NOPROP:
        if(!visit(static_cast<lvalue_noprop_t*>(node)->expr,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_RAW_TYPE:
        
        return true;

    case NODE_COMPOSED_TYPE_PAREN:
        if(!visit(static_cast<composed_type_paren_t*>(node)->inner_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_PTR:
        if(!visit(static_cast<composed_type_ptr_t*>(node)->pointer_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        if(!visit(static_cast<composed_type_nsizedarr_t*>(node)->element_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        if(!visit(static_cast<composed_type_sizedarr_t*>(node)->element_type,context))return false;
if(!visit(static_cast<composed_type_sizedarr_t*>(node)->array_size,context))return false;
        return true;

    case NODE_ELSE_DEFAULT:
        if(!visit(static_cast<else_default_t*>(node)->statements,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_SINGMEM:
        if(!visit(static_cast<structmembers_singmem_t*>(node)->def_type,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_MULTIMEM:
        if(!visit(static_cast<structmembers_multimem_t*>(node)->def_type,context))return false;
if(!visit(static_cast<structmembers_multimem_t*>(node)->other_members,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_EMPTY:
        
        return true;

    case NODE_STRUCT_DEFAULT:
        if(!visit(static_cast<struct_default_t*>(node)->members,context))return false;
        return true;

    case NODE_DECLARATION_FN:
        if(!visit(static_cast<declaration_fn_t*>(node)->args,context))return false;
if(!visit(static_cast<declaration_fn_t*>(node)->return_type,context))return false;
        return true;

    case NODE_DECLARATION_STRUCT:
        if(!visit(static_cast<declaration_struct_t*>(node)->members,context))return false;
        return true;

    case NODE_STATEMENT_EXPR:
        if(!visit(static_cast<statement_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_STATEMENT_DEFINITION:
        if(!visit(static_cast<statement_definition_t*>(node)->def,context))return false;
        return true;

    case NODE_STATEMENT_IF:
        if(!visit(static_cast<statement_if_t*>(node)->if_stmt,context))return false;
        return true;

    case NODE_STATEMENT_WHILE:
        if(!visit(static_cast<statement_while_t*>(node)->while_stmt,context))return false;
        return true;

    case NODE_STATEMENT_DECLARATION:
        if(!visit(static_cast<statement_declaration_t*>(node)->decl_stmt,context))return false;
        return true;

    case NODE_STATEMENT_BREAK:
        
        return true;

    case NODE_STATEMENT_CONTINUE:
        
        return true;

    case NODE_STATEMENT_RETURN_EMPTY:
        
        return true;

    case NODE_STATEMENT_RETURN_STH:
        if(!visit(static_cast<statement_return_sth_t*>(node)->value,context))return false;
        return true;

    case NODE_STATEMENTS_STMT:
        if(!visit(static_cast<statements_stmt_t*>(node)->stmt,context))return false;
        return true;

    case NODE_STATEMENTS_MULTISTMT:
        if(!visit(static_cast<statements_multistmt_t*>(node)->stmt,context))return false;
if(!visit(static_cast<statements_multistmt_t*>(node)->other_stmts,context))return false;
        return true;

    case NODE_STATEMENTS_EMPTY:
        
        return true;

    case NODE_FUNC_RETURNTYPE_HASTYPE:
        if(!visit(static_cast<func_returntype_hastype_t*>(node)->return_type,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_VOID:
        
        return true;

    case NODE_ARGLIST_NONEMPTY_SINGARG:
        if(!visit(static_cast<arglist_nonempty_singarg_t*>(node)->arg_type,context))return false;
        return true;

    case NODE_ARGLIST_NONEMPTY_MULTIARG:
        if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->arg_type,context))return false;
if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->other_args,context))return false;
        return true;

    case NODE_ARGLIST_HASARG:
        if(!visit(static_cast<arglist_hasarg_t*>(node)->args,context))return false;
        return true;

    case NODE_ARGLIST_EMPTY:
        
        return true;

    case NODE_TOP_STATEMENT_FUNC_DEF:
        if(!visit(static_cast<top_statement_func_def_t*>(node)->func,context))return false;
        return true;

    case NODE_TOP_STATEMENT_DECL:
        if(!visit(static_cast<top_statement_decl_t*>(node)->decl,context))return false;
        return true;

    case NODE_TOP_STATEMENT_VAR_DEF:
        if(!visit(static_cast<top_statement_var_def_t*>(node)->def,context))return false;
        return true;

    case NODE_TOP_STATEMENT_STRUCTDEF:
        if(!visit(static_cast<top_statement_structdef_t*>(node)->structdef,context))return false;
        return true;
    }
    return false;
};
bool check_flow_function_default(function_default_t* node, sematic_context_t* context){
    if(!enter_function_scope(node,context))return false;
	if(!visit(node->stmts,context))return false;
	if(!require_all_paths_return(node,node->stmts,context))return false;
	if(!leave_scope(node,context))return false;
    return true;
}
bool check_flow_if_default(if_default_t* node, sematic_context_t* context){
    if(!visit(node->condition,context))return false;
	if(!visit(node->statements,context))return false;
	if(!visit(node->rest_block,context))return false;
	if(!check_control_flow(node,node->condition,node->statements,node->rest_block,context))return false;
    return true;
}
bool check_flow_while_default(while_default_t* node, sematic_context_t* context){
    if(!enter_loop_scope(node,context))return false;
	if(!visit(node->condition,context))return false;
	if(!visit(node->statements,context))return false;
	if(!check_control_flow(node,node->condition,node->statements,context))return false;
	if(!leave_loop_scope(node,context))return false;
    return true;
}
bool check_flow_statement_break(statement_break_t* node, sematic_context_t* context){
    if(!require_loop_context(node,context))return false;
	if(!set_terminating_flow(node,context))return false;
    return true;
}
bool check_flow_statement_continue(statement_continue_t* node, sematic_context_t* context){
    if(!require_loop_context(node,context))return false;
	if(!set_terminating_flow(node,context))return false;
    return true;
}
bool check_flow_statement_return_empty(statement_return_empty_t* node, sematic_context_t* context){
    if(!require_function_context(node,context))return false;
	if(!set_return_flow(node,context))return false;
    return true;
}
bool check_flow_statement_return_sth(statement_return_sth_t* node, sematic_context_t* context){
    if(!require_function_context(node,context))return false;
	if(!set_return_flow(node,context))return false;
    return true;
}
bool check_flow_statement_expr(statement_expr_t* node, sematic_context_t* context){
    if(!visit(node->expr,context))return false;
	if(!set_fallthrough_flow(node,context))return false;
    return true;
}
bool check_flow_statement_definition(statement_definition_t* node, sematic_context_t* context){
    if(!visit(node->def,context))return false;
	if(!set_fallthrough_flow(node,context))return false;
    return true;
}
bool check_flow_statement_declaration(statement_declaration_t* node, sematic_context_t* context){
    if(!visit(node->decl_stmt,context))return false;
	if(!set_fallthrough_flow(node,context))return false;
    return true;
}
bool check_flow_statement_if(statement_if_t* node, sematic_context_t* context){
    if(!visit(node->if_stmt,context))return false;
	if(!propagate_flow(node,node->if_stmt,context))return false;
    return true;
}
bool check_flow_statement_while(statement_while_t* node, sematic_context_t* context){
    if(!visit(node->while_stmt,context))return false;
	if(!propagate_flow(node,node->while_stmt,context))return false;
    return true;
}
bool check_flow_statements_stmt(statements_stmt_t* node, sematic_context_t* context){
    if(!visit(node->stmt,context))return false;
	if(!propagate_flow(node,node->stmt,context))return false;
    return true;
}
bool check_flow_statements_multistmt(statements_multistmt_t* node, sematic_context_t* context){
    if(!visit(node->stmt,context))return false;
	if(!visit(node->other_stmts,context))return false;
	if(!check_unreachable(node,node->stmt,node->other_stmts,context))return false;
	if(!combine_sequential_flow(node,node->stmt,node->other_stmts,context))return false;
    return true;
}
bool check_flow_statements_empty(statements_empty_t* node, sematic_context_t* context){
    if(!set_fallthrough_flow(node,context))return false;
    return true;
}
bool check_flow_else_default(else_default_t* node, sematic_context_t* context){
    if(!visit(node->statements,context))return false;
	if(!propagate_flow(node,node->statements,context))return false;
    return true;
}
bool check_flow_elseif_default(elseif_default_t* node, sematic_context_t* context){
    if(!visit(node->statements,context))return false;
	if(!propagate_flow(node,node->statements,context))return false;
    return true;
}
bool check_flow_elseif_else_onlyelse(elseif_else_onlyelse_t* node, sematic_context_t* context){
    if(!visit(node->else_block,context))return false;
	if(!propagate_flow(node,node->else_block,context))return false;
    return true;
}
bool check_flow_elseif_else_chain(elseif_else_chain_t* node, sematic_context_t* context){
    if(!visit(node->elseif_block,context))return false;
	if(!visit(node->rest_block,context))return false;
	if(!combine_branch_flow(node,node->elseif_block,node->rest_block,context))return false;
    return true;
}
bool check_flow_elseif_else_empty(elseif_else_empty_t* node, sematic_context_t* context){
    if(!set_fallthrough_flow(node,context))return false;
    return true;
}
bool flow_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_flow_function_default(static_cast<function_default_t*>(node),context);
        break;

    case NODE_IF_DEFAULT:
        return check_flow_if_default(static_cast<if_default_t*>(node),context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_flow_while_default(static_cast<while_default_t*>(node),context);
        break;

    case NODE_STATEMENT_BREAK:
        return check_flow_statement_break(static_cast<statement_break_t*>(node),context);
        break;

    case NODE_STATEMENT_CONTINUE:
        return check_flow_statement_continue(static_cast<statement_continue_t*>(node),context);
        break;

    case NODE_STATEMENT_RETURN_EMPTY:
        return check_flow_statement_return_empty(static_cast<statement_return_empty_t*>(node),context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_flow_statement_return_sth(static_cast<statement_return_sth_t*>(node),context);
        break;

    case NODE_STATEMENT_EXPR:
        return check_flow_statement_expr(static_cast<statement_expr_t*>(node),context);
        break;

    case NODE_STATEMENT_DEFINITION:
        return check_flow_statement_definition(static_cast<statement_definition_t*>(node),context);
        break;

    case NODE_STATEMENT_DECLARATION:
        return check_flow_statement_declaration(static_cast<statement_declaration_t*>(node),context);
        break;

    case NODE_STATEMENT_IF:
        return check_flow_statement_if(static_cast<statement_if_t*>(node),context);
        break;

    case NODE_STATEMENT_WHILE:
        return check_flow_statement_while(static_cast<statement_while_t*>(node),context);
        break;

    case NODE_STATEMENTS_STMT:
        return check_flow_statements_stmt(static_cast<statements_stmt_t*>(node),context);
        break;

    case NODE_STATEMENTS_MULTISTMT:
        return check_flow_statements_multistmt(static_cast<statements_multistmt_t*>(node),context);
        break;

    case NODE_STATEMENTS_EMPTY:
        return check_flow_statements_empty(static_cast<statements_empty_t*>(node),context);
        break;

    case NODE_ELSE_DEFAULT:
        return check_flow_else_default(static_cast<else_default_t*>(node),context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_flow_elseif_default(static_cast<elseif_default_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_ONLYELSE:
        return check_flow_elseif_else_onlyelse(static_cast<elseif_else_onlyelse_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_CHAIN:
        return check_flow_elseif_else_chain(static_cast<elseif_else_chain_t*>(node),context);
        break;

    case NODE_ELSEIF_ELSE_EMPTY:
        return check_flow_elseif_else_empty(static_cast<elseif_else_empty_t*>(node),context);
        break;

    case NODE_FACTOR_ID:
        
        return true;

    case NODE_FACTOR_NUM:
        
        return true;

    case NODE_FACTOR_CH:
        
        return true;

    case NODE_FACTOR_STR:
        
        return true;

    case NODE_GLUED_FACTOR_PAREN:
        if(!visit(static_cast<glued_factor_paren_t*>(node)->expr,context))return false;
        return true;

    case NODE_GLUED_FACTOR_DEF:
        if(!visit(static_cast<glued_factor_def_t*>(node)->left,context))return false;
        return true;

    case NODE_GLUED_FACTOR_VALUE:
        if(!visit(static_cast<glued_factor_value_t*>(node)->value,context))return false;
        return true;

    case NODE_GLUED_FACTOR_CALL:
        if(!visit(static_cast<glued_factor_call_t*>(node)->left,context))return false;
if(!visit(static_cast<glued_factor_call_t*>(node)->args,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        if(!visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NEG:
        if(!visit(static_cast<single_op_factor_neg_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_REF:
        if(!visit(static_cast<single_op_factor_ref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        if(!visit(static_cast<single_op_factor_deref_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NOT:
        if(!visit(static_cast<single_op_factor_not_t*>(node)->expr,context))return false;
        return true;

    case NODE_SINGLE_OP_FACTOR_NONE:
        if(!visit(static_cast<single_op_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_POWER_FACTOR_POW:
        if(!visit(static_cast<power_factor_pow_t*>(node)->left,context))return false;
if(!visit(static_cast<power_factor_pow_t*>(node)->right,context))return false;
        return true;

    case NODE_POWER_FACTOR_NONE:
        if(!visit(static_cast<power_factor_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_TERM_MUL:
        if(!visit(static_cast<term_mul_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mul_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_DIV:
        if(!visit(static_cast<term_div_t*>(node)->left,context))return false;
if(!visit(static_cast<term_div_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_MOD:
        if(!visit(static_cast<term_mod_t*>(node)->left,context))return false;
if(!visit(static_cast<term_mod_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITAND:
        if(!visit(static_cast<term_bitand_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitand_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_BITOR:
        if(!visit(static_cast<term_bitor_t*>(node)->left,context))return false;
if(!visit(static_cast<term_bitor_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTLEFT:
        if(!visit(static_cast<term_shiftleft_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftleft_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_SHIFTRIGHT:
        if(!visit(static_cast<term_shiftright_t*>(node)->left,context))return false;
if(!visit(static_cast<term_shiftright_t*>(node)->right,context))return false;
        return true;

    case NODE_TERM_FACTOR:
        if(!visit(static_cast<term_factor_t*>(node)->expr,context))return false;
        return true;

    case NODE_EXPR_ADD:
        if(!visit(static_cast<expr_add_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_add_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_SUB:
        if(!visit(static_cast<expr_sub_t*>(node)->left,context))return false;
if(!visit(static_cast<expr_sub_t*>(node)->right,context))return false;
        return true;

    case NODE_EXPR_TERM:
        if(!visit(static_cast<expr_term_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_AND:
        if(!visit(static_cast<logic_expr_and_and_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_and_and_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_AND_NONE:
        if(!visit(static_cast<logic_expr_and_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_OR:
        if(!visit(static_cast<logic_expr_or_or_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_or_or_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_OR_NONE:
        if(!visit(static_cast<logic_expr_or_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_EQ:
        if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_eq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_neq_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GT:
        if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_gt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LT:
        if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_lt_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_GE:
        if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_ge_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_LE:
        if(!visit(static_cast<logic_expr_eq_le_t*>(node)->left,context))return false;
if(!visit(static_cast<logic_expr_eq_le_t*>(node)->right,context))return false;
        return true;

    case NODE_LOGIC_EXPR_EQ_NONE:
        if(!visit(static_cast<logic_expr_eq_none_t*>(node)->expr,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_ASSIGN:
        if(!visit(static_cast<assign_expr_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_plus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_minus_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mul_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        if(!visit(static_cast<assign_expr_div_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_div_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_mod_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitand_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_bitor_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->left,context))return false;
if(!visit(static_cast<assign_expr_shiftright_assign_t*>(node)->right,context))return false;
        return true;

    case NODE_ASSIGN_EXPR_LOGIC_EXPR:
        if(!visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,context))return false;
        return true;

    case NODE_ULTIMATE_EXPR_DEF:
        if(!visit(static_cast<ultimate_expr_def_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_PARENED:
        if(!visit(static_cast<lvalue_noproperty_parened_t*>(node)->expr,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        if(!visit(static_cast<lvalue_noproperty_deref_t*>(node)->derefee,context))return false;
        return true;

    case NODE_LVALUE_NOPROPERTY_ID:
        
        return true;

    case NODE_LVALUE_PROP:
        if(!visit(static_cast<lvalue_prop_t*>(node)->left,context))return false;
        return true;

    case NODE_LVALUE_NOPROP:
        if(!visit(static_cast<lvalue_noprop_t*>(node)->expr,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_RAW_TYPE:
        
        return true;

    case NODE_COMPOSED_TYPE_PAREN:
        if(!visit(static_cast<composed_type_paren_t*>(node)->inner_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_PTR:
        if(!visit(static_cast<composed_type_ptr_t*>(node)->pointer_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        if(!visit(static_cast<composed_type_nsizedarr_t*>(node)->element_type,context))return false;
        return true;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        if(!visit(static_cast<composed_type_sizedarr_t*>(node)->element_type,context))return false;
if(!visit(static_cast<composed_type_sizedarr_t*>(node)->array_size,context))return false;
        return true;

    case NODE_DEFINITION_DEFTYPE:
        if(!visit(static_cast<definition_deftype_t*>(node)->def_type,context))return false;
if(!visit(static_cast<definition_deftype_t*>(node)->value,context))return false;
        return true;

    case NODE_DEFINITION_DEFNTYPE:
        if(!visit(static_cast<definition_defntype_t*>(node)->value,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_SINGMEM:
        if(!visit(static_cast<structmembers_singmem_t*>(node)->def_type,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_MULTIMEM:
        if(!visit(static_cast<structmembers_multimem_t*>(node)->def_type,context))return false;
if(!visit(static_cast<structmembers_multimem_t*>(node)->other_members,context))return false;
        return true;

    case NODE_STRUCTMEMBERS_EMPTY:
        
        return true;

    case NODE_STRUCT_DEFAULT:
        if(!visit(static_cast<struct_default_t*>(node)->members,context))return false;
        return true;

    case NODE_DECLARATION_VARNTYPE:
        
        return true;

    case NODE_DECLARATION_VAR:
        if(!visit(static_cast<declaration_var_t*>(node)->def_type,context))return false;
        return true;

    case NODE_DECLARATION_FN:
        if(!visit(static_cast<declaration_fn_t*>(node)->args,context))return false;
if(!visit(static_cast<declaration_fn_t*>(node)->return_type,context))return false;
        return true;

    case NODE_DECLARATION_STRUCT:
        if(!visit(static_cast<declaration_struct_t*>(node)->members,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_HASTYPE:
        if(!visit(static_cast<func_returntype_hastype_t*>(node)->return_type,context))return false;
        return true;

    case NODE_FUNC_RETURNTYPE_VOID:
        
        return true;

    case NODE_ARGLIST_NONEMPTY_SINGARG:
        if(!visit(static_cast<arglist_nonempty_singarg_t*>(node)->arg_type,context))return false;
        return true;

    case NODE_ARGLIST_NONEMPTY_MULTIARG:
        if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->arg_type,context))return false;
if(!visit(static_cast<arglist_nonempty_multiarg_t*>(node)->other_args,context))return false;
        return true;

    case NODE_ARGLIST_HASARG:
        if(!visit(static_cast<arglist_hasarg_t*>(node)->args,context))return false;
        return true;

    case NODE_ARGLIST_EMPTY:
        
        return true;

    case NODE_TOP_STATEMENT_FUNC_DEF:
        if(!visit(static_cast<top_statement_func_def_t*>(node)->func,context))return false;
        return true;

    case NODE_TOP_STATEMENT_DECL:
        if(!visit(static_cast<top_statement_decl_t*>(node)->decl,context))return false;
        return true;

    case NODE_TOP_STATEMENT_VAR_DEF:
        if(!visit(static_cast<top_statement_var_def_t*>(node)->def,context))return false;
        return true;

    case NODE_TOP_STATEMENT_STRUCTDEF:
        if(!visit(static_cast<top_statement_structdef_t*>(node)->structdef,context))return false;
        return true;
    }
    return false;
};
bool (*passes[])(ast_node_t*,sematic_context_t*)={
    predeclare_check,
	resolve_check,
	typecheck_check,
	definite_init_check,
	flow_check
};
constexpr std::size_t sematic_pass_count = sizeof(passes) / sizeof(passes[0]);

bool visit(ast_node_t* node,sematic_context_t* context){
    if (node == nullptr || context == nullptr || context->stage >= sematic_pass_count) {
        return false;
    }
    return passes[context->stage](node,context);
}

bool do_sematic(const std::vector<ast_node_t*>& ast, sematic_context_t& context){
    context.reset_analysis();
    for(std::size_t pass_index = 0; pass_index < sematic_pass_count; ++pass_index){
        context.begin_pass(pass_index);
        for(auto* node:ast){
            if(node == nullptr || !passes[pass_index](node,&context)){
                return false;
            }
        }
    }
    return true;
}

bool do_sematic(const std::vector<ast_node_t*>& ast){
    sematic_context_t context;
    return do_sematic(ast, context);
}
