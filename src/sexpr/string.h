typedef struct {
  char *data;
  size_t length;
} String;

String read_file(const char *path);
