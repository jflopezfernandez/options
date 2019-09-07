
#include "options.h"

void fatal_error(const char* error_message) {
    fprintf(stderr, "[Error] %s\n", error_message);
    exit(EXIT_FAILURE);
}
