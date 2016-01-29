/* copyright 2016 Apache 2 sddekit authors */

#include "Python.h"
#include "sddekit.h"

struct module_state {
	PyObject *error;
};

/* GETSTATE {{{ */
#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*) PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif
/* }}} */

static PyObject *
error_out(PyObject *m)
{
	struct module_state *st = GETSTATE(m);
	PyErr_SetString(st->error, "oops");
	return NULL;
}

static PyMethodDef methods[] = {
	{"error_out", (PyCFunction) error_out, METH_NOARGS, NULL},
	{NULL, NULL}
};

/* module init {{{ */
#if PY_MAJOR_VERSION >= 3

static int traverse(PyObject *m, visitproc visit, void *arg)
{
	Py_VISIT(GETSTATE(m)->error);
	return 0;
}

static int clear(PyObject *m)
{
	Py_CLEAR(GETSTATE(m)->error);
	return 0;
}

static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"sddekit",
	NULL,
	sizeof(struct module_state),
	methods,
	NULL,
	traverse,
	clear,
	NULL
};

#define INITERROR return NULL

PyObject * PyInit_sddekit(void)

#else

#define INITERROR return

void initsddekit(void)

#endif

{
#if PY_MAJOR_VERSION >= 3
	PyObject *module = PyModule_Create(&moduledef);
#else
	PyObject *module = Py_InitModule("sddekit", methods);
#endif

	if (module == NULL)
		INITERROR;

	struct module_state *st = GETSTATE(module);

	st->error = PyErr_NewException("sddekit.Error", NULL, NULL);

	if (st->error == NULL)
	{
		Py_DECREF(module);
		INITERROR;
	}

	PyModule_AddObject(module, "__version__", 
#if PY_MAJOR_VERSION >= 3
		PyBytes_FromFormat
#else
		PyString_FromFormat
#endif
			("%d.%d", sd_ver_major(), sd_ver_minor()));

#if PY_MAJOR_VERSION >= 3
	return module;
#endif
}
/* }}} */

/* vim: foldmethod=marker 
 */
