#include "pugixml.hpp"
#include <iostream>
#include "PhysicalGameState.h"
#include "UnitTypeTable.h"
#include "Player.h"
#include "Unit.h"
#include "unordered_map"

int main() {
    UnitTypeTable utt = UnitTypeTable(2);
    cout << utt.VERSION_NON_DETERMINISTIC << endl;
    unordered_map<long, Unit> map;
    
    PhysicalGameState psg = PhysicalGameState::load("basesWorkers32x32A.xml", utt);
    
    cout << "Units" << endl;
    for (auto& u : psg.getUnits()) {
        cout << u.second.toString() << endl;
    }
}