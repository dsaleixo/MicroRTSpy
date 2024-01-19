#include "Unit.h"
#include "UnitType.h"

#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(MicroRTSpy, m) {
    py::class_<Unit>(m, "Unit")
        .def(py::init<long, int, UnitType, int, int ,int>())
        .def(py::init<int, UnitType, int, int, int>())
        .def(py::init<int, UnitType, int, int>())
        .def(py::init<const Unit>())
        .def("getPlayer", &Unit::getPlayer)
        .def("getType", &Unit::getType)
        .def("setType", &Unit::setType)
        .def("getID", &Unit::getID)

        .def("getX", &Unit::getX)
        .def("getY", &Unit::getY)
        .def("setX", &Unit::setX)
        .def("setY", &Unit::setY)
        .def("getResources", &Unit::getResources)
        .def("setResources", &Unit::setResources)


        .def("getHitPoints", &Unit::getHitPoints)
        .def("getMaxHitPoints", &Unit::getMaxHitPoints)
        .def("setHitPoints", &Unit::setHitPoints)
        .def("getCost", &Unit::getCost)
        .def("getMoveTime", &Unit::getMoveTime)
        .def("getAttackTime", &Unit::getAttackTime)

        .def("getMinDamage", &Unit::getMinDamage)
        .def("getMaxDamage", &Unit::getMaxDamage)
        .def("getHarvestAmount", &Unit::getHarvestAmount)
        .def("getHarvestTime", &Unit::getHarvestTime)
        .def("toString", &Unit::toString)
        .def("clone", &Unit::clone)

        .def("hashCode", &Unit::hashCode)
        

        .def("setID", &Unit::setID);
       
}

