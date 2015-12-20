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

static integer c__0 = 0;
static integer c__1 = 1;
static doublecomplex c_b113 = {-1.,-0.};

/* from expokit, free for non-commercial use */
/*     This is a lightweight substitute to the external LAPACK routines */
/*     used by EXPOKIT. It is supplied to ensure that EXPOKIT is */
/*     self-contained and can still run if LAPACK is not yet installed */
/*     in your environement. */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgesv_(integer *n, integer *m, doublereal *a, integer *
	lda, integer *ipiv, doublereal *b, integer *ldb, integer *iflag)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    extern /* Subroutine */ int dgefa_(doublereal *, integer *, integer *, 
	    integer *, integer *), dgesl_(doublereal *, integer *, integer *, 
	    integer *, doublereal *, integer *);

    /* Parameter adjustments */
    --ipiv;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    dgefa_(&a[a_offset], lda, n, &ipiv[1], iflag);
    if (*iflag != 0) {
	s_stop("Error in DGESV (LU factorisation)", (ftnlen)33);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	dgesl_(&a[a_offset], lda, n, &ipiv[1], &b[j * b_dim1 + 1], &c__0);
    }
    return 0;
} /* dgesv_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int dsysv_(char *uplo, integer *n, integer *m, doublereal *a,
	 integer *lda, integer *ipiv, doublereal *b, integer *ldb, doublereal 
	*wrk, integer *lwrk, integer *iflag, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    extern /* Subroutine */ int dsifa_(doublereal *, integer *, integer *, 
	    integer *, integer *), dsisl_(doublereal *, integer *, integer *, 
	    integer *, doublereal *);

    /* Parameter adjustments */
    --ipiv;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --wrk;

    /* Function Body */
    dsifa_(&a[a_offset], lda, n, &ipiv[1], iflag);
    if (*iflag != 0) {
	s_stop("Error in DSYSV (LDL' factorisation)", (ftnlen)35);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	dsisl_(&a[a_offset], lda, n, &ipiv[1], &b[j * b_dim1 + 1]);
    }
    return 0;
} /* dsysv_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int zgesv_(integer *n, integer *m, doublecomplex *a, integer 
	*lda, integer *ipiv, doublecomplex *b, integer *ldb, integer *iflag)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    extern /* Subroutine */ int zgefa_(doublecomplex *, integer *, integer *, 
	    integer *, integer *), zgesl_(doublecomplex *, integer *, integer 
	    *, integer *, doublecomplex *, integer *);

    /* Parameter adjustments */
    --ipiv;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    zgefa_(&a[a_offset], lda, n, &ipiv[1], iflag);
    if (*iflag != 0) {
	s_stop("Error in ZGESV (LU factorisation)", (ftnlen)33);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	zgesl_(&a[a_offset], lda, n, &ipiv[1], &b[j * b_dim1 + 1], &c__0);
    }
    return 0;
} /* zgesv_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int zhesv_(char *uplo, integer *n, integer *m, doublecomplex 
	*a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *wrk, integer *lwrk, integer *iflag, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    extern /* Subroutine */ int zhifa_(doublecomplex *, integer *, integer *, 
	    integer *, integer *), zhisl_(doublecomplex *, integer *, integer 
	    *, integer *, doublecomplex *);

    /* Parameter adjustments */
    --ipiv;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --wrk;

    /* Function Body */
    zhifa_(&a[a_offset], lda, n, &ipiv[1], iflag);
    if (*iflag != 0) {
	s_stop("Error in ZHESV (LDL' factorisation)", (ftnlen)35);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	zhisl_(&a[a_offset], lda, n, &ipiv[1], &b[j * b_dim1 + 1]);
    }
    return 0;
} /* zhesv_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int zsysv_(char *uplo, integer *n, integer *m, doublecomplex 
	*a, integer *lda, integer *ipiv, doublecomplex *b, integer *ldb, 
	doublecomplex *wrk, integer *lwrk, integer *iflag, ftnlen uplo_len)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    extern /* Subroutine */ int zsifa_(doublecomplex *, integer *, integer *, 
	    integer *, integer *), zsisl_(doublecomplex *, integer *, integer 
	    *, integer *, doublecomplex *);

    /* Parameter adjustments */
    --ipiv;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --wrk;

    /* Function Body */
    zsifa_(&a[a_offset], lda, n, &ipiv[1], iflag);
    if (*iflag != 0) {
	s_stop("Error in ZSYSV (LDL' factorisation)", (ftnlen)35);
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	zsisl_(&a[a_offset], lda, n, &ipiv[1], &b[j * b_dim1 + 1]);
    }
    return 0;
} /* zsysv_ */

/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgefa_(doublereal *a, integer *lda, integer *n, integer *
	ipvt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer j, k, l;
    static doublereal t;
    static integer kp1, nm1;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *), daxpy_(integer *, doublereal *, doublereal *, integer 
	    *, doublereal *, integer *);
    extern integer idamax_(integer *, doublereal *, integer *);


/*     dgefa factors a double precision matrix by gaussian elimination. */

/*     dgefa is usually called by dgeco, but it can be called */
/*     directly with a saving in time if  rcond  is not needed. */
/*     (time for dgeco) = (1 + 9/n)*(time for dgefa) . */

/*     on entry */

/*        a       double precision(lda, n) */
/*                the matrix to be factored. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       an upper triangular matrix and the multipliers */
/*                which were used to obtain it. */
/*                the factorization can be written  a = l*u  where */
/*                l  is a product of permutation and unit lower */
/*                triangular matrices and  u  is upper triangular. */

/*        ipvt    integer(n) */
/*                an integer vector of pivot indices. */

/*        info    integer */
/*                = 0  normal value. */
/*                = k  if  u(k,k) .eq. 0.0 .  this is not an error */
/*                     condition for this subroutine, but it does */
/*                     indicate that dgesl or dgedi will divide by zero */
/*                     if called.  use  rcond  in dgeco for a reliable */
/*                     indication of singularity. */

/*     linpack. this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas daxpy,dscal,idamax */

/*     internal variables */



/*     gaussian elimination with partial pivoting */

    /* Parameter adjustments */
    --ipvt;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;
    nm1 = *n - 1;
    if (nm1 < 1) {
	goto L70;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;

/*        find l = pivot index */

	i__2 = *n - k + 1;
	l = idamax_(&i__2, &a[k + k * a_dim1], &c__1) + k - 1;
	ipvt[k] = l;

/*        zero pivot implies this column already triangularized */

	if (a[l + k * a_dim1] == 0.) {
	    goto L40;
	}

/*           interchange if necessary */

	if (l == k) {
	    goto L10;
	}
	t = a[l + k * a_dim1];
	a[l + k * a_dim1] = a[k + k * a_dim1];
	a[k + k * a_dim1] = t;
L10:

/*           compute multipliers */

	t = -1. / a[k + k * a_dim1];
	i__2 = *n - k;
	dscal_(&i__2, &t, &a[k + 1 + k * a_dim1], &c__1);

/*           row elimination with column indexing */

	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    t = a[l + j * a_dim1];
	    if (l == k) {
		goto L20;
	    }
	    a[l + j * a_dim1] = a[k + j * a_dim1];
	    a[k + j * a_dim1] = t;
L20:
	    i__3 = *n - k;
	    daxpy_(&i__3, &t, &a[k + 1 + k * a_dim1], &c__1, &a[k + 1 + j * 
		    a_dim1], &c__1);
/* L30: */
	}
	goto L50;
L40:
	*info = k;
L50:
/* L60: */
	;
    }
L70:
    ipvt[*n] = *n;
    if (a[*n + *n * a_dim1] == 0.) {
	*info = *n;
    }
    return 0;
} /* dgefa_ */

/* ----------------------------------------------------------------------| */
/* Subroutine */ int dgesl_(doublereal *a, integer *lda, integer *n, integer *
	ipvt, doublereal *b, integer *job)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    static integer k, l;
    static doublereal t;
    static integer kb, nm1;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);


/*     dgesl solves the double precision system */
/*     a * x = b  or  trans(a) * x = b */
/*     using the factors computed by dgeco or dgefa. */

/*     on entry */

/*        a       double precision(lda, n) */
/*                the output from dgeco or dgefa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        ipvt    integer(n) */
/*                the pivot vector from dgeco or dgefa. */

/*        b       double precision(n) */
/*                the right hand side vector. */

/*        job     integer */
/*                = 0         to solve  a*x = b , */
/*                = nonzero   to solve  trans(a)*x = b  where */
/*                            trans(a)  is the transpose. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero will occur if the input factor contains a */
/*        zero on the diagonal.  technically this indicates singularity */
/*        but it is often caused by improper arguments or improper */
/*        setting of lda .  it will not occur if the subroutines are */
/*        called correctly and if dgeco has set rcond .gt. 0.0 */
/*        or dgefa has set info .eq. 0 . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call dgeco(a,lda,n,ipvt,rcond,z) */
/*           if (rcond is too small) go to ... */
/*           do 10 j = 1, p */
/*              call dgesl(a,lda,n,ipvt,c(1,j),0) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas daxpy,ddot */

/*     internal variables */


    /* Parameter adjustments */
    --b;
    --ipvt;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    nm1 = *n - 1;
    if (*job != 0) {
	goto L50;
    }

/*        job = 0 , solve  a * x = b */
/*        first solve  l*y = b */

    if (nm1 < 1) {
	goto L30;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	l = ipvt[k];
	t = b[l];
	if (l == k) {
	    goto L10;
	}
	b[l] = b[k];
	b[k] = t;
L10:
	i__2 = *n - k;
	daxpy_(&i__2, &t, &a[k + 1 + k * a_dim1], &c__1, &b[k + 1], &c__1);
/* L20: */
    }
L30:

/*        now solve  u*x = y */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	b[k] /= a[k + k * a_dim1];
	t = -b[k];
	i__2 = k - 1;
	daxpy_(&i__2, &t, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
/* L40: */
    }
    goto L100;
L50:

/*        job = nonzero, solve  trans(a) * x = b */
/*        first solve  trans(u)*y = b */

    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k - 1;
	t = ddot_(&i__2, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
	b[k] = (b[k] - t) / a[k + k * a_dim1];
/* L60: */
    }

/*        now solve trans(l)*x = y */

    if (nm1 < 1) {
	goto L90;
    }
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n - kb;
	i__2 = *n - k;
	b[k] += ddot_(&i__2, &a[k + 1 + k * a_dim1], &c__1, &b[k + 1], &c__1);
	l = ipvt[k];
	if (l == k) {
	    goto L70;
	}
	t = b[l];
	b[l] = b[k];
	b[k] = t;
L70:
/* L80: */
	;
    }
L90:
L100:
    return 0;
} /* dgesl_ */

/* Subroutine */ int dsifa_(doublereal *a, integer *lda, integer *n, integer *
	kpvt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer j, k;
    static doublereal t, ak, bk;
    static integer jj, km1, km2;
    static doublereal akm1, bkm1;
    static integer imax, jmax;
    static doublereal mulk;
    static logical swap;
    static doublereal alpha, denom;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), daxpy_(integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *);
    static integer kstep, imaxp1;
    static doublereal mulkm1, absakk;
    extern integer idamax_(integer *, doublereal *, integer *);
    static doublereal colmax, rowmax;


/*     dsifa factors a double precision symmetric matrix by elimination */
/*     with symmetric pivoting. */

/*     to solve  a*x = b , follow dsifa by dsisl. */
/*     to compute  inverse(a)*c , follow dsifa by dsisl. */
/*     to compute  determinant(a) , follow dsifa by dsidi. */
/*     to compute  inertia(a) , follow dsifa by dsidi. */
/*     to compute  inverse(a) , follow dsifa by dsidi. */

/*     on entry */

/*        a       double precision(lda,n) */
/*                the symmetric matrix to be factored. */
/*                only the diagonal and upper triangle are used. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       a block diagonal matrix and the multipliers which */
/*                were used to obtain it. */
/*                the factorization can be written  a = u*d*trans(u) */
/*                where  u  is a product of permutation and unit */
/*                upper triangular matrices , trans(u) is the */
/*                transpose of  u , and  d  is block diagonal */
/*                with 1 by 1 and 2 by 2 blocks. */

/*        kpvt    integer(n) */
/*                an integer vector of pivot indices. */

/*        info    integer */
/*                = 0  normal value. */
/*                = k  if the k-th pivot block is singular. this is */
/*                     not an error condition for this subroutine, */
/*                     but it does indicate that dsisl or dsidi may */
/*                     divide by zero if called. */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas daxpy,dswap,idamax */
/*     fortran dabs,dmax1,dsqrt */

/*     internal variables */



/*     initialize */

/*     alpha is used in choosing pivot block size. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;

    /* Function Body */
    alpha = (sqrt(17.) + 1.) / 8.;

    *info = 0;

/*     main loop on k, which goes from n to 1. */

    k = *n;
L10:

/*        leave the loop if k=0 or k=1. */

/*     ...exit */
    if (k == 0) {
	goto L200;
    }
    if (k > 1) {
	goto L20;
    }
    kpvt[1] = 1;
    if (a[a_dim1 + 1] == 0.) {
	*info = 1;
    }
/*     ......exit */
    goto L200;
L20:

/*        this section of code determines the kind of */
/*        elimination to be performed.  when it is completed, */
/*        kstep will be set to the size of the pivot block, and */
/*        swap will be set to .true. if an interchange is */
/*        required. */

    km1 = k - 1;
    absakk = (d__1 = a[k + k * a_dim1], abs(d__1));

/*        determine the largest off-diagonal element in */
/*        column k. */

    i__1 = k - 1;
    imax = idamax_(&i__1, &a[k * a_dim1 + 1], &c__1);
    colmax = (d__1 = a[imax + k * a_dim1], abs(d__1));
    if (absakk < alpha * colmax) {
	goto L30;
    }
    kstep = 1;
    swap = FALSE_;
    goto L90;
L30:

/*           determine the largest off-diagonal element in */
/*           row imax. */

    rowmax = 0.;
    imaxp1 = imax + 1;
    i__1 = k;
    for (j = imaxp1; j <= i__1; ++j) {
/* Computing MAX */
	d__2 = rowmax, d__3 = (d__1 = a[imax + j * a_dim1], abs(d__1));
	rowmax = max(d__2,d__3);
/* L40: */
    }
    if (imax == 1) {
	goto L50;
    }
    i__1 = imax - 1;
    jmax = idamax_(&i__1, &a[imax * a_dim1 + 1], &c__1);
/* Computing MAX */
    d__2 = rowmax, d__3 = (d__1 = a[jmax + imax * a_dim1], abs(d__1));
    rowmax = max(d__2,d__3);
L50:
    if ((d__1 = a[imax + imax * a_dim1], abs(d__1)) < alpha * rowmax) {
	goto L60;
    }
    kstep = 1;
    swap = TRUE_;
    goto L80;
L60:
    if (absakk < alpha * colmax * (colmax / rowmax)) {
	goto L70;
    }
    kstep = 1;
    swap = FALSE_;
    goto L80;
L70:
    kstep = 2;
    swap = imax != km1;
L80:
L90:
    if (max(absakk,colmax) != 0.) {
	goto L100;
    }

/*           column k is zero.  set info and iterate the loop. */

    kpvt[k] = k;
    *info = k;
    goto L190;
L100:
    if (kstep == 2) {
	goto L140;
    }

/*           1 x 1 pivot block. */

    if (! swap) {
	goto L120;
    }

/*              perform an interchange. */

    dswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[k * a_dim1 + 1], &c__1);
    i__1 = k;
    for (jj = imax; jj <= i__1; ++jj) {
	j = k + imax - jj;
	t = a[j + k * a_dim1];
	a[j + k * a_dim1] = a[imax + j * a_dim1];
	a[imax + j * a_dim1] = t;
/* L110: */
    }
L120:

/*           perform the elimination. */

    i__1 = km1;
    for (jj = 1; jj <= i__1; ++jj) {
	j = k - jj;
	mulk = -a[j + k * a_dim1] / a[k + k * a_dim1];
	t = mulk;
	daxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	a[j + k * a_dim1] = mulk;
/* L130: */
    }

/*           set the pivot array. */

    kpvt[k] = k;
    if (swap) {
	kpvt[k] = imax;
    }
    goto L190;
L140:

/*           2 x 2 pivot block. */

    if (! swap) {
	goto L160;
    }

/*              perform an interchange. */

    dswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[(k - 1) * a_dim1 + 1], &
	    c__1);
    i__1 = km1;
    for (jj = imax; jj <= i__1; ++jj) {
	j = km1 + imax - jj;
	t = a[j + (k - 1) * a_dim1];
	a[j + (k - 1) * a_dim1] = a[imax + j * a_dim1];
	a[imax + j * a_dim1] = t;
/* L150: */
    }
    t = a[k - 1 + k * a_dim1];
    a[k - 1 + k * a_dim1] = a[imax + k * a_dim1];
    a[imax + k * a_dim1] = t;
L160:

/*           perform the elimination. */

    km2 = k - 2;
    if (km2 == 0) {
	goto L180;
    }
    ak = a[k + k * a_dim1] / a[k - 1 + k * a_dim1];
    akm1 = a[k - 1 + (k - 1) * a_dim1] / a[k - 1 + k * a_dim1];
    denom = 1. - ak * akm1;
    i__1 = km2;
    for (jj = 1; jj <= i__1; ++jj) {
	j = km1 - jj;
	bk = a[j + k * a_dim1] / a[k - 1 + k * a_dim1];
	bkm1 = a[j + (k - 1) * a_dim1] / a[k - 1 + k * a_dim1];
	mulk = (akm1 * bk - bkm1) / denom;
	mulkm1 = (ak * bkm1 - bk) / denom;
	t = mulk;
	daxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	t = mulkm1;
	daxpy_(&j, &t, &a[(k - 1) * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &
		c__1);
	a[j + k * a_dim1] = mulk;
	a[j + (k - 1) * a_dim1] = mulkm1;
/* L170: */
    }
L180:

/*           set the pivot array. */

    kpvt[k] = 1 - k;
    if (swap) {
	kpvt[k] = -imax;
    }
    kpvt[k - 1] = kpvt[k];
L190:
    k -= kstep;
    goto L10;
L200:
    return 0;
} /* dsifa_ */

/* Subroutine */ int dsisl_(doublereal *a, integer *lda, integer *n, integer *
	kpvt, doublereal *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;

    /* Local variables */
    static integer k;
    static doublereal ak, bk;
    static integer kp;
    static doublereal akm1, bkm1;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal temp, denom;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);


/*     dsisl solves the double precision symmetric system */
/*     a * x = b */
/*     using the factors computed by dsifa. */

/*     on entry */

/*        a       double precision(lda,n) */
/*                the output from dsifa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        kpvt    integer(n) */
/*                the pivot vector from dsifa. */

/*        b       double precision(n) */
/*                the right hand side vector. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero may occur if  dsico  has set rcond .eq. 0.0 */
/*        or  dsifa  has set info .ne. 0  . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call dsifa(a,lda,n,kpvt,info) */
/*           if (info .ne. 0) go to ... */
/*           do 10 j = 1, p */
/*              call dsisl(a,lda,n,kpvt,c(1,j)) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas daxpy,ddot */
/*     fortran iabs */

/*     internal variables. */


/*     loop backward applying the transformations and */
/*     d inverse to b. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;
    --b;

    /* Function Body */
    k = *n;
L10:
    if (k == 0) {
	goto L80;
    }
    if (kpvt[k] < 0) {
	goto L40;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L30;
    }
    kp = kpvt[k];
    if (kp == k) {
	goto L20;
    }

/*                 interchange. */

    temp = b[k];
    b[k] = b[kp];
    b[kp] = temp;
L20:

/*              apply the transformation. */

    i__1 = k - 1;
    daxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
L30:

/*           apply d inverse. */

    b[k] /= a[k + k * a_dim1];
    --k;
    goto L70;
L40:

/*           2 x 2 pivot block. */

    if (k == 2) {
	goto L60;
    }
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k - 1) {
	goto L50;
    }

/*                 interchange. */

    temp = b[k - 1];
    b[k - 1] = b[kp];
    b[kp] = temp;
L50:

/*              apply the transformation. */

    i__1 = k - 2;
    daxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    i__1 = k - 2;
    daxpy_(&i__1, &b[k - 1], &a[(k - 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
L60:

/*           apply d inverse. */

    ak = a[k + k * a_dim1] / a[k - 1 + k * a_dim1];
    akm1 = a[k - 1 + (k - 1) * a_dim1] / a[k - 1 + k * a_dim1];
    bk = b[k] / a[k - 1 + k * a_dim1];
    bkm1 = b[k - 1] / a[k - 1 + k * a_dim1];
    denom = ak * akm1 - 1.;
    b[k] = (akm1 * bk - bkm1) / denom;
    b[k - 1] = (ak * bkm1 - bk) / denom;
    k += -2;
L70:
    goto L10;
L80:

/*     loop forward applying the transformations. */

    k = 1;
L90:
    if (k > *n) {
	goto L160;
    }
    if (kpvt[k] < 0) {
	goto L120;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L110;
    }

/*              apply the transformation. */

    i__1 = k - 1;
    b[k] += ddot_(&i__1, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    kp = kpvt[k];
    if (kp == k) {
	goto L100;
    }

/*                 interchange. */

    temp = b[k];
    b[k] = b[kp];
    b[kp] = temp;
L100:
L110:
    ++k;
    goto L150;
L120:

/*           2 x 2 pivot block. */

    if (k == 1) {
	goto L140;
    }

/*              apply the transformation. */

    i__1 = k - 1;
    b[k] += ddot_(&i__1, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    i__1 = k - 1;
    b[k + 1] += ddot_(&i__1, &a[(k + 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k) {
	goto L130;
    }

/*                 interchange. */

    temp = b[k];
    b[k] = b[kp];
    b[kp] = temp;
L130:
L140:
    k += 2;
L150:
    goto L90;
L160:
    return 0;
} /* dsisl_ */

/* Subroutine */ int zgefa_(doublecomplex *a, integer *lda, integer *n, 
	integer *ipvt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;
    doublecomplex z__1;

    /* Builtin functions */
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer j, k, l;
    static doublecomplex t;
    static integer kp1, nm1;
    extern /* Subroutine */ int zscal_(integer *, doublecomplex *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern integer izamax_(integer *, doublecomplex *, integer *);


/*     zgefa factors a complex*16 matrix by gaussian elimination. */

/*     zgefa is usually called by zgeco, but it can be called */
/*     directly with a saving in time if  rcond  is not needed. */
/*     (time for zgeco) = (1 + 9/n)*(time for zgefa) . */

/*     on entry */

/*        a       complex*16(lda, n) */
/*                the matrix to be factored. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       an upper triangular matrix and the multipliers */
/*                which were used to obtain it. */
/*                the factorization can be written  a = l*u  where */
/*                l  is a product of permutation and unit lower */
/*                triangular matrices and  u  is upper triangular. */

/*        ipvt    integer(n) */
/*                an integer vector of pivot indices. */

/*        info    integer */
/*                = 0  normal value. */
/*                = k  if  u(k,k) .eq. 0.0 .  this is not an error */
/*                     condition for this subroutine, but it does */
/*                     indicate that zgesl or zgedi will divide by zero */
/*                     if called.  use  rcond  in zgeco for a reliable */
/*                     indication of singularity. */

/*     linpack. this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas zaxpy,zscal,izamax */
/*     fortran dabs */

/*     internal variables */



/*     gaussian elimination with partial pivoting */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipvt;

    /* Function Body */
    *info = 0;
    nm1 = *n - 1;
    if (nm1 < 1) {
	goto L70;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	kp1 = k + 1;

/*        find l = pivot index */

	i__2 = *n - k + 1;
	l = izamax_(&i__2, &a[k + k * a_dim1], &c__1) + k - 1;
	ipvt[k] = l;

/*        zero pivot implies this column already triangularized */

	i__2 = l + k * a_dim1;
	i__3 = l + k * a_dim1;
	z__1.r = a[i__3].r * 0. - a[i__3].i * -1., z__1.i = a[i__3].i * 0. + 
		a[i__3].r * -1.;
	if ((d__1 = a[i__2].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) == 0.) 
		{
	    goto L40;
	}

/*           interchange if necessary */

	if (l == k) {
	    goto L10;
	}
	i__2 = l + k * a_dim1;
	t.r = a[i__2].r, t.i = a[i__2].i;
	i__2 = l + k * a_dim1;
	i__3 = k + k * a_dim1;
	a[i__2].r = a[i__3].r, a[i__2].i = a[i__3].i;
	i__2 = k + k * a_dim1;
	a[i__2].r = t.r, a[i__2].i = t.i;
L10:

/*           compute multipliers */

	z_div(&z__1, &c_b113, &a[k + k * a_dim1]);
	t.r = z__1.r, t.i = z__1.i;
	i__2 = *n - k;
	zscal_(&i__2, &t, &a[k + 1 + k * a_dim1], &c__1);

/*           row elimination with column indexing */

	i__2 = *n;
	for (j = kp1; j <= i__2; ++j) {
	    i__3 = l + j * a_dim1;
	    t.r = a[i__3].r, t.i = a[i__3].i;
	    if (l == k) {
		goto L20;
	    }
	    i__3 = l + j * a_dim1;
	    i__4 = k + j * a_dim1;
	    a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
	    i__3 = k + j * a_dim1;
	    a[i__3].r = t.r, a[i__3].i = t.i;
L20:
	    i__3 = *n - k;
	    zaxpy_(&i__3, &t, &a[k + 1 + k * a_dim1], &c__1, &a[k + 1 + j * 
		    a_dim1], &c__1);
/* L30: */
	}
	goto L50;
L40:
	*info = k;
L50:
/* L60: */
	;
    }
L70:
    ipvt[*n] = *n;
    i__1 = *n + *n * a_dim1;
    i__2 = *n + *n * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    if ((d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) == 0.) {
	*info = *n;
    }
    return 0;
} /* zgefa_ */

/* Subroutine */ int zgesl_(doublecomplex *a, integer *lda, integer *n, 
	integer *ipvt, doublecomplex *b, integer *job)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *), d_cnjg(
	    doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer k, l;
    static doublecomplex t;
    static integer kb, nm1;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);


/*     zgesl solves the complex*16 system */
/*     a * x = b  or  ctrans(a) * x = b */
/*     using the factors computed by zgeco or zgefa. */

/*     on entry */

/*        a       complex*16(lda, n) */
/*                the output from zgeco or zgefa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        ipvt    integer(n) */
/*                the pivot vector from zgeco or zgefa. */

/*        b       complex*16(n) */
/*                the right hand side vector. */

/*        job     integer */
/*                = 0         to solve  a*x = b , */
/*                = nonzero   to solve  ctrans(a)*x = b  where */
/*                            ctrans(a)  is the conjugate transpose. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero will occur if the input factor contains a */
/*        zero on the diagonal.  technically this indicates singularity */
/*        but it is often caused by improper arguments or improper */
/*        setting of lda .  it will not occur if the subroutines are */
/*        called correctly and if zgeco has set rcond .gt. 0.0 */
/*        or zgefa has set info .eq. 0 . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call zgeco(a,lda,n,ipvt,rcond,z) */
/*           if (rcond is too small) go to ... */
/*           do 10 j = 1, p */
/*              call zgesl(a,lda,n,ipvt,c(1,j),0) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas zaxpy,zdotc */
/*     fortran dconjg */

/*     internal variables */


    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipvt;
    --b;

    /* Function Body */
    nm1 = *n - 1;
    if (*job != 0) {
	goto L50;
    }

/*        job = 0 , solve  a * x = b */
/*        first solve  l*y = b */

    if (nm1 < 1) {
	goto L30;
    }
    i__1 = nm1;
    for (k = 1; k <= i__1; ++k) {
	l = ipvt[k];
	i__2 = l;
	t.r = b[i__2].r, t.i = b[i__2].i;
	if (l == k) {
	    goto L10;
	}
	i__2 = l;
	i__3 = k;
	b[i__2].r = b[i__3].r, b[i__2].i = b[i__3].i;
	i__2 = k;
	b[i__2].r = t.r, b[i__2].i = t.i;
L10:
	i__2 = *n - k;
	zaxpy_(&i__2, &t, &a[k + 1 + k * a_dim1], &c__1, &b[k + 1], &c__1);
/* L20: */
    }
L30:

/*        now solve  u*x = y */

    i__1 = *n;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n + 1 - kb;
	i__2 = k;
	z_div(&z__1, &b[k], &a[k + k * a_dim1]);
	b[i__2].r = z__1.r, b[i__2].i = z__1.i;
	i__2 = k;
	z__1.r = -b[i__2].r, z__1.i = -b[i__2].i;
	t.r = z__1.r, t.i = z__1.i;
	i__2 = k - 1;
	zaxpy_(&i__2, &t, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
/* L40: */
    }
    goto L100;
L50:

/*        job = nonzero, solve  ctrans(a) * x = b */
/*        first solve  ctrans(u)*y = b */

    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	i__2 = k - 1;
	zdotc_(&z__1, &i__2, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
	t.r = z__1.r, t.i = z__1.i;
	i__2 = k;
	i__3 = k;
	z__2.r = b[i__3].r - t.r, z__2.i = b[i__3].i - t.i;
	d_cnjg(&z__3, &a[k + k * a_dim1]);
	z_div(&z__1, &z__2, &z__3);
	b[i__2].r = z__1.r, b[i__2].i = z__1.i;
/* L60: */
    }

/*        now solve ctrans(l)*x = y */

    if (nm1 < 1) {
	goto L90;
    }
    i__1 = nm1;
    for (kb = 1; kb <= i__1; ++kb) {
	k = *n - kb;
	i__2 = k;
	i__3 = k;
	i__4 = *n - k;
	zdotc_(&z__2, &i__4, &a[k + 1 + k * a_dim1], &c__1, &b[k + 1], &c__1);
	z__1.r = b[i__3].r + z__2.r, z__1.i = b[i__3].i + z__2.i;
	b[i__2].r = z__1.r, b[i__2].i = z__1.i;
	l = ipvt[k];
	if (l == k) {
	    goto L70;
	}
	i__2 = l;
	t.r = b[i__2].r, t.i = b[i__2].i;
	i__2 = l;
	i__3 = k;
	b[i__2].r = b[i__3].r, b[i__2].i = b[i__3].i;
	i__2 = k;
	b[i__2].r = t.r, b[i__2].i = t.i;
L70:
/* L80: */
	;
    }
L90:
L100:
    return 0;
} /* zgesl_ */

/* Subroutine */ int zhifa_(doublecomplex *a, integer *lda, integer *n, 
	integer *kpvt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    double sqrt(doublereal);
    void d_cnjg(doublecomplex *, doublecomplex *), z_div(doublecomplex *, 
	    doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer j, k;
    static doublecomplex t, ak, bk;
    static integer jj, km1, km2;
    static doublecomplex akm1, bkm1;
    static integer imax, jmax;
    static doublecomplex mulk;
    static logical swap;
    static doublereal alpha;
    static doublecomplex denom;
    static integer kstep;
    extern /* Subroutine */ int zswap_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static integer imaxp1;
    static doublecomplex mulkm1;
    static doublereal absakk, colmax;
    extern integer izamax_(integer *, doublecomplex *, integer *);
    static doublereal rowmax;


/*     zhifa factors a complex*16 hermitian matrix by elimination */
/*     with symmetric pivoting. */

/*     to solve  a*x = b , follow zhifa by zhisl. */
/*     to compute  inverse(a)*c , follow zhifa by zhisl. */
/*     to compute  determinant(a) , follow zhifa by zhidi. */
/*     to compute  inertia(a) , follow zhifa by zhidi. */
/*     to compute  inverse(a) , follow zhifa by zhidi. */

/*     on entry */

/*        a       complex*16(lda,n) */
/*                the hermitian matrix to be factored. */
/*                only the diagonal and upper triangle are used. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       a block diagonal matrix and the multipliers which */
/*                were used to obtain it. */
/*                the factorization can be written  a = u*d*ctrans(u) */
/*                where  u  is a product of permutation and unit */
/*                upper triangular matrices , ctrans(u) is the */
/*                conjugate transpose of  u , and  d  is block diagonal */
/*                with 1 by 1 and 2 by 2 blocks. */

/*        kpvt    integer(n) */
/*                an integer vector of pivot indices. */

/*        info    integer */
/*                = 0  normal value. */
/*                = k  if the k-th pivot block is singular. this is */
/*                     not an error condition for this subroutine, */
/*                     but it does indicate that zhisl or zhidi may */
/*                     divide by zero if called. */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas zaxpy,zswap,izamax */
/*     fortran dabs,dmax1,dcmplx,dconjg,dsqrt */

/*     internal variables */



/*     initialize */

/*     alpha is used in choosing pivot block size. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;

    /* Function Body */
    alpha = (sqrt(17.) + 1.) / 8.;

    *info = 0;

/*     main loop on k, which goes from n to 1. */

    k = *n;
L10:

/*        leave the loop if k=0 or k=1. */

/*     ...exit */
    if (k == 0) {
	goto L200;
    }
    if (k > 1) {
	goto L20;
    }
    kpvt[1] = 1;
    i__1 = a_dim1 + 1;
    i__2 = a_dim1 + 1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    if ((d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) == 0.) {
	*info = 1;
    }
/*     ......exit */
    goto L200;
L20:

/*        this section of code determines the kind of */
/*        elimination to be performed.  when it is completed, */
/*        kstep will be set to the size of the pivot block, and */
/*        swap will be set to .true. if an interchange is */
/*        required. */

    km1 = k - 1;
    i__1 = k + k * a_dim1;
    i__2 = k + k * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    absakk = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2));

/*        determine the largest off-diagonal element in */
/*        column k. */

    i__1 = k - 1;
    imax = izamax_(&i__1, &a[k * a_dim1 + 1], &c__1);
    i__1 = imax + k * a_dim1;
    i__2 = imax + k * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    colmax = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2));
    if (absakk < alpha * colmax) {
	goto L30;
    }
    kstep = 1;
    swap = FALSE_;
    goto L90;
L30:

/*           determine the largest off-diagonal element in */
/*           row imax. */

    rowmax = 0.;
    imaxp1 = imax + 1;
    i__1 = k;
    for (j = imaxp1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = imax + j * a_dim1;
	i__3 = imax + j * a_dim1;
	z__1.r = a[i__3].r * 0. - a[i__3].i * -1., z__1.i = a[i__3].i * 0. + 
		a[i__3].r * -1.;
	d__3 = rowmax, d__4 = (d__1 = a[i__2].r, abs(d__1)) + (d__2 = z__1.r, 
		abs(d__2));
	rowmax = max(d__3,d__4);
/* L40: */
    }
    if (imax == 1) {
	goto L50;
    }
    i__1 = imax - 1;
    jmax = izamax_(&i__1, &a[imax * a_dim1 + 1], &c__1);
/* Computing MAX */
    i__1 = jmax + imax * a_dim1;
    i__2 = jmax + imax * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    d__3 = rowmax, d__4 = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(
	    d__2));
    rowmax = max(d__3,d__4);
L50:
    i__1 = imax + imax * a_dim1;
    i__2 = imax + imax * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    if ((d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) < alpha * 
	    rowmax) {
	goto L60;
    }
    kstep = 1;
    swap = TRUE_;
    goto L80;
L60:
    if (absakk < alpha * colmax * (colmax / rowmax)) {
	goto L70;
    }
    kstep = 1;
    swap = FALSE_;
    goto L80;
L70:
    kstep = 2;
    swap = imax != km1;
L80:
L90:
    if (max(absakk,colmax) != 0.) {
	goto L100;
    }

/*           column k is zero.  set info and iterate the loop. */

    kpvt[k] = k;
    *info = k;
    goto L190;
L100:
    if (kstep == 2) {
	goto L140;
    }

/*           1 x 1 pivot block. */

    if (! swap) {
	goto L120;
    }

/*              perform an interchange. */

    zswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[k * a_dim1 + 1], &c__1);
    i__1 = k;
    for (jj = imax; jj <= i__1; ++jj) {
	j = k + imax - jj;
	d_cnjg(&z__1, &a[j + k * a_dim1]);
	t.r = z__1.r, t.i = z__1.i;
	i__2 = j + k * a_dim1;
	d_cnjg(&z__1, &a[imax + j * a_dim1]);
	a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	i__2 = imax + j * a_dim1;
	a[i__2].r = t.r, a[i__2].i = t.i;
/* L110: */
    }
L120:

/*           perform the elimination. */

    i__1 = km1;
    for (jj = 1; jj <= i__1; ++jj) {
	j = k - jj;
	i__2 = j + k * a_dim1;
	z__2.r = -a[i__2].r, z__2.i = -a[i__2].i;
	z_div(&z__1, &z__2, &a[k + k * a_dim1]);
	mulk.r = z__1.r, mulk.i = z__1.i;
	d_cnjg(&z__1, &mulk);
	t.r = z__1.r, t.i = z__1.i;
	zaxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	i__2 = j + j * a_dim1;
	i__3 = j + j * a_dim1;
	d__1 = a[i__3].r;
	z__1.r = d__1, z__1.i = 0.;
	a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	i__2 = j + k * a_dim1;
	a[i__2].r = mulk.r, a[i__2].i = mulk.i;
/* L130: */
    }

/*           set the pivot array. */

    kpvt[k] = k;
    if (swap) {
	kpvt[k] = imax;
    }
    goto L190;
L140:

/*           2 x 2 pivot block. */

    if (! swap) {
	goto L160;
    }

/*              perform an interchange. */

    zswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[(k - 1) * a_dim1 + 1], &
	    c__1);
    i__1 = km1;
    for (jj = imax; jj <= i__1; ++jj) {
	j = km1 + imax - jj;
	d_cnjg(&z__1, &a[j + (k - 1) * a_dim1]);
	t.r = z__1.r, t.i = z__1.i;
	i__2 = j + (k - 1) * a_dim1;
	d_cnjg(&z__1, &a[imax + j * a_dim1]);
	a[i__2].r = z__1.r, a[i__2].i = z__1.i;
	i__2 = imax + j * a_dim1;
	a[i__2].r = t.r, a[i__2].i = t.i;
/* L150: */
    }
    i__1 = k - 1 + k * a_dim1;
    t.r = a[i__1].r, t.i = a[i__1].i;
    i__1 = k - 1 + k * a_dim1;
    i__2 = imax + k * a_dim1;
    a[i__1].r = a[i__2].r, a[i__1].i = a[i__2].i;
    i__1 = imax + k * a_dim1;
    a[i__1].r = t.r, a[i__1].i = t.i;
L160:

/*           perform the elimination. */

    km2 = k - 2;
    if (km2 == 0) {
	goto L180;
    }
    z_div(&z__1, &a[k + k * a_dim1], &a[k - 1 + k * a_dim1]);
    ak.r = z__1.r, ak.i = z__1.i;
    d_cnjg(&z__2, &a[k - 1 + k * a_dim1]);
    z_div(&z__1, &a[k - 1 + (k - 1) * a_dim1], &z__2);
    akm1.r = z__1.r, akm1.i = z__1.i;
    z__2.r = ak.r * akm1.r - ak.i * akm1.i, z__2.i = ak.r * akm1.i + ak.i * 
	    akm1.r;
    z__1.r = 1. - z__2.r, z__1.i = -z__2.i;
    denom.r = z__1.r, denom.i = z__1.i;
    i__1 = km2;
    for (jj = 1; jj <= i__1; ++jj) {
	j = km1 - jj;
	z_div(&z__1, &a[j + k * a_dim1], &a[k - 1 + k * a_dim1]);
	bk.r = z__1.r, bk.i = z__1.i;
	d_cnjg(&z__2, &a[k - 1 + k * a_dim1]);
	z_div(&z__1, &a[j + (k - 1) * a_dim1], &z__2);
	bkm1.r = z__1.r, bkm1.i = z__1.i;
	z__3.r = akm1.r * bk.r - akm1.i * bk.i, z__3.i = akm1.r * bk.i + 
		akm1.i * bk.r;
	z__2.r = z__3.r - bkm1.r, z__2.i = z__3.i - bkm1.i;
	z_div(&z__1, &z__2, &denom);
	mulk.r = z__1.r, mulk.i = z__1.i;
	z__3.r = ak.r * bkm1.r - ak.i * bkm1.i, z__3.i = ak.r * bkm1.i + ak.i 
		* bkm1.r;
	z__2.r = z__3.r - bk.r, z__2.i = z__3.i - bk.i;
	z_div(&z__1, &z__2, &denom);
	mulkm1.r = z__1.r, mulkm1.i = z__1.i;
	d_cnjg(&z__1, &mulk);
	t.r = z__1.r, t.i = z__1.i;
	zaxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	d_cnjg(&z__1, &mulkm1);
	t.r = z__1.r, t.i = z__1.i;
	zaxpy_(&j, &t, &a[(k - 1) * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &
		c__1);
	i__2 = j + k * a_dim1;
	a[i__2].r = mulk.r, a[i__2].i = mulk.i;
	i__2 = j + (k - 1) * a_dim1;
	a[i__2].r = mulkm1.r, a[i__2].i = mulkm1.i;
	i__2 = j + j * a_dim1;
	i__3 = j + j * a_dim1;
	d__1 = a[i__3].r;
	z__1.r = d__1, z__1.i = 0.;
	a[i__2].r = z__1.r, a[i__2].i = z__1.i;
/* L170: */
    }
L180:

/*           set the pivot array. */

    kpvt[k] = 1 - k;
    if (swap) {
	kpvt[k] = -imax;
    }
    kpvt[k - 1] = kpvt[k];
L190:
    k -= kstep;
    goto L10;
L200:
    return 0;
} /* zhifa_ */

/* Subroutine */ int zhisl_(doublecomplex *a, integer *lda, integer *n, 
	integer *kpvt, doublecomplex *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *), d_cnjg(
	    doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer k;
    static doublecomplex ak, bk;
    static integer kp;
    static doublecomplex akm1, bkm1, temp, denom;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);


/*     zhisl solves the complex*16 hermitian system */
/*     a * x = b */
/*     using the factors computed by zhifa. */

/*     on entry */

/*        a       complex*16(lda,n) */
/*                the output from zhifa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        kpvt    integer(n) */
/*                the pivot vector from zhifa. */

/*        b       complex*16(n) */
/*                the right hand side vector. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero may occur if  zhico  has set rcond .eq. 0.0 */
/*        or  zhifa  has set info .ne. 0  . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call zhifa(a,lda,n,kpvt,info) */
/*           if (info .ne. 0) go to ... */
/*           do 10 j = 1, p */
/*              call zhisl(a,lda,n,kpvt,c(1,j)) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas zaxpy,zdotc */
/*     fortran dconjg,iabs */

/*     internal variables. */


/*     loop backward applying the transformations and */
/*     d inverse to b. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;
    --b;

    /* Function Body */
    k = *n;
L10:
    if (k == 0) {
	goto L80;
    }
    if (kpvt[k] < 0) {
	goto L40;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L30;
    }
    kp = kpvt[k];
    if (kp == k) {
	goto L20;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L20:

/*              apply the transformation. */

    i__1 = k - 1;
    zaxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
L30:

/*           apply d inverse. */

    i__1 = k;
    z_div(&z__1, &b[k], &a[k + k * a_dim1]);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    --k;
    goto L70;
L40:

/*           2 x 2 pivot block. */

    if (k == 2) {
	goto L60;
    }
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k - 1) {
	goto L50;
    }

/*                 interchange. */

    i__1 = k - 1;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k - 1;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L50:

/*              apply the transformation. */

    i__1 = k - 2;
    zaxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    i__1 = k - 2;
    zaxpy_(&i__1, &b[k - 1], &a[(k - 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
L60:

/*           apply d inverse. */

    d_cnjg(&z__2, &a[k - 1 + k * a_dim1]);
    z_div(&z__1, &a[k + k * a_dim1], &z__2);
    ak.r = z__1.r, ak.i = z__1.i;
    z_div(&z__1, &a[k - 1 + (k - 1) * a_dim1], &a[k - 1 + k * a_dim1]);
    akm1.r = z__1.r, akm1.i = z__1.i;
    d_cnjg(&z__2, &a[k - 1 + k * a_dim1]);
    z_div(&z__1, &b[k], &z__2);
    bk.r = z__1.r, bk.i = z__1.i;
    z_div(&z__1, &b[k - 1], &a[k - 1 + k * a_dim1]);
    bkm1.r = z__1.r, bkm1.i = z__1.i;
    z__2.r = ak.r * akm1.r - ak.i * akm1.i, z__2.i = ak.r * akm1.i + ak.i * 
	    akm1.r;
    z__1.r = z__2.r - 1., z__1.i = z__2.i;
    denom.r = z__1.r, denom.i = z__1.i;
    i__1 = k;
    z__3.r = akm1.r * bk.r - akm1.i * bk.i, z__3.i = akm1.r * bk.i + akm1.i * 
	    bk.r;
    z__2.r = z__3.r - bkm1.r, z__2.i = z__3.i - bkm1.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k - 1;
    z__3.r = ak.r * bkm1.r - ak.i * bkm1.i, z__3.i = ak.r * bkm1.i + ak.i * 
	    bkm1.r;
    z__2.r = z__3.r - bk.r, z__2.i = z__3.i - bk.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    k += -2;
L70:
    goto L10;
L80:

/*     loop forward applying the transformations. */

    k = 1;
L90:
    if (k > *n) {
	goto L160;
    }
    if (kpvt[k] < 0) {
	goto L120;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L110;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotc_(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = kpvt[k];
    if (kp == k) {
	goto L100;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L100:
L110:
    ++k;
    goto L150;
L120:

/*           2 x 2 pivot block. */

    if (k == 1) {
	goto L140;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotc_(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k + 1;
    i__2 = k + 1;
    i__3 = k - 1;
    zdotc_(&z__2, &i__3, &a[(k + 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k) {
	goto L130;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L130:
L140:
    k += 2;
L150:
    goto L90;
L160:
    return 0;
} /* zhisl_ */

/* Subroutine */ int zsifa_(doublecomplex *a, integer *lda, integer *n, 
	integer *kpvt, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    double sqrt(doublereal);
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer j, k;
    static doublecomplex t, ak, bk;
    static integer jj, km1, km2;
    static doublecomplex akm1, bkm1;
    static integer imax, jmax;
    static doublecomplex mulk;
    static logical swap;
    static doublereal alpha;
    static doublecomplex denom;
    static integer kstep;
    extern /* Subroutine */ int zswap_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static integer imaxp1;
    static doublecomplex mulkm1;
    static doublereal absakk, colmax;
    extern integer izamax_(integer *, doublecomplex *, integer *);
    static doublereal rowmax;


/*     zsifa factors a complex*16 symmetric matrix by elimination */
/*     with symmetric pivoting. */

/*     to solve  a*x = b , follow zsifa by zsisl. */
/*     to compute  inverse(a)*c , follow zsifa by zsisl. */
/*     to compute  determinant(a) , follow zsifa by zsidi. */
/*     to compute  inverse(a) , follow zsifa by zsidi. */

/*     on entry */

/*        a       complex*16(lda,n) */
/*                the symmetric matrix to be factored. */
/*                only the diagonal and upper triangle are used. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       a block diagonal matrix and the multipliers which */
/*                were used to obtain it. */
/*                the factorization can be written  a = u*d*trans(u) */
/*                where  u  is a product of permutation and unit */
/*                upper triangular matrices , trans(u) is the */
/*                transpose of  u , and  d  is block diagonal */
/*                with 1 by 1 and 2 by 2 blocks. */

/*        kpvt    integer(n) */
/*                an integer vector of pivot indices. */

/*        info    integer */
/*                = 0  normal value. */
/*                = k  if the k-th pivot block is singular. this is */
/*                     not an error condition for this subroutine, */
/*                     but it does indicate that zsisl or zsidi may */
/*                     divide by zero if called. */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas zaxpy,zswap,izamax */
/*     fortran dabs,dmax1,dsqrt */

/*     internal variables */



/*     initialize */

/*     alpha is used in choosing pivot block size. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;

    /* Function Body */
    alpha = (sqrt(17.) + 1.) / 8.;

    *info = 0;

/*     main loop on k, which goes from n to 1. */

    k = *n;
L10:

/*        leave the loop if k=0 or k=1. */

/*     ...exit */
    if (k == 0) {
	goto L200;
    }
    if (k > 1) {
	goto L20;
    }
    kpvt[1] = 1;
    i__1 = a_dim1 + 1;
    i__2 = a_dim1 + 1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    if ((d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) == 0.) {
	*info = 1;
    }
/*     ......exit */
    goto L200;
L20:

/*        this section of code determines the kind of */
/*        elimination to be performed.  when it is completed, */
/*        kstep will be set to the size of the pivot block, and */
/*        swap will be set to .true. if an interchange is */
/*        required. */

    km1 = k - 1;
    i__1 = k + k * a_dim1;
    i__2 = k + k * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    absakk = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2));

/*        determine the largest off-diagonal element in */
/*        column k. */

    i__1 = k - 1;
    imax = izamax_(&i__1, &a[k * a_dim1 + 1], &c__1);
    i__1 = imax + k * a_dim1;
    i__2 = imax + k * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    colmax = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2));
    if (absakk < alpha * colmax) {
	goto L30;
    }
    kstep = 1;
    swap = FALSE_;
    goto L90;
L30:

/*           determine the largest off-diagonal element in */
/*           row imax. */

    rowmax = 0.;
    imaxp1 = imax + 1;
    i__1 = k;
    for (j = imaxp1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = imax + j * a_dim1;
	i__3 = imax + j * a_dim1;
	z__1.r = a[i__3].r * 0. - a[i__3].i * -1., z__1.i = a[i__3].i * 0. + 
		a[i__3].r * -1.;
	d__3 = rowmax, d__4 = (d__1 = a[i__2].r, abs(d__1)) + (d__2 = z__1.r, 
		abs(d__2));
	rowmax = max(d__3,d__4);
/* L40: */
    }
    if (imax == 1) {
	goto L50;
    }
    i__1 = imax - 1;
    jmax = izamax_(&i__1, &a[imax * a_dim1 + 1], &c__1);
/* Computing MAX */
    i__1 = jmax + imax * a_dim1;
    i__2 = jmax + imax * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    d__3 = rowmax, d__4 = (d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(
	    d__2));
    rowmax = max(d__3,d__4);
L50:
    i__1 = imax + imax * a_dim1;
    i__2 = imax + imax * a_dim1;
    z__1.r = a[i__2].r * 0. - a[i__2].i * -1., z__1.i = a[i__2].i * 0. + a[
	    i__2].r * -1.;
    if ((d__1 = a[i__1].r, abs(d__1)) + (d__2 = z__1.r, abs(d__2)) < alpha * 
	    rowmax) {
	goto L60;
    }
    kstep = 1;
    swap = TRUE_;
    goto L80;
L60:
    if (absakk < alpha * colmax * (colmax / rowmax)) {
	goto L70;
    }
    kstep = 1;
    swap = FALSE_;
    goto L80;
L70:
    kstep = 2;
    swap = imax != km1;
L80:
L90:
    if (max(absakk,colmax) != 0.) {
	goto L100;
    }

/*           column k is zero.  set info and iterate the loop. */

    kpvt[k] = k;
    *info = k;
    goto L190;
L100:
    if (kstep == 2) {
	goto L140;
    }

/*           1 x 1 pivot block. */

    if (! swap) {
	goto L120;
    }

/*              perform an interchange. */

    zswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[k * a_dim1 + 1], &c__1);
    i__1 = k;
    for (jj = imax; jj <= i__1; ++jj) {
	j = k + imax - jj;
	i__2 = j + k * a_dim1;
	t.r = a[i__2].r, t.i = a[i__2].i;
	i__2 = j + k * a_dim1;
	i__3 = imax + j * a_dim1;
	a[i__2].r = a[i__3].r, a[i__2].i = a[i__3].i;
	i__2 = imax + j * a_dim1;
	a[i__2].r = t.r, a[i__2].i = t.i;
/* L110: */
    }
L120:

/*           perform the elimination. */

    i__1 = km1;
    for (jj = 1; jj <= i__1; ++jj) {
	j = k - jj;
	i__2 = j + k * a_dim1;
	z__2.r = -a[i__2].r, z__2.i = -a[i__2].i;
	z_div(&z__1, &z__2, &a[k + k * a_dim1]);
	mulk.r = z__1.r, mulk.i = z__1.i;
	t.r = mulk.r, t.i = mulk.i;
	zaxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	i__2 = j + k * a_dim1;
	a[i__2].r = mulk.r, a[i__2].i = mulk.i;
/* L130: */
    }

/*           set the pivot array. */

    kpvt[k] = k;
    if (swap) {
	kpvt[k] = imax;
    }
    goto L190;
L140:

/*           2 x 2 pivot block. */

    if (! swap) {
	goto L160;
    }

/*              perform an interchange. */

    zswap_(&imax, &a[imax * a_dim1 + 1], &c__1, &a[(k - 1) * a_dim1 + 1], &
	    c__1);
    i__1 = km1;
    for (jj = imax; jj <= i__1; ++jj) {
	j = km1 + imax - jj;
	i__2 = j + (k - 1) * a_dim1;
	t.r = a[i__2].r, t.i = a[i__2].i;
	i__2 = j + (k - 1) * a_dim1;
	i__3 = imax + j * a_dim1;
	a[i__2].r = a[i__3].r, a[i__2].i = a[i__3].i;
	i__2 = imax + j * a_dim1;
	a[i__2].r = t.r, a[i__2].i = t.i;
/* L150: */
    }
    i__1 = k - 1 + k * a_dim1;
    t.r = a[i__1].r, t.i = a[i__1].i;
    i__1 = k - 1 + k * a_dim1;
    i__2 = imax + k * a_dim1;
    a[i__1].r = a[i__2].r, a[i__1].i = a[i__2].i;
    i__1 = imax + k * a_dim1;
    a[i__1].r = t.r, a[i__1].i = t.i;
L160:

/*           perform the elimination. */

    km2 = k - 2;
    if (km2 == 0) {
	goto L180;
    }
    z_div(&z__1, &a[k + k * a_dim1], &a[k - 1 + k * a_dim1]);
    ak.r = z__1.r, ak.i = z__1.i;
    z_div(&z__1, &a[k - 1 + (k - 1) * a_dim1], &a[k - 1 + k * a_dim1]);
    akm1.r = z__1.r, akm1.i = z__1.i;
    z__2.r = ak.r * akm1.r - ak.i * akm1.i, z__2.i = ak.r * akm1.i + ak.i * 
	    akm1.r;
    z__1.r = 1. - z__2.r, z__1.i = -z__2.i;
    denom.r = z__1.r, denom.i = z__1.i;
    i__1 = km2;
    for (jj = 1; jj <= i__1; ++jj) {
	j = km1 - jj;
	z_div(&z__1, &a[j + k * a_dim1], &a[k - 1 + k * a_dim1]);
	bk.r = z__1.r, bk.i = z__1.i;
	z_div(&z__1, &a[j + (k - 1) * a_dim1], &a[k - 1 + k * a_dim1]);
	bkm1.r = z__1.r, bkm1.i = z__1.i;
	z__3.r = akm1.r * bk.r - akm1.i * bk.i, z__3.i = akm1.r * bk.i + 
		akm1.i * bk.r;
	z__2.r = z__3.r - bkm1.r, z__2.i = z__3.i - bkm1.i;
	z_div(&z__1, &z__2, &denom);
	mulk.r = z__1.r, mulk.i = z__1.i;
	z__3.r = ak.r * bkm1.r - ak.i * bkm1.i, z__3.i = ak.r * bkm1.i + ak.i 
		* bkm1.r;
	z__2.r = z__3.r - bk.r, z__2.i = z__3.i - bk.i;
	z_div(&z__1, &z__2, &denom);
	mulkm1.r = z__1.r, mulkm1.i = z__1.i;
	t.r = mulk.r, t.i = mulk.i;
	zaxpy_(&j, &t, &a[k * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &c__1);
	t.r = mulkm1.r, t.i = mulkm1.i;
	zaxpy_(&j, &t, &a[(k - 1) * a_dim1 + 1], &c__1, &a[j * a_dim1 + 1], &
		c__1);
	i__2 = j + k * a_dim1;
	a[i__2].r = mulk.r, a[i__2].i = mulk.i;
	i__2 = j + (k - 1) * a_dim1;
	a[i__2].r = mulkm1.r, a[i__2].i = mulkm1.i;
/* L170: */
    }
L180:

/*           set the pivot array. */

    kpvt[k] = 1 - k;
    if (swap) {
	kpvt[k] = -imax;
    }
    kpvt[k - 1] = kpvt[k];
L190:
    k -= kstep;
    goto L10;
L200:
    return 0;
} /* zsifa_ */

/* Subroutine */ int zsisl_(doublecomplex *a, integer *lda, integer *n, 
	integer *kpvt, doublecomplex *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublecomplex z__1, z__2, z__3;

    /* Builtin functions */
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer k;
    static doublecomplex ak, bk;
    static integer kp;
    static doublecomplex akm1, bkm1, temp, denom;
    extern /* Double Complex */ VOID zdotu_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    extern /* Subroutine */ int zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);


/*     zsisl solves the complex*16 symmetric system */
/*     a * x = b */
/*     using the factors computed by zsifa. */

/*     on entry */

/*        a       complex*16(lda,n) */
/*                the output from zsifa. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*        kpvt    integer(n) */
/*                the pivot vector from zsifa. */

/*        b       complex*16(n) */
/*                the right hand side vector. */

/*     on return */

/*        b       the solution vector  x . */

/*     error condition */

/*        a division by zero may occur if  zsico  has set rcond .eq. 0.0 */
/*        or  zsifa  has set info .ne. 0  . */

/*     to compute  inverse(a) * c  where  c  is a matrix */
/*     with  p  columns */
/*           call zsifa(a,lda,n,kpvt,info) */
/*           if (info .ne. 0) go to ... */
/*           do 10 j = 1, p */
/*              call zsisl(a,lda,n,kpvt,c(1,j)) */
/*        10 continue */

/*     linpack. this version dated 08/14/78 . */
/*     james bunch, univ. calif. san diego, argonne nat. lab. */

/*     subroutines and functions */

/*     blas zaxpy,zdotu */
/*     fortran iabs */

/*     internal variables. */


/*     loop backward applying the transformations and */
/*     d inverse to b. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --kpvt;
    --b;

    /* Function Body */
    k = *n;
L10:
    if (k == 0) {
	goto L80;
    }
    if (kpvt[k] < 0) {
	goto L40;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L30;
    }
    kp = kpvt[k];
    if (kp == k) {
	goto L20;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L20:

/*              apply the transformation. */

    i__1 = k - 1;
    zaxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
L30:

/*           apply d inverse. */

    i__1 = k;
    z_div(&z__1, &b[k], &a[k + k * a_dim1]);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    --k;
    goto L70;
L40:

/*           2 x 2 pivot block. */

    if (k == 2) {
	goto L60;
    }
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k - 1) {
	goto L50;
    }

/*                 interchange. */

    i__1 = k - 1;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k - 1;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L50:

/*              apply the transformation. */

    i__1 = k - 2;
    zaxpy_(&i__1, &b[k], &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    i__1 = k - 2;
    zaxpy_(&i__1, &b[k - 1], &a[(k - 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
L60:

/*           apply d inverse. */

    z_div(&z__1, &a[k + k * a_dim1], &a[k - 1 + k * a_dim1]);
    ak.r = z__1.r, ak.i = z__1.i;
    z_div(&z__1, &a[k - 1 + (k - 1) * a_dim1], &a[k - 1 + k * a_dim1]);
    akm1.r = z__1.r, akm1.i = z__1.i;
    z_div(&z__1, &b[k], &a[k - 1 + k * a_dim1]);
    bk.r = z__1.r, bk.i = z__1.i;
    z_div(&z__1, &b[k - 1], &a[k - 1 + k * a_dim1]);
    bkm1.r = z__1.r, bkm1.i = z__1.i;
    z__2.r = ak.r * akm1.r - ak.i * akm1.i, z__2.i = ak.r * akm1.i + ak.i * 
	    akm1.r;
    z__1.r = z__2.r - 1., z__1.i = z__2.i;
    denom.r = z__1.r, denom.i = z__1.i;
    i__1 = k;
    z__3.r = akm1.r * bk.r - akm1.i * bk.i, z__3.i = akm1.r * bk.i + akm1.i * 
	    bk.r;
    z__2.r = z__3.r - bkm1.r, z__2.i = z__3.i - bkm1.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k - 1;
    z__3.r = ak.r * bkm1.r - ak.i * bkm1.i, z__3.i = ak.r * bkm1.i + ak.i * 
	    bkm1.r;
    z__2.r = z__3.r - bk.r, z__2.i = z__3.i - bk.i;
    z_div(&z__1, &z__2, &denom);
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    k += -2;
L70:
    goto L10;
L80:

/*     loop forward applying the transformations. */

    k = 1;
L90:
    if (k > *n) {
	goto L160;
    }
    if (kpvt[k] < 0) {
	goto L120;
    }

/*           1 x 1 pivot block. */

    if (k == 1) {
	goto L110;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotu_(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = kpvt[k];
    if (kp == k) {
	goto L100;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L100:
L110:
    ++k;
    goto L150;
L120:

/*           2 x 2 pivot block. */

    if (k == 1) {
	goto L140;
    }

/*              apply the transformation. */

    i__1 = k;
    i__2 = k;
    i__3 = k - 1;
    zdotu_(&z__2, &i__3, &a[k * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    i__1 = k + 1;
    i__2 = k + 1;
    i__3 = k - 1;
    zdotu_(&z__2, &i__3, &a[(k + 1) * a_dim1 + 1], &c__1, &b[1], &c__1);
    z__1.r = b[i__2].r + z__2.r, z__1.i = b[i__2].i + z__2.i;
    b[i__1].r = z__1.r, b[i__1].i = z__1.i;
    kp = (i__1 = kpvt[k], abs(i__1));
    if (kp == k) {
	goto L130;
    }

/*                 interchange. */

    i__1 = k;
    temp.r = b[i__1].r, temp.i = b[i__1].i;
    i__1 = k;
    i__2 = kp;
    b[i__1].r = b[i__2].r, b[i__1].i = b[i__2].i;
    i__1 = kp;
    b[i__1].r = temp.r, b[i__1].i = temp.i;
L130:
L140:
    k += 2;
L150:
    goto L90;
L160:
    return 0;
} /* zsisl_ */

