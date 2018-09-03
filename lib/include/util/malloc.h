/* copyright 2016 Apache 2 libtvb authors */


#include "../libtvb.h"

typedef void*(*tvb_malloc_t)(size_t size);
typedef void*(*tvb_realloc_t)(void *ptr, size_t size);
typedef void(*tvb_free_t)(void *ptr);

/**
 * Set custom allocators to be used whenever tvb_ calls require allocating or freeing 
 * memory.
 */
TVB_API void
tvb_malloc_set_allocators(tvb_malloc_t malloc, tvb_realloc_t realloc, tvb_free_t free);

/**
 * Set allocators to stdlib functions (malloc, realloc, free)
 */
TVB_API void
tvb_malloc_set_stdlib_allocators();

/**
 * Allocate memory using current allocator.
 */
TVB_API void *
tvb_malloc(size_t size);

/**
 * Allocate memory using current allocator.
 */
TVB_API void *
tvb_realloc(void *ptr, size_t size);

/**
 * Initialize & finalize register of memory allocated by tvb_malloc
 */
TVB_API void
tvb_malloc_reg_init();

TVB_API void
tvb_malloc_reg_stop();

/**
 * return TVB_OK if valid pointer, TVB_ERR if invalid, TVB_UNKNOWN if we don't know
 * (because register inactive for example) 
 */
TVB_API enum tvb_stat
tvb_malloc_reg_query(void *);

/*! Return total number of bytes allocated in library data structures. */
uint32_t tvb_malloc_total_nbytes();

/**
 * Free memory using current allocator.
 */
TVB_API void
tvb_free(void *ptr);
