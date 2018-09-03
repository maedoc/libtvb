/* copyright 2016 Apache 2 libtvb authors */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "weights.c"
#include "tract_lengths.c"

#include "libtvb.h"

struct {
    double tavg_kernel[20];
    struct tvb_out_mem *mem;
    struct tvb_out_conv *tavg;
    struct tvb_out *until;
    struct tvb_out_fork *fork;
    struct tvb_out *mons[2];
} mon;

enum tvb_stat
setup_mon()
{
    mon.mem = tvb_out_mem_new();
    mon.tavg = tvb_out_conv_new(20, mon.tavg_kernel, 20, mon.mem->as_out(mon.mem));
    mon.until = tvb_out_new_until(1e3);
    mon.mons[0] = mon.tavg->as_out(mon.tavg);
    mon.mons[1] = mon.until;
    mon.fork = tvb_out_fork_new(2, mon.mons);
    return mon.mem && mon.tavg && mon.until && mon.fork ? TVB_OK : TVB_ERR;
}

struct tvb_net *net;

enum tvb_stat
setup_net(struct tvb_sys *node_sys, struct tvb_conn *conn)
{
    uint32_t *sys_map = tvb_malloc(76 * sizeof(uint32_t));
    struct tvb_sys *sys[1];
    for (uint32_t i=0; i<76; i++)
        sys_map[i] = 0;
    sys[0] = node_sys;
    net = tvb_net_new(76, 1, sys_map, sys, conn);
    if (net == NULL)
        return TVB_ERR;
    return TVB_OK;
}

int main()
{
    uint32_t n = 76;

	if (setup_mon() != TVB_OK)
    {
        tvb_err("mon setup failed.");
        return 1;
    }

	/* connectivity, assuming conduction velocity of 1.0 */
    struct tvb_conn *conn = tvb_conn_new_dense(n, n, weights, tract_lengths);
    tvb_log_info("conn has %d nonzeros.", conn->get_n_nonzero(conn));

	/* setup model */
    struct tvb_sys_gen2d *g2d = tvb_sys_gen2d_new();
    g2d->set_a(g2d, 0.0);
    
    /* setup network */
    if (setup_net(g2d->as_sys(g2d), conn) != TVB_OK)
    {
        tvb_err("setup network failed.");
        return 1;
    }
    
	/* setup scheme & solver */

    struct tvb_hist *hist = tvb_hist_new_linterp(conn->get_n_nonzero(conn),
        conn->get_nonzero_indices(conn), conn->get_delays(conn), 0.0, 0.1);
    struct tvb_hfill *hfill = tvb_hfill_new_val(0.0);
    hist->fill(hist, hfill);
    struct tvb_rng *rng = tvb_rng_new_mt(42);
	struct tvb_sch *heun = tvb_sch_new_heun(0.0, 0.1,
        net->as_sys(net), hist, rng);

    /* construct initial conditions, solver & run it */
 	double *x0 = tvb_malloc(sizeof(double)*2*n);
	for (uint32_t i=0; i<(2*n); i++)
		x0[i] = 0.0;       
    struct tvb_sol *sol = tvb_sol_new_default(
        0.0, x0, heun, mon.fork->as_out(mon.fork));

	sol->cont(sol);
    
    /* let OS clean up */
	return 0;
}
