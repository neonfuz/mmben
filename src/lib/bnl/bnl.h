typedef enum {
  TOK_NULL,
  TOK_LPAR,
  TOK_RPAR,
  TOK_SYM,
} Token_type;

typedef struct {
  Token_type type;
  int start, length;
} Token;

typedef Token* Token_vec;

typedef struct {
  char *body;
  Token_vec tokens;
} AST;

AST AST_parse(char *sexpr);
void AST_print(AST ast);