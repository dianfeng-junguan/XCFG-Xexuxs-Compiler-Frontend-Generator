#include <vector>
#include <stdio.h>
#include "lexer.h"
class ast_node_t{
public:
    virtual ~ast_node_t() = default;
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
        bool flag=false;
        for(int i=0;i<sizeof(parser_rules)/sizeof(parser_rule_t);i++){
            ast_node_t *node;
            if(node=parser_rules[i].parser(tokenstream)){
                nodes.push_back(node);
                flag=true;
                break;
            }
        }
        if(!flag){
            printf("parser error: failed to parse token at line %d, column %d\n",tokenstream->peek()->line+1,tokenstream->peek()->column+1);
            tokenstream->begin_parsing();
            tokenstream->next();
            tokenstream->end_parsing();
        }
    }
    return nodes;
}