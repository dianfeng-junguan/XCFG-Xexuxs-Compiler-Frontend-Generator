#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "lexer.h"
{%}
tokenstream_t do_lex(char *str){
    std::vector<token_t> tokens;
    long slen=strlen(str);
    long ptr=0;
    int line=0,column=0;
    while (ptr<slen) {
        bool flag=false;
        for (int i=0; i<LEXER_RULES_LEN; i++) {
            lexer_rule_t rule=lexer_rules[i];
            std::regex re(rule.pattern);
            std::smatch matches;
            if(std::regex_search(str,matches,re,std::regex_constants::match_continuous)){
                std::string v=matches[0].str();
                token_t tok={
                    .token_type=rule.tok_type,
                    .value=v.c_str(),
                    .line=line,
                    .column=column
                };
                tokens.push_back(tok);
                // move forward
                for (int j=0; j<matches[0].length(); j++) {
                    if(*str=='\n'){
                        line++;
                        column=0;
                    }else {
                        column++;
                    }
                    str++;
                }
                ptr+=matches[0].length();
                flag=true;
            }
        }
        if(!flag){
            printf("lexer error: failed to parse token at line %d, column %d\n",line+1,column+1);
            // move 1 forward to skip
            str++;
            ptr++;
        }
    }
    tokenstream_t ts(tokens);
    return ts;
}