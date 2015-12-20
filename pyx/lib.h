typedef double(*cb)(void*, double);
double func(cb, void* data, double x);
typedef void(*cb2)(void*, int, double*);
void func2(cb2 c, void *data);
