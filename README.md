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

The IR rule file defines instructions to be generated for certain node. 
```
definition.deftype:
    temp %1
    temp %2
    alloc $sym %2 
    visit value %1
    store %2 %1
    yield_none
expr.add:
    temp %1
    temp %2
    temp %3
    visit left %1
    visit right %2
    add %1 %2 %3
    yield %3
a.b:
    temp %1
    temp %2
    temp %3
    temp %bogus
    visit left %1
    visit_ref left %bogus
    visit right %2
    call func %1 %2 =%3
    yield %3
...
```
`%temp` is the temporary variable. Temporary variables are recorded in a class that holds its number and type. 

Instructions:

`temp <temp>`: to define a temp var. This instruction adds a temp var to the temp var table of this rule and does not actually generate an IR instruction. A temp var can be re-loaded multiple times and each load overrides pervious value.

`cast $conversion(<nodemember>) <temp:src> <temp:dest>`: cast a temp var of `nodemember` type to the dest type recorded in `nodemember` previously in sematic stage.
Sematic stage code is supposed to maintain a type system and record basic types and a type conversion recipe:
```c++
using conversion_id_t = std::uint32_t;

using conversion_lower_fn_t = bool (*)(
    const ir_value_t& source,
    type_id_t target_type,
    ir_value_t& result,
    ir_builder_t& builder
);

struct conversion_descriptor_t {
    conversion_id_t id;
    type_id_t source_type;
    type_id_t target_type;
    conversion_lower_fn_t lower;
};
class type_system_t {
public:
    std::unordered_map<
        conversion_id_t,
        conversion_descriptor_t
    > conversions;

    const conversion_descriptor_t* find_conversion(
        conversion_id_t id
    ) const;
};
```
and when generating IR, the `$conversion()` is replaced by according conversion id such as 0 for `identity`, 1 for `int_to_long` (just an example) and so on:
```
cast 1 %1 %2
```

`visit <node> <temp>`: to visit `node` and store its evaluated result in `temp`.

`visit_ref <node> <temp>`: to get the address of `node` and store it in `temp`. Normal `visit` yields the value wrapped in a temp var, so this instruction is need when you need to refer to the original symbol rather than the temp var.

`store <temp:symbol-place> <temp>`: to store `temp` in `symbol-place`.

`load <temp:symbol-place> <temp:result>`: to load `temp` from `symbol-place`.

`call <func> [arg arg1...] =<temp>`: to call a function and store its result. The `func` mentioned here is a function symbol. `arg`s are supposed to be temp vars.

`call_value <temp> [arg arg1...] =<temp>`: treat the temp var as a function pointer and call it. `arg`s are supposed to be temp vars.

Note that by keeping nothing after `=`, the result of the function is discarded.

`alloc <symbol> <temp>`: to allocate a symbol. `symbol` is a helper notation of the symbol defined by this node and does not have to be necessarily the same name as the real symbol name or name of the member where symbol name is stored. The generated code gets the symbol by checking the connecting created previously in sematic stage. `temp` saves the place of the symbol.

The format of `symbol` is `$name`.

`yield <temp>`: to yield a temp var to the parent and return to the parent IR generation process.

`yield_none`: to return to its IR parent without yielding anything.

`return <temp>`: to return the function.

`return_none`: to return the function.

`if <temp> <label-true> <label-false>`: if a value of the temp var is true, jump to label-true otherwise label-false.

`goto <label>`: to jump to a label.

`label <label>`: to declare a label. The name format of a label is `#label`. Note that a scope of a label is restricted in the node rule, and you cannot refer to it in another node rule in the rule file. This is just for rule file. In actual IRs, you can use function to refer to labels from far away as long as you store them in the context ahead.

Besides, there are built-in operations:

```
add/sub/mul/div/mod/shl/shr temp temp dest_temp
bitand/bitor/bitxor temp temp dest_temp
bitnot/negate/minus temp dest_temp
and/or temp temp dest_temp
deref temp dest_temp  # load the pointed value of temp to dest_temp
equ/neq/gt/lt/ge/le temp temp dest_temp
```

The actual data structure of IR is graph. The generated code takes in the AST and returns an IR graph. The structure of an IR graph is:
```
module
    function
        block
            instruction
            terminator
```
`terminator` here includes 
```
return
return_none
goto
if
```
