#include "UnitActionAssignment.h"
#include "UnitAction.h"
#include "Unit.h"

long UnitActionAssignment::getIdUnit() {
    return this->id_unit;
}
UnitAction& UnitActionAssignment::getUnitAction() {
    return this->action;
}
int UnitActionAssignment::getTime() {
    return this->time;
}



UnitActionAssignment::~UnitActionAssignment() {
	
    
}
UnitActionAssignment::UnitActionAssignment(long a_unit, UnitAction &a_action, int a_time) {
    this->id_unit = a_unit;
    this->action = a_action;
    //if (action == nullptr) {
    //    cout << "UnitActionAssignment with null action!" < endl;
    //}
    this->time = a_time;
}

string UnitActionAssignment::toString() {
    return "uaa : {"+to_string(this->time)+", " + to_string(this->id_unit) + ", " + this->action.toString() + "}";
}