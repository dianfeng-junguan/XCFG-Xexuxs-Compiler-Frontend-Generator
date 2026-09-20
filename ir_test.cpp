#include "ir.h"
#include "parser.h"
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);
tempvar_t visit_ref(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);

tempvar_t ir_definition_deftype(definition_deftype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar();
tempvar_t temp_converted=context->create_tempvar();
tempvar_t temp_address=context->create_tempvar();
graph->add_ir(new ir_alloc_t(context->get_symbol(node), temp_address));
temp_value=visit(static_cast<definition_deftype_t*>(node)->value,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->value), temp_value, temp_converted));
graph->add_ir(new ir_store_t(temp_address,temp_converted));
return tempvar_t::empty();

}
        
tempvar_t ir_definition_defntype(definition_defntype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar();
tempvar_t temp_address=context->create_tempvar();
graph->add_ir(new ir_alloc_t(context->get_symbol(node), temp_address));
temp_value=visit(static_cast<definition_defntype_t*>(node)->value,graph,context);
graph->add_ir(new ir_store_t(temp_address,temp_value));
return tempvar_t::empty();

}
        
tempvar_t ir_declaration_varntype(declaration_varntype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
graph->add_ir(new ir_alloc_t(context->get_symbol(node), temp_address));
return tempvar_t::empty();

}
        
tempvar_t ir_declaration_var(declaration_var_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
graph->add_ir(new ir_alloc_t(context->get_symbol(node), temp_address));
return tempvar_t::empty();

}
        
tempvar_t ir_assign_expr_assign(assign_expr_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_converted=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_assign_t*>(node)->left,graph,context);
temp_right=visit(static_cast<assign_expr_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_converted));
graph->add_ir(new ir_store_t(temp_address,temp_converted));
return temp_converted;

}
        
tempvar_t ir_assign_expr_plus_assign(assign_expr_plus_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_plus_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_plus_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_add_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_minus_assign(assign_expr_minus_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_minus_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_minus_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_sub_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_mul_assign(assign_expr_mul_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_mul_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_mul_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_mul_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_div_assign(assign_expr_div_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_div_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_div_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_div_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_mod_assign(assign_expr_mod_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_mod_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_mod_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_mod_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_bitand_assign(assign_expr_bitand_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_bitand_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_bitand_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_bitand_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_bitor_assign(assign_expr_bitor_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_bitor_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_bitor_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_bitor_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_shiftleft_assign(assign_expr_shiftleft_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_shiftleft_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_shl_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_shiftright_assign(assign_expr_shiftright_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar();
tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_address=visit_ref(static_cast<assign_expr_shiftright_assign_t*>(node)->left,graph,context);
graph->add_ir(new ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_shiftright_assign_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_shr_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(new ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_logic_expr(assign_expr_logic_expr_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_eq(logic_expr_eq_eq_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_eq_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_eq_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_equ_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_neq(logic_expr_eq_neq_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_neq_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_neq_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_neq_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_gt(logic_expr_eq_gt_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_gt_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_gt_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_gt_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_lt(logic_expr_eq_lt_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_lt_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_lt_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_lt_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_ge(logic_expr_eq_ge_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_ge_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_ge_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_ge_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_le(logic_expr_eq_le_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<logic_expr_eq_le_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_le_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_le_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_none(logic_expr_eq_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<logic_expr_eq_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_or_or(logic_expr_or_or_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
basic_block_id_t label_true=graph->create_block();
basic_block_id_t label_right=graph->create_block();
basic_block_id_t label_end=graph->create_block();
temp_left=visit(static_cast<logic_expr_or_or_t*>(node)->left,graph,context);
graph->connect(graph->get_current_block(),label_true);
graph->connect(graph->get_current_block(),label_right);graph->add_ir(new ir_if_t(temp_left,label_true,label_right));
graph->set_current_block(label_true);
graph->add_ir(new ir_or_t(temp_left, temp_left, temp_result));
graph->connect(graph->get_current_block(),label_end);
graph->add_ir(new ir_goto_t(context->create_or_get_label("label_end")));
graph->set_current_block(label_right);
temp_result=visit(static_cast<logic_expr_or_or_t*>(node)->right,graph,context);
graph->connect(graph->get_current_block(),label_end);
graph->add_ir(new ir_goto_t(context->create_or_get_label("label_end")));
graph->set_current_block(label_end);
return temp_result;

}
        
tempvar_t ir_logic_expr_or_none(logic_expr_or_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<logic_expr_or_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_and_and(logic_expr_and_and_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
basic_block_id_t label_right=graph->create_block();
basic_block_id_t label_false=graph->create_block();
basic_block_id_t label_end=graph->create_block();
temp_left=visit(static_cast<logic_expr_and_and_t*>(node)->left,graph,context);
graph->connect(graph->get_current_block(),label_right);
graph->connect(graph->get_current_block(),label_false);graph->add_ir(new ir_if_t(temp_left,label_right,label_false));
graph->set_current_block(label_right);
temp_result=visit(static_cast<logic_expr_and_and_t*>(node)->right,graph,context);
graph->connect(graph->get_current_block(),label_end);
graph->add_ir(new ir_goto_t(context->create_or_get_label("label_end")));
graph->set_current_block(label_false);
graph->add_ir(new ir_and_t(temp_left, temp_left, temp_result));
graph->connect(graph->get_current_block(),label_end);
graph->add_ir(new ir_goto_t(context->create_or_get_label("label_end")));
graph->set_current_block(label_end);
return temp_result;

}
        
tempvar_t ir_logic_expr_and_none(logic_expr_and_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<logic_expr_and_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_expr_add(expr_add_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<expr_add_t*>(node)->left,graph,context);
temp_right=visit(static_cast<expr_add_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_add_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_expr_sub(expr_sub_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<expr_sub_t*>(node)->left,graph,context);
temp_right=visit(static_cast<expr_sub_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_sub_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_expr_term(expr_term_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<expr_term_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_term_mul(term_mul_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_mul_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_mul_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_mul_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_div(term_div_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_div_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_div_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_div_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_mod(term_mod_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_mod_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_mod_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_mod_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_bitand(term_bitand_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_bitand_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_bitand_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_bitand_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_bitor(term_bitor_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_bitor_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_bitor_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_bitor_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_shiftleft(term_shiftleft_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_shiftleft_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_shiftleft_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_shl_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_shiftright(term_shiftright_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<term_shiftright_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_shiftright_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_shr_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_factor(term_factor_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<term_factor_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_single_op_factor_bitnot(single_op_factor_bitnot_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_operand=visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,graph,context);
graph->add_ir(new ir_bitnot_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_neg(single_op_factor_neg_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_operand=visit(static_cast<single_op_factor_neg_t*>(node)->expr,graph,context);
graph->add_ir(new ir_minus_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_ref(single_op_factor_ref_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit_ref(static_cast<single_op_factor_ref_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_single_op_factor_deref(single_op_factor_deref_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_pointer=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_pointer=visit(static_cast<single_op_factor_deref_t*>(node)->expr,graph,context);
graph->add_ir(new ir_deref_t(temp_pointer, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_not(single_op_factor_not_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_operand=visit(static_cast<single_op_factor_not_t*>(node)->expr,graph,context);
graph->add_ir(new ir_negate_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_none(single_op_factor_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<single_op_factor_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_power_factor_pow(power_factor_pow_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar();
tempvar_t temp_right=context->create_tempvar();
tempvar_t temp_left_converted=context->create_tempvar();
tempvar_t temp_right_converted=context->create_tempvar();
tempvar_t temp_result=context->create_tempvar();
temp_left=visit(static_cast<power_factor_pow_t*>(node)->left,graph,context);
temp_right=visit(static_cast<power_factor_pow_t*>(node)->right,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->left), temp_left, temp_left_converted));

    graph->add_ir(new ir_cast_t(context->get_conversion(node->right), temp_right, temp_right_converted));
graph->add_ir(new ir_bitxor_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_power_factor_none(power_factor_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<power_factor_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_glued_factor_paren(glued_factor_paren_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<glued_factor_paren_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_glued_factor_value(glued_factor_value_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<glued_factor_value_t*>(node)->value,graph,context);
return temp_result;

}
        
tempvar_t ir_ultimate_expr_def(ultimate_expr_def_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar();
temp_result=visit(static_cast<ultimate_expr_def_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_statement_expr(statement_expr_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_unused=context->create_tempvar();
temp_unused=visit(static_cast<statement_expr_t*>(node)->expr,graph,context);
return tempvar_t::empty();

}
        
tempvar_t ir_statement_return_empty(statement_return_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    graph->add_ir(new ir_return_none_t());
return tempvar_t::empty();

}
        
tempvar_t ir_statement_return_sth(statement_return_sth_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar();
tempvar_t temp_converted=context->create_tempvar();
temp_value=visit(static_cast<statement_return_sth_t*>(node)->value,graph,context);

    graph->add_ir(new ir_cast_t(context->get_conversion(node->value), temp_value, temp_converted));
graph->add_ir(new ir_return_t(temp_converted));
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

tempvar_t ir_glued_factor_call(glued_factor_call_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
	visit(node->args,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_glued_factor_lvalue(glued_factor_lvalue_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->value,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_shift_expr_shiftleft(shift_expr_shiftleft_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
	visit(node->right,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_shift_expr_shiftright(shift_expr_shiftright_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
	visit(node->right,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_shift_expr_expr(shift_expr_expr_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->expr,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_bitand_expr_bitand(bitand_expr_bitand_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
	visit(node->right,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_bitand_expr_shift(bitand_expr_shift_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->expr,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_bitor_expr_bitor(bitor_expr_bitor_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
	visit(node->right,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_bitor_expr_bitand(bitor_expr_bitand_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->expr,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_parened(lvalue_noproperty_parened_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->expr,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_deref(lvalue_noproperty_deref_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->derefee,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noproperty_id(lvalue_noproperty_id_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_prop(lvalue_prop_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->left,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_lvalue_noprop(lvalue_noprop_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->expr,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_raw_type(composed_type_raw_type_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_paren(composed_type_paren_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->inner_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_ptr(composed_type_ptr_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->pointer_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_sizedarr(composed_type_sizedarr_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->element_type,graph,context);
	visit(node->array_size,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_composed_type_nsizedarr(composed_type_nsizedarr_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->element_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_else_default(else_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->statements,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_elseif_default(elseif_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->condition,graph,context);
	visit(node->statements,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_onlyelse(elseif_else_onlyelse_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->else_block,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_chain(elseif_else_chain_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->elseif_block,graph,context);
	visit(node->rest_block,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_elseif_else_empty(elseif_else_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_if_default(if_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->condition,graph,context);
	visit(node->statements,graph,context);
	visit(node->rest_block,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_while_default(while_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->condition,graph,context);
	visit(node->statements,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_multimem(structmembers_multimem_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->def_type,graph,context);
	visit(node->other_members,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_singmem(structmembers_singmem_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->def_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_structmembers_empty(structmembers_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_struct_default(struct_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->members,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_declaration_fn(declaration_fn_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->args,graph,context);
	visit(node->return_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_declaration_struct(declaration_struct_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->members,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statement_definition(statement_definition_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->def,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statement_if(statement_if_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->if_stmt,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statement_while(statement_while_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->while_stmt,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statement_declaration(statement_declaration_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->decl_stmt,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statement_break(statement_break_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_statement_continue(statement_continue_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_statements_nonempty_multistmt(statements_nonempty_multistmt_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->stmt,graph,context);
	visit(node->other_stmts,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statements_nonempty_stmt(statements_nonempty_stmt_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->stmt,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statements_hasstatements(statements_hasstatements_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->statements,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_statements_empty(statements_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_func_returntype_hastype(func_returntype_hastype_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->return_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_func_returntype_void(func_returntype_void_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_parameter_list_nonempty_multiarg(parameter_list_nonempty_multiarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->arg_type,graph,context);
	visit(node->other_args,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_parameter_list_nonempty_singarg(parameter_list_nonempty_singarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->arg_type,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_parameter_list_hasarg(parameter_list_hasarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->args,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_parameter_list_empty(parameter_list_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_argument_list_nonempty_multiarg(argument_list_nonempty_multiarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->value,graph,context);
	visit(node->other_args,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_argument_list_nonempty_singarg(argument_list_nonempty_singarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->value,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_argument_list_hasarg(argument_list_hasarg_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->args,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_argument_list_empty(argument_list_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    
    return tempvar_t::empty();
}

tempvar_t ir_function_default(function_default_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->args,graph,context);
	visit(node->return_type,graph,context);
	visit(node->stmts,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_func_def(top_statement_func_def_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->func,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_decl(top_statement_decl_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->decl,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_var_def(top_statement_var_def_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->def,graph,context);
    return tempvar_t::empty();
}

tempvar_t ir_top_statement_structdef(top_statement_structdef_t* node,ir_graph_t* graph,ir_context_t* context){
    visit(node->structdef,graph,context);
    return tempvar_t::empty();
}

tempvar_t _visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context, bool ref){
    if(node==nullptr || graph==nullptr || context==nullptr){
        throw std::invalid_argument("Null pointer passed to visit function.");
    }
    if (ref) {
        context->push_visit_ref();
    }else{
        context->push_visit();
    }
    tempvar_t temp_result=context->create_tempvar("");
    switch(node->get_kind()){
        	case NODE_FACTOR_NUM:
	temp_result=ir_factor_num(static_cast<factor_num_t*>(node),graph,context);
	break;

		case NODE_FACTOR_CH:
	temp_result=ir_factor_ch(static_cast<factor_ch_t*>(node),graph,context);
	break;

		case NODE_FACTOR_STR:
	temp_result=ir_factor_str(static_cast<factor_str_t*>(node),graph,context);
	break;

		case NODE_GLUED_FACTOR_PAREN:
	temp_result=ir_glued_factor_paren(static_cast<glued_factor_paren_t*>(node),graph,context);
	break;

		case NODE_GLUED_FACTOR_CALL:
	temp_result=ir_glued_factor_call(static_cast<glued_factor_call_t*>(node),graph,context);
	break;

		case NODE_GLUED_FACTOR_LVALUE:
	temp_result=ir_glued_factor_lvalue(static_cast<glued_factor_lvalue_t*>(node),graph,context);
	break;

		case NODE_GLUED_FACTOR_VALUE:
	temp_result=ir_glued_factor_value(static_cast<glued_factor_value_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_BITNOT:
	temp_result=ir_single_op_factor_bitnot(static_cast<single_op_factor_bitnot_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_NEG:
	temp_result=ir_single_op_factor_neg(static_cast<single_op_factor_neg_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_REF:
	temp_result=ir_single_op_factor_ref(static_cast<single_op_factor_ref_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_DEREF:
	temp_result=ir_single_op_factor_deref(static_cast<single_op_factor_deref_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_NOT:
	temp_result=ir_single_op_factor_not(static_cast<single_op_factor_not_t*>(node),graph,context);
	break;

		case NODE_SINGLE_OP_FACTOR_NONE:
	temp_result=ir_single_op_factor_none(static_cast<single_op_factor_none_t*>(node),graph,context);
	break;

		case NODE_POWER_FACTOR_POW:
	temp_result=ir_power_factor_pow(static_cast<power_factor_pow_t*>(node),graph,context);
	break;

		case NODE_POWER_FACTOR_NONE:
	temp_result=ir_power_factor_none(static_cast<power_factor_none_t*>(node),graph,context);
	break;

		case NODE_TERM_MUL:
	temp_result=ir_term_mul(static_cast<term_mul_t*>(node),graph,context);
	break;

		case NODE_TERM_DIV:
	temp_result=ir_term_div(static_cast<term_div_t*>(node),graph,context);
	break;

		case NODE_TERM_MOD:
	temp_result=ir_term_mod(static_cast<term_mod_t*>(node),graph,context);
	break;

		case NODE_TERM_FACTOR:
	temp_result=ir_term_factor(static_cast<term_factor_t*>(node),graph,context);
	break;

		case NODE_SHIFT_EXPR_SHIFTLEFT:
	temp_result=ir_shift_expr_shiftleft(static_cast<shift_expr_shiftleft_t*>(node),graph,context);
	break;

		case NODE_SHIFT_EXPR_SHIFTRIGHT:
	temp_result=ir_shift_expr_shiftright(static_cast<shift_expr_shiftright_t*>(node),graph,context);
	break;

		case NODE_SHIFT_EXPR_EXPR:
	temp_result=ir_shift_expr_expr(static_cast<shift_expr_expr_t*>(node),graph,context);
	break;

		case NODE_BITAND_EXPR_BITAND:
	temp_result=ir_bitand_expr_bitand(static_cast<bitand_expr_bitand_t*>(node),graph,context);
	break;

		case NODE_BITAND_EXPR_SHIFT:
	temp_result=ir_bitand_expr_shift(static_cast<bitand_expr_shift_t*>(node),graph,context);
	break;

		case NODE_BITOR_EXPR_BITOR:
	temp_result=ir_bitor_expr_bitor(static_cast<bitor_expr_bitor_t*>(node),graph,context);
	break;

		case NODE_BITOR_EXPR_BITAND:
	temp_result=ir_bitor_expr_bitand(static_cast<bitor_expr_bitand_t*>(node),graph,context);
	break;

		case NODE_EXPR_ADD:
	temp_result=ir_expr_add(static_cast<expr_add_t*>(node),graph,context);
	break;

		case NODE_EXPR_SUB:
	temp_result=ir_expr_sub(static_cast<expr_sub_t*>(node),graph,context);
	break;

		case NODE_EXPR_TERM:
	temp_result=ir_expr_term(static_cast<expr_term_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_AND_AND:
	temp_result=ir_logic_expr_and_and(static_cast<logic_expr_and_and_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_AND_NONE:
	temp_result=ir_logic_expr_and_none(static_cast<logic_expr_and_none_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_OR_OR:
	temp_result=ir_logic_expr_or_or(static_cast<logic_expr_or_or_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_OR_NONE:
	temp_result=ir_logic_expr_or_none(static_cast<logic_expr_or_none_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_EQ:
	temp_result=ir_logic_expr_eq_eq(static_cast<logic_expr_eq_eq_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_NEQ:
	temp_result=ir_logic_expr_eq_neq(static_cast<logic_expr_eq_neq_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_GT:
	temp_result=ir_logic_expr_eq_gt(static_cast<logic_expr_eq_gt_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_LT:
	temp_result=ir_logic_expr_eq_lt(static_cast<logic_expr_eq_lt_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_GE:
	temp_result=ir_logic_expr_eq_ge(static_cast<logic_expr_eq_ge_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_LE:
	temp_result=ir_logic_expr_eq_le(static_cast<logic_expr_eq_le_t*>(node),graph,context);
	break;

		case NODE_LOGIC_EXPR_EQ_NONE:
	temp_result=ir_logic_expr_eq_none(static_cast<logic_expr_eq_none_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_ASSIGN:
	temp_result=ir_assign_expr_assign(static_cast<assign_expr_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
	temp_result=ir_assign_expr_plus_assign(static_cast<assign_expr_plus_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
	temp_result=ir_assign_expr_minus_assign(static_cast<assign_expr_minus_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_MUL_ASSIGN:
	temp_result=ir_assign_expr_mul_assign(static_cast<assign_expr_mul_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_DIV_ASSIGN:
	temp_result=ir_assign_expr_div_assign(static_cast<assign_expr_div_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_MOD_ASSIGN:
	temp_result=ir_assign_expr_mod_assign(static_cast<assign_expr_mod_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
	temp_result=ir_assign_expr_bitand_assign(static_cast<assign_expr_bitand_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
	temp_result=ir_assign_expr_bitor_assign(static_cast<assign_expr_bitor_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
	temp_result=ir_assign_expr_shiftleft_assign(static_cast<assign_expr_shiftleft_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
	temp_result=ir_assign_expr_shiftright_assign(static_cast<assign_expr_shiftright_assign_t*>(node),graph,context);
	break;

		case NODE_ASSIGN_EXPR_LOGIC_EXPR:
	temp_result=ir_assign_expr_logic_expr(static_cast<assign_expr_logic_expr_t*>(node),graph,context);
	break;

		case NODE_ULTIMATE_EXPR_DEF:
	temp_result=ir_ultimate_expr_def(static_cast<ultimate_expr_def_t*>(node),graph,context);
	break;

		case NODE_LVALUE_NOPROPERTY_PARENED:
	temp_result=ir_lvalue_noproperty_parened(static_cast<lvalue_noproperty_parened_t*>(node),graph,context);
	break;

		case NODE_LVALUE_NOPROPERTY_DEREF:
	temp_result=ir_lvalue_noproperty_deref(static_cast<lvalue_noproperty_deref_t*>(node),graph,context);
	break;

		case NODE_LVALUE_NOPROPERTY_ID:
	temp_result=ir_lvalue_noproperty_id(static_cast<lvalue_noproperty_id_t*>(node),graph,context);
	break;

		case NODE_LVALUE_PROP:
	temp_result=ir_lvalue_prop(static_cast<lvalue_prop_t*>(node),graph,context);
	break;

		case NODE_LVALUE_NOPROP:
	temp_result=ir_lvalue_noprop(static_cast<lvalue_noprop_t*>(node),graph,context);
	break;

		case NODE_COMPOSED_TYPE_RAW_TYPE:
	temp_result=ir_composed_type_raw_type(static_cast<composed_type_raw_type_t*>(node),graph,context);
	break;

		case NODE_COMPOSED_TYPE_PAREN:
	temp_result=ir_composed_type_paren(static_cast<composed_type_paren_t*>(node),graph,context);
	break;

		case NODE_COMPOSED_TYPE_PTR:
	temp_result=ir_composed_type_ptr(static_cast<composed_type_ptr_t*>(node),graph,context);
	break;

		case NODE_COMPOSED_TYPE_SIZEDARR:
	temp_result=ir_composed_type_sizedarr(static_cast<composed_type_sizedarr_t*>(node),graph,context);
	break;

		case NODE_COMPOSED_TYPE_NSIZEDARR:
	temp_result=ir_composed_type_nsizedarr(static_cast<composed_type_nsizedarr_t*>(node),graph,context);
	break;

		case NODE_DEFINITION_DEFTYPE:
	temp_result=ir_definition_deftype(static_cast<definition_deftype_t*>(node),graph,context);
	break;

		case NODE_DEFINITION_DEFNTYPE:
	temp_result=ir_definition_defntype(static_cast<definition_defntype_t*>(node),graph,context);
	break;

		case NODE_ELSE_DEFAULT:
	temp_result=ir_else_default(static_cast<else_default_t*>(node),graph,context);
	break;

		case NODE_ELSEIF_DEFAULT:
	temp_result=ir_elseif_default(static_cast<elseif_default_t*>(node),graph,context);
	break;

		case NODE_ELSEIF_ELSE_ONLYELSE:
	temp_result=ir_elseif_else_onlyelse(static_cast<elseif_else_onlyelse_t*>(node),graph,context);
	break;

		case NODE_ELSEIF_ELSE_CHAIN:
	temp_result=ir_elseif_else_chain(static_cast<elseif_else_chain_t*>(node),graph,context);
	break;

		case NODE_ELSEIF_ELSE_EMPTY:
	temp_result=ir_elseif_else_empty(static_cast<elseif_else_empty_t*>(node),graph,context);
	break;

		case NODE_IF_DEFAULT:
	temp_result=ir_if_default(static_cast<if_default_t*>(node),graph,context);
	break;

		case NODE_WHILE_DEFAULT:
	temp_result=ir_while_default(static_cast<while_default_t*>(node),graph,context);
	break;

		case NODE_STRUCTMEMBERS_MULTIMEM:
	temp_result=ir_structmembers_multimem(static_cast<structmembers_multimem_t*>(node),graph,context);
	break;

		case NODE_STRUCTMEMBERS_SINGMEM:
	temp_result=ir_structmembers_singmem(static_cast<structmembers_singmem_t*>(node),graph,context);
	break;

		case NODE_STRUCTMEMBERS_EMPTY:
	temp_result=ir_structmembers_empty(static_cast<structmembers_empty_t*>(node),graph,context);
	break;

		case NODE_STRUCT_DEFAULT:
	temp_result=ir_struct_default(static_cast<struct_default_t*>(node),graph,context);
	break;

		case NODE_DECLARATION_VARNTYPE:
	temp_result=ir_declaration_varntype(static_cast<declaration_varntype_t*>(node),graph,context);
	break;

		case NODE_DECLARATION_VAR:
	temp_result=ir_declaration_var(static_cast<declaration_var_t*>(node),graph,context);
	break;

		case NODE_DECLARATION_FN:
	temp_result=ir_declaration_fn(static_cast<declaration_fn_t*>(node),graph,context);
	break;

		case NODE_DECLARATION_STRUCT:
	temp_result=ir_declaration_struct(static_cast<declaration_struct_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_EXPR:
	temp_result=ir_statement_expr(static_cast<statement_expr_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_DEFINITION:
	temp_result=ir_statement_definition(static_cast<statement_definition_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_IF:
	temp_result=ir_statement_if(static_cast<statement_if_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_WHILE:
	temp_result=ir_statement_while(static_cast<statement_while_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_DECLARATION:
	temp_result=ir_statement_declaration(static_cast<statement_declaration_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_BREAK:
	temp_result=ir_statement_break(static_cast<statement_break_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_CONTINUE:
	temp_result=ir_statement_continue(static_cast<statement_continue_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_RETURN_STH:
	temp_result=ir_statement_return_sth(static_cast<statement_return_sth_t*>(node),graph,context);
	break;

		case NODE_STATEMENT_RETURN_EMPTY:
	temp_result=ir_statement_return_empty(static_cast<statement_return_empty_t*>(node),graph,context);
	break;

		case NODE_STATEMENTS_NONEMPTY_MULTISTMT:
	temp_result=ir_statements_nonempty_multistmt(static_cast<statements_nonempty_multistmt_t*>(node),graph,context);
	break;

		case NODE_STATEMENTS_NONEMPTY_STMT:
	temp_result=ir_statements_nonempty_stmt(static_cast<statements_nonempty_stmt_t*>(node),graph,context);
	break;

		case NODE_STATEMENTS_HASSTATEMENTS:
	temp_result=ir_statements_hasstatements(static_cast<statements_hasstatements_t*>(node),graph,context);
	break;

		case NODE_STATEMENTS_EMPTY:
	temp_result=ir_statements_empty(static_cast<statements_empty_t*>(node),graph,context);
	break;

		case NODE_FUNC_RETURNTYPE_HASTYPE:
	temp_result=ir_func_returntype_hastype(static_cast<func_returntype_hastype_t*>(node),graph,context);
	break;

		case NODE_FUNC_RETURNTYPE_VOID:
	temp_result=ir_func_returntype_void(static_cast<func_returntype_void_t*>(node),graph,context);
	break;

		case NODE_PARAMETER_LIST_NONEMPTY_MULTIARG:
	temp_result=ir_parameter_list_nonempty_multiarg(static_cast<parameter_list_nonempty_multiarg_t*>(node),graph,context);
	break;

		case NODE_PARAMETER_LIST_NONEMPTY_SINGARG:
	temp_result=ir_parameter_list_nonempty_singarg(static_cast<parameter_list_nonempty_singarg_t*>(node),graph,context);
	break;

		case NODE_PARAMETER_LIST_HASARG:
	temp_result=ir_parameter_list_hasarg(static_cast<parameter_list_hasarg_t*>(node),graph,context);
	break;

		case NODE_PARAMETER_LIST_EMPTY:
	temp_result=ir_parameter_list_empty(static_cast<parameter_list_empty_t*>(node),graph,context);
	break;

		case NODE_ARGUMENT_LIST_NONEMPTY_MULTIARG:
	temp_result=ir_argument_list_nonempty_multiarg(static_cast<argument_list_nonempty_multiarg_t*>(node),graph,context);
	break;

		case NODE_ARGUMENT_LIST_NONEMPTY_SINGARG:
	temp_result=ir_argument_list_nonempty_singarg(static_cast<argument_list_nonempty_singarg_t*>(node),graph,context);
	break;

		case NODE_ARGUMENT_LIST_HASARG:
	temp_result=ir_argument_list_hasarg(static_cast<argument_list_hasarg_t*>(node),graph,context);
	break;

		case NODE_ARGUMENT_LIST_EMPTY:
	temp_result=ir_argument_list_empty(static_cast<argument_list_empty_t*>(node),graph,context);
	break;

		case NODE_FUNCTION_DEFAULT:
	temp_result=ir_function_default(static_cast<function_default_t*>(node),graph,context);
	break;

		case NODE_TOP_STATEMENT_FUNC_DEF:
	temp_result=ir_top_statement_func_def(static_cast<top_statement_func_def_t*>(node),graph,context);
	break;

		case NODE_TOP_STATEMENT_DECL:
	temp_result=ir_top_statement_decl(static_cast<top_statement_decl_t*>(node),graph,context);
	break;

		case NODE_TOP_STATEMENT_VAR_DEF:
	temp_result=ir_top_statement_var_def(static_cast<top_statement_var_def_t*>(node),graph,context);
	break;

		case NODE_TOP_STATEMENT_STRUCTDEF:
	temp_result=ir_top_statement_structdef(static_cast<top_statement_structdef_t*>(node),graph,context);
	break;

        default:
            if (ref) {
                context->push_visit_ref();
            }else{
                context->push_visit();
            }
            throw std::invalid_argument("Unknown node type.");
    }
    if (ref) {
        context->pop_visit_ref();
    }else{
        context->pop_visit();
    }
    return temp_result;
}
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context){
    return _visit(node, graph, context, false);
}
tempvar_t visit_ref(ast_node_t* node,ir_graph_t* graph,ir_context_t* context){
    return _visit(node, graph, context, true);
}
void do_ir(const std::vector<ast_node_t*>& ast, ir_context_t& context){
    for(auto* node:ast){
        switch(node->get_kind()){
            // TODO : Add cases for specific node types that require their own IR graph such as structs, global variables etc.
            default:
                // Here we demonstrate how to create a new IR graph(function).
                ir_graph_t* new_graph=context.module.functions.emplace_back(std::make_unique<ir_graph_t>()).get();
                basic_block_id_t entry=new_graph->create_block();
                new_graph->entry=entry;
                new_graph->set_current_block(entry);
                visit(node,new_graph,&context);
                break;
        }
    }
}