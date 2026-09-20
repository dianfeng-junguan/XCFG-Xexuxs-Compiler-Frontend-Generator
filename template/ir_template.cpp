#include "ir.h"
#include "parser.h"
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);
tempvar_t visit_ref(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);
{funcs}
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
        {%}
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