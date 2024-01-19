#include "PhysicalGameState.h"
#include "UnitTypeTable.h"
#include <pybind11/stl.h>

#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;



PYBIND11_MODULE(MicroRTSpy, m) {
    py::class_<PhysicalGameState>(m, "PhysicalGameState")
        .def(py::init<int,int>())
        .def("load", &PhysicalGameState::load)
        .def("getUnits", &PhysicalGameState::getUnits)
        .def("addUnit", &PhysicalGameState::addUnit)
        .def("addPlayer", &PhysicalGameState::addPlayer)
        .def("getUnit", &PhysicalGameState::getUnit);

    py::class_<UnitTypeTable>(m, "UnitTypeTable")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int>())
        .def("setUnitTypeTable", &UnitTypeTable::setUnitTypeTable)
        .def("addUnitType", &UnitTypeTable::addUnitType)
        .def("getUnitTypes", &UnitTypeTable::getUnitTypes)
        .def("getMoveConflictResolutionStrategy", &UnitTypeTable::getMoveConflictResolutionStrategy)
        .def("getUnit", &UnitTypeTable::getUnitTypes);


    py::class_<Unit>(m, "Unit")
        .def(py::init<long, int, UnitType, int, int, int>())
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

    py::class_<Player>(m, "Player")
        .def(py::init<int, int>())
        .def("getID", &Player::getID)
        .def("getResources", &Player::getResources)
        .def("setResources", &Player::setResources)
        .def("toString", &Player::toString)
        .def("fromXML", &Player::fromXML)
        .def("clone", &Player::clone);
       

    py::class_<UnitType>(m, "UnitType")
        .def("equals", &UnitType::equals)
        .def("produces", &UnitType::produces);

}

