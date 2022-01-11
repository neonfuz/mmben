#include <SDL2/SDL.h>

typedef enum {
  TVM_PUSH,
  TVM_SET,
  TVM_PRINT,
} TVM_type;

typedef struct {
  TVM_type type : 2;
  SDL_bool backwards : 1;
  union {
    struct {
      Uint16 index, val;
    };
  };
} TVM_event;

typedef Uint16* Uint16_vec;
typedef TVM_event* TVM_event_vec;

typedef struct {
  Uint16_vec stack;
  TVM_event_vec events;
  Uint32 pc;
} TVM_vm;

TVM_vm new_TVM(void);
void TVM_execute(TVM_vm *vm, TVM_event *event);
void TVM_print(TVM_vm *vm);
