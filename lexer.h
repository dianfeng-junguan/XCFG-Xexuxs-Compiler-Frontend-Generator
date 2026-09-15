#pragma once
#include <cassert>
#include <vector>
#include <string>

typedef enum{
TOKEN_LET,
TOKEN_FN,
TOKEN_IF,
TOKEN_ELSE,
TOKEN_WHILE,
TOKEN_BREAK,
TOKEN_RETURN,
TOKEN_CONTINUE,
TOKEN_INCLUDE,
TOKEN_INT,
TOKEN_STRING_TYPEKW,
TOKEN_CHAR_TYPEKW,
TOKEN_VOID,
TOKEN_STRUCT,
TOKEN_NUMBER,
TOKEN_FLOAT,
TOKEN_STRING,
TOKEN_CHAR,
TOKEN_IDENTIFIER,
TOKEN_ADDASSIGN,
TOKEN_MINUSASSIGN,
TOKEN_MULASSIGN,
TOKEN_DIVASSIGN,
TOKEN_MODASSIGN,
TOKEN_BITANDASSIGN,
TOKEN_BITORASSIGN,
TOKEN_SHIFTLEFTASSIGN,
TOKEN_SHIFTRIGHTASSIGN,
TOKEN_GREATEREQUAL,
TOKEN_LESSEQUAL,
TOKEN_EQUAL,
TOKEN_ASSIGN,
TOKEN_UNEQUAL,
TOKEN_SHIFTLEFT,
TOKEN_SHIFTRIGHT,
TOKEN_OR,
TOKEN_GREATERTHAN,
TOKEN_LESSTHAN,
TOKEN_ADD,
TOKEN_MINUS,
TOKEN_STAR,
TOKEN_SLASH,
TOKEN_PERCENT,
TOKEN_PROPERTY,
TOKEN_OPENPAREN,
TOKEN_CLOSEDPAREN,
TOKEN_AND,
TOKEN_NOT,
TOKEN_BITAND,
TOKEN_BITOR,
TOKEN_BITNOT,
TOKEN_BITXOR,
TOKEN_COMMA,
TOKEN_OPEN_SQUAREDBRACKET,
TOKEN_CLOSED_SQUAREDBRACKET,
TOKEN_OPENBRACKET,
TOKEN_CLOSEDBRACKET,
TOKEN_SEMICOLON,
TOKEN_COLON,
TOKEN_LINE_COMMENT,
TOKEN_BLOCK_COMMENT,
TOKEN_WHITESPACE,

}token_type_t;
    
#define BELONGS_TO_CATEGORY_KEYWORDS(toktype) (toktype==TOKEN_LET||toktype==TOKEN_FN||toktype==TOKEN_IF||toktype==TOKEN_ELSE||toktype==TOKEN_WHILE||toktype==TOKEN_BREAK||toktype==TOKEN_RETURN||toktype==TOKEN_CONTINUE||toktype==TOKEN_INCLUDE)
        
#define BELONGS_TO_CATEGORY_TYPEKW(toktype) (toktype==TOKEN_INT||toktype==TOKEN_STRING_TYPEKW||toktype==TOKEN_CHAR_TYPEKW||toktype==TOKEN_VOID||toktype==TOKEN_STRUCT)
        
#define BELONGS_TO_CATEGORY_NUMBER(toktype) (toktype==TOKEN_NUMBER||toktype==TOKEN_FLOAT)
        
#define BELONGS_TO_CATEGORY_STRING(toktype) (toktype==TOKEN_STRING)
        
#define BELONGS_TO_CATEGORY_CHAR(toktype) (toktype==TOKEN_CHAR)
        
#define BELONGS_TO_CATEGORY_IDENTIFIER(toktype) (toktype==TOKEN_IDENTIFIER)
        
#define BELONGS_TO_CATEGORY_OPERATOR(toktype) (toktype==TOKEN_ADDASSIGN||toktype==TOKEN_MINUSASSIGN||toktype==TOKEN_MULASSIGN||toktype==TOKEN_DIVASSIGN||toktype==TOKEN_MODASSIGN||toktype==TOKEN_BITANDASSIGN||toktype==TOKEN_BITORASSIGN||toktype==TOKEN_SHIFTLEFTASSIGN||toktype==TOKEN_SHIFTRIGHTASSIGN||toktype==TOKEN_GREATEREQUAL||toktype==TOKEN_LESSEQUAL||toktype==TOKEN_EQUAL||toktype==TOKEN_ASSIGN||toktype==TOKEN_UNEQUAL||toktype==TOKEN_SHIFTLEFT||toktype==TOKEN_SHIFTRIGHT||toktype==TOKEN_OR||toktype==TOKEN_GREATERTHAN||toktype==TOKEN_LESSTHAN||toktype==TOKEN_ADD||toktype==TOKEN_MINUS||toktype==TOKEN_STAR||toktype==TOKEN_SLASH||toktype==TOKEN_PERCENT||toktype==TOKEN_PROPERTY||toktype==TOKEN_OPENPAREN||toktype==TOKEN_CLOSEDPAREN||toktype==TOKEN_AND||toktype==TOKEN_NOT||toktype==TOKEN_BITAND||toktype==TOKEN_BITOR||toktype==TOKEN_BITNOT||toktype==TOKEN_BITXOR||toktype==TOKEN_COMMA||toktype==TOKEN_OPEN_SQUAREDBRACKET||toktype==TOKEN_CLOSED_SQUAREDBRACKET)
        
#define BELONGS_TO_CATEGORY_BI_OPERATOR(toktype) (toktype==TOKEN_ADD||toktype==TOKEN_MINUS||toktype==TOKEN_STAR||toktype==TOKEN_SLASH||toktype==TOKEN_AND||toktype==TOKEN_OR||toktype==TOKEN_NOT||toktype==TOKEN_BITAND||toktype==TOKEN_BITOR||toktype==TOKEN_BITXOR||toktype==TOKEN_PROPERTY||toktype==TOKEN_PERCENT||toktype==TOKEN_UNEQUAL||toktype==TOKEN_GREATERTHAN||toktype==TOKEN_LESSTHAN||toktype==TOKEN_GREATEREQUAL||toktype==TOKEN_LESSEQUAL||toktype==TOKEN_SHIFTLEFT||toktype==TOKEN_SHIFTRIGHT||toktype==TOKEN_ADDASSIGN||toktype==TOKEN_MINUSASSIGN||toktype==TOKEN_MULASSIGN||toktype==TOKEN_DIVASSIGN||toktype==TOKEN_MODASSIGN||toktype==TOKEN_BITANDASSIGN||toktype==TOKEN_BITORASSIGN||toktype==TOKEN_SHIFTLEFTASSIGN||toktype==TOKEN_SHIFTRIGHTASSIGN)
        
#define BELONGS_TO_CATEGORY_SINGLE_OPERATOR(toktype) (toktype==TOKEN_ADD||toktype==TOKEN_MINUS||toktype==TOKEN_STAR||toktype==TOKEN_NOT||toktype==TOKEN_BITNOT||toktype==TOKEN_BITAND)
        
#define BELONGS_TO_CATEGORY_SEPARATOR(toktype) (toktype==TOKEN_OPENBRACKET||toktype==TOKEN_CLOSEDBRACKET||toktype==TOKEN_SEMICOLON||toktype==TOKEN_COLON)
        
#define BELONGS_TO_CATEGORY_COMMENT(toktype) (toktype==TOKEN_LINE_COMMENT||toktype==TOKEN_BLOCK_COMMENT)
        
#define BELONGS_TO_CATEGORY_WHITESPACE(toktype) (toktype==TOKEN_WHITESPACE)
        
typedef struct lexer_rule_t{
    const char* name;
    const char* pattern;
    token_type_t tok_type;
}lexer_rule_t;
typedef struct _token_t{
    token_type_t token_type;
    std::string value;
    int line;
    int column;
}token_t;
class tokenstream_t{
    public:
        tokenstream_t(std::vector<token_t> tokens):tokens(tokens),ptrs(1, 0){}
        token_t *peek(){
            if(ptrs.back()>=tokens.size()){
                return NULL;
            }
            return &tokens[ptrs.back()];
        }
        void next(){
            assert(ptrs.size()>0);
            ptrs.back()++;
        }
        void begin_parsing(){
            ptrs.push_back(ptrs.back());
        }
        void end_parsing(){
            assert(ptrs.size()>=2);
            long last_ptr=ptrs.back();
            ptrs.pop_back();
            ptrs.back()=last_ptr;
        }
        void reset(){
            assert(ptrs.size()>=2);
            ptrs.pop_back();
        }
        token_t *consume(){
            if(ptrs.back()>=tokens.size()){
                return NULL;
            }
            token_t *token=&tokens[ptrs.back()++];
            return token;
        }
        bool eof(){
            return ptrs.back()>=tokens.size();
        }
    private:
        std::vector<token_t> tokens;
        std::vector<long> ptrs;
};