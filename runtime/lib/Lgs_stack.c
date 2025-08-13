#include <stdlib.h>
#include <string.h>

#define LGS_MAX_FRAMES 64
#define LGS_MAX_LOCALS 16

typedef struct {
    char* locals[LGS_MAX_LOCALS];
    int local_count;
} Lgs_Stack_Frame;

typedef struct {
    Lgs_Stack_Frame frames[LGS_MAX_FRAMES];
    int top;
} Lgs_Stack;

void Lgs_Stack_push(Lgs_Stack* stack) {
    stack->top++;
    Lgs_Stack_Frame* frame = &stack->frames[stack->top];
    frame->local_count = 0;
}

void Lgs_Stack_pop(Lgs_Stack* stack) {
    stack->top--;
}

void Lgs_Stack_addLocal(Lgs_Stack_Frame* frame, const char* name) {
    frame->locals[frame->local_count++] = strdup(name);
}

char* Lgs_Stack_getLocal(const Lgs_Stack_Frame* frame, const int index) {
    return frame->locals[index];
}

void Lgs_Stack_free(const Lgs_Stack* stack) {
    for (int f = 0; f <= stack->top; f++) {
        for (int i = 0; i < stack->frames[f].local_count; i++) {
            free(stack->frames[f].locals[i]);
        }
    }
}
