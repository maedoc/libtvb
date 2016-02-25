/* copyright 2016 Apache 2 sddekit authors */

/* TODO mv lib, string & math into impl files */
/* standard C includes {{{ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
/* }}} */

/* -DSD_API_EXPORT dllexport {{{ */
#if defined(_MSC_VER)
#ifdef SD_API_EXPORT
#define SD_API __declspec(dllexport)
#else
#define SD_API __declspec(dllimport)
#endif
#else
#define SD_API
#endif
/* }}} */

/* TODO double check these versions, ignore restrict if compiler doesn't support it {{{ */
#if defined(__GNUC__) && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#   define restrict __restrict
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#   define restrict __restrict
#else
#   define restrict
#endif
/* }}} */

/* TODO drop these */
/* cf. https://gist.github.com/maedoc/f22f691c1ee22fe1961d#prelude {{{ */
#define SD_AS(obj, type) (((obj)->type)(obj))

#define SD_CALL_AS(obj, type, meth, ...) \
	SD_AS(obj, type)->meth(SD_AS(obj, type), __VA_ARGS__)

#define SD_CALL_AS_(obj, type, meth) \
	SD_AS(obj, type)->meth(SD_AS(obj, type))
/* }}} */

/* vim: foldmethod=marker
 */
