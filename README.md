# Compiler Generator
Generates C source files of a compiler according to the rules defined in the files.

## Rule File Format

### 1. Lexer

The Generator generates lexer using regex.

format:

```
#KEYWORDS:
let:(let)
#NUMBER:
number:((0x|b|o)[0-9A-Fa-f]+)|[0-9]+(h|b)
float:[0-9]+.[0-9]+
~BI-OPERATOR
add
minus
star
```

The `#xxx` is the category of the tokens. The `a:b` is the token rule, where a is the token name and b is the regex pattern. The `~xxx` is the category which contains defined tokens. This is used to put tokens into multiple categories for convenience.

### 2. Parser

```
$factor:
identifier
#NUMBER

$expr:
$factor #BI-OPERATOR $expr
#SINGLE-OPERATOR $expr
$factor

$definition:
let identifier:#TYPEKW assign $expr semicolon
let identifier assign $expr semicolon

```

The generated code is expected to generate AST tree where all absorbed tokens will be converted into nodes. Note that `!` means empty.

### Left-combined

Rulesets like

```
$expr:
add: $expr add $term
```

are left-combined. They feature in beginning the recipe with the rulesets themselves. For such rulesets, the rules that are not left-combined still has its corresponding rule parser functions like

```c
expr_add_t* parse_expr_add(tokenstream_t *ts){
    ...
}
```

while the ruleset parser functions are changed into a loop form.

```c
static expr_paren_t* parse_expr_paren(tokenstream_t *ts) {
    // ... openparen ...
    n->expr = parse_expr(ts);      
    // ... closedparen ...
}
static expr_t* parse_expr_start(tokenstream_t *ts) {
    expr_t *n;
    if (n = (expr_t*)parse_expr_paren(ts)) return n;
    if (n = (expr_t*)parse_term(ts))       return n; 
    return NULL;
}
// this one
expr_t* parse_expr(tokenstream_t *ts) {
    expr_t *node = parse_expr_start(ts);
    if (!node) return NULL;
    for (;;) {
        if (peek(ts)->token_type == TOKEN_ADD) {
            consume(ts);
            expr_add_t *n = new expr_add_t();
            n->left = node; n->right = parse_term(ts);
            node = n; 
        } else if (peek(ts)->token_type == TOKEN_MINUS) { ... }
        else break;
    }
    return node;
}

```

In a loop, the ruleset parser function collects nodes needed and then create node from them.
Another function is created `xxx_start` which is basically trying non-left-combined rules. It is used in ruleset parser function to parse the start of left-combined rules.

### 3. Sematic Check

This stage includes symbol table establishment, type checking, control-flow validation and diagnostics.

By default, functions and struct types are visible throughout their containing block, while variables become visible after their declaration or definition. The semantic checker is organized as several passes:

```
predeclare  collect names that are visible throughout a scope
resolve    create scopes and resolve symbols and members
typecheck  infer expression types and validate operations
flow       validate returns, loops and reachability
```

A semantic rule file is `sematic.rule`. Its basic form is:

```
[pass]
ruleset.rule:
    enter check_before_children(arguments)
    children member1 member2
    leave check_after_children(arguments)
```

`[pass]` selects the semantic pass. `ruleset.rule` identifies an AST node, for example `expr.add` refers to the `add` rule under `$expr` in `parser.rule`.

The three traversal directives are explicit:

* `enter` runs when the visitor enters the node. Use it to create scopes, establish context, or predeclare symbols.
* `children` recursively visits the listed AST members. The members are the names after `@` in `parser.rule`.
* `leave` runs after the listed children have been visited. Use it for checks that depend on child results, such as type checking and control-flow aggregation.

For example:

```
[resolve]
function.default:
    enter enter_function_scope()
    enter declare_parameters(args)
    children return_type stmts
    leave leave_scope()

[typecheck]
expr.add:
    children left right
    leave check_addable(left,right) infer_binary_result_type(left,right)

[flow]
function.default:
    children stmts
    leave require_all_paths_return(stmts)
```

The generator can collect the action names and generate their declarations or empty definitions. Arguments such as `left` and `right` document which node members an action uses; the generated implementation should also receive the current node and a semantic context containing scopes, types and diagnostics.

The usual dependency order is `predeclare -> resolve -> typecheck -> flow`. Within one node, scope/context actions normally run in `enter`, child-dependent checks in `leave`.

#### Symbol Table 

#### Type Inference



### 4. IR
