#include "UnitTypeTable.h"


#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(MicroRTSpy, m) {
    py::class_<UnitTypeTable>(m, "UnitTypeTable")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int>())
        .def("setUnitTypeTable", &UnitTypeTable::setUnitTypeTable)
        .def("addUnitType", &UnitTypeTable::addUnitType)
        .def("getUnitTypes", &UnitTypeTable::getUnitTypes)
        .def("getMoveConflictResolutionStrategy", &UnitTypeTable::getMoveConflictResolutionStrategy)

        .def("getUnit", &UnitTypeTable::getUnitTypes);
       
}

