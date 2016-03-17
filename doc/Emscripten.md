# Javascript

Because SDDEKit is a C library, it's straighforward to build it as a JavaScript
library and embed it in HTML with Emscripten. With the benchmark mentioned above
as an example, compile it natively,

```bash
$ make BUILD=fast -B -j bench_net_exc
...
$ ./bench_net_exc
[bench_net_exc] nnz=1560
[INFO] bench/bench_net_exc.c:71 (main) continuation required 23.766 s
```

A little slow on this 2009 Core 2 Duo laptop. Now, with 
the [Emscripten SDK installed](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html),
build an HTML page that runs the benchmark in your browser:

```bash
$ make CC=emcc BUILD=js OBJEXT=bc EXE=.html -B -j bench_net_exc.html
...
```

Open [`bench_net_exc.html`](http://rawgit.com/maedoc/sddekit/js-bench-html/bench_net_exc.html)
 with your browser. On this same machine, Safari
runs the benchmark in 74 s, Firefox 55 s. On a win 10 workstation,
GCC-compiled takes 12 s, Firefox takes 32 s & MS Edge 39 s.

Obviously for high-performance computing & science JS isn't ideal, but it could
be useful for creating interactive graphics exploring dynamical systems.
