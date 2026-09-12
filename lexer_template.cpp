#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>
#include "lexer.h"
{%}
tokenstream_t do_lex(std::string str){
    std::vector<token_t> tokens;
    long slen=str.length();
    long ptr=0;
    int line=0,column=0;
    // cache regex
    std::regex regexes[LEXER_RULES_LEN];
    for(int i=0;i<LEXER_RULES_LEN;i++){
        regexes[i]=std::regex(lexer_rules[i].pattern);
    }
    while (ptr<slen) {
        bool flag=false;
        for (int i=0; i<LEXER_RULES_LEN; i++) {
            lexer_rule_t rule=lexer_rules[i];
            std::regex &re=regexes[i];
            std::smatch matches;
            std::string subbedstr=str.substr(ptr);
            if(std::regex_search(subbedstr,matches,re,std::regex_constants::match_continuous)){
                std::string v=matches[0].str();
                token_t tok={
                    .token_type=rule.tok_type,
                    .value=v,
                    .line=line,
                    .column=column
                };
                tokens.push_back(tok);
                // move forward
                for (int j=0; j<matches[0].length(); j++) {
                    if(str[ptr+j]=='\n'){
                        line++;
                        column=0;
                    }else {
                        column++;
                    }
                }
                ptr+=matches[0].length();
                flag=true;
                break;
            }
        }
        if(!flag){
            printf("lexer error: failed to parse token at line %d, column %d\n",line+1,column+1);
            // move 1 forward to skip
            ptr++;
        }
    }

    // remove comments and whitespace tokens
    std::vector<token_t> filtered_tokens;
    for (auto tok : tokens) {
        if(BELONGS_TO_CATEGORY_COMMENT(tok.token_type)||BELONGS_TO_CATEGORY_WHITESPACE(tok.token_type)){
            continue;
        }
        filtered_tokens.push_back(tok);
    }
    tokenstream_t ts(filtered_tokens);
    return ts;
}