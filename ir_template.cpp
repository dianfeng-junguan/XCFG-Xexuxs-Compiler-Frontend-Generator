#include "ir.h"
#include "parser.h"
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context);
{funcs}
tempvar_t visit(ast_node_t* node,ir_graph_t* graph,ir_context_t* context){
    if(node==nullptr || graph==nullptr || context==nullptr){
        throw std::invalid_argument("Null pointer passed to visit function.");
    }
    switch(node->get_kind()){
        {%}
        default:
            throw std::invalid_argument("Unknown node type.");
    }
}
void do_ir(const std::vector<ast_node_t*>& ast, ir_context_t& context){
    for(auto* node:ast){
        visit(node,&context.graph,&context);
    }
}