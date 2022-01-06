#include <SDL2/SDL.h>
#include "../../lib/bnl/bnl.h"
#include "../../lib/bnl/util.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    return 1;
  }
  SDL_assert(sizeof(Object) == 8);
  char *content = read_file(argv[1]);
  Lexed lexed = BNL_lex(content);
  Lexed_dedupe(&lexed);
  Lexed_print(lexed);

  return 0;
}
