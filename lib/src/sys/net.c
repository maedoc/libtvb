/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	uint32_t n_node, n_subsys, *node_subsys_map;
	double *aff;
	struct sd_sys sd_sys;
	struct sd_net sd_net;
	struct sd_conn *conn;
	struct sd_sys **subsys;
	struct {
		uint32_t n_dim, n_in, n_out, n_rpar, n_ipar;
	} sys_counts;
};

/* obj free n byte copy */

static void data_free(struct data *data)
{
	sd_free(data->subsys);
	sd_free(data->aff);
	sd_free(data);
}

static uint32_t data_n_byte(struct data *data)
{
    uint32_t byte_count = sizeof(struct data);
    byte_count += data->sys_counts.n_in * sizeof(double);
    byte_count += data->n_subsys * sizeof(struct sd_sys *);
    return byte_count;
}

static struct data *data_copy(struct data *data)
{
    struct data *copy = sd_net_new(
        data->n_node, data->n_subsys, data->node_subsys_map,
        data->subsys, data->conn)->data;
    if (copy == NULL)
        sd_err("alloc net copy failed.");
    return copy;
}

sd_declare_tag_functions(sd_sys)
sd_declare_tag_functions(sd_net)

static void update_sys_counts(struct data *data)
{
	data->sys_counts.n_out = 0;
	data->sys_counts.n_in = 0;
	data->sys_counts.n_dim = 0;
	data->sys_counts.n_rpar = 0;
	data->sys_counts.n_ipar = 0;
	for (uint32_t i=0; i<data->n_node; i++)
	{
		struct sd_sys *sys = data->subsys[data->node_subsys_map[i]];
		data->sys_counts.n_out += sys->get_n_out(sys);
		data->sys_counts.n_in += sys->get_n_in(sys);
		data->sys_counts.n_dim += sys->get_n_dim(sys);
		data->sys_counts.n_rpar += sys->get_n_rpar(sys);
		data->sys_counts.n_ipar += sys->get_n_ipar(sys);
	}
}

static struct sd_sys * as_sys(struct sd_net *net) { return &((struct data *) net->data)->sd_sys; }

static struct sd_conn * net_get_conn(struct sd_net *net) { return ((struct data *) net->data)->conn; }

static uint32_t net_get_n_node(struct sd_net *net) { return ((struct data *) net->data)->n_node; }

static uint32_t net_get_n_sub_sys(struct sd_net *net) { return ((struct data *) net->data)->n_subsys; }

static struct sd_sys * net_get_subsys(struct sd_net *net, uint32_t i) { return ((struct data *) net->data)->subsys[i]; }

static enum sd_stat net_set_subsys(struct sd_net *net, uint32_t i_sys, struct sd_sys *sys)
{
	struct data *data = net->data;
	data->subsys[i_sys] = sys;
	update_sys_counts(data);
	return SD_OK;
}

static uint32_t net_get_node_subsys(struct sd_net *net, uint32_t i_node) { return ((struct data *) net->data)->node_subsys_map[i_node]; }

static enum sd_stat net_set_node_subsys(struct sd_net *net, uint32_t i_node, uint32_t i_sys)
{
	struct data *data = net->data;
	data->node_subsys_map[i_node] = i_sys;
	update_sys_counts(data);
	return SD_OK;
}
/* }}} */

/* sys impl {{{ */
#define GET_COUNT(name) \
static uint32_t sys_ ## name(struct sd_sys *sys) \
{ \
	return ((struct data *) sys->data)->sys_counts.name;\
}

GET_COUNT(n_dim)
GET_COUNT(n_in)
GET_COUNT(n_out)
GET_COUNT(n_rpar)
GET_COUNT(n_ipar)

#undef GET_COUNT


/* sys apply impl */

static enum sd_stat sys_apply(struct sd_sys *sys, 
		struct sd_sys_in *in, struct sd_sys_out *out)
{
	struct data *data = sys->data;
	struct sd_conn *conn = data->conn;
	struct sd_sys_in in_i = *in;
	struct sd_sys_out out_i = *out;
	/* apply weights to delayed data, use result as input to subsystems */
	conn->row_wise_weighted_sum(conn, in->input, data->aff);
	in_i.input = data->aff;
	/* apply each subsys to its section */
    /* TODO omp parallel for */
	for (uint32_t i_node=0; i_node<data->n_node; i_node++)
	{
		struct sd_sys *subsys = data->subsys[data->node_subsys_map[i_node]];
        in_i.id = i_node;
        in_i.n_dim = subsys->get_n_dim(subsys);
        in_i.n_in = subsys->get_n_in(subsys);
        in_i.n_out = subsys->get_n_out(subsys);
		enum sd_stat stat = subsys->apply(subsys, &in_i, &out_i);
		if (stat != SD_OK)
			return stat;
		in_i.state += in_i.n_dim;
		out_i.drift += in_i.n_dim;
		out_i.diffusion += in_i.n_dim;
		in_i.input += in_i.n_in;
		out_i.output += in_i.n_out;
	}
	return SD_OK;
}

static bool incompat_subsys_and_conn(struct data *data, struct sd_conn *conn)
{
	uint32_t n_in  = data->sys_counts.n_in
	       , n_out = data->sys_counts.n_out
	       , n_rows = conn->get_n_row(conn)
	       , n_cols = conn->get_n_col(conn)
	       ;

	if (n_in != n_rows || n_out != n_cols)
	{
		sd_log_info(
                "incompatible subsys & connectivity "
                "(n_in=%d != n_rows=%d || n_out=%d != n_cols=%d)",
			    n_in, n_rows, n_out, n_cols);
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
		aff += sub->get_n_in(sub);
	}
	return aff;
}

static struct sd_sys sd_sys_defaults = {
    sd_declare_tag_vtable(sd_sys),
    .get_n_dim = &sys_n_dim,
    .get_n_in = &sys_n_in,
    .get_n_out = &sys_n_out,
    .get_n_rpar = &sys_n_rpar,
    .get_n_ipar = &sys_n_ipar,
    .apply = sys_apply
};

static struct sd_net sd_net_defaults = {
    sd_declare_tag_vtable(sd_net),
    .as_sys = &as_sys,
    .get_conn = &net_get_conn,
    .get_n_node = &net_get_n_node,
    .get_n_subsys = &net_get_n_sub_sys,
    .get_subsys = &net_get_subsys,
    .set_subsys = &net_set_subsys,
    .get_node_subsys = &net_get_node_subsys,
    .set_node_subsys = &net_set_node_subsys
};

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
     || (data->node_subsys_map = sd_malloc(sizeof(uint32_t) * n_node)) == NULL
     || (data->subsys = sd_malloc(sizeof(struct sd_sys *) * n_subsys)) == NULL
     || incompat_subsys_and_conn(data, conn)
	 )
	{
        if (data->aff != NULL) sd_free(data->aff);
        if (data->node_subsys_map != NULL) sd_free(data->node_subsys_map);
        if (data->subsys != NULL) sd_free(data->subsys);
		if (data != NULL) sd_free(data);
		sd_err("alloc net failed.");
		return NULL;
	}
	data->n_node = n_node;
	data->n_subsys = n_subsys;
    memcpy(data->node_subsys_map, node_subsys_map, sizeof(uint32_t) * n_node);
    data->sd_sys = sd_sys_defaults;
    data->sd_net = sd_net_defaults;
    data->sd_sys.data = data->sd_net.data = data; 
	data->conn = conn;
    memcpy(data->subsys, subsys, sizeof(struct sd_sys *) * n_subsys);
	update_sys_counts(data);
	return &data->sd_net;
}