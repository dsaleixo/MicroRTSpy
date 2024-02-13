#include "GameState.h"
#include "PhysicalGameState.h"
#include "UnitTypeTable.h"
#include <unordered_map>
#include <cstdlib>

GameState::GameState(PhysicalGameState* a_pgs, UnitTypeTable* a_utt) {
	this->pgs =  a_pgs;
	this->utt = a_utt;
	this->time = 0;

}

Player GameState::getPlayer(int ID) {
    return this->pgs->getPlayer(ID);
}


bool GameState::canExecuteAnyAction(int pID) {
    for (Unit *u : this->pgs->getUnits()) {
        if (u->getPlayer() == pID) {
            if (unitActions.find(u) == unitActions.end()) return true;
        }
    }
    return false;
}

int GameState::winner() {
    return this->pgs->winner();
}

bool GameState::gameover() {
    return  this->pgs->gameover();
}

int GameState::getNextChangeTime() {
    int nextChangeTime = -1;

    for (Player &player : this->pgs->players) {
        if (this->canExecuteAnyAction(player.getID())) return this->getTime();
    }

    for (auto &Puaa : this->unitActions) {
        UnitActionAssignment& uaa = Puaa.second;
        int t = uaa.time + uaa.action->ETA(uaa.unit);
        if (nextChangeTime == -1 || t < nextChangeTime) nextChangeTime = t;
    }

    if (nextChangeTime == -1) return this->getTime();
    return nextChangeTime;
}

bool GameState::integrityCheck() {
    vector<Unit*> alreadyUsed;
   
    
    for (auto& it : this->unitActions) {
  
        Unit* u = it.second.unit;
        
        if (std::find(pgs->getUnits().begin(), pgs->getUnits().end(), u) == pgs->getUnits().end()) {
             cout << "integrityCheck: unit does not exist!" << endl;;
            return false;
        }
        
        if (std::find(alreadyUsed.begin(), alreadyUsed.end(), u) != alreadyUsed.end()) {
             cout << "integrityCheck: two actions to the same unit!" << endl;
            return false;
        }
        
        
       
    }
   
    return true;
}



bool GameState::issue(PlayerAction &pa) {
    bool returnValue = false;
    

    
    for (auto& p : pa.actions) {
        // cout << "sas01" << endl;
        //            if (p.m_a==null) {
        //                System.err.println("Issuing an action to a null unit!!!");
        //                System.exit(1);
        //            }
        //            if (unitActions.get(p.m_a)!=null) {
        //                System.err.println("Issuing an action to a unit with another action!");
        //            } else 
        //            {
                        // check for conflicts:
        ResourceUsage ru = p.second.resourceUsage(p.first, pgs);
    
        for (auto& Puaa : this->unitActions) {
            auto& uaa = Puaa.second;
           
            bool aux = uaa.action->resourceUsage(uaa.unit, pgs).consistentWith(ru, this);
            
            if (!aux) {
                // conflicting actions:
              
                if (uaa.time == time) {
                    // The actions were issued in the same game cycle, so it's normal
                    bool cancel_old = false;
                    bool cancel_new = false;
                    switch (this->utt->getMoveConflictResolutionStrategy()) {
                    default:
                        // cout << "Unknown move conflict resolution strategy in the UnitTypeTable!: " << utt->getMoveConflictResolutionStrategy() << endl;
                        // cout << "err.println(""Defaulting to MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH" << endl;
                    case UnitTypeTable::MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH:
                        cancel_old = cancel_new = true;
                        break;
                    case UnitTypeTable::MOVE_CONFLICT_RESOLUTION_CANCEL_RANDOM:
                        if (rand() % 2 == 0) cancel_new = true;
                        else cancel_old = true;
                        break;
                    case UnitTypeTable::MOVE_CONFLICT_RESOLUTION_CANCEL_ALTERNATING:
                        if ((unitCancelationCounter % 2) == 0) cancel_new = true;
                        else cancel_old = true;
                        unitCancelationCounter++;
                        break;
                    }
                   
                    int duration1 = uaa.action->ETA(uaa.unit);
                    int duration2 = p.second.ETA(p.first);
                    if (cancel_old) {
                        //                                System.out.println("Old action canceled: " + uaa.unit.getID() + ", " + uaa.action);
                        uaa.action = new UnitAction(UnitAction::TYPE_NONE, min(duration1, duration2));
                    }
                    if (cancel_new) {
                        //                                System.out.println("New action canceled: " + p.m_a.getID() + ", " + p.m_b);
                        p = make_pair(p.first, UnitAction(UnitAction::TYPE_NONE, min(duration1, duration2)));
                    }
                    
                }
                else {
                    // This is more a problem, since it means there is a bug somewhere...
                    // (probably in one of the AIs)
                    // cout << "Inconsistent actions were executed!" << endl;
                    // cout << uaa.toString() << endl;
                    // cout << "  Resources: " << uaa.action->resourceUsage(uaa.unit, pgs).toString() << endl;
                    // cout << p.first->toString() + " assigned action " + p.second.toString() << " at time " << time << endl;
                    // cout << "  Resources: " + ru.toString() << endl;
                    //// cout << "Player resources: " << this->pgs->getPlayer(0).getResources().toString() << ", " + pgs.getPlayer(1).getResources() << endl;
                    // cout << "Resource Consistency: " << uaa.action->resourceUsage(uaa.unit, pgs).consistentWith(ru, this) << endl;

                    /*
                    try {
                        throw new Exception("dummy");   // just to be able to print the stack trace
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                    */
                    // only the newly issued action is cancelled, since it's the problematic one...
                    // cout << "sas7" << endl;
                    p.second = UnitAction(UnitAction::TYPE_NONE);
                }
            }
            
        }
     
        UnitActionAssignment* uaa = new UnitActionAssignment(p.first, new UnitAction(p.second), time);
        
        pair<Unit*, UnitActionAssignment> temp{ p.first, *uaa };
       
        unitActions.insert(temp);
       

        if (p.second.type != UnitAction::getTYPE_NONE()) returnValue = true;
        // cout << "sas11 " << pa.actions.size() << endl;
        //                System.out.println("Issuing action " + p.m_b + " to " + p.m_a);                
        //            }

    }
    
    return returnValue;
}



bool GameState::issueSafe(PlayerAction& pa){
   
  


    // cout << "ok1" << endl;
    if (!pa.integrityCheck()) { cout << "PlayerAction inconsistent before 'issueSafe'" << endl;; }
  
    if (!integrityCheck()) { cout << "GameState inconsistent before 'issueSafe'" << endl;}
    for (pair<Unit*, UnitAction>& p : pa.actions) {
     
        if (p.first == nullptr) {
            // cout<<"Issuing an action to a null unit!!!"<<endl;
            return false;
        }
       
        if (!p.first->canExecuteAction(p.second, *this)) {
            if (REPORT_ILLEGAL_ACTIONS) {
                 cout << "Issuing a non legal action to unit " + p.second.toString() + "!! Ignoring it..." << endl;
            }
            // replace the action by a NONE action of the same duration:
            int l = p.second.ETA(p.first);
             
            p.second =  UnitAction(UnitAction::TYPE_NONE, l);
        }
      
        // get the unit that corresponds to that action (since the state might have been cloned):
        if (std::find(pgs->getUnits().begin(), pgs->getUnits().end(), p.first) != pgs->getUnits().end()) {
            bool found = false;
            for (Unit* u : pgs->units) {
                if (//u.getClass() == p.m_a.getClass() &&
                    //                        u.getID() == p.m_a.getID()) {
                    u->getX() == p.first->getX() &&
                    u->getY() == p.first->getY()) {
                    p.first = u;
                    found = true;
                    break;
                }
            }
           
            if (!found) {
                // cout << "Inconsistent order: pa" << endl;
            }
        }

        {
            // check to see if the action is legal!
            ResourceUsage r = p.second.resourceUsage(p.first, pgs);
            for (int position : r.getPositionsUsed()) {
                int y = position / pgs->getWidth();
                int x = position % pgs->getWidth();
                if (pgs->getTerrain(x, y) != PhysicalGameState::TERRAIN_NONE ||
                    pgs->getUnitAt(x, y) != nullptr) {
                    UnitAction new_ua =  UnitAction(UnitAction::TYPE_NONE, p.second.ETA(p.first));
                    // cout << "Player " << p.first->getPlayer() << " issued an illegal move action (to " << x + "," << y + ") to unit " + p.first->getID() << " at time " + this->getTime() << ", cancelling and replacing by " + new_ua.toString() << endl;
                    // cout << "    Action: " + p.second.toString() << endl;
                    // cout << "    Resources used by the action: " << r.toString() << endl;
                    // cout << "    Unit at that coordinate " << pgs->getUnitAt(x, y) << endl;
                    p.second = new_ua;
                }
            }
        }


    }
  
    

    bool returnValue = issue(pa);
   
    if (!integrityCheck()) // cout << "GameState inconsistent after 'issueSafe': pa " << endl;
    return returnValue;
}


int GameState::getTime() {
	return this->time;
}

PhysicalGameState* GameState::getPhysicalGameState() {
	return this->pgs;
}



bool GameState::cycle() {
	this->time++ ;
    
    vector<UnitActionAssignment> readyToExecute;
    for (auto& uaa : this->unitActions) {
        
        // cout << uaa.second.unit->toString() << endl;
        // cout << uaa.second.action->toString() << endl;
        // cout << uaa.second.action->ETA(uaa.first) + uaa.second.time  << endl;
        if (uaa.second.action->ETA(uaa.first) + uaa.second.time <= time) readyToExecute.push_back(uaa.second);
        // cout << "eeee1" << endl;
    }
  
    // execute the actions:
    for (UnitActionAssignment& uaa : readyToExecute) {
        unitActions.erase(uaa.unit);

        //            System.out.println("Executing action for " + u + " issued at time " + uaa.time + " with duration " + uaa.action.ETA(uaa.unit));
        uaa.action->execute(uaa.unit, *this);
        
    }

    return false;
	return true;
}

UnitActionAssignment* GameState::getActionAssignment(Unit* u) {
  
   auto got = this->unitActions.find(u);
  
   if (got == this->unitActions.end())return nullptr;
   
    UnitActionAssignment& aux = this->unitActions.at(u);
    
    return &aux;
}

void GameState::removeUnit(Unit* u) {
    
    this->pgs->removeUnit(u);

    this->unitActions.erase(u);
   
}
