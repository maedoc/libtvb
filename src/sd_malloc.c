/* copyright 2016 Apache 2 sddekit authors */

#ifdef SDDEBUG
#include <stdio.h>
#endif

#include "sddekit.h"

static sd_malloc_t _sd_malloc = malloc;
static sd_realloc_t _sd_realloc = realloc;
static sd_free_t _sd_free = free;

void sd_malloc_set_allocators(sd_malloc_t malloc, sd_realloc_t realloc, sd_free_t free) {
	if (malloc == NULL || realloc == NULL || free == NULL) {
		sd_err( "sd_malloc_set_allocators passed a NULL allocator." );
		return;
	}
	_sd_malloc = malloc;
	_sd_realloc = realloc;
	_sd_free = free;
}

void sd_malloc_set_stdlib_allocators() {
	sd_malloc_set_allocators(&malloc, &realloc, &free);
}

void *sd_malloc(size_t size) {
	void *new_ptr;
	new_ptr = (*_sd_malloc)(size);
	if (new_ptr==NULL)
		sd_err( "[sd_alloc] alloc returned a NULL pointer." );
	return new_ptr;
}

void *sd_realloc(void *ptr, size_t size) {
	void *new_ptr;
	new_ptr = (*_sd_realloc)(ptr, size);
	if (new_ptr==NULL)
		sd_err( "[sd_realloc] realloc returned a NULL pointer." );
	return new_ptr;
}

void sd_free(void *ptr) {
#ifdef SDDEBUGFREE
	static int n = 0;
#endif
	if (ptr==NULL) {
		sd_log_debug( "[sd_free] cowardly refusing to free a NULL pointer." );
		return;
	}
#ifdef SDDEBUGFREE
	sd_log_debug("%d'th call to sd_free on %p.", n, ptr);
	n++;
#endif
	(*_sd_free)(ptr);
}
