/* copyright 2016 Apache 2 sddekit authors */

#ifndef SK_CONFIG_H
#define SK_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get compile-time major version number.
 */
int sk_ver_major ();

/**
 * Get compile-time minor version number.
 */
int sk_ver_minor ();

/**
 * Get compile-time Git revision.
 */
const char *sk_git_rev ();

/**
 * Get compile-time resource directory.
 */
const char *sk_res_dir ();

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
