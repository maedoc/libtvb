/* copyright 2016 Apache 2 sddekit authors */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "weights.c"
#include "tract_lengths.c"

#include "sddekit.h"

struct {
    double tavg_kernel[20];
    struct sd_out_mem *mem;
    struct sd_out_conv *tavg;
    struct sd_out *until;
    struct sd_out_fork *fork;
    struct sd_out *mons[2];
} mon;

enum sd_stat
setup_mon()
{
    mon.mem = sd_out_mem_new();
    mon.tavg = sd_out_conv_new(20, mon.tavg_kernel, 20, mon.mem->as_out(mon.mem));
    mon.until = sd_out_new_until(1e3);
    mon.mons[0] = mon.tavg->as_out(mon.tavg);
    mon.mons[1] = mon.until;
    mon.fork = sd_out_fork_new(2, mon.mons);
    return mon.mem && mon.tavg && mon.until && mon.fork ? SD_OK : SD_ERR;
}

struct sd_net *net;

enum sd_stat
setup_net(struct sd_sys *node_sys, struct sd_conn *conn)
{
    uint32_t *sys_map = sd_malloc(76 * sizeof(uint32_t));
    struct sd_sys *sys[1];
    for (uint32_t i=0; i<76; i++)
        sys_map[i] = 0;
    sys[0] = node_sys;
    net = sd_net_new(76, 1, sys_map, sys, conn);
    if (net == NULL)
        return SD_ERR;
    return SD_OK;
}

int main()
{
    uint32_t n = 76;

	if (setup_mon() != SD_OK)
    {
        sd_err("mon setup failed.");
        return 1;
    }

	/* connectivity, assuming conduction velocity of 1.0 */
    struct sd_conn *conn = sd_conn_new_dense(n, n, weights, tract_lengths);
    sd_log_info("conn has %d nonzeros.", conn->get_n_nonzero(conn));

	/* setup model */
    struct sd_sys_gen2d *g2d = sd_sys_gen2d_new();
    g2d->set_a(g2d, 0.0);
    
    /* setup network */
    if (setup_net(g2d->as_sys(g2d), conn) != SD_OK)
    {
        sd_err("setup network failed.");
        return 1;
    }
    
	/* setup scheme & solver */

    struct sd_hist *hist = sd_hist_new_linterp(conn->get_n_nonzero(conn),
        conn->get_nonzero_indices(conn), conn->get_delays(conn), 0.0, 0.1);
    struct sd_hfill *hfill = sd_hfill_new_val(0.0);
    hist->fill(hist, hfill);
    struct sd_rng *rng = sd_rng_new_mt(42);
	struct sd_sch *heun = sd_sch_new_heun(0.0, 0.1,
        net->as_sys(net), hist, rng);

    /* construct initial conditions, solver & run it */
 	double *x0 = sd_malloc(sizeof(double)*2*n);
	for (uint32_t i=0; i<(2*n); i++)
		x0[i] = 0.0;       
    struct sd_sol *sol = sd_sol_new_default(
        0.0, x0, heun, mon.fork->as_out(mon.fork));

	sol->cont(sol);
    
    /* let OS clean up */
	return 0;
}
