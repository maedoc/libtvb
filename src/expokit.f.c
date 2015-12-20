/*  -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b3 = 1.;
static integer c__1 = 1;
static doublereal c_b8 = 10.;
static integer c__9 = 9;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__6 = 6;
static doublereal c_b65 = 0.;
static integer c__2 = 2;
static doublereal c_b127 = -1.;
static doublereal c_b131 = 2.;
static doublecomplex c_b172 = {0.,0.};
static doublecomplex c_b173 = {1.,0.};

/* from expokit, free for non-commercial use */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dmexpv_(integer *n, integer *m, doublereal *t, 
	doublereal *v, doublereal *w, doublereal *tol, doublereal *anorm, 
	doublereal *wsp, integer *lwsp, integer *iwsp, integer *liwsp, S_fp 
	matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double d_sign(doublereal *, doublereal *), sqrt(doublereal), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__, roundoff;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublereal hij, sgn, eps, hj1j, sqr1, beta;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal hump;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static integer ifree, lfree;
    static doublereal t_old__;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    extern doublereal dasum_(integer *, doublereal *, integer *);
    static integer iexph;
    static doublereal t_new__;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer nexph;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal t_now__;
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    static doublereal vnorm;
    extern /* Subroutine */ int dgpadm_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, integer *), dnchbv_(integer *, doublereal *,
	     doublereal *, integer *, doublereal *, doublereal *);
    static integer nscale;
    static doublereal rndoff, t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal s_round__, tbrkdwn, s_error__, x_round__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___42 = { 0, 6, 0, 0, 0 };
    static cilist io___50 = { 0, 6, 0, 0, 0 };
    static cilist io___51 = { 0, 6, 0, 0, 0 };
    static cilist io___52 = { 0, 6, 0, 0, 0 };
    static cilist io___53 = { 0, 6, 0, 0, 0 };
    static cilist io___54 = { 0, 6, 0, 0, 0 };
    static cilist io___55 = { 0, 6, 0, 0, 0 };
    static cilist io___56 = { 0, 6, 0, 0, 0 };
    static cilist io___58 = { 0, 6, 0, 0, 0 };
    static cilist io___59 = { 0, 6, 0, 0, 0 };
    static cilist io___60 = { 0, 6, 0, 0, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___62 = { 0, 6, 0, 0, 0 };
    static cilist io___63 = { 0, 6, 0, 0, 0 };
    static cilist io___64 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  DMEXPV computes w = exp(t*A)*v - Customised for MARKOV CHAINS. */

/*     It does not compute the matrix exponential in isolation but */
/*     instead, it computes directly the action of the exponential */
/*     operator on the operand vector. This way of doing so allows */
/*     for addressing large sparse problems. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/*     This is a customised version for Markov Chains. This means that a */
/*     check is done within this code to ensure that the resulting vector */
/*     w is a probability vector, i.e., w must have all its components */
/*     in [0,1], with sum equal to 1. This check is done at some expense */
/*     and the user may try DGEXPV which is cheaper since it ignores */
/*     probability constraints. */

/*     IMPORTANT: The check assumes that the transition rate matrix Q */
/*                satisfies Qe = 0, where e=(1,...,1)'. Don't use DMEXPV */
/*                if this condition does not hold. Use DGEXPV instead. */
/*                DMEXPV/DGEXPV require the matrix-vector product */
/*                y = A*x = Q'*x, i.e, the TRANSPOSE of Q times a vector. */
/*                Failure to remember this leads to wrong results. */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     v(n)   : (input) given operand vector. */

/*     w(n)   : (output) computed approximation of exp(t*A)*v. */

/*     tol    : (input/output) the requested acurracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+2)^2+4*(m+2)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H     wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+2 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*              IMPORTANT: DMEXPV requires the product y = Ax = Q'x, i.e. */
/*              the TRANSPOSE of the transition rate matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = x_round, maximum among all roundoff errors (lower bound) */
/*     wsp(4)  = s_round, sum of roundoff errors (lower bound) */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */
/*     wsp(9)  = hump, i.e., max||exp(sA)||, s in [0,t] (or [t,0] if t<0) */
/*     wsp(10) = ||w||/||v||, scaled norm of the solution w. */
/*     -----------------------------------------------------------------| */
/*     The `hump' is a measure of the conditioning of the problem. The */
/*     matrix exponential is well-conditioned if hump = 1, whereas it is */
/*     poorly-conditioned if hump >> 1. However the solution can still be */
/*     relatively fairly accurate even when the hump is large (the hump */
/*     is an upper bound), especially when the hump and the scaled norm */
/*     of w [this is also computed and returned in wsp(10)] are of the */
/*     same order of magnitude (further details in reference below). */
/*     Markov chains are usually well-conditioned problems. */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). The value 0 switches to the */
/*               uniform rational Chebyshev approximation of type (14,14) */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --w;
    --v;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 2;
    if (*lwsp < *n * (*m + 2) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 2) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DMEXPV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 2;
    mh = *m + 2;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    sgn = d_sign(&c_b3, t);
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    s_round__ = 0.;
    x_error__ = 0.;
    x_round__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    dcopy_(n, &v[1], &c__1, &w[1], &c__1);
    beta = dnrm2_(n, &w[1], &c__1);
    vnorm = beta;
    hump = beta;

/* ---  obtain the very first stepsize ... */

    sqr1 = sqrt(.1);
    xm = 1. / (doublereal) (*m);
    d__1 = (*m + 1) / 2.72;
    i__1 = *m + 1;
    p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002);
    d__1 = p1 / (beta * 4. * *anorm);
    t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);
    p1 = 1. / beta;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[iv + i__ - 1] = p1 * w[i__];
    }
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + i__ - 1] = 0.;
    }

/* ---  Arnoldi loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    hij = ddot_(n, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &c__1)
		    ;
	    d__1 = -hij;
	    daxpy_(n, &d__1, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    wsp[ih + (j - 1) * mh + i__ - 1] = hij;
	}
	hj1j = dnrm2_(n, &wsp[j1v], &c__1);
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___42);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	wsp[ih + (j - 1) * mh + j] = hj1j;
	d__1 = 1. / hj1j;
	dscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dnrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1 for the 2-corrected scheme ... */

L300:
    wsp[ih + *m * mh + *m + 1] = 1.;

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*V*exp(t_step*H)*e1 .. */

    ++nexph;
    mx = mbrkdwn + k1;
    if (TRUE_) {
/* ---     irreducible rational Pade approximation ... */
	d__1 = sgn * t_step__;
	dgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[
		1], &iexph, &ns, iflag);
	iexph = ifree + iexph - 1;
	nscale += ns;
    } else {
/* ---     uniform rational Chebyshev approximation ... */
	iexph = ifree;
	i__1 = mx;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    wsp[iexph + i__ - 1] = 0.;
	}
	wsp[iexph] = 1.;
	d__1 = sgn * t_step__;
	dnchbv_(&mx, &d__1, &wsp[ih], &mh, &wsp[iexph], &wsp[ifree + mx]);
    }
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = (d__1 = wsp[iexph + *m], abs(d__1)) * beta;
	p2 = (d__1 = wsp[iexph + *m + 1], abs(d__1)) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m - 1);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___50);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___51);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___52);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___53);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___54);
	    do_lio(&c__9, &c__1, "Failure in DMEXPV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___55);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___56);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* ---  now update w = beta*V*exp(t_step*H)*e1 and the hump ... */

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 1;
    mx = mbrkdwn + max(i__1,i__2);
    dgemv_("n", n, &mx, &beta, &wsp[iv], n, &wsp[iexph], &c__1, &c_b65, &w[1],
	     &c__1, (ftnlen)1);
    beta = dnrm2_(n, &w[1], &c__1);
    hump = max(hump,beta);

/* ---  Markov model constraints ... */

    j = 0;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (w[i__] < 0.) {
	    w[i__] = 0.;
	    ++j;
	}
    }
    p1 = dasum_(n, &w[1], &c__1);
    if (j > 0) {
	d__1 = 1. / p1;
	dscal_(n, &d__1, &w[1], &c__1);
    }
    roundoff = (d__1 = 1. - p1, abs(d__1)) / (doublereal) (*n);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,roundoff);
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___58);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___59);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___60);
	do_lio(&c__9, &c__1, "wnorm     =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___61);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___62);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___63);
	do_lio(&c__9, &c__1, "roundoff  =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&roundoff, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___64);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    s_round__ += roundoff;
    x_error__ = max(x_error__,err_loc__);
    x_round__ = max(x_round__,roundoff);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    wsp[1] = step_min__;
    wsp[2] = step_max__;
    wsp[3] = x_round__;
    wsp[4] = s_round__;
    wsp[5] = x_error__;
    wsp[6] = s_error__;
    wsp[7] = tbrkdwn;
    wsp[8] = sgn * t_now__;
    wsp[9] = hump / vnorm;
    wsp[10] = beta / vnorm;
    return 0;
} /* dmexpv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgpadm_(integer *ideg, integer *m, doublereal *t, 
	doublereal *h__, integer *ldh, doublereal *wsp, integer *lwsp, 
	integer *ipiv, integer *iexph, integer *ns, integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double log(doublereal);
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal cp, cq;
    static integer ip, mm, iq, ih2, iodd, iget, iput, icoef;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal scale;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, ftnlen, ftnlen);
    static integer ifree;
    extern /* Subroutine */ int dgesv_(integer *, integer *, doublereal *, 
	    integer *, integer *, doublereal *, integer *, integer *);
    static integer iused;
    static doublereal hnorm;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal scale2;

/* -----Purpose----------------------------------------------------------| */

/*     Computes exp(t*H), the matrix exponential of a general matrix in */
/*     full, using the irreducible rational Pade approximation to the */
/*     exponential function exp(x) = r(x) = (+/-)( I + 2*(q(x)/p(x)) ), */
/*     combined with scaling-and-squaring. */

/* -----Arguments--------------------------------------------------------| */

/*     ideg      : (input) the degre of the diagonal Pade to be used. */
/*                 a value of 6 is generally satisfactory. */

/*     m         : (input) order of H. */

/*     H(ldh,m)  : (input) argument matrix. */

/*     t         : (input) time-scale (can be < 0). */

/*     wsp(lwsp) : (workspace/output) lwsp .ge. 4*m*m+ideg+1. */

/*     ipiv(m)   : (workspace) */

/* >>>> iexph     : (output) number such that wsp(iexph) points to exp(tH) */
/*                 i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1) */
/*                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                 NOTE: if the routine was called with wsp(iptr), */
/*                       then exp(tH) will start at wsp(iptr+iexph-1). */

/*     ns        : (output) number of scaling-squaring used. */

/*     iflag     : (output) exit flag. */
/*                      0 - no problem */
/*                     <0 - problem */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --ipiv;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;
    --wsp;

    /* Function Body */
    mm = *m * *m;
    *iflag = 0;
    if (*ldh < *m) {
	*iflag = -1;
    }
    if (*lwsp < (mm << 2) + *ideg + 1) {
	*iflag = -2;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DGPADM)", (ftnlen)30);
    }

/* ---  initialise pointers ... */

    icoef = 1;
    ih2 = icoef + (*ideg + 1);
    ip = ih2 + mm;
    iq = ip + mm;
    ifree = iq + mm;

/* ---  scaling: seek ns such that ||t*H/2^ns|| < 1/2; */
/*     and set scale = t/2^ns ... */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[i__] = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    wsp[i__] += (d__1 = h__[i__ + j * h_dim1], abs(d__1));
	}
    }
    hnorm = 0.;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = hnorm, d__2 = wsp[i__];
	hnorm = max(d__1,d__2);
    }
    hnorm = (d__1 = *t * hnorm, abs(d__1));
    if (hnorm == 0.) {
	s_stop("Error - null H in input of DGPADM.", (ftnlen)34);
    }
/* Computing MAX */
    i__1 = 0, i__2 = (integer) (log(hnorm) / log(2.)) + 2;
    *ns = max(i__1,i__2);
    scale = *t / (doublereal) pow_ii(&c__2, ns);
    scale2 = scale * scale;

/* ---  compute Pade coefficients ... */

    i__ = *ideg + 1;
    j = (*ideg << 1) + 1;
    wsp[icoef] = 1.;
    i__1 = *ideg;
    for (k = 1; k <= i__1; ++k) {
	wsp[icoef + k] = wsp[icoef + k - 1] * (doublereal) (i__ - k) / (
		doublereal) (k * (j - k));
    }

/* ---  H2 = scale2*H*H ... */

    dgemm_("n", "n", m, m, m, &scale2, &h__[h_offset], ldh, &h__[h_offset], 
	    ldh, &c_b65, &wsp[ih2], m, (ftnlen)1, (ftnlen)1);

/* ---  initialize p (numerator) and q (denominator) ... */

    cp = wsp[icoef + *ideg - 1];
    cq = wsp[icoef + *ideg];
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    wsp[ip + (j - 1) * *m + i__ - 1] = 0.;
	    wsp[iq + (j - 1) * *m + i__ - 1] = 0.;
	}
	wsp[ip + (j - 1) * (*m + 1)] = cp;
	wsp[iq + (j - 1) * (*m + 1)] = cq;
    }

/* ---  Apply Horner rule ... */

    iodd = 1;
    k = *ideg - 1;
L100:
    iused = iodd * iq + (1 - iodd) * ip;
    dgemm_("n", "n", m, m, m, &c_b3, &wsp[iused], m, &wsp[ih2], m, &c_b65, &
	    wsp[ifree], m, (ftnlen)1, (ftnlen)1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	wsp[ifree + (j - 1) * (*m + 1)] += wsp[icoef + k - 1];
    }
    ip = (1 - iodd) * ifree + iodd * ip;
    iq = iodd * ifree + (1 - iodd) * iq;
    ifree = iused;
    iodd = 1 - iodd;
    --k;
    if (k > 0) {
	goto L100;
    }

/* ---  Obtain (+/-)(I + 2*(p\q)) ... */

    if (iodd == 1) {
	dgemm_("n", "n", m, m, m, &scale, &wsp[iq], m, &h__[h_offset], ldh, &
		c_b65, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	iq = ifree;
    } else {
	dgemm_("n", "n", m, m, m, &scale, &wsp[ip], m, &h__[h_offset], ldh, &
		c_b65, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	ip = ifree;
    }
    daxpy_(&mm, &c_b127, &wsp[ip], &c__1, &wsp[iq], &c__1);
    dgesv_(m, m, &wsp[iq], m, &ipiv[1], &wsp[ip], m, iflag);
    if (*iflag != 0) {
	s_stop("Problem in DGESV (within DGPADM)", (ftnlen)32);
    }
    dscal_(&mm, &c_b131, &wsp[ip], &c__1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	wsp[ip + (j - 1) * (*m + 1)] += 1.;
    }
    iput = ip;
    if (*ns == 0 && iodd == 1) {
	dscal_(&mm, &c_b127, &wsp[ip], &c__1);
	goto L200;
    }

/* --   squaring : exp(t*H) = (exp(t*H))^(2^ns) ... */

    iodd = 1;
    i__1 = *ns;
    for (k = 1; k <= i__1; ++k) {
	iget = iodd * ip + (1 - iodd) * iq;
	iput = (1 - iodd) * ip + iodd * iq;
	dgemm_("n", "n", m, m, m, &c_b3, &wsp[iget], m, &wsp[iget], m, &c_b65,
		 &wsp[iput], m, (ftnlen)1, (ftnlen)1);
	iodd = 1 - iodd;
    }
L200:
    *iexph = iput;
    return 0;
} /* dgpadm_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dspadm_(integer *ideg, integer *m, doublereal *t, 
	doublereal *h__, integer *ldh, doublereal *wsp, integer *lwsp, 
	integer *ipiv, integer *iexph, integer *ns, integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double log(doublereal);
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal cp, cq;
    static integer ip, mm, iq, ih2, iodd, iget, iput, icoef;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal scale;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, ftnlen, ftnlen);
    static integer ifree, iused;
    static doublereal hnorm;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *), dsysv_(char *, integer *, 
	    integer *, doublereal *, integer *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, integer *, ftnlen);
    static doublereal scale2;

/* -----Purpose----------------------------------------------------------| */

/*     Computes exp(t*H), the matrix exponential of a symmetric matrix */
/*     in full, using the irreducible rational Pade approximation to the */
/*     exponential function exp(x) = r(x) = (+/-)( I + 2*(q(x)/p(x)) ), */
/*     combined with scaling-and-squaring. */

/* -----Arguments--------------------------------------------------------| */

/*     ideg      : (input) the degre of the diagonal Pade to be used. */
/*                 a value of 6 is generally satisfactory. */

/*     m         : (input) order of H. */

/*     H(ldh,m)  : (input) argument matrix (both lower and upper parts). */

/*     t         : (input) time-scale (can be < 0). */

/*     wsp(lwsp) : (workspace/output) lwsp .ge. 4*m*m+ideg+1. */

/*     ipiv(m)   : (workspace) */

/* >>>> iexph     : (output) number such that wsp(iexph) points to exp(tH) */
/*                 i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1) */
/*                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                 NOTE: if the routine was called with wsp(iptr), */
/*                       then exp(tH) will start at wsp(iptr+iexph-1). */

/*     ns        : (output) number of scaling-squaring used. */

/*     iflag     : (output) exit flag. */
/*                      0 - no problem */
/*                     <0 - problem */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --ipiv;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;
    --wsp;

    /* Function Body */
    mm = *m * *m;
    *iflag = 0;
    if (*ldh < *m) {
	*iflag = -1;
    }
    if (*lwsp < (mm << 2) + *ideg + 1) {
	*iflag = -2;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DSPADM)", (ftnlen)30);
    }

/* ---  initialise pointers ... */

    icoef = 1;
    ih2 = icoef + (*ideg + 1);
    ip = ih2 + mm;
    iq = ip + mm;
    ifree = iq + mm;

/* ---  scaling: seek ns such that ||t*H/2^ns|| < 1/2; */
/*     and set scale = t/2^ns ... */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[i__] = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    wsp[i__] += (d__1 = h__[i__ + j * h_dim1], abs(d__1));
	}
    }
    hnorm = 0.;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = hnorm, d__2 = wsp[i__];
	hnorm = max(d__1,d__2);
    }
    hnorm = (d__1 = *t * hnorm, abs(d__1));
    if (hnorm == 0.) {
	s_stop("Error - null H in input of DSPADM.", (ftnlen)34);
    }
/* Computing MAX */
    i__1 = 0, i__2 = (integer) (log(hnorm) / log(2.)) + 2;
    *ns = max(i__1,i__2);
    scale = *t / (doublereal) pow_ii(&c__2, ns);
    scale2 = scale * scale;

/* ---  compute Pade coefficients ... */

    i__ = *ideg + 1;
    j = (*ideg << 1) + 1;
    wsp[icoef] = 1.;
    i__1 = *ideg;
    for (k = 1; k <= i__1; ++k) {
	wsp[icoef + k] = wsp[icoef + k - 1] * (doublereal) (i__ - k) / (
		doublereal) (k * (j - k));
    }

/* ---  H2 = scale2*H*H ... */

    dgemm_("n", "n", m, m, m, &scale2, &h__[h_offset], ldh, &h__[h_offset], 
	    ldh, &c_b65, &wsp[ih2], m, (ftnlen)1, (ftnlen)1);

/* ---  initialize p (numerator) and q (denominator) ... */

    cp = wsp[icoef + *ideg - 1];
    cq = wsp[icoef + *ideg];
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    wsp[ip + (j - 1) * *m + i__ - 1] = 0.;
	    wsp[iq + (j - 1) * *m + i__ - 1] = 0.;
	}
	wsp[ip + (j - 1) * (*m + 1)] = cp;
	wsp[iq + (j - 1) * (*m + 1)] = cq;
    }

/* ---  Apply Horner rule ... */

    iodd = 1;
    k = *ideg - 1;
L100:
    iused = iodd * iq + (1 - iodd) * ip;
    dgemm_("n", "n", m, m, m, &c_b3, &wsp[iused], m, &wsp[ih2], m, &c_b65, &
	    wsp[ifree], m, (ftnlen)1, (ftnlen)1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	wsp[ifree + (j - 1) * (*m + 1)] += wsp[icoef + k - 1];
    }
    ip = (1 - iodd) * ifree + iodd * ip;
    iq = iodd * ifree + (1 - iodd) * iq;
    ifree = iused;
    iodd = 1 - iodd;
    --k;
    if (k > 0) {
	goto L100;
    }

/* ---  Obtain (+/-)(I + 2*(p\q)) ... */

    if (iodd == 1) {
	dgemm_("n", "n", m, m, m, &scale, &wsp[iq], m, &h__[h_offset], ldh, &
		c_b65, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	iq = ifree;
    } else {
	dgemm_("n", "n", m, m, m, &scale, &wsp[ip], m, &h__[h_offset], ldh, &
		c_b65, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	ip = ifree;
    }
    daxpy_(&mm, &c_b127, &wsp[ip], &c__1, &wsp[iq], &c__1);
    dsysv_("U", m, m, &wsp[iq], m, &ipiv[1], &wsp[ip], m, &wsp[ih2], &mm, 
	    iflag, (ftnlen)1);
    if (*iflag != 0) {
	s_stop("Problem in DSYSV (within DSPADM)", (ftnlen)32);
    }
    dscal_(&mm, &c_b131, &wsp[ip], &c__1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	wsp[ip + (j - 1) * (*m + 1)] += 1.;
    }
    iput = ip;
    if (*ns == 0 && iodd == 1) {
	dscal_(&mm, &c_b127, &wsp[ip], &c__1);
	goto L200;
    }

/* --   squaring : exp(t*H) = (exp(t*H))^(2^ns) ... */

    iodd = 1;
    i__1 = *ns;
    for (k = 1; k <= i__1; ++k) {
	iget = iodd * ip + (1 - iodd) * iq;
	iput = (1 - iodd) * ip + iodd * iq;
	dgemm_("n", "n", m, m, m, &c_b3, &wsp[iget], m, &wsp[iget], m, &c_b65,
		 &wsp[iput], m, (ftnlen)1, (ftnlen)1);
	iodd = 1 - iodd;
    }
L200:
    *iexph = iput;
    return 0;
} /* dspadm_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zgpadm_(integer *ideg, integer *m, doublereal *t, 
	doublecomplex *h__, integer *ldh, doublecomplex *wsp, integer *lwsp, 
	integer *ipiv, integer *iexph, integer *ns, integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double z_abs(doublecomplex *), log(doublereal);
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static integer i__, j, k;
    static doublecomplex cp, cq;
    static integer ip, mm, iq, ih2, iodd, iget, iput, icoef;
    static doublecomplex scale;
    static integer ifree, iused;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, ftnlen, ftnlen);
    static doublereal hnorm;
    extern /* Subroutine */ int zgesv_(integer *, integer *, doublecomplex *, 
	    integer *, integer *, doublecomplex *, integer *, integer *);
    static doublecomplex scale2;
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), zdscal_(
	    integer *, doublereal *, doublecomplex *, integer *);

/* -----Purpose----------------------------------------------------------| */

/*     Computes exp(t*H), the matrix exponential of a general complex */
/*     matrix in full, using the irreducible rational Pade approximation */
/*     to the exponential exp(z) = r(z) = (+/-)( I + 2*(q(z)/p(z)) ), */
/*     combined with scaling-and-squaring. */

/* -----Arguments--------------------------------------------------------| */

/*     ideg      : (input) the degre of the diagonal Pade to be used. */
/*                 a value of 6 is generally satisfactory. */

/*     m         : (input) order of H. */

/*     H(ldh,m)  : (input) argument matrix. */

/*     t         : (input) time-scale (can be < 0). */

/*     wsp(lwsp) : (workspace/output) lwsp .ge. 4*m*m+ideg+1. */

/*     ipiv(m)   : (workspace) */

/* >>>> iexph     : (output) number such that wsp(iexph) points to exp(tH) */
/*                 i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1) */
/*                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                 NOTE: if the routine was called with wsp(iptr), */
/*                       then exp(tH) will start at wsp(iptr+iexph-1). */

/*     ns        : (output) number of scaling-squaring used. */

/*     iflag     : (output) exit flag. */
/*                       0 - no problem */
/*                      <0 - problem */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --ipiv;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;
    --wsp;

    /* Function Body */
    mm = *m * *m;
    *iflag = 0;
    if (*ldh < *m) {
	*iflag = -1;
    }
    if (*lwsp < (mm << 2) + *ideg + 1) {
	*iflag = -2;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of ZGPADM)", (ftnlen)30);
    }

/* ---  initialise pointers ... */

    icoef = 1;
    ih2 = icoef + (*ideg + 1);
    ip = ih2 + mm;
    iq = ip + mm;
    ifree = iq + mm;

/* ---  scaling: seek ns such that ||t*H/2^ns|| < 1/2; */
/*     and set scale = t/2^ns ... */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__;
	    i__4 = i__;
	    d__1 = z_abs(&h__[i__ + j * h_dim1]);
	    z__1.r = wsp[i__4].r + d__1, z__1.i = wsp[i__4].i;
	    wsp[i__3].r = z__1.r, wsp[i__3].i = z__1.i;
	}
    }
    hnorm = 0.;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	i__2 = i__;
	d__1 = hnorm, d__2 = wsp[i__2].r;
	hnorm = max(d__1,d__2);
    }
    hnorm = (d__1 = *t * hnorm, abs(d__1));
    if (hnorm == 0.) {
	s_stop("Error - null H in input of ZGPADM.", (ftnlen)34);
    }
/* Computing MAX */
    i__1 = 0, i__2 = (integer) (log(hnorm) / log(2.)) + 2;
    *ns = max(i__1,i__2);
    d__1 = *t / (doublereal) pow_ii(&c__2, ns);
    z__1.r = d__1, z__1.i = 0.;
    scale.r = z__1.r, scale.i = z__1.i;
    z__1.r = scale.r * scale.r - scale.i * scale.i, z__1.i = scale.r * 
	    scale.i + scale.i * scale.r;
    scale2.r = z__1.r, scale2.i = z__1.i;

/* ---  compute Pade coefficients ... */

    i__ = *ideg + 1;
    j = (*ideg << 1) + 1;
    i__1 = icoef;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;
    i__1 = *ideg;
    for (k = 1; k <= i__1; ++k) {
	i__2 = icoef + k;
	i__3 = icoef + k - 1;
	d__1 = (doublereal) (i__ - k);
	z__2.r = d__1 * wsp[i__3].r, z__2.i = d__1 * wsp[i__3].i;
	d__2 = (doublereal) (k * (j - k));
	z__1.r = z__2.r / d__2, z__1.i = z__2.i / d__2;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }

/* ---  H2 = scale2*H*H ... */

    zgemm_("n", "n", m, m, m, &scale2, &h__[h_offset], ldh, &h__[h_offset], 
	    ldh, &c_b172, &wsp[ih2], m, (ftnlen)1, (ftnlen)1);

/* ---  initialise p (numerator) and q (denominator) ... */

    i__1 = icoef + *ideg - 1;
    cp.r = wsp[i__1].r, cp.i = wsp[i__1].i;
    i__1 = icoef + *ideg;
    cq.r = wsp[i__1].r, cq.i = wsp[i__1].i;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = ip + (j - 1) * *m + i__ - 1;
	    wsp[i__3].r = 0., wsp[i__3].i = 0.;
	    i__3 = iq + (j - 1) * *m + i__ - 1;
	    wsp[i__3].r = 0., wsp[i__3].i = 0.;
	}
	i__2 = ip + (j - 1) * (*m + 1);
	wsp[i__2].r = cp.r, wsp[i__2].i = cp.i;
	i__2 = iq + (j - 1) * (*m + 1);
	wsp[i__2].r = cq.r, wsp[i__2].i = cq.i;
    }

/* ---  Apply Horner rule ... */

    iodd = 1;
    k = *ideg - 1;
L100:
    iused = iodd * iq + (1 - iodd) * ip;
    zgemm_("n", "n", m, m, m, &c_b173, &wsp[iused], m, &wsp[ih2], m, &c_b172, 
	    &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ifree + (j - 1) * (*m + 1);
	i__3 = ifree + (j - 1) * (*m + 1);
	i__4 = icoef + k - 1;
	z__1.r = wsp[i__3].r + wsp[i__4].r, z__1.i = wsp[i__3].i + wsp[i__4]
		.i;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    ip = (1 - iodd) * ifree + iodd * ip;
    iq = iodd * ifree + (1 - iodd) * iq;
    ifree = iused;
    iodd = 1 - iodd;
    --k;
    if (k > 0) {
	goto L100;
    }

/* ---  Obtain (+/-)(I + 2*(p\q)) ... */

    if (iodd != 0) {
	zgemm_("n", "n", m, m, m, &scale, &wsp[iq], m, &h__[h_offset], ldh, &
		c_b172, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	iq = ifree;
    } else {
	zgemm_("n", "n", m, m, m, &scale, &wsp[ip], m, &h__[h_offset], ldh, &
		c_b172, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	ip = ifree;
    }
    z__1.r = -1., z__1.i = -0.;
    zaxpy_(&mm, &z__1, &wsp[ip], &c__1, &wsp[iq], &c__1);
    zgesv_(m, m, &wsp[iq], m, &ipiv[1], &wsp[ip], m, iflag);
    if (*iflag != 0) {
	s_stop("Problem in ZGESV (within ZGPADM)", (ftnlen)32);
    }
    zdscal_(&mm, &c_b131, &wsp[ip], &c__1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ip + (j - 1) * (*m + 1);
	i__3 = ip + (j - 1) * (*m + 1);
	z__1.r = wsp[i__3].r + 1., z__1.i = wsp[i__3].i + 0.;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    iput = ip;
    if (*ns == 0 && iodd != 0) {
	zdscal_(&mm, &c_b127, &wsp[ip], &c__1);
	goto L200;
    }

/* --   squaring : exp(t*H) = (exp(t*H))^(2^ns) ... */

    iodd = 1;
    i__1 = *ns;
    for (k = 1; k <= i__1; ++k) {
	iget = iodd * ip + (1 - iodd) * iq;
	iput = (1 - iodd) * ip + iodd * iq;
	zgemm_("n", "n", m, m, m, &c_b173, &wsp[iget], m, &wsp[iget], m, &
		c_b172, &wsp[iput], m, (ftnlen)1, (ftnlen)1);
	iodd = 1 - iodd;
    }
L200:
    *iexph = iput;
    return 0;
} /* zgpadm_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int zhpadm_(integer *ideg, integer *m, doublereal *t, 
	doublecomplex *h__, integer *ldh, doublecomplex *wsp, integer *lwsp, 
	integer *ipiv, integer *iexph, integer *ns, integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double z_abs(doublecomplex *), log(doublereal);
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static integer i__, j, k;
    static doublecomplex cp, cq;
    static integer ip, mm, iq, ih2, iodd, iget, iput, icoef;
    static doublecomplex scale;
    static integer ifree, iused;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *, ftnlen, ftnlen);
    static doublereal hnorm;
    extern /* Subroutine */ int zhesv_(char *, integer *, integer *, 
	    doublecomplex *, integer *, integer *, doublecomplex *, integer *,
	     doublecomplex *, integer *, integer *, ftnlen);
    static doublecomplex scale2;
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), zdscal_(
	    integer *, doublereal *, doublecomplex *, integer *);

/* -----Purpose----------------------------------------------------------| */

/*     Computes exp(t*H), the matrix exponential of an Hermitian matrix */
/*     in full, using the irreducible rational Pade approximation to the */
/*     exponential function exp(z) = r(z) = (+/-)( I + 2*(q(z)/p(z)) ), */
/*     combined with scaling-and-squaring. */

/* -----Arguments--------------------------------------------------------| */

/*     ideg      : (input) the degre of the diagonal Pade to be used. */
/*                 a value of 6 is generally satisfactory. */

/*     m         : (input) order of H. */

/*     H(ldh,m)  : (input) argument matrix (both lower and upper parts). */

/*     t         : (input) time-scale (can be < 0). */

/*     wsp(lwsp) : (workspace/output) lwsp .ge. 4*m*m+ideg+1. */

/*     ipiv(m)   : (workspace) */

/* >>>> iexph     : (output) number such that wsp(iexph) points to exp(tH) */
/*                 i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1) */
/*                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/*                 NOTE: if the routine was called with wsp(iptr), */
/*                       then exp(tH) will start at wsp(iptr+iexph-1). */

/*     ns        : (output) number of scaling-squaring used. */

/*     iflag     : (output) exit flag. */
/*                       0 - no problem */
/*                      <0 - problem */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --ipiv;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;
    --wsp;

    /* Function Body */
    mm = *m * *m;
    *iflag = 0;
    if (*ldh < *m) {
	*iflag = -1;
    }
    if (*lwsp < (mm << 2) + *ideg + 1) {
	*iflag = -2;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of ZHPADM)", (ftnlen)30);
    }

/* ---  initialise pointers ... */

    icoef = 1;
    ih2 = icoef + (*ideg + 1);
    ip = ih2 + mm;
    iq = ip + mm;
    ifree = iq + mm;

/* ---  scaling: seek ns such that ||t*H/2^ns|| < 1/2; */
/*     and set scale = t/2^ns ... */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = i__;
	    i__4 = i__;
	    d__1 = z_abs(&h__[i__ + j * h_dim1]);
	    z__1.r = wsp[i__4].r + d__1, z__1.i = wsp[i__4].i;
	    wsp[i__3].r = z__1.r, wsp[i__3].i = z__1.i;
	}
    }
    hnorm = 0.;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	i__2 = i__;
	d__1 = hnorm, d__2 = wsp[i__2].r;
	hnorm = max(d__1,d__2);
    }
    hnorm = (d__1 = *t * hnorm, abs(d__1));
    if (hnorm == 0.) {
	s_stop("Error - null H in input of ZHPADM.", (ftnlen)34);
    }
/* Computing MAX */
    i__1 = 0, i__2 = (integer) (log(hnorm) / log(2.)) + 2;
    *ns = max(i__1,i__2);
    d__1 = *t / (doublereal) pow_ii(&c__2, ns);
    z__1.r = d__1, z__1.i = 0.;
    scale.r = z__1.r, scale.i = z__1.i;
    z__1.r = scale.r * scale.r - scale.i * scale.i, z__1.i = scale.r * 
	    scale.i + scale.i * scale.r;
    scale2.r = z__1.r, scale2.i = z__1.i;

/* ---  compute Pade coefficients ... */

    i__ = *ideg + 1;
    j = (*ideg << 1) + 1;
    i__1 = icoef;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;
    i__1 = *ideg;
    for (k = 1; k <= i__1; ++k) {
	i__2 = icoef + k;
	i__3 = icoef + k - 1;
	d__1 = (doublereal) (i__ - k);
	z__2.r = d__1 * wsp[i__3].r, z__2.i = d__1 * wsp[i__3].i;
	d__2 = (doublereal) (k * (j - k));
	z__1.r = z__2.r / d__2, z__1.i = z__2.i / d__2;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }

/* ---  H2 = scale2*H*H ... */

    zgemm_("n", "n", m, m, m, &scale2, &h__[h_offset], ldh, &h__[h_offset], 
	    ldh, &c_b172, &wsp[ih2], m, (ftnlen)1, (ftnlen)1);

/* ---  initialise p (numerator) and q (denominator) ... */

    i__1 = icoef + *ideg - 1;
    cp.r = wsp[i__1].r, cp.i = wsp[i__1].i;
    i__1 = icoef + *ideg;
    cq.r = wsp[i__1].r, cq.i = wsp[i__1].i;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = ip + (j - 1) * *m + i__ - 1;
	    wsp[i__3].r = 0., wsp[i__3].i = 0.;
	    i__3 = iq + (j - 1) * *m + i__ - 1;
	    wsp[i__3].r = 0., wsp[i__3].i = 0.;
	}
	i__2 = ip + (j - 1) * (*m + 1);
	wsp[i__2].r = cp.r, wsp[i__2].i = cp.i;
	i__2 = iq + (j - 1) * (*m + 1);
	wsp[i__2].r = cq.r, wsp[i__2].i = cq.i;
    }

/* ---  Apply Horner rule ... */

    iodd = 1;
    k = *ideg - 1;
L100:
    iused = iodd * iq + (1 - iodd) * ip;
    zgemm_("n", "n", m, m, m, &c_b173, &wsp[iused], m, &wsp[ih2], m, &c_b172, 
	    &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ifree + (j - 1) * (*m + 1);
	i__3 = ifree + (j - 1) * (*m + 1);
	i__4 = icoef + k - 1;
	z__1.r = wsp[i__3].r + wsp[i__4].r, z__1.i = wsp[i__3].i + wsp[i__4]
		.i;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    ip = (1 - iodd) * ifree + iodd * ip;
    iq = iodd * ifree + (1 - iodd) * iq;
    ifree = iused;
    iodd = 1 - iodd;
    --k;
    if (k > 0) {
	goto L100;
    }

/* ---  Obtain (+/-)(I + 2*(p\q)) ... */

    if (iodd != 0) {
	zgemm_("n", "n", m, m, m, &scale, &wsp[iq], m, &h__[h_offset], ldh, &
		c_b172, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	iq = ifree;
    } else {
	zgemm_("n", "n", m, m, m, &scale, &wsp[ip], m, &h__[h_offset], ldh, &
		c_b172, &wsp[ifree], m, (ftnlen)1, (ftnlen)1);
	ip = ifree;
    }
    z__1.r = -1., z__1.i = -0.;
    zaxpy_(&mm, &z__1, &wsp[ip], &c__1, &wsp[iq], &c__1);
    zhesv_("U", m, m, &wsp[iq], m, &ipiv[1], &wsp[ip], m, &wsp[ih2], &mm, 
	    iflag, (ftnlen)1);
    if (*iflag != 0) {
	s_stop("Problem in ZHESV (within ZHPADM)", (ftnlen)32);
    }
    zdscal_(&mm, &c_b131, &wsp[ip], &c__1);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ip + (j - 1) * (*m + 1);
	i__3 = ip + (j - 1) * (*m + 1);
	z__1.r = wsp[i__3].r + 1., z__1.i = wsp[i__3].i + 0.;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    iput = ip;
    if (*ns == 0 && iodd != 0) {
	zdscal_(&mm, &c_b127, &wsp[ip], &c__1);
	goto L200;
    }

/* --   squaring : exp(t*H) = (exp(t*H))^(2^ns) ... */

    iodd = 1;
    i__1 = *ns;
    for (k = 1; k <= i__1; ++k) {
	iget = iodd * ip + (1 - iodd) * iq;
	iput = (1 - iodd) * ip + iodd * iq;
	zgemm_("n", "n", m, m, m, &c_b173, &wsp[iget], m, &wsp[iget], m, &
		c_b172, &wsp[iput], m, (ftnlen)1, (ftnlen)1);
	iodd = 1 - iodd;
    }
L200:
    *iexph = iput;
    return 0;
} /* zhpadm_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgchbv_(integer *m, doublereal *t, doublereal *h__, 
	integer *ldh, doublereal *y, doublecomplex *wsp, integer *iwsp, 
	integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, ih, ip, iy, iz;
    static doublecomplex alpha[7], theta[7];
    extern /* Subroutine */ int zgesv_(integer *, integer *, doublecomplex *, 
	    integer *, integer *, doublecomplex *, integer *, integer *);
    static doublereal alpha0;

/* -----Purpose----------------------------------------------------------| */

/* ---  DGCHBV computes y = exp(t*H)*y using the partial fraction */
/*     expansion of the uniform rational Chebyshev approximation */
/*     to exp(-x) of type (14,14). H is a General matrix. */
/*     About 14-digit accuracy is expected if the matrix H is negative */
/*     definite. The algorithm may behave poorly otherwise. */

/* -----Arguments--------------------------------------------------------| */

/*     m       : (input) order of the matrix H */

/*     t       : (input) time-scaling factor (can be < 0). */

/*     H(ldh,m): (input) argument matrix. */

/*     y(m)    : (input/output) on input the operand vector, */
/*               on output the resulting vector exp(t*H)*y. */

/*     iwsp(m) : (workspace) */

/*     wsp     : (workspace). Observe that a double precision vector of */
/*               length 2*m*(m+2) can be used as well when calling this */
/*               routine (thus avoiding an idle complex array elsewhere) */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  Pointers ... */
    /* Parameter adjustments */
    --iwsp;
    --wsp;
    --y;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;

    /* Function Body */
    ih = 1;
    iy = ih + *m * *m;
    iz = iy + *m;
/* ---  Coefficients and poles of the partial fraction expansion ... */
    alpha0 = 1.83216998528140087e-12;
    alpha[0].r = 55.7503973136501826, alpha[0].i = -204.295038779771857;
    alpha[1].r = -93.8666838877006739, alpha[1].i = 91.2874896775456363;
    alpha[2].r = 46.9965415550370835, alpha[2].i = -11.6167609985818103;
    alpha[3].r = -9.61424200626061065, alpha[3].i = -2.64195613880262669;
    alpha[4].r = .752722063978321642, alpha[4].i = .67036736556637777;
    alpha[5].r = -.0188781253158648576, alpha[5].i = -.0343696176445802414;
    alpha[6].r = 1.43086431411801849e-4, alpha[6].i = 2.87221133228814096e-4;
    theta[0].r = -5.62314417475317895, theta[0].i = 1.1940692161124744;
    theta[1].r = -5.0893467972821611, theta[1].i = 3.58882439228376881;
    theta[2].r = -3.99337136365302569, theta[2].i = 6.00483209099604664;
    theta[3].r = -2.26978543095856366, theta[3].i = 8.46173881758693369;
    theta[4].r = .208756929753827868, theta[4].i = 10.9912615662209418;
    theta[5].r = 3.70327340957595652, theta[5].i = 13.6563731924991884;
    theta[6].r = 8.89777151877331107, theta[6].i = 16.6309842834712071;

/* ---  Accumulation of the contribution of each pole ... */

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = iz + j - 1;
	i__3 = j;
	wsp[i__2].r = y[i__3], wsp[i__2].i = 0.;
	y[j] *= alpha0;
    }
    for (ip = 1; ip <= 7; ++ip) {
/* ---     Solve each fraction using Gaussian elimination with pivoting... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = ih + (j - 1) * *m + i__ - 1;
		d__1 = -(*t) * h__[i__ + j * h_dim1];
		wsp[i__3].r = d__1, wsp[i__3].i = 0.;
	    }
	    i__2 = ih + (j - 1) * *m + j - 1;
	    i__3 = ih + (j - 1) * *m + j - 1;
	    i__4 = ip - 1;
	    z__1.r = wsp[i__3].r - theta[i__4].r, z__1.i = wsp[i__3].i - 
		    theta[i__4].i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	    i__2 = iy + j - 1;
	    i__3 = iz + j - 1;
	    wsp[i__2].r = wsp[i__3].r, wsp[i__2].i = wsp[i__3].i;
	}
	zgesv_(m, &c__1, &wsp[ih], m, &iwsp[1], &wsp[iy], m, iflag);
	if (*iflag != 0) {
	    s_stop("Error in DGCHBV", (ftnlen)15);
	}
/* ---     Accumulate the partial result in y ... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = ip - 1;
	    i__3 = iy + j - 1;
	    z__1.r = alpha[i__2].r * wsp[i__3].r - alpha[i__2].i * wsp[i__3]
		    .i, z__1.i = alpha[i__2].r * wsp[i__3].i + alpha[i__2].i *
		     wsp[i__3].r;
	    y[j] += z__1.r;
	}
    }
    return 0;
} /* dgchbv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dschbv_(integer *m, doublereal *t, doublereal *h__, 
	integer *ldh, doublereal *y, doublecomplex *wsp, integer *iwsp, 
	integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, ih, ip, iy, iz;
    static doublecomplex alpha[7], theta[7];
    static doublereal alpha0;

/* -----Purpose----------------------------------------------------------| */

/* ---  DSCHBV computes y = exp(t*H)*y using the partial fraction */
/*     expansion of the uniform rational Chebyshev approximation */
/*     to exp(-x) of type (14,14). H is assumed to be symmetric. */
/*     About 14-digit accuracy is expected if the matrix H is negative */
/*     definite. The algorithm may behave poorly otherwise. */

/* -----Arguments--------------------------------------------------------| */

/*     m       : (input) order of matrix H */

/*     t       : (input) time-scaling factor (can be < 0). */

/*     H(ldh,m): (input) symmetric matrix. */

/*     y(m)    : (input/output) on input the operand vector, */
/*               on output the resulting vector exp(t*H)*y. */

/*     iwsp(m) : (workspace) */

/*     wsp     : (workspace). Observe that a double precision vector of */
/*               length 2*m*(m+2) can be used as well when calling this */
/*               routine (thus avoiding an idle complex array elsewhere) */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  Pointers ... */
    /* Parameter adjustments */
    --iwsp;
    --wsp;
    --y;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;

    /* Function Body */
    ih = 1;
    iy = ih + *m * *m;
    iz = iy + *m;
/* ---  Coefficients and poles of the partial fraction expansion ... */
    alpha0 = 1.83216998528140087e-12;
    alpha[0].r = 55.7503973136501826, alpha[0].i = -204.295038779771857;
    alpha[1].r = -93.8666838877006739, alpha[1].i = 91.2874896775456363;
    alpha[2].r = 46.9965415550370835, alpha[2].i = -11.6167609985818103;
    alpha[3].r = -9.61424200626061065, alpha[3].i = -2.64195613880262669;
    alpha[4].r = .752722063978321642, alpha[4].i = .67036736556637777;
    alpha[5].r = -.0188781253158648576, alpha[5].i = -.0343696176445802414;
    alpha[6].r = 1.43086431411801849e-4, alpha[6].i = 2.87221133228814096e-4;
    theta[0].r = -5.62314417475317895, theta[0].i = 1.1940692161124744;
    theta[1].r = -5.0893467972821611, theta[1].i = 3.58882439228376881;
    theta[2].r = -3.99337136365302569, theta[2].i = 6.00483209099604664;
    theta[3].r = -2.26978543095856366, theta[3].i = 8.46173881758693369;
    theta[4].r = .208756929753827868, theta[4].i = 10.9912615662209418;
    theta[5].r = 3.70327340957595652, theta[5].i = 13.6563731924991884;
    theta[6].r = 8.89777151877331107, theta[6].i = 16.6309842834712071;

/* ---  Accumulation of the contribution of each pole ... */

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = iz + j - 1;
	i__3 = j;
	wsp[i__2].r = y[i__3], wsp[i__2].i = 0.;
	y[j] *= alpha0;
    }
    for (ip = 1; ip <= 7; ++ip) {
/* ---     Solve each fraction using Gaussian elimination with pivoting... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = ih + (j - 1) * *m + i__ - 1;
		d__1 = -(*t) * h__[i__ + j * h_dim1];
		wsp[i__3].r = d__1, wsp[i__3].i = 0.;
	    }
	    i__2 = ih + (j - 1) * *m + j - 1;
	    i__3 = ih + (j - 1) * *m + j - 1;
	    i__4 = ip - 1;
	    z__1.r = wsp[i__3].r - theta[i__4].r, z__1.i = wsp[i__3].i - 
		    theta[i__4].i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	    i__2 = iy + j - 1;
	    i__3 = iz + j - 1;
	    wsp[i__2].r = wsp[i__3].r, wsp[i__2].i = wsp[i__3].i;
	}
/* call ZSYSV('U', M, 1, WSP(iH),M, IWSP, WSP(iY),M, W,1, IFLAG ) */
	if (*iflag != 0) {
	    s_stop("Error in DSCHBV", (ftnlen)15);
	}
/* ---     Accumulate the partial result in y ... */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = ip - 1;
	    i__3 = iy + i__ - 1;
	    z__1.r = alpha[i__2].r * wsp[i__3].r - alpha[i__2].i * wsp[i__3]
		    .i, z__1.i = alpha[i__2].r * wsp[i__3].i + alpha[i__2].i *
		     wsp[i__3].r;
	    y[i__] += z__1.r;
	}
    }
    return 0;
} /* dschbv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zgchbv_(integer *m, doublereal *t, doublecomplex *h__, 
	integer *ldh, doublecomplex *y, doublecomplex *wsp, integer *iwsp, 
	integer *iflag)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4, i__5;
    doublereal d__1;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    void d_cnjg(doublecomplex *, doublecomplex *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, ih, ip, iy, iz;
    static doublecomplex alpha[14], theta[14];
    extern /* Subroutine */ int zgesv_(integer *, integer *, doublecomplex *, 
	    integer *, integer *, doublecomplex *, integer *, integer *);
    static doublereal alpha0;

/* -----Purpose----------------------------------------------------------| */

/* ---  ZGCHBV computes y = exp(t*H)*y using the partial fraction */
/*     expansion of the uniform rational Chebyshev approximation */
/*     to exp(-x) of type (14,14). H is a General matrix. */
/*     About 14-digit accuracy is expected if the matrix H is negative */
/*     definite. The algorithm may behave poorly otherwise. */

/* -----Arguments--------------------------------------------------------| */

/*     m       : (input) order of the matrix H. */

/*     t       : (input) time-scaling factor (can be < 0). */

/*     H(ldh,m): (input) argument matrix. */

/*     y(m)    : (input/output) on input the operand vector, */
/*               on output the resulting vector exp(t*H)*y. */

/*     iwsp(m) : (workspace) */

/*     wsp     : (workspace). Observe that a double precision vector of */
/*               length 2*m*(m+2) can be used as well when calling this */
/*               routine. */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  Pointers ... */
    /* Parameter adjustments */
    --iwsp;
    --wsp;
    --y;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;

    /* Function Body */
    ih = 1;
    iy = ih + *m * *m;
    iz = iy + *m;
/* ---  Coefficients and poles of the partial fraction expansion ... */
    alpha0 = 1.83216998528140087e-12;
    alpha[0].r = 55.7503973136501826, alpha[0].i = -204.295038779771857;
    alpha[1].r = -93.8666838877006739, alpha[1].i = 91.2874896775456363;
    alpha[2].r = 46.9965415550370835, alpha[2].i = -11.6167609985818103;
    alpha[3].r = -9.61424200626061065, alpha[3].i = -2.64195613880262669;
    alpha[4].r = .752722063978321642, alpha[4].i = .67036736556637777;
    alpha[5].r = -.0188781253158648576, alpha[5].i = -.0343696176445802414;
    alpha[6].r = 1.43086431411801849e-4, alpha[6].i = 2.87221133228814096e-4;
    theta[0].r = -5.62314417475317895, theta[0].i = 1.1940692161124744;
    theta[1].r = -5.0893467972821611, theta[1].i = 3.58882439228376881;
    theta[2].r = -3.99337136365302569, theta[2].i = 6.00483209099604664;
    theta[3].r = -2.26978543095856366, theta[3].i = 8.46173881758693369;
    theta[4].r = .208756929753827868, theta[4].i = 10.9912615662209418;
    theta[5].r = 3.70327340957595652, theta[5].i = 13.6563731924991884;
    theta[6].r = 8.89777151877331107, theta[6].i = 16.6309842834712071;

    for (ip = 1; ip <= 7; ++ip) {
	i__1 = ip + 6;
	d_cnjg(&z__1, &theta[ip - 1]);
	theta[i__1].r = z__1.r, theta[i__1].i = z__1.i;
	i__1 = ip + 6;
	d_cnjg(&z__1, &alpha[ip - 1]);
	alpha[i__1].r = z__1.r, alpha[i__1].i = z__1.i;
    }

/* ---  Accumulation of the contribution of each pole ... */

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = iz + j - 1;
	i__3 = j;
	wsp[i__2].r = y[i__3].r, wsp[i__2].i = y[i__3].i;
	i__2 = j;
	i__3 = j;
	z__1.r = alpha0 * y[i__3].r, z__1.i = alpha0 * y[i__3].i;
	y[i__2].r = z__1.r, y[i__2].i = z__1.i;
    }
    for (ip = 1; ip <= 14; ++ip) {
	i__1 = ip - 1;
	i__2 = ip - 1;
	z__1.r = alpha[i__2].r * .5, z__1.i = alpha[i__2].i * .5;
	alpha[i__1].r = z__1.r, alpha[i__1].i = z__1.i;
/* ---     Solve each fraction using Gaussian elimination with pivoting... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = ih + (j - 1) * *m + i__ - 1;
		d__1 = -(*t);
		i__4 = i__ + j * h_dim1;
		z__1.r = d__1 * h__[i__4].r, z__1.i = d__1 * h__[i__4].i;
		wsp[i__3].r = z__1.r, wsp[i__3].i = z__1.i;
	    }
	    i__2 = ih + (j - 1) * *m + j - 1;
	    i__3 = ih + (j - 1) * *m + j - 1;
	    i__4 = ip - 1;
	    z__1.r = wsp[i__3].r - theta[i__4].r, z__1.i = wsp[i__3].i - 
		    theta[i__4].i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	    i__2 = iy + j - 1;
	    i__3 = iz + j - 1;
	    wsp[i__2].r = wsp[i__3].r, wsp[i__2].i = wsp[i__3].i;
	}
	zgesv_(m, &c__1, &wsp[ih], m, &iwsp[1], &wsp[iy], m, iflag);
	if (*iflag != 0) {
	    s_stop("Error in ZGCHBV", (ftnlen)15);
	}
/* ---     Accumulate the partial result in y ... */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    i__3 = i__;
	    i__4 = ip - 1;
	    i__5 = iy + i__ - 1;
	    z__2.r = alpha[i__4].r * wsp[i__5].r - alpha[i__4].i * wsp[i__5]
		    .i, z__2.i = alpha[i__4].r * wsp[i__5].i + alpha[i__4].i *
		     wsp[i__5].r;
	    z__1.r = y[i__3].r + z__2.r, z__1.i = y[i__3].i + z__2.i;
	    y[i__2].r = z__1.r, y[i__2].i = z__1.i;
	}
    }
    return 0;
} /* zgchbv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dnchbv_(integer *m, doublereal *t, doublereal *h__, 
	integer *ldh, doublereal *y, doublecomplex *wsp)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4;
    doublereal d__1;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    double z_abs(doublecomplex *);
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer i__, j, k, ih, ip, iy, iz;
    static doublecomplex tmpc, alpha[7], theta[7];
    extern /* Subroutine */ int zswap_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    static doublereal alpha0;
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);

/* -----Purpose----------------------------------------------------------| */

/* ---  DNCHBV computes y = exp(t*H)*y using the partial fraction */
/*     expansion of the uniform rational Chebyshev approximation */
/*     to exp(-x) of type (14,14). H is assumed to be upper-Hessenberg. */
/*     About 14-digit accuracy is expected if the matrix H is negative */
/*     definite. The algorithm may behave poorly otherwise. */

/* -----Arguments--------------------------------------------------------| */

/*     m       : (input) order of the Hessenberg matrix H */

/*     t       : (input) time-scaling factor (can be < 0). */

/*     H(ldh,m): (input) upper Hessenberg matrix. */

/*     y(m)    : (input/output) on input the operand vector, */
/*               on output the resulting vector exp(t*H)*y. */

/*     wsp     : (workspace). Observe that a double precision vector of */
/*               length 2*m*(m+2) can be used as well when calling this */
/*               routine (thus avoiding an idle complex array elsewhere) */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  Pointers ... */
    /* Parameter adjustments */
    --wsp;
    --y;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;

    /* Function Body */
    ih = 1;
    iy = ih + *m * *m;
    iz = iy + *m;
/* ---  Coefficients and poles of the partial fraction expansion... */
    alpha0 = 1.83216998528140087e-12;
    alpha[0].r = 55.7503973136501826, alpha[0].i = -204.295038779771857;
    alpha[1].r = -93.8666838877006739, alpha[1].i = 91.2874896775456363;
    alpha[2].r = 46.9965415550370835, alpha[2].i = -11.6167609985818103;
    alpha[3].r = -9.61424200626061065, alpha[3].i = -2.64195613880262669;
    alpha[4].r = .752722063978321642, alpha[4].i = .67036736556637777;
    alpha[5].r = -.0188781253158648576, alpha[5].i = -.0343696176445802414;
    alpha[6].r = 1.43086431411801849e-4, alpha[6].i = 2.87221133228814096e-4;
    theta[0].r = -5.62314417475317895, theta[0].i = 1.1940692161124744;
    theta[1].r = -5.0893467972821611, theta[1].i = 3.58882439228376881;
    theta[2].r = -3.99337136365302569, theta[2].i = 6.00483209099604664;
    theta[3].r = -2.26978543095856366, theta[3].i = 8.46173881758693369;
    theta[4].r = .208756929753827868, theta[4].i = 10.9912615662209418;
    theta[5].r = 3.70327340957595652, theta[5].i = 13.6563731924991884;
    theta[6].r = 8.89777151877331107, theta[6].i = 16.6309842834712071;

/* ---  Accumulation of the contribution of each pole ... */

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = iz + j - 1;
	i__3 = j;
	wsp[i__2].r = y[i__3], wsp[i__2].i = 0.;
	y[j] *= alpha0;
    }
    for (ip = 1; ip <= 7; ++ip) {
/* ---     Solve each fraction using Gaussian elimination with pivoting... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = iy + j - 1;
	    i__3 = iz + j - 1;
	    wsp[i__2].r = wsp[i__3].r, wsp[i__2].i = wsp[i__3].i;
/* Computing MIN */
	    i__3 = j + 1;
	    i__2 = min(i__3,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = ih + (j - 1) * *m + i__ - 1;
		d__1 = -(*t) * h__[i__ + j * h_dim1];
		wsp[i__3].r = d__1, wsp[i__3].i = 0.;
	    }
	    i__2 = ih + (j - 1) * *m + j - 1;
	    i__3 = ih + (j - 1) * *m + j - 1;
	    i__4 = ip - 1;
	    z__1.r = wsp[i__3].r - theta[i__4].r, z__1.i = wsp[i__3].i - 
		    theta[i__4].i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	    i__2 = *m;
	    for (k = i__; k <= i__2; ++k) {
		i__3 = ih + (j - 1) * *m + k - 1;
		wsp[i__3].r = 0., wsp[i__3].i = 0.;
	    }
	}
	i__1 = *m - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* ---        Get pivot and exchange rows ... */
	    if (z_abs(&wsp[ih + (i__ - 1) * *m + i__ - 1]) < z_abs(&wsp[ih + (
		    i__ - 1) * *m + i__])) {
		i__2 = *m - i__ + 1;
		zswap_(&i__2, &wsp[ih + (i__ - 1) * *m + i__ - 1], m, &wsp[ih 
			+ (i__ - 1) * *m + i__], m);
		zswap_(&c__1, &wsp[iy + i__ - 1], &c__1, &wsp[iy + i__], &
			c__1);
	    }
/* ---        Forward eliminiation ... */
	    z_div(&z__1, &wsp[ih + (i__ - 1) * *m + i__], &wsp[ih + (i__ - 1) 
		    * *m + i__ - 1]);
	    tmpc.r = z__1.r, tmpc.i = z__1.i;
	    i__2 = *m - i__;
	    z__1.r = -tmpc.r, z__1.i = -tmpc.i;
	    zaxpy_(&i__2, &z__1, &wsp[ih + i__ * *m + i__ - 1], m, &wsp[ih + 
		    i__ * *m + i__], m);
	    i__2 = iy + i__;
	    i__3 = iy + i__;
	    i__4 = iy + i__ - 1;
	    z__2.r = tmpc.r * wsp[i__4].r - tmpc.i * wsp[i__4].i, z__2.i = 
		    tmpc.r * wsp[i__4].i + tmpc.i * wsp[i__4].r;
	    z__1.r = wsp[i__3].r - z__2.r, z__1.i = wsp[i__3].i - z__2.i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	}
/* ---     Backward substitution ... */
	for (i__ = *m; i__ >= 1; --i__) {
	    i__1 = iy + i__ - 1;
	    tmpc.r = wsp[i__1].r, tmpc.i = wsp[i__1].i;
	    i__1 = *m;
	    for (j = i__ + 1; j <= i__1; ++j) {
		i__2 = ih + (j - 1) * *m + i__ - 1;
		i__3 = iy + j - 1;
		z__2.r = wsp[i__2].r * wsp[i__3].r - wsp[i__2].i * wsp[i__3]
			.i, z__2.i = wsp[i__2].r * wsp[i__3].i + wsp[i__2].i *
			 wsp[i__3].r;
		z__1.r = tmpc.r - z__2.r, z__1.i = tmpc.i - z__2.i;
		tmpc.r = z__1.r, tmpc.i = z__1.i;
	    }
	    i__1 = iy + i__ - 1;
	    z_div(&z__1, &tmpc, &wsp[ih + (i__ - 1) * *m + i__ - 1]);
	    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
	}
/* ---     Accumulate the partial result in y ... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = ip - 1;
	    i__3 = iy + j - 1;
	    z__1.r = alpha[i__2].r * wsp[i__3].r - alpha[i__2].i * wsp[i__3]
		    .i, z__1.i = alpha[i__2].r * wsp[i__3].i + alpha[i__2].i *
		     wsp[i__3].r;
	    y[j] += z__1.r;
	}
    }
    return 0;
} /* dnchbv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int znchbv_(integer *m, doublereal *t, doublecomplex *h__, 
	integer *ldh, doublecomplex *y, doublecomplex *wsp)
{
    /* System generated locals */
    integer h_dim1, h_offset, i__1, i__2, i__3, i__4, i__5;
    doublereal d__1;
    doublecomplex z__1, z__2;

    /* Builtin functions */
    void d_cnjg(doublecomplex *, doublecomplex *);
    double z_abs(doublecomplex *);
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer i__, j, k, ih, ip, iy, iz;
    static doublecomplex tmpc, alpha[7], theta[7];
    extern /* Subroutine */ int zswap_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    static doublereal alpha0;
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);

/* -----Purpose----------------------------------------------------------| */

/* ---  ZNCHBV computes y = exp(t*H)*y using the partial fraction */
/*     expansion of the uniform rational Chebyshev approximation */
/*     to exp(-x) of type (14,14). H is assumed to be upper-Hessenberg. */
/*     About 14-digit accuracy is expected if the matrix H is negative */
/*     definite. The algorithm may behave poorly otherwise. */

/* -----Arguments--------------------------------------------------------| */

/*     m       : (input) order of the Hessenberg matrix H */

/*     t       : (input) time-scaling factor (can be < 0). */

/*     H(ldh,m): (input) upper Hessenberg matrix. */

/*     y(m)    : (input/output) on input the operand vector, */
/*               on output the resulting vector exp(t*H)*y. */

/*     wsp     : (workspace). Observe that a double precision vector of */
/*               length 2*m*(m+2) can be used as well when calling this */
/*               routine. */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  Pointers ... */
    /* Parameter adjustments */
    --wsp;
    --y;
    h_dim1 = *ldh;
    h_offset = 1 + h_dim1;
    h__ -= h_offset;

    /* Function Body */
    ih = 1;
    iy = ih + *m * *m;
    iz = iy + *m;
/* ---  Coefficients and poles of the partial fraction expansion... */
    alpha0 = 1.83216998528140087e-12;
    alpha[0].r = 55.7503973136501826, alpha[0].i = -204.295038779771857;
    alpha[1].r = -93.8666838877006739, alpha[1].i = 91.2874896775456363;
    alpha[2].r = 46.9965415550370835, alpha[2].i = -11.6167609985818103;
    alpha[3].r = -9.61424200626061065, alpha[3].i = -2.64195613880262669;
    alpha[4].r = .752722063978321642, alpha[4].i = .67036736556637777;
    alpha[5].r = -.0188781253158648576, alpha[5].i = -.0343696176445802414;
    alpha[6].r = 1.43086431411801849e-4, alpha[6].i = 2.87221133228814096e-4;
    theta[0].r = -5.62314417475317895, theta[0].i = 1.1940692161124744;
    theta[1].r = -5.0893467972821611, theta[1].i = 3.58882439228376881;
    theta[2].r = -3.99337136365302569, theta[2].i = 6.00483209099604664;
    theta[3].r = -2.26978543095856366, theta[3].i = 8.46173881758693369;
    theta[4].r = .208756929753827868, theta[4].i = 10.9912615662209418;
    theta[5].r = 3.70327340957595652, theta[5].i = 13.6563731924991884;
    theta[6].r = 8.89777151877331107, theta[6].i = 16.6309842834712071;

    for (ip = 1; ip <= 7; ++ip) {
	i__1 = ip + 6;
	d_cnjg(&z__1, &theta[ip - 1]);
	theta[i__1].r = z__1.r, theta[i__1].i = z__1.i;
	i__1 = ip + 6;
	d_cnjg(&z__1, &alpha[ip - 1]);
	alpha[i__1].r = z__1.r, alpha[i__1].i = z__1.i;
    }

/* ---  Accumulation of the contribution of each pole ... */

    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = iz + j - 1;
	i__3 = j;
	wsp[i__2].r = y[i__3].r, wsp[i__2].i = y[i__3].i;
	i__2 = j;
	i__3 = j;
	z__1.r = alpha0 * y[i__3].r, z__1.i = alpha0 * y[i__3].i;
	y[i__2].r = z__1.r, y[i__2].i = z__1.i;
    }
    for (ip = 1; ip <= 14; ++ip) {
	i__1 = ip - 1;
	i__2 = ip - 1;
	z__1.r = alpha[i__2].r * .5, z__1.i = alpha[i__2].i * .5;
	alpha[i__1].r = z__1.r, alpha[i__1].i = z__1.i;
/* ---     Solve each fraction using Gaussian elimination with pivoting... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = iy + j - 1;
	    i__3 = iz + j - 1;
	    wsp[i__2].r = wsp[i__3].r, wsp[i__2].i = wsp[i__3].i;
/* Computing MIN */
	    i__3 = j + 1;
	    i__2 = min(i__3,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = ih + (j - 1) * *m + i__ - 1;
		d__1 = -(*t);
		i__4 = i__ + j * h_dim1;
		z__1.r = d__1 * h__[i__4].r, z__1.i = d__1 * h__[i__4].i;
		wsp[i__3].r = z__1.r, wsp[i__3].i = z__1.i;
	    }
	    i__2 = ih + (j - 1) * *m + j - 1;
	    i__3 = ih + (j - 1) * *m + j - 1;
	    i__4 = ip - 1;
	    z__1.r = wsp[i__3].r - theta[i__4].r, z__1.i = wsp[i__3].i - 
		    theta[i__4].i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	    i__2 = *m;
	    for (k = i__; k <= i__2; ++k) {
		i__3 = ih + (j - 1) * *m + k - 1;
		wsp[i__3].r = 0., wsp[i__3].i = 0.;
	    }
	}
	i__1 = *m - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* ---        Get pivot and exchange rows ... */
	    if (z_abs(&wsp[ih + (i__ - 1) * *m + i__ - 1]) < z_abs(&wsp[ih + (
		    i__ - 1) * *m + i__])) {
		i__2 = *m - i__ + 1;
		zswap_(&i__2, &wsp[ih + (i__ - 1) * *m + i__ - 1], m, &wsp[ih 
			+ (i__ - 1) * *m + i__], m);
		zswap_(&c__1, &wsp[iy + i__ - 1], &c__1, &wsp[iy + i__], &
			c__1);
	    }
/* ---        Forward eliminiation ... */
	    z_div(&z__1, &wsp[ih + (i__ - 1) * *m + i__], &wsp[ih + (i__ - 1) 
		    * *m + i__ - 1]);
	    tmpc.r = z__1.r, tmpc.i = z__1.i;
	    i__2 = *m - i__;
	    z__1.r = -tmpc.r, z__1.i = -tmpc.i;
	    zaxpy_(&i__2, &z__1, &wsp[ih + i__ * *m + i__ - 1], m, &wsp[ih + 
		    i__ * *m + i__], m);
	    i__2 = iy + i__;
	    i__3 = iy + i__;
	    i__4 = iy + i__ - 1;
	    z__2.r = tmpc.r * wsp[i__4].r - tmpc.i * wsp[i__4].i, z__2.i = 
		    tmpc.r * wsp[i__4].i + tmpc.i * wsp[i__4].r;
	    z__1.r = wsp[i__3].r - z__2.r, z__1.i = wsp[i__3].i - z__2.i;
	    wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
	}
/* ---     Backward substitution ... */
	for (i__ = *m; i__ >= 1; --i__) {
	    i__1 = iy + i__ - 1;
	    tmpc.r = wsp[i__1].r, tmpc.i = wsp[i__1].i;
	    i__1 = *m;
	    for (j = i__ + 1; j <= i__1; ++j) {
		i__2 = ih + (j - 1) * *m + i__ - 1;
		i__3 = iy + j - 1;
		z__2.r = wsp[i__2].r * wsp[i__3].r - wsp[i__2].i * wsp[i__3]
			.i, z__2.i = wsp[i__2].r * wsp[i__3].i + wsp[i__2].i *
			 wsp[i__3].r;
		z__1.r = tmpc.r - z__2.r, z__1.i = tmpc.i - z__2.i;
		tmpc.r = z__1.r, tmpc.i = z__1.i;
	    }
	    i__1 = iy + i__ - 1;
	    z_div(&z__1, &tmpc, &wsp[ih + (i__ - 1) * *m + i__ - 1]);
	    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
	}
/* ---     Accumulate the partial result in y ... */
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = j;
	    i__3 = j;
	    i__4 = ip - 1;
	    i__5 = iy + j - 1;
	    z__2.r = alpha[i__4].r * wsp[i__5].r - alpha[i__4].i * wsp[i__5]
		    .i, z__2.i = alpha[i__4].r * wsp[i__5].i + alpha[i__4].i *
		     wsp[i__5].r;
	    z__1.r = y[i__3].r + z__2.r, z__1.i = y[i__3].i + z__2.i;
	    y[i__2].r = z__1.r, y[i__2].i = z__1.i;
	}
    }
    return 0;
} /* znchbv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgexpv_(integer *n, integer *m, doublereal *t, 
	doublereal *v, doublereal *w, doublereal *tol, doublereal *anorm, 
	doublereal *wsp, integer *lwsp, integer *iwsp, integer *liwsp, S_fp 
	matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublereal hij, sgn, eps, hj1j, sqr1, beta;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal hump;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static integer ifree, lfree;
    static doublereal t_old__;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    static integer iexph;
    static doublereal t_new__;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer nexph;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal t_now__;
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    static doublereal vnorm;
    extern /* Subroutine */ int dgpadm_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, integer *), dnchbv_(integer *, doublereal *,
	     doublereal *, integer *, doublereal *, doublecomplex *);
    static integer nscale;
    static doublereal rndoff, t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___225 = { 0, 6, 0, 0, 0 };
    static cilist io___233 = { 0, 6, 0, 0, 0 };
    static cilist io___234 = { 0, 6, 0, 0, 0 };
    static cilist io___235 = { 0, 6, 0, 0, 0 };
    static cilist io___236 = { 0, 6, 0, 0, 0 };
    static cilist io___237 = { 0, 6, 0, 0, 0 };
    static cilist io___238 = { 0, 6, 0, 0, 0 };
    static cilist io___239 = { 0, 6, 0, 0, 0 };
    static cilist io___240 = { 0, 6, 0, 0, 0 };
    static cilist io___241 = { 0, 6, 0, 0, 0 };
    static cilist io___242 = { 0, 6, 0, 0, 0 };
    static cilist io___243 = { 0, 6, 0, 0, 0 };
    static cilist io___244 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  DGEXPV computes w = exp(t*A)*v - for a General matrix A. */

/*     It does not compute the matrix exponential in isolation but */
/*     instead, it computes directly the action of the exponential */
/*     operator on the operand vector. This way of doing so allows */
/*     for addressing large sparse problems. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     v(n)   : (input) given operand vector. */

/*     w(n)   : (output) computed approximation of exp(t*A)*v. */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+2)^2+4*(m+2)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+2 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in wsp and iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */
/*     wsp(9)  = hump, i.e., max||exp(sA)||, s in [0,t] (or [t,0] if t<0) */
/*     wsp(10) = ||w||/||v||, scaled norm of the solution w. */
/*     -----------------------------------------------------------------| */
/*     The `hump' is a measure of the conditioning of the problem. The */
/*     matrix exponential is well-conditioned if hump = 1, whereas it is */
/*     poorly-conditioned if hump >> 1. However the solution can still be */
/*     relatively fairly accurate even when the hump is large (the hump */
/*     is an upper bound), especially when the hump and the scaled norm */
/*     of w [this is also computed and returned in wsp(10)] are of the */
/*     same order of magnitude (further details in reference below). */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). The value 0 switches to the */
/*               uniform rational Chebyshev approximation of type (14,14) */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --w;
    --v;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 2;
    if (*lwsp < *n * (*m + 2) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 2) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DGEXPV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 2;
    mh = *m + 2;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    dcopy_(n, &v[1], &c__1, &w[1], &c__1);
    beta = dnrm2_(n, &w[1], &c__1);
    vnorm = beta;
    hump = beta;

/* ---  obtain the very first stepsize ... */

    sqr1 = sqrt(.1);
    xm = 1. / (doublereal) (*m);
    d__1 = (*m + 1) / 2.72;
    i__1 = *m + 1;
    p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002);
    d__1 = p1 / (beta * 4. * *anorm);
    t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);
    p1 = 1. / beta;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[iv + i__ - 1] = p1 * w[i__];
    }
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + i__ - 1] = 0.;
    }

/* ---  Arnoldi loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    hij = ddot_(n, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &c__1)
		    ;
	    d__1 = -hij;
	    daxpy_(n, &d__1, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    wsp[ih + (j - 1) * mh + i__ - 1] = hij;
	}
	hj1j = dnrm2_(n, &wsp[j1v], &c__1);
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___225);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	wsp[ih + (j - 1) * mh + j] = hj1j;
	d__1 = 1. / hj1j;
	dscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dnrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1 for the 2-corrected scheme ... */

L300:
    wsp[ih + *m * mh + *m + 1] = 1.;

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*V*exp(t_step*H)*e1 ... */

    ++nexph;
    mx = mbrkdwn + k1;
    if (TRUE_) {
/* ---     irreducible rational Pade approximation ... */
	d__1 = sgn * t_step__;
	dgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[
		1], &iexph, &ns, iflag);
	iexph = ifree + iexph - 1;
	nscale += ns;
    } else {
/* ---     uniform rational Chebyshev approximation ... */
	iexph = ifree;
	i__1 = mx;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    wsp[iexph + i__ - 1] = 0.;
	}
	wsp[iexph] = 1.;
	d__1 = sgn * t_step__;
	dnchbv_(&mx, &d__1, &wsp[ih], &mh, &wsp[iexph], (doublecomplex*)&wsp[
		ifree + mx]);
    }
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = (d__1 = wsp[iexph + *m], abs(d__1)) * beta;
	p2 = (d__1 = wsp[iexph + *m + 1], abs(d__1)) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m - 1);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___233);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___234);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___235);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___236);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___237);
	    do_lio(&c__9, &c__1, "Failure in DGEXPV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___238);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___239);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* ---  now update w = beta*V*exp(t_step*H)*e1 and the hump ... */

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 1;
    mx = mbrkdwn + max(i__1,i__2);
    dgemv_("n", n, &mx, &beta, &wsp[iv], n, &wsp[iexph], &c__1, &c_b65, &w[1],
	     &c__1, (ftnlen)1);
    beta = dnrm2_(n, &w[1], &c__1);
    hump = max(hump,beta);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___240);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___241);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___242);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___243);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___244);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 1000) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    wsp[1] = step_min__;
    wsp[2] = step_max__;
    wsp[3] = 0.;
    wsp[4] = 0.;
    wsp[5] = x_error__;
    wsp[6] = s_error__;
    wsp[7] = tbrkdwn;
    wsp[8] = sgn * t_now__;
    wsp[9] = hump / vnorm;
    wsp[10] = beta / vnorm;
    return 0;
} /* dgexpv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dsexpv_(integer *n, integer *m, doublereal *t, 
	doublereal *v, doublereal *w, doublereal *tol, doublereal *anorm, 
	doublereal *wsp, integer *lwsp, integer *iwsp, integer *liwsp, S_fp 
	matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublereal hjj, sgn, eps, hj1j, sqr1, beta;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal hump;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static integer ifree, lfree;
    static doublereal t_old__;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    static integer iexph;
    static doublereal t_new__;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer nexph;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal t_now__;
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    static doublereal vnorm;
    extern /* Subroutine */ int dgpadm_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, integer *), dnchbv_(integer *, doublereal *,
	     doublereal *, integer *, doublereal *, doublecomplex *);
    static integer nscale;
    static doublereal rndoff, t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___284 = { 0, 6, 0, 0, 0 };
    static cilist io___292 = { 0, 6, 0, 0, 0 };
    static cilist io___293 = { 0, 6, 0, 0, 0 };
    static cilist io___294 = { 0, 6, 0, 0, 0 };
    static cilist io___295 = { 0, 6, 0, 0, 0 };
    static cilist io___296 = { 0, 6, 0, 0, 0 };
    static cilist io___297 = { 0, 6, 0, 0, 0 };
    static cilist io___298 = { 0, 6, 0, 0, 0 };
    static cilist io___299 = { 0, 6, 0, 0, 0 };
    static cilist io___300 = { 0, 6, 0, 0, 0 };
    static cilist io___301 = { 0, 6, 0, 0, 0 };
    static cilist io___302 = { 0, 6, 0, 0, 0 };
    static cilist io___303 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  DSEXPV computes w = exp(t*A)*v - for a Symmetric matrix A. */

/*     It does not compute the matrix exponential in isolation but */
/*     instead, it computes directly the action of the exponential */
/*     operator on the operand vector. This way of doing so allows */
/*     for addressing large sparse problems. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     v(n)   : (input) given operand vector. */

/*     w(n)   : (output) computed approximation of exp(t*A)*v. */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+2)^2+4*(m+2)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+2 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, nbr of Tridiagonal matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, nbr of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */
/*     wsp(9)  = hump, i.e., max||exp(sA)||, s in [0,t] (or [t,0] if t<0) */
/*     wsp(10) = ||w||/||v||, scaled norm of the solution w. */
/*     -----------------------------------------------------------------| */
/*     The `hump' is a measure of the conditioning of the problem. The */
/*     matrix exponential is well-conditioned if hump = 1, whereas it is */
/*     poorly-conditioned if hump >> 1. However the solution can still be */
/*     relatively fairly accurate even when the hump is large (the hump */
/*     is an upper bound), especially when the hump and the scaled norm */
/*     of w [this is also computed and returned in wsp(10)] are of the */
/*     same order of magnitude (further details in reference below). */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). The value 0 switches to the */
/*               uniform rational Chebyshev approximation of type (14,14) */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --w;
    --v;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 2;
    if (*lwsp < *n * (*m + 2) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 2) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DSEXPV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 2;
    mh = *m + 2;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    dcopy_(n, &v[1], &c__1, &w[1], &c__1);
    beta = dnrm2_(n, &w[1], &c__1);
    vnorm = beta;
    hump = beta;

/* ---  obtain the very first stepsize ... */

    sqr1 = sqrt(.1);
    xm = 1. / (doublereal) (*m);
    d__1 = (*m + 1) / 2.72;
    i__1 = *m + 1;
    p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002);
    d__1 = p1 / (beta * 4. * *anorm);
    t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);
    p1 = 1. / beta;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[iv + i__ - 1] = p1 * w[i__];
    }
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + i__ - 1] = 0.;
    }

/* ---  Lanczos loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	if (j > 1) {
	    d__1 = -wsp[ih + (j - 1) * mh + j - 2];
	    daxpy_(n, &d__1, &wsp[j1v - (*n << 1)], &c__1, &wsp[j1v], &c__1);
	}
	hjj = ddot_(n, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	d__1 = -hjj;
	daxpy_(n, &d__1, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hj1j = dnrm2_(n, &wsp[j1v], &c__1);
	wsp[ih + (j - 1) * (mh + 1)] = hjj;
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___284);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	wsp[ih + (j - 1) * mh + j] = hj1j;
	wsp[ih + j * mh + j - 1] = hj1j;
	d__1 = 1. / hj1j;
	dscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dnrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1 for the 2-corrected scheme ... */

L300:
    wsp[ih + *m * mh + *m - 1] = 0.;
    wsp[ih + *m * mh + *m + 1] = 1.;

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*V*exp(t_step*H)*e1 ... */

    ++nexph;
    mx = mbrkdwn + k1;
    if (TRUE_) {
/* ---     irreducible rational Pade approximation ... */
	d__1 = sgn * t_step__;
	dgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[
		1], &iexph, &ns, iflag);
	iexph = ifree + iexph - 1;
	nscale += ns;
    } else {
/* ---     uniform rational Chebyshev approximation ... */
	iexph = ifree;
	i__1 = mx;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    wsp[iexph + i__ - 1] = 0.;
	}
	wsp[iexph] = 1.;
	d__1 = sgn * t_step__;
	dnchbv_(&mx, &d__1, &wsp[ih], &mh, &wsp[iexph], (doublecomplex*)&wsp[
		ifree + mx]);
    }
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = (d__1 = wsp[iexph + *m], abs(d__1)) * beta;
	p2 = (d__1 = wsp[iexph + *m + 1], abs(d__1)) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m - 1);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___292);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___293);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___294);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___295);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___296);
	    do_lio(&c__9, &c__1, "Failure in DSEXPV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___297);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___298);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* ---  now update w = beta*V*exp(t_step*H)*e1 and the hump ... */

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 1;
    mx = mbrkdwn + max(i__1,i__2);
    dgemv_("n", n, &mx, &beta, &wsp[iv], n, &wsp[iexph], &c__1, &c_b65, &w[1],
	     &c__1, (ftnlen)1);
    beta = dnrm2_(n, &w[1], &c__1);
    hump = max(hump,beta);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___299);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___300);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___301);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___302);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___303);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    wsp[1] = step_min__;
    wsp[2] = step_max__;
    wsp[3] = 0.;
    wsp[4] = 0.;
    wsp[5] = x_error__;
    wsp[6] = s_error__;
    wsp[7] = tbrkdwn;
    wsp[8] = sgn * t_now__;
    wsp[9] = hump / vnorm;
    wsp[10] = beta / vnorm;
    return 0;
} /* dsexpv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zgexpv_(integer *n, integer *m, doublereal *t, 
	doublecomplex *v, doublecomplex *w, doublereal *tol, doublereal *
	anorm, doublecomplex *wsp, integer *lwsp, integer *iwsp, integer *
	liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;
    complex q__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double z_abs(doublecomplex *);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublecomplex hij;
    static doublereal sgn, eps, hj1j, sqr1, beta, hump;
    static integer ifree, lfree;
    static doublereal t_old__;
    static integer iexph;
    static doublereal t_new__;
    static integer nexph;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublereal t_now__;
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen);
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    static doublereal vnorm;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    static integer nscale;
    static doublereal rndoff;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *), zgpadm_(integer *, integer *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, integer *, integer *, integer *, integer *), znchbv_(
	    integer *, doublereal *, doublecomplex *, integer *, 
	    doublecomplex *, doublecomplex *);
    static doublereal t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___343 = { 0, 6, 0, 0, 0 };
    static cilist io___351 = { 0, 6, 0, 0, 0 };
    static cilist io___352 = { 0, 6, 0, 0, 0 };
    static cilist io___353 = { 0, 6, 0, 0, 0 };
    static cilist io___354 = { 0, 6, 0, 0, 0 };
    static cilist io___355 = { 0, 6, 0, 0, 0 };
    static cilist io___356 = { 0, 6, 0, 0, 0 };
    static cilist io___357 = { 0, 6, 0, 0, 0 };
    static cilist io___358 = { 0, 6, 0, 0, 0 };
    static cilist io___359 = { 0, 6, 0, 0, 0 };
    static cilist io___360 = { 0, 6, 0, 0, 0 };
    static cilist io___361 = { 0, 6, 0, 0, 0 };
    static cilist io___362 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  ZGEXPV computes w = exp(t*A)*v */
/*     for a Zomplex (i.e., complex double precision) matrix A */

/*     It does not compute the matrix exponential in isolation but */
/*     instead, it computes directly the action of the exponential */
/*     operator on the operand vector. This way of doing so allows */
/*     for addressing large sparse problems. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     v(n)   : (input) given operand vector. */

/*     w(n)   : (output) computed approximation of exp(t*A)*v. */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+2)^2+4*(m+2)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+2 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        complex*16 x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = x_round, maximum among all roundoff errors (lower bound) */
/*     wsp(4)  = s_round, sum of roundoff errors (lower bound) */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */
/*     wsp(9)  = hump, i.e., max||exp(sA)||, s in [0,t] (or [t,0] if t<0) */
/*     wsp(10) = ||w||/||v||, scaled norm of the solution w. */
/*     -----------------------------------------------------------------| */
/*     The `hump' is a measure of the conditioning of the problem. The */
/*     matrix exponential is well-conditioned if hump = 1, whereas it is */
/*     poorly-conditioned if hump >> 1. However the solution can still be */
/*     relatively fairly accurate even when the hump is large (the hump */
/*     is an upper bound), especially when the hump and the scaled norm */
/*     of w [this is also computed and returned in wsp(10)] are of the */
/*     same order of magnitude (further details in reference below). */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). The value 0 switches to the */
/*               uniform rational Chebyshev approximation of type (14,14) */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */

    /* Parameter adjustments */
    --w;
    --v;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 2;
    if (*lwsp < *n * (*m + 2) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 2) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of ZGEXPV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 2;
    mh = *m + 2;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    zcopy_(n, &v[1], &c__1, &w[1], &c__1);
    beta = dznrm2_(n, &w[1], &c__1);
    vnorm = beta;
    hump = beta;

/* ---  obtain the very first stepsize ... */

    sqr1 = sqrt(.1);
    xm = 1. / (doublereal) (*m);
    d__1 = (*m + 1) / 2.72;
    i__1 = *m + 1;
    p2 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002);
    d__1 = p2 / (beta * 4. * *anorm);
    t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);
    p1 = 1. / beta;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = iv + i__ - 1;
	i__3 = i__;
	z__1.r = p1 * w[i__3].r, z__1.i = p1 * w[i__3].i;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + i__ - 1;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }

/* ---  Arnoldi loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    zdotc_(&z__1, n, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    hij.r = z__1.r, hij.i = z__1.i;
	    z__1.r = -hij.r, z__1.i = -hij.i;
	    zaxpy_(n, &z__1, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    i__3 = ih + (j - 1) * mh + i__ - 1;
	    wsp[i__3].r = hij.r, wsp[i__3].i = hij.i;
	}
	hj1j = dznrm2_(n, &wsp[j1v], &c__1);
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___343);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	i__2 = ih + (j - 1) * mh + j;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	d__1 = 1. / hj1j;
	zdscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dznrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1 for the 2-corrected scheme ... */

L300:
    i__1 = ih + *m * mh + *m + 1;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*V*exp(t_step*H)*e1 ... */

    ++nexph;
    mx = mbrkdwn + k1;
    if (TRUE_) {
/* ---     irreducible rational Pade approximation ... */
	d__1 = sgn * t_step__;
	zgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[
		1], &iexph, &ns, iflag);
	iexph = ifree + iexph - 1;
	nscale += ns;
    } else {
/* ---     uniform rational Chebyshev approximation ... */
	iexph = ifree;
	i__1 = mx;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = iexph + i__ - 1;
	    wsp[i__2].r = 0., wsp[i__2].i = 0.;
	}
	i__1 = iexph;
	wsp[i__1].r = 1., wsp[i__1].i = 0.;
	d__1 = sgn * t_step__;
	znchbv_(&mx, &d__1, &wsp[ih], &mh, &wsp[iexph], &wsp[ifree + mx]);
    }
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = z_abs(&wsp[iexph + *m]) * beta;
	p2 = z_abs(&wsp[iexph + *m + 1]) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m - 1);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___351);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___352);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___353);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___354);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___355);
	    do_lio(&c__9, &c__1, "Failure in ZGEXPV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___356);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___357);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* ---  now update w = beta*V*exp(t_step*H)*e1 and the hump ... */

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 1;
    mx = mbrkdwn + max(i__1,i__2);
    q__1.r = beta, q__1.i = 0.f;
    hij.r = q__1.r, hij.i = q__1.i;
    zgemv_("n", n, &mx, &hij, &wsp[iv], n, &wsp[iexph], &c__1, &c_b172, &w[1],
	     &c__1, (ftnlen)1);
    beta = dznrm2_(n, &w[1], &c__1);
    hump = max(hump,beta);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___358);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___359);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___360);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___361);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___362);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    q__1.r = step_min__, q__1.i = 0.f;
    wsp[1].r = q__1.r, wsp[1].i = q__1.i;
    q__1.r = step_max__, q__1.i = 0.f;
    wsp[2].r = q__1.r, wsp[2].i = q__1.i;
    wsp[3].r = 0.f, wsp[3].i = 0.f;
    wsp[4].r = 0.f, wsp[4].i = 0.f;
    q__1.r = x_error__, q__1.i = 0.f;
    wsp[5].r = q__1.r, wsp[5].i = q__1.i;
    q__1.r = s_error__, q__1.i = 0.f;
    wsp[6].r = q__1.r, wsp[6].i = q__1.i;
    q__1.r = tbrkdwn, q__1.i = 0.f;
    wsp[7].r = q__1.r, wsp[7].i = q__1.i;
    d__1 = sgn * t_now__;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[8].r = q__1.r, wsp[8].i = q__1.i;
    d__1 = hump / vnorm;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[9].r = q__1.r, wsp[9].i = q__1.i;
    d__1 = beta / vnorm;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[10].r = q__1.r, wsp[10].i = q__1.i;
    return 0;
} /* zgexpv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zhexpv_(integer *n, integer *m, doublereal *t, 
	doublecomplex *v, doublecomplex *w, doublereal *tol, doublereal *
	anorm, doublecomplex *wsp, integer *lwsp, integer *iwsp, integer *
	liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;
    complex q__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double z_abs(doublecomplex *);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublecomplex hjj;
    static doublereal sgn, eps, hj1j, sqr1, beta, hump;
    static integer ifree, lfree;
    static doublereal t_old__;
    static integer iexph;
    static doublereal t_new__;
    static integer nexph;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublereal t_now__;
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen);
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    static doublereal vnorm;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    static integer nscale;
    static doublereal rndoff;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *), zgpadm_(integer *, integer *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, integer *, integer *, integer *, integer *), znchbv_(
	    integer *, doublereal *, doublecomplex *, integer *, 
	    doublecomplex *, doublecomplex *);
    static doublereal t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___402 = { 0, 6, 0, 0, 0 };
    static cilist io___410 = { 0, 6, 0, 0, 0 };
    static cilist io___411 = { 0, 6, 0, 0, 0 };
    static cilist io___412 = { 0, 6, 0, 0, 0 };
    static cilist io___413 = { 0, 6, 0, 0, 0 };
    static cilist io___414 = { 0, 6, 0, 0, 0 };
    static cilist io___415 = { 0, 6, 0, 0, 0 };
    static cilist io___416 = { 0, 6, 0, 0, 0 };
    static cilist io___417 = { 0, 6, 0, 0, 0 };
    static cilist io___418 = { 0, 6, 0, 0, 0 };
    static cilist io___419 = { 0, 6, 0, 0, 0 };
    static cilist io___420 = { 0, 6, 0, 0, 0 };
    static cilist io___421 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  ZHEXPV computes w = exp(t*A)*v for a Hermitian matrix A. */

/*     It does not compute the matrix exponential in isolation but */
/*     instead, it computes directly the action of the exponential */
/*     operator on the operand vector. This way of doing so allows */
/*     for addressing large sparse problems. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     v(n)   : (input) given operand vector. */

/*     w(n)   : (output) computed approximation of exp(t*A)*v. */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+2)^2+4*(m+2)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+2 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        complex*16 x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */
/*     wsp(9)  = hump, i.e., max||exp(sA)||, s in [0,t] (or [t,0] if t<0) */
/*     wsp(10) = ||w||/||v||, scaled norm of the solution w. */
/*     -----------------------------------------------------------------| */
/*     The `hump' is a measure of the conditioning of the problem. The */
/*     matrix exponential is well-conditioned if hump = 1, whereas it is */
/*     poorly-conditioned if hump >> 1. However the solution can still be */
/*     relatively fairly accurate even when the hump is large (the hump */
/*     is an upper bound), especially when the hump and the scaled norm */
/*     of w [this is also computed and returned in wsp(10)] are of the */
/*     same order of magnitude (further details in reference below). */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). The value 0 switches to the */
/*               uniform rational Chebyshev approximation of type (14,14) */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */


/* ---  check restrictions on input parameters ... */

    /* Parameter adjustments */
    --w;
    --v;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 2;
    if (*lwsp < *n * (*m + 2) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 2) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DHEXPV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 2;
    mh = *m + 2;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    zcopy_(n, &v[1], &c__1, &w[1], &c__1);
    beta = dznrm2_(n, &w[1], &c__1);
    vnorm = beta;
    hump = beta;

/* ---  obtain the very first stepsize ... */

    sqr1 = sqrt(.1);
    xm = 1. / (doublereal) (*m);
    d__1 = (*m + 1) / 2.72;
    i__1 = *m + 1;
    p2 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002);
    d__1 = p2 / (beta * 4. * *anorm);
    t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);
    beta = dznrm2_(n, &w[1], &c__1);
    p1 = 1. / beta;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = iv + i__ - 1;
	i__3 = i__;
	z__1.r = p1 * w[i__3].r, z__1.i = p1 * w[i__3].i;
	wsp[i__2].r = z__1.r, wsp[i__2].i = z__1.i;
    }
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + i__ - 1;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }

/* ---  Lanczos loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	if (j > 1) {
	    i__2 = ih + (j - 1) * mh + j - 2;
	    z__1.r = -wsp[i__2].r, z__1.i = -wsp[i__2].i;
	    zaxpy_(n, &z__1, &wsp[j1v - (*n << 1)], &c__1, &wsp[j1v], &c__1);
	}
	zdotc_(&z__1, n, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hjj.r = z__1.r, hjj.i = z__1.i;
	z__1.r = -hjj.r, z__1.i = -hjj.i;
	zaxpy_(n, &z__1, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hj1j = dznrm2_(n, &wsp[j1v], &c__1);
	i__2 = ih + (j - 1) * (mh + 1);
	wsp[i__2].r = hjj.r, wsp[i__2].i = hjj.i;
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___402);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	i__2 = ih + (j - 1) * mh + j;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	i__2 = ih + j * mh + j - 1;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	d__1 = 1. / hj1j;
	zdscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dznrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1 for the 2-corrected scheme ... */

L300:
    i__1 = ih + *m * mh + *m - 1;
    wsp[i__1].r = 0., wsp[i__1].i = 0.;
    i__1 = ih + *m * mh + *m + 1;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*V*exp(t_step*H)*e1 ... */

    ++nexph;
    mx = mbrkdwn + k1;
    if (TRUE_) {
/* ---     irreducible rational Pade approximation ... */
	d__1 = sgn * t_step__;
	zgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[
		1], &iexph, &ns, iflag);
	iexph = ifree + iexph - 1;
	nscale += ns;
    } else {
/* ---     uniform rational Chebyshev approximation ... */
	iexph = ifree;
	i__1 = mx;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = iexph + i__ - 1;
	    wsp[i__2].r = 0., wsp[i__2].i = 0.;
	}
	i__1 = iexph;
	wsp[i__1].r = 1., wsp[i__1].i = 0.;
	d__1 = sgn * t_step__;
	znchbv_(&mx, &d__1, &wsp[ih], &mh, &wsp[iexph], &wsp[ifree + mx]);
    }
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = z_abs(&wsp[iexph + *m]) * beta;
	p2 = z_abs(&wsp[iexph + *m + 1]) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m - 1);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___410);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___411);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___412);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___413);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___414);
	    do_lio(&c__9, &c__1, "Failure in ZHEXPV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___415);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___416);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* ---  now update w = beta*V*exp(t_step*H)*e1 and the hump ... */

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 1;
    mx = mbrkdwn + max(i__1,i__2);
    q__1.r = beta, q__1.i = 0.f;
    hjj.r = q__1.r, hjj.i = q__1.i;
    zgemv_("n", n, &mx, &hjj, &wsp[iv], n, &wsp[iexph], &c__1, &c_b172, &w[1],
	     &c__1, (ftnlen)1);
    beta = dznrm2_(n, &w[1], &c__1);
    hump = max(hump,beta);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___417);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___418);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___419);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___420);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___421);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    q__1.r = step_min__, q__1.i = 0.f;
    wsp[1].r = q__1.r, wsp[1].i = q__1.i;
    q__1.r = step_max__, q__1.i = 0.f;
    wsp[2].r = q__1.r, wsp[2].i = q__1.i;
    wsp[3].r = 0.f, wsp[3].i = 0.f;
    wsp[4].r = 0.f, wsp[4].i = 0.f;
    q__1.r = x_error__, q__1.i = 0.f;
    wsp[5].r = q__1.r, wsp[5].i = q__1.i;
    q__1.r = s_error__, q__1.i = 0.f;
    wsp[6].r = q__1.r, wsp[6].i = q__1.i;
    q__1.r = tbrkdwn, q__1.i = 0.f;
    wsp[7].r = q__1.r, wsp[7].i = q__1.i;
    d__1 = sgn * t_now__;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[8].r = q__1.r, wsp[8].i = q__1.i;
    d__1 = hump / vnorm;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[9].r = q__1.r, wsp[9].i = q__1.i;
    d__1 = beta / vnorm;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[10].r = q__1.r, wsp[10].i = q__1.i;
    return 0;
} /* zhexpv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgphiv_(integer *n, integer *m, doublereal *t, 
	doublereal *u, doublereal *v, doublereal *w, doublereal *tol, 
	doublereal *anorm, doublereal *wsp, integer *lwsp, integer *iwsp, 
	integer *liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublereal hij, sgn, eps, hj1j, sqr1, beta;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *), dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static integer ifree, lfree, iphih;
    static doublereal t_old__;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    static integer iexph;
    static doublereal t_new__;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer nexph;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal t_now__;
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    extern /* Subroutine */ int dgpadm_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, integer *);
    static integer nscale;
    static doublereal rndoff, t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___459 = { 0, 6, 0, 0, 0 };
    static cilist io___468 = { 0, 6, 0, 0, 0 };
    static cilist io___469 = { 0, 6, 0, 0, 0 };
    static cilist io___470 = { 0, 6, 0, 0, 0 };
    static cilist io___471 = { 0, 6, 0, 0, 0 };
    static cilist io___472 = { 0, 6, 0, 0, 0 };
    static cilist io___473 = { 0, 6, 0, 0, 0 };
    static cilist io___474 = { 0, 6, 0, 0, 0 };
    static cilist io___475 = { 0, 6, 0, 0, 0 };
    static cilist io___476 = { 0, 6, 0, 0, 0 };
    static cilist io___477 = { 0, 6, 0, 0, 0 };
    static cilist io___478 = { 0, 6, 0, 0, 0 };
    static cilist io___479 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  DGPHIV computes w = exp(t*A)v + t*phi(tA)u which is the solution */
/*     of the nonhomogeneous linear ODE problem w' = Aw + u, w(0) = v. */
/*     phi(z) = (exp(z)-1)/z and A is a General matrix. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     u(n)   : (input) operand vector with respect to the phi function */
/*              (forcing term of the ODE problem). */

/*     v(n)   : (input) operand vector with respect to the exp function */
/*              (initial condition of the ODE problem). */

/*     w(n)   : (output) computed approximation of exp(t*A)v + t*phi(tA)u */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+3)^2+4*(m+3)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+3 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --w;
    --v;
    --u;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 3;
    if (*lwsp < *n * (*m + 3) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 3) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DGPHIV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 3;
    mh = *m + 3;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */

/* ---  step-by-step integration ... */

    sgn = d_sign(&c_b3, t);
    sqr1 = sqrt(.1);
    dcopy_(n, &v[1], &c__1, &w[1], &c__1);
L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nmult;
    (*matvec)(&w[1], &wsp[iv]);
    daxpy_(n, &c_b3, &u[1], &c__1, &wsp[iv], &c__1);
    beta = dnrm2_(n, &wsp[iv], &c__1);
    if (beta == 0.) {
	goto L500;
    }
    d__1 = 1. / beta;
    dscal_(n, &d__1, &wsp[iv], &c__1);
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + i__ - 1] = 0.;
    }
    if (nstep == 0) {
/* ---     obtain the very first stepsize ... */
	xm = 1. / (doublereal) (*m);
	d__1 = (*m + 1) / 2.72;
	i__1 = *m + 1;
	p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002)
		;
	d__1 = p1 / (beta * 4. * *anorm);
	t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_new__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_new__ / p1 + .55;
	t_new__ = d_int(&d__1) * p1;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);

/* ---  Arnoldi loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    hij = ddot_(n, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &c__1)
		    ;
	    d__1 = -hij;
	    daxpy_(n, &d__1, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    wsp[ih + (j - 1) * mh + i__ - 1] = hij;
	}
	hj1j = dnrm2_(n, &wsp[j1v], &c__1);
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___459);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	wsp[ih + (j - 1) * mh + j] = hj1j;
	d__1 = 1. / hj1j;
	dscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dnrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1's for the 3-extended scheme ... */

L300:
    wsp[ih + mh * mbrkdwn] = 1.;
    wsp[ih + (*m - 1) * mh + *m] = 0.;
    i__1 = k1 - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + (*m + i__) * mh + *m + i__ - 1] = 1.;
    }

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*t_step*V*phi(t_step*H)*e1 + w */

    ++nexph;
/* ---  irreducible rational Pade approximation ... */
    mx = mbrkdwn + max(1,k1);
    d__1 = sgn * t_step__;
    dgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[1], &
	    iexph, &ns, iflag);
    iexph = ifree + iexph - 1;
    iphih = iexph + mbrkdwn * mx;
    nscale += ns;
    wsp[iphih + mbrkdwn] = hj1j * wsp[iphih + mx + mbrkdwn - 1];
    wsp[iphih + mbrkdwn + 1] = hj1j * wsp[iphih + (mx << 1) + mbrkdwn - 1];
/* L402: */
/* ---  error estimate ... */
    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = (d__1 = wsp[iphih + *m], abs(d__1)) * beta;
	p2 = (d__1 = wsp[iphih + *m + 1], abs(d__1)) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m + 1);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m + 1);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m);
	}
    }
/* ---  reject the step-size if the error is not acceptable ... */
    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___468);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___469);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___470);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___471);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___472);
	    do_lio(&c__9, &c__1, "Failure in DGPHIV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___473);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___474);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 2;
    mx = mbrkdwn + max(i__1,i__2);
    dgemv_("n", n, &mx, &beta, &wsp[iv], n, &wsp[iphih], &c__1, &c_b3, &w[1], 
	    &c__1, (ftnlen)1);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___475);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___476);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___477);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___478);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___479);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 1000) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    wsp[1] = step_min__;
    wsp[2] = step_max__;
    wsp[3] = 0.;
    wsp[4] = 0.;
    wsp[5] = x_error__;
    wsp[6] = s_error__;
    wsp[7] = tbrkdwn;
    wsp[8] = sgn * t_now__;
    return 0;
} /* dgphiv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dsphiv_(integer *n, integer *m, doublereal *t, 
	doublereal *u, doublereal *v, doublereal *w, doublereal *tol, 
	doublereal *anorm, doublereal *wsp, integer *lwsp, integer *iwsp, 
	integer *liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublereal hjj, sgn, eps, hj1j, sqr1, beta;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *), dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static integer ifree, lfree, iphih;
    static doublereal t_old__;
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, ftnlen);
    static integer iexph;
    static doublereal t_new__;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer nexph;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static doublereal t_now__;
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    extern /* Subroutine */ int dgpadm_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, integer *);
    static integer nscale;
    static doublereal rndoff, t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___517 = { 0, 6, 0, 0, 0 };
    static cilist io___526 = { 0, 6, 0, 0, 0 };
    static cilist io___527 = { 0, 6, 0, 0, 0 };
    static cilist io___528 = { 0, 6, 0, 0, 0 };
    static cilist io___529 = { 0, 6, 0, 0, 0 };
    static cilist io___530 = { 0, 6, 0, 0, 0 };
    static cilist io___531 = { 0, 6, 0, 0, 0 };
    static cilist io___532 = { 0, 6, 0, 0, 0 };
    static cilist io___533 = { 0, 6, 0, 0, 0 };
    static cilist io___534 = { 0, 6, 0, 0, 0 };
    static cilist io___535 = { 0, 6, 0, 0, 0 };
    static cilist io___536 = { 0, 6, 0, 0, 0 };
    static cilist io___537 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  DSPHIV computes w = exp(t*A)v + t*phi(tA)u which is the solution */
/*     of the nonhomogeneous linear ODE problem w' = Aw + u, w(0) = v. */
/*     phi(z) = (exp(z)-1)/z and A is a Symmetric matrix. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     u(n)   : (input) operand vector with respect to the phi function */
/*              (forcing term of the ODE problem). */

/*     v(n)   : (input) operand vector with respect to the exp function */
/*              (initial condition of the ODE problem). */

/*     w(n)   : (output) computed approximation of exp(t*A)v + t*phi(tA)u */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+3)^2+4*(m+3)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+3 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */

/* ---  check restrictions on input parameters ... */
    /* Parameter adjustments */
    --w;
    --v;
    --u;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 3;
    if (*lwsp < *n * (*m + 3) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 3) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of DSPHIV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 3;
    mh = *m + 3;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */

/* ---  step-by-step integration ... */

    sgn = d_sign(&c_b3, t);
    sqr1 = sqrt(.1);
    dcopy_(n, &v[1], &c__1, &w[1], &c__1);
L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nmult;
    (*matvec)(&w[1], &wsp[iv]);
    daxpy_(n, &c_b3, &u[1], &c__1, &wsp[iv], &c__1);
    beta = dnrm2_(n, &wsp[iv], &c__1);
    if (beta == 0.) {
	goto L500;
    }
    d__1 = 1. / beta;
    dscal_(n, &d__1, &wsp[iv], &c__1);
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + i__ - 1] = 0.;
    }
    if (nstep == 0) {
/* ---     obtain the very first stepsize ... */
	xm = 1. / (doublereal) (*m);
	d__1 = (*m + 1) / 2.72;
	i__1 = *m + 1;
	p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002)
		;
	d__1 = p1 / (beta * 4. * *anorm);
	t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_new__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_new__ / p1 + .55;
	t_new__ = d_int(&d__1) * p1;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);

/* ---  Lanczos loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	if (j > 1) {
	    d__1 = -wsp[ih + (j - 1) * mh + j - 2];
	    daxpy_(n, &d__1, &wsp[j1v - (*n << 1)], &c__1, &wsp[j1v], &c__1);
	}
	hjj = ddot_(n, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	d__1 = -hjj;
	daxpy_(n, &d__1, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hj1j = dnrm2_(n, &wsp[j1v], &c__1);
	wsp[ih + (j - 1) * (mh + 1)] = hjj;
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___517);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	wsp[ih + (j - 1) * mh + j] = hj1j;
	wsp[ih + j * mh + j - 1] = hj1j;
	d__1 = 1. / hj1j;
	dscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dnrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1's for the 3-extended scheme ... */

L300:
    wsp[ih + mh * mbrkdwn] = 1.;
    wsp[ih + *m * mh + *m - 1] = 0.;
    wsp[ih + (*m - 1) * mh + *m] = 0.;
    i__1 = k1 - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	wsp[ih + (*m + i__) * mh + *m + i__ - 1] = 1.;
    }

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*t_step*V*phi(t_step*H)*e1 + w */

    ++nexph;
    mx = mbrkdwn + max(1,k1);
/* ---  irreducible rational Pade approximation ... */
    d__1 = sgn * t_step__;
    dgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[1], &
	    iexph, &ns, iflag);
    iexph = ifree + iexph - 1;
    iphih = iexph + mbrkdwn * mx;
    nscale += ns;
    wsp[iphih + mbrkdwn] = hj1j * wsp[iphih + mx + mbrkdwn - 1];
    wsp[iphih + mbrkdwn + 1] = hj1j * wsp[iphih + (mx << 1) + mbrkdwn - 1];
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = (d__1 = wsp[iphih + *m], abs(d__1)) * beta;
	p2 = (d__1 = wsp[iphih + *m + 1], abs(d__1)) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m + 1);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m + 1);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___526);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___527);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___528);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___529);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___530);
	    do_lio(&c__9, &c__1, "Failure in DSPHIV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___531);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___532);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 2;
    mx = mbrkdwn + max(i__1,i__2);
    dgemv_("n", n, &mx, &beta, &wsp[iv], n, &wsp[iphih], &c__1, &c_b3, &w[1], 
	    &c__1, (ftnlen)1);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___533);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___534);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___535);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___536);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___537);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    wsp[1] = step_min__;
    wsp[2] = step_max__;
    wsp[3] = 0.;
    wsp[4] = 0.;
    wsp[5] = x_error__;
    wsp[6] = s_error__;
    wsp[7] = tbrkdwn;
    wsp[8] = sgn * t_now__;
    return 0;
} /* dsphiv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zgphiv_(integer *n, integer *m, doublereal *t, 
	doublecomplex *u, doublecomplex *v, doublecomplex *w, doublereal *tol,
	 doublereal *anorm, doublecomplex *wsp, integer *lwsp, integer *iwsp, 
	integer *liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;
    complex q__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double z_abs(doublecomplex *);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublecomplex hij;
    static doublereal sgn, eps, hj1j, sqr1, beta;
    static integer ifree, lfree, iphih;
    static doublereal t_old__;
    static integer iexph;
    static doublereal t_new__;
    static integer nexph;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublereal t_now__;
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen);
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    static integer nscale;
    static doublereal rndoff;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *), zgpadm_(integer *, integer *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, integer *, integer *, integer *, integer *);
    static doublereal t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___575 = { 0, 6, 0, 0, 0 };
    static cilist io___584 = { 0, 6, 0, 0, 0 };
    static cilist io___585 = { 0, 6, 0, 0, 0 };
    static cilist io___586 = { 0, 6, 0, 0, 0 };
    static cilist io___587 = { 0, 6, 0, 0, 0 };
    static cilist io___588 = { 0, 6, 0, 0, 0 };
    static cilist io___589 = { 0, 6, 0, 0, 0 };
    static cilist io___590 = { 0, 6, 0, 0, 0 };
    static cilist io___591 = { 0, 6, 0, 0, 0 };
    static cilist io___592 = { 0, 6, 0, 0, 0 };
    static cilist io___593 = { 0, 6, 0, 0, 0 };
    static cilist io___594 = { 0, 6, 0, 0, 0 };
    static cilist io___595 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  ZGPHIV computes w = exp(t*A)v + t*phi(tA)u which is the solution */
/*     of the nonhomogeneous linear ODE problem w' = Aw + u, w(0) = v. */
/*     phi(z) = (exp(z)-1)/z and A is a Zomplex (i.e., complex double */
/*     precision matrix). */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     u(n)   : (input) operand vector with respect to the phi function */
/*              (forcing term of the ODE problem). */

/*     v(n)   : (input) operand vector with respect to the exp function */
/*              (initial condition of the ODE problem). */

/*     w(n)   : (output) computed approximation of exp(t*A)v + t*phi(tA)u */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+3)^2+4*(m+3)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+3 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */


/* ---  check restrictions on input parameters ... */

    /* Parameter adjustments */
    --w;
    --v;
    --u;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 3;
    if (*lwsp < *n * (*m + 3) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 3) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of ZGPHIV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 3;
    mh = *m + 3;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    sqr1 = sqrt(.1);
    zcopy_(n, &v[1], &c__1, &w[1], &c__1);

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nmult;
    (*matvec)(&w[1], &wsp[iv]);
    zaxpy_(n, &c_b173, &u[1], &c__1, &wsp[iv], &c__1);
    beta = dznrm2_(n, &wsp[iv], &c__1);
    if (beta == 0.) {
	goto L500;
    }
    d__1 = 1. / beta;
    zdscal_(n, &d__1, &wsp[iv], &c__1);
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + i__ - 1;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }
    if (nstep == 0) {
/* ---     obtain the very first stepsize ... */
	xm = 1. / (doublereal) (*m);
	d__1 = (*m + 1) / 2.72;
	i__1 = *m + 1;
	p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002)
		;
	d__1 = p1 / (beta * 4. * *anorm);
	t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_new__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_new__ / p1 + .55;
	t_new__ = d_int(&d__1) * p1;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);

/* ---  Arnoldi loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    zdotc_(&z__1, n, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    hij.r = z__1.r, hij.i = z__1.i;
	    z__1.r = -hij.r, z__1.i = -hij.i;
	    zaxpy_(n, &z__1, &wsp[iv + (i__ - 1) * *n], &c__1, &wsp[j1v], &
		    c__1);
	    i__3 = ih + (j - 1) * mh + i__ - 1;
	    wsp[i__3].r = hij.r, wsp[i__3].i = hij.i;
	}
	hj1j = dznrm2_(n, &wsp[j1v], &c__1);
/* ---     if `happy breakdown' go straightforward at the end ... */
	if (hj1j <= break_tol__) {
	    s_wsle(&io___575);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	i__2 = ih + (j - 1) * mh + j;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	d__1 = 1. / hj1j;
	zdscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dznrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1's for the 3-extended scheme ... */

L300:
    i__1 = ih + mh * mbrkdwn;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;
    i__1 = ih + (*m - 1) * mh + *m;
    wsp[i__1].r = 0., wsp[i__1].i = 0.;
    i__1 = k1 - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + (*m + i__) * mh + *m + i__ - 1;
	wsp[i__2].r = 1., wsp[i__2].i = 0.;
    }

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*t_step*V*phi(t_step*H)*e1 + w */

    ++nexph;
    mx = mbrkdwn + max(1,k1);
/* ---  irreducible rational Pade approximation ... */
    d__1 = sgn * t_step__;
    zgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[1], &
	    iexph, &ns, iflag);
    iexph = ifree + iexph - 1;
    iphih = iexph + mbrkdwn * mx;
    nscale += ns;
    i__1 = iphih + mbrkdwn;
    i__2 = iphih + mx + mbrkdwn - 1;
    z__1.r = hj1j * wsp[i__2].r, z__1.i = hj1j * wsp[i__2].i;
    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
    i__1 = iphih + mbrkdwn + 1;
    i__2 = iphih + (mx << 1) + mbrkdwn - 1;
    z__1.r = hj1j * wsp[i__2].r, z__1.i = hj1j * wsp[i__2].i;
    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = z_abs(&wsp[iphih + *m]) * beta;
	p2 = z_abs(&wsp[iphih + *m + 1]) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m + 1);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m + 1);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___584);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___585);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___586);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___587);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___588);
	    do_lio(&c__9, &c__1, "Failure in ZGPHIV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___589);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___590);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 2;
    mx = mbrkdwn + max(i__1,i__2);
    q__1.r = beta, q__1.i = 0.f;
    hij.r = q__1.r, hij.i = q__1.i;
    zgemv_("n", n, &mx, &hij, &wsp[iv], n, &wsp[iphih], &c__1, &c_b173, &w[1],
	     &c__1, (ftnlen)1);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___591);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___592);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___593);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___594);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___595);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    q__1.r = step_min__, q__1.i = 0.f;
    wsp[1].r = q__1.r, wsp[1].i = q__1.i;
    q__1.r = step_max__, q__1.i = 0.f;
    wsp[2].r = q__1.r, wsp[2].i = q__1.i;
    wsp[3].r = 0.f, wsp[3].i = 0.f;
    wsp[4].r = 0.f, wsp[4].i = 0.f;
    q__1.r = x_error__, q__1.i = 0.f;
    wsp[5].r = q__1.r, wsp[5].i = q__1.i;
    q__1.r = s_error__, q__1.i = 0.f;
    wsp[6].r = q__1.r, wsp[6].i = q__1.i;
    q__1.r = tbrkdwn, q__1.i = 0.f;
    wsp[7].r = q__1.r, wsp[7].i = q__1.i;
    d__1 = sgn * t_now__;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[8].r = q__1.r, wsp[8].i = q__1.i;
    return 0;
} /* zgphiv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int zhphiv_(integer *n, integer *m, doublereal *t, 
	doublecomplex *u, doublecomplex *v, doublecomplex *w, doublereal *tol,
	 doublereal *anorm, doublecomplex *wsp, integer *lwsp, integer *iwsp, 
	integer *liwsp, S_fp matvec, integer *itrace, integer *iflag)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;
    complex q__1;
    doublecomplex z__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double sqrt(doublereal), d_sign(doublereal *, doublereal *), pow_di(
	    doublereal *, integer *), pow_dd(doublereal *, doublereal *), 
	    d_lg10(doublereal *);
    integer i_dnnt(doublereal *);
    double d_int(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double z_abs(doublecomplex *);

    /* Local variables */
    static integer ibrkflag;
    static doublereal step_min__, step_max__;
    static integer i__, j;
    static doublereal break_tol__;
    static integer k1;
    static doublereal p1, p2, p3;
    static integer ih, mh, iv, ns, mx;
    static doublereal xm;
    static integer j1v;
    static doublecomplex hjj;
    static doublereal sgn, eps, hj1j, sqr1, beta;
    static integer ifree, lfree, iphih;
    static doublereal t_old__;
    static integer iexph;
    static doublereal t_new__;
    static integer nexph;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublereal t_now__;
    extern /* Subroutine */ int zgemv_(char *, integer *, integer *, 
	    doublecomplex *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, ftnlen);
    static integer nstep;
    static doublereal t_out__;
    static integer nmult;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern doublereal dznrm2_(integer *, doublecomplex *, integer *);
    static integer nscale;
    static doublereal rndoff;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *), zgpadm_(integer *, integer *, 
	    doublereal *, doublecomplex *, integer *, doublecomplex *, 
	    integer *, integer *, integer *, integer *, integer *);
    static doublereal t_step__, avnorm;
    static integer ireject;
    static doublereal err_loc__;
    static integer nreject, mbrkdwn;
    static doublereal tbrkdwn, s_error__, x_error__;

    /* Fortran I/O blocks */
    static cilist io___633 = { 0, 6, 0, 0, 0 };
    static cilist io___642 = { 0, 6, 0, 0, 0 };
    static cilist io___643 = { 0, 6, 0, 0, 0 };
    static cilist io___644 = { 0, 6, 0, 0, 0 };
    static cilist io___645 = { 0, 6, 0, 0, 0 };
    static cilist io___646 = { 0, 6, 0, 0, 0 };
    static cilist io___647 = { 0, 6, 0, 0, 0 };
    static cilist io___648 = { 0, 6, 0, 0, 0 };
    static cilist io___649 = { 0, 6, 0, 0, 0 };
    static cilist io___650 = { 0, 6, 0, 0, 0 };
    static cilist io___651 = { 0, 6, 0, 0, 0 };
    static cilist io___652 = { 0, 6, 0, 0, 0 };
    static cilist io___653 = { 0, 6, 0, 0, 0 };


/* -----Purpose----------------------------------------------------------| */

/* ---  ZHPHIV computes w = exp(t*A)v + t*phi(tA)u which is the solution */
/*     of the nonhomogeneous linear ODE problem w' = Aw + u, w(0) = v. */
/*     phi(z) = (exp(z)-1)/z and A is an Hermitian matrix. */

/*     The method used is based on Krylov subspace projection */
/*     techniques and the matrix under consideration interacts only */
/*     via the external routine `matvec' performing the matrix-vector */
/*     product (matrix-free method). */

/* -----Arguments--------------------------------------------------------| */

/*     n      : (input) order of the principal matrix A. */

/*     m      : (input) maximum size for the Krylov basis. */

/*     t      : (input) time at wich the solution is needed (can be < 0). */

/*     u(n)   : (input) operand vector with respect to the phi function */
/*              (forcing term of the ODE problem). */

/*     v(n)   : (input) operand vector with respect to the exp function */
/*              (initial condition of the ODE problem). */

/*     w(n)   : (output) computed approximation of exp(t*A)v + t*phi(tA)u */

/*     tol    : (input/output) the requested accuracy tolerance on w. */
/*              If on input tol=0.0d0 or tol is too small (tol.le.eps) */
/*              the internal value sqrt(eps) is used, and tol is set to */
/*              sqrt(eps) on output (`eps' denotes the machine epsilon). */
/*              (`Happy breakdown' is assumed if h(j+1,j) .le. anorm*tol) */

/*     anorm  : (input) an approximation of some norm of A. */

/*   wsp(lwsp): (workspace) lwsp .ge. n*(m+1)+n+(m+3)^2+4*(m+3)^2+ideg+1 */
/*                                   +---------+-------+---------------+ */
/*              (actually, ideg=6)        V        H      wsp for PADE */

/* iwsp(liwsp): (workspace) liwsp .ge. m+3 */

/*     matvec : external subroutine for matrix-vector multiplication. */
/*              synopsis: matvec( x, y ) */
/*                        double precision x(*), y(*) */
/*              computes: y(1:n) <- A*x(1:n) */
/*                        where A is the principal matrix. */

/*     itrace : (input) running mode. 0=silent, 1=print step-by-step info */

/*     iflag  : (output) exit flag. */
/*              <0 - bad input arguments */
/*               0 - no problem */
/*               1 - maximum number of steps reached without convergence */
/*               2 - requested tolerance was too high */

/* -----Accounts on the computation--------------------------------------| */
/*     Upon exit, an interested user may retrieve accounts on the */
/*     computations. They are located in the workspace arrays wsp and */
/*     iwsp as indicated below: */

/*     location  mnemonic                 description */
/*     -----------------------------------------------------------------| */
/*     iwsp(1) = nmult, number of matrix-vector multiplications used */
/*     iwsp(2) = nexph, number of Hessenberg matrix exponential evaluated */
/*     iwsp(3) = nscale, number of repeated squaring involved in Pade */
/*     iwsp(4) = nstep, number of integration steps used up to completion */
/*     iwsp(5) = nreject, number of rejected step-sizes */
/*     iwsp(6) = ibrkflag, set to 1 if `happy breakdown' and 0 otherwise */
/*     iwsp(7) = mbrkdwn, if `happy brkdown', basis-size when it occured */
/*     -----------------------------------------------------------------| */
/*     wsp(1)  = step_min, minimum step-size used during integration */
/*     wsp(2)  = step_max, maximum step-size used during integration */
/*     wsp(3)  = dummy */
/*     wsp(4)  = dummy */
/*     wsp(5)  = x_error, maximum among all local truncation errors */
/*     wsp(6)  = s_error, global sum of local truncation errors */
/*     wsp(7)  = tbrkdwn, if `happy breakdown', time when it occured */
/*     wsp(8)  = t_now, integration domain successfully covered */

/* ----------------------------------------------------------------------| */
/* -----The following parameters may also be adjusted herein-------------| */

/*     mxstep  : maximum allowable number of integration steps. */
/*               The value 0 means an infinite number of steps. */

/*     mxreject: maximum allowable number of rejections at each step. */
/*               The value 0 means an infinite number of rejections. */

/*     ideg    : the Pade approximation of type (ideg,ideg) is used as */
/*               an approximation to exp(H). */

/*     delta   : local truncation error `safety factor' */

/*     gamma   : stepsize `shrinking factor' */

/* ----------------------------------------------------------------------| */
/*     Roger B. Sidje (rbs@maths.uq.edu.au) */
/*     EXPOKIT: Software Package for Computing Matrix Exponentials. */
/*     ACM - Transactions On Mathematical Software, 24(1):130-156, 1998 */
/* ----------------------------------------------------------------------| */


/* ---  check restrictions on input parameters ... */

    /* Parameter adjustments */
    --w;
    --v;
    --u;
    --wsp;
    --iwsp;

    /* Function Body */
    *iflag = 0;
/* Computing 2nd power */
    i__1 = *m + 3;
    if (*lwsp < *n * (*m + 3) + i__1 * i__1 * 5 + 7) {
	*iflag = -1;
    }
    if (*liwsp < *m + 3) {
	*iflag = -2;
    }
    if (*m >= *n || *m <= 0) {
	*iflag = -3;
    }
    if (*iflag != 0) {
	s_stop("bad sizes (in input of ZHPHIV)", (ftnlen)30);
    }

/* ---  initialisations ... */

    k1 = 3;
    mh = *m + 3;
    iv = 1;
    ih = iv + *n * (*m + 1) + *n;
    ifree = ih + mh * mh;
    lfree = *lwsp - ifree + 1;
    ibrkflag = 0;
    mbrkdwn = *m;
    nmult = 0;
    nreject = 0;
    nexph = 0;
    nscale = 0;
    t_out__ = abs(*t);
    tbrkdwn = 0.;
    step_min__ = t_out__;
    step_max__ = 0.;
    nstep = 0;
    s_error__ = 0.;
    x_error__ = 0.;
    t_now__ = 0.;
    t_new__ = 0.;
    p1 = 1.3333333333333333;
L1:
    p2 = p1 - 1.;
    p3 = p2 + p2 + p2;
    eps = (d__1 = p3 - 1., abs(d__1));
    if (eps == 0.) {
	goto L1;
    }
    if (*tol <= eps) {
	*tol = sqrt(eps);
    }
    rndoff = eps * *anorm;
    break_tol__ = 1e-7;
/* >>>  break_tol = tol */
/* >>>  break_tol = anorm*tol */
    sgn = d_sign(&c_b3, t);
    sqr1 = sqrt(.1);
    zcopy_(n, &v[1], &c__1, &w[1], &c__1);

/* ---  step-by-step integration ... */

L100:
    if (t_now__ >= t_out__) {
	goto L500;
    }
    ++nmult;
    (*matvec)(&w[1], &wsp[iv]);
    zaxpy_(n, &c_b173, &u[1], &c__1, &wsp[iv], &c__1);
    beta = dznrm2_(n, &wsp[iv], &c__1);
    if (beta == 0.) {
	goto L500;
    }
    d__1 = 1. / beta;
    zdscal_(n, &d__1, &wsp[iv], &c__1);
    i__1 = mh * mh;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + i__ - 1;
	wsp[i__2].r = 0., wsp[i__2].i = 0.;
    }
    if (nstep == 0) {
/* ---     obtain the very first stepsize ... */
	xm = 1. / (doublereal) (*m);
	d__1 = (*m + 1) / 2.72;
	i__1 = *m + 1;
	p1 = *tol * pow_di(&d__1, &i__1) * sqrt((*m + 1) * 6.2800000000000002)
		;
	d__1 = p1 / (beta * 4. * *anorm);
	t_new__ = 1. / *anorm * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_new__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_new__ / p1 + .55;
	t_new__ = d_int(&d__1) * p1;
    }
    ++nstep;
/* Computing MIN */
    d__1 = t_out__ - t_now__;
    t_step__ = min(d__1,t_new__);

/* ---  Lanczos loop ... */

    j1v = iv + *n;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	++nmult;
	(*matvec)(&wsp[j1v - *n], &wsp[j1v]);
	if (j > 1) {
	    i__2 = ih + (j - 1) * mh + j - 2;
	    z__1.r = -wsp[i__2].r, z__1.i = -wsp[i__2].i;
	    zaxpy_(n, &z__1, &wsp[j1v - (*n << 1)], &c__1, &wsp[j1v], &c__1);
	}
	zdotc_(&z__1, n, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hjj.r = z__1.r, hjj.i = z__1.i;
	z__1.r = -hjj.r, z__1.i = -hjj.i;
	zaxpy_(n, &z__1, &wsp[j1v - *n], &c__1, &wsp[j1v], &c__1);
	hj1j = dznrm2_(n, &wsp[j1v], &c__1);
	i__2 = ih + (j - 1) * (mh + 1);
	wsp[i__2].r = hjj.r, wsp[i__2].i = hjj.i;
	if (hj1j <= break_tol__) {
	    s_wsle(&io___633);
	    do_lio(&c__9, &c__1, "happy breakdown: mbrkdwn =", (ftnlen)26);
	    do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " h =", (ftnlen)4);
	    do_lio(&c__5, &c__1, (char *)&hj1j, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    k1 = 0;
	    ibrkflag = 1;
	    mbrkdwn = j;
	    tbrkdwn = t_now__;
	    t_step__ = t_out__ - t_now__;
	    goto L300;
	}
	i__2 = ih + (j - 1) * mh + j;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	i__2 = ih + j * mh + j - 1;
	q__1.r = hj1j, q__1.i = 0.f;
	wsp[i__2].r = q__1.r, wsp[i__2].i = q__1.i;
	d__1 = 1. / hj1j;
	zdscal_(n, &d__1, &wsp[j1v], &c__1);
	j1v += *n;
/* L200: */
    }
    ++nmult;
    (*matvec)(&wsp[j1v - *n], &wsp[j1v]);
    avnorm = dznrm2_(n, &wsp[j1v], &c__1);

/* ---  set 1's for the 3-extended scheme ... */

L300:
    i__1 = ih + mh * mbrkdwn;
    wsp[i__1].r = 1., wsp[i__1].i = 0.;
    i__1 = ih + *m * mh + *m - 1;
    wsp[i__1].r = 0., wsp[i__1].i = 0.;
    i__1 = ih + (*m - 1) * mh + *m;
    wsp[i__1].r = 0., wsp[i__1].i = 0.;
    i__1 = k1 - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ih + (*m + i__) * mh + *m + i__ - 1;
	wsp[i__2].r = 1., wsp[i__2].i = 0.;
    }

/* ---  loop while ireject<mxreject until the tolerance is reached ... */

    ireject = 0;
L401:

/* ---  compute w = beta*t_step*V*phi(t_step*H)*e1 + w */

    ++nexph;
    mx = mbrkdwn + max(1,k1);
/* ---  irreducible rational Pade approximation ... */
    d__1 = sgn * t_step__;
    zgpadm_(&c__6, &mx, &d__1, &wsp[ih], &mh, &wsp[ifree], &lfree, &iwsp[1], &
	    iexph, &ns, iflag);
    iexph = ifree + iexph - 1;
    iphih = iexph + mbrkdwn * mx;
    nscale += ns;
    i__1 = iphih + mbrkdwn;
    i__2 = iphih + mx + mbrkdwn - 1;
    z__1.r = hj1j * wsp[i__2].r, z__1.i = hj1j * wsp[i__2].i;
    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
    i__1 = iphih + mbrkdwn + 1;
    i__2 = iphih + (mx << 1) + mbrkdwn - 1;
    z__1.r = hj1j * wsp[i__2].r, z__1.i = hj1j * wsp[i__2].i;
    wsp[i__1].r = z__1.r, wsp[i__1].i = z__1.i;
/* L402: */

/* ---  error estimate ... */

    if (k1 == 0) {
	err_loc__ = *tol;
    } else {
	p1 = z_abs(&wsp[iphih + *m]) * beta;
	p2 = z_abs(&wsp[iphih + *m + 1]) * beta * avnorm;
	if (p1 > p2 * 10.) {
	    err_loc__ = p2;
	    xm = 1. / (doublereal) (*m + 1);
	} else if (p1 > p2) {
	    err_loc__ = p1 * p2 / (p1 - p2);
	    xm = 1. / (doublereal) (*m + 1);
	} else {
	    err_loc__ = p1;
	    xm = 1. / (doublereal) (*m);
	}
    }

/* ---  reject the step-size if the error is not acceptable ... */

    if (k1 != 0 && err_loc__ > t_step__ * 1.2 * *tol) {
	t_old__ = t_step__;
	d__1 = t_step__ * *tol / err_loc__;
	t_step__ = t_step__ * .9 * pow_dd(&d__1, &xm);
	d__1 = d_lg10(&t_step__) - sqr1;
	i__1 = i_dnnt(&d__1) - 1;
	p1 = pow_di(&c_b8, &i__1);
	d__1 = t_step__ / p1 + .55;
	t_step__ = d_int(&d__1) * p1;
	if (*itrace != 0) {
	    s_wsle(&io___642);
	    do_lio(&c__9, &c__1, "t_step =", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&t_old__, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsle();
	    s_wsle(&io___643);
	    do_lio(&c__9, &c__1, "err_loc =", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(
		    doublereal));
	    e_wsle();
	    s_wsle(&io___644);
	    do_lio(&c__9, &c__1, "err_required =", (ftnlen)14);
	    d__1 = t_old__ * 1.2 * *tol;
	    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_wsle(&io___645);
	    do_lio(&c__9, &c__1, "stepsize rejected, stepping down to:", (
		    ftnlen)36);
	    do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal)
		    );
	    e_wsle();
	}
	++ireject;
	++nreject;
	if (FALSE_) {
	    s_wsle(&io___646);
	    do_lio(&c__9, &c__1, "Failure in ZHPHIV: ---", (ftnlen)22);
	    e_wsle();
	    s_wsle(&io___647);
	    do_lio(&c__9, &c__1, "The requested tolerance is too high.", (
		    ftnlen)36);
	    e_wsle();
	    s_wsle(&io___648);
	    do_lio(&c__9, &c__1, "Rerun with a smaller value.", (ftnlen)27);
	    e_wsle();
	    *iflag = 2;
	    return 0;
	}
	goto L401;
    }

/* Computing MAX */
    i__1 = 0, i__2 = k1 - 2;
    mx = mbrkdwn + max(i__1,i__2);
    q__1.r = beta, q__1.i = 0.f;
    hjj.r = q__1.r, hjj.i = q__1.i;
    zgemv_("n", n, &mx, &hjj, &wsp[iv], n, &wsp[iphih], &c__1, &c_b173, &w[1],
	     &c__1, (ftnlen)1);

/* ---  suggested value for the next stepsize ... */

    d__1 = t_step__ * *tol / err_loc__;
    t_new__ = t_step__ * .9 * pow_dd(&d__1, &xm);
    d__1 = d_lg10(&t_new__) - sqr1;
    i__1 = i_dnnt(&d__1) - 1;
    p1 = pow_di(&c_b8, &i__1);
    d__1 = t_new__ / p1 + .55;
    t_new__ = d_int(&d__1) * p1;
    err_loc__ = max(err_loc__,rndoff);

/* ---  update the time covered ... */

    t_now__ += t_step__;

/* ---  display and keep some information ... */

    if (*itrace != 0) {
	s_wsle(&io___649);
	do_lio(&c__9, &c__1, "integration", (ftnlen)11);
	do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	do_lio(&c__9, &c__1, "---------------------------------", (ftnlen)33);
	e_wsle();
	s_wsle(&io___650);
	do_lio(&c__9, &c__1, "scale-square =", (ftnlen)14);
	do_lio(&c__3, &c__1, (char *)&ns, (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___651);
	do_lio(&c__9, &c__1, "step_size =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_step__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___652);
	do_lio(&c__9, &c__1, "err_loc   =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&err_loc__, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___653);
	do_lio(&c__9, &c__1, "next_step =", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&t_new__, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    step_min__ = min(step_min__,t_step__);
    step_max__ = max(step_max__,t_step__);
    s_error__ += err_loc__;
    x_error__ = max(x_error__,err_loc__);
    if (nstep < 500) {
	goto L100;
    }
    *iflag = 1;
L500:
    iwsp[1] = nmult;
    iwsp[2] = nexph;
    iwsp[3] = nscale;
    iwsp[4] = nstep;
    iwsp[5] = nreject;
    iwsp[6] = ibrkflag;
    iwsp[7] = mbrkdwn;
    q__1.r = step_min__, q__1.i = 0.f;
    wsp[1].r = q__1.r, wsp[1].i = q__1.i;
    q__1.r = step_max__, q__1.i = 0.f;
    wsp[2].r = q__1.r, wsp[2].i = q__1.i;
    wsp[3].r = 0.f, wsp[3].i = 0.f;
    wsp[4].r = 0.f, wsp[4].i = 0.f;
    q__1.r = x_error__, q__1.i = 0.f;
    wsp[5].r = q__1.r, wsp[5].i = q__1.i;
    q__1.r = s_error__, q__1.i = 0.f;
    wsp[6].r = q__1.r, wsp[6].i = q__1.i;
    q__1.r = tbrkdwn, q__1.i = 0.f;
    wsp[7].r = q__1.r, wsp[7].i = q__1.i;
    d__1 = sgn * t_now__;
    q__1.r = d__1, q__1.i = 0.f;
    wsp[8].r = q__1.r, wsp[8].i = q__1.i;
    return 0;
} /* zhphiv_ */

