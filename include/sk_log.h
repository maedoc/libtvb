/* Apache 2.0 INS-AMU 2015 */

/**
 * \file sk_log.h implements handlers for information, debugging output
 * and error messages. Messages may be redirected to custom handlers.
 */

#ifndef SK_LOG_H
#define SK_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Type definition for callback handling formatted messages.
 */
typedef int (*sk_log_msg_fp)(const char * __restrict fmt, ...);

extern sk_log_msg_fp sk_log_msg;

/**
 * Get function pointer handling messages.
 */
sk_log_msg_fp sk_log_get_msg();

/**
 * Set function pointer handling messages.
 */
void sk_log_set_msg(sk_log_msg_fp fp);

/**
 * Get status of quiet flag.
 */
int sk_log_get_quiet();

/**
 * Set status of quiet flag.
 */
void sk_log_set_quiet(int flag);

/**
 * Get status of verbose flag.
 */
int sk_log_get_verbose();

/**
 * Set status of verbose flag.
 */
void sk_log_set_verbose(int flag);

#define sk_log_info(fmt, ...) if (!sk_log_get_quiet()) \
	sk_log_msg("[INFO] %s:%d " fmt "\n", __FILE__, __LINE__, ## __VA_ARGS__)

#define sk_log_debug(fmt, ...) if (sk_log_get_verbose()) \
	sk_log_msg("[DEBUG] %s:%d " fmt "\n", __FILE__, __LINE__, ## __VA_ARGS__)

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
