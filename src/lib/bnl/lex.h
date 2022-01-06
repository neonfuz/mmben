typedef enum {
  TOK_NULL,
  TOK_SYM,
  TOK_STR,
  TOK_LPAR, TOK_RPAR,
  TOK_LBR,  TOK_RBR,
  TOK_MAX,
} Token_type;

typedef struct {
  Token_type type;
  int start, length;
} Token;

typedef Token* Token_vec;

typedef struct {
  char *body;
  Token_vec tokens;
} Lexed;

void Lexed_print(Lexed lexed);
Lexed *Lexed_compact(Lexed *l);
Lexed *Lexed_dedupe(Lexed *l);
