#include "pugixml.hpp"
#include <iostream>
#include "PhysicalGameState.h"
#include "UnitTypeTable.h"
#include "Player.h"
#include "Unit.h"

int main() {
    UnitTypeTable utt = UnitTypeTable(2);
    cout << utt.VERSION_NON_DETERMINISTIC << endl;
    PhysicalGameState psg = PhysicalGameState::load("basesWorkers32x32A.xml", utt);
    for (int i = 0; i < 3; i++) {
        cout << "Units" << endl;
        for (Unit* u : psg.getUnits()) {
            cout << u->toString() << endl;
        }
    }
}