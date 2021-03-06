#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "java_class.c"
#include "ui.c"


static java_attr read_java_attribute(void *java_class, int *class_index);

static int short_swap(short s) {
    unsigned char b1, b2;
    b1 = s & 255;
    b2 = (s >> 8) & 255;
    return ((short)b1 << 8) + b2;
}

static int long_swap(int i)  {
    unsigned char b1, b2, b3, b4;
    b1 = i & 255;
    b2 = (i >> 8) & 255;
    b3 = (i >> 16) & 255;
    b4 = (i >> 24) & 255;

    return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}

static short read_int(void *java_class, int *class_index, char* to_print) {
    int result = long_swap(
            *((int*) ((char*)java_class + (*class_index)))
            );
    printf(to_print,
            result
          );

    // Move forward two bytes.
    *class_index += 4;

    return result;
}

static short read_short(void *java_class, int *class_index, char* to_print) {
    short result = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf(to_print,
            result
          );

    // Move forward two bytes.
    *class_index += 2;

    return result;
}


static int file_size(FILE *in, size_t *size) {
    if (fseek(in, 0, SEEK_END) == 0) {
        long len = ftell(in);
        if (len > 0) {
            if (fseek(in, 0, SEEK_SET) == 0) {
                *size = (size_t) len;
                return 1;
            }
        }
    }
    return 0;
}

static void * load_binary_class(const char * filename, size_t *size) {
    FILE *in;
    void *data = NULL;
    size_t len;


    if ((in = fopen(filename, "rb")) != NULL) {
        if (file_size(in, &len)) {
            if ((data = malloc(len)) != NULL) {
                if (fread(data, 1, len, in) == len) {
                    *size = len;
                } else {
                    free(data);
                    data = NULL;
                }
            }
        }
        fclose(in);
    }
    return data;


}

/**
 * Print out the java magic number aka cafebabe
 */
static void print_java_magic_prefix(void * java_class, int * class_index, java_class_s * class_object) {
    int magic = long_swap(*(int*)java_class);
    printf("Java class file prefix: 0x%x\n", 
            magic
          );
    class_object->magic = magic;
    *class_index += 4;
}

/**
 * Minor version of the java class file. No idea what this is.
 */
static void print_java_minor_version(void * java_class, int *class_index, java_class_s * class_object) {
    short minor = short_swap(*((short *)java_class + 2));
    printf("Java Minor Version %hd\n",
            minor
          );
    class_object->minor = minor;
    *class_index += 2;
}

/**
 * Major version of the java class file. Defines the jkd version that 
 * was used to build it. 51 for javaSE7
 */
static void print_java_major_version(void * java_class, int *class_index, java_class_s * class_object) {
    short major = short_swap(*((short *)java_class + 3));
    printf("Java Major Version %hd\n",
            major
          );
    class_object->major = major;
    *class_index += 2;
}

/**
 * Get the size of the constant pool in java. Return it and print it out.
 */
static int print_and_get_const_pool_size(void * java_class, int *class_index, java_class_s * class_object) {
    short const_pool_size = short_swap(*((short *)java_class + 4));
    printf("Size of constant pool:%hd\n",
            const_pool_size
          );
    class_object->const_count = const_pool_size;
    *class_index += 2;
    return const_pool_size;
}

/**
 * Prints the utf8 constant type
 */
static char * print_java_constant_utf8(void *java_class, int *class_index) {
    short string_length = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    char * info = malloc(string_length * sizeof(string_length));
    bzero(info, string_length);
    printf("    String length: %hd\n", 
            string_length
          );
    char *string_constant = malloc(string_length + 1);
    int i = 0;
    for (i; i < string_length; i++) {
        string_constant[i] = *((char*)java_class + *class_index);
        info[i] = string_constant[i];
        (*class_index)++;
    }
    string_constant[string_length] = '\0';
    printf("    String constant: %s\n",
            string_constant
          );

    return info;
}

/**
 * Ref-type constant. From the JVM spec:
 * u1 tag;
 * u2 class_index;
 * ut name_and_type_index;
 */
static char * print_java_constant_ref(void *java_class, int *class_index) {
    short jvm_class_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("    Class index: %hd\n",
            jvm_class_index
          );
    *class_index += 2;
    short name_and_type_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("    Name and Type index: %hd\n",
            name_and_type_index
          );
    *class_index += 2;
    return 0;
}

/**
 * Prints the Class-type constant
 */
static char * print_java_constant_class(void *java_class, int *class_index) {
    short name_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("    Name index: %hd\n",
            name_index
          );
    *class_index += 2;
    return 0;
}

static char * print_java_constant_string(void *java_class, int *class_index) {
    short string_index = read_short(java_class, class_index, "    String index: %hd\n");
}

static char * print_java_constant_integer(void *java_class, int *class_index) {
     int int_constant = read_int(java_class, class_index, "    Integer Constant: %hd\n");
}

static char * print_java_constant_float(void *java_class, int *class_index) {
     int float_constant = read_int(java_class, class_index, "    Float Constant: %hd\n");
}

static char * print_java_constant_double(void *java_class, int *class_index) {
     int double_constant_1 = read_int(java_class, class_index, "    Double Constant1: %hd\n");
     int double_constant_2 = read_int(java_class, class_index, "    Double Constant2: %hd\n");
}

static char * print_java_constant_name_and_type(void *java_class, int *class_index) {
    short name_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("    Name index: %hd\n",
            name_index
          );
    *class_index += 2;
    short descriptor_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("    Descriptor index: %hd\n",
            descriptor_index
          );
    *class_index += 2;
    return 0;
}

static char * handle_tag(short tag, void *java_class, int *class_index) {
    switch (tag) {
        case 1:
            return print_java_constant_utf8(java_class, class_index);
            break;
        case 3:
            return print_java_constant_integer(java_class, class_index);
            break;
        case 4:
            return print_java_constant_float(java_class, class_index);
            break;
        case 5:
            perror("Unimplemented: read Long");
            exit(-1);
            break;
        case 6:
            return print_java_constant_double(java_class, class_index);
            break;
        case 7:
            return print_java_constant_class(java_class, class_index);
            break;
        case 8:
            return print_java_constant_string(java_class, class_index);
        case 9:
        case 10:
        case 11:
            return print_java_constant_ref(java_class, class_index);
            break;
        case 12:
            return print_java_constant_name_and_type(java_class, class_index);
        default:
            perror("didn't recognize that flag...!");
            exit(-1);
            break;
    }
}

static void print_java_constant(void * java_class, int * class_index, int *const_index, java_class_s * class_object) {
    // Constant's are "1-indexed" whatever that means.
    printf("Constant %d:\n",
            (*const_index) + 1
          );
    char tag_c = *((char*)java_class + *class_index);
    short tag = (short) tag_c;

    printf("    Constant Tag: %hd\n",
            tag
          );
    (*class_index)++;
    char * info = handle_tag(tag, java_class, class_index);
    add_constant(class_object, tag_c, info);

    // WTF? Lol... 
    if (tag == 6) {
        printf("increasing constant for double tab.\n");
        (*const_index)++;
    }
}

static void print_java_access_flags(void * java_class, int * class_index) {
    short access_flags = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Access Flags: %hd\n",
            access_flags
          );
    *class_index += 2;

}

static void print_java_this_class(void * java_class, int * class_index) {
    short this_class = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("This Class: %hd\n",
            this_class
          );
    *class_index += 2;

}

static void print_java_super_class(void * java_class, int * class_index) {
    short super_class = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Super Class: %hd\n",
            super_class
          );
    *class_index += 2;

}

static int print_and_get_java_interface_count(void *java_class, int *class_index) {
    short interface_count = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Interface count: %hd\n",
            interface_count
          );
    *class_index += 2;
    return interface_count;
}

static void print_java_interface(void *java_class, int *class_index, int interface_index) {
    short interface = read_short(java_class, class_index, "    Interface: %hd\n");
    return;
}

static int print_and_get_java_fields_count(void *java_class, int *class_index) {
    short fields_count = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Fields count: %hd\n",
            fields_count
          );
    *class_index += 2;
    return fields_count;
}

static void print_java_field(void *java_class, int *class_index, int fields_index) {
    short access_flags = read_short(java_class, class_index, "      AccessFlags: %hd\n");
    short name_index = read_short(java_class, class_index, "       NameIndex: %hd\n");
    short desc_index = read_short(java_class, class_index, "       DescriptorIndex: %hd\n");
    short attr_count = read_short(java_class, class_index, "       AttrCount: %hd\n");
    int i = 0;
    for (; i < attr_count; i++) {
        read_java_attribute(java_class, class_index);
    }
}

static int print_and_get_java_methods_count(void *java_class, int *class_index, java_class_s * class_object) {
    short methods_count = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Methods count: %hd\n",
            methods_count
          );
    *class_index += 2;
    class_object->methods_count = methods_count;
    return methods_count;
}


static int print_and_get_java_attributes_count(void *java_class, int *class_index) {
    short attributes_count = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    printf("Attributes count: %hd\n",
            attributes_count
          );
    *class_index += 2;
    return attributes_count;
}

static java_attr read_java_attribute(void *java_class, int *class_index) {
    java_attr result;
    short name_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    printf("            Name index: %d\n",
            name_index
          );

    result.name_index = name_index;

    int attribute_length = long_swap(
            *((int*) ((char*)java_class + (*class_index)))
            );
    *class_index += 4;
    printf("            Attribute length: %d\n",
            attribute_length
          );
    result.length = attribute_length;

    printf("            ");
    int i = 0;
    result.content = malloc(sizeof(char) * result.length);
    for (i; i < attribute_length; i++) {
        short s = (short) *((char*)java_class + (*class_index));
        (*class_index)++;
        printf("%d ",
                s
              );
        result.content[i] = s;
    }
    printf("\n");

    return result; 
}

static java_method read_java_method(void *java_class, int *class_index, int methods_index) {
    java_method result;
    printf("    Methods[%d]:\n",
            methods_index
          );
    short access_flags = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    printf("        Access flags: %d\n",
            access_flags
          );
    result.access_flags = access_flags;

    short name_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    printf("        Name index: %d\n",
            name_index
          );
    result.name_index = name_index;


    short descriptor_index = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    printf("        Descriptor index: %d\n",
            descriptor_index
          );
    result.descriptor_index = descriptor_index;

    short attributes_count = short_swap(
            *((short*) ((char*)java_class + (*class_index)))
            );
    *class_index += 2;
    printf("        Attributes count: %d\n",
            attributes_count
          );
    result.attributes_count = attributes_count;

    int attributes_index = 0;
    java_attr* attrs = malloc(sizeof(java_attr) * attributes_count);
    for (attributes_index; attributes_index < attributes_count; attributes_index++) {
        java_attr attr = read_java_attribute(java_class, class_index);
        attrs[attributes_index] = attr;
    }

    result.attrs = attrs;
    return result;
}

/**
 * Takes in a java class object, and a bunch of bytes representing a class,
 * and interprets the bytes, stores them in the class.
 */
static void interpret_java_class(void * java_class, size_t *size, java_class_s* class_object) {
    int class_index = 0;


    // Cafe babes are so fine.
    print_java_magic_prefix(java_class, &class_index, class_object);

    // Versions
    print_java_minor_version(java_class, &class_index, class_object);
    print_java_major_version(java_class, &class_index, class_object);

    const int const_pool_size = print_and_get_const_pool_size(java_class, &class_index, class_object);
    int const_index = 0;

    // const_pool_size - 1 due to JVM spec being strange..
    for (const_index; const_index < (const_pool_size - 1); const_index++) {
        print_java_constant(java_class, &class_index, &const_index, class_object);
    }

    print_java_access_flags(java_class, &class_index);
    print_java_this_class(java_class, &class_index);
    print_java_super_class(java_class, &class_index);

    const int interface_count = print_and_get_java_interface_count(java_class, &class_index);
    int interface_index = 0;

    for (interface_index; interface_index < interface_count; interface_index++) {
        print_java_interface(java_class, &class_index, interface_index);
    }

    const int fields_count = print_and_get_java_fields_count(java_class, &class_index);
    int fields_index = 0;

    for (fields_index; fields_index < fields_count; fields_index++) {
        print_java_field(java_class, &class_index, fields_index);
    }

    const int methods_count = print_and_get_java_methods_count(java_class, &class_index, class_object);
    int methods_index = 0;

    class_object->methods = malloc(sizeof(java_method) * methods_count);

    for (methods_index; methods_index < methods_count; methods_index++) {
        java_method m = read_java_method(java_class, &class_index, methods_index);
        class_object->methods[methods_index] = m;
    }

    const int attributes_count = print_and_get_java_attributes_count(java_class, &class_index);
    int attributes_index = 0;
    java_attr* attrs = malloc(sizeof(java_attr) * attributes_count);

    for (attributes_index; attributes_index < attributes_count; attributes_index++) {
        attrs[attributes_index] = read_java_attribute(java_class, &class_index);
    }
    class_object->attrs = attrs; 
}


int main(int argc, char **argv) {
    void * java_class;
    size_t size;
    java_class_s * class_object = malloc(sizeof(java_class_s));
    initialize_java_class(class_object);

    if ((java_class = load_binary_class(argv[1], &size)) != NULL) {
        printf("Loaded a java class woohoo!\n");
        printf("the class had size %u\n", (unsigned int) size);
        interpret_java_class(java_class, &size, class_object);
    } else {
        printf("Couldn't load file %s!!\n", argv[1]);
    }

    questions(class_object);

    return 0;
}
