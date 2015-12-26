/* Apache 2.0 INS-AMU 2015 */

#ifdef SKDEBUG
#include <stdio.h>
#endif

#include <stdlib.h>

#include "sk_malloc.h"
#include "sk_log.h"
#include "sk_err.h"

static sk_malloc_t _sk_malloc = malloc;
static sk_realloc_t _sk_realloc = realloc;
static sk_free_t _sk_free = free;

void sk_malloc_set_allocators(sk_malloc_t malloc, sk_realloc_t realloc, sk_free_t free) {
	if (malloc == NULL || realloc == NULL || free == NULL) {
		sk_err( "sk_malloc_set_allocators passed a NULL allocator." );
		return;
	}
	_sk_malloc = malloc;
	_sk_realloc = realloc;
	_sk_free = free;
}

void sk_malloc_set_stdlib_allocators() {
	sk_malloc_set_allocators(&malloc, &realloc, &free);
}

void *sk_malloc(size_t size) {
	void *new_ptr;
	new_ptr = (*_sk_malloc)(size);
	if (new_ptr==NULL)
		sk_err( "[sk_alloc] alloc returned a NULL pointer.\n" );
	return new_ptr;
}

void *sk_realloc(void *ptr, size_t size) {
	void *new_ptr;
	new_ptr = (*_sk_realloc)(ptr, size);
	if (new_ptr==NULL)
		sk_err( "[sk_realloc] realloc returned a NULL pointer.\n" );
	return new_ptr;
}

void sk_free(void *ptr) {
#ifdef SKDEBUGFREE
	static int n = 0;
#endif
	if (ptr==NULL) {
		sk_log_debug( "[sk_free] cowardly refusing to free a NULL pointer.\n" );
		return;
	}
#ifdef SKDEBUGFREE
	sk_log_debug("%d'th call to sk_free on %p.", n, ptr);
	n++;
#endif
	(*_sk_free)(ptr);
}
