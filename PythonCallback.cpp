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

#include "PythonCallback_impl.h"

#include <Eris/Avatar.h>

#include <iostream>

PythonCallback::PythonCallback(PyObject * callable) : m_callback(callable)
{
    Py_INCREF(m_callback);
}

PythonCallback::~PythonCallback()
{
}

// FIXME Destructor must DECREF.

void PythonCallback::call()
{
    PyObject * ret = PyEval_CallFunction(m_callback, "()");


    if (ret != NULL) {
        Py_DECREF(ret);
    }
}

template class PythonCallback1<Eris::Avatar>;

template<>
PyObject * wrapPtr<Eris::Avatar>(Eris::Avatar *)
{
    return NULL;
}

template<>
PyObject * wrap<Eris::Avatar>(Eris::Avatar & )
{
    return NULL;
}
