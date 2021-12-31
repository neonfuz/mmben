static char *read_file(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  int length = ftell(f);
  char *str = malloc(length + 1);
  str[length] = '\0';
  fseek(f, 0, SEEK_SET);
  for (size_t i=0; i<length; ++i)
    str[i] = fgetc(f);
  return str;
}
