#include "lexer.h"
#include "parser.h"
#include <vector>
class sematic_context_t{
public:
    int stage;
};
void visit(ast_node_t* node,sematic_context_t* context);
{%}
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