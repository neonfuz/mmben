typedef struct {
  char *data;
  size_t length;
  size_t size;
} String;

String read_file(const char *path);
