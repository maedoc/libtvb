/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_NET_H
#define SK_NET_H

/**
 * \file sk_net.h
 *
 * \brief sk_net provides a sk_sys which adapts another sk_sys into a network.
 *
 * The solver & scheme sees the network as just another 
 * system to solve, and the network structure is handled here, not in the
 * solver.
 *
 * We consider in general n nodes and m mass models. The i'th node has model 
 * M[i], with Ms[i] state variables and Me[i] efferent variables. ns = 
 * sum(Ms[i],i,1,n) is the total number of state variables, and ne = 
 * sum(Me[i],i,1,n) respectively efferent variables. x in R^ns is the 
 * state of the network, and ce in R^ne the efferent activity.
 *
 * Connectivity in the network is a sparse R^ne x R^ne matrix, where
 * w in R^nnz is the non-zero weights and d in R^nnz
 * the delays. The non-zero elements are located by Or in N^(n+1) row 
 * offsets and Ic in N^nnz column indices, in so-called CSR format.
 * 
 * The historian requires Ic in N^nnz indices on ce, and 
 * d in R^nnz delay vector, also passed for initializing a network.
 *
 * Computing net afferent cna in R^ne from sys aff ca in R^nnz following
 * the sparse connectivity.
 * 
 * scheme provides ca from history, expects ce, we need to map these
 * sparse needs n, row offsets col indices and data
 */



#include <stdlib.h>

#include "sk_sys.h"
#include "sk_util.h"

typedef struct {
	int n, m, nnz, *M, *Ms, *Me, ns, ne, *Or, *Ic;
	double *w, *d, * restrict cn;
	sk_sys *models;
	void * restrict * restrict models_data;
	/* flag for init1 use */
	int _init1;
} sk_net_data;

/**
 * Init network for general case of heterogeneous network of nm different models
 *
 * \note Further use requires filling data structures.
 *
 * \param d network to initialize.
 * \param n number of nodes in network.
 * \param m number of models used in network.
 * \param nnz number of non-zero elements in weights matrix.
 * \param w array of non-zero elements of weights matrix.
 * \param d array of delays per non-zero weight
 * \return 0 on success, 1 otherwise
 */
int sk_net_initn(sk_net_data * restrict net, int n, int m, 
		 int *M, int *Ms, int *Me, sk_sys *models, void **models_data,
		 int nnz, int *Or, int *Ic, double *w, double *d);

/**
 * Free internal memory used by a network,
 *
 * \note assumes each of the node data themselves have been freed.
 *
 * \param d network data
 */
void sk_net_free(sk_net_data *d);

/**
 * Init network for homogeneous model case where m==1, simplifying setup.
 *
 * \param net network to initialize.
 * \param n number of nodes in network.
 * \param sys model system to use.
 * \param data user data for system.
 * \param ns number of state variables for system.
 * \param ne number of efferent terms for system.
 * \param nnz number of non-zero elements in weights matrix.
 * \param Or array of row offsets in non-zero arrays.
 * \param Ic array of column indices in non-zero arrays.
 * \param w array of non-zero elements of weights matrix.
 * \param d array of delays per non-zero weight
 * \return 0 on success, 1 otherwise
 */
int sk_net_init1(sk_net_data *net, int n, sk_sys sys, void * data, 
		 int ns, int ne, int nnz, int *Or, int *Ic, double *w, double *d);

/**
 * connectivity is ce x ce, but provide api for setting node by node as well
 */

SK_DEFSYS(sk_net_sys);

/**
 * Handles region mapping in case of surface simulation.
 */
typedef struct {
	int i, *n;  /* n=1 for sum instead of averaging */
} sk_net_regmap_data;

SK_DEFSYS(sk_net_regmap);

#endif
