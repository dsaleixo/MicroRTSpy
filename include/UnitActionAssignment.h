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
     long id_unit;
     UnitAction action;
     int time;
     ~UnitActionAssignment();
     UnitActionAssignment(long a_id, UnitAction &a_action, int a_time);
     long getIdUnit();
     UnitAction& getUnitAction();
     int getTime();

     string toString();
     
};

#endif