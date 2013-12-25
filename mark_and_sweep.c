#include "mark_and_sweep.h"

void assert(int predicate, char* message) {
  if (!predicate) {
    printf("Assertion Failed: %s", message);
    exit(1);
  }
}

VM* new_vm() { 
  VM* vm = malloc(sizeof(VM));
  vm->stack_size = 0;
  vm->num_of_objects = 0;
  vm->first_object = NULL;

  return vm;
}

void push(VM* vm, Object* obj) {
  assert(vm->stack_size < MAX_STACK_SIZE, "Stack Overflow!");
  vm->objects[vm->stack_size++] = obj;
  obj->next = vm->first_object;
  vm->first_object = obj;
  vm->num_of_objects++;
}

Object* pop(VM* vm) {
  assert(vm->stack_size > 0, "Stack Underflow!");
  return vm->objects[--vm->stack_size];
}

Object* new_object(ObjectType type) {
  Object* obj = malloc(sizeof(Object));
  obj->type = type;
  obj->marked = 0;
  obj->next = NULL;

  return obj;
}

Object* push_int(VM* vm, int value) {
  Object* obj = new_object(OBJ_INT);
  obj->value = value;
  push(vm, obj);

  return obj;
}

Object* push_pair(VM* vm) {
  Object* obj = new_object(OBJ_PAIR);
  obj->tail = pop(vm);
  obj->head = pop(vm);
  push(vm, obj);

  return obj;
}

void mark(Object* obj) {
  if (obj->marked == 1)
    return;

  ObjectType type = obj->type;
  switch(type) {
    case OBJ_INT:
      obj->marked = 1;
      break;
    case OBJ_PAIR:
      obj->marked = 1;
      mark(obj->head);
      mark(obj->tail);
      break;
  }
}

void mark_all(VM* vm) {
  int i;
  for (i = 0; i < vm->stack_size; i++)
    mark(vm->objects[i]);
}

Object* get_next_marked_object(VM* vm, Object* node) {
  while (node != NULL) {
    if (node->marked == 1) {
      node->marked = 0;
      return node;
    }
    Object* unreachable = node;
    node = unreachable->next;
    free(unreachable);
    vm->num_of_objects--;
  }

  return NULL;
}

void sweep(VM* vm) {
  Object* obj = vm->first_object;
  vm->first_object = get_next_marked_object(vm, obj);
  obj = vm->first_object;
  while (obj != NULL) {
    Object* node = obj->next; 
    obj->next = get_next_marked_object(vm, node);
    obj = obj->next;
  }
}

void gc(VM* vm) {
  mark_all(vm);
  sweep(vm);
}

// For testing purposes
void traverse_objects(VM* vm) {
  Object* obj = vm->first_object;
  while (obj != NULL) {
    if (obj->type == OBJ_PAIR)
      printf("Marked %d and it is PAIR\n", obj->marked);
    else
      printf("Marked %d and VALUE %d\n", obj->marked, obj->value);

    obj = obj->next;
  }
}
