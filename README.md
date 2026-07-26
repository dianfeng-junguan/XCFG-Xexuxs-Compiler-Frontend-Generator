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

### 3. Sematic Check

#### Symbol Table 

#### Type Inference



### 4. IR
