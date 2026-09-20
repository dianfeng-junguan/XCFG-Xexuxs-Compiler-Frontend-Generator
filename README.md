# XCFG - Xexux's Compiler Frontend Generator
XCFG (Xexux's Compiler Frontend Generator) generates C++17 lexer, parser and semantic-checking source files from rule files. The generated frontend tokenizes source text, builds an AST and applies semantic passes to it.

## Usage

The repository stores rule files in `rule/` and C++ templates in `template/`. Run the generator with:

```bash
mkdir -p generated
cargo run -- --rules-dir rule --template-dir template --output-dir generated
```

The output directory must already exist. The generator writes:

```text
lexer.cpp
lexer.h
parser.cpp
parser.h
sematic.cpp
sematic.h
sematic_user.cpp
```

Command-line options:

```text
-t, --template-dir <dir>  C++ template directory; defaults to template
-r, --rules-dir <dir>     Rule directory; defaults to the current directory
-o, --output-dir <dir>    Output directory; defaults to the current directory
```

`sematic_user.cpp` contains generated empty action implementations. Replace their bodies with the language-specific semantic checks. The file is generated again on every run, so preserve completed implementations before regenerating.

## Todos

- regex checked in rust but used in cpp
- Connect the existing IR generator to the command-line generation flow

## Rule File Format

### 1. Lexer

The Generator generates lexer using regex.

format:

```
#KEYWORDS
let:\blet\b
fn:\bfn\b

#NUMBER
float:[0-9]+\.[0-9]+
number:[0-9]+

#OPERATOR
add:\+
minus:-
star:\*

~BI_OPERATOR
add:
minus:
star:
```

`#NAME` starts a category that defines tokens. A line of the form `name:pattern` defines one token, where `name` becomes part of the generated C++ token enum and `pattern` is its regular expression.

`~NAME` starts a reference category. Its entries use `token_name:` and refer to tokens already defined in `#` categories. Reference categories let the same token participate in several logical groups.

Categories and rules are tried in file order. Put longer or more specific token rules before shorter overlapping rules. A token regex must not match the empty string.

### 2. Parser

```
$factor:
id: identifier@value
number: #NUMBER@value

$term:
mul: $term@left star $factor@right
factor: $factor@expr

$expr:
add: $expr@left add $term@right
sub: $expr@left minus $term@right
term: $term@expr

$optional_expr:
some: $expr@expr
empty: !
```

`$name:` starts a ruleset. Every production has the form `rule_name: recipe`.

Recipe terms are:

* `$ruleset` to parse another AST ruleset.
* `#CATEGORY` or `~CATEGORY` to consume any token in a lexer category.
* `token_name` to consume one specific token type.
* `!` for an empty recipe.

Append `@member_name` to a term to store it in the generated AST node. A stored `$ruleset` becomes an AST child pointer, while a stored token or token category becomes a `token_t*`. Terms without `@member_name` are consumed but not stored.

The generated top-level lexer and parser return a result containing both `success` and the produced token stream or AST. Callers must not pass a failed lexer result to the parser, or a failed parser result to semantic analysis. Parser error recovery may leave partial AST roots in a failed result.

### Left-combined

Rulesets like

```
$expr:
add: $expr add $term
```

are left-combined because the recipe begins with its own ruleset. Non-left-combined rules parse the initial operand. A left-combined rule receives that operand and parses the remaining recipe through a generated function similar to:

```cpp
expr_add_t* parse_expr_add_t_nostart(
    expr_t* start_node,
    tokenstream_t* tokenstream
) {
    ...
}
```

The ruleset parser itself is generated as a loop. The following is simplified pseudocode; generated parsers use the transaction methods on `tokenstream_t` for backtracking.

```cpp
static expr_paren_t* parse_expr_paren_t(tokenstream_t* ts) {
    // ... openparen ...
    n->expr = parse_expr_t(ts);
    // ... closedparen ...
}
static expr_t* parse_expr_t_start(tokenstream_t* ts) {
    expr_t* node;
    if ((node = parse_expr_term_t(ts))) return node;
    return nullptr;
}
expr_t* parse_expr_t(tokenstream_t* ts) {
    ts->begin_parsing();
    expr_t* node = parse_expr_t_start(ts);
    if (!node) {
        ts->reset();
        return nullptr;
    }
    while (true) {
        expr_t* next = nullptr;
        if ((next = parse_expr_add_t_nostart(node, ts))) {
            node = next;
            continue;
        } else if ((next = parse_expr_sub_t_nostart(node, ts))) {
            node = next;
            continue;
        } else {
            break;
        }
    }
    ts->end_parsing();
    return node;
}

```

Each successful suffix parse wraps the previous node as the new node's left child. The generated `parse_xxx_start` helper tries non-left-combined rules to obtain the first node.

### 3. Sematic Check

This stage includes symbol table establishment, type checking, control-flow validation and diagnostics.

By default, functions and struct types are visible throughout their containing block, while variables become visible after their declaration or definition. The semantic checker is organized as several passes:

```
predeclare  collect names that are visible throughout a scope
resolve    enter recorded scopes and resolve symbols and members
typecheck  infer expression types and validate operations
definite_init validate reads and merge definite-initialization state
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

The position of an action relative to `visit` determines whether it runs before, between, or after child visits. 

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

The generator collects action names and generates their declarations and empty definitions. For an action written as `check_addable(left,right)`, the generated C++ function receives the current `ast_node_t*`, the typed values of `left` and `right`, and the `sematic_context_t*`, in that order. Returning `false` aborts the entire semantic analysis. `visit` is built in and is not emitted as a user action.

Passes run in file order. The current rule file uses `predeclare -> resolve -> typecheck -> definite_init -> flow`. `predeclare` creates and records scopes with `create_*_scope()`. Later passes use `enter_*_scope()` to enter those existing scopes. Scope/context actions normally precede the children whose interpretation they affect, while checks that consume inferred child types or flow summaries follow those visits.

#### Symbol Table 

#### Type Inference



### 4. IR

The IR rule parser and source generator are experimental and are not currently invoked by the command-line frontend generation flow. The IR rule file defines instructions to be generated for a specific AST node.
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

`temp <temp>`: declare a temporary value for this rule. It generates a local `tempvar_t` initialized with `context->create_tempvar()` but does not add an IR instruction to the graph. Declare each temporary once before its first use.

`cast $conversion(<nodemember>) <temp:src> <temp:dest>`: cast a temporary value using the conversion previously recorded for `nodemember` by the semantic stage. The identifier before the parentheses documents the conversion role; current code generation obtains the conversion with `context->get_conversion(node->nodemember)`.

The semantic stage is expected to maintain a type system and conversion descriptors such as:
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
The generated C++ passes the resolved conversion descriptor to `ir_cast_t`; the rule text is not rewritten into a numeric instruction before C++ generation.

`visit <node> <temp>`: to visit `node` and store its evaluated result in `temp`.

`visit_ref <node> <temp>`: to get the address of `node` and store it in `temp`. Normal `visit` yields the value wrapped in a temp var, so this instruction is needed when you need to refer to the original symbol rather than the temp var.

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

`decllabel <label>`: to declare a label. A label should be declared before being used.

`label <label>`: to indicate that a new basic_block named `label` has started. The name format of a label is `#label`. Note that a scope of a label is restricted in the node rule, and you cannot refer to it in another node rule in the rule file. This is just for rule file. In actual IRs, you can use function to refer to labels from far away as long as you store them in the context ahead.

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

The generated code follows this form:
```c++
tempvar_t ir_ruleset_rule(
    ruleset_rule_t* node,
    ir_graph_t* graph,
    ir_context_t* context
) {
    /*
    
    temp %1
    temp %2
    alloc $sym %2 
    visit value %1
    store %2 %1
    ...
    yield %1
    */
    tempvar_t temp_1 = context->create_tempvar();
    tempvar_t temp_2 = context->create_tempvar();
    graph->add_ir(new ir_alloc_t(context->get_symbol(node), temp_2));
    ...
    basic_block_id_t label_end = graph->create_block();
    graph->connect(graph->get_current_block(), label_end);
    graph->set_current_block(label_end);
    ...
    return temp_1;
}
```
Each rule generates a function that processes specific node type and generates final IR.
```c++
for (auto* node : roots) {
    switch (node->get_kind()) {
        case NODE_RULESET_RULE:
            visit(node, &graph, &context);
            break;
        ...
    }
}
```
