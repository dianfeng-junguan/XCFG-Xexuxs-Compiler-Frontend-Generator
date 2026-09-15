#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>
#include "lexer.h"

    
#define LEXER_RULES_LEN 62
lexer_rule_t lexer_rules[]={
    {.name=(const char*)"let",.pattern=(const char*)"\\blet\\b",.tok_type=TOKEN_LET},
{.name=(const char*)"fn",.pattern=(const char*)"\\bfn\\b",.tok_type=TOKEN_FN},
{.name=(const char*)"if",.pattern=(const char*)"\\bif\\b",.tok_type=TOKEN_IF},
{.name=(const char*)"else",.pattern=(const char*)"\\belse\\b",.tok_type=TOKEN_ELSE},
{.name=(const char*)"while",.pattern=(const char*)"\\bwhile\\b",.tok_type=TOKEN_WHILE},
{.name=(const char*)"break",.pattern=(const char*)"\\bbreak\\b",.tok_type=TOKEN_BREAK},
{.name=(const char*)"return",.pattern=(const char*)"\\breturn\\b",.tok_type=TOKEN_RETURN},
{.name=(const char*)"continue",.pattern=(const char*)"\\bcontinue\\b",.tok_type=TOKEN_CONTINUE},
{.name=(const char*)"include",.pattern=(const char*)"\\binclude\\b",.tok_type=TOKEN_INCLUDE},
{.name=(const char*)"int",.pattern=(const char*)"\\bint\\b",.tok_type=TOKEN_INT},
{.name=(const char*)"string_typekw",.pattern=(const char*)"\\bstring\\b",.tok_type=TOKEN_STRING_TYPEKW},
{.name=(const char*)"char_typekw",.pattern=(const char*)"\\bchar\\b",.tok_type=TOKEN_CHAR_TYPEKW},
{.name=(const char*)"void",.pattern=(const char*)"\\bvoid\\b",.tok_type=TOKEN_VOID},
{.name=(const char*)"struct",.pattern=(const char*)"\\bstruct\\b",.tok_type=TOKEN_STRUCT},
{.name=(const char*)"number",.pattern=(const char*)"(0x[0-9a-fA-F]+)|([0-9a-fA-F]+h)|(0b[01]+)|(0o[1-7]+)|([01]+b)|([0-9]+)",.tok_type=TOKEN_NUMBER},
{.name=(const char*)"float",.pattern=(const char*)"[0-9]+.[0-9]+",.tok_type=TOKEN_FLOAT},
{.name=(const char*)"string",.pattern=(const char*)"\\\"[^\\\"]*\\\"",.tok_type=TOKEN_STRING},
{.name=(const char*)"char",.pattern=(const char*)"\\\'\\\\?[^\\\']?\\\'",.tok_type=TOKEN_CHAR},
{.name=(const char*)"identifier",.pattern=(const char*)"[a-zA-Z_][a-zA-Z_0-9]*",.tok_type=TOKEN_IDENTIFIER},
{.name=(const char*)"addassign",.pattern=(const char*)"\\+=",.tok_type=TOKEN_ADDASSIGN},
{.name=(const char*)"minusassign",.pattern=(const char*)"-=",.tok_type=TOKEN_MINUSASSIGN},
{.name=(const char*)"mulassign",.pattern=(const char*)"\\*=",.tok_type=TOKEN_MULASSIGN},
{.name=(const char*)"divassign",.pattern=(const char*)"/=",.tok_type=TOKEN_DIVASSIGN},
{.name=(const char*)"modassign",.pattern=(const char*)"\\%=",.tok_type=TOKEN_MODASSIGN},
{.name=(const char*)"bitandassign",.pattern=(const char*)"&=",.tok_type=TOKEN_BITANDASSIGN},
{.name=(const char*)"bitorassign",.pattern=(const char*)"\\|=",.tok_type=TOKEN_BITORASSIGN},
{.name=(const char*)"shiftleftassign",.pattern=(const char*)"<<=",.tok_type=TOKEN_SHIFTLEFTASSIGN},
{.name=(const char*)"shiftrightassign",.pattern=(const char*)">>=",.tok_type=TOKEN_SHIFTRIGHTASSIGN},
{.name=(const char*)"greaterequal",.pattern=(const char*)">=",.tok_type=TOKEN_GREATEREQUAL},
{.name=(const char*)"lessequal",.pattern=(const char*)"<=",.tok_type=TOKEN_LESSEQUAL},
{.name=(const char*)"equal",.pattern=(const char*)"==",.tok_type=TOKEN_EQUAL},
{.name=(const char*)"assign",.pattern=(const char*)"=",.tok_type=TOKEN_ASSIGN},
{.name=(const char*)"unequal",.pattern=(const char*)"!=",.tok_type=TOKEN_UNEQUAL},
{.name=(const char*)"shiftleft",.pattern=(const char*)"<<",.tok_type=TOKEN_SHIFTLEFT},
{.name=(const char*)"shiftright",.pattern=(const char*)">>",.tok_type=TOKEN_SHIFTRIGHT},
{.name=(const char*)"or",.pattern=(const char*)"\\|\\|",.tok_type=TOKEN_OR},
{.name=(const char*)"greaterthan",.pattern=(const char*)">",.tok_type=TOKEN_GREATERTHAN},
{.name=(const char*)"lessthan",.pattern=(const char*)"<",.tok_type=TOKEN_LESSTHAN},
{.name=(const char*)"add",.pattern=(const char*)"\\+",.tok_type=TOKEN_ADD},
{.name=(const char*)"minus",.pattern=(const char*)"-",.tok_type=TOKEN_MINUS},
{.name=(const char*)"star",.pattern=(const char*)"\\*",.tok_type=TOKEN_STAR},
{.name=(const char*)"slash",.pattern=(const char*)"/",.tok_type=TOKEN_SLASH},
{.name=(const char*)"percent",.pattern=(const char*)"\\%",.tok_type=TOKEN_PERCENT},
{.name=(const char*)"property",.pattern=(const char*)"\\.",.tok_type=TOKEN_PROPERTY},
{.name=(const char*)"openparen",.pattern=(const char*)"\\(",.tok_type=TOKEN_OPENPAREN},
{.name=(const char*)"closedparen",.pattern=(const char*)"\\)",.tok_type=TOKEN_CLOSEDPAREN},
{.name=(const char*)"and",.pattern=(const char*)"&&",.tok_type=TOKEN_AND},
{.name=(const char*)"not",.pattern=(const char*)"\\!",.tok_type=TOKEN_NOT},
{.name=(const char*)"bitand",.pattern=(const char*)"&",.tok_type=TOKEN_BITAND},
{.name=(const char*)"bitor",.pattern=(const char*)"\\|",.tok_type=TOKEN_BITOR},
{.name=(const char*)"bitnot",.pattern=(const char*)"~",.tok_type=TOKEN_BITNOT},
{.name=(const char*)"bitxor",.pattern=(const char*)"\\^",.tok_type=TOKEN_BITXOR},
{.name=(const char*)"comma",.pattern=(const char*)"\\,",.tok_type=TOKEN_COMMA},
{.name=(const char*)"open_squaredbracket",.pattern=(const char*)"\\[",.tok_type=TOKEN_OPEN_SQUAREDBRACKET},
{.name=(const char*)"closed_squaredbracket",.pattern=(const char*)"\\]",.tok_type=TOKEN_CLOSED_SQUAREDBRACKET},
{.name=(const char*)"openbracket",.pattern=(const char*)"\\{",.tok_type=TOKEN_OPENBRACKET},
{.name=(const char*)"closedbracket",.pattern=(const char*)"\\}",.tok_type=TOKEN_CLOSEDBRACKET},
{.name=(const char*)"semicolon",.pattern=(const char*)";",.tok_type=TOKEN_SEMICOLON},
{.name=(const char*)"colon",.pattern=(const char*)":",.tok_type=TOKEN_COLON},
{.name=(const char*)"line_comment",.pattern=(const char*)"//.*",.tok_type=TOKEN_LINE_COMMENT},
{.name=(const char*)"block_comment",.pattern=(const char*)"/\\*(.|\\n)*\\*/",.tok_type=TOKEN_BLOCK_COMMENT},
{.name=(const char*)"whitespace",.pattern=(const char*)"\\s+",.tok_type=TOKEN_WHITESPACE},

};

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