#ifndef KOKO_JAVA_CLASS_C
#define KOKO_JAVA_CLASS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.c"

/**
 * Holds the info for a java class
 */

struct java_attr;

typedef struct java_const {
    int index;
    char tag;
    char * info;
    struct java_const * next;
} java_const, *java_const_p;

typedef struct java_field {
    int x;
} java_field, *java_field_p;

/**
 * Definition of a method. Access permission (private/protected/public)
 * For more details see http://docs.oracle.com/javase/specs/jvms/se5.0/html/ClassFile.doc.html#1513
 */
typedef struct java_method {
    short access_flags;
    short name_index;
    short descriptor_index;
    short attributes_count;
    struct java_attr * attrs;
} java_method, *java_method_p;

/**
 * Java attribute. Basically a holder for a list of bytes with a name.
 */
typedef struct java_attr {
    short name_index;
    short length;
    char* content;
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

void print_attr(java_attr attr) {
    printf("attr[name] = %d\n", attr.name_index);
    printf("attr[len] = %d\n", attr.length);
    int i = 0;
    for (; i < attr.length; i++) {
        printf("attr[info][%d] = %d (%s)\n", i, attr.content[i], char_to_opcode(attr.content[i]));
    }
}

void inspect_method_attribute(java_method m, short attribute_index) {
    if (attribute_index < 0 || attribute_index > m.attributes_count) {
        perror("No such attribute...\n");
        return;
    }
    java_attr attr = m.attrs[attribute_index];
    print_attr(attr); 
}

void inspect_attribute(java_class_s * class_object, int attribute_index) {
    if  (attribute_index < 0 || attribute_index > class_object->attr_count) {
        perror("No such attribute...\n");
        return;
    }

    java_attr attr = class_object->attrs[attribute_index];
    print_attr(attr);

}

void inspect_method(java_class_s * class_object, int method_index) {
    if (method_index < 0 || method_index >= class_object->methods_count) {
        perror("No such method...\n");
        return;
    }

    java_method method = class_object->methods[method_index];
    printf("java_method[access_flags] = %d\n", method.access_flags);
    printf("java_method[name_index] = %d\n", method.name_index);
    printf("java_method[descriptor_index] = %d\n", method.descriptor_index);
    printf("java_method[attributes_count] = %d\n", method.attributes_count);

    int i = 0;
    for (; i < method.attributes_count; i++) {
        inspect_method_attribute(method, i);
    }

}

#endif
