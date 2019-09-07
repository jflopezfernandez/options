
#include "options.h"

char* duplicate_string(const char* original_string) {
    size_t length = strlen(original_string);
    char* duplicate = allocate_memory(sizeof (char) * (length + 1));
    return strcpy(duplicate, original_string);
}

bool_t strings_match(const char* a, const char* b) {
    return (bool_t) strcmp(a,b) == 0;
}
