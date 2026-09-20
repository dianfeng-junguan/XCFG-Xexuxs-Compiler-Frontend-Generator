#include <memory>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>
#include "lexer.h"

    
#define LEXER_RULES_LEN 62
lexer_rule_t lexer_rules[]={
    {"let", "\\blet\\b", TOKEN_LET},
{"fn", "\\bfn\\b", TOKEN_FN},
{"if", "\\bif\\b", TOKEN_IF},
{"else", "\\belse\\b", TOKEN_ELSE},
{"while", "\\bwhile\\b", TOKEN_WHILE},
{"break", "\\bbreak\\b", TOKEN_BREAK},
{"return", "\\breturn\\b", TOKEN_RETURN},
{"continue", "\\bcontinue\\b", TOKEN_CONTINUE},
{"include", "\\binclude\\b", TOKEN_INCLUDE},
{"int", "\\bint\\b", TOKEN_INT},
{"string_typekw", "\\bstring\\b", TOKEN_STRING_TYPEKW},
{"char_typekw", "\\bchar\\b", TOKEN_CHAR_TYPEKW},
{"void", "\\bvoid\\b", TOKEN_VOID},
{"struct", "\\bstruct\\b", TOKEN_STRUCT},
{"float", "[0-9]+\\.[0-9]+", TOKEN_FLOAT},
{"number", "(0x[0-9a-fA-F]+)|([0-9a-fA-F]+h)|(0b[01]+)|(0o[1-7]+)|([01]+b)|([0-9]+)", TOKEN_NUMBER},
{"string", "\\\"[^\\\"]*\\\"", TOKEN_STRING},
{"char", "\\\'\\\\?[^\\\']?\\\'", TOKEN_CHAR},
{"identifier", "[a-zA-Z_][a-zA-Z_0-9]*", TOKEN_IDENTIFIER},
{"line_comment", "//.*", TOKEN_LINE_COMMENT},
{"block_comment", "/\\*([^*]|\\*+[^*/])*\\*+/", TOKEN_BLOCK_COMMENT},
{"addassign", "\\+=", TOKEN_ADDASSIGN},
{"minusassign", "-=", TOKEN_MINUSASSIGN},
{"mulassign", "\\*=", TOKEN_MULASSIGN},
{"divassign", "/=", TOKEN_DIVASSIGN},
{"modassign", "\\%=", TOKEN_MODASSIGN},
{"bitandassign", "&=", TOKEN_BITANDASSIGN},
{"bitorassign", "\\|=", TOKEN_BITORASSIGN},
{"shiftleftassign", "<<=", TOKEN_SHIFTLEFTASSIGN},
{"shiftrightassign", ">>=", TOKEN_SHIFTRIGHTASSIGN},
{"greaterequal", ">=", TOKEN_GREATEREQUAL},
{"lessequal", "<=", TOKEN_LESSEQUAL},
{"equal", "==", TOKEN_EQUAL},
{"assign", "=", TOKEN_ASSIGN},
{"unequal", "!=", TOKEN_UNEQUAL},
{"shiftleft", "<<", TOKEN_SHIFTLEFT},
{"shiftright", ">>", TOKEN_SHIFTRIGHT},
{"or", "\\|\\|", TOKEN_OR},
{"greaterthan", ">", TOKEN_GREATERTHAN},
{"lessthan", "<", TOKEN_LESSTHAN},
{"add", "\\+", TOKEN_ADD},
{"minus", "-", TOKEN_MINUS},
{"star", "\\*", TOKEN_STAR},
{"slash", "/", TOKEN_SLASH},
{"percent", "\\%", TOKEN_PERCENT},
{"property", "\\.", TOKEN_PROPERTY},
{"openparen", "\\(", TOKEN_OPENPAREN},
{"closedparen", "\\)", TOKEN_CLOSEDPAREN},
{"and", "&&", TOKEN_AND},
{"not", "\\!", TOKEN_NOT},
{"bitand", "&", TOKEN_BITAND},
{"bitor", "\\|", TOKEN_BITOR},
{"bitnot", "~", TOKEN_BITNOT},
{"bitxor", "\\^", TOKEN_BITXOR},
{"comma", "\\,", TOKEN_COMMA},
{"open_squaredbracket", "\\[", TOKEN_OPEN_SQUAREDBRACKET},
{"closed_squaredbracket", "\\]", TOKEN_CLOSED_SQUAREDBRACKET},
{"openbracket", "\\{", TOKEN_OPENBRACKET},
{"closedbracket", "\\}", TOKEN_CLOSEDBRACKET},
{"semicolon", ";", TOKEN_SEMICOLON},
{"colon", ":", TOKEN_COLON},
{"whitespace", "\\s+", TOKEN_WHITESPACE},

};

lexer_result_t do_lex(std::string str){
    std::vector<token_t> tokens;
    long slen=str.length();
    long ptr=0;
    int line=0,column=0;
    bool success=true;
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
                token_t tok={rule.tok_type, v, line, column};
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
            success=false;
            printf("lexer error: failed to parse token at line %d, column %d\n",line+1,column+1);
            // move 1 forward to skip
            if(str[ptr]=='\n'){
                line++;
                column=0;
            }else {
                column++;
            }
            ptr++;
        }
    }

    // remove comments and whitespace tokens
    std::vector<token_t> filtered_tokens;
    for (auto &tok : tokens) {
        if(BELONGS_TO_CATEGORY_COMMENT(tok.token_type)||BELONGS_TO_CATEGORY_WHITESPACE(tok.token_type)){
            continue;
        }
        filtered_tokens.push_back(tok);
    }
    tokenstream_t ts(filtered_tokens);
    return lexer_result_t{success, std::move(ts)};
}
