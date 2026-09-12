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

This stage includes symbol table establishment, type check, control flow validation and error report.

By default, the valid scope of a function/struct is the whole block the it is in, whether before or after, while a variable only gets accessible after its definition or declaration.

A framework of sematic check is generated including checker functions. The specific checking behavior needs to be written manually.

A sematic check rule file looks like this:

```
[resolve]
definition.deftype: declare(name) check_initializer(value)
definition.defntype: declare(name) check_initializer(value)
statements.definition: visit(def)

[typecheck]
expr.add:check_addable(left,right)
definition.deftype: check_type_assignable(def_type,value)

[flow]
function.default: all_paths_return()
```

`[resolve]` is a stage indicator. The generated checker scans the AST stage by stage, each of which checking a specific category of sematic rules.

`ruleset.rule` is the node that is checked. The node scanned will be applied with functions following `:`.

Those like `declare(name)` are check functions. The generator collects the functions appeared and create empty definitions of them. Despite there are already arguments passed in the rule file, they only act as a comment part that explains what will be used in the coming-up checking. The real arguments include at least the node itself and a context variable where necessary sematic information is included.

#### Symbol Table 

#### Type Inference



### 4. IR
