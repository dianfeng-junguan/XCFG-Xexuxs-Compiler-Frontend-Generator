#include <vector>

{%}
typedef struct lexer_rule_t{
    char* name;
    char* pattern;
    token_type_t tok_type;
}lexer_rule_t;
typedef struct _token_t{
    token_type_t token_type;
    char* value;
    int line;
    int column;
}token_t;
class tokenstream_t{
    public:
        tokenstream_t(std::vector<token_t> tokens):tokens(tokens),ptr(0),buffer_ptr(0){}
        token_t *peek(){
            if(ptr>=tokens.size()){
                return NULL;
            }
            return &tokens[buffer_ptr];
        }
        void next(){
            buffer_ptr++;
        }
        void end_parsing(){
            ptr=buffer_ptr;
        }
        void reset(){
            buffer_ptr=ptr;
        }
        token_t *consume(){
            if(ptr>=tokens.size()){
                return NULL;
            }
            token_t *token=&tokens[buffer_ptr++];
            return token;
        }
        bool eof(){
            return ptr>=tokens.size();
        }
    private:
        std::vector<token_t> tokens;
        long ptr;
        long buffer_ptr;
};