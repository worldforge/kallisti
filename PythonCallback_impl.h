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

#include "PythonCallback.h"

#include <iostream>

template <class T>
PythonCallback1<T>::PythonCallback1(PyObject * callable) :
                                       m_callback(callable)
{
    Py_INCREF(m_callback);
}

template <class T>
PythonCallback1<T>::~PythonCallback1()
{
}

// FIXME Destructor must DECREF.


template <class T>
void PythonCallback1<T>::call(T t)
{
    PyObject * ret = PyEval_CallFunction(m_callback, "(O)", wrap(t));

    if (ret != NULL) {
        Py_DECREF(ret);
    } else {
        std::cout << "BOOM" << std::endl << std::flush;
    }
}

template <typename T, typename U>
PythonCallback2<T, U>::PythonCallback2(PyObject * callable) :
                                       m_callback(callable)
{
    Py_INCREF(m_callback);
}

template <typename T, typename U>
PythonCallback2<T, U>::~PythonCallback2()
{
}

// FIXME Destructor must DECREF.


template <typename T, typename U>
void PythonCallback2<T, U>::call(T t, U u)
{
    PyObject * ret = PyEval_CallFunction(m_callback, "(O)", wrap(t), wrap(u));

    if (ret != NULL) {
        Py_DECREF(ret);
    } else {
        std::cout << "BOOM" << std::endl << std::flush;
    }
}
