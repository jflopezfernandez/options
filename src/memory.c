
#include "options.h"

void* allocate_memory(size_t size) {
    void* memory = malloc(size);

    if (memory == NULL) {
        fatal_error("Memory allocation failure in allocate_memory()");
    }

    return memory;
}
