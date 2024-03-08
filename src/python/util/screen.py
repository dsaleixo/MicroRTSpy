from asyncio.windows_events import NULL
import pygame, sys
from pygame.locals import *
from MicroRTSpy import  UnitTypeTable
from MicroRTSpy import PhysicalGameState
from MicroRTSpy import UnitType
from MicroRTSpy import GameState
from MicroRTSpy import UnitActionAssignment
from MicroRTSpy import UnitAction



from pygame.time import delay






class ScreenMicroRTS:
    def __init__(self, gs:GameState) -> None:
        self._dx = 640
        self._dy = 640
        self._window = pygame.display.set_mode((640, 640))
        self._pgs = gs.getPhysicalGameState()
        self._gs = gs
        aux = 255
        self._wallColor = (0, aux*0.33, 0)
        self._po0color = (0, 0, aux*0.25)
        self._po1color =  (aux*0.25, 0, 0)
        self._pobothcolor = (aux*0.25, 0, aux*0.25)
        self._gray = (127,127,127)
        self._green = (0,255,0)
        self._blue = (0,0,255)
        self._red =  (255,0,0)
        self._white = (255,255,255)
        self._lightGray = (200,200,200)
        self._orange =(255,100,10)
        self._yellow = (255,255,0)
        self._cyan = (0, 255, 255)

        pygame.font.init()                               
        self._fonte=pygame.font.get_default_font()              
        self._fontesys=pygame.font.SysFont(self._fonte, 15)      
        self._fontesys2=pygame.font.SysFont(self._fonte, 25)    



        self._width = self._pgs.getWidth()        
        self._height = self._pgs.getHeight()    
        
        

        self._gridx = (self._dx-64)/self._width
        self._gridy = (self._dy-64)/self._height
        self._grid =  min(self._gridx,self._gridy)
        self._sizex = self._grid*self._width
        self._sizey = self._grid*self._height
        self._displacementX=self._dx/2 - self._sizex/2
        self._displacementY=self._dy/2 - self._sizey/2;
       
    def t(self, p):
        return [self._displacementX+p[0],self._displacementY+p[1]]
        
        
    def drawGrid(self)->None:
        
        
        for j in range(self._width):
            for i in range(self._height):
             
                if self._pgs.getTerrain(j,i)==PhysicalGameState.getTERRAIN_WALL(): 
                    p = self.t([j*self._grid, i*self._grid])
                    pygame.draw.rect(self._window, self._wallColor, 
                                      [p[0], p[1], self._grid, self._grid])
             
        

        
        for i in range(self._width+1):
            pygame.draw.line(self._window, self._gray, 
                                self.t([i*self._grid, 0]), 
                                self.t([i*self._grid, self._height*self._grid]), 2)
           
        for i in range(self._height+1):
            pygame.draw.line(self._window, self._gray, 
                                self.t([0, i*self._grid]), 
                                self.t([self._width*self._grid, i*self._grid]), 2)
            
        unitCount0 ="10"
        unitCount1 = "10"
        eval0 = "0"
        eval1 = "0"
        info = "T: " + str(self._gs.getTime()) + ", P₀: " + unitCount0 + " (" + eval0 + "), P₁: " + unitCount1 + " (" + eval1 + ")";
        
        
        txttela = self._fontesys2.render(info, 1, (255,255,255))  ##### renderiza o texto na cor desejadas
      
        p =  self.t([10, self._dy -15])
        self._window.blit(txttela,(10,self._dy -15)  )
       
          
    def drawUnits(self):
        
        for u in self._pgs.getUnits().values():
            
            uaa = self._gs.getActionAssignment(u)
            
            if uaa != None:
                
                offsx = 0;
                offsy = 0;
                action = uaa.getUnitAction()
                type_action =  action.getType()
                if type_action ==UnitAction.getTYPE_ATTACK_LOCATION() :
                    offsx = (action.getLocationX() - u.getX())*self._grid;
                    offsy = (action.getLocationY() - u.getY())*self._grid;
                else :
                    if action.getDirection()==UnitAction.getDIRECTION_UP(): offsy = -self._grid;
                    if action.getDirection()==UnitAction.getDIRECTION_RIGHT(): offsx = self._grid;
                    if action.getDirection()==UnitAction.getDIRECTION_DOWN(): offsy = self._grid;
                    if action.getDirection()==UnitAction.getDIRECTION_LEFT(): offsx = -self._grid;
                
                #print(u.toString(),UnitAction.getTYPE_ATTACK_LOCATION(),type_action)
                if UnitAction.getTYPE_MOVE() == type_action:
                    
                    pygame.draw.line(self._window, self._gray, 
                                self.t([u.getX()*self._grid+self._grid/2, u.getY()*self._grid+self._grid/2]), 
                                self.t([u.getX()*self._grid+self._grid/2 + offsx, u.getY()*self._grid+self._grid/2 + offsy]), 3)
                    
                elif UnitAction.getTYPE_ATTACK_LOCATION() == type_action:
                    #print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
                    pygame.draw.line(self._window, self._red, 
                                self.t([u.getX()*self._grid+self._grid/2, u.getY()*self._grid+self._grid/2]), 
                                self.t([u.getX()*self._grid+self._grid/2 + offsx, u.getY()*self._grid+self._grid/2 + offsy]), 3)
            
                    
                elif UnitAction.getTYPE_HARVEST() == type_action or type_action ==   UnitAction.getTYPE_RETURN(): 
                    pygame.draw.line(self._window, self._white, 
                                self.t([u.getX()*self._grid+self._grid/2, u.getY()*self._grid+self._grid/2]), 
                                self.t([u.getX()*self._grid+self._grid/2 + offsx, u.getY()*self._grid+self._grid/2 + offsy]), 3)
    
                elif UnitAction.getTYPE_PRODUCE() == type_action:
                    pygame.draw.line(self._window, self._blue, 
                            self.t([u.getX()*self._grid+self._grid/2, u.getY()*self._grid+self._grid/2]), 
                            self.t([u.getX()*self._grid+self._grid/2 + offsx, u.getY()*self._grid+self._grid/2 + offsy]), 3)
                     # draw building progress bar
                    ETA = uaa.getTime() + uaa.getUnitAction().ETA(u) - self._gs.getTime();
                    p = self.t([u.getX() * self._grid + offsx, u.getY() * self._grid + offsy])
                    pygame.draw.rect(self._window, self._blue, 
                                      [p[0], p[1], 
                                       self._grid - int(self._grid * (ETA / uaa.getUnitAction().ETA(u))), 
                                       (self._grid / 5.0)])
                 

            reduction = 0
            
            colorPlayer = None
            if u.getPlayer() == 0:
                colorPlayer = self._blue
            elif u.getPlayer() == 1:
                colorPlayer = self._red;
            
            ut = u.getType()
            color = self._white
            if ut.getName() == "Resource":
                color = self._green;
            if ut.getName() == "Base":
                color = self._white
                
            if ut.getName() == "Barracks":
                color = self._lightGray
            
            if ut.getName() == "Worker":
                color = self._gray
                reduction = self._grid/4;
            
            if ut.getName() == "Light":
                color = self._orange
                reduction = self._grid/8;
            
            if ut.getName() == "Heavy":
                color = self._yellow
            if ut.getName() =="Ranged":
                color = self._cyan
                reduction = self._grid/8;
            
            if not ut.getCanMove():
                p = self.t([u.getX()*self._grid+reduction, u.getY()*self._grid+reduction])
  
                pygame.draw.rect(self._window, color, 
                                      [p[0], p[1], 
                                       self._grid-reduction*2, self._grid-reduction*2])
                if colorPlayer != None:
                    pygame.draw.rect(self._window, colorPlayer,
                                  [p[0], p[1], 
                                   self._grid-reduction*2, self._grid-reduction*2],3)

            else:
                p = self.t([u.getX()*self._grid+reduction, u.getY()*self._grid+reduction])
            
                pygame.draw.ellipse(self._window, color, 
                                      [p[0], p[1], 
                                       self._grid-reduction*2, self._grid-reduction*2])
                if colorPlayer != None:
                    pygame.draw.ellipse(self._window, colorPlayer,
                                  [p[0], p[1], 
                                   self._grid-reduction*2, self._grid-reduction*2],1)

            
            if ut.getIsStockpile():
                res = self._pgs.getPlayer(u.getPlayer()).getResources()
                txttela = self._fontesys.render(str(res), 1, (0,0,0))  ##### renderiza o texto na cor desejadas
                p =  self.t([u.getX()*self._grid + self._grid/2 , u.getY()*self._grid + self._grid/2])
                self._window.blit(txttela,(p[0]-6,p[1]-6)  )
                
            if u.getResources()!=0:
                res = u.getResources()
                txttela = self._fontesys.render(str(res), 1, (0,0,0))  ##### renderiza o texto na cor desejadas
                p =  self.t([u.getX()*self._grid + self._grid/2 , u.getY()*self._grid + self._grid/2])
                self._window.blit(txttela,(p[0]-6,p[1]-6)  )

            if u.getHitPoints()<u.getMaxHitPoints():
                p = self.t([u.getX() * self._grid, u.getY() * self._grid ])
                pygame.draw.rect(self._window, self._red, 
                                      [p[0], p[1], 
                                       self._grid, (self._grid / 5.0)])
                
                p = self.t([u.getX() * self._grid, u.getY() * self._grid ])
                pygame.draw.rect(self._window, self._green, 
                                      [p[0], p[1], 
                                       (self._grid*u.getHitPoints())/u.getMaxHitPoints(),
                                      (self._grid / 5.0)])
                
                
               


    def draw(self):
        self._window.fill((0,0,0))
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
        

        self.drawGrid()
        self.drawUnits()
        pygame.display.flip()        

if __name__ == "__main__":
    utt = UnitTypeTable(2);
    
    #pgs = PhysicalGameState.load("../maps/basesWorkers32x32A.xml",utt);
    pgs = PhysicalGameState.load("../maps/mapadavid2.xml",utt);
  
    #pgs = PhysicalGameState.load("../maps/BWDistantResources32x32.xml",utt)
   
    screen = ScreenMicroRTS(pgs)
    cont = 0
    while True:
        print("time ",cont)
                

        screen.draw()
        delay(2000)
        cont+=1;