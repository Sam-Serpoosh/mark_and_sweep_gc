#include "mark_and_sweep.h"

void test1() {
  printf("Test 1: Objects on stack are preserved.\n");
  VM* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);

  gc(vm);
  assert(vm->num_of_objects == 2, "Should have preserved objects.");
}

void test2() {
  printf("Test 2: Unreached objects are collected.\n");
  VM* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  pop(vm);
  pop(vm);

  gc(vm);
  assert(vm->num_of_objects == 0, "Should have collected objects.");
}

void test3() {
  printf("Test 3: Reach nested objects.\n");
  VM* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  push_pair(vm);
  push_int(vm, 3);
  push_int(vm, 4);
  push_pair(vm);
  push_pair(vm);

  gc(vm);
  assert(vm->num_of_objects == 7, "Should have reached objects.");
}

void test4() {
  printf("Test 4: Handle cycles.\n");
  VM* vm = new_vm();
  push_int(vm, 1);
  push_int(vm, 2);
  Object* a = push_pair(vm);
  push_int(vm, 3);
  push_int(vm, 4);
  Object* b = push_pair(vm);

  a->tail = b;
  b->tail = a;

  gc(vm);
  assert(vm->num_of_objects == 4, "Should have collected objects.");
}

int main(int argc, char** argv) {
  test1();
  test2();
  test3();
  test4();

  return 0;
}
