/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

enum tvb_log_level { TVB_LOG_ERROR, TVB_LOG_INFO, TVB_LOG_DEBUG };

/*! Callback handler log messages */
typedef void (*tvb_log_handler)(enum tvb_log_level level, char *message);

/*! Set log message handler pointer used by tvb_log_handle. */
TVB_API void tvb_log_set_handler(tvb_log_handler new_handler);

/*! Get log message handler pointer used by tvb_log_handle. */
TVB_API tvb_log_handler tvb_log_get_handler();

/*! Handle log message; low-level: prefer macros below. */
TVB_API void tvb_log_handle(enum tvb_log_level level, char *format, ...);

/*! Get if error occurred and reset. */
TVB_API bool tvb_log_get_err_and_reset();

/* Macros that user should use & library MUST use. {{{ */

#ifdef _MSC_VER /* MSVC silently drops final comma when appropriate */

/* insert file, line, function name & new line*/
#define _tvb_log_handle(level, fmt, ...) \
       	tvb_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, __VA_ARGS__)

#define tvb_log_info(fmt, ...)  _tvb_log_handle(TVB_LOG_INFO,  fmt, __VA_ARGS__)
#define tvb_log_debug(fmt, ...) _tvb_log_handle(TVB_LOG_DEBUG, fmt, __VA_ARGS__)
#define tvb_log_fail(fmt, ...)  _tvb_log_handle(TVB_LOG_ERROR, fmt, __VA_ARGS__)
#define tvb_err(fmt, ...)       _tvb_log_handle(TVB_LOG_ERROR, fmt, __VA_ARGS__)

#else /* need GCC double hash to eat final comma */

/* insert file, line, function name & new line*/
#define _tvb_log_handle(level, fmt, ...) \
       	tvb_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, ## __VA_ARGS__)

#define tvb_log_info(fmt, ...)  _tvb_log_handle(TVB_LOG_INFO,  fmt, ## __VA_ARGS__)
#define tvb_log_debug(fmt, ...) _tvb_log_handle(TVB_LOG_DEBUG, fmt, ## __VA_ARGS__)
#define tvb_log_fail(fmt, ...)  _tvb_log_handle(TVB_LOG_ERROR, fmt, ## __VA_ARGS__)
#define tvb_err(fmt, ...)       _tvb_log_handle(TVB_LOG_ERROR, fmt, ## __VA_ARGS__)

#endif
