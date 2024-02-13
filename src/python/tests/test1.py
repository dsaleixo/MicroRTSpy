import sys
sys.path.append("../..")

from MicroRTSpy import  UnitTypeTable
from MicroRTSpy import PhysicalGameState
from MicroRTSpy import UnitType
from MicroRTSpy import GameState
from MicroRTSpy import PlayerAction
from MicroRTSpy import UnitAction
from MicroRTSpy import Unit
from MicroRTSpy import UnitActionAssignment


import random

from util.screen import ScreenMicroRTS

import time

class Test1:


        @staticmethod
        def getRandMove(u : Unit, gs : GameState) -> UnitAction:
            a = Test1.getAttack(u,gs)
            if a !=None:
                return a

            g = random.randrange(0,7,1)
            #g = 0
            if g <3: return UnitAction(UnitAction.getTYPE_MOVE(), UnitAction.getDIRECTION_LEFT())
            if g <5: return UnitAction(UnitAction.getTYPE_MOVE(), UnitAction.getDIRECTION_UP())
            if g <6: return UnitAction(UnitAction.getTYPE_MOVE(), UnitAction.getDIRECTION_RIGHT())
            
            if g <7: return UnitAction(UnitAction.getTYPE_MOVE(), UnitAction.getDIRECTION_DOWN())
            

        @staticmethod
        def getAttack(u : Unit, gs : GameState) -> UnitAction:
            a = None
            actions = u.getUnitActions(gs);
            for aa in actions:
                if aa.getActionName() == "attack_location":
                    return aa
            return a
        


        @staticmethod
        def getActionsSimples(gs : GameState, player :int ) -> PlayerAction:
            pgs = gs.getPhysicalGameState()
            pa = PlayerAction()
          
            for u in pgs.getUnits():
                
                if u.getPlayer()==player  and gs.getActionAssignment(u)==None :
                   
                   actions = u.getUnitActions(gs);
            
                   a = Test1.getRandMove(u,gs)
        
                   pa.addUnitAction(u,a)
            return pa
        

        @staticmethod
        def test(map):
            utt = UnitTypeTable(2);
            #pgs = PhysicalGameState.load("../maps/basesWorkers32x32A.xml",utt);
            #pgs = PhysicalGameState.load("../maps/mapadavid2.xml",utt);
            #pgs = PhysicalGameState.load("../maps/BWDistantResources32x32.xml",utt)
            pgs = PhysicalGameState.load(map,utt)
            gs = GameState(pgs,utt)
            screen = ScreenMicroRTS(gs)
            cont = 0
            show = True;
            while not gs.gameover():
                print("time ",cont)   
                if show :
                    screen.draw()
                    time.sleep(0.5) 
                print("jogador0")
                pa0 = Test1.getActionsSimples(gs,0)
                print()
                print("jogador1")
                pa1 = Test1.getActionsSimples(gs,1)
                show = gs.getTime()==gs.getNextChangeTime()
                show = True
                gs.issueSafe(pa0)
                gs.issueSafe(pa1)
                
                
                
                gs.cycle()
                
                cont+=1;
            
                
                    
             
            print("winner = ", gs.winner())


                

        