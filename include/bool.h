
#ifndef PROJECT_INCLUDES_BOOL_H
#define PROJECT_INCLUDES_BOOL_H

typedef enum {
    FALSE = 0,
    TRUE  = 1
} bool_t;

const char* bool_string(bool_t value);

#endif // PROJECT_INCLUDES_BOOL_H
