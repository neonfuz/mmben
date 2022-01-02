typedef enum {
  TOK_NULL,
  TOK_LPAR,
  TOK_RPAR,
  TOK_LBR,
  TOK_RBR,
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
} Lexed;

void Lexed_print(Lexed lexed);

typedef enum {
  OBJ_NULL,
  OBJ_LIST,
  OBJ_SYM,
} Object_type;

typedef struct {
  unsigned val  : 16;
  unsigned next : 16;
} list_Object;

typedef struct {
  unsigned name : 16;
} sym_Object;

typedef struct {
  Object_type type : 2;
  union {
    list_Object list;
    sym_Object sym;
  };
} Object;

typedef Object* Object_vec;

typedef struct {
  Object_vec objs;
  char *syms;
} AST;

Lexed BNL_lex(char *bnl);
AST BNL_parse(char *bnl);
