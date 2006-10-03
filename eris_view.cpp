
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

#include "eris_view.h"

#include <Eris/View.h>

static PyObject * ErisView_method(PyErisView * self)
{
    if (self->view == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL view in eris.View.method");
        return NULL;
    }

    return NULL;
}

static PyMethodDef ErisView_methods[] = {
    {"method",		(PyCFunction)ErisView_method,	METH_VARARGS },
    {NULL, NULL} // sentinel
};

static void ErisView_dealloc(PyErisView * self)
{
    if (self->view != 0) {
        delete self->view;
    }
    self->ob_type->tp_free(self);
}

static PyObject * ErisView_getattr(PyErisView * self, char * name)
{
    return Py_FindMethod(ErisView_methods, (PyObject *)self, name);
}

static int ErisView_setattr(PyErisView * self, char * name, PyObject * v)
{
    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisView_cmp(PyErisView *self, PyObject * other)
{
    if (!PyErisView_Check(other)) {
        return -1;
    }
    PyErisView * other_wrap = (PyErisView *)other;
    if (other_wrap->view == self->view) {
        return 0;
    }
    return -1;
}

static PyObject * ErisView_new(PyTypeObject * type, 
                                  PyObject *, PyObject *)
{
    PyErisView * self = (PyErisView *)type->tp_alloc(type, 0);
    self->view = 0;
    return (PyObject *)self;
}

static int ErisView_init(PyErisView * self, PyObject * args,
                            PyObject * kwds)
{
    PyErr_SetString(PyExc_TypeError, "Cannot create View");
    return -1;
}

PyTypeObject PyErisView_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.View",                      // tp_name
        sizeof(PyErisView),               // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisView_dealloc,     // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisView_getattr,    // tp_getattr
        (setattrfunc)ErisView_setattr,    // tp_setattr
        (cmpfunc)ErisView_cmp,            // tp_compare
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
        "Eris::View objects",             // tp_doc
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
        (initproc)ErisView_init,          // tp_init
        0,                                   // tp_alloc
        ErisView_new,                     // tp_new
};

PyErisView * newPyErisView()
{
    PyErisView * self;
    self = PyObject_NEW(PyErisView, &PyErisView_Type);
    if (self == NULL) {
        return NULL;
    }
    return self;
}
