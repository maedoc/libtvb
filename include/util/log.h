/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

enum sd_log_level { SD_LOG_ERROR, SD_LOG_INFO, SD_LOG_DEBUG };

/*! Callback handler log messages */
typedef void (*sd_log_handler)(enum sd_log_level level, char *message);

/*! Set log message handler pointer used by sd_log_handle. */
SD_API void sd_log_set_handler(sd_log_handler new_handler);

/*! Get log message handler pointer used by sd_log_handle. */
SD_API sd_log_handler sd_log_get_handler();

/*! Handle log message; low-level: prefer macros below. */
SD_API void sd_log_handle(enum sd_log_level level, char *format, ...);

/* Macros that user should use & library MUST use. {{{ */

#ifdef _MSC_VER /* MSVC silently drops final comma when appropriate */

/* insert file, line, function name & new line*/
#define _sd_log_handle(level, fmt, ...) \
       	sd_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, __VA_ARGS__)

#define sd_log_info(fmt, ...)  _sd_log_handle(SD_LOG_INFO,  fmt, __VA_ARGS__)
#define sd_log_debug(fmt, ...) _sd_log_handle(SD_LOG_DEBUG, fmt, __VA_ARGS__)
#define sd_log_fail(fmt, ...)  _sd_log_handle(SD_LOG_ERROR, fmt, __VA_ARGS__)
#define sd_err(fmt, ...)       _sd_log_handle(SD_LOG_ERROR, fmt, __VA_ARGS__)

#else /* need GCC double hash to eat final comma */

/* insert file, line, function name & new line*/
#define _sd_log_handle(level, fmt, ...) \
       	sd_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, ## __VA_ARGS__)

#define sd_log_info(fmt, ...)  _sd_log_handle(SD_LOG_INFO,  fmt, ## __VA_ARGS__)
#define sd_log_debug(fmt, ...) _sd_log_handle(SD_LOG_DEBUG, fmt, ## __VA_ARGS__)
#define sd_log_fail(fmt, ...)  _sd_log_handle(SD_LOG_ERROR, fmt, ## __VA_ARGS__)
#define sd_err(fmt, ...)       _sd_log_handle(SD_LOG_ERROR, fmt, ## __VA_ARGS__)

#endif