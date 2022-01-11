#include <SDL2/SDL.h>
#include "../../lib/c-vector/vec.h"
#include "../../lib/timevm/timevm.h"

int main(int argc, char **argv) {
  TVM_vm vm = new_TVM();
  TVM_event *e = NULL;

  e = vector_add_asg(&vm.events);
  e->type = TVM_PUSH;
  e->backwards = 0;
  e->index = 0;
  e->val = 1;

  e = vector_add_asg(&vm.events);
  e->type = TVM_PUSH;
  e->backwards = 0;
  e->index = 0;
  e->val = 2;

  e = vector_add_asg(&vm.events);
  e->type = TVM_PUSH;
  e->backwards = 0;
  e->index = 0;
  e->val = 3;

  e = vector_add_asg(&vm.events);
  e->type = TVM_SET;
  e->backwards = 0;
  e->index = 1;
  e->val = 5;

  e = vector_add_asg(&vm.events);
  e->type = TVM_PUSH;
  e->backwards = 1;
  e->index = 0;
  e->val = 0;

  while (vm.pc < vector_size(vm.events)) {
    TVM_tick(&vm);
    TVM_print(&vm);
  }
  while (vm.pc) {
    TVM_revtick(&vm);
    TVM_print(&vm);
  }

  return 0;
}
