#define _GNU_SOURCE
#include <search.h>
#include <SDL2/SDL.h>
#include "../c-vector/vec.h"
#include "lex.h"

static Token_type get_tok_type(char c) {
    switch (c) {
    case '"':  return TOK_STR;
    case '(':  return TOK_LPAR;
    case ')':  return TOK_RPAR;
    case '<':  return TOK_LBR;
    case '>':  return TOK_RBR;
    case ' ':
    case '\n':
    case '\t':
    case '\0': return TOK_NULL;
    default:   return TOK_SYM;
    }
}

typedef struct {
  unsigned inString : 1;
} Lexer_state;

static Token_vec lex_bnl(const char *bnl) {
  Lexer_state state = { 0 };
  Token_vec tokens = vector_create();

  Token *t = vector_add_asg(&tokens);
  t->type = TOK_NULL;
  t->start = 0;
  t->length = 0;

  int i=0;
  do {
    Token_type nexttype = get_tok_type(bnl[i]);
    if (state.inString) {
      if (nexttype == TOK_STR) {
        state.inString = 0;
      } else {

      }
    }
    if (nexttype != t->type) {
      if (t->type != TOK_NULL) {
        t->length = i - t->start;
        t = vector_add_asg(&tokens);
      }
      t->type = nexttype;
      t->start = i;
    }
    ++i;
  } while (bnl[i-1]); // i-1 here to process final \0
  vector_pop(tokens); // remove final TOK_NULL token generated by the \0

  return tokens;
}

static
void Token_print(Token t, char *body) {
  printf("%4d %2d %.*s\n",
         t.start, t.length,
         t.length, t.start + body);
}

#define MIN(a,b) ((a)<(b)?(a):(b))

static const char *Token_compare_body_base = NULL;
static int Token_compare_body_r(const Token *a, const Token *b, const char *base) {
  if (a->type != b->type)
    return a->type - b->type;
  int length = MIN(a->length, b->length);
  const char *A = a->start + base;
  const char *B = b->start + base;
  for (int i=0; i<length; ++i)
    if (A[i] != B[i])
      return A[i] - B[i];

  return a->length - b->length;
}
static int Token_compare_body(const void *a, const void *b) {
  return Token_compare_body_r(a, b, Token_compare_body_base);
}
static void null_free(__attribute((unused)) void *nodep) {}

Lexed *Lexed_compact(Lexed *l) {
  int dest = 0;
  for (unsigned t=0; t<vector_size(l->tokens); ++t) {
    int src = l->tokens[t].start;
    int end = src + l->tokens[t].length;
    l->tokens[t].start = dest;
    for (; src<end; ++src, ++dest) {
      l->body[dest] = l->body[src];
    }
  }
  l->body[dest++] = '\0';
  l->body = realloc(l->body, dest);
  return l;
}

Lexed *Lexed_dedupe(Lexed *l) {
  void *tree = NULL;
  int dest = 0;
  Token_compare_body_base = l->body;

  for (unsigned t=0; t<vector_size(l->tokens); ++t) {
    Token *tok = &l->tokens[t];
    Token **found = tfind(tok, &tree, Token_compare_body);
    if (found) {
      tok->start = (*found)->start;
    } else {
      int src = tok->start;
      int end = src + tok->length;
      tok->start = dest;
      for (; src<end; ++src, ++dest) {
        l->body[dest] = l->body[src];
      }
      tsearch(tok, &tree, Token_compare_body);
    }
  }
  l->body[dest++] = '\0';
  l->body = realloc(l->body, dest);
  tdestroy(tree, null_free);
  return l;
}

void Lexed_print(Lexed lexed) {
  int length = vector_size(lexed.tokens);
  for (int i=0; i<length; ++i)
    Token_print(lexed.tokens[i], lexed.body);
}

Lexed BNL_lex(char *bnl) {
  return (Lexed){
    .body = bnl,
    .tokens = lex_bnl(bnl),
  };
}
