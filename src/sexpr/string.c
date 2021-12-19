#include <SDL2/SDL.h>
#include "string.h"

typedef struct {
  char *data;
  size_t length;
} String;

String read_file(const char *path) {
  String s = { NULL, 0 };
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    return s;
  }
  fseek(f, 0, SEEK_END);
  s.length = ftell(f);
  s.data = malloc(s.length+1);
  fseek(f, 0, SEEK_SET);
  for (size_t i=0; i<s.length; ++i)
    s.data[i] = fgetc(f);
  s.data[s.length] = '\0';
  return s;
}

void String_put(String s) {
  for (size_t i=0; i<s.length; ++i)
    fputc(s.data[i], stdout);
}
