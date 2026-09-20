#include "parser.h"
#include "sematic.h"
bool predeclare_function(ast_node_t*,token_t*,parameter_list_t*,func_returntype_t*,sematic_context_t*){
	return true;
}
bool predeclare_struct(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool create_function_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool predeclare_parameters(ast_node_t*,parameter_list_t*,sematic_context_t*){
	return true;
}
bool leave_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool create_struct_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool predeclare_members(ast_node_t*,structmembers_t*,sematic_context_t*){
	return true;
}
bool create_block_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool create_loop_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool enter_function_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool declare_parameters(ast_node_t*,parameter_list_t*,sematic_context_t*){
	return true;
}
bool enter_struct_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool declare_members(ast_node_t*,structmembers_t*,sematic_context_t*){
	return true;
}
bool declare_variable(ast_node_t*,token_t*,composed_type_t*,sematic_context_t*){
	return true;
}
bool declare_inferred_variable(ast_node_t*,token_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool declare_variable(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool resolve_function_signature(ast_node_t*,token_t*,parameter_list_t*,func_returntype_t*,sematic_context_t*){
	return true;
}
bool resolve_struct_signature(ast_node_t*,token_t*,structmembers_t*,sematic_context_t*){
	return true;
}
bool resolve_arguments(ast_node_t*,argument_list_t*,sematic_context_t*){
	return true;
}
bool resolve_member(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*){
	return true;
}
bool resolve_symbol(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool enter_block_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool enter_loop_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool enter_function_context(ast_node_t*,token_t*,func_returntype_t*,sematic_context_t*){
	return true;
}
bool check_function_type(ast_node_t*,parameter_list_t*,func_returntype_t*,sematic_context_t*){
	return true;
}
bool leave_function_context(ast_node_t*,sematic_context_t*){
	return true;
}
bool enter_struct_context(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool leave_struct_context(ast_node_t*,sematic_context_t*){
	return true;
}
bool require_valid_variable_type(ast_node_t*,composed_type_t*,sematic_context_t*){
	return true;
}
bool check_assignable(ast_node_t*,composed_type_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool infer_variable_type(ast_node_t*,token_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool require_valid_parameter_type(ast_node_t*,composed_type_t*,sematic_context_t*){
	return true;
}
bool require_valid_member_type(ast_node_t*,composed_type_t*,sematic_context_t*){
	return true;
}
bool require_modifiable_lvalue(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool check_assignable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool check_addable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_minusable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_mulable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_divable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_modable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_bitandable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_bitorable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_shiftleftable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_shiftrightable(ast_node_t*,lvalue_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,logic_expr_or_t*,sematic_context_t*){
	return true;
}
bool check_equalable(ast_node_t*,logic_expr_eq_t*,bitor_expr_t*,sematic_context_t*){
	return true;
}
bool set_boolean_type(ast_node_t*,sematic_context_t*){
	return true;
}
bool check_nequalable(ast_node_t*,logic_expr_eq_t*,bitor_expr_t*,sematic_context_t*){
	return true;
}
bool check_comparable(ast_node_t*,logic_expr_eq_t*,bitor_expr_t*,sematic_context_t*){
	return true;
}
bool require_boolean(ast_node_t*,logic_expr_or_t*,sematic_context_t*){
	return true;
}
bool require_boolean(ast_node_t*,logic_expr_and_t*,sematic_context_t*){
	return true;
}
bool require_boolean(ast_node_t*,logic_expr_eq_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,logic_expr_eq_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,logic_expr_and_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,bitor_expr_t*,sematic_context_t*){
	return true;
}
bool check_addable(ast_node_t*,expr_t*,term_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,expr_t*,term_t*,sematic_context_t*){
	return true;
}
bool check_minusable(ast_node_t*,expr_t*,term_t*,sematic_context_t*){
	return true;
}
bool check_mulable(ast_node_t*,term_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,term_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool check_divable(ast_node_t*,term_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool check_modable(ast_node_t*,term_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool check_bitandable(ast_node_t*,bitand_expr_t*,shift_expr_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,bitand_expr_t*,shift_expr_t*,sematic_context_t*){
	return true;
}
bool check_bitorable(ast_node_t*,bitor_expr_t*,bitand_expr_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,bitor_expr_t*,bitand_expr_t*,sematic_context_t*){
	return true;
}
bool check_shiftleftable(ast_node_t*,shift_expr_t*,expr_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,shift_expr_t*,expr_t*,sematic_context_t*){
	return true;
}
bool check_shiftrightable(ast_node_t*,shift_expr_t*,expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool require_numeric(ast_node_t*,power_factor_t*,sematic_context_t*){
	return true;
}
bool require_numeric(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool infer_binary_result_type(ast_node_t*,power_factor_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool require_lvalue(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool infer_pointer_type(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool require_pointer(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool infer_pointee_type(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool require_boolean(ast_node_t*,single_op_factor_t*,sematic_context_t*){
	return true;
}
bool require_pointer(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool infer_pointee_type(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool require_lvalue(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_symbol_type(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,lvalue_noproperty_t*,sematic_context_t*){
	return true;
}
bool require_callable(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool check_argument_count(ast_node_t*,lvalue_t*,argument_list_t*,sematic_context_t*){
	return true;
}
bool check_argument_types(ast_node_t*,lvalue_t*,argument_list_t*,sematic_context_t*){
	return true;
}
bool infer_call_result_type(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool check_member_access(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*){
	return true;
}
bool propagate_member_type(ast_node_t*,lvalue_t*,token_t*,sematic_context_t*){
	return true;
}
bool set_number_type(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool set_char_type(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool set_string_type(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,factor_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,term_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,shift_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,bitand_expr_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,glued_factor_t*,sematic_context_t*){
	return true;
}
bool propagate_type(ast_node_t*,assign_expr_t*,sematic_context_t*){
	return true;
}
bool check_valid_type(ast_node_t*,composed_type_t*,sematic_context_t*){
	return true;
}
bool resolve_type_name(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool set_named_type(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool require_integer(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool require_constant_expression(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool require_positive(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool require_function_context(ast_node_t*,sematic_context_t*){
	return true;
}
bool check_empty_return_type(ast_node_t*,sematic_context_t*){
	return true;
}
bool check_match_return_type(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool require_boolean(ast_node_t*,ultimate_expr_t*,sematic_context_t*){
	return true;
}
bool begin_definite_function(ast_node_t*,sematic_context_t*){
	return true;
}
bool mark_parameters_initialized(ast_node_t*,parameter_list_t*,sematic_context_t*){
	return true;
}
bool end_definite_function(ast_node_t*,sematic_context_t*){
	return true;
}
bool mark_initialized(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool mark_uninitialized(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool push_write_access(ast_node_t*,sematic_context_t*){
	return true;
}
bool pop_access_mode(ast_node_t*,sematic_context_t*){
	return true;
}
bool mark_lvalue_initialized(ast_node_t*,lvalue_t*,sematic_context_t*){
	return true;
}
bool push_read_access(ast_node_t*,sematic_context_t*){
	return true;
}
bool push_address_access(ast_node_t*,sematic_context_t*){
	return true;
}
bool require_initialized_if_read(ast_node_t*,token_t*,sematic_context_t*){
	return true;
}
bool begin_optional_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool end_optional_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool begin_conditional_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool begin_init_branch(ast_node_t*,sematic_context_t*){
	return true;
}
bool end_init_branch(ast_node_t*,sematic_context_t*){
	return true;
}
bool end_conditional_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool record_implicit_init_branch(ast_node_t*,sematic_context_t*){
	return true;
}
bool save_init_condition_fallthrough(ast_node_t*,sematic_context_t*){
	return true;
}
bool begin_loop_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool end_loop_init(ast_node_t*,sematic_context_t*){
	return true;
}
bool require_all_paths_return(ast_node_t*,statements_t*,sematic_context_t*){
	return true;
}
bool check_control_flow(ast_node_t*,ultimate_expr_t*,statements_t*,elseif_else_t*,sematic_context_t*){
	return true;
}
bool check_control_flow(ast_node_t*,ultimate_expr_t*,statements_t*,sematic_context_t*){
	return true;
}
bool leave_loop_scope(ast_node_t*,sematic_context_t*){
	return true;
}
bool require_loop_context(ast_node_t*,sematic_context_t*){
	return true;
}
bool set_terminating_flow(ast_node_t*,sematic_context_t*){
	return true;
}
bool set_return_flow(ast_node_t*,sematic_context_t*){
	return true;
}
bool set_fallthrough_flow(ast_node_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,if_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,while_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,statement_t*,sematic_context_t*){
	return true;
}
bool check_unreachable(ast_node_t*,statement_t*,statements_nonempty_t*,sematic_context_t*){
	return true;
}
bool combine_sequential_flow(ast_node_t*,statement_t*,statements_nonempty_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,statements_nonempty_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,statements_t*,sematic_context_t*){
	return true;
}
bool propagate_flow(ast_node_t*,else_t*,sematic_context_t*){
	return true;
}
bool combine_branch_flow(ast_node_t*,elseif_t*,elseif_else_t*,sematic_context_t*){
	return true;
}