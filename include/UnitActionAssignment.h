#ifndef UAA_H // include guard
#define UAA_H  
class UnitActionAssignment;
class UnitAction;
#include "Unit.h"
#include "UnitAction.h"
#include <string>

using namespace std;

class UnitActionAssignment {
public:  
     Unit *unit;
     UnitAction *action;
     int time;
     ~UnitActionAssignment();
     UnitActionAssignment(Unit* a_unit, UnitAction *a_action, int a_time);
     Unit* getUnit();
     UnitAction* getUnitAction();
     int getTime();

     string toString();
     
};

#endif