#include "ir.h"
#include "parser.h"
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);

tempvar_t ir_definition_deftype(definition_deftype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar("temp_value");
tempvar_t temp_converted=context->create_tempvar("temp_converted");
tempvar_t temp_address=context->create_tempvar("temp_address");
graph->add_ir(ir_alloc_t("sym", temp_address));
temp_value=visit(static_cast<definition_deftype_t*>(node)->value,graph,context);
graph->add_ir(ir_cast_t("conversion(value)", temp_value, temp_converted));
graph->add_ir(ir_store_t(temp_address,temp_converted));
return tempvar_t("");

}
        
tempvar_t ir_definition_defntype(definition_defntype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar("temp_value");
tempvar_t temp_address=context->create_tempvar("temp_address");
graph->add_ir(ir_alloc_t("sym", temp_address));
temp_value=visit(static_cast<definition_defntype_t*>(node)->value,graph,context);
graph->add_ir(ir_store_t(temp_address,temp_value));
return tempvar_t("");

}
        
tempvar_t ir_declaration_varntype(declaration_varntype_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
graph->add_ir(ir_alloc_t("sym", temp_address));
return tempvar_t("");

}
        
tempvar_t ir_declaration_var(declaration_var_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
graph->add_ir(ir_alloc_t("sym", temp_address));
return tempvar_t("");

}
        
tempvar_t ir_assign_expr_assign(assign_expr_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_converted=context->create_tempvar("temp_converted");
temp_address=visit_ref(static_cast<assign_expr_assign_t*>(node)->left,graph,context);
temp_right=visit(static_cast<assign_expr_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_converted));
graph->add_ir(ir_store_t(temp_address,temp_converted));
return temp_converted;

}
        
tempvar_t ir_assign_expr_plus_assign(assign_expr_plus_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_plus_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_plus_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_add_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_minus_assign(assign_expr_minus_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_minus_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_minus_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_sub_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_mul_assign(assign_expr_mul_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_mul_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_mul_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_mul_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_div_assign(assign_expr_div_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_div_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_div_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_div_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_mod_assign(assign_expr_mod_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_mod_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_mod_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_mod_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_bitand_assign(assign_expr_bitand_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_bitand_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_bitand_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_bitand_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_bitor_assign(assign_expr_bitor_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_bitor_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_bitor_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_bitor_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_shiftleft_assign(assign_expr_shiftleft_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_shiftleft_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_shiftleft_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_shl_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_shiftright_assign(assign_expr_shiftright_assign_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_address=context->create_tempvar("temp_address");
tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_address=visit_ref(static_cast<assign_expr_shiftright_assign_t*>(node)->left,graph,context);
graph->add_ir(ir_load_t(temp_address,temp_left));
temp_right=visit(static_cast<assign_expr_shiftright_assign_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_shr_t(temp_left_converted, temp_right_converted, temp_result));
graph->add_ir(ir_store_t(temp_address,temp_result));
return temp_result;

}
        
tempvar_t ir_assign_expr_logic_expr(assign_expr_logic_expr_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<assign_expr_logic_expr_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_eq(logic_expr_eq_eq_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_eq_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_eq_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_equ_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_neq(logic_expr_eq_neq_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_neq_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_neq_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_neq_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_gt(logic_expr_eq_gt_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_gt_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_gt_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_gt_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_lt(logic_expr_eq_lt_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_lt_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_lt_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_lt_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_ge(logic_expr_eq_ge_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_ge_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_ge_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_ge_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_le(logic_expr_eq_le_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_eq_le_t*>(node)->left,graph,context);
temp_right=visit(static_cast<logic_expr_eq_le_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_le_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_logic_expr_eq_none(logic_expr_eq_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<logic_expr_eq_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_or_or(logic_expr_or_or_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_or_or_t*>(node)->left,graph,context);
graph->add_ir(ir_if_t(temp_left,context->create_or_get_label("label_true"),context->create_or_get_label("label_right")));
label_t label_true=context->create_or_get_label("label_true");
graph->set_current_label(label_true);
graph->add_ir(ir_or_t(temp_left, temp_left, temp_result));
label_t label_end=context->create_or_get_label("label_end");
graph->add_ir(ir_goto_t(label_end));
{
	basic_block_t* old_block=graph->get_current_block();
basic_block_t* new_block=graph->new_block();
graph->connect(old_block,new_block);
graph->set_current_block(new_block);
}
label_t label_right=context->create_or_get_label("label_right");
graph->set_current_label(label_right);
temp_result=visit(static_cast<logic_expr_or_or_t*>(node)->right,graph,context);
label_t label_end=context->create_or_get_label("label_end");
graph->add_ir(ir_goto_t(label_end));
{
	basic_block_t* old_block=graph->get_current_block();
basic_block_t* new_block=graph->new_block();
graph->connect(old_block,new_block);
graph->set_current_block(new_block);
}
label_t label_end=context->create_or_get_label("label_end");
graph->set_current_label(label_end);
return temp_result;

}
        
tempvar_t ir_logic_expr_or_none(logic_expr_or_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<logic_expr_or_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_logic_expr_and_and(logic_expr_and_and_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<logic_expr_and_and_t*>(node)->left,graph,context);
graph->add_ir(ir_if_t(temp_left,context->create_or_get_label("label_right"),context->create_or_get_label("label_false")));
label_t label_right=context->create_or_get_label("label_right");
graph->set_current_label(label_right);
temp_result=visit(static_cast<logic_expr_and_and_t*>(node)->right,graph,context);
label_t label_end=context->create_or_get_label("label_end");
graph->add_ir(ir_goto_t(label_end));
{
	basic_block_t* old_block=graph->get_current_block();
basic_block_t* new_block=graph->new_block();
graph->connect(old_block,new_block);
graph->set_current_block(new_block);
}
label_t label_false=context->create_or_get_label("label_false");
graph->set_current_label(label_false);
graph->add_ir(ir_and_t(temp_left, temp_left, temp_result));
label_t label_end=context->create_or_get_label("label_end");
graph->add_ir(ir_goto_t(label_end));
{
	basic_block_t* old_block=graph->get_current_block();
basic_block_t* new_block=graph->new_block();
graph->connect(old_block,new_block);
graph->set_current_block(new_block);
}
label_t label_end=context->create_or_get_label("label_end");
graph->set_current_label(label_end);
return temp_result;

}
        
tempvar_t ir_logic_expr_and_none(logic_expr_and_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<logic_expr_and_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_expr_add(expr_add_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<expr_add_t*>(node)->left,graph,context);
temp_right=visit(static_cast<expr_add_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_add_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_expr_sub(expr_sub_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<expr_sub_t*>(node)->left,graph,context);
temp_right=visit(static_cast<expr_sub_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_sub_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_expr_term(expr_term_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<expr_term_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_term_mul(term_mul_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_mul_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_mul_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_mul_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_div(term_div_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_div_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_div_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_div_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_mod(term_mod_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_mod_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_mod_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_mod_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_bitand(term_bitand_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_bitand_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_bitand_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_bitand_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_bitor(term_bitor_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_bitor_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_bitor_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_bitor_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_shiftleft(term_shiftleft_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_shiftleft_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_shiftleft_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_shl_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_shiftright(term_shiftright_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<term_shiftright_t*>(node)->left,graph,context);
temp_right=visit(static_cast<term_shiftright_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_shr_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_term_factor(term_factor_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<term_factor_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_single_op_factor_bitnot(single_op_factor_bitnot_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar("temp_operand");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_operand=visit(static_cast<single_op_factor_bitnot_t*>(node)->expr,graph,context);
graph->add_ir(ir_bitnot_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_neg(single_op_factor_neg_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar("temp_operand");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_operand=visit(static_cast<single_op_factor_neg_t*>(node)->expr,graph,context);
graph->add_ir(ir_minus_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_ref(single_op_factor_ref_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit_ref(static_cast<single_op_factor_ref_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_single_op_factor_deref(single_op_factor_deref_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_pointer=context->create_tempvar("temp_pointer");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_pointer=visit(static_cast<single_op_factor_deref_t*>(node)->expr,graph,context);
graph->add_ir(ir_deref_t(temp_pointer, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_not(single_op_factor_not_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_operand=context->create_tempvar("temp_operand");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_operand=visit(static_cast<single_op_factor_not_t*>(node)->expr,graph,context);
graph->add_ir(ir_negate_t(temp_operand, temp_result));
return temp_result;

}
        
tempvar_t ir_single_op_factor_none(single_op_factor_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<single_op_factor_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_power_factor_pow(power_factor_pow_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_left=context->create_tempvar("temp_left");
tempvar_t temp_right=context->create_tempvar("temp_right");
tempvar_t temp_left_converted=context->create_tempvar("temp_left_converted");
tempvar_t temp_right_converted=context->create_tempvar("temp_right_converted");
tempvar_t temp_result=context->create_tempvar("temp_result");
temp_left=visit(static_cast<power_factor_pow_t*>(node)->left,graph,context);
temp_right=visit(static_cast<power_factor_pow_t*>(node)->right,graph,context);
graph->add_ir(ir_cast_t("conversion(left)", temp_left, temp_left_converted));
graph->add_ir(ir_cast_t("conversion(right)", temp_right, temp_right_converted));
graph->add_ir(ir_bitxor_t(temp_left_converted, temp_right_converted, temp_result));
return temp_result;

}
        
tempvar_t ir_power_factor_none(power_factor_none_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<power_factor_none_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_glued_factor_paren(glued_factor_paren_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<glued_factor_paren_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_glued_factor_value(glued_factor_value_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<glued_factor_value_t*>(node)->value,graph,context);
return temp_result;

}
        
tempvar_t ir_ultimate_expr_def(ultimate_expr_def_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_result=context->create_tempvar("temp_result");
temp_result=visit(static_cast<ultimate_expr_def_t*>(node)->expr,graph,context);
return temp_result;

}
        
tempvar_t ir_statement_expr(statement_expr_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_unused=context->create_tempvar("temp_unused");
temp_unused=visit(static_cast<statement_expr_t*>(node)->expr,graph,context);
return tempvar_t("");

}
        
tempvar_t ir_statement_return_empty(statement_return_empty_t* node,ir_graph_t* graph,ir_context_t* context){
    graph->add_ir(ir_return_none_t());
return tempvar_t("");

}
        
tempvar_t ir_statement_return_sth(statement_return_sth_t* node,ir_graph_t* graph,ir_context_t* context){
    tempvar_t temp_value=context->create_tempvar("temp_value");
tempvar_t temp_converted=context->create_tempvar("temp_converted");
temp_value=visit(static_cast<statement_return_sth_t*>(node)->value,graph,context);
graph->add_ir(ir_cast_t("conversion(value)", temp_value, temp_converted));
graph->add_ir(ir_return_t(temp_converted));
return tempvar_t("");

}
        
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context){
    if(node==nullptr || graph==nullptr || context==nullptr){
        throw std::invalid_argument("Null pointer passed to visit function.");
    }
    switch(node->get_kind()){
        	case NODE_DEFINITION_DEFTYPE:
return ir_definition_deftype(node,graph,context);

	case NODE_DEFINITION_DEFNTYPE:
return ir_definition_defntype(node,graph,context);

	case NODE_DECLARATION_VARNTYPE:
return ir_declaration_varntype(node,graph,context);

	case NODE_DECLARATION_VAR:
return ir_declaration_var(node,graph,context);

	case NODE_ASSIGN_EXPR_ASSIGN:
return ir_assign_expr_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_PLUS_ASSIGN:
return ir_assign_expr_plus_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_MINUS_ASSIGN:
return ir_assign_expr_minus_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_MUL_ASSIGN:
return ir_assign_expr_mul_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_DIV_ASSIGN:
return ir_assign_expr_div_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_MOD_ASSIGN:
return ir_assign_expr_mod_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_BITAND_ASSIGN:
return ir_assign_expr_bitand_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_BITOR_ASSIGN:
return ir_assign_expr_bitor_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN:
return ir_assign_expr_shiftleft_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN:
return ir_assign_expr_shiftright_assign(node,graph,context);

	case NODE_ASSIGN_EXPR_LOGIC_EXPR:
return ir_assign_expr_logic_expr(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_EQ:
return ir_logic_expr_eq_eq(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_NEQ:
return ir_logic_expr_eq_neq(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_GT:
return ir_logic_expr_eq_gt(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_LT:
return ir_logic_expr_eq_lt(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_GE:
return ir_logic_expr_eq_ge(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_LE:
return ir_logic_expr_eq_le(node,graph,context);

	case NODE_LOGIC_EXPR_EQ_NONE:
return ir_logic_expr_eq_none(node,graph,context);

	case NODE_LOGIC_EXPR_OR_OR:
return ir_logic_expr_or_or(node,graph,context);

	case NODE_LOGIC_EXPR_OR_NONE:
return ir_logic_expr_or_none(node,graph,context);

	case NODE_LOGIC_EXPR_AND_AND:
return ir_logic_expr_and_and(node,graph,context);

	case NODE_LOGIC_EXPR_AND_NONE:
return ir_logic_expr_and_none(node,graph,context);

	case NODE_EXPR_ADD:
return ir_expr_add(node,graph,context);

	case NODE_EXPR_SUB:
return ir_expr_sub(node,graph,context);

	case NODE_EXPR_TERM:
return ir_expr_term(node,graph,context);

	case NODE_TERM_MUL:
return ir_term_mul(node,graph,context);

	case NODE_TERM_DIV:
return ir_term_div(node,graph,context);

	case NODE_TERM_MOD:
return ir_term_mod(node,graph,context);

	case NODE_TERM_BITAND:
return ir_term_bitand(node,graph,context);

	case NODE_TERM_BITOR:
return ir_term_bitor(node,graph,context);

	case NODE_TERM_SHIFTLEFT:
return ir_term_shiftleft(node,graph,context);

	case NODE_TERM_SHIFTRIGHT:
return ir_term_shiftright(node,graph,context);

	case NODE_TERM_FACTOR:
return ir_term_factor(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_BITNOT:
return ir_single_op_factor_bitnot(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_NEG:
return ir_single_op_factor_neg(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_REF:
return ir_single_op_factor_ref(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_DEREF:
return ir_single_op_factor_deref(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_NOT:
return ir_single_op_factor_not(node,graph,context);

	case NODE_SINGLE_OP_FACTOR_NONE:
return ir_single_op_factor_none(node,graph,context);

	case NODE_POWER_FACTOR_POW:
return ir_power_factor_pow(node,graph,context);

	case NODE_POWER_FACTOR_NONE:
return ir_power_factor_none(node,graph,context);

	case NODE_GLUED_FACTOR_PAREN:
return ir_glued_factor_paren(node,graph,context);

	case NODE_GLUED_FACTOR_VALUE:
return ir_glued_factor_value(node,graph,context);

	case NODE_ULTIMATE_EXPR_DEF:
return ir_ultimate_expr_def(node,graph,context);

	case NODE_STATEMENT_EXPR:
return ir_statement_expr(node,graph,context);

	case NODE_STATEMENT_RETURN_EMPTY:
return ir_statement_return_empty(node,graph,context);

	case NODE_STATEMENT_RETURN_STH:
return ir_statement_return_sth(node,graph,context);

        default:
            throw std::invalid_argument("Unknown node type.");
    }
}
void do_ir(const std::vector<ast_node_t*>& ast, ir_context_t& context){
    for(auto* node:ast){
        visit(node,&context.graph,&context);
    }
}