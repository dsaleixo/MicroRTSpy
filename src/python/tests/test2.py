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
from MicroRTSpy import AStarPathFinding

import random

from util.screen import ScreenMicroRTS

import time

class Test2:


        @staticmethod
        def getMove(u : Unit, gs : GameState) -> UnitAction:
            a = Test2.getAttack(u,gs)
            if a !=None:
                return a
            pgs = gs.getPhysicalGameState()
            w  = pgs.getWidth()
            h = pgs.getHeight()
            pf  = AStarPathFinding(w,h)
            player_ad = 1 - u.getPlayer()
            u_ad = None
            for uu in pgs.getUnits():
                if uu.getPlayer() == player_ad and   uu.getType().getName() == "Base":
                    u_ad = uu
            a = pf.findPathToPositionInRange(u, u_ad.getX()+u_ad.getY()*w,1, gs)
            print(a.toString())
            print(u.toString(),u_ad.toString())
            return a

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
                
                if u.getPlayer()==player  and gs.getActionAssignment(u)==None and  u.getType().getName() == "Worker" :
                   
                   actions = u.getUnitActions(gs);
            
                   a = Test2.getMove(u,gs)
        
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
                    time.sleep(0.2) 
                print("jogador0")
                pa0 = Test2.getActionsSimples(gs,0)
                print()
                print("jogador1")
                pa1 = Test2.getActionsSimples(gs,1)
                show = gs.getTime()==gs.getNextChangeTime()
                
                gs.issueSafe(pa0)
                gs.issueSafe(pa1)
                
                
                
                gs.cycle()
                
                cont+=1;
            
                
                    
             
            print("winner = ", gs.winner())


                

        