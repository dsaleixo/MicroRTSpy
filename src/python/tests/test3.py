import sys

from ai.abstraction.AbstractionLayerAI import AbstractionLayerAI
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

class Test3:
         
        

        @staticmethod
        def getTrain(ai : AbstractionLayerAI,gs : GameState,player : int, utt : UnitTypeTable):
            pgs = gs.getPhysicalGameState()
            
            target = None
            unit = None
            cont = 0
            utype = utt.getUnitTypeString("Heavy")
           
            for u in pgs.getUnits():
                
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Heavy" :
                    cont += 1
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Barracks" and gs.getActionAssignment(u)==None:
                    unit = u 
                
          
            if unit != None and cont <3 :
                
                #ai.buildIfNotAlreadyBuilding(unit,utype,u.getX(),u.getY()+1,reservedPositions,p,pgs);
                ai.train(unit, utype)
              


        @staticmethod
        def getBuild(ai : AbstractionLayerAI,gs : GameState,player : int, utt : UnitTypeTable):
            pgs = gs.getPhysicalGameState()
            target = None
            unit = None
            cont = 0
            utype = utt.getUnitTypeString("Barracks")
            print("ok")
            for u in pgs.getUnits():
                
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Barracks" :
                    cont += 1
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Worker" and gs.getActionAssignment(u)==None:
                    unit = u 
                
          
            if unit != None and cont <1 :
               
                reservedPositions = []
                p = gs.getPlayer(0)
                ai.buildIfNotAlreadyBuilding(unit,utype,unit.getX(),unit.getY(),reservedPositions,p,gs);
                #ai.build(unit,utype,unit.getX(),unit.getY()+1)
               


        @staticmethod
        def getHarvest(ai : AbstractionLayerAI, gs : GameState,player : int):
            
            pgs = gs.getPhysicalGameState()
            target = None
            unit = None
            base = None
            
            for u in pgs.getUnits():
                
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Base" :
                    base = u 
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Worker" and gs.getActionAssignment(u)==None:
                    unit = u 
                if u.getPlayer()==-1:
                    target = u
                 
            if unit != None and target != None and (not unit in ai._actions):
                ai.harvest(unit, target, base)
                
         
            
            return 

        @staticmethod
        def getAttack(ai : AbstractionLayerAI, gs : GameState,player : int):
            
            pgs = gs.getPhysicalGameState()
            target = None
            unit = None
          
            
            for u in pgs.getUnits():
                
                
                if player == 0 and u.getPlayer()==0 and u.getType().getName() == "Heavy" and gs.getActionAssignment(u)==None:
                    unit = u 
                if u.getPlayer()==1:
                    target = u
                 
            if unit != None and target != None and (not unit in ai._actions):
                ai.attack(unit, target)
                
         
            
            return 


        @staticmethod
        def getActions( gs : GameState,player : int, utt):
            pgs = gs.getPhysicalGameState()
            ai = AbstractionLayerAI(pgs)
            if player == 0: 
                Test3.getBuild(ai,gs,0,utt)
                Test3.getHarvest(ai,gs,0)
                Test3.getTrain(ai,gs,0,utt)
                Test3.getAttack(ai,gs,0)
               
            
            pa = ai.translateActions(player,gs)
            
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
            while not gs.gameover() and gs.getTime()<3000:
                print("time ",cont)   
                if show :
                    screen.draw()
                    time.sleep(0.1) 
                print("jogador0")
                pa0 = Test3.getActions(gs,0,utt)
                print()
                print("jogador1")
                pa1 = Test3.getActions(gs,1,utt)
                show = gs.updateScream()
                
                gs.issueSafe(pa0)
             
                gs.issueSafe(pa1)
                for a in pa0.getActions():
                    print(a[0].toString(),a[1].toString())
                
                
                gs.cycle()
                
                cont+=1;
            
                
                    
             
            print("winner = ", gs.winner())


                

        