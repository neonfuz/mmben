#include <SDL2/SDL.h>
#include "../../lib/microtar/microtar.h"

int main(int argc, char **argv) {
  SDL_assert(argc > 2);

  mtar_t tar;
  mtar_header_t h;

  /* Open archive for reading */
  int ret = mtar_open(&tar, argv[1], "r");
  if (ret < 0) {
    fprintf(stderr, "%s\n", mtar_strerror(ret));
    return -1;
  }
  /* Print all file names and sizes */
  while ( (mtar_read_header(&tar, &h)) != MTAR_ENULLRECORD ) {
    printf("%s (%d bytes)\n", h.name, h.size);
    mtar_next(&tar);
  }

  mtar_close(&tar);

  return 0;
}
