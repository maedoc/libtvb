function sk_tests
% sk_tests Test SDDEKit
%
% This file collects informal set of tests of the MATLAB binding
%
% copyright 2016 Apache 2 sddekit authors

    %% sddekit's rng is independent of MATLAB's
    rng = rk_state;
    rng.seed = 42;
    r0 = rng.gauss();
    rng.seed = 42;
    assert(rng.gauss() == r0);

    %% history class
    dt = 0.1;
    vi = [1 1 0 0] + 1;
    vd = [5.5 4.5 33.3 0] * dt;
    h = sk_hist(vi, vd, 0.0, dt);
    assert(4 == h.nd)
    assert(4 == h.nd)
    assert(0.0 == h.t)
    assert(dt == h.dt)
    assert(2 == h.nu)
    assert(1 + 0 == h.lim(1))
    assert(1 + 36 == h.lim(2))
    assert(1 + 8 + 36 == h.lim(3))
    assert(1 + 36 == h.len(1))
    assert(1 + 8 == h.len(2))
    assert(1 + 0 == h.pos(1))
    assert(1 + 0 == h.pos(2))
    assert(1 + 0 == h.uvi(1))
    assert(1 + 1 == h.uvi(2))
    assert(1 + 1 == h.maxvi)
    assert(1 + 0 == h.vi2i(1))
    assert(1 + 1 == h.vi2i(2))
    assert(vd(1) == h.maxd(2))
    assert(vd(3) == h.maxd(1))
    assert(1 + 1 == h.vi(1))
    assert(1 + 1 == h.vi(2))
    assert(1 + 0 == h.vi(3))
    assert(1 + 0 == h.vi(4))
    assert(vd(1) == h.vd(1))
    assert(vd(2) == h.vd(2))
    assert(vd(3) == h.vd(3))
    assert(vd(4) == h.vd(4))

    h.fill(@(~, t, i) t)
    for i=1:35
        assert(-(i - 1)*dt == h.buf_lin(i))
    end
    assert(dt == h.buf_lin(36))
    for i=1:7
        assert(-(i - 1)*dt == h.buf_lin(36 + i))
    end
    assert(dt == h.buf_lin(36 + 8))

    allclose = @(l, r) all( (l - r).^2 < 1e-10);

    x = h.get(dt/3);
    assert(allclose(x, -vd(:)+dt/3));

    h.set(dt/2.0, [1.5 1.0])
    assert(allclose(h.buf_lin(36), 3.0))
    assert(allclose(h.buf_lin(36 + 8), 2.0))

    %% scheme
    sch = sk_sch_em(2);
    sys = [];
    sys.f = @test_sys_2d;
    x = [1 0]';
    c = [0 0]';
    t = 0.23;
    [x_, c_, sys_] = sch.apply(h, rng, sys, t, dt, x, c);
    assert(sys_.t == t);
    

end

% [f g c data] = sys(data, hist, t, i, x, c)
function [f, g, c, data] = test_sys_2d(data, hist, t, i, x, c)
    data.t = t;
    f = [x(2) -x(1)]';
    g = [0 0]';
    c = x(:);
end
