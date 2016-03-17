What is a stochastic delay differential equation?

Quickly, if you recognize
```
d/dt x = f(x(t))
```
it's an ODE. Its discretization in time looks like this
```
x_{t + dt} = x_t + f(x_t) dt
```
for the Euler method. Add a stochastic term, and it looks like this
```
x_{t + dt} = x_t + f(x_t) dt + g(x_t) dW_t
```
where `dW_t` is a Gaussian random number. This is the Euler-Maruyama method (implemented [here](https://github.com/maedoc/sddekit/blob/master/src/sd_scheme.c#L103), provided by the [`sd_sch_em_new`](https://github.com/maedoc/sddekit/blob/master/src/sddekit_api.h#L1244) constructor).

Now, add delays,
```
x_{t + dt} = x_t + f(x_t, x_{t - tau}) dt + g(x_t, x_{t - tau}) dW_t
```
where f & g now depend also on past values of x, and you have an SDDE.
