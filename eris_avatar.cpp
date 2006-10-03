
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

#include "eris_avatar.h"

#include "eris_view.h"
#include "PythonCallback.h"

#include <Eris/Avatar.h>

static PyObject * ErisAvatar_getView(PyErisAvatar * self)
{
    if (self->avatar == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL avatar in eris.Avatar.method");
        return NULL;
    }

    Eris::View * view = self->avatar->getView();
    if (view == NULL) {
        PyErr_SetString(PyExc_RuntimeError,
                        "No view available yet");
        return NULL;
    }
    PyErisView * view_wrap = newPyErisView();
    if (view_wrap == NULL) {
        return NULL;
    }
    view_wrap->view = view;
    return (PyObject *)view_wrap;
}

static PyMethodDef ErisAvatar_methods[] = {
    {"getView",                (PyCFunction)ErisAvatar_getView,        METH_VARARGS },
    {NULL, NULL} // sentinel
};

static void ErisAvatar_dealloc(PyErisAvatar * self)
{
    // We don't own this pointer
    // if (self->avatar != 0) {
        // delete self->avatar;
    // }
    self->ob_type->tp_free(self);
}

static PyObject * ErisAvatar_getattr(PyErisAvatar * self, char * name)
{
    return Py_FindMethod(ErisAvatar_methods, (PyObject *)self, name);
}

static int ErisAvatar_setattr(PyErisAvatar * self, char * name, PyObject * v)
{
    if (strcmp(name, "GotCharacterEntity") == 0) {
        if (!PyCallable_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "Callback requires a callable");
            return -1;
        }
        // Will need to be a template, or something. Possibly a number of
        // templates, one for each type we will need to wrap.
        PythonCallback1<Eris::Entity *> * callback = new PythonCallback1<Eris::Entity *>(v);
        self->avatar->GotCharacterEntity.connect(sigc::mem_fun(*callback, &PythonCallback1<Eris::Entity *>::call));
        return 0;
    }
    if (strcmp(name, "InvAdded") == 0) {
        if (!PyCallable_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "Callback requires a callable");
            return -1;
        }
        // Will need to be a template, or something. Possibly a number of
        // templates, one for each type we will need to wrap.
        PythonCallback1<Eris::Entity *> * callback = new PythonCallback1<Eris::Entity *>(v);
        self->avatar->InvAdded.connect(sigc::mem_fun(*callback, &PythonCallback1<Eris::Entity *>::call));
        return 0;
    }
    if (strcmp(name, "InvRemoved") == 0) {
        if (!PyCallable_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "Callback requires a callable");
            return -1;
        }
        // Will need to be a template, or something. Possibly a number of
        // templates, one for each type we will need to wrap.
        PythonCallback1<Eris::Entity *> * callback = new PythonCallback1<Eris::Entity *>(v);
        self->avatar->InvRemoved.connect(sigc::mem_fun(*callback, &PythonCallback1<Eris::Entity *>::call));
        return 0;
    }
    if (strcmp(name, "Hear") == 0) {
        if (!PyCallable_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "Callback requires a callable");
            return -1;
        }
        // Will need to be a template, or something. Possibly a number of
        // templates, one for each type we will need to wrap.
        // PythonCallback2<Eris::Entity *, const Atlas::Objects::Operation::RootOperation &> * callback = new PythonCallback2<Eris::Entity *, const Atlas::Objects::Operation::RootOperation &>(v);
        // self->avatar->Hear.connect(sigc::mem_fun(*callback, &PythonCallback2<Eris::Entity *, const Atlas::Objects::Operation::RootOperation &>::call));
        return 0;
    }

    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisAvatar_cmp(PyErisAvatar *self, PyObject * other)
{
    if (!PyErisAvatar_Check(other)) {
        return -1;
    }
    PyErisAvatar * other_wrap = (PyErisAvatar *)other;
    if (other_wrap->avatar == self->avatar) {
        return 0;
    }
    return -1;
}

static PyObject * ErisAvatar_new(PyTypeObject * type, 
                                  PyObject *, PyObject *)
{
    PyErisAvatar * self = (PyErisAvatar *)type->tp_alloc(type, 0);
    self->avatar = 0;
    return (PyObject *)self;
}

static int ErisAvatar_init(PyErisAvatar * self, PyObject * args,
                            PyObject * kwds)
{
    PyErr_SetString(PyExc_TypeError, "Cannot create Avatar");
    return -1;
}

PyTypeObject PyErisAvatar_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.Avatar",                      // tp_name
        sizeof(PyErisAvatar),               // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisAvatar_dealloc,     // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisAvatar_getattr,    // tp_getattr
        (setattrfunc)ErisAvatar_setattr,    // tp_setattr
        (cmpfunc)ErisAvatar_cmp,            // tp_compare
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
        "Eris::Avatar objects",             // tp_doc
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
        (initproc)ErisAvatar_init,          // tp_init
        0,                                   // tp_alloc
        ErisAvatar_new,                     // tp_new
};

PyErisAvatar * newPyErisAvatar()
{
    PyErisAvatar * self;
    self = PyObject_NEW(PyErisAvatar, &PyErisAvatar_Type);
    if (self == NULL) {
        return NULL;
    }
    return self;
}
