#include "../c-vector/vec.h"
#include "timevm.h"

#define swap(a, b) do {   \
    typeof(*a) _tmp = *a; \
    *a = *b;              \
    *b = _tmp;            \
  } while(0)

TVM_vm new_TVM(void) {
  TVM_vm vm = {
    .stack  = vector_create(),
    .events = vector_create(),
    .pc     = 0,
  };
  return vm;
}

void TVM_execute(TVM_vm *vm, TVM_event *event) {
  Uint16 index = vector_size(vm->stack) - event->index;
  switch (event->type) {
  case TVM_PUSH:
    if (!event->backwards) {
      vector_insert(&vm->stack, index, event->val);
    } else {
      event->val = vm->stack[index-1];
      vector_remove(&vm->stack, index-1);
    }
    break;
  case TVM_SET:
    swap(&event->val, &vm->stack[index-1]);
    break;
  case TVM_PRINT:
    for (unsigned i=0; i<vector_size(vm->stack); ++i)
      printf("%d ", vm->stack[i]);
    putchar('\n');
    break;
  }
  event->backwards = !event->backwards;
}

void TVM_print(TVM_vm *vm) {
  TVM_event print = { .type = TVM_PRINT, .backwards = 0 };
  TVM_execute(vm, &print);
}
