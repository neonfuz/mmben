#include <SDL2/SDL.h>
#include "../sexpr/string.h"
#include "../sexpr/sexpr.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    return 1;
  }

  return 0;
}
