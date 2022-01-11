#include <SDL2/SDL.h>
#include "../../lib/c-vector/vec.h"
#include "../../lib/timevm/timevm.h"

int main(int argc, char **argv) {
  TVM_vm vm = new_TVM();
  TVM_event_vec events = vector_create();
  TVM_event *e = NULL;

  e = vector_add_asg(&events);
  e->type = TVM_PUSH;
  e->index = 0;
  e->val = 1;
  e->backwards = 0;

  e = vector_add_asg(&events);
  e->type = TVM_PUSH;
  e->index = 0;
  e->val = 2;
  e->backwards = 0;

  e = vector_add_asg(&events);
  e->type = TVM_PUSH;
  e->index = 0;
  e->val = 3;
  e->backwards = 0;

  e = vector_add_asg(&events);
  e->type = TVM_SET;
  e->index = 1;
  e->val = 5;
  e->backwards = 0;

  for (vm.pc=0; vm.pc<vector_size(events); ++vm.pc) {
    TVM_execute(&vm, &events[vm.pc]);
    TVM_print(&vm);
  }
  for (vm.pc=vector_size(events); vm.pc; --vm.pc) {
    TVM_execute(&vm, &events[vm.pc-1]);
    TVM_print(&vm);
  }

  return 0;
}
