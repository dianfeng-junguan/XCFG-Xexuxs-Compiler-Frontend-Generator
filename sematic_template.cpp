#include "lexer.h"
#include "parser.h"
#include "sematic.h"
#include <vector>
bool visit(ast_node_t* node,sematic_context_t* context);
{%}
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
