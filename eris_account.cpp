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

#include "eris_account.h"

#include "eris_connection.h"

#include <Eris/Account.h>

static PyObject * ErisAccount_login(PyErisAccount * self, PyObject * args)
{
    if (self->account == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL account in eris.Account.login");
        return NULL;
    }

    char * u, * p;
    if (!PyArg_ParseTuple(args, "ss", &u, &p)) {
        return NULL;
    }

    Eris::Result res = self->account->login(u, p);
    if (res == Eris::NOT_CONNECTED) {
        PyErr_SetString(PyExc_IOError, "Not connected");
        return NULL;
    } else if (res == Eris::ALREADY_LOGGED_IN) {
        PyErr_SetString(PyExc_IOError, "Already logged in");
        return NULL;
    } else if (res != Eris::NO_ERR) {
        PyErr_SetString(PyExc_IOError, "Unknown Error");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * ErisAccount_createAccount(PyErisAccount * self,
                                            PyObject * args)
{
    if (self->account == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL account in eris.Account.createAccount");
        return NULL;
    }

    char * u, * f, * p;
    if (!PyArg_ParseTuple(args, "sss", &u, &f, &p)) {
        return NULL;
    }

    Eris::Result res = self->account->createAccount(u, f, p);
    if (res == Eris::NOT_CONNECTED) {
        PyErr_SetString(PyExc_IOError, "Not connected");
        return NULL;
    } else if (res == Eris::ALREADY_LOGGED_IN) {
        PyErr_SetString(PyExc_IOError, "Already logged in");
        return NULL;
    } else if (res != Eris::NO_ERR) {
        PyErr_SetString(PyExc_IOError, "Unknown Error");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * ErisAccount_logout(PyErisAccount * self)
{
    if (self->account == 0) {
        PyErr_SetString(PyExc_AssertionError,
                        "NULL account in eris.Account.logout");
        return NULL;
    }

    // self->account->logout();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef ErisAccount_methods[] = {
    {"login",		(PyCFunction)ErisAccount_login,		METH_VARARGS },
    {"createAccount",	(PyCFunction)ErisAccount_createAccount,	METH_VARARGS },
    {"logout",		(PyCFunction)ErisAccount_logout,	METH_NOARGS },
    {NULL, NULL} // sentinel
};

static void ErisAccount_dealloc(PyErisAccount * self)
{
    if (self->account != 0) {
        delete self->account;
    }
    self->ob_type->tp_free(self);
}

static PyObject * ErisAccount_getattr(PyErisAccount * self, char * name)
{
    return Py_FindMethod(ErisAccount_methods, (PyObject *)self, name);
}

static int ErisAccount_setattr(PyErisAccount * self, char * name, PyObject * v)
{
#if 0
    if (strcmp(name, "StatusChanged") == 0) {
        return 0;
    }
#endif
    PyErr_SetString(PyExc_AttributeError, "unknown attribute");
    return -1;
}

static int ErisAccount_cmp(PyErisAccount *self, PyObject * other)
{
    if (!PyErisAccount_Check(other)) {
        return -1;
    }
    PyErisAccount * other_acc = (PyErisAccount *)other;
    if (other_acc->account == self->account) {
        return 0;
    }
    return -1;
}

static PyObject * ErisAccount_new(PyTypeObject * type, 
                                  PyObject *, PyObject *)
{
    PyErisAccount * self = (PyErisAccount *)type->tp_alloc(type, 0);
    self->account = 0;
    return (PyObject *)self;
}

static int ErisAccount_init(PyErisAccount * self, PyObject * args,
                            PyObject * kwds)
{
    PyObject * c;

    if (!PyArg_ParseTuple(args, "O!", &PyErisConnection_Type, &c)) {
        return -1;
    }

    assert(PyErisConnection_Check(c));

    PyErisConnection * connection = (PyErisConnection *)c;
    self->account = new Eris::Account(connection->connection);

    return 0;
}

PyTypeObject PyErisAccount_Type = {
        PyObject_HEAD_INIT(NULL)
        0,                                   // ob_size
        "eris.Account",                      // tp_name
        sizeof(PyErisAccount),               // tp_basicsize
        0,                                   // tp_itemsize
        // methods
        (destructor)ErisAccount_dealloc,     // tp_dealloc
        0,                                   // tp_print
        (getattrfunc)ErisAccount_getattr,    // tp_getattr
        (setattrfunc)ErisAccount_setattr,    // tp_setattr
        (cmpfunc)ErisAccount_cmp,            // tp_compare
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
        "Eris::Account objects",             // tp_doc
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
        (initproc)ErisAccount_init,          // tp_init
        0,                                   // tp_alloc
        ErisAccount_new,                     // tp_new
};
