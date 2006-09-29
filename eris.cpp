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

#include <iostream>

static PyMethodDef no_methods[] = {
    {NULL,          NULL}                       /* Sentinel */
};

PyMODINIT_FUNC
initeris()
{
    std::cout << "WAH" << std::endl << std::flush;

    PyObject * eris = Py_InitModule("eris", no_methods);

    if (eris == NULL) {
        return;
    }

    if (PyType_Ready(&PyErisConnection_Type) < 0) {
        // ????
        return;
    }
    PyModule_AddObject(eris, "Connection", (PyObject *)&PyErisConnection_Type);
}
