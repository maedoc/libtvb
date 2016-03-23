/* copyright 2016 Apache 2 sddekit authors */


#include "../sddekit.h"

typedef void*(*sd_malloc_t)(size_t size);
typedef void*(*sd_realloc_t)(void *ptr, size_t size);
typedef void(*sd_free_t)(void *ptr);

/**
 * Set custom allocators to be used whenever sd_ calls require allocating or freeing 
 * memory.
 */
SD_API void
sd_malloc_set_allocators(sd_malloc_t malloc, sd_realloc_t realloc, sd_free_t free);

/**
 * Set allocators to stdlib functions (malloc, realloc, free)
 */
SD_API void
sd_malloc_set_stdlib_allocators();

/**
 * Allocate memory using current allocator.
 */
SD_API void *
sd_malloc(size_t size);

/**
 * Allocate memory using current allocator.
 */
SD_API void *
sd_realloc(void *ptr, size_t size);

/**
 * Initialize & finalize register of memory allocated by sd_malloc
 */
SD_API void
sd_malloc_reg_init();

SD_API void
sd_malloc_reg_stop();

/**
 * return SD_OK if valid pointer, SD_ERR if invalid, SD_UNKNOWN if we don't know
 * (because register inactive for example) 
 */
SD_API enum sd_stat
sd_malloc_reg_query(void *);

/*! Return total number of bytes allocated in library data structures. */
uint32_t sd_malloc_total_nbytes();

/**
 * Free memory using current allocator.
 */
SD_API void
sd_free(void *ptr);
