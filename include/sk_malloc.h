/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_MALLOC_H
#define SK_MALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void*(*sk_malloc_t)(size_t size);
typedef void*(*sk_realloc_t)(void *ptr, size_t size);
typedef void(*sk_free_t)(void *ptr);

/**
 * Set custom allocators to be used whenever sk_ calls require allocating or freeing 
 * memory.
 */
void sk_malloc_set_allocators(sk_malloc_t malloc, sk_realloc_t realloc, sk_free_t free);

/**
 * Set allocators to stdlib functions (malloc, realloc, free)
 */
void sk_malloc_set_stdlib_allocators();

/**
 * Allocate memory using current allocator.
 */
void *sk_malloc(size_t size);

/**
 * Allocate memory using current allocator.
 */
void *sk_realloc(void *ptr, size_t size);

/**
 * Free memory using current allocator.
 */
void sk_free(void *ptr);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
