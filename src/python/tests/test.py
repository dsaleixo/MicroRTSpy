import sys
print(sys.version)
from MicroRTSpy import PhysicalGameState
from MicroRTSpy import  PhysicalGameState
from MicroRTSpy import  UnitTypeTable
from MicroRTSpy import Player
from MicroRTSpy import Unit
 


if __name__ == '__main__':
    utt = UnitTypeTable(2);
    #print(utt.VERSION_NON_DETERMINISTIC)
    psg = PhysicalGameState.load("../maps/basesWorkers32x32A.xml",utt);

    print("Units")
    for u in psg.getUnits().values():
        print (u.toString());
    