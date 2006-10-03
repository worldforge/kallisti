
// Kallisti Online RPG Library Modules for Python
// Copyright (C) 2006 Alistair Riddoch
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include "eris_wrapper.h"

#include <Eris/Wrapper.h>

static PyObject * ErisWrapper_method(PyErisWrapper * self)
{
    if (self->wrapper == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL wrapper in eris.Wrapper.method");
        return NULL;
    }
}

static PyMethodDef ErisWrapper_methods[] = {
    {"method",		(PyCFunction)ErisWrapper_method,	METH_VARARGS },
    {NULL, NULL} // sentinel
};

static void ErisWrapper_dealloc(PyErisWrapper * self)
{
    if (self->wrapper != 0) {
        delete self->wrapper;
    }
    self->ob_type->tp_free(self);
}

static PyObject * ErisWrapper_getattr(PyErisWrapper * self, char * name)
{
    return Py_FindMethod(ErisWrapper_methods, (PyObject *)self, name);
}

static int ErisWrapper_setattr(PyErisWrapper * self, char * name, PyObject * v)
{
    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisWrapper_cmp(PyErisWrapper *self, PyObject * other)
{
    if (!PyErisWrapper_Check(other)) {
        return -1;
    }
    PyErisWrapper * other_wrap = (PyErisWrapper *)other;
    if (other_wrap->wrapper == self->wrapper) {
        return 0;
    }
    return -1;
}

static PyObject * ErisWrapper_new(PyTypeObject * type, 
                                  PyObject *, PyObject *)
{
    PyErisWrapper * self = (PyErisWrapper *)type->tp_alloc(type, 0);
    self->wrapper = 0;
    return (PyObject *)self;
}

static int ErisWrapper_init(PyErisWrapper * self, PyObject * args,
                            PyObject * kwds)
{
    PyObject * c;

    if (!PyArg_ParseTuple(args, "")) {
        return -1;
    }

    self->wrapper = new Eris::Wrapper();

    return 0;
}

PyTypeObject PyErisWrapper_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.Wrapper",                      // tp_name
        sizeof(PyErisWrapper),               // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisWrapper_dealloc,     // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisWrapper_getattr,    // tp_getattr
        (setattrfunc)ErisWrapper_setattr,    // tp_setattr
        (cmpfunc)ErisWrapper_cmp,            // tp_compare
        0,                                   // tp_repr
        0,                                   // tp_as_number
        0,                                   // tp_as_sequence
        0,                                   // tp_as_mapping
        0,                                   // tp_hash
        0,                                   // tp_call
        0,                                   // tp_str
        0,                                   // tp_getattro
        0,                                   // tp_setattro
        0,                                   // tp_as_buffer
        Py_TPFLAGS_DEFAULT,                  // tp_flags
        "Eris::Wrapper objects",             // tp_doc
        0,                                   // tp_travers
        0,                                   // tp_clear
        0,                                   // tp_richcompare
        0,                                   // tp_weaklistoffset
        0,                                   // tp_iter
        0,                                   // tp_iternext
        0,                                   // tp_methods
        0,                                   // tp_members
        0,                                   // tp_getset
        0,                                   // tp_base
        0,                                   // tp_dict
        0,                                   // tp_descr_get
        0,                                   // tp_descr_set
        0,                                   // tp_dictoffset
        (initproc)ErisWrapper_init,          // tp_init
        0,                                   // tp_alloc
        ErisWrapper_new,                     // tp_new
};
