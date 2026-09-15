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
    action_before_child(arguments)
    visit(member1)
    visit(member2)
    action_after_children(arguments)
```

`[pass]` selects the semantic pass. `ruleset.rule` identifies an AST node, for example `expr.add` refers to the `add` rule under `$expr` in `parser.rule`.

Every indented step is executed once, from top to bottom. There are two kinds of steps:

* `visit(member)` recursively applies the current pass to one AST child. `visit` takes exactly one argument. To visit several children, write one `visit` line for each child in the required order.
* `action(member1,member2,...)` calls a user-supplied semantic action. An action may take zero or more arguments, and every argument must be the name of a direct member of the current parser rule (the name after `@` in `parser.rule`).

The position of an action relative to `visit` determines whether it runs before, between, or after child visits. This replaces separate `enter`, `children`, and `leave` directives and also permits more precise ordering, such as entering a scope after checking a condition but before visiting a body.

If a node has no explicit rule in a pass, the generator automatically visits all of its AST children in parser-rule order. Once a node has an explicit rule, that automatic traversal is replaced completely: every child needed by that pass must appear in an explicit `visit(child)` step. Token members must not be passed to `visit`; they may be passed to ordinary actions.

For example:

```
[resolve]
function.default:
    enter_function_scope()
    declare_parameters(args)
    visit(return_type)
    visit(stmts)
    leave_scope()

[typecheck]
expr.add:
    visit(left)
    visit(right)
    check_addable(left,right)
    infer_binary_result_type(left,right)

[flow]
function.default:
    enter_function_scope()
    visit(stmts)
    require_all_paths_return(stmts)
    leave_scope()
```

The generator collects action names and generates their declarations and empty definitions. For an action written as `check_addable(left,right)`, the generated C++ function receives the current `ast_node_t*`, the typed values of `left` and `right`, and the `sematic_context_t*`, in that order. Returning `false` stops the current pass immediately. `visit` is built in and is not emitted as a user action.

Passes run in file order; the usual dependency order is `predeclare -> resolve -> typecheck -> flow`. Scope/context actions normally precede the children whose interpretation they affect, while checks that consume inferred child types or flow summaries follow those visits.

#### Symbol Table 

#### Type Inference



### 4. IR
