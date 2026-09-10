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

typedef enum{
NODE_FACTOR,
NODE_EXPR,
NODE_LVALUE,
NODE_COMPOSED_TYPE,
NODE_DEFINITION,
NODE_ELSE,
NODE_ELSEIF,
NODE_ELSEIF_ELSE,
NODE_IF,
NODE_WHILE,
NODE_STRUCTMEMBERS,
NODE_STRUCT,
NODE_DECLARATION,
NODE_STATEMENT,
NODE_STATEMENTS,
NODE_FUNC_RETURNTYPE,
NODE_ARGLIST_NONEMPTY,
NODE_ARGLIST,
NODE_FUNCTION,

}node_type_t;

class factor_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class expr_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class lvalue_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class composed_type_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class definition_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class else_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class elseif_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class elseif_else_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class if_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class while_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class structmembers_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class struct_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class declaration_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class statement_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class statements_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class func_returntype_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class arglist_nonempty_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class arglist_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class function_t:public ast_node_t{
public:
virtual node_type_t get_kind()=0;
};

class factor_id_t:public factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_num_t:public factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_ch_t:public factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_str_t:public factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class expr_fac_t:public expr_t{
public:
factor_t* left;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_assign_t:public expr_t{
public:
lvalue_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_singop_t:public expr_t{
public:
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_paren_t:public expr_t{
public:
expr_t* left;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_biop_t:public expr_t{
public:
expr_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_call_t:public expr_t{
public:
expr_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class lvalue_id_t:public lvalue_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_LVALUE;}
};

class lvalue_deref_t:public lvalue_t{
public:
token_t* op;
expr_t* value;

node_type_t get_kind(){return NODE_LVALUE;}
};

class lvalue_visit_t:public lvalue_t{
public:
expr_t* left;
token_t* op;
token_t* right;

node_type_t get_kind(){return NODE_LVALUE;}
};

class composed_type_raw_type_t:public composed_type_t{
public:
token_t* inner_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_paren_t:public composed_type_t{
public:
composed_type_t* inner_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_ptr_t:public composed_type_t{
public:
composed_type_t* pointer_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_nsizedarr_t:public composed_type_t{
public:
composed_type_t* element_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_sizedarr_t:public composed_type_t{
public:
composed_type_t* element_type;
expr_t* array_size;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class definition_deftype_t:public definition_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_DEFINITION;}
};

class definition_defntype_t:public definition_t{
public:
token_t* name;
expr_t* value;

node_type_t get_kind(){return NODE_DEFINITION;}
};

class else_default_t:public else_t{
public:
token_t* statements;

node_type_t get_kind(){return NODE_ELSE;}
};

class elseif_default_t:public elseif_t{
public:
token_t* condition;
token_t* statements;

node_type_t get_kind(){return NODE_ELSEIF;}
};

class elseif_else_onlyelse_t:public elseif_else_t{
public:
else_t* else_block;

node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};

class elseif_else_chain_t:public elseif_else_t{
public:
elseif_t* elseif_block;
elseif_else_t* rest_block;

node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};

class if_default_t:public if_t{
public:
expr_t* condition;
statements_t* statements;
elseif_else_t* rest_block;

node_type_t get_kind(){return NODE_IF;}
};

class while_default_t:public while_t{
public:
expr_t* condition;
statements_t* statements;

node_type_t get_kind(){return NODE_WHILE;}
};

class structmembers_singmem_t:public structmembers_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};

class structmembers_multimem_t:public structmembers_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};

class struct_default_t:public struct_t{
public:
token_t* name;
structmembers_t* members;

node_type_t get_kind(){return NODE_STRUCT;}
};

class declaration_varntype_t:public declaration_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_var_t:public declaration_t{
public:
token_t* name;
composed_type_t* def_type;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_fn_t:public declaration_t{
public:
token_t* name;
arglist_t* args;
func_returntype_t* return_type;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_struct_t:public declaration_t{
public:
token_t* name;
structmembers_t* members;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class statement_expr_t:public statement_t{
public:
expr_t* expr;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_definition_t:public statement_t{
public:
definition_t* def;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_if_t:public statement_t{
public:
if_t* if_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_while_t:public statement_t{
public:
while_t* while_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_declaration_t:public statement_t{
public:
declaration_t* decl_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statements_stmt_t:public statements_t{
public:
statement_t* stmt;

node_type_t get_kind(){return NODE_STATEMENTS;}
};

class statements_multistmt_t:public statements_t{
public:
statement_t* stmt;
statements_t* other_stmts;

node_type_t get_kind(){return NODE_STATEMENTS;}
};

class func_returntype_hastype_t:public func_returntype_t{
public:
composed_type_t* return_type;

node_type_t get_kind(){return NODE_FUNC_RETURNTYPE;}
};

class arglist_nonempty_singarg_t:public arglist_nonempty_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};

class arglist_nonempty_multiarg_t:public arglist_nonempty_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};

class arglist_hasarg_t:public arglist_t{
public:
arglist_nonempty_t* args;

node_type_t get_kind(){return NODE_ARGLIST;}
};

class function_default_t:public function_t{
public:
arglist_t* args;
func_returntype_t* return_type;
statements_t* stmts;

node_type_t get_kind(){return NODE_FUNCTION;}
};

factor_id_t* parse_factor_id(tokenstream_t *tokenstream){
    factor_id_t* node=new factor_id_t();
    
    if(!(node->value=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
factor_num_t* parse_factor_num(tokenstream_t *tokenstream){
    factor_num_t* node=new factor_num_t();
    
    if(BELONGS_TO_CATEGORY_NUMBER(tokenstream->peek()->token_type)){
        node->value = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
factor_ch_t* parse_factor_ch(tokenstream_t *tokenstream){
    factor_ch_t* node=new factor_ch_t();
    
    if(BELONGS_TO_CATEGORY_CHAR(tokenstream->peek()->token_type)){
        node->value = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
factor_str_t* parse_factor_str(tokenstream_t *tokenstream){
    factor_str_t* node=new factor_str_t();
    
    if(BELONGS_TO_CATEGORY_STRING(tokenstream->peek()->token_type)){
        node->value = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
factor_t* parse_factor(tokenstream_t *tokenstream){
    factor_t* node;
    
if(node=parse_factor_id(tokenstream)){return node;}

if(node=parse_factor_num(tokenstream)){return node;}

if(node=parse_factor_ch(tokenstream)){return node;}

if(node=parse_factor_str(tokenstream)){return node;}

    return NULL;
}

expr_fac_t* parse_expr_fac(tokenstream_t *tokenstream){
    expr_fac_t* node=new expr_fac_t();
    
    if(!(node->left=parse_factor(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_assign_t* parse_expr_assign(tokenstream_t *tokenstream){
    expr_assign_t* node=new expr_assign_t();
    
    if(!(node->left=parse_lvalue(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!(node->op=parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return NULL;}


    if(!(node->right=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_singop_t* parse_expr_singop(tokenstream_t *tokenstream){
    expr_singop_t* node=new expr_singop_t();
    
    if(BELONGS_TO_CATEGORY_SINGLE_op(tokenstream->peek()->token_type)){
        node->op = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    if(!(node->right=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_paren_t* parse_expr_paren(tokenstream_t *tokenstream){
    expr_paren_t* node=new expr_paren_t();
    
    if(!parse_token(tokenstream,TOKEN_OPENPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->left=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDPAREN)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_biop_t* parse_expr_biop(tokenstream_t *tokenstream){
    expr_biop_t* node=new expr_biop_t();
    
    if(!(node->left=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(BELONGS_TO_CATEGORY_BI_op(tokenstream->peek()->token_type)){
        node->op = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    if(!(node->right=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_call_t* parse_expr_call(tokenstream_t *tokenstream){
    expr_call_t* node=new expr_call_t();
    
    if(!(node->left=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!(node->op=parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return NULL;}


    if(!(node->right=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDPAREN)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
expr_t* parse_expr(tokenstream_t *tokenstream){
    expr_t* node;
    
if(node=parse_expr_fac(tokenstream)){return node;}

if(node=parse_expr_assign(tokenstream)){return node;}

if(node=parse_expr_singop(tokenstream)){return node;}

if(node=parse_expr_paren(tokenstream)){return node;}

if(node=parse_expr_biop(tokenstream)){return node;}

if(node=parse_expr_call(tokenstream)){return node;}

    return NULL;
}

lvalue_id_t* parse_lvalue_id(tokenstream_t *tokenstream){
    lvalue_id_t* node=new lvalue_id_t();
    
    if(!(node->value=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
lvalue_deref_t* parse_lvalue_deref(tokenstream_t *tokenstream){
    lvalue_deref_t* node=new lvalue_deref_t();
    
    if(!(node->op=parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return NULL;}


    if(!(node->value=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
lvalue_visit_t* parse_lvalue_visit(tokenstream_t *tokenstream){
    lvalue_visit_t* node=new lvalue_visit_t();
    
    if(!(node->left=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!(node->op=parse_token(tokenstream,TOKEN_PROPERTY))){tokenstream->reset();delete node;return NULL;}


    if(!(node->right=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
lvalue_t* parse_lvalue(tokenstream_t *tokenstream){
    lvalue_t* node;
    
if(node=parse_lvalue_id(tokenstream)){return node;}

if(node=parse_lvalue_deref(tokenstream)){return node;}

if(node=parse_lvalue_visit(tokenstream)){return node;}

    return NULL;
}

composed_type_raw_type_t* parse_composed_type_raw_type(tokenstream_t *tokenstream){
    composed_type_raw_type_t* node=new composed_type_raw_type_t();
    
    if(BELONGS_TO_CATEGORY_TYPEKW(tokenstream->peek()->token_type)){
        node->inner_type = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
composed_type_paren_t* parse_composed_type_paren(tokenstream_t *tokenstream){
    composed_type_paren_t* node=new composed_type_paren_t();
    
    if(!parse_token(tokenstream,TOKEN_OPENPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->inner_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDPAREN)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
composed_type_ptr_t* parse_composed_type_ptr(tokenstream_t *tokenstream){
    composed_type_ptr_t* node=new composed_type_ptr_t();
    
    if(!(node->pointer_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_STAR)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
composed_type_nsizedarr_t* parse_composed_type_nsizedarr(tokenstream_t *tokenstream){
    composed_type_nsizedarr_t* node=new composed_type_nsizedarr_t();
    
    if(!(node->element_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
composed_type_sizedarr_t* parse_composed_type_sizedarr(tokenstream_t *tokenstream){
    composed_type_sizedarr_t* node=new composed_type_sizedarr_t();
    
    if(!(node->element_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->array_size=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
composed_type_t* parse_composed_type(tokenstream_t *tokenstream){
    composed_type_t* node;
    
if(node=parse_composed_type_raw_type(tokenstream)){return node;}

if(node=parse_composed_type_paren(tokenstream)){return node;}

if(node=parse_composed_type_ptr(tokenstream)){return node;}

if(node=parse_composed_type_nsizedarr(tokenstream)){return node;}

if(node=parse_composed_type_sizedarr(tokenstream)){return node;}

    return NULL;
}

definition_deftype_t* parse_definition_deftype(tokenstream_t *tokenstream){
    definition_deftype_t* node=new definition_deftype_t();
    
    if(!parse_token(tokenstream,TOKEN_LET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
definition_defntype_t* parse_definition_defntype(tokenstream_t *tokenstream){
    definition_defntype_t* node=new definition_defntype_t();
    
    if(!parse_token(tokenstream,TOKEN_LET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_ASSIGN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->value=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
definition_t* parse_definition(tokenstream_t *tokenstream){
    definition_t* node;
    
if(node=parse_definition_deftype(tokenstream)){return node;}

if(node=parse_definition_defntype(tokenstream)){return node;}

    return NULL;
}

else_default_t* parse_else_default(tokenstream_t *tokenstream){
    else_default_t* node=new else_default_t();
    
    if(!parse_token(tokenstream,TOKEN_ELSE)){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(BELONGS_TO_CATEGORY_statements(tokenstream->peek()->token_type)){
        node->statements = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
else_t* parse_else(tokenstream_t *tokenstream){
    else_t* node;
    
if(node=parse_else_default(tokenstream)){return node;}

    return NULL;
}

elseif_default_t* parse_elseif_default(tokenstream_t *tokenstream){
    elseif_default_t* node=new elseif_default_t();
    
    if(!parse_token(tokenstream,TOKEN_ELSEIF)){tokenstream->reset();delete node;return NULL;}


    if(!(node->condition=parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return NULL;}


    if(BELONGS_TO_CATEGORY_statements(tokenstream->peek()->token_type)){
        node->statements = tokenstream->consume();
    }else{tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
elseif_t* parse_elseif(tokenstream_t *tokenstream){
    elseif_t* node;
    
if(node=parse_elseif_default(tokenstream)){return node;}

    return NULL;
}

elseif_else_onlyelse_t* parse_elseif_else_onlyelse(tokenstream_t *tokenstream){
    elseif_else_onlyelse_t* node=new elseif_else_onlyelse_t();
    
    if(!(node->else_block=parse_else(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
elseif_else_chain_t* parse_elseif_else_chain(tokenstream_t *tokenstream){
    elseif_else_chain_t* node=new elseif_else_chain_t();
    
    if(!(node->elseif_block=parse_elseif(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!(node->rest_block=parse_elseif_else(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
elseif_else_t* parse_elseif_else(tokenstream_t *tokenstream){
    elseif_else_t* node;
    
if(node=parse_elseif_else_onlyelse(tokenstream)){return node;}

if(node=parse_elseif_else_chain(tokenstream)){return node;}

    return NULL;
}

if_default_t* parse_if_default(tokenstream_t *tokenstream){
    if_default_t* node=new if_default_t();
    
    if(!parse_token(tokenstream,TOKEN_IF)){tokenstream->reset();delete node;return NULL;}


    if(!(node->condition=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->statements=parse_statements(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->rest_block=parse_elseif_else(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
if_t* parse_if(tokenstream_t *tokenstream){
    if_t* node;
    
if(node=parse_if_default(tokenstream)){return node;}

    return NULL;
}

while_default_t* parse_while_default(tokenstream_t *tokenstream){
    while_default_t* node=new while_default_t();
    
    if(!parse_token(tokenstream,TOKEN_WHILE)){tokenstream->reset();delete node;return NULL;}


    if(!(node->condition=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->statements=parse_statements(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
while_t* parse_while(tokenstream_t *tokenstream){
    while_t* node;
    
if(node=parse_while_default(tokenstream)){return node;}

    return NULL;
}

structmembers_singmem_t* parse_structmembers_singmem(tokenstream_t *tokenstream){
    structmembers_singmem_t* node=new structmembers_singmem_t();
    
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
structmembers_multimem_t* parse_structmembers_multimem(tokenstream_t *tokenstream){
    structmembers_multimem_t* node=new structmembers_multimem_t();
    
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
structmembers_t* parse_structmembers(tokenstream_t *tokenstream){
    structmembers_t* node;
    
if(node=parse_structmembers_singmem(tokenstream)){return node;}

if(node=parse_structmembers_multimem(tokenstream)){return node;}

    return NULL;
}

struct_default_t* parse_struct_default(tokenstream_t *tokenstream){
    struct_default_t* node=new struct_default_t();
    
    if(!parse_token(tokenstream,TOKEN_STRUCT)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->members=parse_structmembers(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
struct_t* parse_struct(tokenstream_t *tokenstream){
    struct_t* node;
    
if(node=parse_struct_default(tokenstream)){return node;}

    return NULL;
}

declaration_varntype_t* parse_declaration_varntype(tokenstream_t *tokenstream){
    declaration_varntype_t* node=new declaration_varntype_t();
    
    if(!parse_token(tokenstream,TOKEN_LET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_SEMICOLON)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
declaration_var_t* parse_declaration_var(tokenstream_t *tokenstream){
    declaration_var_t* node=new declaration_var_t();
    
    if(!parse_token(tokenstream,TOKEN_LET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_COLON)){tokenstream->reset();delete node;return NULL;}


    if(!(node->def_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_SEMICOLON)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
declaration_fn_t* parse_declaration_fn(tokenstream_t *tokenstream){
    declaration_fn_t* node=new declaration_fn_t();
    
    if(!parse_token(tokenstream,TOKEN_FN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->args=parse_arglist(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->return_type=parse_func_returntype(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_SEMICOLON)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
declaration_struct_t* parse_declaration_struct(tokenstream_t *tokenstream){
    declaration_struct_t* node=new declaration_struct_t();
    
    if(!parse_token(tokenstream,TOKEN_STRUCT)){tokenstream->reset();delete node;return NULL;}


    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->members=parse_structmembers(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
declaration_t* parse_declaration(tokenstream_t *tokenstream){
    declaration_t* node;
    
if(node=parse_declaration_varntype(tokenstream)){return node;}

if(node=parse_declaration_var(tokenstream)){return node;}

if(node=parse_declaration_fn(tokenstream)){return node;}

if(node=parse_declaration_struct(tokenstream)){return node;}

    return NULL;
}

statement_expr_t* parse_statement_expr(tokenstream_t *tokenstream){
    statement_expr_t* node=new statement_expr_t();
    
    if(!(node->expr=parse_expr(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_SEMICOLON)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statement_definition_t* parse_statement_definition(tokenstream_t *tokenstream){
    statement_definition_t* node=new statement_definition_t();
    
    if(!(node->def=parse_definition(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_SEMICOLON)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statement_if_t* parse_statement_if(tokenstream_t *tokenstream){
    statement_if_t* node=new statement_if_t();
    
    if(!(node->if_stmt=parse_if(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statement_while_t* parse_statement_while(tokenstream_t *tokenstream){
    statement_while_t* node=new statement_while_t();
    
    if(!(node->while_stmt=parse_while(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statement_declaration_t* parse_statement_declaration(tokenstream_t *tokenstream){
    statement_declaration_t* node=new statement_declaration_t();
    
    if(!(node->decl_stmt=parse_declaration(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statement_t* parse_statement(tokenstream_t *tokenstream){
    statement_t* node;
    
if(node=parse_statement_expr(tokenstream)){return node;}

if(node=parse_statement_definition(tokenstream)){return node;}

if(node=parse_statement_if(tokenstream)){return node;}

if(node=parse_statement_while(tokenstream)){return node;}

if(node=parse_statement_declaration(tokenstream)){return node;}

    return NULL;
}

statements_stmt_t* parse_statements_stmt(tokenstream_t *tokenstream){
    statements_stmt_t* node=new statements_stmt_t();
    
    if(!(node->stmt=parse_statement(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statements_multistmt_t* parse_statements_multistmt(tokenstream_t *tokenstream){
    statements_multistmt_t* node=new statements_multistmt_t();
    
    if(!(node->stmt=parse_statement(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!(node->other_stmts=parse_statements(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
statements_t* parse_statements(tokenstream_t *tokenstream){
    statements_t* node;
    
if(node=parse_statements_stmt(tokenstream)){return node;}

if(node=parse_statements_multistmt(tokenstream)){return node;}

    return NULL;
}

func_returntype_hastype_t* parse_func_returntype_hastype(tokenstream_t *tokenstream){
    func_returntype_hastype_t* node=new func_returntype_hastype_t();
    
    if(!parse_token(tokenstream,TOKEN_MINUS)){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_GREATERTHAN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->return_type=parse_composed_type(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
func_returntype_t* parse_func_returntype(tokenstream_t *tokenstream){
    func_returntype_t* node;
    
if(node=parse_func_returntype_hastype(tokenstream)){return node;}

    return NULL;
}

arglist_nonempty_singarg_t* parse_arglist_nonempty_singarg(tokenstream_t *tokenstream){
    arglist_nonempty_singarg_t* node=new arglist_nonempty_singarg_t();
    
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
arglist_nonempty_multiarg_t* parse_arglist_nonempty_multiarg(tokenstream_t *tokenstream){
    arglist_nonempty_multiarg_t* node=new arglist_nonempty_multiarg_t();
    
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
arglist_nonempty_t* parse_arglist_nonempty(tokenstream_t *tokenstream){
    arglist_nonempty_t* node;
    
if(node=parse_arglist_nonempty_singarg(tokenstream)){return node;}

if(node=parse_arglist_nonempty_multiarg(tokenstream)){return node;}

    return NULL;
}

arglist_hasarg_t* parse_arglist_hasarg(tokenstream_t *tokenstream){
    arglist_hasarg_t* node=new arglist_hasarg_t();
    
    if(!(node->args=parse_arglist_nonempty(tokenstream))){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
arglist_t* parse_arglist(tokenstream_t *tokenstream){
    arglist_t* node;
    
if(node=parse_arglist_hasarg(tokenstream)){return node;}

    return NULL;
}

function_default_t* parse_function_default(tokenstream_t *tokenstream){
    function_default_t* node=new function_default_t();
    
    if(!parse_token(tokenstream,TOKEN_FN)){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_IDENTIFIER)){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->args=parse_arglist(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDPAREN)){tokenstream->reset();delete node;return NULL;}


    if(!(node->return_type=parse_func_returntype(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_OPENBRACKET)){tokenstream->reset();delete node;return NULL;}


    if(!(node->stmts=parse_statements(tokenstream))){tokenstream->reset();delete node;return NULL;}


    if(!parse_token(tokenstream,TOKEN_CLOSEDBRACKET)){tokenstream->reset();delete node;return NULL;}


    tokenstream->end_parsing();
    return node;
}
            
function_t* parse_function(tokenstream_t *tokenstream){
    function_t* node;
    
if(node=parse_function_default(tokenstream)){return node;}

    return NULL;
}

typedef struct{
    char* name;
    int (*parser)(tokenstream_t *ts, void* dest);
}parser_rule_t;

parser_rule_t parser_rules[]={
{.name="factor", .parser=parse_factor},
{.name="expr", .parser=parse_expr},
{.name="lvalue", .parser=parse_lvalue},
{.name="composed_type", .parser=parse_composed_type},
{.name="definition", .parser=parse_definition},
{.name="else", .parser=parse_else},
{.name="elseif", .parser=parse_elseif},
{.name="elseif_else", .parser=parse_elseif_else},
{.name="if", .parser=parse_if},
{.name="while", .parser=parse_while},
{.name="structmembers", .parser=parse_structmembers},
{.name="struct", .parser=parse_struct},
{.name="declaration", .parser=parse_declaration},
{.name="statement", .parser=parse_statement},
{.name="statements", .parser=parse_statements},
{.name="func_returntype", .parser=parse_func_returntype},
{.name="arglist_nonempty", .parser=parse_arglist_nonempty},
{.name="arglist", .parser=parse_arglist},
{.name="function", .parser=parse_function},

};
    
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