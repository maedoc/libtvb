/* copyright 2016 Apache 2 sddekit authors */

#define sd_declare_common_members(tag) \
	void *data; \
	struct tag* (*copy)(struct tag *obj); \
	uint32_t (*n_byte)(struct tag *obj); \
	void (*free)(struct tag *obj)

/* For every interface an object implements,
 * it likely needs to have a single implementation of the actual object
 * methods (free, n_byte, copy) and then forward calls in the different
 * interfaces to these methods.
 *
 * Note that these assume that you've define a struct data & your
 * methods are data_{free,n_byte,copy}.
 */

#define sd_declare_tag_free(tag) \
static void tag ## _free(struct tag *tag) { data_free(tag->data); }

#define sd_declare_tag_n_byte(tag) \
static uint32_t tag ## _n_byte(struct tag *tag) { return data_n_byte(tag->data); }

#define sd_declare_tag_copy(tag) \
static struct tag *tag ## _ ## copy(struct tag *tag) \
{ \
	struct data *data = data_copy(tag->data); \
	return &data->tag; \
}

#define sd_declare_tag_functions(tag) \
sd_declare_tag_free(tag) \
sd_declare_tag_n_byte(tag) \
sd_declare_tag_copy(tag)

#define sd_declare_tag_vtable(tag) \
	.free = &tag ## _free, \
	.n_byte = &tag ## _n_byte, \
	.copy = &tag ## _copy
