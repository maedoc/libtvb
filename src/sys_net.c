/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	uint32_t n_node, n_subsys, *node_subsys_map;
	double *aff;
	struct sd_sys sys;
	struct sd_net net;
	struct sd_conn *conn;
	struct sd_sys **subsys;
	struct {
		uint32_t ndim, ndc, nobs, nrpar, nipar;
	} sys_counts;
};

void data_free(struct data *d)
{
	sd_free(d->subsys);
	sd_free(d->aff);
	sd_free(d);
}

static void update_sys_counts(struct data *d)/*{{{*/
{
	d->sys_counts.nobs = 0;
	d->sys_counts.ndc = 0;
	d->sys_counts.ndim = 0;
	d->sys_counts.nrpar = 0;
	d->sys_counts.nipar = 0;
	for (uint32_t i=0; i<d->n_node; i++)
	{
		struct sd_sys *s = d->subsys[d->node_subsys_map[i]];
		d->sys_counts.nobs += s->nobs(s);
		d->sys_counts.ndc += s->ndc(s);
		d->sys_counts.ndim += s->ndim(s);
		d->sys_counts.nrpar += s->nrpar(s);
		d->sys_counts.nipar += s->nipar(s);
	}
}/*}}}*/

/* accessors {{{ */
static struct sd_sys * net_sys(struct sd_net *net)
{
	return &((struct data *) net->ptr)->sys;
}

static struct sd_conn * net_get_conn(struct sd_net *net)
{
	return ((struct data *) net->ptr)->conn;
}

static void net_free(struct sd_net *net)
{
	data_free(net->ptr);
}

static uint32_t net_get_n_node(struct sd_net *net)
{
	return ((struct data *) net->ptr)->n_node;
}

static uint32_t net_get_n_sub_sys(struct sd_net *net)
{
	return ((struct data *) net->ptr)->n_subsys;
}

static struct sd_sys * net_get_subsys(struct sd_net *net, uint32_t i)
{
	return ((struct data *) net->ptr)->subsys[i];
}

static enum sd_stat net_set_subsys(struct sd_net *net, uint32_t i_sys, struct sd_sys *sys)
{
	struct data *data = net->ptr;
	data->subsys[i_sys] = sys;
	update_sys_counts(data);
	return SD_OK;
}

static uint32_t net_get_node_subsys(struct sd_net *net, uint32_t i_node)
{
	return ((struct data *) net->ptr)->node_subsys_map[i_node];
}

static enum sd_stat net_set_node_subsys(struct sd_net *net, uint32_t i_node, uint32_t i_sys)
{
	struct data *data = net->ptr;
	data->node_subsys_map[i_node] = i_sys;
	update_sys_counts(data);
	return SD_OK;
}
/* }}} */

/* sys impl {{{ */
#define GET_COUNT(name) \
static uint32_t sys_ ## name(struct sd_sys *sys) \
{ \
	return ((struct data *) sys->ptr)->sys_counts.name;\
}

GET_COUNT(ndim)
GET_COUNT(ndc)
GET_COUNT(nobs)
GET_COUNT(nrpar)
GET_COUNT(nipar)

#undef GET_COUNT

static void sys_free(struct sd_sys *sys)
{
	data_free(sys->ptr);
}

/* }}} */

/* sys apply impl {{{ */

static enum sd_stat sys_apply(struct sd_sys *sys, 
		struct sd_sys_in *in, struct sd_sys_out *out)
{
	struct data *data = sys->ptr;
	struct sd_conn *conn = data->conn;
	struct sd_sys_in in_i = *in;
	struct sd_sys_out out_i = *out;
	/* apply weights to delayed data, use result as input to subsystems */
	conn->row_wise_weighted_sum(conn, in->i, data->aff);
	in_i.i = data->aff;
	/* apply each subsys to its section */
	for (uint32_t i_node=0; i_node<data->n_node; i_node++)
	{
		struct sd_sys *subsys = data->subsys[data->node_subsys_map[i_node]];
		enum sd_stat stat = subsys->apply(subsys, &in_i, &out_i);
		if (stat != SD_OK)
			return stat;
		uint32_t ndim = subsys->ndim(subsys);
		in_i.x += ndim;
		out_i.f += ndim;
		out_i.g += ndim;
		in_i.i += subsys->ndc(subsys);
		out_i.o += subsys->nobs(subsys);
	}
	return SD_OK;
}

/* }}} */

/* initialization {{{ */

static bool incompat_subsys_and_conn(struct data *data, struct sd_conn *conn)
{
	uint32_t ndc  = data->sys_counts.ndc
	       , nobs = data->sys_counts.nobs
	       , n_rows = conn->n_rows(conn)
	       , n_cols = conn->n_cols(conn)
	       ;

	if (ndc != n_rows || nobs != n_cols)
	{
		sd_log_info("ndc=%d != n_rows=%d || nobs=%d != n_cols=%d",
			    ndc, n_rows, nobs, n_cols);
		return false;
	}
	return true;
}

/* TODO refactor */
static uint32_t count_aff(uint32_t n, uint32_t *node_subsys_map, struct sd_sys **subsys)
{
	uint32_t aff = 0;
	for (uint32_t i=0; i<n; i++)
	{
		struct sd_sys *sub = subsys[node_subsys_map[i]];
		aff += sub->ndc(sub);
	}
	return aff;
}

struct sd_net *
sd_net_new(uint32_t n_node, uint32_t n_subsys, uint32_t *node_subsys_map, 
	   struct sd_sys **subsys,
	   struct sd_conn *conn)
{
	struct data *data, zero = {0};
	uint32_t n_aff = count_aff(n_node, node_subsys_map, subsys);
	if ((data = sd_malloc(sizeof(struct data))) == NULL
	 || (*data = zero, 0)
	 || (data->aff = sd_malloc(sizeof(double)*n_aff)) == NULL
	 )
	{
		if (data!=NULL)
			sd_free(data);
		sd_err("alloc net failed.");
		return NULL;
	}
	data->n_node = n_node;
	data->n_subsys = n_subsys;
	data->sys = {&sys_ndim, &sys_ndc, &sys_nobs, &sys_nrpar, &sys_nipar,
		     &sys_apply, &sys_free, data};
	data->net = {data, &net_sys, &net_get_conn, &net_free,
		     &net_get_n_node, &net_get_n_sub_sys, &net_get_subsys,
		     &net_set_subsys, &net_get_node_subsys, &net_set_node_subsys};
	data->conn = conn;
	update_sys_counts(&data->sys);
	return &data->net;
}

/* }}} */

/* vim: foldmethod=marker
 */
