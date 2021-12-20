#include <SDL2/SDL.h>
#include "string.h"

String read_file(const char *path) {
  String s = { NULL, 0, 0 };
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    return s;
  }
  fseek(f, 0, SEEK_END);
  s.length = ftell(f);
  s.size = s.length + 1;
  s.data = malloc(s.size);
  fseek(f, 0, SEEK_SET);
  for (size_t i=0; i<s.length; ++i)
    s.data[i] = fgetc(f);
  s.data[s.length] = '\0';
  return s;
}

void String_print(String s) {
  for (size_t i=0; i<s.length; ++i)
    fputc(s.data[i], stdout);
}
