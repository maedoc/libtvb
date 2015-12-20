/* Apache 2.0 INS-AMU 2015 */

#ifdef SKDEBUG
#include <stdio.h>
#endif

#include "sk_malloc.h"

static sk_malloc_t _sk_malloc = malloc;
static sk_realloc_t _sk_realloc = realloc;
static sk_free_t _sk_free = free;

void sk_malloc_set_allocators(sk_malloc_t malloc, sk_realloc_t realloc, sk_free_t free) {
	if (malloc == NULL || realloc == NULL || free == NULL) {
#ifdef SKDEBUG
		fprintf(stderr, "[sk_malloc_set_allocators] at least one fn ptr == NULL\n");
#endif
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
#ifdef SKDEBUG
	if (new_ptr==NULL)
		fprintf(stderr, "[sk_alloc] alloc returned a NULL pointer.\n");
#endif
	return new_ptr;
}

void *sk_realloc(void *ptr, size_t size) {
	void *new_ptr;
	new_ptr = (*_sk_realloc)(ptr, size);
#ifdef SKDEBUG
	if (new_ptr==NULL)
		fprintf(stderr, "[sk_realloc] realloc returned a NULL pointer.\n");
#endif
	return new_ptr;
}

void sk_free(void *ptr) {
#ifdef SKDEBUG
	if (ptr==NULL) {
		fprintf(stderr, "[sk_free] cowardly refusing to free a NULL pointer.\n");
		return;
	}
#endif
	(*_sk_free)(ptr);
}
