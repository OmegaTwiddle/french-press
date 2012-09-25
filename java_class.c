/**
 * Holds the info for a java class
 */

typedef struct java_const {
  int index;
  char tag;
  char * info;
  struct java_const * next;
} java_const, *java_const_p;

typedef struct java_field {
  int x;
} java_field, *java_field_p;

typedef struct java_method {

} java_method, *java_method_p;

typedef struct java_attr {

} java_attr, *java_attr_p;


typedef struct java_class_s {
  int magic;
  short minor;
  short major;
  short const_count;
  java_const * const_pool;
  short access_flags;
  short this_class;
  short super_class;
  short interfaces_count;
  short * interfaces;
  short fields_count;
  java_field * fields;
  short methods_count;
  java_method * methods;
  short attr_count;
  java_attr * attrs;
} java_class_s, *java_class_p;


void add_constant(java_class_s * class_object, char tag, char * info) {
  java_const * j_const = malloc(sizeof(java_const));
  j_const->tag =  tag;
  j_const->info = info;
  j_const->next = (java_const *)0;
  java_const * curr = class_object->const_pool;
  if (curr == 0) {
    class_object->const_pool = j_const;
  } else {
    while (curr->next != 0) {
      curr = curr->next;
    }
    curr->next = j_const;
  }
  puts("WOHOOOOOOO");
}

void initialize_java_class(java_class_s * class_object) {
  class_object->const_pool = 0;
}
