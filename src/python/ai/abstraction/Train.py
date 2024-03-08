from .AbstractAction import AbstractAction
from MicroRTSpy import Unit,UnitAction,ResourceUsage,GameState, AStarPathFinding,UnitType,PhysicalGameState

class Train(AbstractAction):
   

    def toString(self):
        return "faz "
    
    def __init__(self, u : Unit,  a_type : UnitType, a_preference  :int = None) :
        super().__init__(u);
        self._type = a_type;
        if not a_preference ==None:
            self._preference = a_preference
        else:
            self._preference = UnitAction.getDIRECTION_NONE()
    
    
    def completed(self, pgs:GameState):
        return False;
    
    
    '''
    public boolean equals(Object o)
    {
        if (!(o instanceof Train)) return false;
        Train a = (Train)o;
        return type == a.type;
    }
    
    
    public void toxml(XMLWriter w)
    {
        w.tagWithAttributes("Train","unitID=\""+unit.getID()+"\" type=\""+type.name+"\"");
        w.tag("/Train");
    }     
    '''
    def  execute(self, gs : GameState,  ru :ResourceUsage)->UnitAction :
        #find the best location for the unit:
        pgs = gs.getPhysicalGameState();
        x = self._unit.getX();
        y = self._unit.getY();
        best_direction = -1;
        best_score = -1;
        
        if y>0 and gs.free(x,y-1):
            score = self.score(x,y-1, type, self._unit.getPlayer(), pgs)
            if UnitAction.getDIRECTION_UP()==self._preference:
                score=10000000;
            if score>best_score or best_direction==-1:
                best_score = score;
                best_direction = UnitAction.getDIRECTION_UP();     
        
        if  x<pgs.getWidth()-1 and gs.free(x+1,y):
            score = self.score(x+1,y, self._type, self._unit.getPlayer(), pgs);
            if(UnitAction.getDIRECTION_RIGHT()==self._preference):
                score=10000000;
            if score>best_score or best_direction==-1:
                best_score = score;
                best_direction = UnitAction.getDIRECTION_RIGHT();            
            

        if y<pgs.getHeight()-1 and gs.free(x,y+1):
            score = self.score(x,y+1, self._type, self._unit.getPlayer(), pgs);
            if UnitAction.getDIRECTION_DOWN()==self._preference:
                score=10000000;
            if score>best_score or best_direction==-1:
                best_score = score;
                best_direction = UnitAction.getDIRECTION_DOWN();   
           
        if x>0 and gs.free(x-1,y):
            score = self.score(x-1,y, self._type, self._unit.getPlayer(), pgs);
            if UnitAction.getDIRECTION_LEFT()== self._preference: score=10000000;
            if score>best_score or best_direction==-1: 
                best_score = score;
                best_direction = UnitAction.getDIRECTION_LEFT();
       
    
        completed = True;
        
    #       System.out.println("Executing train: " + type + " best direction " + best_direction);

       
        if best_direction!=-1:
            ua =  UnitAction(UnitAction.getTYPE_PRODUCE(),best_direction, self._type);
            
            if gs.isUnitActionAllowed(self._unit, ua):
                return ua;
       
        
       
        return None;
    
    
    def score(self,  x : int,  y : int,  type : UnitType,  player :int,  pgs :PhysicalGameState)->int :
        distance = 0;
        first = True;
                
        if self._type.getcanHarvest():
            # score is minus distance to closest resource
            for  u in pgs.getUnits().values():
                if u.getType().getisResource():
                    d = abs(u.getX() - x) + abs(u.getY() - y);
                    if first or d<distance:
                        distance = d;
                        first = False;
        else :
            # score is minus distance to closest enemy
            for  u  in pgs.getUnits().values():
                if u.getPlayer()>=0 and u.getPlayer()!=player:
                    d = abs(u.getX() - x) + abs(u.getY() - y);
                    if first or d<distance:
                        distance = d;
                        first = False;
                 

        return -distance;
    