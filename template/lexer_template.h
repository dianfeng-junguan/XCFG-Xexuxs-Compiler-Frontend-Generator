#pragma once
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>
#include <string>
{%}
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
        tokenstream_t(std::vector<token_t> tokens):ptrs(1, 0){
            for(auto &tok:tokens){
                this->tokens.push_back(std::make_unique<token_t>(tok));
            }
        }
        token_t *peek(){
            if(ptrs.back()>=tokens.size()){
                return NULL;
            }
            return tokens[ptrs.back()].get();
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
            token_t *token=tokens[ptrs.back()++].get();
            return token;
        }
        bool eof(){
            return ptrs.back()>=tokens.size();
        }
    private:
        std::vector<std::unique_ptr<token_t>> tokens;
        std::vector<long> ptrs;
};
typedef struct{
    bool success;
    tokenstream_t tokenstream;
}lexer_result_t;