#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 256

typedef enum {
  OBJ_INT,
  OBJ_PAIR
} ObjectType;

typedef struct StructObject {
  unsigned char marked;
  ObjectType type;
  struct StructObject* next;
  union {
    // OBJ_INT
    int value;

    // OBJ_PAIR
    struct {
      struct StructObject* head;
      struct StructObject* tail;
    };
  };
} Object;

typedef struct {
  Object* objects[MAX_STACK_SIZE];
  int stack_size;
  int num_of_objects;
  Object* first_object;
} VM;

void assert(int predicate, char* message);
VM* new_vm();
void push(VM* vm, Object* obj);
Object* pop(VM* vm);
Object* new_object(ObjectType type);
Object* push_int(VM* vm, int value);
Object* push_pair(VM* vm);
void mark(Object* obj);
void mark_all(VM* vm);
Object* get_next_marked_object(VM* vm, Object* node);
void sweep(VM* vm);
void gc(VM* vm);
void traverse_objects(VM* vm);
