
from MicroRTSpy import  UnitTypeTable
from MicroRTSpy import PhysicalGameState
from MicroRTSpy import UnitType
from MicroRTSpy import GameState
from MicroRTSpy import PlayerAction
from MicroRTSpy import UnitAction
from MicroRTSpy import Unit
from MicroRTSpy import UnitActionAssignment
from MicroRTSpy import AStarPathFinding
from MicroRTSpy import Player
from MicroRTSpy import ResourceUsage



from .Move import Move
from .Train import Train
from .Build import Build
from .Attack import Attack
from .Idle import Idle
from .Harvest import Harvest


class AbstractionLayerAI:
    VERIFY_ACTION_CORRECTNESS = False;
    def __init__(self, pgs : PhysicalGameState):
        self._actions = {}
        
        self._pf = AStarPathFinding(pgs.getWidth(), pgs.getHeight())
    # In case the GameState is cloned, and the Unit pointers in the "actions" map change, this variable
    # saves a pointer to the previous GameState, if it's different than the current one, then we need to find a mapping
    # between the old units and the new ones
        self.lastGameState = None
        
    def resert(self):
        self.actions.clear()
        

    def translateActions(self, player : int,  gs : GameState) :
        pgs = gs.getPhysicalGameState()
        pa =  PlayerAction()
        desires = []
        
        #self._lastGameState = gs;
        
        # Execute abstract actions:
        toDelete = []
        ru =  ResourceUsage();
        for  aa in self._actions.values():
            if not aa.getUnit() in pgs.getUnits():
                # The unit is dead:
                toDelete.remove(aa._unit)
            else :
                if aa.completed(gs):
                    toDelete.add(aa._unit);
                else :
                    if gs.getActionAssignment(aa._unit) == None:
                        ua = aa.execute(gs, ru)
                        if ua != None:
                            if AbstractionLayerAI.VERIFY_ACTION_CORRECTNESS:
                                # verify that the action is actually feasible:
                                ual = aa._unit.getUnitActions(gs);
                                if ua in ual:
                                    desires.append((aa._unit, ua))
                                
                            else :
                                desires.append((aa._unit, ua))
                            
                            ru.merge(ua.resourceUsage(aa._unit, pgs))
          
        for  u in toDelete:
            self._actions.remove(u);
        
        
        # compose desires:
        r = gs.getResourceUsage();
       
        pa.setResourceUsage(r);
        
        for  desire in desires:
            r2 = desire[1].resourceUsage(desire[0], pgs)
            if pa.consistentWith(r2, gs):
                pa.addUnitAction(desire[0], desire[1])
                pa.getResourceUsage().merge(r2)
         
        #pa.fillWithNones(gs, player, 10)
        
        return pa
    
    def getAbstractAction(self, u : Unit) :
        if u in self._actions:
            return self._actions[u]
        else:
            None
   

    def move(self, u : Unit, x : int,  y : int):
        self._actions[u] = Move(u, x, y, self._pf)
    

    def train(self, u : Unit,  unit_type : UnitType) :
        self._actions[u] = Train(u, unit_type)
        
    

    def train(self, u : Unit, unit_type : UnitType, preference : int= None) -> None:
        self._actions[u] = Train(u, unit_type, preference)
       
    
    
    def build(self,  u : Unit,  unit_type : UnitType, x : int,  y : int) -> None:
        self._actions[u] = Build(u, unit_type, x, y, self._pf)
       # actions.put(u, new Build(u, unit_type, x, y, pf));
    

    def harvest(self, u : Unit,  target : Unit,  base : Unit) -> None:
        self._actions[u] = Harvest(u, target, base, self._pf)
        #actions.put(u, new Harvest(u, target, base, pf));
    

    def attack(self, u : Unit, target : Unit) -> None:
        self._actions[u] = Attack(u, target, self._pf)
        

    def idle(self, u : Unit) :
        self._actions[u] = Idle(u)

    def findBuildingPosition(self, reserved : list[int], desiredX : int, desiredY : int, p : Player, gs : GameState) -> int:
        
        x = -1
        y = -1
        pgs = gs.getPhysicalGameState()

     
        
        for l in range(1,max(pgs.getHeight(), pgs.getWidth())):
            for side in range(4):
                
                    if side == 0:#up
                        y = desiredY - l;
                        if y < 0 :
                            continue;
                        
                        for dx in range(-l,l+1):
                            x = desiredX + dx;
                            if x < 0 or x >= pgs.getWidth():
                                continue;
                            pos = x + y * pgs.getWidth();
                            if not pos in reserved and gs.free(x,y) :
                                return pos;
                           
                        
                    elif side == 1:#right
                        x = desiredX + l;
                        if x >= pgs.getWidth():
                            continue;
                        
                        for dy in range(-l,l+1):
                            y = desiredY + dy;
                            if y < 0 or y >= pgs.getHeight():
                                continue;
                            pos = x + y * pgs.getWidth();
                            if (not pos in reserved) and gs.free(x,y): 
                                return pos;
                            
                        
                    elif side == 2:#down
                        y = desiredY + l
                        if y >= pgs.getHeight():
                            continue
                        
                        for dx in range(-l,l+1):
                            x = desiredX + dx;
                            if x < 0 or x >= pgs.getWidth() :
                                continue;
                            
                            pos = x + y * pgs.getWidth();
                            if (not pos in reserved) and gs.free(x,y): 
                                return pos
                       
                    elif side== 3:#left
                        x = desiredX - l;
                        if x < 0: 
                            continue;
                      
                        for dy in range(-l,l+1):
                            y = desiredY + dy;
                            if y < 0 or y >= pgs.getHeight():
                                continue;
                            
                            pos = x + y * pgs.getWidth();
                            if (not pos in reserved) and gs.free(x,y):
                                return pos;
                     
        return -1;

    def buildIfNotAlreadyBuilding(self,  u : Unit,  utype : UnitType,  desiredX : int,  desiredY : int, reservedPositions : list[int],  p : Player,  gs : GameState) -> bool: 
        action = self.getAbstractAction(u);
#        System.out.println("buildIfNotAlreadyBuilding: action = " + action);
        pgs = gs.getPhysicalGameState()
        if not isinstance(action , Build) or action.type != utype :
            
            pos = self.findBuildingPosition(reservedPositions, desiredX, desiredY, p, gs);
           
    #           System.out.println("pos = " + (pos % pgs.getWidth()) + "," + (pos / pgs.getWidth()));
            
            self.build(u, utype, pos % pgs.getWidth(), pos // pgs.getWidth());#strange
           
            reservedPositions.append(pos);
            return True;
        else :
            return False;
        
