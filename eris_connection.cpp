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

#include "eris_connection.h"

#include <Eris/Connection.h>

static PyObject * ErisConnection_connect(PyErisConnection * self)
{
    if (self->connection == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL connection in eris.Connection.connect");
        return NULL;
    }

    if (self->connection->connect() != 0) {
        PyErr_SetString(PyExc_IOError,
                        "Unable to create socket");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * ErisConnection_disconnect(PyErisConnection * self)
{
    if (self->connection == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL connection in eris.Connection.disconnect");
        return NULL;
    }

    if (self->connection->disconnect() != 0) {
        PyErr_SetString(PyExc_IOError,
                        "Unable to disconnect");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * ErisConnection_send(PyErisConnection * self)
{
    if (self->connection == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL connection in eris.Connection.send");
        return NULL;
    }

    // self->connection->send();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef ErisConnection_methods[] = {
    {"connect",		(PyCFunction)ErisConnection_connect,	METH_NOARGS },
    {"disconnect",	(PyCFunction)ErisConnection_disconnect,	METH_NOARGS },
    {"send",		(PyCFunction)ErisConnection_send,	METH_O },
    {NULL, NULL} // sentinel
};

static void ErisConnection_dealloc(PyErisConnection * self)
{
    if (self->connection != 0) {
        delete self->connection;
    }
    self->ob_type->tp_free(self);
}

static PyObject * ErisConnection_getattr(PyErisConnection * self, char * name)
{
    return Py_FindMethod(ErisConnection_methods, (PyObject *)self, name);
}

static int ErisConnection_setattr(PyErisConnection * self, char * name,
                                  PyObject * v)
{
    if (strcmp(name, "GotServerInfo") == 0) {
        if (!PyCallable_Check(v)) {
            PyErr_SetString(PyExc_TypeError, "Callback requires a callable");
            return -1;
        }
        // Will need to be a template, or something. Possibly a number of
        // templates, one for each type we will need to wrap.
        // PythonCallback * callback = new PythonCallback(v);
        // self->connection->GotServerInfo.connect(sigc::mem_fun(*callback, &PythonCallback::call));
        return 0;
    }
    if (strcmp(name, "Disconnecting") == 0) {
        return 0;
    }
    if (strcmp(name, "Failure") == 0) {
        return 0;
    }
    if (strcmp(name, "StatusChanged") == 0) {
        return 0;
    }
    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisConnection_cmp(PyErisConnection *self, PyObject * other)
{
    if (!PyErisConnection_Check(other)) {
        return -1;
    }
    PyErisConnection * other_con = (PyErisConnection *)other;
    if (other_con->connection == self->connection) {
        return 0;
    }
    return -1;
}

static PyObject * ErisConnection_new(PyTypeObject * type, 
                                     PyObject *, PyObject *)
{
    PyErisConnection * self = (PyErisConnection *)type->tp_alloc(type, 0);
    self->connection = 0;
    return (PyObject *)self;
}

static int ErisConnection_init(PyErisConnection * self, PyObject * args,
                               PyObject * kwds)
{
    char * client, * hostname;
    int port, debug;

    if (!PyArg_ParseTuple(args, "ssii", &client, &hostname, &port, &debug)) {
        return -1;
    }
    self->connection = new Eris::Connection(client, hostname, port, debug);

    return 0;
}

PyTypeObject PyErisConnection_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.Connection",                   // tp_name
        sizeof(PyErisConnection),            // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisConnection_dealloc,  // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisConnection_getattr, // tp_getattr
        (setattrfunc)ErisConnection_setattr, // tp_setattr
        (cmpfunc)ErisConnection_cmp,         // tp_compare
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
        "Eris::Connection objects",          // tp_doc
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
        (initproc)ErisConnection_init,       // tp_init
        0,                                   // tp_alloc
        ErisConnection_new,                  // tp_new
};
