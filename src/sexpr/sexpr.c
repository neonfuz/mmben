#include <SDL2/SDL.h>
#include "string.h"

typedef enum {
  T_LPAR,
  T_RPAR,
  T_STR,
  T_INT,
} Token;

typedef struct Lex {
  Token t;
  struct Lex *next;
} Lexed;

Lexed lex_sexpr(const char *sexpr) {
  Lexed l = {0};
  return l;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

}
