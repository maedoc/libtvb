_originally in reply to a polite email asking about high-level overview of libtvb_

I'll describe the main ideas of the library, but if you want to get
started *today* consider reading the 
main header file [`src/libtvb.h`](https://github.com/maedoc/libtvb/blob/master/src/libtvb.h),
or it's [doxygen-generated form](http://maedoc.github.io/libtvb/libtvb_8h.html).

The code is younger than other opensource projects, so I appreciate
your patience while the documentation is written. Still, in my group we have been working
on these algorithms for several years now, and libtvb is inspired by several
of the simulation problems solved by the [Virtual Brain](http://thevirtualbrain.org),
a 5 year old project.

## Main idea

The main 'idea' of libtvb is to support computational modeling with
[stochastic delay differential equations](SDDE) (and simpler cases of SDE, DDE
or ODEs) by providing a modular library that a user can combine to
simulate their model. Practically, this means we decompose the
mathematics into several components.

- The *system* (`tvb_sys`) computes the right-hand-sides of the differential
  equations (and their stochastic terms if relevant).
- The *history buffer* (`tvb_hist`) tracks the values of state variables at previous
  points in time.
- The *integration scheme* (`tvb_sch`) discretizes the continuous-time
  differential equation, computing next state based on current state
- The *output monitor* (`tvb_out`) tracks specific variables of interest
  or some computation on them like temporal averaging, or storing to a
  file, or whatever user needs.
- The *solver* (`tvb_sol`) combines the above elements and performs the
  main loop of stepping through time until one of the output monitors
  tells it to stop.

These are the main elements, though there are some other supporting data
structures such as the network system (`tvb_net`) which implements the
`tvb_sys` interface but helps implement network systems (where each node
has the same equations) such as neural networks.

## diversion on C coding style

When I said 'modular' before, I mean that the main data structures are
these C `struct`s with mostly function pointers inside; this is
'interface pattern' or 'dependency injection'. It is really quite
useful, because it means that we can dynamically swap out
implementations. For example, right now, I've only written a single
threaded history implementation, but once a parallel version is provided, I
only have to use a new constructor (e.g. `tvb_hist_par_new()`) instead of
the default; nothing else changes. In old school C, I'd have to rewrite
all the calls to the history implementation.

With this in mind, function pointers sometimes take a little more
patience. In GDB for example, you need to set a breakpoint not as the
function name, but the file & line number, but stepping into a function
pointer call.

You can see a few more things I've thought about in C style
[here](https://github.com/maedoc/libtvb/issues/84).