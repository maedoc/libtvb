We have a few opinions on how to write C, starting with the C99 standard.

- use interfaces (`struct`s of function pointers) + constructors as much as possible in API
- common code or data? _composition over inheritance_ make a private header with struct / functions, or an interface if useful
- stick to `double`, `uint32_t` & `bool` or custom types in API 

## reading
1. [link resources as binary blob](http://smackerelofopinion.blogspot.fr/2015/12/incorporating-and-accesses-binary-data.html?m=1)
2. consider https://matt.sh/howto-c
3. consider https://hintjens.gitbooks.io/scalable-c/content/chapter2.html
4. consider http://crafn.kapsi.fi/new_engine.html
5. https://news.ycombinator.com/item?id=10908042
6. http://chickenwing.software/scratches/programming/annoying-apis
7. [questionable tricks](http://stackoverflow.com/questions/599365/what-is-your-favorite-c-programming-trick?rq=1)
8. [on `typedef`ing `struct`s](http://yarchive.net/comp/linux/typedefs.html)
9. [Write code that is easy to delete](http://programmingisterrible.com/post/139222674273/write-code-that-is-easy-to-delete-not-easy-to)
10. [Compound Literals](http://www.drdobbs.com/the-new-c-compound-literals/184401404)
11. [advice on autovectorization](http://locklessinc.com/articles/vectorize/)
12. [advice on mem opts (PDF)](http://www.research.scea.com/research/pdfs/GDC2003_Memory_Optimization_18Mar03.pdf)
13. [comments on strict aliasing and optimization](http://blog.regehr.org/archives/1307)
14. [type puns & optimization](http://blog.regehr.org/archives/959)

From 9, 

> Boilerplate works best when libraries are expected to cater to all tastes, but sometimes there is just too much duplication. It’s time to wrap your flexible library with one that has opinions on policy, workflow, and state. Building simple-to-use APIs is about turning your boilerplate into a library.

is a good point, and sddekit should provide two levels of apis. The current work provides the highly verbose API and later on a second opinionated API can be placed on top.

10 has a few interesting tidbits, such as 
```c
struct POINT { int x, y; };
struct POINT *p;
p = &(struct POINT) {1, 1};
p->x = 2;
p->y = 2;
printf("*p = %d, %d\n", p->x, p->y);
```
in other words, compound literals are lvalues with addresses.

## typedefing

I was fairly convinced by the points [made by Linus](http://yarchive.net/comp/linux/typedefs.html) that `typedef`ing generally hurts readability, so I'd prefer not using it.

## Aliasing and mutation

Rust makes a good case, but fundamentally they are baking a few best practices into their compiler: avoid simultaneous aliasing and mutation. In C99, excluding these can be obtained via the `restrict` and `const` keywords respectively, but I found tightening it all down was just too verbose

```c
struct foo {
    const double * const restrict
        (* const get_values)(const struct foo * const restrict self);
};
```

The first and second `const` keeps you from changing elements pointed at by `values` or the memory address in `values` respectively. It also promises that no other pointer accesses the same memory as that accessed by `values`. Great guarantees, but heavy to write out.

One option would be `typedef` again
```c
typedef const double * const restrict doubles;

bool all_equal(uint32_t n, doubles x, doubles y);
```
but this hides the pointer etc etc.

## tools

- [qira](http://qira.me/) time traveling (well, stateless) debugger for linux
- address and undefined behavior sanitizers for GCC/Clang
- feedback directed optimization