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
string:\bstring\b
char:\bchar\b
void:\bvoid\b
struct:\bstruct\b
#NUMBER
number:(0x[0-9a-fA-F]+)|([0-9a-fA-F]+h)|(0b[01]+)|(0o[1-7]+)|([01]+b)|([0-9]+)
float:[0-9]+.[0-9]+
#STRING
string:\"[^\"]*\"
#CHAR
char:\'\\?[^\']?\'
#IDENTIFIER
identifier:[a-zA-Z_][a-zA-Z_0-9]*
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

~BI-OPERATOR
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

The `$xxx` is called "node". The struct definitions of nodes are generated. For each node, a struct is defined and its members are taken from the names after the `@`. The thing before the `@` is called "scanned" here. The member type is inferred by rules below:

```
if scanned is specific token or token category
    member type is the same as the type of token.value
elseif scanned is a category
    member type is a pointer to the structs in categories
end
```

For every node struct, its members are sum of names occurred in all its generation rules. Some members might have multiple types inferred from different rules and they are defined as unions, the name of which is the name collected from rules and its inner member names are set as the rule name. 

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
singop:~SINGLE-OPERATOR@operator $expr@right
paren:openparen $expr@left closedparen
biop:$expr@left ~BI-OPERATOR@operator $expr@right
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

$elseif-else:
empty:!
onlyelse:$else@else_block
chain:$elseif@elseif_block $elseif-else@rest_block

$if:
default:if $expr@condition openbracket $statements@statements closedbracket $elseif-else@rest_block

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



# IR

```

```