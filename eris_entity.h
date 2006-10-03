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

#ifndef KALLISTI_ERIS_ENTITY_H
#define KALLISTI_ERIS_ENTITY_H

#include <Python.h>

namespace Eris {
  class Entity;
}

typedef struct {
    PyObject_HEAD
    Eris::Entity * entity;
} PyErisEntity;

extern PyTypeObject PyErisEntity_Type;

// FIXME Is this legal any more?
#define PyErisEntity_Check(_o) ((_o)->ob_type == &PyErisEntity_Type)

PyErisEntity * newPyErisEntity();

#endif // KALLISTI_ERIS_ENTITY_H
