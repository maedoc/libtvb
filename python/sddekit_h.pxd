# copyright 2016 Apache 2 sddekit authors

# This file provides the Cython declarations for the C library
# defined in the C header. If you want to use the Cython types
# from Cython code, see sddekit.pxd.

cdef extern from "sddekit.h":

    # stat enum {{{
    ctypedef enum sd_stat:
        SD_OK
        SD_ERR
        SD_CONT
        SD_STOP
    # }}}

    # util {{{
    sd_stat sd_util_read_square_matrix(char *fname, uint32_t *n, double **w)

    sd_stat sd_util_uniqi(uint32_t n,
                  uint32_t * restrict ints, 
                  uint32_t * restrict nuniq, 
                  uint32_t **uints)
    # }}}

    # rng {{{
    ctypedef struct sd_rng:
        void *ptr
        void (*seed)(sd_rng*, uint32_t seed)
        double (*norm)(sd_rng*)
        void (*fill_norm)(sd_rng*, uint32_t n, double *x)
        uint32_t (*nbytes)(sd_rng*)
        void (*free)(sd_rng*)

    sd_rng * sd_rng_new_default()
    # }}}

    # hfill {{{
    ctypedef struct sd_hfill:
        void *ptr
        sd_stat (*apply)(sd_hfill*, uint32_t n, double * t, uint32_t *indices, double * buf)
        void (*free)(sd_hfill*)

    sd_hfill * sd_hfill_new_val(double val)
    # }}}

    # hist {{{
    ctypedef struct sd_hist:
        uint32_t(*get_maxvi)(sd_hist*)
        uint32_t(*get_vi2i)(sd_hist*, uint32_t vi)
        uint32_t(*get_nu)(sd_hist *h)
        void (*free)(sd_hist *h)
        sd_stat (*fill)(sd_hist *h, sd_hfill *filler)
        void (*get)(sd_hist *h, double t, double *aff)
        void (*set)(sd_hist *h, double t, double *eff)
        uint32_t (*nbytes)(sd_hist *h)
        double (*get_buf_lin)(sd_hist *h, uint32_t index)
        uint32_t (*get_nd)(sd_hist *h)
        double (*get_t)(sd_hist *h)
        double (*get_dt)(sd_hist *h)
        uint32_t (*get_lim)(sd_hist *h, uint32_t i)
        uint32_t (*get_len)(sd_hist *h, uint32_t i)
        uint32_t (*get_pos)(sd_hist *h, uint32_t i)
        uint32_t (*get_uvi)(sd_hist *h, uint32_t i)
        double (*get_maxd)(sd_hist *h, uint32_t i)
        uint32_t (*get_vi)(sd_hist *h, uint32_t i)
        double (*get_vd)(sd_hist *h, uint32_t i)

    sd_hist * sd_hist_new_default(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)
    # }}}

    # sys {{{
    ctypedef struct sd_sys:
        uint32_t (*ndim)(sd_sys*)
        uint32_t (*ndc)(sd_sys*)
        uint32_t (*nobs)(sd_sys*)
        uint32_t (*nrpar)(sd_sys*)
        uint32_t (*nipar)(sd_sys*)
        sd_stat (*apply)(sd_sys*, sd_sys_in*, sd_sys_out*)
        void (*free)(sd_sys*)
        void *ptr
    ctypedef struct sd_sys_in:
        uint32_t nx, nc, id
        double t, *x, *i 
        sd_hist *hist
        sd_rng *rng
    ctypedef struct sd_sys_out:
        double *f, *g, *o
    # sys }}}

    # net {{{
    ctypedef struct sd_net:
	sd_sys * ( * sys)(sd_net *d)
        void (*free)(sd_net *d)
        uint32_t (*get_n)(sd_net *net)
        uint32_t (*get_m)(sd_net *net)
        uint32_t (*get_nnz)(sd_net *net)
        uint32_t *(*get_or)(sd_net *net)
        uint32_t (*get_or_i)(sd_net *net, uint32_t i)
        uint32_t *(*get_ic)(sd_net *net)
        uint32_t (*get_ic_i)(sd_net *net, uint32_t i)
        double *(*get_w)(sd_net *net)
        double (*get_w_i)(sd_net *net, uint32_t i)
        double *(*get_d)(sd_net *net)
        double (*get_d_i)(sd_net *net, uint32_t i)
        uint32_t (*get_ns)(sd_net *net)
        uint32_t (*get_ne)(sd_net *net)
        bool (*cn_is_null)(sd_net *net)
        uint32_t (*get_Ms_i)(sd_net *net, uint32_t i)
        uint32_t (*get_Ma_i)(sd_net *net, uint32_t i)
        uint32_t (*get_Me_i)(sd_net *net, uint32_t i)
        uint32_t (*get_M_i)(sd_net *net, uint32_t i)
        sd_sys * (*get_models_i)(sd_net *net, uint32_t i)
	bool (*get__init1)(sd_net *net)
        sd_net*
        sd_net_new_het(uint32_t n, uint32_t m, uint32_t * M, uint32_t * Ms, 
	       uint32_t * Ma, uint32_t * Me, 
	       sd_sys **models,
	       uint32_t nnz, uint32_t * Or, uint32_t * Ic, 
               double * w, double * d)
        sd_net * sd_net_new_hom(uint32_t n, sd_sys *sys,
                uint32_t ns, uint32_t na, uint32_t ne, uint32_t nnz, 
                uint32_t * Or,
                uint32_t * Ic, 
                double * w,
                double * d)
    # net }}}

# vim: sw=4 et foldmethod=marker
