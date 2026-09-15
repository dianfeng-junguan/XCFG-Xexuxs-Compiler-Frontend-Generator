
typedef enum{
NODE_FACTOR_ID,
NODE_FACTOR_NUM,
NODE_FACTOR_CH,
NODE_FACTOR_STR,
NODE_GLUED_FACTOR_PAREN,
NODE_GLUED_FACTOR_DEF,
NODE_GLUED_FACTOR_VALUE,
NODE_GLUED_FACTOR_CALL,
NODE_SINGLE_OP_FACTOR_BITNOT,
NODE_SINGLE_OP_FACTOR_NEG,
NODE_SINGLE_OP_FACTOR_REF,
NODE_SINGLE_OP_FACTOR_DEREF,
NODE_SINGLE_OP_FACTOR_NOT,
NODE_SINGLE_OP_FACTOR_NONE,
NODE_POWER_FACTOR_POW,
NODE_POWER_FACTOR_NONE,
NODE_TERM_MUL,
NODE_TERM_DIV,
NODE_TERM_MOD,
NODE_TERM_BITAND,
NODE_TERM_BITOR,
NODE_TERM_SHIFTLEFT,
NODE_TERM_SHIFTRIGHT,
NODE_TERM_FACTOR,
NODE_EXPR_ADD,
NODE_EXPR_SUB,
NODE_EXPR_TERM,
NODE_LOGIC_EXPR_AND_AND,
NODE_LOGIC_EXPR_AND_NONE,
NODE_LOGIC_EXPR_OR_OR,
NODE_LOGIC_EXPR_OR_NONE,
NODE_LOGIC_EXPR_EQ_EQ,
NODE_LOGIC_EXPR_EQ_NEQ,
NODE_LOGIC_EXPR_EQ_GT,
NODE_LOGIC_EXPR_EQ_LT,
NODE_LOGIC_EXPR_EQ_GE,
NODE_LOGIC_EXPR_EQ_LE,
NODE_LOGIC_EXPR_EQ_NONE,
NODE_ASSIGN_EXPR_ASSIGN,
NODE_ASSIGN_EXPR_PLUS_ASSIGN,
NODE_ASSIGN_EXPR_MINUS_ASSIGN,
NODE_ASSIGN_EXPR_MUL_ASSIGN,
NODE_ASSIGN_EXPR_DIV_ASSIGN,
NODE_ASSIGN_EXPR_MOD_ASSIGN,
NODE_ASSIGN_EXPR_BITAND_ASSIGN,
NODE_ASSIGN_EXPR_BITOR_ASSIGN,
NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN,
NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN,
NODE_ASSIGN_EXPR_LOGIC_EXPR,
NODE_ULTIMATE_EXPR_DEF,
NODE_LVALUE_NOPROPERTY_PARENED,
NODE_LVALUE_NOPROPERTY_DEREF,
NODE_LVALUE_NOPROPERTY_ID,
NODE_LVALUE_PROP,
NODE_LVALUE_NOPROP,
NODE_COMPOSED_TYPE_RAW_TYPE,
NODE_COMPOSED_TYPE_PAREN,
NODE_COMPOSED_TYPE_PTR,
NODE_COMPOSED_TYPE_NSIZEDARR,
NODE_COMPOSED_TYPE_SIZEDARR,
NODE_DEFINITION_DEFTYPE,
NODE_DEFINITION_DEFNTYPE,
NODE_ELSE_DEFAULT,
NODE_ELSEIF_DEFAULT,
NODE_ELSEIF_ELSE_ONLYELSE,
NODE_ELSEIF_ELSE_CHAIN,
NODE_ELSEIF_ELSE_EMPTY,
NODE_IF_DEFAULT,
NODE_WHILE_DEFAULT,
NODE_STRUCTMEMBERS_SINGMEM,
NODE_STRUCTMEMBERS_MULTIMEM,
NODE_STRUCTMEMBERS_EMPTY,
NODE_STRUCT_DEFAULT,
NODE_DECLARATION_VARNTYPE,
NODE_DECLARATION_VAR,
NODE_DECLARATION_FN,
NODE_DECLARATION_STRUCT,
NODE_STATEMENT_EXPR,
NODE_STATEMENT_DEFINITION,
NODE_STATEMENT_IF,
NODE_STATEMENT_WHILE,
NODE_STATEMENT_DECLARATION,
NODE_STATEMENT_BREAK,
NODE_STATEMENT_CONTINUE,
NODE_STATEMENT_RETURN_EMPTY,
NODE_STATEMENT_RETURN_STH,
NODE_STATEMENTS_STMT,
NODE_STATEMENTS_MULTISTMT,
NODE_STATEMENTS_EMPTY,
NODE_FUNC_RETURNTYPE_HASTYPE,
NODE_FUNC_RETURNTYPE_VOID,
NODE_ARGLIST_NONEMPTY_SINGARG,
NODE_ARGLIST_NONEMPTY_MULTIARG,
NODE_ARGLIST_HASARG,
NODE_ARGLIST_EMPTY,
NODE_FUNCTION_DEFAULT,
NODE_TOP_STATEMENT_FUNC_DEF,
NODE_TOP_STATEMENT_DECL,
NODE_TOP_STATEMENT_VAR_DEF,
NODE_TOP_STATEMENT_STRUCTDEF,

}node_type_t;

#pragma once
#include "lexer.h"
class ast_node_t{
public:
    virtual ~ast_node_t() = default;
    virtual node_type_t get_kind() const = 0;
};
class factor_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~factor_t() = default;
};
class glued_factor_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~glued_factor_t() = default;
};
class single_op_factor_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~single_op_factor_t() = default;
};
class power_factor_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~power_factor_t() = default;
};
class term_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~term_t() = default;
};
class expr_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~expr_t() = default;
};
class logic_expr_and_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~logic_expr_and_t() = default;
};
class logic_expr_or_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~logic_expr_or_t() = default;
};
class logic_expr_eq_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~logic_expr_eq_t() = default;
};
class assign_expr_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~assign_expr_t() = default;
};
class ultimate_expr_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~ultimate_expr_t() = default;
};
class lvalue_noproperty_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~lvalue_noproperty_t() = default;
};
class lvalue_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~lvalue_t() = default;
};
class composed_type_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~composed_type_t() = default;
};
class definition_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~definition_t() = default;
};
class else_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~else_t() = default;
};
class elseif_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~elseif_t() = default;
};
class elseif_else_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~elseif_else_t() = default;
};
class if_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~if_t() = default;
};
class while_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~while_t() = default;
};
class structmembers_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~structmembers_t() = default;
};
class struct_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~struct_t() = default;
};
class declaration_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~declaration_t() = default;
};
class statement_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~statement_t() = default;
};
class statements_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~statements_t() = default;
};
class func_returntype_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~func_returntype_t() = default;
};
class arglist_nonempty_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~arglist_nonempty_t() = default;
};
class arglist_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~arglist_t() = default;
};
class function_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~function_t() = default;
};
class top_statement_t:public ast_node_t{
    public:
    virtual node_type_t get_kind() const override;
    virtual ~top_statement_t() = default;
};
class factor_id_t:public factor_t{
    public:
    token_t *value;
    ~factor_id_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_FACTOR_ID;}
};
class factor_num_t:public factor_t{
    public:
    token_t *value;
    ~factor_num_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_FACTOR_NUM;}
};
class factor_ch_t:public factor_t{
    public:
    token_t *value;
    ~factor_ch_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_FACTOR_CH;}
};
class factor_str_t:public factor_t{
    public:
    token_t *value;
    ~factor_str_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_FACTOR_STR;}
};
class glued_factor_paren_t:public glued_factor_t{
    public:
    ultimate_expr_t* expr;
    ~glued_factor_paren_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_GLUED_FACTOR_PAREN;}
};
class glued_factor_def_t:public glued_factor_t{
    public:
    lvalue_t* left;
	token_t *right;
    ~glued_factor_def_t() override{
        delete left;

    }
    node_type_t get_kind() const override {return NODE_GLUED_FACTOR_DEF;}
};
class glued_factor_value_t:public glued_factor_t{
    public:
    factor_t* value;
    ~glued_factor_value_t() override{
        delete value;

    }
    node_type_t get_kind() const override {return NODE_GLUED_FACTOR_VALUE;}
};
class glued_factor_call_t:public glued_factor_t{
    public:
    lvalue_t* left;
	arglist_t* args;
    ~glued_factor_call_t() override{
        delete left;
delete args;

    }
    node_type_t get_kind() const override {return NODE_GLUED_FACTOR_CALL;}
};
class single_op_factor_bitnot_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_bitnot_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_BITNOT;}
};
class single_op_factor_neg_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_neg_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_NEG;}
};
class single_op_factor_ref_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_ref_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_REF;}
};
class single_op_factor_deref_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_deref_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_DEREF;}
};
class single_op_factor_not_t:public single_op_factor_t{
    public:
    single_op_factor_t* expr;
    ~single_op_factor_not_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_NOT;}
};
class single_op_factor_none_t:public single_op_factor_t{
    public:
    glued_factor_t* expr;
    ~single_op_factor_none_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_SINGLE_OP_FACTOR_NONE;}
};
class power_factor_pow_t:public power_factor_t{
    public:
    single_op_factor_t* left;
	power_factor_t* right;
    ~power_factor_pow_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_POWER_FACTOR_POW;}
};
class power_factor_none_t:public power_factor_t{
    public:
    single_op_factor_t* expr;
    ~power_factor_none_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_POWER_FACTOR_NONE;}
};
class term_mul_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_mul_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_MUL;}
};
class term_div_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_div_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_DIV;}
};
class term_mod_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_mod_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_MOD;}
};
class term_bitand_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_bitand_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_BITAND;}
};
class term_bitor_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_bitor_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_BITOR;}
};
class term_shiftleft_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_shiftleft_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_SHIFTLEFT;}
};
class term_shiftright_t:public term_t{
    public:
    power_factor_t* left;
	term_t* right;
    ~term_shiftright_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_TERM_SHIFTRIGHT;}
};
class term_factor_t:public term_t{
    public:
    power_factor_t* expr;
    ~term_factor_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_TERM_FACTOR;}
};
class expr_add_t:public expr_t{
    public:
    term_t* left;
	expr_t* right;
    ~expr_add_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_EXPR_ADD;}
};
class expr_sub_t:public expr_t{
    public:
    term_t* left;
	expr_t* right;
    ~expr_sub_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_EXPR_SUB;}
};
class expr_term_t:public expr_t{
    public:
    term_t* expr;
    ~expr_term_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_EXPR_TERM;}
};
class logic_expr_and_and_t:public logic_expr_and_t{
    public:
    expr_t* left;
	logic_expr_and_t* right;
    ~logic_expr_and_and_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_AND_AND;}
};
class logic_expr_and_none_t:public logic_expr_and_t{
    public:
    expr_t* expr;
    ~logic_expr_and_none_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_AND_NONE;}
};
class logic_expr_or_or_t:public logic_expr_or_t{
    public:
    logic_expr_and_t* left;
	logic_expr_or_t* right;
    ~logic_expr_or_or_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_OR_OR;}
};
class logic_expr_or_none_t:public logic_expr_or_t{
    public:
    logic_expr_and_t* expr;
    ~logic_expr_or_none_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_OR_NONE;}
};
class logic_expr_eq_eq_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_eq_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_EQ;}
};
class logic_expr_eq_neq_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_neq_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_NEQ;}
};
class logic_expr_eq_gt_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_gt_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_GT;}
};
class logic_expr_eq_lt_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_lt_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_LT;}
};
class logic_expr_eq_ge_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_ge_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_GE;}
};
class logic_expr_eq_le_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* left;
	logic_expr_eq_t* right;
    ~logic_expr_eq_le_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_LE;}
};
class logic_expr_eq_none_t:public logic_expr_eq_t{
    public:
    logic_expr_or_t* expr;
    ~logic_expr_eq_none_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_LOGIC_EXPR_EQ_NONE;}
};
class assign_expr_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_ASSIGN;}
};
class assign_expr_plus_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_plus_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_PLUS_ASSIGN;}
};
class assign_expr_minus_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_minus_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_MINUS_ASSIGN;}
};
class assign_expr_mul_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_mul_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_MUL_ASSIGN;}
};
class assign_expr_div_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_div_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_DIV_ASSIGN;}
};
class assign_expr_mod_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_mod_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_MOD_ASSIGN;}
};
class assign_expr_bitand_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_bitand_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_BITAND_ASSIGN;}
};
class assign_expr_bitor_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_bitor_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_BITOR_ASSIGN;}
};
class assign_expr_shiftleft_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_shiftleft_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_SHIFTLEFT_ASSIGN;}
};
class assign_expr_shiftright_assign_t:public assign_expr_t{
    public:
    lvalue_t* left;
	assign_expr_t* right;
    ~assign_expr_shiftright_assign_t() override{
        delete left;
delete right;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_SHIFTRIGHT_ASSIGN;}
};
class assign_expr_logic_expr_t:public assign_expr_t{
    public:
    logic_expr_eq_t* expr;
    ~assign_expr_logic_expr_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_ASSIGN_EXPR_LOGIC_EXPR;}
};
class ultimate_expr_def_t:public ultimate_expr_t{
    public:
    assign_expr_t* expr;
    ~ultimate_expr_def_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_ULTIMATE_EXPR_DEF;}
};
class lvalue_noproperty_parened_t:public lvalue_noproperty_t{
    public:
    ultimate_expr_t* expr;
    ~lvalue_noproperty_parened_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_LVALUE_NOPROPERTY_PARENED;}
};
class lvalue_noproperty_deref_t:public lvalue_noproperty_t{
    public:
    lvalue_t* derefee;
    ~lvalue_noproperty_deref_t() override{
        delete derefee;

    }
    node_type_t get_kind() const override {return NODE_LVALUE_NOPROPERTY_DEREF;}
};
class lvalue_noproperty_id_t:public lvalue_noproperty_t{
    public:
    token_t *id;
    ~lvalue_noproperty_id_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_LVALUE_NOPROPERTY_ID;}
};
class lvalue_prop_t:public lvalue_t{
    public:
    lvalue_noproperty_t* left;
	token_t *right;
    ~lvalue_prop_t() override{
        delete left;

    }
    node_type_t get_kind() const override {return NODE_LVALUE_PROP;}
};
class lvalue_noprop_t:public lvalue_t{
    public:
    lvalue_noproperty_t* expr;
    ~lvalue_noprop_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_LVALUE_NOPROP;}
};
class composed_type_raw_type_t:public composed_type_t{
    public:
    token_t *inner_type;
    ~composed_type_raw_type_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_COMPOSED_TYPE_RAW_TYPE;}
};
class composed_type_paren_t:public composed_type_t{
    public:
    composed_type_t* inner_type;
    ~composed_type_paren_t() override{
        delete inner_type;

    }
    node_type_t get_kind() const override {return NODE_COMPOSED_TYPE_PAREN;}
};
class composed_type_ptr_t:public composed_type_t{
    public:
    composed_type_t* pointer_type;
    ~composed_type_ptr_t() override{
        delete pointer_type;

    }
    node_type_t get_kind() const override {return NODE_COMPOSED_TYPE_PTR;}
};
class composed_type_nsizedarr_t:public composed_type_t{
    public:
    composed_type_t* element_type;
    ~composed_type_nsizedarr_t() override{
        delete element_type;

    }
    node_type_t get_kind() const override {return NODE_COMPOSED_TYPE_NSIZEDARR;}
};
class composed_type_sizedarr_t:public composed_type_t{
    public:
    composed_type_t* element_type;
	ultimate_expr_t* array_size;
    ~composed_type_sizedarr_t() override{
        delete element_type;
delete array_size;

    }
    node_type_t get_kind() const override {return NODE_COMPOSED_TYPE_SIZEDARR;}
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
    node_type_t get_kind() const override {return NODE_DEFINITION_DEFTYPE;}
};
class definition_defntype_t:public definition_t{
    public:
    token_t *name;
	ultimate_expr_t* value;
    ~definition_defntype_t() override{
        delete value;

    }
    node_type_t get_kind() const override {return NODE_DEFINITION_DEFNTYPE;}
};
class else_default_t:public else_t{
    public:
    statements_t* statements;
    ~else_default_t() override{
        delete statements;

    }
    node_type_t get_kind() const override {return NODE_ELSE_DEFAULT;}
};
class elseif_default_t:public elseif_t{
    public:
    ultimate_expr_t* condition;
	statements_t* statements;
    ~elseif_default_t() override{
        delete condition;
delete statements;

    }
    node_type_t get_kind() const override {return NODE_ELSEIF_DEFAULT;}
};
class elseif_else_onlyelse_t:public elseif_else_t{
    public:
    else_t* else_block;
    ~elseif_else_onlyelse_t() override{
        delete else_block;

    }
    node_type_t get_kind() const override {return NODE_ELSEIF_ELSE_ONLYELSE;}
};
class elseif_else_chain_t:public elseif_else_t{
    public:
    elseif_t* elseif_block;
	elseif_else_t* rest_block;
    ~elseif_else_chain_t() override{
        delete elseif_block;
delete rest_block;

    }
    node_type_t get_kind() const override {return NODE_ELSEIF_ELSE_CHAIN;}
};
class elseif_else_empty_t:public elseif_else_t{
    public:
    ;
    ~elseif_else_empty_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_ELSEIF_ELSE_EMPTY;}
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
    node_type_t get_kind() const override {return NODE_IF_DEFAULT;}
};
class while_default_t:public while_t{
    public:
    ultimate_expr_t* condition;
	statements_t* statements;
    ~while_default_t() override{
        delete condition;
delete statements;

    }
    node_type_t get_kind() const override {return NODE_WHILE_DEFAULT;}
};
class structmembers_singmem_t:public structmembers_t{
    public:
    token_t *name;
	composed_type_t* def_type;
    ~structmembers_singmem_t() override{
        delete def_type;

    }
    node_type_t get_kind() const override {return NODE_STRUCTMEMBERS_SINGMEM;}
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
    node_type_t get_kind() const override {return NODE_STRUCTMEMBERS_MULTIMEM;}
};
class structmembers_empty_t:public structmembers_t{
    public:
    ;
    ~structmembers_empty_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_STRUCTMEMBERS_EMPTY;}
};
class struct_default_t:public struct_t{
    public:
    token_t *name;
	structmembers_t* members;
    ~struct_default_t() override{
        delete members;

    }
    node_type_t get_kind() const override {return NODE_STRUCT_DEFAULT;}
};
class declaration_varntype_t:public declaration_t{
    public:
    token_t *name;
    ~declaration_varntype_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_DECLARATION_VARNTYPE;}
};
class declaration_var_t:public declaration_t{
    public:
    token_t *name;
	composed_type_t* def_type;
    ~declaration_var_t() override{
        delete def_type;

    }
    node_type_t get_kind() const override {return NODE_DECLARATION_VAR;}
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
    node_type_t get_kind() const override {return NODE_DECLARATION_FN;}
};
class declaration_struct_t:public declaration_t{
    public:
    token_t *name;
	structmembers_t* members;
    ~declaration_struct_t() override{
        delete members;

    }
    node_type_t get_kind() const override {return NODE_DECLARATION_STRUCT;}
};
class statement_expr_t:public statement_t{
    public:
    ultimate_expr_t* expr;
    ~statement_expr_t() override{
        delete expr;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_EXPR;}
};
class statement_definition_t:public statement_t{
    public:
    definition_t* def;
    ~statement_definition_t() override{
        delete def;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_DEFINITION;}
};
class statement_if_t:public statement_t{
    public:
    if_t* if_stmt;
    ~statement_if_t() override{
        delete if_stmt;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_IF;}
};
class statement_while_t:public statement_t{
    public:
    while_t* while_stmt;
    ~statement_while_t() override{
        delete while_stmt;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_WHILE;}
};
class statement_declaration_t:public statement_t{
    public:
    declaration_t* decl_stmt;
    ~statement_declaration_t() override{
        delete decl_stmt;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_DECLARATION;}
};
class statement_break_t:public statement_t{
    public:
    ;
    ~statement_break_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_STATEMENT_BREAK;}
};
class statement_continue_t:public statement_t{
    public:
    ;
    ~statement_continue_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_STATEMENT_CONTINUE;}
};
class statement_return_empty_t:public statement_t{
    public:
    ;
    ~statement_return_empty_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_STATEMENT_RETURN_EMPTY;}
};
class statement_return_sth_t:public statement_t{
    public:
    ultimate_expr_t* value;
    ~statement_return_sth_t() override{
        delete value;

    }
    node_type_t get_kind() const override {return NODE_STATEMENT_RETURN_STH;}
};
class statements_stmt_t:public statements_t{
    public:
    statement_t* stmt;
    ~statements_stmt_t() override{
        delete stmt;

    }
    node_type_t get_kind() const override {return NODE_STATEMENTS_STMT;}
};
class statements_multistmt_t:public statements_t{
    public:
    statement_t* stmt;
	statements_t* other_stmts;
    ~statements_multistmt_t() override{
        delete stmt;
delete other_stmts;

    }
    node_type_t get_kind() const override {return NODE_STATEMENTS_MULTISTMT;}
};
class statements_empty_t:public statements_t{
    public:
    ;
    ~statements_empty_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_STATEMENTS_EMPTY;}
};
class func_returntype_hastype_t:public func_returntype_t{
    public:
    composed_type_t* return_type;
    ~func_returntype_hastype_t() override{
        delete return_type;

    }
    node_type_t get_kind() const override {return NODE_FUNC_RETURNTYPE_HASTYPE;}
};
class func_returntype_void_t:public func_returntype_t{
    public:
    ;
    ~func_returntype_void_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_FUNC_RETURNTYPE_VOID;}
};
class arglist_nonempty_singarg_t:public arglist_nonempty_t{
    public:
    token_t *name;
	composed_type_t* arg_type;
    ~arglist_nonempty_singarg_t() override{
        delete arg_type;

    }
    node_type_t get_kind() const override {return NODE_ARGLIST_NONEMPTY_SINGARG;}
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
    node_type_t get_kind() const override {return NODE_ARGLIST_NONEMPTY_MULTIARG;}
};
class arglist_hasarg_t:public arglist_t{
    public:
    arglist_nonempty_t* args;
    ~arglist_hasarg_t() override{
        delete args;

    }
    node_type_t get_kind() const override {return NODE_ARGLIST_HASARG;}
};
class arglist_empty_t:public arglist_t{
    public:
    ;
    ~arglist_empty_t() override{
        
    }
    node_type_t get_kind() const override {return NODE_ARGLIST_EMPTY;}
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
    node_type_t get_kind() const override {return NODE_FUNCTION_DEFAULT;}
};
class top_statement_func_def_t:public top_statement_t{
    public:
    function_t* func;
    ~top_statement_func_def_t() override{
        delete func;

    }
    node_type_t get_kind() const override {return NODE_TOP_STATEMENT_FUNC_DEF;}
};
class top_statement_decl_t:public top_statement_t{
    public:
    declaration_t* decl;
    ~top_statement_decl_t() override{
        delete decl;

    }
    node_type_t get_kind() const override {return NODE_TOP_STATEMENT_DECL;}
};
class top_statement_var_def_t:public top_statement_t{
    public:
    definition_t* def;
    ~top_statement_var_def_t() override{
        delete def;

    }
    node_type_t get_kind() const override {return NODE_TOP_STATEMENT_VAR_DEF;}
};
class top_statement_structdef_t:public top_statement_t{
    public:
    struct_t* structdef;
    ~top_statement_structdef_t() override{
        delete structdef;

    }
    node_type_t get_kind() const override {return NODE_TOP_STATEMENT_STRUCTDEF;}
};
