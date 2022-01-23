#include <SDL2/SDL.h>

typedef enum {
  TVM_NOP,
  TVM_PRINT,
  TVM_SHIFT,
  TVM_UNSHIFT,
  TVM_SET,
  TVM_SNAP,
  TVM_ROLLBACK,
} TVM_type;

typedef struct {
  TVM_type type : 3;
  union {
    struct { Uint16 index, val; };
    struct { Uint32 jump; };
  };
} TVM_event;

typedef Uint16* Uint16_vec;
typedef TVM_event* TVM_event_vec;

typedef struct {
  Uint16_vec stack;
  TVM_event_vec events;
  Uint32 pc, time;
} TVM_vm;

TVM_vm new_TVM(void);
void TVM_print(TVM_vm *vm);
void TVM_tick(TVM_vm *vm);
