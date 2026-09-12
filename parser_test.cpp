#include <vector>
#include <stdio.h>
#include "lexer.h"
class ast_node_t{
public:
    virtual ~ast_node_t() = default;
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
NODE_GLUED_FACTOR,
NODE_SINGLE_OP_FACTOR,
NODE_POWER_FACTOR,
NODE_TERM,
NODE_EXPR,
NODE_LOGIC_EXPR_AND,
NODE_LOGIC_EXPR_OR,
NODE_LOGIC_EXPR_EQ,
NODE_ASSIGN_EXPR,
NODE_ULTIMATE_EXPR,
NODE_LVALUE_NOPROPERTY,
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
NODE_TOP_STATEMENT,

}node_type_t;
class factor_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~factor_t() = default;
};
class glued_factor_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~glued_factor_t() = default;
};
class single_op_factor_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~single_op_factor_t() = default;
};
class power_factor_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~power_factor_t() = default;
};
class term_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~term_t() = default;
};
class expr_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~expr_t() = default;
};
class logic_expr_and_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~logic_expr_and_t() = default;
};
class logic_expr_or_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~logic_expr_or_t() = default;
};
class logic_expr_eq_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~logic_expr_eq_t() = default;
};
class assign_expr_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~assign_expr_t() = default;
};
class ultimate_expr_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~ultimate_expr_t() = default;
};
class lvalue_noproperty_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~lvalue_noproperty_t() = default;
};
class lvalue_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~lvalue_t() = default;
};
class composed_type_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~composed_type_t() = default;
};
class definition_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~definition_t() = default;
};
class else_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~else_t() = default;
};
class elseif_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~elseif_t() = default;
};
class elseif_else_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~elseif_else_t() = default;
};
class if_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~if_t() = default;
};
class while_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~while_t() = default;
};
class structmembers_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~structmembers_t() = default;
};
class struct_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~struct_t() = default;
};
class declaration_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~declaration_t() = default;
};
class statement_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~statement_t() = default;
};
class statements_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~statements_t() = default;
};
class func_returntype_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~func_returntype_t() = default;
};
class arglist_nonempty_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~arglist_nonempty_t() = default;
};
class arglist_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~arglist_t() = default;
};
class function_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~function_t() = default;
};
class top_statement_t:ast_node_t{
    public:
    virtual node_type_t get_kind()=0;
    virtual ~top_statement_t() = default;
};
class factor_id_t:public factor_t{
    public:
    token_t *value;
    ~factor_id_t() override{
        
    }
    node_type_t get_kind(){return NODE_FACTOR;}
};
class factor_num_t:public factor_t{
    public:
    token_t *value;
    ~factor_num_t() override{
        
    }
    node_type_t get_kind(){return NODE_FACTOR;}
};
class factor_ch_t:public factor_t{
    public:
    token_t *value;
    ~factor_ch_t() override{
        
    }
    node_type_t get_kind(){return NODE_FACTOR;}
};
class factor_str_t:public factor_t{
    public:
    token_t *value;
    ~factor_str_t() override{
        
    }
    node_type_t get_kind(){return NODE_FACTOR;}
};
class glued_factor_paren_t:public glued_factor_t{
    public:
    ultimate_expr_t* expr;
    ~glued_factor_paren_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_GLUED_FACTOR;}
};
class glued_factor_def_t:public glued_factor_t{
    public:
    lvalue_t* left;
	token_t *right;
    ~glued_factor_def_t() override{
        delete left;

    }
    node_type_t get_kind(){return NODE_GLUED_FACTOR;}
};
class glued_factor_value_t:public glued_factor_t{
    public:
    factor_t* value;
    ~glued_factor_value_t() override{
        delete value;

    }
    node_type_t get_kind(){return NODE_GLUED_FACTOR;}
};
class glued_factor_call_t:public glued_factor_t{
    public:
    lvalue_t* left;
	arglist_t* args;
    ~glued_factor_call_t() override{
        delete left;
delete args;

    }
    node_type_t get_kind(){return NODE_GLUED_FACTOR;}
};
class single_op_factor_bitnot_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_bitnot_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class single_op_factor_neg_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_neg_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class single_op_factor_ref_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_ref_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class single_op_factor_deref_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_deref_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class single_op_factor_not_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_not_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class single_op_factor_none_t:public single_op_factor_t{
    public:
    glued_factor_t* expr;
    ~single_op_factor_none_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_SINGLE_OP_FACTOR;}
};
class power_factor_pow_t:public power_factor_t{
    public:
    single_op_factor_t* left;
	power_factor_t* right;
    ~power_factor_pow_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_POWER_FACTOR;}
};
class power_factor_none_t:public power_factor_t{
    public:
    single_op_factor_t* expr;
    ~power_factor_none_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_POWER_FACTOR;}
};
class term_mul_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_mul_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_div_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_div_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_mod_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_mod_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_bitand_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_bitand_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_bitor_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_bitor_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_shiftleft_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_shiftleft_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_shiftright_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_shiftright_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class term_factor_t:public term_t{
    public:
    power_factor_t* expr;
    ~term_factor_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_TERM;}
};
class expr_add_t:public expr_t{
    public:
    term_t* left;
	expr_t* right;
    ~expr_add_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_EXPR;}
};
class expr_sub_t:public expr_t{
    public:
    term_t* left;
	expr_t* right;
    ~expr_sub_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_EXPR;}
};
class expr_term_t:public expr_t{
    public:
    term_t* expr;
    ~expr_term_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_EXPR;}
};
class logic_expr_and_and_t:public logic_expr_and_t{
    public:
    expr_t* left;
	logic_expr_and_t* right;
    ~logic_expr_and_and_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_AND;}
};
class logic_expr_and_none_t:public logic_expr_and_t{
    public:
    expr_t* expr;
    ~logic_expr_and_none_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_AND;}
};
class logic_expr_or_or_t:public logic_expr_or_t{
    public:
    logic_expr_and_t* left;
	logic_expr_or_t* right;
    ~logic_expr_or_or_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_OR;}
};
class logic_expr_or_none_t:public logic_expr_or_t{
    public:
    logic_expr_and_t* expr;
    ~logic_expr_or_none_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_OR;}
};
class logic_expr_eq_eq_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_eq_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_neq_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_neq_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_gt_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_gt_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_lt_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_lt_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_ge_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_ge_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_le_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_le_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class logic_expr_eq_none_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* expr;
    ~logic_expr_eq_none_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_LOGIC_EXPR_EQ;}
};
class assign_expr_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_plus_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_plus_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_minus_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_minus_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_mul_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_mul_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_div_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_div_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_mod_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_mod_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_bitand_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_bitand_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_bitor_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_bitor_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_shiftleft_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_shiftleft_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_shiftright_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_shiftright_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class assign_expr_logic_expr_t:public assign_expr_t{
    public:
    logic_expr_eq_t* expr;
    ~assign_expr_logic_expr_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_ASSIGN_EXPR;}
};
class ultimate_expr_def_t:public ultimate_expr_t{
    public:
    assign_expr_t* expr;
    ~ultimate_expr_def_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_ULTIMATE_EXPR;}
};
class lvalue_noproperty_parened_t:public lvalue_noproperty_t{
    public:
    ultimate_expr_t* expr;
    ~lvalue_noproperty_parened_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_LVALUE_NOPROPERTY;}
};
class lvalue_noproperty_deref_t:public lvalue_noproperty_t{
    public:
    lvalue_t* derefee;
    ~lvalue_noproperty_deref_t() override{
        delete derefee;

    }
    node_type_t get_kind(){return NODE_LVALUE_NOPROPERTY;}
};
class lvalue_noproperty_id_t:public lvalue_noproperty_t{
    public:
    token_t *id;
    ~lvalue_noproperty_id_t() override{
        
    }
    node_type_t get_kind(){return NODE_LVALUE_NOPROPERTY;}
};
class lvalue_prop_t:public lvalue_t{
    public:
    lvalue_noproperty_t* left;
	token_t *right;
    ~lvalue_prop_t() override{
        delete left;

    }
    node_type_t get_kind(){return NODE_LVALUE;}
};
class lvalue_noprop_t:public lvalue_t{
    public:
    lvalue_noproperty_t* expr;
    ~lvalue_noprop_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_LVALUE;}
};
class composed_type_raw_type_t:public composed_type_t{
    public:
    token_t *inner_type;
    ~composed_type_raw_type_t() override{
        
    }
    node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};
class composed_type_paren_t:public composed_type_t{
    public:
    composed_type_t* inner_type;
    ~composed_type_paren_t() override{
        delete inner_type;

    }
    node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};
class composed_type_ptr_t:public composed_type_t{
    public:
    composed_type_t* pointer_type;
    ~composed_type_ptr_t() override{
        delete pointer_type;

    }
    node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};
class composed_type_nsizedarr_t:public composed_type_t{
    public:
    composed_type_t* element_type;
    ~composed_type_nsizedarr_t() override{
        delete element_type;

    }
    node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};
class composed_type_sizedarr_t:public composed_type_t{
    public:
    composed_type_t* element_type;
	ultimate_expr_t* array_size;
    ~composed_type_sizedarr_t() override{
        delete element_type;
delete array_size;

    }
    node_type_t get_kind(){return NODE_COMPOSED_TYPE;}
};
class definition_deftype_t:public definition_t{
    public:
    token_t *name;
	composed_type_t* def_type;
	ultimate_expr_t* value;
    ~definition_deftype_t() override{
        delete def_type;
delete value;

    }
    node_type_t get_kind(){return NODE_DEFINITION;}
};
class definition_defntype_t:public definition_t{
    public:
    token_t *name;
	ultimate_expr_t* value;
    ~definition_defntype_t() override{
        delete value;

    }
    node_type_t get_kind(){return NODE_DEFINITION;}
};
class else_default_t:public else_t{
    public:
    statements_t* statements;
    ~else_default_t() override{
        delete statements;

    }
    node_type_t get_kind(){return NODE_ELSE;}
};
class elseif_default_t:public elseif_t{
    public:
    ultimate_expr_t* condition;
	statements_t* statements;
    ~elseif_default_t() override{
        delete condition;
delete statements;

    }
    node_type_t get_kind(){return NODE_ELSEIF;}
};
class elseif_else_onlyelse_t:public elseif_else_t{
    public:
    else_t* else_block;
    ~elseif_else_onlyelse_t() override{
        delete else_block;

    }
    node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};
class elseif_else_chain_t:public elseif_else_t{
    public:
    elseif_t* elseif_block;
	elseif_else_t* rest_block;
    ~elseif_else_chain_t() override{
        delete elseif_block;
delete rest_block;

    }
    node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};
class elseif_else_empty_t:public elseif_else_t{
    public:
    ;
    ~elseif_else_empty_t() override{
        
    }
    node_type_t get_kind(){return NODE_ELSEIF_ELSE;}
};
class if_default_t:public if_t{
    public:
    ultimate_expr_t* condition;
	statements_t* statements;
	elseif_else_t* rest_block;
    ~if_default_t() override{
        delete condition;
delete statements;
delete rest_block;

    }
    node_type_t get_kind(){return NODE_IF;}
};
class while_default_t:public while_t{
    public:
    ultimate_expr_t* condition;
	statements_t* statements;
    ~while_default_t() override{
        delete condition;
delete statements;

    }
    node_type_t get_kind(){return NODE_WHILE;}
};
class structmembers_singmem_t:public structmembers_t{
    public:
    token_t *name;
	composed_type_t* def_type;
    ~structmembers_singmem_t() override{
        delete def_type;

    }
    node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};
class structmembers_multimem_t:public structmembers_t{
    public:
    token_t *name;
	composed_type_t* def_type;
	structmembers_t* other_members;
    ~structmembers_multimem_t() override{
        delete def_type;
delete other_members;

    }
    node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};
class structmembers_empty_t:public structmembers_t{
    public:
    ;
    ~structmembers_empty_t() override{
        
    }
    node_type_t get_kind(){return NODE_STRUCTMEMBERS;}
};
class struct_default_t:public struct_t{
    public:
    token_t *name;
	structmembers_t* members;
    ~struct_default_t() override{
        delete members;

    }
    node_type_t get_kind(){return NODE_STRUCT;}
};
class declaration_varntype_t:public declaration_t{
    public:
    token_t *name;
    ~declaration_varntype_t() override{
        
    }
    node_type_t get_kind(){return NODE_DECLARATION;}
};
class declaration_var_t:public declaration_t{
    public:
    token_t *name;
	composed_type_t* def_type;
    ~declaration_var_t() override{
        delete def_type;

    }
    node_type_t get_kind(){return NODE_DECLARATION;}
};
class declaration_fn_t:public declaration_t{
    public:
    token_t *name;
	arglist_t* args;
	func_returntype_t* return_type;
    ~declaration_fn_t() override{
        delete args;
delete return_type;

    }
    node_type_t get_kind(){return NODE_DECLARATION;}
};
class declaration_struct_t:public declaration_t{
    public:
    token_t *name;
	structmembers_t* members;
    ~declaration_struct_t() override{
        delete members;

    }
    node_type_t get_kind(){return NODE_DECLARATION;}
};
class statement_expr_t:public statement_t{
    public:
    ultimate_expr_t* expr;
    ~statement_expr_t() override{
        delete expr;

    }
    node_type_t get_kind(){return NODE_STATEMENT;}
};
class statement_definition_t:public statement_t{
    public:
    definition_t* def;
    ~statement_definition_t() override{
        delete def;

    }
    node_type_t get_kind(){return NODE_STATEMENT;}
};
class statement_if_t:public statement_t{
    public:
    if_t* if_stmt;
    ~statement_if_t() override{
        delete if_stmt;

    }
    node_type_t get_kind(){return NODE_STATEMENT;}
};
class statement_while_t:public statement_t{
    public:
    while_t* while_stmt;
    ~statement_while_t() override{
        delete while_stmt;

    }
    node_type_t get_kind(){return NODE_STATEMENT;}
};
class statement_declaration_t:public statement_t{
    public:
    declaration_t* decl_stmt;
    ~statement_declaration_t() override{
        delete decl_stmt;

    }
    node_type_t get_kind(){return NODE_STATEMENT;}
};
class statements_stmt_t:public statements_t{
    public:
    statement_t* stmt;
    ~statements_stmt_t() override{
        delete stmt;

    }
    node_type_t get_kind(){return NODE_STATEMENTS;}
};
class statements_multistmt_t:public statements_t{
    public:
    statement_t* stmt;
	statements_t* other_stmts;
    ~statements_multistmt_t() override{
        delete stmt;
delete other_stmts;

    }
    node_type_t get_kind(){return NODE_STATEMENTS;}
};
class statements_empty_t:public statements_t{
    public:
    ;
    ~statements_empty_t() override{
        
    }
    node_type_t get_kind(){return NODE_STATEMENTS;}
};
class func_returntype_hastype_t:public func_returntype_t{
    public:
    composed_type_t* return_type;
    ~func_returntype_hastype_t() override{
        delete return_type;

    }
    node_type_t get_kind(){return NODE_FUNC_RETURNTYPE;}
};
class func_returntype_void_t:public func_returntype_t{
    public:
    ;
    ~func_returntype_void_t() override{
        
    }
    node_type_t get_kind(){return NODE_FUNC_RETURNTYPE;}
};
class arglist_nonempty_singarg_t:public arglist_nonempty_t{
    public:
    token_t *name;
	composed_type_t* arg_type;
    ~arglist_nonempty_singarg_t() override{
        delete arg_type;

    }
    node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};
class arglist_nonempty_multiarg_t:public arglist_nonempty_t{
    public:
    token_t *name;
	composed_type_t* arg_type;
	arglist_nonempty_t* other_args;
    ~arglist_nonempty_multiarg_t() override{
        delete arg_type;
delete other_args;

    }
    node_type_t get_kind(){return NODE_ARGLIST_NONEMPTY;}
};
class arglist_hasarg_t:public arglist_t{
    public:
    arglist_nonempty_t* args;
    ~arglist_hasarg_t() override{
        delete args;

    }
    node_type_t get_kind(){return NODE_ARGLIST;}
};
class arglist_empty_t:public arglist_t{
    public:
    ;
    ~arglist_empty_t() override{
        
    }
    node_type_t get_kind(){return NODE_ARGLIST;}
};
class function_default_t:public function_t{
    public:
    token_t *name;
	arglist_t* args;
	func_returntype_t* return_type;
	statements_t* stmts;
    ~function_default_t() override{
        delete args;
delete return_type;
delete stmts;

    }
    node_type_t get_kind(){return NODE_FUNCTION;}
};
class top_statement_func_def_t:public top_statement_t{
    public:
    function_t* func;
    ~top_statement_func_def_t() override{
        delete func;

    }
    node_type_t get_kind(){return NODE_TOP_STATEMENT;}
};
class top_statement_decl_t:public top_statement_t{
    public:
    declaration_t* decl;
    ~top_statement_decl_t() override{
        delete decl;

    }
    node_type_t get_kind(){return NODE_TOP_STATEMENT;}
};
class top_statement_var_def_t:public top_statement_t{
    public:
    definition_t* def;
    ~top_statement_var_def_t() override{
        delete def;

    }
    node_type_t get_kind(){return NODE_TOP_STATEMENT;}
};
class top_statement_structdef_t:public top_statement_t{
    public:
    struct_t* structdef;
    ~top_statement_structdef_t() override{
        delete structdef;

    }
    node_type_t get_kind(){return NODE_TOP_STATEMENT;}
};
factor_t *parse_factor_t(tokenstream_t *tokenstream);

glued_factor_t *parse_glued_factor_t(tokenstream_t *tokenstream);

single_op_factor_t *parse_single_op_factor_t(tokenstream_t *tokenstream);

power_factor_t *parse_power_factor_t(tokenstream_t *tokenstream);

term_t *parse_term_t(tokenstream_t *tokenstream);

expr_t *parse_expr_t(tokenstream_t *tokenstream);

logic_expr_and_t *parse_logic_expr_and_t(tokenstream_t *tokenstream);

logic_expr_or_t *parse_logic_expr_or_t(tokenstream_t *tokenstream);

logic_expr_eq_t *parse_logic_expr_eq_t(tokenstream_t *tokenstream);

assign_expr_t *parse_assign_expr_t(tokenstream_t *tokenstream);

ultimate_expr_t *parse_ultimate_expr_t(tokenstream_t *tokenstream);

lvalue_noproperty_t *parse_lvalue_noproperty_t(tokenstream_t *tokenstream);

lvalue_t *parse_lvalue_t(tokenstream_t *tokenstream);

composed_type_t *parse_composed_type_t(tokenstream_t *tokenstream);

definition_t *parse_definition_t(tokenstream_t *tokenstream);

else_t *parse_else_t(tokenstream_t *tokenstream);

elseif_t *parse_elseif_t(tokenstream_t *tokenstream);

elseif_else_t *parse_elseif_else_t(tokenstream_t *tokenstream);

if_t *parse_if_t(tokenstream_t *tokenstream);

while_t *parse_while_t(tokenstream_t *tokenstream);

structmembers_t *parse_structmembers_t(tokenstream_t *tokenstream);

struct_t *parse_struct_t(tokenstream_t *tokenstream);

declaration_t *parse_declaration_t(tokenstream_t *tokenstream);

statement_t *parse_statement_t(tokenstream_t *tokenstream);

statements_t *parse_statements_t(tokenstream_t *tokenstream);

func_returntype_t *parse_func_returntype_t(tokenstream_t *tokenstream);

arglist_nonempty_t *parse_arglist_nonempty_t(tokenstream_t *tokenstream);

arglist_t *parse_arglist_t(tokenstream_t *tokenstream);

function_t *parse_function_t(tokenstream_t *tokenstream);

top_statement_t *parse_top_statement_t(tokenstream_t *tokenstream);

factor_id_t* parse_factor_id_t(tokenstream_t *tokenstream){
    factor_id_t* node=new factor_id_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_num_t* parse_factor_num_t(tokenstream_t *tokenstream){
    factor_num_t* node=new factor_num_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_NUMBER(tokenstream->peek()->token_type)){node->value=tokenstream->consume();}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_ch_t* parse_factor_ch_t(tokenstream_t *tokenstream){
    factor_ch_t* node=new factor_ch_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_CHAR(tokenstream->peek()->token_type)){node->value=tokenstream->consume();}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_str_t* parse_factor_str_t(tokenstream_t *tokenstream){
    factor_str_t* node=new factor_str_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_STRING(tokenstream->peek()->token_type)){node->value=tokenstream->consume();}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

factor_t* parse_factor_t(tokenstream_t *tokenstream){{
    factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_factor_id_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_factor_num_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_factor_ch_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_factor_str_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

glued_factor_paren_t* parse_glued_factor_paren_t(tokenstream_t *tokenstream){
    glued_factor_paren_t* node=new glued_factor_paren_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_def_t* parse_glued_factor_def_t(tokenstream_t *tokenstream){
    glued_factor_def_t* node=new glued_factor_def_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_PROPERTY))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_value_t* parse_glued_factor_value_t(tokenstream_t *tokenstream){
    glued_factor_value_t* node=new glued_factor_value_t();
    tokenstream->begin_parsing();
    if(!(node->value=parse_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_call_t* parse_glued_factor_call_t(tokenstream_t *tokenstream){
    glued_factor_call_t* node=new glued_factor_call_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_arglist_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

glued_factor_t* parse_glued_factor_t(tokenstream_t *tokenstream){{
    glued_factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_glued_factor_paren_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_def_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_value_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_glued_factor_call_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

single_op_factor_bitnot_t* parse_single_op_factor_bitnot_t(tokenstream_t *tokenstream){
    single_op_factor_bitnot_t* node=new single_op_factor_bitnot_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITNOT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_neg_t* parse_single_op_factor_neg_t(tokenstream_t *tokenstream){
    single_op_factor_neg_t* node=new single_op_factor_neg_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_ref_t* parse_single_op_factor_ref_t(tokenstream_t *tokenstream){
    single_op_factor_ref_t* node=new single_op_factor_ref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_BITAND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_deref_t* parse_single_op_factor_deref_t(tokenstream_t *tokenstream){
    single_op_factor_deref_t* node=new single_op_factor_deref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_not_t* parse_single_op_factor_not_t(tokenstream_t *tokenstream){
    single_op_factor_not_t* node=new single_op_factor_not_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_NOT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_none_t* parse_single_op_factor_none_t(tokenstream_t *tokenstream){
    single_op_factor_none_t* node=new single_op_factor_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_glued_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

single_op_factor_t* parse_single_op_factor_t(tokenstream_t *tokenstream){{
    single_op_factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_single_op_factor_bitnot_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_neg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_ref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_deref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_not_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_single_op_factor_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

power_factor_pow_t* parse_power_factor_pow_t(tokenstream_t *tokenstream){
    power_factor_pow_t* node=new power_factor_pow_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITXOR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

power_factor_none_t* parse_power_factor_none_t(tokenstream_t *tokenstream){
    power_factor_none_t* node=new power_factor_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_single_op_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

power_factor_t* parse_power_factor_t(tokenstream_t *tokenstream){{
    power_factor_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_power_factor_pow_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_power_factor_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

term_mul_t* parse_term_mul_t(tokenstream_t *tokenstream){
    term_mul_t* node=new term_mul_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_div_t* parse_term_div_t(tokenstream_t *tokenstream){
    term_div_t* node=new term_div_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SLASH))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_mod_t* parse_term_mod_t(tokenstream_t *tokenstream){
    term_mod_t* node=new term_mod_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_PERCENT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_bitand_t* parse_term_bitand_t(tokenstream_t *tokenstream){
    term_bitand_t* node=new term_bitand_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITAND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_bitor_t* parse_term_bitor_t(tokenstream_t *tokenstream){
    term_bitor_t* node=new term_bitor_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITOR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_shiftleft_t* parse_term_shiftleft_t(tokenstream_t *tokenstream){
    term_shiftleft_t* node=new term_shiftleft_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTLEFT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_shiftright_t* parse_term_shiftright_t(tokenstream_t *tokenstream){
    term_shiftright_t* node=new term_shiftright_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTRIGHT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_factor_t* parse_term_factor_t(tokenstream_t *tokenstream){
    term_factor_t* node=new term_factor_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_power_factor_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

term_t* parse_term_t(tokenstream_t *tokenstream){{
    term_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_term_mul_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_div_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_mod_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_bitand_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_bitor_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_shiftleft_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_shiftright_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_term_factor_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

expr_add_t* parse_expr_add_t(tokenstream_t *tokenstream){
    expr_add_t* node=new expr_add_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ADD))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

expr_sub_t* parse_expr_sub_t(tokenstream_t *tokenstream){
    expr_sub_t* node=new expr_sub_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

expr_term_t* parse_expr_term_t(tokenstream_t *tokenstream){
    expr_term_t* node=new expr_term_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_term_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

expr_t* parse_expr_t(tokenstream_t *tokenstream){{
    expr_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_expr_add_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_expr_sub_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_expr_term_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

logic_expr_and_and_t* parse_logic_expr_and_and_t(tokenstream_t *tokenstream){
    logic_expr_and_and_t* node=new logic_expr_and_and_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_AND))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_and_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_and_none_t* parse_logic_expr_and_none_t(tokenstream_t *tokenstream){
    logic_expr_and_none_t* node=new logic_expr_and_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_and_t* parse_logic_expr_and_t(tokenstream_t *tokenstream){{
    logic_expr_and_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_logic_expr_and_and_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_and_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

logic_expr_or_or_t* parse_logic_expr_or_or_t(tokenstream_t *tokenstream){
    logic_expr_or_or_t* node=new logic_expr_or_or_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_and_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_or_none_t* parse_logic_expr_or_none_t(tokenstream_t *tokenstream){
    logic_expr_or_none_t* node=new logic_expr_or_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_and_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_or_t* parse_logic_expr_or_t(tokenstream_t *tokenstream){{
    logic_expr_or_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_logic_expr_or_or_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_or_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

logic_expr_eq_eq_t* parse_logic_expr_eq_eq_t(tokenstream_t *tokenstream){
    logic_expr_eq_eq_t* node=new logic_expr_eq_eq_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_EQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_neq_t* parse_logic_expr_eq_neq_t(tokenstream_t *tokenstream){
    logic_expr_eq_neq_t* node=new logic_expr_eq_neq_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_UNEQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_gt_t* parse_logic_expr_eq_gt_t(tokenstream_t *tokenstream){
    logic_expr_eq_gt_t* node=new logic_expr_eq_gt_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_GREATERTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_lt_t* parse_logic_expr_eq_lt_t(tokenstream_t *tokenstream){
    logic_expr_eq_lt_t* node=new logic_expr_eq_lt_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_LESSTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_ge_t* parse_logic_expr_eq_ge_t(tokenstream_t *tokenstream){
    logic_expr_eq_ge_t* node=new logic_expr_eq_ge_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_GREATEREQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_le_t* parse_logic_expr_eq_le_t(tokenstream_t *tokenstream){
    logic_expr_eq_le_t* node=new logic_expr_eq_le_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_LESSEQUAL))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_none_t* parse_logic_expr_eq_none_t(tokenstream_t *tokenstream){
    logic_expr_eq_none_t* node=new logic_expr_eq_none_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_or_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

logic_expr_eq_t* parse_logic_expr_eq_t(tokenstream_t *tokenstream){{
    logic_expr_eq_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_logic_expr_eq_eq_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_neq_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_gt_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_lt_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_ge_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_le_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_logic_expr_eq_none_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

assign_expr_assign_t* parse_assign_expr_assign_t(tokenstream_t *tokenstream){
    assign_expr_assign_t* node=new assign_expr_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_plus_assign_t* parse_assign_expr_plus_assign_t(tokenstream_t *tokenstream){
    assign_expr_plus_assign_t* node=new assign_expr_plus_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ADDASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_minus_assign_t* parse_assign_expr_minus_assign_t(tokenstream_t *tokenstream){
    assign_expr_minus_assign_t* node=new assign_expr_minus_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MINUSASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_mul_assign_t* parse_assign_expr_mul_assign_t(tokenstream_t *tokenstream){
    assign_expr_mul_assign_t* node=new assign_expr_mul_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MULASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_div_assign_t* parse_assign_expr_div_assign_t(tokenstream_t *tokenstream){
    assign_expr_div_assign_t* node=new assign_expr_div_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_DIVASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_mod_assign_t* parse_assign_expr_mod_assign_t(tokenstream_t *tokenstream){
    assign_expr_mod_assign_t* node=new assign_expr_mod_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_MODASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_bitand_assign_t* parse_assign_expr_bitand_assign_t(tokenstream_t *tokenstream){
    assign_expr_bitand_assign_t* node=new assign_expr_bitand_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITANDASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_bitor_assign_t* parse_assign_expr_bitor_assign_t(tokenstream_t *tokenstream){
    assign_expr_bitor_assign_t* node=new assign_expr_bitor_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_BITORASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_shiftleft_assign_t* parse_assign_expr_shiftleft_assign_t(tokenstream_t *tokenstream){
    assign_expr_shiftleft_assign_t* node=new assign_expr_shiftleft_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTLEFTASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_shiftright_assign_t* parse_assign_expr_shiftright_assign_t(tokenstream_t *tokenstream){
    assign_expr_shiftright_assign_t* node=new assign_expr_shiftright_assign_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SHIFTRIGHTASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_logic_expr_t* parse_assign_expr_logic_expr_t(tokenstream_t *tokenstream){
    assign_expr_logic_expr_t* node=new assign_expr_logic_expr_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_logic_expr_eq_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

assign_expr_t* parse_assign_expr_t(tokenstream_t *tokenstream){{
    assign_expr_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_assign_expr_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_plus_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_minus_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_mul_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_div_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_mod_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_bitand_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_bitor_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_shiftleft_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_shiftright_assign_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_assign_expr_logic_expr_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

ultimate_expr_def_t* parse_ultimate_expr_def_t(tokenstream_t *tokenstream){
    ultimate_expr_def_t* node=new ultimate_expr_def_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_assign_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

ultimate_expr_t* parse_ultimate_expr_t(tokenstream_t *tokenstream){{
    ultimate_expr_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_ultimate_expr_def_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

lvalue_noproperty_parened_t* parse_lvalue_noproperty_parened_t(tokenstream_t *tokenstream){
    lvalue_noproperty_parened_t* node=new lvalue_noproperty_parened_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_deref_t* parse_lvalue_noproperty_deref_t(tokenstream_t *tokenstream){
    lvalue_noproperty_deref_t* node=new lvalue_noproperty_deref_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
if(!(node->derefee=parse_lvalue_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_id_t* parse_lvalue_noproperty_id_t(tokenstream_t *tokenstream){
    lvalue_noproperty_id_t* node=new lvalue_noproperty_id_t();
    tokenstream->begin_parsing();
    if(!(node->id=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noproperty_t* parse_lvalue_noproperty_t(tokenstream_t *tokenstream){{
    lvalue_noproperty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_lvalue_noproperty_parened_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_lvalue_noproperty_deref_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_lvalue_noproperty_id_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

lvalue_prop_t* parse_lvalue_prop_t(tokenstream_t *tokenstream){
    lvalue_prop_t* node=new lvalue_prop_t();
    tokenstream->begin_parsing();
    if(!(node->left=parse_lvalue_noproperty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_PROPERTY))){tokenstream->reset();delete node;return nullptr;}
if(!(node->right=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_noprop_t* parse_lvalue_noprop_t(tokenstream_t *tokenstream){
    lvalue_noprop_t* node=new lvalue_noprop_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_lvalue_noproperty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

lvalue_t* parse_lvalue_t(tokenstream_t *tokenstream){{
    lvalue_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_lvalue_prop_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_lvalue_noprop_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

composed_type_raw_type_t* parse_composed_type_raw_type_t(tokenstream_t *tokenstream){
    composed_type_raw_type_t* node=new composed_type_raw_type_t();
    tokenstream->begin_parsing();
    if(!tokenstream->eof()&&BELONGS_TO_CATEGORY_TYPEKW(tokenstream->peek()->token_type)){node->inner_type=tokenstream->consume();}else{tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_paren_t* parse_composed_type_paren_t(tokenstream_t *tokenstream){
    composed_type_paren_t* node=new composed_type_paren_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->inner_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_ptr_t* parse_composed_type_ptr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_ptr_t* node=new composed_type_ptr_t();
    tokenstream->begin_parsing();
    node->pointer_type=start_node;
    if(!(parse_token(tokenstream,TOKEN_STAR))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_nsizedarr_t* parse_composed_type_nsizedarr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_nsizedarr_t* node=new composed_type_nsizedarr_t();
    tokenstream->begin_parsing();
    node->element_type=start_node;
    if(!(parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

composed_type_sizedarr_t* parse_composed_type_sizedarr_t_nostart(composed_type_t* start_node,tokenstream_t *tokenstream){
    composed_type_sizedarr_t* node=new composed_type_sizedarr_t();
    tokenstream->begin_parsing();
    node->element_type=start_node;
    if(!(parse_token(tokenstream,TOKEN_OPEN_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->array_size=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSED_SQUAREDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}
static composed_type_t* parse_composed_type_t_start(tokenstream_t *tokenstream){
        composed_type_t* node;
        tokenstream->begin_parsing();
        if((node=parse_composed_type_raw_type_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_composed_type_paren_t(tokenstream))){tokenstream->end_parsing();return node;}
	
	
	
        tokenstream->reset();
        return nullptr;
}
composed_type_t* parse_composed_type_t(tokenstream_t *tokenstream){
    tokenstream->begin_parsing();
    composed_type_t* node = parse_composed_type_t_start(tokenstream);
    if(!node) {tokenstream->reset();return nullptr;}
    while(1){
        composed_type_t* next=nullptrptr;
        
	
	if((next=parse_composed_type_ptr_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_composed_type_nsizedarr_t_nostart(node,tokenstream))){node=next;continue;}
	else if((next=parse_composed_type_sizedarr_t_nostart(node,tokenstream))){node=next;continue;}else break;
    }
    tokenstream->end_parsing();
    return node;
}
definition_deftype_t* parse_definition_deftype_t(tokenstream_t *tokenstream){
    definition_deftype_t* node=new definition_deftype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

definition_defntype_t* parse_definition_defntype_t(tokenstream_t *tokenstream){
    definition_defntype_t* node=new definition_defntype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_ASSIGN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->value=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

definition_t* parse_definition_t(tokenstream_t *tokenstream){{
    definition_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_definition_deftype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_definition_defntype_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

else_default_t* parse_else_default_t(tokenstream_t *tokenstream){
    else_default_t* node=new else_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_ELSE))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

else_t* parse_else_t(tokenstream_t *tokenstream){{
    else_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_else_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

elseif_default_t* parse_elseif_default_t(tokenstream_t *tokenstream){
    elseif_default_t* node=new elseif_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_ELSE))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_IF))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_t* parse_elseif_t(tokenstream_t *tokenstream){{
    elseif_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_elseif_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

elseif_else_onlyelse_t* parse_elseif_else_onlyelse_t(tokenstream_t *tokenstream){
    elseif_else_onlyelse_t* node=new elseif_else_onlyelse_t();
    tokenstream->begin_parsing();
    if(!(node->else_block=parse_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_else_chain_t* parse_elseif_else_chain_t(tokenstream_t *tokenstream){
    elseif_else_chain_t* node=new elseif_else_chain_t();
    tokenstream->begin_parsing();
    if(!(node->elseif_block=parse_elseif_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(node->rest_block=parse_elseif_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

elseif_else_empty_t* parse_elseif_else_empty_t(tokenstream_t *tokenstream){
    elseif_else_empty_t* node=new elseif_else_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

elseif_else_t* parse_elseif_else_t(tokenstream_t *tokenstream){{
    elseif_else_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_elseif_else_onlyelse_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_elseif_else_chain_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_elseif_else_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

if_default_t* parse_if_default_t(tokenstream_t *tokenstream){
    if_default_t* node=new if_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_IF))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->rest_block=parse_elseif_else_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

if_t* parse_if_t(tokenstream_t *tokenstream){{
    if_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_if_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

while_default_t* parse_while_default_t(tokenstream_t *tokenstream){
    while_default_t* node=new while_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_WHILE))){tokenstream->reset();delete node;return nullptr;}
if(!(node->condition=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->statements=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

while_t* parse_while_t(tokenstream_t *tokenstream){{
    while_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_while_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

structmembers_singmem_t* parse_structmembers_singmem_t(tokenstream_t *tokenstream){
    structmembers_singmem_t* node=new structmembers_singmem_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

structmembers_multimem_t* parse_structmembers_multimem_t(tokenstream_t *tokenstream){
    structmembers_multimem_t* node=new structmembers_multimem_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COMMA))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

structmembers_empty_t* parse_structmembers_empty_t(tokenstream_t *tokenstream){
    structmembers_empty_t* node=new structmembers_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

structmembers_t* parse_structmembers_t(tokenstream_t *tokenstream){{
    structmembers_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_structmembers_singmem_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_structmembers_multimem_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_structmembers_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

struct_default_t* parse_struct_default_t(tokenstream_t *tokenstream){
    struct_default_t* node=new struct_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STRUCT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

struct_t* parse_struct_t(tokenstream_t *tokenstream){{
    struct_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_struct_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

declaration_varntype_t* parse_declaration_varntype_t(tokenstream_t *tokenstream){
    declaration_varntype_t* node=new declaration_varntype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_var_t* parse_declaration_var_t(tokenstream_t *tokenstream){
    declaration_var_t* node=new declaration_var_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_LET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COLON))){tokenstream->reset();delete node;return nullptr;}
if(!(node->def_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_fn_t* parse_declaration_fn_t(tokenstream_t *tokenstream){
    declaration_fn_t* node=new declaration_fn_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_FN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_arglist_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_func_returntype_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_struct_t* parse_declaration_struct_t(tokenstream_t *tokenstream){
    declaration_struct_t* node=new declaration_struct_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_STRUCT))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->members=parse_structmembers_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

declaration_t* parse_declaration_t(tokenstream_t *tokenstream){{
    declaration_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_declaration_varntype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_var_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_fn_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_declaration_struct_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

statement_expr_t* parse_statement_expr_t(tokenstream_t *tokenstream){
    statement_expr_t* node=new statement_expr_t();
    tokenstream->begin_parsing();
    if(!(node->expr=parse_ultimate_expr_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_definition_t* parse_statement_definition_t(tokenstream_t *tokenstream){
    statement_definition_t* node=new statement_definition_t();
    tokenstream->begin_parsing();
    if(!(node->def=parse_definition_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_if_t* parse_statement_if_t(tokenstream_t *tokenstream){
    statement_if_t* node=new statement_if_t();
    tokenstream->begin_parsing();
    if(!(node->if_stmt=parse_if_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_while_t* parse_statement_while_t(tokenstream_t *tokenstream){
    statement_while_t* node=new statement_while_t();
    tokenstream->begin_parsing();
    if(!(node->while_stmt=parse_while_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_declaration_t* parse_statement_declaration_t(tokenstream_t *tokenstream){
    statement_declaration_t* node=new statement_declaration_t();
    tokenstream->begin_parsing();
    if(!(node->decl_stmt=parse_declaration_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statement_t* parse_statement_t(tokenstream_t *tokenstream){{
    statement_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_statement_expr_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_definition_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_if_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_while_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statement_declaration_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

statements_stmt_t* parse_statements_stmt_t(tokenstream_t *tokenstream){
    statements_stmt_t* node=new statements_stmt_t();
    tokenstream->begin_parsing();
    if(!(node->stmt=parse_statement_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statements_multistmt_t* parse_statements_multistmt_t(tokenstream_t *tokenstream){
    statements_multistmt_t* node=new statements_multistmt_t();
    tokenstream->begin_parsing();
    if(!(node->stmt=parse_statement_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_stmts=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

statements_empty_t* parse_statements_empty_t(tokenstream_t *tokenstream){
    statements_empty_t* node=new statements_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

statements_t* parse_statements_t(tokenstream_t *tokenstream){{
    statements_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_statements_stmt_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statements_multistmt_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_statements_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

func_returntype_hastype_t* parse_func_returntype_hastype_t(tokenstream_t *tokenstream){
    func_returntype_hastype_t* node=new func_returntype_hastype_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_MINUS))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_GREATERTHAN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

func_returntype_void_t* parse_func_returntype_void_t(tokenstream_t *tokenstream){
    func_returntype_void_t* node=new func_returntype_void_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

func_returntype_t* parse_func_returntype_t(tokenstream_t *tokenstream){{
    func_returntype_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_func_returntype_hastype_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_func_returntype_void_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

arglist_nonempty_singarg_t* parse_arglist_nonempty_singarg_t(tokenstream_t *tokenstream){
    arglist_nonempty_singarg_t* node=new arglist_nonempty_singarg_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(node->arg_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

arglist_nonempty_multiarg_t* parse_arglist_nonempty_multiarg_t(tokenstream_t *tokenstream){
    arglist_nonempty_multiarg_t* node=new arglist_nonempty_multiarg_t();
    tokenstream->begin_parsing();
    if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(node->arg_type=parse_composed_type_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_COMMA))){tokenstream->reset();delete node;return nullptr;}
if(!(node->other_args=parse_arglist_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

arglist_nonempty_t* parse_arglist_nonempty_t(tokenstream_t *tokenstream){{
    arglist_nonempty_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_arglist_nonempty_singarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_arglist_nonempty_multiarg_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

arglist_hasarg_t* parse_arglist_hasarg_t(tokenstream_t *tokenstream){
    arglist_hasarg_t* node=new arglist_hasarg_t();
    tokenstream->begin_parsing();
    if(!(node->args=parse_arglist_nonempty_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

arglist_empty_t* parse_arglist_empty_t(tokenstream_t *tokenstream){
    arglist_empty_t* node=new arglist_empty_t();
    tokenstream->begin_parsing();
    
    tokenstream->end_parsing();
    return node;
}

arglist_t* parse_arglist_t(tokenstream_t *tokenstream){{
    arglist_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_arglist_hasarg_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_arglist_empty_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

function_default_t* parse_function_default_t(tokenstream_t *tokenstream){
    function_default_t* node=new function_default_t();
    tokenstream->begin_parsing();
    if(!(parse_token(tokenstream,TOKEN_FN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->name=parse_token(tokenstream,TOKEN_IDENTIFIER))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->args=parse_arglist_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDPAREN))){tokenstream->reset();delete node;return nullptr;}
if(!(node->return_type=parse_func_returntype_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_OPENBRACKET))){tokenstream->reset();delete node;return nullptr;}
if(!(node->stmts=parse_statements_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_CLOSEDBRACKET))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

function_t* parse_function_t(tokenstream_t *tokenstream){{
    function_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_function_default_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}

top_statement_func_def_t* parse_top_statement_func_def_t(tokenstream_t *tokenstream){
    top_statement_func_def_t* node=new top_statement_func_def_t();
    tokenstream->begin_parsing();
    if(!(node->func=parse_function_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_decl_t* parse_top_statement_decl_t(tokenstream_t *tokenstream){
    top_statement_decl_t* node=new top_statement_decl_t();
    tokenstream->begin_parsing();
    if(!(node->decl=parse_declaration_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_var_def_t* parse_top_statement_var_def_t(tokenstream_t *tokenstream){
    top_statement_var_def_t* node=new top_statement_var_def_t();
    tokenstream->begin_parsing();
    if(!(node->def=parse_definition_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
if(!(parse_token(tokenstream,TOKEN_SEMICOLON))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_structdef_t* parse_top_statement_structdef_t(tokenstream_t *tokenstream){
    top_statement_structdef_t* node=new top_statement_structdef_t();
    tokenstream->begin_parsing();
    if(!(node->structdef=parse_struct_t(tokenstream))){tokenstream->reset();delete node;return nullptr;}
    tokenstream->end_parsing();
    return node;
}

top_statement_t* parse_top_statement_t(tokenstream_t *tokenstream){{
    top_statement_t* node=nullptr;
    tokenstream->begin_parsing();
    if((node=parse_top_statement_func_def_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_decl_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_var_def_t(tokenstream))){tokenstream->end_parsing();return node;}
	if((node=parse_top_statement_structdef_t(tokenstream))){tokenstream->end_parsing();return node;}
    tokenstream->reset();
    return node;
}}


typedef struct{
    char* name;
    ast_node_t* (*parser)(tokenstream_t *ts);
}parser_rule_t;

parser_rule_t parser_rules[]={
{.name="top_statement", .parser=(ast_node_t* (*)(tokenstream_t*))parse_top_statement_t},

};
    
std::vector<ast_node_t*> do_parse(tokenstream_t *tokenstream){
    std::vector<ast_node_t*> nodes;
    while(!tokenstream->eof()){
        bool flag=false;
        for(int i=0;i<sizeof(parser_rules)/sizeof(parser_rule_t);i++){
            ast_node_t *node;
            if(node=parser_rules[i].parser(tokenstream)){
                nodes.push_back(node);
                flag=true;
                break;
            }
        }
        if(!flag){
            printf("parser error: failed to parse token at line %d, column %d\n",tokenstream->peek()->line+1,tokenstream->peek()->column+1);
            tokenstream->begin_parsing();
            tokenstream->next();
            tokenstream->end_parsing();
        }
    }
    return nodes;
}