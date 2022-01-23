#include <SDL2/SDL.h>
#include "../../lib/c-vector/vec.h"
#include "../../lib/timevm/timevm.h"

int main(int argc, char **argv) {
  TVM_vm vm = new_TVM();
  TVM_event *e = NULL;

#define EVENT_PUSH_IV(_type, _index, _val)      \
  e = vector_add_asg(&vm.events);               \
  e->type = _type;                              \
  e->index = _index;                            \
  e->val = _val

#define EVENT_PUSH_J(_type, _jump)              \
  e = vector_add_asg(&vm.events);               \
  e->type = _type;                              \
  e->jump = _jump

#define EVENT_SHIFT(i, v)   EVENT_PUSH_IV(TVM_SHIFT,   i, v)
#define EVENT_UNSHIFT(i)    EVENT_PUSH_IV(TVM_UNSHIFT, i, 0)
#define EVENT_SET(i, v)     EVENT_PUSH_IV(TVM_SET,     i, v)
#define EVENT_PRINT()       EVENT_PUSH_IV(TVM_PRINT,   0, 0)
#define EVENT_NOP()         EVENT_PUSH_IV(TVM_NOP,     0, 0)
#define EVENT_SNAP()        EVENT_PUSH_J (TVM_SNAP,       0)
#define EVENT_ROLLBACK(j)   EVENT_PUSH_J (TVM_ROLLBACK,   j)

  EVENT_SHIFT(   0, 1);
  EVENT_SHIFT(   0, 2);
  EVENT_SHIFT(   0, 3);
  EVENT_PRINT(       );
  EVENT_SNAP(        );
  EVENT_SET(     1, 5);
  EVENT_ROLLBACK(   1);
  EVENT_NOP(         );
  EVENT_UNSHIFT( 0   );
  EVENT_PRINT(       );
  EVENT_PRINT(       );

  while (vm.pc < vector_size(vm.events)) {
    TVM_tick(&vm);
  }
//  while (vm.pc) {
//    TVM_revtick(&vm);
//    TVM_print(&vm);
//  }

  return 0;
}
