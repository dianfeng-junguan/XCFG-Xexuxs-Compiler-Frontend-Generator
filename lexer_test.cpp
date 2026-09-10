#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "lexer.h"

    
#define LEXER_RULES_LEN 3257
lexer_rule_t lexer_rules[]={
    {.name="let",.pattern="\\blet\\b",.tok_type=TOKEN_LET},
{.name="fn",.pattern="\\bfn\\b",.tok_type=TOKEN_FN},
{.name="if",.pattern="\\bif\\b",.tok_type=TOKEN_IF},
{.name="else",.pattern="\\belse\\b",.tok_type=TOKEN_ELSE},
{.name="while",.pattern="\\bwhile\\b",.tok_type=TOKEN_WHILE},
{.name="break",.pattern="\\bbreak\\b",.tok_type=TOKEN_BREAK},
{.name="return",.pattern="\\breturn\\b",.tok_type=TOKEN_RETURN},
{.name="include",.pattern="\\binclude\\b",.tok_type=TOKEN_INCLUDE},
{.name="int",.pattern="\\bint\\b",.tok_type=TOKEN_INT},
{.name="string_typekw",.pattern="\\bstring\\b",.tok_type=TOKEN_STRING_TYPEKW},
{.name="char_typekw",.pattern="\\bchar\\b",.tok_type=TOKEN_CHAR_TYPEKW},
{.name="void",.pattern="\\bvoid\\b",.tok_type=TOKEN_VOID},
{.name="struct",.pattern="\\bstruct\\b",.tok_type=TOKEN_STRUCT},
{.name="number",.pattern="(0x[0-9a-fA-F]+)|([0-9a-fA-F]+h)|(0b[01]+)|(0o[1-7]+)|([01]+b)|([0-9]+)",.tok_type=TOKEN_NUMBER},
{.name="float",.pattern="[0-9]+.[0-9]+",.tok_type=TOKEN_FLOAT},
{.name="string",.pattern="\\\"[^\\\"]*\\\"",.tok_type=TOKEN_STRING},
{.name="char",.pattern="\\\'\\\\?[^\\\']?\\\'",.tok_type=TOKEN_CHAR},
{.name="identifier",.pattern="[a-zA-Z_][a-zA-Z_0-9]*",.tok_type=TOKEN_IDENTIFIER},
{.name="add",.pattern="\\+",.tok_type=TOKEN_ADD},
{.name="minus",.pattern="-",.tok_type=TOKEN_MINUS},
{.name="star",.pattern="\\*",.tok_type=TOKEN_STAR},
{.name="slash",.pattern="/",.tok_type=TOKEN_SLASH},
{.name="percent",.pattern="\\%",.tok_type=TOKEN_PERCENT},
{.name="property",.pattern="\\.",.tok_type=TOKEN_PROPERTY},
{.name="openparen",.pattern="\\(",.tok_type=TOKEN_OPENPAREN},
{.name="closedparen",.pattern="\\)",.tok_type=TOKEN_CLOSEDPAREN},
{.name="and",.pattern="&&",.tok_type=TOKEN_AND},
{.name="or",.pattern="\\|\\|",.tok_type=TOKEN_OR},
{.name="not",.pattern="\\!",.tok_type=TOKEN_NOT},
{.name="bitand",.pattern="&",.tok_type=TOKEN_BITAND},
{.name="bitor",.pattern="|",.tok_type=TOKEN_BITOR},
{.name="bitnot",.pattern="~",.tok_type=TOKEN_BITNOT},
{.name="bitxor",.pattern="^",.tok_type=TOKEN_BITXOR},
{.name="shiftleft",.pattern="<<",.tok_type=TOKEN_SHIFTLEFT},
{.name="shiftright",.pattern=">>",.tok_type=TOKEN_SHIFTRIGHT},
{.name="comma",.pattern="\\,",.tok_type=TOKEN_COMMA},
{.name="open_squarebracket",.pattern="\\[",.tok_type=TOKEN_OPEN_SQUAREBRACKET},
{.name="closed_squarebracket",.pattern="\\]",.tok_type=TOKEN_CLOSED_SQUAREBRACKET},
{.name="greaterthan",.pattern=">",.tok_type=TOKEN_GREATERTHAN},
{.name="greaterequal",.pattern=">=",.tok_type=TOKEN_GREATEREQUAL},
{.name="lessequal",.pattern="<=",.tok_type=TOKEN_LESSEQUAL},
{.name="lessthan",.pattern="<",.tok_type=TOKEN_LESSTHAN},
{.name="equal",.pattern="==",.tok_type=TOKEN_EQUAL},
{.name="assign",.pattern="=",.tok_type=TOKEN_ASSIGN},
{.name="unequal",.pattern="!=",.tok_type=TOKEN_UNEQUAL},
{.name="openbracket",.pattern="\\{",.tok_type=TOKEN_OPENBRACKET},
{.name="closedbracket",.pattern="\\}",.tok_type=TOKEN_CLOSEDBRACKET},
{.name="semicolon",.pattern=";",.tok_type=TOKEN_SEMICOLON},
{.name="colon",.pattern=":",.tok_type=TOKEN_COLON},
{.name="line_comment",.pattern="//.*",.tok_type=TOKEN_LINE_COMMENT},
{.name="block_comment",.pattern="/\\*(.|\\n)*\\*/",.tok_type=TOKEN_BLOCK_COMMENT},
{.name="whitespace",.pattern="\\s+",.tok_type=TOKEN_WHITESPACE},

};

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