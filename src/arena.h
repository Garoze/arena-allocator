#ifndef _ARENA_H
#define _ARENA_H

#include <stddef.h>
#include <stdint.h>

struct _arena_alloc
{
    uint8_t* buffer;
    size_t buffer_len;
    size_t curr_offset;
    size_t prev_offset;
};
typedef struct _arena_alloc Arena;

#ifndef DEFAULT_ALIGNMENT
    #define DEFAULT_ALIGNMENT (2 * sizeof(void*))
#endif

/**
 * @internal - Check if the alignment is a power of `2`
 *
 * align {size_t} - The alignment
 *
 * returns {bool} - `true` if the align is a power of 2 `false` otherwise
 *
 */
#define __is_power_of_two(align) (((align) & ((align)-1)) == 0)

/**
 * @internal -  Return the current pointer
 *
 * a {Arena*} - The Arena itself
 *
 * returns {uintptr_t} - The offset of the current_ptr
 *
 */
#define __arena_current_ptr(a)                                                 \
    ((uintptr_t)(a)->buffer + (uintptr_t)(a)->curr_offset)

/**
 * @nternal - Align a ptr by the aligment amount
 *
 * ptr {uintptr_t} - The pointer to align
 * align {size_t} - The alignment amount
 *
 * returns {uintptr_t} - The ptr already aligned
 *
 */
uintptr_t __align_forward(uintptr_t ptr, size_t align);

/**
 * @internal - Alloc `x` amount of memory respecting the aligment
 *
 * arena {Arena*} - Arena ptr itself
 * size {size_t} - The amount to be allocate
 * arena {Arena*} - Arena ptr itself
 *
 * returns {size_t} - The length of the buffer itself
 *
 */
void* __arena_alloc_align(Arena* arena, size_t size, size_t align);

/**
 * @public - Alloc `x` amount of memory and return the ptr
 * size {size_t} - The amount to be allocate
 */
void* arena_alloc(Arena* arena, size_t size);

/**
 * @public - Free a Arena
 */
void arena_free_all(Arena* arena);

/**
 * @public - Create a Arena and return a Arena ptr
 * size {size_t} - The amount to be allocate
 */
Arena* arena_create(size_t size);

#endif // _ARENA_H
