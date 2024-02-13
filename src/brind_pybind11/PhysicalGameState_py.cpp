#include "PhysicalGameState.h"
#include "UnitTypeTable.h"
#include <pybind11/stl.h>
#include "Unit.h"
#include "Player.h"
#include "UnitType.h"
#include "GameState.h"
#include "PlayerAction.h"
#include "ResourceUsage.h"
#include "UnitAction.h"
#include "UnitActionAssignment.h"


#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;



PYBIND11_MODULE(MicroRTSpy, m) {


    py::class_<UnitActionAssignment>(m, "UnitActionAssignment")
        .def("getUnit", &UnitActionAssignment::getUnit, py::return_value_policy::reference)
        .def("getUnitAction", &UnitActionAssignment::getUnitAction, py::return_value_policy::reference)
        .def("getTime", &UnitActionAssignment::getTime)
        .def("toString", &UnitActionAssignment::toString);

    py::class_<UnitAction>(m, "UnitAction")
        .def(py::init<int>())
        .def(py::init<int, int>())
        .def(py::init<int, int, int>())
        .def(py::init<int, int, UnitType*>())
        .def("toString", &UnitAction::toString)
        .def("getDirection", &UnitAction::getDirection)
        .def("getLocationX", &UnitAction::getLocationX)
        .def("getLocationY", &UnitAction::getLocationY)
        .def("getType", &UnitAction::getType)
        .def("getActionName", &UnitAction::getActionName)
        .def("getTYPE_NONE", &UnitAction::getTYPE_NONE)
        .def("getTYPE_MOVE", &UnitAction::getTYPE_MOVE)
        .def("getTYPE_HARVEST", &UnitAction::getTYPE_HARVEST)
        .def("getTYPE_RETURN", &UnitAction::getTYPE_RETURN)
        .def("getTYPE_PRODUCE", &UnitAction::getTYPE_PRODUCE)
        .def("getTYPE_ATTACK_LOCATION", &UnitAction::getTYPE_ATTACK_LOCATION)
        .def("getNUMBER_OF_ACTION_TYPES", &UnitAction::getNUMBER_OF_ACTION_TYPES)
        .def("getDIRECTION_NONE", &UnitAction::getDIRECTION_NONE)
        .def("getDIRECTION_UP", &UnitAction::getDIRECTION_UP)
        .def("getDIRECTION_RIGHT", &UnitAction::getDIRECTION_RIGHT)
        .def("getDIRECTION_DOWN", &UnitAction::getDIRECTION_DOWN)
        .def("getDIRECTION_LEFT", &UnitAction::getDIRECTION_LEFT);

    py::class_<PlayerAction>(m, "PlayerAction")
        .def(py::init<>())
        .def("addUnitAction", &PlayerAction::addUnitAction);

    py::class_<GameState>(m, "GameState")
        .def(py::init<PhysicalGameState*, UnitTypeTable*>())
        .def("getActionAssignment", &GameState::getActionAssignment, py::return_value_policy::reference)
        .def("getTime", &GameState::getTime)
        .def("getNextChangeTime", &GameState::getNextChangeTime)
        .def("issueSafe", &GameState::issueSafe)
        .def("cycle", &GameState::cycle)
        .def("winner", &GameState::winner)
        .def("gameover", &GameState::gameover)
        .def("getPhysicalGameState", &GameState::getPhysicalGameState, py::return_value_policy::reference);

    py::class_<PhysicalGameState>(m, "PhysicalGameState")
        .def(py::init<int,int>())
        .def("load", &PhysicalGameState::load)
        .def("getUnits", &PhysicalGameState::getUnits, py::return_value_policy::reference)
        .def("addUnit", &PhysicalGameState::addUnit)
        .def("addPlayer", &PhysicalGameState::addPlayer)
        .def("getPlayer", &PhysicalGameState::getPlayer)
        .def("getWidth", &PhysicalGameState::getWidth)
        .def("getHeight", &PhysicalGameState::getHeight)
        .def("getTerrain", &PhysicalGameState::getTerrain)
        .def("getTERRAIN_WALL", &PhysicalGameState::getTERRAIN_WALL)
        .def("winner", &PhysicalGameState::winner)
        .def("gameover", &PhysicalGameState::gameover)
        .def("getUnit", &PhysicalGameState::getUnit);

    py::class_<UnitTypeTable>(m, "UnitTypeTable")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int>())
        .def("setUnitTypeTable", &UnitTypeTable::setUnitTypeTable)
        .def("addUnitType", &UnitTypeTable::addUnitType)
        .def("getUnitTypes", &UnitTypeTable::getUnitTypes, py::return_value_policy::reference)
        .def("getMoveConflictResolutionStrategy", &UnitTypeTable::getMoveConflictResolutionStrategy)
        .def("getUnit", &UnitTypeTable::getUnitTypes);


    py::class_<Unit>(m, "Unit")
        .def(py::init<long, int, UnitType*, int, int, int>())
        .def(py::init<int, UnitType*, int, int, int>())
        .def(py::init<int, UnitType*, int, int>())
        .def(py::init<const Unit>())
        .def("getPlayer", &Unit::getPlayer)
        .def("getType", &Unit::getType, py::return_value_policy::reference)
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
        .def("getUnitActions", &Unit::getUnitActions, py::return_value_policy::reference)
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
        .def("getName", &UnitType::getName)
        .def("getIsStockpile", &UnitType::getIsStockpile)
        .def("getCanMove", &UnitType::getCanMove)
        .def("produces", &UnitType::produces);

}

