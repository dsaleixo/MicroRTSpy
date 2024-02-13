#include "UnitActionAssignment.h"
#include "UnitAction.h"
#include "Unit.h"

Unit* UnitActionAssignment::getUnit() {
    return this->unit;
}
UnitAction* UnitActionAssignment::getUnitAction() {
    return this->action;
}
int UnitActionAssignment::getTime() {
    return this->time;
}



UnitActionAssignment::~UnitActionAssignment() {
	this->unit = nullptr;
    this->action = nullptr;
    
}
UnitActionAssignment::UnitActionAssignment(Unit* a_unit, UnitAction *a_action, int a_time) {
    this->unit = a_unit;
    this->action = a_action;
    //if (action == nullptr) {
    //    cout << "UnitActionAssignment with null action!" < endl;
    //}
    this->time = a_time;
}

string UnitActionAssignment::toString() {
    return "uaa : {"+to_string(this->time)+", " + this->unit->toString() + ", " + this->action->toString() + "}";
}