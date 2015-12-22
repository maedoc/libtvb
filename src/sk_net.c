/* Apache 2.0 INS-AMU 2015 */

#include <string.h> /* memcpy */

#include "sk_net.h"
#include "sk_malloc.h"

struct sk_net_data {
	int n, m, nnz, *M, *Ms, *Me, ns, ne, *Or, *Ic;
	double *w, *d, * restrict cn;
	sk_sys *models;
	void **models_data;
	/* flag for init1 use */
	int _init1;
};

sk_net_data *sk_net_alloc() {
	return sk_malloc (sizeof(sk_net_data));
}

SK_DEFSYS(sk_net_sys)
{
	int l, j, mi;
	double *xi, *fi, *gi, *ci;
	sk_net_data *d = data;

	/* unused arguments */
	(void) nx; (void) Jf; (void) Jg; (void) Jce; (void) nc;

	/* compute coupling 
	 *
	 * solver deals with c following Ic,d, but here we wanted ce
	 */
	for (l=0; l<d->ne; l++) 
		for (d->cn[l]=0.0, j=d->Or[l]; j<d->Or[l+1]; j++)
			/* c is len(ui), not ne! Ic[j] can't index it directly */
			d->cn[l] += c[sk_hist_get_vi2i(hist, d->Ic[j])] * d->w[j];

	/* evaluate system(s) */
	if (Jf==NULL) {
		for  (l=0, xi=x, fi=f, gi=g, ci=d->cn; l<d->n; l++, 
		      xi+=d->Ms[mi], fi+=d->Ms[mi], gi+=d->Ms[mi], ci+=d->Me[mi]) 
		{
			mi = d->M[l];
			(*(d->models[mi]))(d->models_data[mi], hist, t, i,
				d->Ms[mi], xi, fi, gi, NULL, NULL,
				d->Me[mi], ci, NULL);
		}
	} else {
		/* TODO evaluate & compute Jf/Jg/Jc 
		 * in net, we expect sys to evaluate only its own Jf/Jg, not whole.
		 * we are responsible for Jf/Jg ? or need Jc? Jca, Jce? 
		 *
		 * Jf/Jg include ca, i.e. [ df0/dx0 df0/dx1 .. df0/dca0 .. ] 
		 *
		 * may need Jc [ dce0/dx0 .. dce0/dca0 .. ]
		 *
		 * system defines Jf/Jg as block, we handle full network Jf/Jg
		 * which may be sparse if have large network.
		 * 
		 * assume sparse J by default: for small systems, penalty is small
		 * for large systems, need sparse; overall complexity is reduced.
		 */
	}
	/* compute coupling 
	 *
	 * solver deals with c following Ic,d, but here we wanted ce
	 * so we need to pack our cn into c.
	 */
	for (l=0; l<d->nnz; l++)
		c[l] = d->cn[d->Ic[l]];
	return 0;
}

struct sk_net_regmap_data {
	int i, *n;  /* n=1 for sum instead of averaging */
};

SK_DEFSYS(sk_net_regmap)
{
	int l;
	sk_net_regmap_data *d = data;
	/* unused arguments */
	(void) nx;(void) t; (void) Jf; (void) Jg; (void) Jce; (void) hist; (void) i;
	f[0] = 0.0;
	g[0] = 0.0;
	x[0] = 0.0;
	for (l=0; l<nc; l++)
		x[0] += c[l];
	c[0] = x[0] / d->n[d->i];
	return 0;
}

int sk_net_init1(sk_net_data *net, int n, sk_sys sys, void *data, 
		int ns, int ne, int nnz, int *Or, int *Ic, double *w, double *d)
{
	int i, *M, *Ms, *Me;
	sk_sys *models;
	void **model_data;
	M = sk_malloc (sizeof(int) * n);
	Ms = sk_malloc (sizeof(int));
	Me = sk_malloc (sizeof(int));
	models = sk_malloc (sizeof(sk_sys));
	model_data = sk_malloc (sizeof(void*));
	Ms[0] = ns;
	Me[0] = ne;
	for(i=0; i<n; i++)
		M[i] = 0;
	models[0] = sys;
	model_data[0] = data;
	sk_net_initn(net, n, 1, M, Ms, Me, models, model_data, nnz, Or, Ic, w, d);
	net->_init1 = 1;
	return 0;
}

void sk_net_free(sk_net_data *net)
{
	if (net->_init1) {
		sk_free(net->M);
		sk_free(net->Ms);
		sk_free(net->Me);
		sk_free(net->models);
		sk_free((void*) net->models_data);
		sk_free(net->cn);
	}
	sk_free(net);
}


int sk_net_initn(sk_net_data *net, int n, int m, 
		 int *M, int *Ms, int *Me, sk_sys *models, void **models_data,
		 int nnz, int *Or, int *Ic, double *w, double *d)
{
	int i;
	net->n = n;
	net->m = m;
	net->nnz = nnz;
	net->M = M;
	net->Ms = Ms;
	net->Me = Me;
	net->models = models;
	net->models_data = models_data;
	net->Or = Or;
	net->Ic = Ic; /* TODO ? same as Ie ? */
	net->w = w;
	net->d = d;
	/* intialize based on passed attributes: Ie, cne, cna */
	net->ns = 0;
	net->ne = 0;
	for (i=0; i<n; i++) {
		net->ns += net->Ms[net->M[i]];
		net->ne += net->Me[net->M[i]];
	}
	net->cn = sk_malloc (sizeof(double) * net->ne);
	net->_init1 = 0;
	return 0;
}

int sk_net_get_n(sk_net_data *net) {
	return net->n;
}

int sk_net_get_m(sk_net_data *net) {
	return net->m;
}

int sk_net_get_nnz(sk_net_data *net) {
	return net->nnz;
}

int *sk_net_get_or(sk_net_data *net) {
	return net->Or;
}

int sk_net_get_or_i(sk_net_data *net, int i) {
	return net->Or[i];
}

int *sk_net_get_ic(sk_net_data *net) {
	return net->Ic;
}

int sk_net_get_ic_i(sk_net_data *net, int i) {
	return net->Ic[i];
}

double *sk_net_get_w(sk_net_data *net) {
	return net->w;
}

double sk_net_get_w_i(sk_net_data *net, int i) {
	return net->w[i];
}

double *sk_net_get_d(sk_net_data *net) {
	return net->d;
}

double sk_net_get_d_i(sk_net_data *net, int i) {
	return net->d[i];
}

int sk_net_get_ns(sk_net_data *net) {
	return net->ns;
}

int sk_net_get_ne(sk_net_data *net) {
	return net->ne;
}

int sk_net_cn_is_null(sk_net_data *net) {
	return net->cn == NULL;
}

int sk_net_get_Ms_i(sk_net_data *net, int i) {
	return net->Ms[i];
}

int sk_net_get_Me_i(sk_net_data *net, int i) {
	return net->Me[i];
}

int sk_net_get_M_i(sk_net_data *net, int i) {
	return net->M[i];
}

sk_sys sk_net_get_models_i(sk_net_data *net, int i) {
	return net->models[i];
}

void *sk_net_get_models_data_i(sk_net_data *net, int i) {
	return net->models_data[i];
}

int sk_net_get__init1(sk_net_data *net) {
	return net->_init1;
}

