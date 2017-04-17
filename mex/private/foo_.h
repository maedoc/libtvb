typedef struct foo foo;

foo *foo_new();

void foo_del(foo *f);

int foo_get_iters(foo *f);

void foo_set_iters(foo *f, int iters);

typedef int(*foo_iters_manip)(void*, int);

void foo_manip_iters(foo *f, foo_iters_manip cb, void *data);

typedef void(*foo_array_manip)(void*, int, double *x);

void foo_manip_array(foo *f, foo_array_manip cb, void *data);
