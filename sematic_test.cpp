#include "lexer.h"
#include "parser.h"
#include <vector>
class sematic_context_t{
public:
    int stage;
};
void visit(ast_node_t* node,sematic_context_t* context);
bool predeclare_function(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context);
bool predeclare_struct(ast_node_t* node,token_t* name,sematic_context_t* context);
bool predeclare_function(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context);
bool predeclare_struct(ast_node_t* node,token_t* name,sematic_context_t* context);
bool enter_function_scope(ast_node_t* node,sematic_context_t* context);
bool declare_parameters(ast_node_t* node,arglist_t* args,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool enter_struct_scope(ast_node_t* node,sematic_context_t* context);
bool declare_members(ast_node_t* node,structmembers_t* members,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool declare_variable(ast_node_t* node,token_t* name,composed_type_t* def_type,sematic_context_t* context);
bool declare_inferred_variable(ast_node_t* node,token_t* name,ultimate_expr_t* value,sematic_context_t* context);
bool declare_variable(ast_node_t* node,token_t* name,sematic_context_t* context);
bool declare_variable(ast_node_t* node,token_t* name,composed_type_t* def_type,sematic_context_t* context);
bool resolve_function_signature(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context);
bool resolve_struct_signature(ast_node_t* node,token_t* name,structmembers_t* members,sematic_context_t* context);
bool resolve_symbol(ast_node_t* node,token_t* value,sematic_context_t* context);
bool resolve_member(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context);
bool resolve_arguments(ast_node_t* node,arglist_t* args,sematic_context_t* context);
bool resolve_member(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context);
bool resolve_symbol(ast_node_t* node,token_t* id,sematic_context_t* context);
bool enter_block_scope(ast_node_t* node,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool enter_loop_scope(ast_node_t* node,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool enter_block_scope(ast_node_t* node,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool enter_block_scope(ast_node_t* node,sematic_context_t* context);
bool leave_scope(ast_node_t* node,sematic_context_t* context);
bool check_assignable(ast_node_t* node,composed_type_t* def_type,ultimate_expr_t* value,sematic_context_t* context);
bool mark_initialized(ast_node_t* node,token_t* name,sematic_context_t* context);
bool infer_variable_type(ast_node_t* node,token_t* name,ultimate_expr_t* value,sematic_context_t* context);
bool mark_initialized(ast_node_t* node,token_t* name,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_assignable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_addable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_minusable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_mulable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_divable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_modable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_bitandable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_bitorable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_shiftleftable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_shiftrightable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context);
bool check_equalable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_nequalable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool require_boolean(ast_node_t* node,logic_expr_and_t* left,sematic_context_t* context);
bool require_boolean(ast_node_t* node,logic_expr_or_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool require_boolean(ast_node_t* node,expr_t* left,sematic_context_t* context);
bool require_boolean(ast_node_t* node,logic_expr_and_t* right,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool check_addable(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context);
bool check_minusable(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context);
bool check_mulable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_divable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_modable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_bitandable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_bitorable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_shiftleftable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool check_shiftrightable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context);
bool require_numeric(ast_node_t* node,single_op_factor_t* left,sematic_context_t* context);
bool require_numeric(ast_node_t* node,power_factor_t* right,sematic_context_t* context);
bool infer_binary_result_type(ast_node_t* node,single_op_factor_t* left,power_factor_t* right,sematic_context_t* context);
bool require_numeric(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool require_numeric(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool require_lvalue(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool infer_pointer_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool require_pointer(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool infer_pointee_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool require_boolean(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool set_boolean_type(ast_node_t* node,sematic_context_t* context);
bool require_pointer(ast_node_t* node,lvalue_t* derefee,sematic_context_t* context);
bool infer_pointee_type(ast_node_t* node,lvalue_t* derefee,sematic_context_t* context);
bool require_callable(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_argument_count(ast_node_t* node,lvalue_t* left,arglist_t* args,sematic_context_t* context);
bool check_argument_types(ast_node_t* node,lvalue_t* left,arglist_t* args,sematic_context_t* context);
bool infer_call_result_type(ast_node_t* node,lvalue_t* left,sematic_context_t* context);
bool check_member_access(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context);
bool propagate_member_type(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context);
bool check_member_access(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context);
bool propagate_member_type(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context);
bool propagate_symbol_type(ast_node_t* node,token_t* value,sematic_context_t* context);
bool set_number_type(ast_node_t* node,token_t* value,sematic_context_t* context);
bool set_char_type(ast_node_t* node,token_t* value,sematic_context_t* context);
bool set_string_type(ast_node_t* node,token_t* value,sematic_context_t* context);
bool propagate_type(ast_node_t* node,factor_t* value,sematic_context_t* context);
bool propagate_type(ast_node_t* node,ultimate_expr_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,term_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,glued_factor_t* expr,sematic_context_t* context);
bool propagate_type(ast_node_t* node,assign_expr_t* expr,sematic_context_t* context);
bool check_valid_type(ast_node_t* node,composed_type_t* inner_type,sematic_context_t* context);
bool check_valid_type(ast_node_t* node,composed_type_t* pointer_type,sematic_context_t* context);
bool check_valid_type(ast_node_t* node,composed_type_t* element_type,sematic_context_t* context);
bool check_valid_type(ast_node_t* node,composed_type_t* element_type,sematic_context_t* context);
bool require_integer(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context);
bool require_constant_expression(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context);
bool require_positive(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context);
bool require_function_context(ast_node_t* node,sematic_context_t* context);
bool check_empty_return_type(ast_node_t* node,sematic_context_t* context);
bool require_function_context(ast_node_t* node,sematic_context_t* context);
bool check_match_return_type(ast_node_t* node,ultimate_expr_t* value,sematic_context_t* context);
bool require_all_paths_return(ast_node_t* node,statements_t* stmts,sematic_context_t* context);
bool check_control_flow(ast_node_t* node,ultimate_expr_t* condition,statements_t* statements,elseif_else_t* rest_block,sematic_context_t* context);
bool check_control_flow(ast_node_t* node,ultimate_expr_t* condition,statements_t* statements,sematic_context_t* context);
bool leave_loop_scope(ast_node_t* node,sematic_context_t* context);
bool require_loop_context(ast_node_t* node,sematic_context_t* context);
bool require_loop_context(ast_node_t* node,sematic_context_t* context);
bool require_function_context(ast_node_t* node,sematic_context_t* context);
bool require_function_context(ast_node_t* node,sematic_context_t* context);
bool check_unreachable(ast_node_t* node,statement_t* stmt,statements_t* other_stmts,sematic_context_t* context);
bool check_predeclare_declaration_fn(declaration_fn_t *node,sematic_context_t *context){
    predeclare_function(node,node->name,node->args,node->return_type,context);
    
    
}
bool check_predeclare_declaration_struct(declaration_struct_t *node,sematic_context_t *context){
    predeclare_struct(node,node->name,context);
    
    
}
bool check_predeclare_function_default(function_default_t *node,sematic_context_t *context){
    predeclare_function(node,node->name,node->args,node->return_type,context);
    
    
}
bool check_predeclare_struct_default(struct_default_t *node,sematic_context_t *context){
    predeclare_struct(node,node->name,context);
    
    
}
bool predeclare_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_DECLARATION_FN:
        return check_predeclare_declaration_fn(node,context);
        break;

    case NODE_DECLARATION_STRUCT:
        return check_predeclare_declaration_struct(node,context);
        break;

    case NODE_FUNCTION_DEFAULT:
        return check_predeclare_function_default(node,context);
        break;

    case NODE_STRUCT_DEFAULT:
        return check_predeclare_struct_default(node,context);
        break;
    }
    return false;
};
bool check_resolve_function_default(function_default_t *node,sematic_context_t *context){
    enter_function_scope(node,,context);
	declare_parameters(node,node->args,context);
    visit(node->return_type,context);
	visit(node->stmts,context);
    leave_scope(node,,context);
}
bool check_resolve_struct_default(struct_default_t *node,sematic_context_t *context){
    enter_struct_scope(node,,context);
	declare_members(node,node->members,context);
    visit(node->members,context);
    leave_scope(node,,context);
}
bool check_resolve_definition_deftype(definition_deftype_t *node,sematic_context_t *context){
    
    visit(node->def_type,context);
	visit(node->value,context);
    declare_variable(node,node->name,node->def_type,context);
}
bool check_resolve_definition_defntype(definition_defntype_t *node,sematic_context_t *context){
    
    visit(node->value,context);
    declare_inferred_variable(node,node->name,node->value,context);
}
bool check_resolve_declaration_varntype(declaration_varntype_t *node,sematic_context_t *context){
    
    
    declare_variable(node,node->name,context);
}
bool check_resolve_declaration_var(declaration_var_t *node,sematic_context_t *context){
    
    visit(node->def_type,context);
    declare_variable(node,node->name,node->def_type,context);
}
bool check_resolve_declaration_fn(declaration_fn_t *node,sematic_context_t *context){
    
    visit(node->args,context);
	visit(node->return_type,context);
    resolve_function_signature(node,node->name,node->args,node->return_type,context);
}
bool check_resolve_declaration_struct(declaration_struct_t *node,sematic_context_t *context){
    
    visit(node->members,context);
    resolve_struct_signature(node,node->name,node->members,context);
}
bool check_resolve_factor_id(factor_id_t *node,sematic_context_t *context){
    
    
    resolve_symbol(node,node->value,context);
}
bool check_resolve_glued_factor_def(glued_factor_def_t *node,sematic_context_t *context){
    
    visit(node->left,context);
    resolve_member(node,node->left,node->right,context);
}
bool check_resolve_glued_factor_call(glued_factor_call_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->args,context);
    resolve_arguments(node,node->args,context);
}
bool check_resolve_lvalue_prop(lvalue_prop_t *node,sematic_context_t *context){
    
    visit(node->left,context);
    resolve_member(node,node->left,node->right,context);
}
bool check_resolve_lvalue_noproperty_id(lvalue_noproperty_id_t *node,sematic_context_t *context){
    
    
    resolve_symbol(node,node->id,context);
}
bool check_resolve_if_default(if_default_t *node,sematic_context_t *context){
    enter_block_scope(node,,context);
    visit(node->condition,context);
	visit(node->statements,context);
	visit(node->rest_block,context);
    leave_scope(node,,context);
}
bool check_resolve_while_default(while_default_t *node,sematic_context_t *context){
    enter_loop_scope(node,,context);
    visit(node->condition,context);
	visit(node->statements,context);
    leave_scope(node,,context);
}
bool check_resolve_else_default(else_default_t *node,sematic_context_t *context){
    enter_block_scope(node,,context);
    visit(node->statements,context);
    leave_scope(node,,context);
}
bool check_resolve_elseif_default(elseif_default_t *node,sematic_context_t *context){
    enter_block_scope(node,,context);
    visit(node->condition,context);
	visit(node->statements,context);
    leave_scope(node,,context);
}
bool check_resolve_statement_definition(statement_definition_t *node,sematic_context_t *context){
    
    visit(node->def,context);
    
}
bool check_resolve_statement_expr(statement_expr_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    
}
bool check_resolve_statement_declaration(statement_declaration_t *node,sematic_context_t *context){
    
    visit(node->decl_stmt,context);
    
}
bool check_resolve_statement_if(statement_if_t *node,sematic_context_t *context){
    
    visit(node->if_stmt,context);
    
}
bool check_resolve_statement_while(statement_while_t *node,sematic_context_t *context){
    
    visit(node->while_stmt,context);
    
}
bool check_resolve_statement_return_sth(statement_return_sth_t *node,sematic_context_t *context){
    
    visit(node->value,context);
    
}
bool resolve_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_resolve_function_default(node,context);
        break;

    case NODE_STRUCT_DEFAULT:
        return check_resolve_struct_default(node,context);
        break;

    case NODE_DEFINITION_DEFTYPE:
        return check_resolve_definition_deftype(node,context);
        break;

    case NODE_DEFINITION_DEFNTYPE:
        return check_resolve_definition_defntype(node,context);
        break;

    case NODE_DECLARATION_VARNTYPE:
        return check_resolve_declaration_varntype(node,context);
        break;

    case NODE_DECLARATION_VAR:
        return check_resolve_declaration_var(node,context);
        break;

    case NODE_DECLARATION_FN:
        return check_resolve_declaration_fn(node,context);
        break;

    case NODE_DECLARATION_STRUCT:
        return check_resolve_declaration_struct(node,context);
        break;

    case NODE_FACTOR_ID:
        return check_resolve_factor_id(node,context);
        break;

    case NODE_GLUED_FACTOR_DEF:
        return check_resolve_glued_factor_def(node,context);
        break;

    case NODE_GLUED_FACTOR_CALL:
        return check_resolve_glued_factor_call(node,context);
        break;

    case NODE_LVALUE_PROP:
        return check_resolve_lvalue_prop(node,context);
        break;

    case NODE_LVALUE_NOPROPERTY_ID:
        return check_resolve_lvalue_noproperty_id(node,context);
        break;

    case NODE_IF_DEFAULT:
        return check_resolve_if_default(node,context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_resolve_while_default(node,context);
        break;

    case NODE_ELSE_DEFAULT:
        return check_resolve_else_default(node,context);
        break;

    case NODE_ELSEIF_DEFAULT:
        return check_resolve_elseif_default(node,context);
        break;

    case NODE_STATEMENT_DEFINITION:
        return check_resolve_statement_definition(node,context);
        break;

    case NODE_STATEMENT_EXPR:
        return check_resolve_statement_expr(node,context);
        break;

    case NODE_STATEMENT_DECLARATION:
        return check_resolve_statement_declaration(node,context);
        break;

    case NODE_STATEMENT_IF:
        return check_resolve_statement_if(node,context);
        break;

    case NODE_STATEMENT_WHILE:
        return check_resolve_statement_while(node,context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_resolve_statement_return_sth(node,context);
        break;
    }
    return false;
};
bool check_typecheck_definition_deftype(definition_deftype_t *node,sematic_context_t *context){
    
    visit(node->def_type,context);
	visit(node->value,context);
    check_assignable(node,node->def_type,node->value,context);
	mark_initialized(node,node->name,context);
}
bool check_typecheck_definition_defntype(definition_defntype_t *node,sematic_context_t *context){
    
    visit(node->value,context);
    infer_variable_type(node,node->name,node->value,context);
	mark_initialized(node,node->name,context);
}
bool check_typecheck_assign_expr_assign(assign_expr_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_assignable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_plus_assign(assign_expr_plus_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_addable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_minus_assign(assign_expr_minus_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_minusable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_mul_assign(assign_expr_mul_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_mulable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_div_assign(assign_expr_div_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_divable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_mod_assign(assign_expr_mod_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_modable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_bitand_assign(assign_expr_bitand_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_bitandable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_bitor_assign(assign_expr_bitor_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_bitorable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_shiftleft_assign(assign_expr_shiftleft_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_shiftleftable(node,node->left,node->right,context);
}
bool check_typecheck_assign_expr_shiftright_assign(assign_expr_shiftright_assign_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_modifiable_lvalue(node,node->left,context);
	check_shiftrightable(node,node->left,node->right,context);
}
bool check_typecheck_logic_expr_eq_eq(logic_expr_eq_eq_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_equalable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_eq_neq(logic_expr_eq_neq_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_nequalable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_eq_gt(logic_expr_eq_gt_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_comparable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_eq_lt(logic_expr_eq_lt_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_comparable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_eq_ge(logic_expr_eq_ge_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_comparable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_eq_le(logic_expr_eq_le_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_comparable(node,node->left,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_or_or(logic_expr_or_or_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_boolean(node,node->left,context);
	require_boolean(node,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_logic_expr_and_and(logic_expr_and_and_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_boolean(node,node->left,context);
	require_boolean(node,node->right,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_expr_add(expr_add_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_addable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_expr_sub(expr_sub_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_minusable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_mul(term_mul_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_mulable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_div(term_div_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_divable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_mod(term_mod_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_modable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_bitand(term_bitand_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_bitandable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_bitor(term_bitor_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_bitorable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_shiftleft(term_shiftleft_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_shiftleftable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_term_shiftright(term_shiftright_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    check_shiftrightable(node,node->left,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_power_factor_pow(power_factor_pow_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->right,context);
    require_numeric(node,node->left,context);
	require_numeric(node,node->right,context);
	infer_binary_result_type(node,node->left,node->right,context);
}
bool check_typecheck_single_op_factor_bitnot(single_op_factor_bitnot_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    require_numeric(node,node->expr,context);
	propagate_type(node,node->expr,context);
}
bool check_typecheck_single_op_factor_neg(single_op_factor_neg_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    require_numeric(node,node->expr,context);
	propagate_type(node,node->expr,context);
}
bool check_typecheck_single_op_factor_ref(single_op_factor_ref_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    require_lvalue(node,node->expr,context);
	infer_pointer_type(node,node->expr,context);
}
bool check_typecheck_single_op_factor_deref(single_op_factor_deref_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    require_pointer(node,node->expr,context);
	infer_pointee_type(node,node->expr,context);
}
bool check_typecheck_single_op_factor_not(single_op_factor_not_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    require_boolean(node,node->expr,context);
	set_boolean_type(node,,context);
}
bool check_typecheck_lvalue_noproperty_deref(lvalue_noproperty_deref_t *node,sematic_context_t *context){
    
    visit(node->derefee,context);
    require_pointer(node,node->derefee,context);
	infer_pointee_type(node,node->derefee,context);
}
bool check_typecheck_glued_factor_call(glued_factor_call_t *node,sematic_context_t *context){
    
    visit(node->left,context);
	visit(node->args,context);
    require_callable(node,node->left,context);
	check_argument_count(node,node->left,node->args,context);
	check_argument_types(node,node->left,node->args,context);
	infer_call_result_type(node,node->left,context);
}
bool check_typecheck_glued_factor_def(glued_factor_def_t *node,sematic_context_t *context){
    
    visit(node->left,context);
    check_member_access(node,node->left,node->right,context);
	propagate_member_type(node,node->left,node->right,context);
}
bool check_typecheck_lvalue_prop(lvalue_prop_t *node,sematic_context_t *context){
    
    visit(node->left,context);
    check_member_access(node,node->left,node->right,context);
	propagate_member_type(node,node->left,node->right,context);
}
bool check_typecheck_factor_id(factor_id_t *node,sematic_context_t *context){
    
    
    propagate_symbol_type(node,node->value,context);
}
bool check_typecheck_factor_num(factor_num_t *node,sematic_context_t *context){
    
    
    set_number_type(node,node->value,context);
}
bool check_typecheck_factor_ch(factor_ch_t *node,sematic_context_t *context){
    
    
    set_char_type(node,node->value,context);
}
bool check_typecheck_factor_str(factor_str_t *node,sematic_context_t *context){
    
    
    set_string_type(node,node->value,context);
}
bool check_typecheck_glued_factor_value(glued_factor_value_t *node,sematic_context_t *context){
    
    visit(node->value,context);
    propagate_type(node,node->value,context);
}
bool check_typecheck_glued_factor_paren(glued_factor_paren_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    propagate_type(node,node->expr,context);
}
bool check_typecheck_expr_term(expr_term_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    propagate_type(node,node->expr,context);
}
bool check_typecheck_power_factor_none(power_factor_none_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    propagate_type(node,node->expr,context);
}
bool check_typecheck_single_op_factor_none(single_op_factor_none_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    propagate_type(node,node->expr,context);
}
bool check_typecheck_ultimate_expr_def(ultimate_expr_def_t *node,sematic_context_t *context){
    
    visit(node->expr,context);
    propagate_type(node,node->expr,context);
}
bool check_typecheck_composed_type_paren(composed_type_paren_t *node,sematic_context_t *context){
    
    visit(node->inner_type,context);
    check_valid_type(node,node->inner_type,context);
}
bool check_typecheck_composed_type_ptr(composed_type_ptr_t *node,sematic_context_t *context){
    
    visit(node->pointer_type,context);
    check_valid_type(node,node->pointer_type,context);
}
bool check_typecheck_composed_type_nsizedarr(composed_type_nsizedarr_t *node,sematic_context_t *context){
    
    visit(node->element_type,context);
    check_valid_type(node,node->element_type,context);
}
bool check_typecheck_composed_type_sizedarr(composed_type_sizedarr_t *node,sematic_context_t *context){
    
    visit(node->element_type,context);
	visit(node->array_size,context);
    check_valid_type(node,node->element_type,context);
	require_integer(node,node->array_size,context);
	require_constant_expression(node,node->array_size,context);
	require_positive(node,node->array_size,context);
}
bool check_typecheck_statement_return_empty(statement_return_empty_t *node,sematic_context_t *context){
    
    
    require_function_context(node,,context);
	check_empty_return_type(node,,context);
}
bool check_typecheck_statement_return_sth(statement_return_sth_t *node,sematic_context_t *context){
    
    visit(node->value,context);
    require_function_context(node,,context);
	check_match_return_type(node,node->value,context);
}
bool typecheck_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_DEFINITION_DEFTYPE:
        return check_typecheck_definition_deftype(node,context);
        break;

    case NODE_DEFINITION_DEFNTYPE:
        return check_typecheck_definition_defntype(node,context);
        break;

    case NODE_ASSIGN_EXPR_ASSIGN:
        return check_typecheck_assign_expr_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
        return check_typecheck_assign_expr_plus_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
        return check_typecheck_assign_expr_minus_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_MUL_ASSIGN:
        return check_typecheck_assign_expr_mul_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_DIV_ASSIGN:
        return check_typecheck_assign_expr_div_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_MOD_ASSIGN:
        return check_typecheck_assign_expr_mod_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
        return check_typecheck_assign_expr_bitand_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
        return check_typecheck_assign_expr_bitor_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
        return check_typecheck_assign_expr_shiftleft_assign(node,context);
        break;

    case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
        return check_typecheck_assign_expr_shiftright_assign(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_EQ:
        return check_typecheck_logic_expr_eq_eq(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_NEQ:
        return check_typecheck_logic_expr_eq_neq(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_GT:
        return check_typecheck_logic_expr_eq_gt(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_LT:
        return check_typecheck_logic_expr_eq_lt(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_GE:
        return check_typecheck_logic_expr_eq_ge(node,context);
        break;

    case NODE_LOGIC_EXPR_EQ_LE:
        return check_typecheck_logic_expr_eq_le(node,context);
        break;

    case NODE_LOGIC_EXPR_OR_OR:
        return check_typecheck_logic_expr_or_or(node,context);
        break;

    case NODE_LOGIC_EXPR_AND_AND:
        return check_typecheck_logic_expr_and_and(node,context);
        break;

    case NODE_EXPR_ADD:
        return check_typecheck_expr_add(node,context);
        break;

    case NODE_EXPR_SUB:
        return check_typecheck_expr_sub(node,context);
        break;

    case NODE_TERM_MUL:
        return check_typecheck_term_mul(node,context);
        break;

    case NODE_TERM_DIV:
        return check_typecheck_term_div(node,context);
        break;

    case NODE_TERM_MOD:
        return check_typecheck_term_mod(node,context);
        break;

    case NODE_TERM_BITAND:
        return check_typecheck_term_bitand(node,context);
        break;

    case NODE_TERM_BITOR:
        return check_typecheck_term_bitor(node,context);
        break;

    case NODE_TERM_SHIFTLEFT:
        return check_typecheck_term_shiftleft(node,context);
        break;

    case NODE_TERM_SHIFTRIGHT:
        return check_typecheck_term_shiftright(node,context);
        break;

    case NODE_POWER_FACTOR_POW:
        return check_typecheck_power_factor_pow(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_BITNOT:
        return check_typecheck_single_op_factor_bitnot(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_NEG:
        return check_typecheck_single_op_factor_neg(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_REF:
        return check_typecheck_single_op_factor_ref(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_DEREF:
        return check_typecheck_single_op_factor_deref(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_NOT:
        return check_typecheck_single_op_factor_not(node,context);
        break;

    case NODE_LVALUE_NOPROPERTY_DEREF:
        return check_typecheck_lvalue_noproperty_deref(node,context);
        break;

    case NODE_GLUED_FACTOR_CALL:
        return check_typecheck_glued_factor_call(node,context);
        break;

    case NODE_GLUED_FACTOR_DEF:
        return check_typecheck_glued_factor_def(node,context);
        break;

    case NODE_LVALUE_PROP:
        return check_typecheck_lvalue_prop(node,context);
        break;

    case NODE_FACTOR_ID:
        return check_typecheck_factor_id(node,context);
        break;

    case NODE_FACTOR_NUM:
        return check_typecheck_factor_num(node,context);
        break;

    case NODE_FACTOR_CH:
        return check_typecheck_factor_ch(node,context);
        break;

    case NODE_FACTOR_STR:
        return check_typecheck_factor_str(node,context);
        break;

    case NODE_GLUED_FACTOR_VALUE:
        return check_typecheck_glued_factor_value(node,context);
        break;

    case NODE_GLUED_FACTOR_PAREN:
        return check_typecheck_glued_factor_paren(node,context);
        break;

    case NODE_EXPR_TERM:
        return check_typecheck_expr_term(node,context);
        break;

    case NODE_POWER_FACTOR_NONE:
        return check_typecheck_power_factor_none(node,context);
        break;

    case NODE_SINGLE_OP_FACTOR_NONE:
        return check_typecheck_single_op_factor_none(node,context);
        break;

    case NODE_ULTIMATE_EXPR_DEF:
        return check_typecheck_ultimate_expr_def(node,context);
        break;

    case NODE_COMPOSED_TYPE_PAREN:
        return check_typecheck_composed_type_paren(node,context);
        break;

    case NODE_COMPOSED_TYPE_PTR:
        return check_typecheck_composed_type_ptr(node,context);
        break;

    case NODE_COMPOSED_TYPE_NSIZEDARR:
        return check_typecheck_composed_type_nsizedarr(node,context);
        break;

    case NODE_COMPOSED_TYPE_SIZEDARR:
        return check_typecheck_composed_type_sizedarr(node,context);
        break;

    case NODE_STATEMENT_RETURN_EMPTY:
        return check_typecheck_statement_return_empty(node,context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_typecheck_statement_return_sth(node,context);
        break;
    }
    return false;
};
bool check_flow_function_default(function_default_t *node,sematic_context_t *context){
    
    visit(node->stmts,context);
    require_all_paths_return(node,node->stmts,context);
}
bool check_flow_if_default(if_default_t *node,sematic_context_t *context){
    
    visit(node->condition,context);
	visit(node->statements,context);
	visit(node->rest_block,context);
    check_control_flow(node,node->condition,node->statements,node->rest_block,context);
}
bool check_flow_while_default(while_default_t *node,sematic_context_t *context){
    
    visit(node->condition,context);
	visit(node->statements,context);
    check_control_flow(node,node->condition,node->statements,context);
	leave_loop_scope(node,,context);
}
bool check_flow_statement_break(statement_break_t *node,sematic_context_t *context){
    
    
    require_loop_context(node,,context);
}
bool check_flow_statement_continue(statement_continue_t *node,sematic_context_t *context){
    
    
    require_loop_context(node,,context);
}
bool check_flow_statement_return_empty(statement_return_empty_t *node,sematic_context_t *context){
    
    
    require_function_context(node,,context);
}
bool check_flow_statement_return_sth(statement_return_sth_t *node,sematic_context_t *context){
    
    
    require_function_context(node,,context);
}
bool check_flow_statements_multistmt(statements_multistmt_t *node,sematic_context_t *context){
    
    visit(node->stmt,context);
	visit(node->other_stmts,context);
    check_unreachable(node,node->stmt,node->other_stmts,context);
}
bool flow_check(ast_node_t* node,sematic_context_t* context){
    switch(node->get_kind()){
    
    case NODE_FUNCTION_DEFAULT:
        return check_flow_function_default(node,context);
        break;

    case NODE_IF_DEFAULT:
        return check_flow_if_default(node,context);
        break;

    case NODE_WHILE_DEFAULT:
        return check_flow_while_default(node,context);
        break;

    case NODE_STATEMENT_BREAK:
        return check_flow_statement_break(node,context);
        break;

    case NODE_STATEMENT_CONTINUE:
        return check_flow_statement_continue(node,context);
        break;

    case NODE_STATEMENT_RETURN_EMPTY:
        return check_flow_statement_return_empty(node,context);
        break;

    case NODE_STATEMENT_RETURN_STH:
        return check_flow_statement_return_sth(node,context);
        break;

    case NODE_STATEMENTS_MULTISTMT:
        return check_flow_statements_multistmt(node,context);
        break;
    }
    return false;
};bool predeclare_function(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context){
	
}
bool predeclare_struct(ast_node_t* node,token_t* name,sematic_context_t* context){
	
}
bool predeclare_function(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context){
	
}
bool predeclare_struct(ast_node_t* node,token_t* name,sematic_context_t* context){
	
}
bool enter_function_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool declare_parameters(ast_node_t* node,arglist_t* args,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool enter_struct_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool declare_members(ast_node_t* node,structmembers_t* members,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool declare_variable(ast_node_t* node,token_t* name,composed_type_t* def_type,sematic_context_t* context){
	
}
bool declare_inferred_variable(ast_node_t* node,token_t* name,ultimate_expr_t* value,sematic_context_t* context){
	
}
bool declare_variable(ast_node_t* node,token_t* name,sematic_context_t* context){
	
}
bool declare_variable(ast_node_t* node,token_t* name,composed_type_t* def_type,sematic_context_t* context){
	
}
bool resolve_function_signature(ast_node_t* node,token_t* name,arglist_t* args,func_returntype_t* return_type,sematic_context_t* context){
	
}
bool resolve_struct_signature(ast_node_t* node,token_t* name,structmembers_t* members,sematic_context_t* context){
	
}
bool resolve_symbol(ast_node_t* node,token_t* value,sematic_context_t* context){
	
}
bool resolve_member(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context){
	
}
bool resolve_arguments(ast_node_t* node,arglist_t* args,sematic_context_t* context){
	
}
bool resolve_member(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context){
	
}
bool resolve_symbol(ast_node_t* node,token_t* id,sematic_context_t* context){
	
}
bool enter_block_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool enter_loop_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool enter_block_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool enter_block_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool leave_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool check_assignable(ast_node_t* node,composed_type_t* def_type,ultimate_expr_t* value,sematic_context_t* context){
	
}
bool mark_initialized(ast_node_t* node,token_t* name,sematic_context_t* context){
	
}
bool infer_variable_type(ast_node_t* node,token_t* name,ultimate_expr_t* value,sematic_context_t* context){
	
}
bool mark_initialized(ast_node_t* node,token_t* name,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_assignable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_addable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_minusable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_mulable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_divable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_modable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_bitandable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_bitorable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_shiftleftable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool require_modifiable_lvalue(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_shiftrightable(ast_node_t* node,lvalue_t* left,assign_expr_t* right,sematic_context_t* context){
	
}
bool check_equalable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_nequalable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_comparable(ast_node_t* node,logic_expr_or_t* left,logic_expr_eq_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool require_boolean(ast_node_t* node,logic_expr_and_t* left,sematic_context_t* context){
	
}
bool require_boolean(ast_node_t* node,logic_expr_or_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool require_boolean(ast_node_t* node,expr_t* left,sematic_context_t* context){
	
}
bool require_boolean(ast_node_t* node,logic_expr_and_t* right,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool check_addable(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context){
	
}
bool check_minusable(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,term_t* left,expr_t* right,sematic_context_t* context){
	
}
bool check_mulable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_divable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_modable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_bitandable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_bitorable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_shiftleftable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool check_shiftrightable(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,power_factor_t* left,term_t* right,sematic_context_t* context){
	
}
bool require_numeric(ast_node_t* node,single_op_factor_t* left,sematic_context_t* context){
	
}
bool require_numeric(ast_node_t* node,power_factor_t* right,sematic_context_t* context){
	
}
bool infer_binary_result_type(ast_node_t* node,single_op_factor_t* left,power_factor_t* right,sematic_context_t* context){
	
}
bool require_numeric(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool require_numeric(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool require_lvalue(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool infer_pointer_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool require_pointer(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool infer_pointee_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool require_boolean(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool set_boolean_type(ast_node_t* node,sematic_context_t* context){
	
}
bool require_pointer(ast_node_t* node,lvalue_t* derefee,sematic_context_t* context){
	
}
bool infer_pointee_type(ast_node_t* node,lvalue_t* derefee,sematic_context_t* context){
	
}
bool require_callable(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_argument_count(ast_node_t* node,lvalue_t* left,arglist_t* args,sematic_context_t* context){
	
}
bool check_argument_types(ast_node_t* node,lvalue_t* left,arglist_t* args,sematic_context_t* context){
	
}
bool infer_call_result_type(ast_node_t* node,lvalue_t* left,sematic_context_t* context){
	
}
bool check_member_access(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context){
	
}
bool propagate_member_type(ast_node_t* node,lvalue_t* left,token_t* right,sematic_context_t* context){
	
}
bool check_member_access(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context){
	
}
bool propagate_member_type(ast_node_t* node,lvalue_noproperty_t* left,token_t* right,sematic_context_t* context){
	
}
bool propagate_symbol_type(ast_node_t* node,token_t* value,sematic_context_t* context){
	
}
bool set_number_type(ast_node_t* node,token_t* value,sematic_context_t* context){
	
}
bool set_char_type(ast_node_t* node,token_t* value,sematic_context_t* context){
	
}
bool set_string_type(ast_node_t* node,token_t* value,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,factor_t* value,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,ultimate_expr_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,term_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,single_op_factor_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,glued_factor_t* expr,sematic_context_t* context){
	
}
bool propagate_type(ast_node_t* node,assign_expr_t* expr,sematic_context_t* context){
	
}
bool check_valid_type(ast_node_t* node,composed_type_t* inner_type,sematic_context_t* context){
	
}
bool check_valid_type(ast_node_t* node,composed_type_t* pointer_type,sematic_context_t* context){
	
}
bool check_valid_type(ast_node_t* node,composed_type_t* element_type,sematic_context_t* context){
	
}
bool check_valid_type(ast_node_t* node,composed_type_t* element_type,sematic_context_t* context){
	
}
bool require_integer(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context){
	
}
bool require_constant_expression(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context){
	
}
bool require_positive(ast_node_t* node,ultimate_expr_t* array_size,sematic_context_t* context){
	
}
bool require_function_context(ast_node_t* node,sematic_context_t* context){
	
}
bool check_empty_return_type(ast_node_t* node,sematic_context_t* context){
	
}
bool require_function_context(ast_node_t* node,sematic_context_t* context){
	
}
bool check_match_return_type(ast_node_t* node,ultimate_expr_t* value,sematic_context_t* context){
	
}
bool require_all_paths_return(ast_node_t* node,statements_t* stmts,sematic_context_t* context){
	
}
bool check_control_flow(ast_node_t* node,ultimate_expr_t* condition,statements_t* statements,elseif_else_t* rest_block,sematic_context_t* context){
	
}
bool check_control_flow(ast_node_t* node,ultimate_expr_t* condition,statements_t* statements,sematic_context_t* context){
	
}
bool leave_loop_scope(ast_node_t* node,sematic_context_t* context){
	
}
bool require_loop_context(ast_node_t* node,sematic_context_t* context){
	
}
bool require_loop_context(ast_node_t* node,sematic_context_t* context){
	
}
bool require_function_context(ast_node_t* node,sematic_context_t* context){
	
}
bool require_function_context(ast_node_t* node,sematic_context_t* context){
	
}
bool check_unreachable(ast_node_t* node,statement_t* stmt,statements_t* other_stmts,sematic_context_t* context){
	
}
bool (*passes)(ast_node_t*,sematic_context_t*)[]={
    predeclare_check,
	resolve_check,
	typecheck_check,
	flow_check
};
void visit(ast_node_t* node,sematic_context_t* context){
    passes[context->stage](node,context);
}
bool do_sematic(std::vector<ast_node_t*> ast){
    sematic_context_t context;
    context.stage = 0;
    for(auto pass:passes){
        for(auto node:ast){
            if(!pass(node,&context)){
                return false;
            }
        }
        context.stage++;
    }
    return true;
}