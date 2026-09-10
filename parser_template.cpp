#include <vector>
#include "lexer.h"
class ast_node_t{

};
token_t* parse_token(tokenstream_t *tokenstream, token_type_t token_type){
    token_t *token=tokenstream->peek();
    if(token==NULL){
        return NULL;
    }
    if(token->token_type==token_type){
        tokenstream->next();
        return token;
    }
    return NULL;
}
{%}
std::vector<ast_node_t*> do_parse(tokenstream_t *tokenstream){
    std::vector<ast_node_t*> nodes;
    while(!tokenstream->eof()){
        for(int i=0;i<sizeof(parser_rules)/sizeof(parser_rule_t);i++){
            ast_node_t *node;
            if(node=parser_rules[i].parser(tokenstream)){
                nodes.push_back(node);
                break;
            }
        }
    }
    return nodes;
}