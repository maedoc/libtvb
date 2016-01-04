/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* write data to file */

typedef struct file_data {
	sd_out out_if;
	sd_out_file file_if;
	FILE *fd;
	bool isstd;
} file_data;

static sd_stat
file_apply(sd_out *out, double t, 
		   uint32_t nx, double * restrict x,
		   uint32_t nc, double * restrict c)
{
	uint32_t i;
	file_data *d = out->ptr;
	fprintf(d->fd, "%f %d ", t, nx);
	for (i=0; i<nx; i++) 
		fprintf(d->fd, "%f ", x[i]);
	fprintf(d->fd, "%d ", nc);
	for (i=0; i<nc; i++) 
		fprintf(d->fd, "%f ", c[i]);
	fprintf(d->fd, "\n");
	return SD_CONT;
}

static void
file_free(sd_out *out) 
{
	file_data *d = out->ptr;
	if (!(d->isstd))
		fclose(d->fd);
	sd_free(d);
}

static bool
file_is_std(sd_out_file *file) 
{
	return ((file_data*)file->ptr)->isstd;
}

static sd_out *
out_from_file(sd_out_file *file)
{
	return &(((file_data*)file->ptr)->out_if);
}

static FILE *
file_get_fd(sd_out_file *file)
{
	return ((file_data*)file->ptr)->fd;
}

static sd_out 
file_out_defaults = { .free = &file_free, .apply = &file_apply };

static sd_out_file 
file_defaults = { .out = &out_from_file,.is_std = &file_is_std,.get_fd = &file_get_fd };

static sd_out_file *
sd_out_file_new(FILE *file, bool is_std)
{
	file_data *d;
	d = sd_malloc (sizeof(file_data));
	if (d == NULL)
	{
		sd_err("alloc out file failed.");
		return NULL;
    }
	{
		file_data zero = { 0 };
		*d = zero;
	}
	d->fd = file;
	d->isstd = is_std;
	d->file_if = file_defaults;
	d->out_if = file_out_defaults;
	d->file_if.ptr = d->out_if.ptr = d;
	return &(d->file_if);
}

sd_out_file *
sd_out_file_new_from_name(char *fname) 
{
	FILE *file;
	if ((file = fopen(fname, "w"))==NULL) 
	{
		sd_err("unable to open file for writing.");
		return NULL;
	}
	return sd_out_file_new(file, false);
}

sd_out_file *
sd_out_file_new_from_std(FILE *std) 
{
	return sd_out_file_new(std, true);
}
