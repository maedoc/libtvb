/* Apache 2.0 INS-AMU 2015 */

#include <string.h> /* memcpy */

#include "sk_net.h"
#include "sk_util.h" /* SK_MALLOCHECK */


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
			d->cn[l] += c[hist->vi2i[d->Ic[j]]] * d->w[j];

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
	SK_MALLOCHECK(M = malloc (sizeof(int) * n));
	SK_MALLOCHECK(Ms = malloc (sizeof(int)));
	SK_MALLOCHECK(Me = malloc (sizeof(int)));
	SK_MALLOCHECK(models = malloc (sizeof(sk_sys)));
	SK_MALLOCHECK(model_data = malloc (sizeof(void*)));
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
		free(net->M);
		free(net->Ms);
		free(net->Me);
		free(net->models);
		free((void*) net->models_data);
		free(net->cn);
	}
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
	SK_MALLOCHECK(net->cn = malloc (sizeof(double) * net->ne));
	net->_init1 = 0;
	return 0;
}
