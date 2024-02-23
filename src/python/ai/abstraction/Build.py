from .AbstractAction import AbstractAction
from MicroRTSpy import Unit,UnitAction,ResourceUsage,GameState, AStarPathFinding,UnitType

class Build(AbstractAction):
    
    def toString(self):
            return "faz "    

    def __init__(self, u : Unit,  a_type : UnitType,  a_x: int,  a_y : int,  a_pf : AStarPathFinding):
        super().__init__(u);
        self._type = a_type
        self._x = a_x
        self._y = a_y
        self._pf = a_pf
    
        '''
    bool completed(GameState gs) {
        PhysicalGameState pgs = gs.getPhysicalGameState();
        Unit u = pgs.getUnitAt(x, y);
        return u != null;
    }
    
    
    public boolean equals(Object o)
    {
        if (!(o instanceof Build)) return false;
        Build a = (Build)o;
        return type == a.type && x == a.x && y == a.y && pf.getClass() == a.pf.getClass();
    }
    

    public void toxml(XMLWriter w)
    {
        w.tagWithAttributes("Build","unitID=\""+unit.getID()+"\" type=\""+type.name+"\" x=\""+x+"\" y=\""+y+"\" pathfinding=\""+pf.getClass().getSimpleName()+"\"");
        w.tag("/Build");
    }    
    '''
    def execute(self, gs : GameState,  ru : ResourceUsage) ->UnitAction:
        pgs = gs.getPhysicalGameState();
    #      System.out.println("findPathToAdjacentPosition to " + unit.getX() + "," + unit.getY() + " from Build: (" + x + "," + y + ")");
        move = self._pf.findPathToAdjacentPosition(self._unit, int(self._x+self._y*pgs.getWidth()), gs);
        #       System.out.println("Move: " + move);

        if move.getType()!=UnitAction.getTYPE_NONE() :
            if gs.isUnitActionAllowed(self._unit, move):
                 return move;
            return None;
        
       
        # build:
        
        ua = None;
        if self._x == self._unit.getX() and self._y == self._unit.getY()-1:
            ua =  UnitAction(UnitAction.getTYPE_PRODUCE(),UnitAction.getDIRECTION_UP(),self._type)
        if self._x == self._unit.getX()+1 and self._y == self._unit.getY():
            ua =  UnitAction(UnitAction.getTYPE_PRODUCE(),UnitAction.getDIRECTION_RIGHT(),self._type)
        if self._x == self._unit.getX() and  self._y == self._unit.getY()+1: 
            ua =  UnitAction(UnitAction.getTYPE_PRODUCE(),UnitAction.getDIRECTION_DOWN(),self._type)
        if self._x == self._unit.getX()-1 and self._y == self._unit.getY():
            ua =  UnitAction(UnitAction.getTYPE_PRODUCE(),UnitAction.getDIRECTION_LEFT(),self._type);
        
     
        if ua!=None and gs.isUnitActionAllowed(self._unit, ua):
            return ua;        
        
    #      System.err.println("Build.execute: something weird just happened " + unit + " builds at " + x + "," + y);
        return None;
    