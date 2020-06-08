/*
 * Python wrapper for shash
 *
 * Public domain
 * 2020 Ronen Lapushner
 * 2007 Viliam Holub
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "simi.h"
#include "simiw.h"

static PyObject *method_charikar_hash64(PyObject *self, PyObject *args) {
    const char *data;
    Py_ssize_t data_len;

    /* Extract the raw data and it's length */
    if (!PyArg_ParseTuple(args, "s#", &data, &data_len))
        return NULL;

    /* Calculate the Charikar hash */
    uint64_t hash = charikar_hash64(data, data_len);
    
    return PyLong_FromUnsignedLongLong(hash);
}

static PyObject *method_charikar_hash64_wide(PyObject *self, PyObject *args) {
    const char *data;
    Py_ssize_t data_len;
    int stoken_size;

    /* Extract the raw data and it's length */
    if (!PyArg_ParseTuple(args, "s#i", &data, &data_len, &stoken_size))
        return NULL;

    /* Sanity-check the arguments */
    if (stoken_size < 1) {
        PyErr_SetString(PyExc_ValueError, "supertoken size must be >= 1");
        return NULL;
    }

    /* Calculate the Charikar hash */
    uint64_t hash = charikar_hash64_wide(data, data_len, stoken_size);
    
    return PyLong_FromUnsignedLongLong(hash);
}

static PyObject *method_chaikar_hamming_dist(PyObject *self, PyObject *args) {
    uint64_t hash1, hash2;

    /* Extract the two hashes */
    if (!PyArg_ParseTuple(args, "kk", &hash1, &hash2))
        return NULL;

    return PyLong_FromLong((long)hamming_dist(hash1, hash2));
}

/* ======================================================================================== */

/* Module method definition table */
static struct PyMethodDef method_table[] = {
    {   
        "charikar_hash64", 
        method_charikar_hash64, 
        METH_VARARGS, 
        "Calculates Charikar's hash for the given data" 
    },
    {   
        "charikar_hash64_wide", 
        method_charikar_hash64_wide, 
        METH_VARARGS, 
        "Calculates Charikar's hash for the given data, with variable supertoken size" 
    },
    {   
        "hamming_dist", 
        method_chaikar_hamming_dist, 
        METH_VARARGS, 
        "Calculates the Hamming distance between two 64-bit integers" 
    },
    { NULL, NULL, 0, NULL }
};

/* ======================================================================================== */

/* Module definition and initialization */

const char * const shash_doc = "A Python wrapper for shash, implementing Charkiar's hash for identifying " \
"documents and detecting duplicate documents";

static struct PyModuleDef python_shash_moddef = {
    PyModuleDef_HEAD_INIT,
    "python-shash",
    shash_doc,
    -1,
    method_table
};

PyMODINIT_FUNC PyInit_shash(void) {
    return PyModule_Create(&python_shash_moddef);
}

/* ======================================================================================== */