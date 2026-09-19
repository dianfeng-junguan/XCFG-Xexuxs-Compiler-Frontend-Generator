#include "ir.h"
#include "parser.h"

tempvar_t ir_factor_id(factor_id_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_factor_num(factor_num_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_factor_ch(factor_ch_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_factor_str(factor_str_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_glued_factor_def(glued_factor_def_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_glued_factor_call(glued_factor_call_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_parened(lvalue_noproperty_parened_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_deref(lvalue_noproperty_deref_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_id(lvalue_noproperty_id_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_prop(lvalue_prop_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noprop(lvalue_noprop_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_raw_type(composed_type_raw_type_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_paren(composed_type_paren_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_ptr(composed_type_ptr_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_nsizedarr(composed_type_nsizedarr_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_sizedarr(composed_type_sizedarr_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_else_default(else_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_elseif_default(elseif_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_onlyelse(elseif_else_onlyelse_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_chain(elseif_else_chain_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_empty(elseif_else_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_if_default(if_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_while_default(while_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_singmem(structmembers_singmem_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_multimem(structmembers_multimem_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_empty(structmembers_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_struct_default(struct_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_declaration_fn(declaration_fn_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_declaration_struct(declaration_struct_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_definition(statement_definition_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_if(statement_if_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_while(statement_while_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_declaration(statement_declaration_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_break(statement_break_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statement_continue(statement_continue_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statements_stmt(statements_stmt_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statements_multistmt(statements_multistmt_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_statements_empty(statements_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_func_returntype_hastype(func_returntype_hastype_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_func_returntype_void(func_returntype_void_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_arglist_nonempty_singarg(arglist_nonempty_singarg_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_arglist_nonempty_multiarg(arglist_nonempty_multiarg_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_arglist_hasarg(arglist_hasarg_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_arglist_empty(arglist_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_function_default(function_default_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_func_def(top_statement_func_def_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_decl(top_statement_decl_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_var_def(top_statement_var_def_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_structdef(top_statement_structdef_t* node,ir_graph_t* graph,ir_context_t* context){
    return tempvar_t::empty();
}

