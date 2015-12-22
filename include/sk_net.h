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

#ifdef __cplusplus
extern "C" {
#endif
typedef struct sk_net_data sk_net_data;

/**
 * Allocate memory for a network.
 */
sk_net_data *sk_net_alloc();

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
 * Get number of nodes in network.
 *
 * \param net network instance.
 */
int sk_net_get_n(sk_net_data *net);

/**
 * Get number of models in network.
 *
 * \param net network instance.
 */
int sk_net_get_m(sk_net_data *net);

/**
 * Get number of non-zero weights and delays in network.
 *
 * \param net network instance.
 */
int sk_net_get_nnz(sk_net_data *net);

/**
 * Get non-zero row offset vector.
 *
 * \param net network instance.
 */
int *sk_net_get_or(sk_net_data *net);

/**
 * Get i'th non-zero row offset.
 *
 * \param net network instance.
 * \param i index
 */
int sk_net_get_or_i(sk_net_data *net, int i);

/**
 * Get non-zero column index vector.
 *
 * \param net network instance.
 */
int *sk_net_get_ic(sk_net_data *net);

/**
 * Get i'th non-zero column index.
 *
 * \param net network instance.
 * \param i index
 */
int sk_net_get_ic_i(sk_net_data *net, int i);

/**
 * Get non-zero weight vector.
 *
 * \param net network instance.
 */
double *sk_net_get_w(sk_net_data *net);

/**
 * Get the i'th non-zero weight.
 *
 * \param net network instance.
 */
double sk_net_get_w_i(sk_net_data *net, int i);

/**
 * Get non-zero delay vector.
 *
 * \param net network instance.
 */
double *sk_net_get_d(sk_net_data *net);

/**
 * Get the i'th non-zero delay.
 *
 * \param net network instance.
 */
double sk_net_get_d_i(sk_net_data *net, int i);

/**
 * Get total number of state variables in network.
 *
 * \param net network instance.
 */
int sk_net_get_ns(sk_net_data *net);

/**
 * Get total number of efferent variables in network.
 *
 * \param net network instance.
 */
int sk_net_get_ne(sk_net_data *net);

/**
 * Get NULL status of cn
 * \note provided for unit testing.
 * \param net network instance.
 */
int sk_net_cn_is_null();

/**
 * Get number of state variables fot the i'th model.
 *
 * \param net network instance.
 * \param i index
 */
int sk_net_get_Ms_i(sk_net_data *net, int i);

/**
 * Get number of efferent variables fot the i'th model.
 *
 * \param net network instance.
 * \param i index
 */
int sk_net_get_Me_i(sk_net_data *net, int i);

/**
 * Get model index for i'th node.
 *
 * \param net network instance.
 * \param i index
 */
int sk_net_get_M_i(sk_net_data *net, int i);

/**
 * Get i'th model's callback (i.e. function pointer).
 *
 * \param net network instance.
 * \param i index
 */
sk_sys sk_net_get_models_i(sk_net_data *net, int i);

/**
 * Get i'th model's user data.
 *
 * \param net network instance.
 * \param i index
 */
void *sk_net_get_models_data_i(sk_net_data *net, int i);

int sk_net_get__init1();

/**
 * Handles region mapping in case of surface simulation.
 */
SK_DEFSYS(sk_net_regmap);

typedef struct sk_net_regmap_data sk_net_regmap_data;

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
