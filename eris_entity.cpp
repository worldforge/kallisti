
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

#include "eris_entity.h"

#include <Eris/Entity.h>

static PyObject * ErisEntity_method(PyErisEntity * self)
{
    if (self->entity == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL entity in eris.Entity.method");
        return NULL;
    }
}

static PyMethodDef ErisEntity_methods[] = {
    {"method",		(PyCFunction)ErisEntity_method,	METH_VARARGS },
    {NULL, NULL} // sentinel
};

static void ErisEntity_dealloc(PyErisEntity * self)
{
    if (self->entity != 0) {
        delete self->entity;
    }
    self->ob_type->tp_free(self);
}

static PyObject * ErisEntity_getattr(PyErisEntity * self, char * name)
{
    return Py_FindMethod(ErisEntity_methods, (PyObject *)self, name);
}

static int ErisEntity_setattr(PyErisEntity * self, char * name, PyObject * v)
{
    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisEntity_cmp(PyErisEntity *self, PyObject * other)
{
    if (!PyErisEntity_Check(other)) {
        return -1;
    }
    PyErisEntity * other_ent = (PyErisEntity *)other;
    if (other_ent->entity == self->entity) {
        return 0;
    }
    return -1;
}

static PyObject * ErisEntity_new(PyTypeObject * type, 
                                  PyObject *, PyObject *)
{
    PyErisEntity * self = (PyErisEntity *)type->tp_alloc(type, 0);
    self->entity = 0;
    return (PyObject *)self;
}

static int ErisEntity_init(PyErisEntity * self, PyObject * args,
                            PyObject * kwds)
{
    PyErr_SetString(PyExc_TypeError, "Cannot create Entity");
    return -1;
}

PyTypeObject PyErisEntity_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.Entity",                      // tp_name
        sizeof(PyErisEntity),               // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisEntity_dealloc,     // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisEntity_getattr,    // tp_getattr
        (setattrfunc)ErisEntity_setattr,    // tp_setattr
        (cmpfunc)ErisEntity_cmp,            // tp_compare
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
        "Eris::Entity objects",             // tp_doc
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
        (initproc)ErisEntity_init,          // tp_init
        0,                                   // tp_alloc
        ErisEntity_new,                     // tp_new
};

PyErisEntity * newPyErisEntity()
{
    PyErisEntity * self;
    self = PyObject_NEW(PyErisEntity, &PyErisEntity_Type);
    if (self == NULL) {
        return NULL;
    }
    return self;
}
