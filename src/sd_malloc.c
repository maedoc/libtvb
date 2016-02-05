/* copyright 2016 Apache 2 sddekit authors */

#ifdef SDDEBUG
#include <stdio.h>
#endif

#include "sddekit.h"

static sd_malloc_t _sd_malloc = malloc;
static sd_realloc_t _sd_realloc = realloc;
static sd_free_t _sd_free = free;

//memory register
mem_register *mem_reg_base = NULL, *mem_reg_end = NULL;

void *sd_malloc_reg_search(void *);
void sd_malloc_reg_push(void *);
void sd_malloc_reg_pop(void *ptr);

void *sd_malloc_reg_search(void *ptr) {
	mem_register *temp, *store;
	for(temp = mem_reg_base, store = mem_reg_base; temp != NULL; temp = temp->next) {
		if(temp->ptr == ptr)
			return store;
		store = temp;
	}
	return NULL;
}

sd_stat sd_malloc_reg_query(void *ptr){
	mem_register *temp = sd_malloc_reg_search(ptr);
	if(temp == NULL)
		return SD_ERR;
	else 
		return SD_OK;
	//TODO SD_UNKNOWN
}

void sd_malloc_reg_push(void *new_ptr) {
	if(new_ptr == NULL)
		return;
	mem_register *n;
	//Allocating this with malloc. We don't want a sd_malloc loop!! ;)
	n = (mem_register *)malloc(sizeof(mem_register));
	if(n == NULL) {
		sd_err( "malloc returned a NULL pointer while mem_register allocation" );
		return;
	}
	n->ptr = new_ptr;
	n->next = NULL;
	if(mem_reg_base == NULL) {
		mem_reg_base = n;
		mem_reg_end = n;
	} else {
		mem_reg_end->next = n;
		mem_reg_end = n;
	}
}

void sd_malloc_reg_pop(void *ptr) {
	if(ptr == NULL)
		return;
	mem_register *temp = sd_malloc_reg_search(ptr);
	if(temp == NULL) {
		sd_err("Unable to find. Not allocated by sd_malloc.");
		return;
	}
	if(temp == mem_reg_base && temp->ptr == ptr) {
		mem_reg_base = mem_reg_base->next;
		if(temp == mem_reg_end)
			mem_reg_end = NULL; //In this case register has only one element.
	} else {
		mem_register *temp2 = temp;
		temp = temp->next;
		temp2->next = temp->next;
		if(temp == mem_reg_end)
			mem_reg_end = temp2;
	}
	free(temp);
}

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
	sd_malloc_reg_push(new_ptr);
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
	sd_malloc_reg_pop(ptr);
	(*_sd_free)(ptr);
}
