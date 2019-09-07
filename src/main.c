
#include "options.h"

typedef enum {
    OPTION_ATTRIBUTE_NONE     = 0x00,
    OPTION_ATTRIBUTE_ARGUMENT = 0x01,
    OPTION_ATTRIBUTE_REQUIRED = 0x02
} option_attributes_t;

typedef enum {
    OPTION_NONE,
    OPTION_HELP,
    OPTION_VERSION,
    OPTION_VERBOSE
} option_id_t;

struct option_t {
    option_id_t id;
    option_attributes_t attributes;
    const char* short_string;
    const char* long_string;
    const char* description;
};

#ifndef NONE
#define NONE ""
#else
#error "'NONE' preprocessor macro has already been defined."
#endif

static const struct option_t options[] = {
    { OPTION_HELP, OPTION_ATTRIBUTE_NONE   , "-h", "--help"   , "Display help menu and exit"                     },
    { OPTION_VERSION, OPTION_ATTRIBUTE_NONE, NONE, "--version", "Display program version info and exit"          },
    { OPTION_VERBOSE, OPTION_ATTRIBUTE_NONE, "-v", "--verbose", "Display detailed info during program execution" }
};

#if defined(NONE)
#undef NONE
#endif

static const size_t number_of_options = sizeof (options) / sizeof (options[0]);

option_id_t is_valid_option(const char* str) {
    /** The current implementation iterates through the entire options table and
     *  compares the input string against both the short and long option
     *  strings. In reality this should be a hash table, so make a note to
     *  re-implement this later.
     * 
     *  TODO: Re-write is_valid_option as a hash table.
     * 
     */
    for (size_t i = 0; i < number_of_options; ++i) {
        if (strings_match(str,options[i].short_string) || strings_match(str,options[i].long_string)) {
            return options[i].id;
        }
    }

    return OPTION_NONE;
}

struct settings_t {
    bool_t verbose;
};

static struct settings_t settings;

static void enable_verbose_output(void) {
    settings.verbose = TRUE;
}

struct element_t {
    void* data;
    struct element_t* next;
};

static inline struct element_t* allocate_element(void) {
    struct element_t* element = allocate_memory(sizeof (struct element_t));

    element->next = NULL;

    return element;
}

struct element_t* new_element(void* data) {
    struct element_t* element = allocate_element();

    element->data = data;

    return element;
}

struct queue_t {
    struct element_t* head;
};

static void enqueue(struct queue_t* queue, struct element_t* element) {
    if (queue->head == NULL) {
        queue->head = element;
        return;
    }

    struct element_t* queue_iterator = queue->head;

    while (queue_iterator->next) {
        queue_iterator = queue_iterator->next;
    }

    queue_iterator->next = element;
}

const char **parse_command_line(int argc, char **argv) {
    /** If the user does not supply any command-line arguments, handle that
     *  right away. The alternative would be to initialize the entire options-
     *  parsing apparatus, which will always be complete overkill.
     * 
     *  TODO: Print program usage.
     * 
     */
    if (argc == 1) {
        fatal_error("No input(s).");
    }

    for (int i = 1; i < argc; ++i) {
        option_id_t option_id = is_valid_option(argv[i]);

        if (option_id == OPTION_NONE) {
            // TODO: Add option to arguments vector
            printf("%s\n", argv[i]);
            continue;
        }

        switch (option_id) {
            case OPTION_HELP: {
                // TODO: Handle help option
                printf("%s\n", "[help menu]");
                exit(EXIT_SUCCESS);
            } break;

            case OPTION_VERSION: {
                // TODO: Handle version option
                printf("%s\n", "[version info]");
                exit(EXIT_SUCCESS);
            } break;

            case OPTION_VERBOSE: {
                // TODO: Handle verbose option
                // printf("Verbose option enabled\n");
                // settings.verbose = TRUE;
                enable_verbose_output();
            } break;

            default: {
                fatal_error("Invalid option string");
            } break;
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    const char **arguments = parse_command_line(argc, argv);

    if (settings.verbose) {
        printf("[%s] %s\n", basename(argv[0]), "Verbose mode enabled");
    }

    if (arguments == NULL) {
        fatal_error("The arguments vector is empty");
    }

    return EXIT_SUCCESS;
}
