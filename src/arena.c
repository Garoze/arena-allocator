#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"

uintptr_t __align_forward(uintptr_t ptr, size_t align)
{
    assert(__is_power_of_two(align));

    uintptr_t p = ptr;
    uintptr_t a = (uintptr_t)align;
    uintptr_t modulo = p & (a - 1);

    if (modulo != 0)
    {
        p += a - modulo;
    }

    return p;
}

void* __arena_alloc_align(Arena* arena, size_t size, size_t align)
{
    uintptr_t current_ptr = __arena_current_ptr(arena);

    uintptr_t offset = __align_forward(current_ptr, align);

    offset -= (uintptr_t)arena->buffer;

    if ((offset + size) <= arena->buffer_len)
    {
        void* ptr = &arena->buffer[offset];

        arena->prev_offset = offset;
        arena->curr_offset = offset + size;

        memset(ptr, 0, size);

        return ptr;
    }

    return NULL;
}

void* arena_alloc(Arena* arena, size_t size)
{
    return __arena_alloc_align(arena, size, DEFAULT_ALIGNMENT);
}

Arena* arena_create(size_t size)
{
    Arena* temp = calloc(1, sizeof(Arena));
    temp->buffer = malloc(size);
    temp->buffer_len = size;
    temp->curr_offset = 0;
    temp->prev_offset = 0;

    return temp;
}

void arena_free_all(Arena* arena)
{
    arena->curr_offset = 0;
    arena->prev_offset = 0;
}
