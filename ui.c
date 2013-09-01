#define MAX_BUF 1000
#include "java_class.c"

/**
 * UI after the class has loaded.
 */

void questions(java_class_s* class_object) {

    // What do you want to know?

    printf("Which methods do you want to inspect?\n");

    // Note, code taken from stack overflow answer to Q 7831755
    while (1) {
        int c = getchar();
        if (c == EOF) break;
        if (!isspace(c)) {
            ungetc(c, stdin);
            break;
        }
    }

    int i = 0;
    char * input = (char *) malloc(MAX_BUF);
    while (i < MAX_BUF) {
        int c = getchar();
        input[i] = c;
        if (isspace(c) || c == EOF) {
            break;
        }

        i++;
    }


    printf("you typed %s!\n", input);
    int method_index = atoi(input);
    for (i = 0; i < method_index; i++) {
        printf("woo!\n");
    }

    inspect_method(class_object, method_index);

    free(input);
    return;

}

