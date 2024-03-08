from .AbstractAction import AbstractAction
from MicroRTSpy import Unit,UnitAction,ResourceUsage,GameState,AStarPathFinding

class Harvest(AbstractAction):
    
    
    def toString(self):
        return "faz "

    def __init__(self, u : Unit,  a_target : Unit,  a_base : Unit,  a_pf : AStarPathFinding) :
        super().__init__(u);
        self._target = a_target;
        self._base = a_base;
        self._pf = a_pf;
    
    
    
    def  getTarget(self)->Unit :
        return self._target
    
    
    def getBase(self)->Unit :
        return self._base
    
    
   # public boolean completed(GameState gs) {
   #     return !gs.getPhysicalGameState().getUnits().contains(target);
   # }
    
    '''
    public boolean equals(Object o)
    {
        if (!(o instanceof Harvest)) return false;
        Harvest a = (Harvest)o;
        return target.getID() == a.target.getID() && base.getID() == a.base.getID()
            && pf.getClass() == a.pf.getClass();
    }
    

    public void toxml(XMLWriter w)
    {
        w.tagWithAttributes("Harvest","unitID=\""+unit.getID()+"\" target=\""+target.getID()+"\" base=\""+base.getID()+"\" pathfinding=\""+pf.getClass().getSimpleName()+"\"");
        w.tag("/Harvest");
    }    
    '''
    
    def execute(self,  gs :GameState,  ru : ResourceUsage)->UnitAction :
        pgs = gs.getPhysicalGameState();
        if (self._unit.getResources()==0) :
            # go get resources:
            #        System.out.println("findPathToAdjacentPosition from Harvest: (" + target.getX() + "," + target.getY() + ")");
            move = self._pf.findPathToAdjacentPosition(self._unit, self._target.getX()+self._target.getY()*gs.getPhysicalGameState().getWidth(), gs);
            print("aki ",move.toString())
            if move.getType()!=UnitAction.getTYPE_NONE():
                
                if gs.isUnitActionAllowed(self._unit, move):
                    print("aki ",move.toString(),self._unit.toString())
                    return move;
                return None
            
            
            # harvest:
            if self._target.getX() == self._unit.getX() and self._target.getY() == self._unit.getY()-1 :
                return  UnitAction(UnitAction.getTYPE_HARVEST(),UnitAction.getDIRECTION_UP());
            if self._target.getX() == self._unit.getX()+1 and self._target.getY() == self._unit.getY():
                return  UnitAction(UnitAction.getTYPE_HARVEST(),UnitAction.getDIRECTION_RIGHT());
            if self._target.getX() == self._unit.getX() and self._target.getY() == self._unit.getY()+1:
                return  UnitAction(UnitAction.getTYPE_HARVEST(),UnitAction.getDIRECTION_DOWN());
            if self._target.getX() == self._unit.getX()-1 and self._target.getY() == self._unit.getY():
                return  UnitAction(UnitAction.getTYPE_HARVEST(),UnitAction.getDIRECTION_LEFT());
        else :
            # return resources:
            #          System.out.println("findPathToAdjacentPosition from Return: (" + target.getX() + "," + target.getY() + ")");
            move = self._pf.findPathToAdjacentPosition(self._unit, self._base.getX()+self._base.getY()*gs.getPhysicalGameState().getWidth(), gs);
            if move.getType()!=UnitAction.getTYPE_NONE():
                if gs.isUnitActionAllowed(self._unit, move):
                    return move;
                return None;
            

            # harvest:
            if self._base.getX() == self._unit.getX() and self._base.getY() == self._unit.getY()-1:
                return  UnitAction(UnitAction.getTYPE_RETURN(),UnitAction.getDIRECTION_UP())
            if self._base.getX() == self._unit.getX()+1 and self._base.getY() == self._unit.getY():
                return  UnitAction(UnitAction.getTYPE_RETURN(),UnitAction.getDIRECTION_RIGHT())
            if self._base.getX() == self._unit.getX() and self._base.getY() == self._unit.getY()+1:
                return  UnitAction(UnitAction.getTYPE_RETURN(),UnitAction.getDIRECTION_DOWN());
            if self._base.getX() == self._unit.getX()-1 and self._base.getY() == self._unit.getY():
                return  UnitAction(UnitAction.getTYPE_RETURN(),UnitAction.getDIRECTION_LEFT());
        
        return None
        