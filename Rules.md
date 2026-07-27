# Lexer

```
#KEYWORDS
let:\blet\b
fn:\bfn\b
if:\bif\b
else:\belse\b
while:\bwhile\b
break:\bbreak\b
return:\breturn\b
include:\binclude\b
#TYPEKW
int:\bint\b
string_typekw:\bstring\b
char_typekw:\bchar\b
void:\bvoid\b
struct:\bstruct\b
#NUMBER
number:(0x[0_9a_fA_F]+)|([0_9a_fA_F]+h)|(0b[01]+)|(0o[1_7]+)|([01]+b)|([0_9]+)
float:[0_9]+.[0_9]+
#STRING
string:\"[^\"]*\"
#CHAR
char:\'\\?[^\']?\'
#IDENTIFIER
identifier:[a_zA_Z_][a_zA_Z_0_9]*
#OPERATOR
add:\+
minus:-
star:\*
slash:/
percent:\%
property:\.
openparen:\(
closedparen:\)
and:&&
or:\|\|
not:\!
bitand:&
bitor:|
bitnot:~
bitxor:^
shiftleft:<<
shiftright:>>
comma:\,
open_squarebracket:\[
closed_squarebracket:\]
greaterthan:>
greaterequal:>=
lessequal:<=
lessthan:<
equal:==
assign:=
unequal:!=

~BI_OPERATOR
add
minus
star
slash
and
or
not
bitand
bitor
bitxor
property
percent
unequal
greaterthan
lessthan
greaterequal
lessequal
shiftleft
shiftright

~SINGLE_OPERATOR
add
minus
star
not
bitnot
bitand

#SEPARATOR
openbracket:\{
closedbracket:\}
semicolon:;
colon::
#COMMENT
line_comment://.*
block_comment:/\*(.|\n)*\*/
#WHITESPACE
whitespace:\s+
```

# Parser

The `$xxx` is called "node". The class definitions of rules are generated. For each rule, a class is defined and its members are taken from the names after the `@`. The thing before the `@` is called "scanned" here. The member type is inferred by rules below:

```
if scanned is specific token or token category
    member type is the same as the type of token.value
elseif scanned is a category
    member type is a pointer to the node class
end
```

A Node is defined as a class that other rule classes inherit from. The class has a method like `get_type()` and it returns the rule class type, since it is needed to get the exact type after getting the class from the parent node and we only know the node type from the pointer rather than the rule type.


Rules:
```pwsh
$factor:
id:identifier@value
num:#NUMBER@value
ch:#CHAR@value
str:#STRING@value

$expr:
fac:$factor@left
assign:$lvalue@left assign@operator $expr@right
singop:~SINGLE_OPERATOR@operator $expr@right
paren:openparen $expr@left closedparen
biop:$expr@left ~BI_OPERATOR@operator $expr@right
call:$expr@left openparen@operator $expr@right closedparen

$lvalue:
id:identifier@value
deref:star@operator $expr@value
visit:$expr@left property@operator identifier@right

$composed_type:
raw_type:#TYPEKW@inner_type
paren:openparen $composed_type@inner_type closedparen
ptr:$composed_type@pointer_type star
nsizedarr:$composed_type@element_type open_squaredbracket closed_squaredbracket
sizedarr:$composed_type@element_type open_squaredbracket $expr@array_size closed_squaredbracket

$definition:
deftype:let identifier@name:$composed_type@def_type assign $expr@value
defntype:let identifier@name assign $expr@value

$else:
default:else openbracket #statements@statements closedbracket

$elseif:
default:elseif openbracket@condition #statements@statements closedbracket

$elseif_else:
empty:!
onlyelse:$else@else_block
chain:$elseif@elseif_block $elseif_else@rest_block

$if:
default:if $expr@condition openbracket $statements@statements closedbracket $elseif_else@rest_block

$while:
default:while $expr@condition openbracket $statements@statements closedbracket

$structmembers:
empty:!
singmem:identifier@name:$composed_type@def_type
multimem:identifier@name:$composed_type@def_type comma $structmembers@other_members

$struct:
default:struct identifier@name openbracket $structmembers@members closedbracket

$declaration:
varntype:let identifier@name semicolon
var:let identifier@name colon $composed_type@def_type semicolon
fn:fn identifier@name openparen $arglist@args closedparen $func_returntype@return_type semicolon
struct:struct identifier@name openbracket $structmembers@members closedbracket

$statement:
expr:$expr@expr semicolon
definition:$definition@def semicolon
if:$if@if_stmt
while:$while@while_stmt
declaration:$declaration@decl_stmt

$statements:
empty:!
stmt:$statement@stmt
multistmt:$statement@stmt $statements@other_stmts

$func_returntype:
void:!
hastype:minus greaterthan $composed_type@return_type

$arglist_nonempty:
singarg:identifier@name:$composed_type@arg_type
multiarg:identifier@name:$composed_type@arg_type comma $arglist_nonempty@other_args

$arglist:
empty:!
hasarg:$arglist_nonempty@args

$function:
default:fn identifier openparen $arglist@args closedparen $func_returntype@return_type openbracket $statements@stmts closedbracket

```

# Sematic

1. Create symbol tables
2. grammar checking

## Symbol table

If a symbol is defined or declared, it is available in all the scope it is in, both before or after the definition or declaration. 

## Grammar rules

Allowed type conversion:

```
string <=> int
char <=> int
pointer <=> int
pointer <=> string
array <=> pointer
```



# IR

You might want to do something to the AST tree to make it easier to generate assembly from it. IR is something you create after you do some conversion to the AST tree.

Definitions are extracted and those in a same scope are collected into a single block called `allocsyms` to be put at the beginning of the scope where all symbols in this scope are allocated at once. Specific size of symbols is not got involved yet but such re_ordering makes it easier to generate assembly thereafter. And `freesyms` is also inserted to mark the end of symbol lifetime.

```

```

# Assembly

Here we visit the IR tree at depth_first order. For expression, temporary var is needed and a table is maintained to record used temp vars. For example, a expr node with operator=add will visit its leaves first and generate code of leaves so that values of leaves are ready when needed. The values of leaves are stored in temp vars.