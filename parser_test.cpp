
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

class factor_t{
public:
virtual node_type_t get_kind()=0;
};

class expr_t{
public:
virtual node_type_t get_kind()=0;
};

class lvalue_t{
public:
virtual node_type_t get_kind()=0;
};

class composed_type_t{
public:
virtual node_type_t get_kind()=0;
};

class definition_t{
public:
virtual node_type_t get_kind()=0;
};

class else_t{
public:
virtual node_type_t get_kind()=0;
};

class elseif_t{
public:
virtual node_type_t get_kind()=0;
};

class elseif_else_t{
public:
virtual node_type_t get_kind()=0;
};

class if_t{
public:
virtual node_type_t get_kind()=0;
};

class while_t{
public:
virtual node_type_t get_kind()=0;
};

class structmembers_t{
public:
virtual node_type_t get_kind()=0;
};

class struct_t{
public:
virtual node_type_t get_kind()=0;
};

class declaration_t{
public:
virtual node_type_t get_kind()=0;
};

class statement_t{
public:
virtual node_type_t get_kind()=0;
};

class statements_t{
public:
virtual node_type_t get_kind()=0;
};

class func_returntype_t{
public:
virtual node_type_t get_kind()=0;
};

class arglist_nonempty_t{
public:
virtual node_type_t get_kind()=0;
};

class arglist_t{
public:
virtual node_type_t get_kind()=0;
};

class function_t{
public:
virtual node_type_t get_kind()=0;
};

class factor_id_t:factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_num_t:factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_ch_t:factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class factor_str_t:factor_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_FACTOR;}
};

class expr_fac_t:expr_t{
public:
factor_t* left;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_assign_t:expr_t{
public:
lvalue_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_singop_t:expr_t{
public:
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_paren_t:expr_t{
public:
expr_t* left;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_biop_t:expr_t{
public:
expr_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class expr_call_t:expr_t{
public:
expr_t* left;
token_t* op;
expr_t* right;

node_type_t get_kind(){return NODE_EXPR;}
};

class lvalue_id_t:lvalue_t{
public:
token_t* value;

node_type_t get_kind(){return NODE_LVALUE;}
};

class lvalue_deref_t:lvalue_t{
public:
token_t* op;
expr_t* value;

node_type_t get_kind(){return NODE_LVALUE;}
};

class lvalue_visit_t:lvalue_t{
public:
expr_t* left;
token_t* op;
token_t* right;

node_type_t get_kind(){return NODE_LVALUE;}
};

class composed_type_raw_type_t:composed_type_t{
public:
token_t* inner_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_paren_t:composed_type_t{
public:
composed_type_t* inner_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_ptr_t:composed_type_t{
public:
composed_type_t* pointer_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_nsizedarr_t:composed_type_t{
public:
composed_type_t* element_type;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class composed_type_sizedarr_t:composed_type_t{
public:
composed_type_t* element_type;
expr_t* array_size;

node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};

class definition_deftype_t:definition_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_DEFINITION;}
};

class definition_defntype_t:definition_t{
public:
token_t* name;
expr_t* value;

node_type_t get_kind(){return NODE_DEFINITION;}
};

class else_default_t:else_t{
public:
token_t* statements;

node_type_t get_kind(){return NODE_ELSE;}
};

class elseif_default_t:elseif_t{
public:
token_t* condition;
token_t* statements;

node_type_t get_kind(){return NODE_ELSEIF;}
};

class elseif_else_onlyelse_t:elseif_else_t{
public:
else_t* else_block;

node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};

class elseif_else_chain_t:elseif_else_t{
public:
elseif_t* elseif_block;
elseif_else_t* rest_block;

node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};

class if_default_t:if_t{
public:
expr_t* condition;
statements_t* statements;
elseif_else_t* rest_block;

node_type_t get_kind(){return NODE_IF;}
};

class while_default_t:while_t{
public:
expr_t* condition;
statements_t* statements;

node_type_t get_kind(){return NODE_WHILE;}
};

class structmembers_singmem_t:structmembers_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};

class structmembers_multimem_t:structmembers_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};

class struct_default_t:struct_t{
public:
token_t* name;
structmembers_t* members;

node_type_t get_kind(){return NODE_STRUCT;}
};

class declaration_varntype_t:declaration_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_var_t:declaration_t{
public:
token_t* name;
composed_type_t* def_type;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_fn_t:declaration_t{
public:
token_t* name;
arglist_t* args;
func_returntype_t* return_type;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class declaration_struct_t:declaration_t{
public:
token_t* name;
structmembers_t* members;

node_type_t get_kind(){return NODE_DECLARATION;}
};

class statement_expr_t:statement_t{
public:
expr_t* expr;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_definition_t:statement_t{
public:
definition_t* def;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_if_t:statement_t{
public:
if_t* if_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_while_t:statement_t{
public:
while_t* while_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statement_declaration_t:statement_t{
public:
declaration_t* decl_stmt;

node_type_t get_kind(){return NODE_STATEMENT;}
};

class statements_stmt_t:statements_t{
public:
statement_t* stmt;

node_type_t get_kind(){return NODE_STATEMENTS;}
};

class statements_multistmt_t:statements_t{
public:
statement_t* stmt;
statements_t* other_stmts;

node_type_t get_kind(){return NODE_STATEMENTS;}
};

class func_returntype_hastype_t:func_returntype_t{
public:
composed_type_t* return_type;

node_type_t get_kind(){return NODE_FUNC_RETURNTYPE;}
};

class arglist_nonempty_singarg_t:arglist_nonempty_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};

class arglist_nonempty_multiarg_t:arglist_nonempty_t{
public:
token_t* name;

node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};

class arglist_hasarg_t:arglist_t{
public:
arglist_nonempty_t* args;

node_type_t get_kind(){return NODE_ARGLIST;}
};

class function_default_t:function_t{
public:
arglist_t* args;
func_returntype_t* return_type;
statements_t* stmts;

node_type_t get_kind(){return NODE_FUNCTION;}
};

typedef struct{
    char* name;
    int recipe_size;
    node_type_t recipe[9];
}parser_rule_t;

parser_rule_t parser_rules[]={
{.name="id", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="num", .recipe_size=1, recipe={NODE_NUMBER}},
{.name="ch", .recipe_size=1, recipe={NODE_CHAR}},
{.name="str", .recipe_size=1, recipe={NODE_STRING}},
{.name="fac", .recipe_size=1, recipe={NODE_FACTOR}},
{.name="assign", .recipe_size=3, recipe={NODE_LVALUE, NODE_ASSIGN, NODE_EXPR}},
{.name="singop", .recipe_size=2, recipe={NODE_SINGLE_OP, NODE_EXPR}},
{.name="paren", .recipe_size=3, recipe={NODE_OPENPAREN, NODE_EXPR, NODE_CLOSEDPAREN}},
{.name="biop", .recipe_size=3, recipe={NODE_EXPR, NODE_BI_OP, NODE_EXPR}},
{.name="call", .recipe_size=4, recipe={NODE_EXPR, NODE_OPENPAREN, NODE_EXPR, NODE_CLOSEDPAREN}},
{.name="id", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="deref", .recipe_size=2, recipe={NODE_STAR, NODE_EXPR}},
{.name="visit", .recipe_size=3, recipe={NODE_EXPR, NODE_PROPERTY, NODE_IDENTIFIER}},
{.name="raw_type", .recipe_size=1, recipe={NODE_TYPEKW}},
{.name="paren", .recipe_size=3, recipe={NODE_OPENPAREN, NODE_COMPOSED_TYPE, NODE_CLOSEDPAREN}},
{.name="ptr", .recipe_size=2, recipe={NODE_COMPOSED_TYPE, NODE_STAR}},
{.name="nsizedarr", .recipe_size=3, recipe={NODE_COMPOSED_TYPE, NODE_OPEN_SQUAREDBRACKET, NODE_CLOSED_SQUAREDBRACKET}},
{.name="sizedarr", .recipe_size=4, recipe={NODE_COMPOSED_TYPE, NODE_OPEN_SQUAREDBRACKET, NODE_EXPR, NODE_CLOSED_SQUAREDBRACKET}},
{.name="deftype", .recipe_size=2, recipe={NODE_LET, NODE_IDENTIFIER}},
{.name="defntype", .recipe_size=4, recipe={NODE_LET, NODE_IDENTIFIER, NODE_ASSIGN, NODE_EXPR}},
{.name="default", .recipe_size=4, recipe={NODE_ELSE, NODE_OPENBRACKET, NODE_STATEMENTS, NODE_CLOSEDBRACKET}},
{.name="default", .recipe_size=4, recipe={NODE_ELSEIF, NODE_OPENBRACKET, NODE_STATEMENTS, NODE_CLOSEDBRACKET}},
{.name="onlyelse", .recipe_size=1, recipe={NODE_ELSE}},
{.name="chain", .recipe_size=2, recipe={NODE_ELSEIF, NODE_ELSEIF_ELSE}},
{.name="default", .recipe_size=6, recipe={NODE_IF, NODE_EXPR, NODE_OPENBRACKET, NODE_STATEMENTS, NODE_CLOSEDBRACKET, NODE_ELSEIF_ELSE}},
{.name="default", .recipe_size=5, recipe={NODE_WHILE, NODE_EXPR, NODE_OPENBRACKET, NODE_STATEMENTS, NODE_CLOSEDBRACKET}},
{.name="singmem", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="multimem", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="default", .recipe_size=5, recipe={NODE_STRUCT, NODE_IDENTIFIER, NODE_OPENBRACKET, NODE_STRUCTMEMBERS, NODE_CLOSEDBRACKET}},
{.name="varntype", .recipe_size=3, recipe={NODE_LET, NODE_IDENTIFIER, NODE_SEMICOLON}},
{.name="var", .recipe_size=5, recipe={NODE_LET, NODE_IDENTIFIER, NODE_COLON, NODE_COMPOSED_TYPE, NODE_SEMICOLON}},
{.name="fn", .recipe_size=7, recipe={NODE_FN, NODE_IDENTIFIER, NODE_OPENPAREN, NODE_ARGLIST, NODE_CLOSEDPAREN, NODE_FUNC_RETURNTYPE, NODE_SEMICOLON}},
{.name="struct", .recipe_size=5, recipe={NODE_STRUCT, NODE_IDENTIFIER, NODE_OPENBRACKET, NODE_STRUCTMEMBERS, NODE_CLOSEDBRACKET}},
{.name="expr", .recipe_size=2, recipe={NODE_EXPR, NODE_SEMICOLON}},
{.name="definition", .recipe_size=2, recipe={NODE_DEFINITION, NODE_SEMICOLON}},
{.name="if", .recipe_size=1, recipe={NODE_IF}},
{.name="while", .recipe_size=1, recipe={NODE_WHILE}},
{.name="declaration", .recipe_size=1, recipe={NODE_DECLARATION}},
{.name="stmt", .recipe_size=1, recipe={NODE_STATEMENT}},
{.name="multistmt", .recipe_size=2, recipe={NODE_STATEMENT, NODE_STATEMENTS}},
{.name="hastype", .recipe_size=3, recipe={NODE_MINUS, NODE_GREATERTHAN, NODE_COMPOSED_TYPE}},
{.name="singarg", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="multiarg", .recipe_size=1, recipe={NODE_IDENTIFIER}},
{.name="hasarg", .recipe_size=1, recipe={NODE_ARGLIST_NONEMPTY}},
{.name="default", .recipe_size=9, recipe={NODE_FN, NODE_IDENTIFIER, NODE_OPENPAREN, NODE_ARGLIST, NODE_CLOSEDPAREN, NODE_FUNC_RETURNTYPE, NODE_OPENBRACKET, NODE_STATEMENTS, NODE_CLOSEDBRACKET}},

};
    