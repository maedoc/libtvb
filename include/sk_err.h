/* copyright 2016 Apache 2 sddekit authors */

#ifndef SK_ERR_H
#define SK_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

#define SK_OK 0
#define SK_ERR 1

/**
 * Typedef for error handler callback.
 *
 * \param errno error number.
 * \param file file name where error originates.
 * \param line line number in file where error originates.
 * \param reason description of error.
 */
typedef void (*sk_err_handler_fp)(int errno, char *file, int line, char *reason);

/**
 * The default error handler logs the error in the debug log.
 */
void sk_err_default_handler(int errno, char *file, int line, char *reason);

/**
 * Get the current error handler.
 */
sk_err_handler_fp sk_err_get_handler();

/**
 * Set the current error handler.
 *
 * \param fp new handler. if NULL, errors will be unhandled.
 */
void sk_err_set_handler(sk_err_handler_fp fp);

/**
 * Dispatches error to current error handler.
 */
void sk_err_handler(int errno, char *file, int line, char *reason);

/**
 * Handle an error.
 * 
 * \param reason description of error
 */
#define sk_err(reason) sk_err_handler(SK_ERR, __FILE__, __LINE__, reason);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
