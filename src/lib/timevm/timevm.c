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
    .time   = 0,
  };
  return vm;
}

TVM_event TVM_tick_mem(Uint16_vec *stackPtr, const TVM_event *event) {
  Uint16 index = vector_size(*stackPtr) - event->index;
  TVM_event undo = *event;
  switch (event->type) {
  case TVM_SHIFT:
      undo.type = TVM_UNSHIFT;
      vector_insert(stackPtr, index, event->val);
      break;
  case TVM_UNSHIFT:
      undo.val = (*stackPtr)[index-1];
      undo.type = TVM_SHIFT;
      vector_remove(stackPtr, index-1);
      break;
  case TVM_SET:
    swap(&undo.val, &(*stackPtr)[index-1]);
    break;
  case TVM_NOP:
    break;
  case TVM_PRINT:
    for (unsigned i=0; i<vector_size(*stackPtr); ++i)
      printf("%d ", (*stackPtr)[i]);
    putchar('\n');
    break;
  case TVM_SNAP:
  case TVM_ROLLBACK:
     // snap & rollback are handled in TVM_tick. Do nothing here so
     // TVM_tick can blindly call this function while rolling back.
    break;
  }
  return undo;
}

void TVM_tick(TVM_vm *vm) {
  switch (vm->events[vm->pc].type) {
  case TVM_SNAP:
    vm->events[vm->pc].jump = vm->time++;
    break;
  case TVM_ROLLBACK:
    vm->time -= vm->events[vm->pc].jump;
    do {
      // TODO optimize how many calls
      TVM_tick_mem(&vm->stack, &vm->events[vm->pc--]);
    } while (vm->events[vm->pc].type != TVM_SNAP ||
             vm->events[vm->pc].jump != vm->time);
    break;
  default:
    vm->events[vm->pc] = TVM_tick_mem(&vm->stack, &vm->events[vm->pc]);
  }
  vm->pc++;
}

void TVM_print(TVM_vm *vm) {
  TVM_event print = { .type = TVM_PRINT };
  TVM_tick_mem(&vm->stack, &print);
}
