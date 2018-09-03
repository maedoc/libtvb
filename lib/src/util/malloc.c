/* copyright 2016 Apache 2 libtvb authors */

#include <stdlib.h>

#include "libtvb.h"

static tvb_malloc_t _tvb_malloc = malloc;
static tvb_realloc_t _tvb_realloc = realloc;
static tvb_free_t _tvb_free = free;

/* Memory register */

/* Objects {{{ */
typedef struct mem_register mem_register;

struct mem_register {
	void *start;
	void *upto;
	struct mem_register *next;
};

/* Memory register indicator object */
static bool reg_active = false;

/* Required register starting and ending nodes */
static mem_register *mem_reg_base = NULL, *mem_reg_end = NULL;

/* Total registered bytes stored. */
static uint32_t total_reg_bytes = 0;

/*  }}} */

/*  fuctions {{{ */
static mem_register *reg_search(void *);
static void reg_push(void *, size_t);
static void reg_pop(void *ptr);

/* Initiates memory register */
void tvb_malloc_reg_init() {
	reg_active = true;
}

/* Stops memory register and free register memory */
void tvb_malloc_reg_stop() {
	if(mem_reg_base == NULL) {
		reg_active = false;
		return;
	}
	mem_register *temp = mem_reg_base;
	for(mem_reg_base = mem_reg_base->next; mem_reg_base != NULL; mem_reg_base = mem_reg_base->next) {
		(*_tvb_free)(temp);
		temp = mem_reg_base;
	}
	(*_tvb_free)(temp);
	mem_reg_base = NULL;
	mem_reg_end = NULL;
	total_reg_bytes = 0;
	reg_active = false;
}

/* Return total registered bytes stored. */
uint32_t tvb_malloc_total_nbytes() {
       return total_reg_bytes;
}

/* Search for an object in register 
   Returns the object before ptr if found
   Returns the object with ptr if found and is mem_register_base
   Else returns NULL
*/
static mem_register *reg_search(void *ptr) {
	mem_register *temp, *store;
	for(temp = mem_reg_base, store = mem_reg_base; temp != NULL; temp = temp->next) {
		if((temp->start <= ptr) && (temp->upto > ptr))
			return store;
		store = temp;
	}
	return NULL;
}

/* Checks if ptr exists in register */
enum tvb_stat tvb_malloc_reg_query(void *ptr){
	if(reg_active)
		return reg_search(ptr) != NULL ? TVB_OK : TVB_ERR;
	else
		return TVB_UNKNOWN;
}

/* Adds a record of a new chunk of memory to register */
static void reg_push(void *new_ptr, size_t size) {
	if(new_ptr == NULL)
		return;
	mem_register *n;
	n = (mem_register *)(*_tvb_malloc)(sizeof(mem_register));
	if(n == NULL) {
		tvb_err( "malloc returned a NULL pointer while mem_register allocation" );
		return;
	}
	n->start = new_ptr;
	/* pointer arith on void* is undefined behavior because void is not a
	 * type with a specific size. However, we know size is the number of
	 * bytes, so we just need to cast new_ptr to a type with size of one byte
	 * e.g. a char
	 */
	n->upto = (void*) (((char*) new_ptr) + size);
	n->next = NULL;
	if(mem_reg_base == NULL) {
		mem_reg_base = n;
		mem_reg_end = n;
	} else {
		mem_reg_end->next = n;
		mem_reg_end = n;
	}
	total_reg_bytes += (uint32_t)size;
}

/* Deletes record of a chunk of memory from register */
static void reg_pop(void *ptr) {
	if(ptr == NULL)
		return;
	mem_register *temp = reg_search(ptr);
	if(temp == NULL) {
		/* Unable to find, not allocated by us OR allocated before
		 * reg was active. 
		 */
		return;
	}
	if(temp == mem_reg_base && temp->start == ptr) {
		mem_reg_base = mem_reg_base->next;
		if(temp == mem_reg_end)
			/* In this case register has only one element. */
			mem_reg_end = NULL;
	} else {
		mem_register *temp2 = temp;
		temp = temp->next;
		temp2->next = temp->next;
		if(temp == mem_reg_end)
			mem_reg_end = temp2;
	}
	total_reg_bytes -= (uint32_t)( (char*)(temp->upto) - (char*)(temp->start) );
	(*_tvb_free)(temp);
}

void tvb_malloc_set_allocators(tvb_malloc_t malloc, tvb_realloc_t realloc, tvb_free_t free) {
	if (malloc == NULL || realloc == NULL || free == NULL) {
		tvb_err( "tvb_malloc_set_allocators passed a NULL allocator." );
		return;
	}
	_tvb_malloc = malloc;
	_tvb_realloc = realloc;
	_tvb_free = free;
}

void tvb_malloc_set_stdlib_allocators() {
	tvb_malloc_set_allocators(&malloc, &realloc, &free);
}

void *tvb_malloc(size_t size) {
	void *new_ptr;
	new_ptr = (*_tvb_malloc)(size);
	if (new_ptr==NULL)
		tvb_err( "alloc returned a NULL pointer." );
	if (reg_active)
		reg_push(new_ptr, size);
	return new_ptr;
}

void *tvb_realloc(void *ptr, size_t size) {
	void *new_ptr;
	new_ptr = (*_tvb_realloc)(ptr, size);
	if (new_ptr==NULL)
		tvb_err( "realloc returned a NULL pointer." );
	if (reg_active) {
		reg_pop(ptr);
		reg_push(new_ptr, size);
	}
	return new_ptr;
}

void tvb_free(void *ptr) {
	if (ptr==NULL) {
		tvb_log_debug( "cowardly refusing to free a NULL pointer." );
		return;
	}
	if (reg_active)
		reg_pop(ptr);
	(*_tvb_free)(ptr);
}
