#include <stdio.h>

#include "arena.h"

int main(void)
{
    Arena* arena = arena_create(50);

    char* name = arena_alloc(arena, 4);

    name = "Dev";

    printf("Name: %s\n", name);

    return 0;
}
