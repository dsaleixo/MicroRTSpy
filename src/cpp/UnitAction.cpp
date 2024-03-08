#include "UnitAction.h"
#include "UnitType.h"
#include "ResourceUsage.h"
#include <string>
#include "PhysicalGameState.h"
#include "GameState.h"


using namespace std;

int UnitAction::getTYPE_NONE() { return TYPE_NONE; }
 int UnitAction::getTYPE_MOVE() { return TYPE_MOVE; }
 int UnitAction::getTYPE_HARVEST() { return TYPE_HARVEST; }
 int UnitAction::getTYPE_RETURN() { return TYPE_RETURN; }
 int UnitAction::getTYPE_PRODUCE() { return TYPE_PRODUCE; }
 int UnitAction::getTYPE_ATTACK_LOCATION() { return TYPE_ATTACK_LOCATION; }
 int UnitAction::getNUMBER_OF_ACTION_TYPES() { return TYPE_RETURN; }
 int UnitAction::getDIRECTION_NONE() { return  DIRECTION_NONE; }
 int UnitAction::getDIRECTION_UP() { return DIRECTION_UP; }
 int UnitAction::getDIRECTION_RIGHT() { return DIRECTION_RIGHT; }
 int UnitAction::getDIRECTION_DOWN() { return DIRECTION_DOWN; }
 int UnitAction::getDIRECTION_LEFT() { return DIRECTION_LEFT; }


 bool UnitAction::operator==(const UnitAction& other) {
     if (this->type != other.type) return false;
     if (this->parameter != other.parameter)return false;
     if (this->x != other.x || this->y != other.y) return false;
     if (this->unitType != nullptr && other.unitType != nullptr) {
         if (this->unitType->getName() != other.unitType->getName()) return false;
     }
     return true;

 }

 UnitAction::UnitAction() {
     this->unitType = nullptr;
 }

UnitAction::UnitAction(int a_type) {
    this->type = a_type;
    this->unitType = nullptr;
}


UnitAction::UnitAction(int a_type, int a_direction) {
    this->type = a_type;
    this->parameter = a_direction;
    this->unitType = nullptr;
}

UnitAction::UnitAction(int a_type, int a_direction, UnitType* a_unit_type) {
    this->type = a_type;
    this->parameter = a_direction;
    this->unitType = a_unit_type;
}


UnitAction::UnitAction(const UnitAction& other) {
    this->type = other.type;
    this->parameter = other.parameter;
    this->x = other.x;
    this->y = other.y;
    this->unitType = other.unitType;
}

UnitAction::~UnitAction() {
    this->unitType = nullptr;
}

UnitAction::UnitAction(int a_type, int a_x, int a_y) {
    this->type = a_type;
    this->x = a_x;
    this->y = a_y;
    this->unitType = nullptr;
    
}


bool UnitAction::equals(UnitAction &a) {

    if (a.type != this->type) {
        return false;
    }
    else if (type == TYPE_NONE || type == TYPE_MOVE || type == TYPE_HARVEST
        || type == TYPE_RETURN) {
        return a.parameter == this->parameter;
    }
    else if (type == TYPE_ATTACK_LOCATION) {
        return a.x == this->x && a.y == this->y;
    }
    else {
        return a.parameter == this->parameter && a.unitType == this->unitType;
    }
}

int UnitAction::getType() {
    return this->type;
}


UnitType* UnitAction::getUnitType() {
    return this->unitType;
}

ResourceUsage UnitAction::resourceUsage(Unit &u, PhysicalGameState* pgs) {
    ResourceUsage r_cache2;
   
    switch (type) {
        case TYPE_MOVE: {
            int pos = u.getX() + u.getY() * pgs->getWidth();
            switch (parameter) {
            case DIRECTION_UP:
                pos -= pgs->getWidth();
                break;
            case DIRECTION_RIGHT:
                pos++;
                break;
            case DIRECTION_DOWN:
                pos += pgs->getWidth();
                break;
            case DIRECTION_LEFT:
                pos--;
                break;
            }
            r_cache2.positionsUsed.push_back(pos);
        }
                      break;
        case TYPE_PRODUCE: {
            r_cache2.resourcesUsed[u.getPlayer()] += this->unitType->cost;
            int pos = u.getX() + u.getY() * pgs->getWidth();
            switch (parameter) {
            case DIRECTION_UP:
                pos -= pgs->getWidth();
                break;
            case DIRECTION_RIGHT:
                pos++;
                break;
            case DIRECTION_DOWN:
                pos += pgs->getWidth();
                break;
            case DIRECTION_LEFT:
                pos--;
                break;
            }
            r_cache2.positionsUsed.push_back(pos);
        }
        break;
    }
  
    return r_cache2;
}


int UnitAction::ETA(Unit &u) {
    
    switch (type) {
    case TYPE_NONE:
        return parameter;

    case TYPE_MOVE:
        return u.getMoveTime();

    case TYPE_ATTACK_LOCATION:
        return u.getAttackTime();

    case TYPE_HARVEST:
        return u.getHarvestTime();

    case TYPE_RETURN:
        return u.getMoveTime();

    case TYPE_PRODUCE:
        return unitType->produceTime;
    }

    return 0;
}

void UnitAction::execute(Unit &u, GameState& s) {
    PhysicalGameState *pgs = s.getPhysicalGameState();
    switch (type) {
        case TYPE_NONE:	//no-op
            break;

        case TYPE_MOVE: //moves the unit in the intended direction
            
            switch (parameter) {
            case DIRECTION_UP:
                u.setY(u.getY() - 1);
                break;
            case DIRECTION_RIGHT:
                u.setX(u.getX() + 1);
                break;
            case DIRECTION_DOWN:
                u.setY(u.getY() + 1);
                break;
            case DIRECTION_LEFT:
                u.setX(u.getX() - 1);
                break;
            }
            break;

        case TYPE_ATTACK_LOCATION: //if there's a unit in the target location, damages it
        {
            Unit &other = pgs->getUnitAt(x, y);
            if (other != Unit::unit_null) {
                int damage;
                if (u.getMinDamage() == u.getMaxDamage()) {
                    damage = u.getMinDamage();
                }
                else {
                    damage = u.getMinDamage() + (rand()%(1 + (u.getMaxDamage() - u.getMinDamage())));
                }
                other.setHitPoints(other.getHitPoints() - damage);
                if (other.getHitPoints() <= 0) {
                    s.removeUnit(other);
                }
            }
        }
        break;

        case TYPE_HARVEST: //attempts to harvest from a resource in the target direction
        {
            Unit &maybeAResource = Unit::unit_null;
            switch (parameter) {
            case DIRECTION_UP:
                maybeAResource = pgs->getUnitAt(u.getX(), u.getY() - 1);
                break;
            case DIRECTION_RIGHT:
                maybeAResource = pgs->getUnitAt(u.getX() + 1, u.getY());
                break;
            case DIRECTION_DOWN:
                maybeAResource = pgs->getUnitAt(u.getX(), u.getY() + 1);
                break;
            case DIRECTION_LEFT:
                maybeAResource = pgs->getUnitAt(u.getX() - 1, u.getY());
                break;
            }
            if (maybeAResource != Unit::unit_null && maybeAResource.getType()->isResource && u.getType()->canHarvest && u.getResources() == 0) {
                //indeed it is a resource, harvest from it
                maybeAResource.setResources(maybeAResource.getResources() - u.getHarvestAmount());
                if (maybeAResource.getResources() <= 0) {
                    s.removeUnit(maybeAResource);
                }
                u.setResources(u.getHarvestAmount());
            }
        }
        break;

        case TYPE_RETURN: //returns to base with a resource
        {
            Unit &base = Unit::unit_null;
            switch (parameter) {
            case DIRECTION_UP:
                base = pgs->getUnitAt(u.getX(), u.getY() - 1);
                break;
            case DIRECTION_RIGHT:
                base = pgs->getUnitAt(u.getX() + 1, u.getY());
                break;
            case DIRECTION_DOWN:
                base = pgs->getUnitAt(u.getX(), u.getY() + 1);
                break;
            case DIRECTION_LEFT:
                base = pgs->getUnitAt(u.getX() - 1, u.getY());
                break;
            }
           
            if (base != Unit::unit_null && base.getType()->isStockpile && u.getResources() > 0) {
                Player &p = pgs->getPlayer(u.getPlayer());
                
                p.setResources(p.getResources() + u.getResources());
                
                u.setResources(0);
               
            }
            else {// base is not there

            }
        }
        break;
        case TYPE_PRODUCE: //produces a unit in the target direction
        {
            Unit newUnit ;
            int targetx = u.getX();
            int targety = u.getY();
            switch (this->parameter) {
            case DIRECTION_UP:
                targety--;
                break;
            case DIRECTION_RIGHT:
                targetx++;
                break;
            case DIRECTION_DOWN:
                targety++;
                break;
            case DIRECTION_LEFT:
                targetx--;
                break;
            }
            newUnit =  Unit(u.getPlayer(), unitType, targetx, targety, 0);
            
            Player &p = pgs->getPlayer(u.getPlayer());
            if ((p.getResources() - newUnit.getCost()) >= 0) {
                pgs->addUnit(newUnit);
                p.setResources(p.getResources() - newUnit.getCost());
            }

            if (p.getResources() < 0) {
                //System.err.print("Illegal action executed! resources of player " + p.ID + " are now " + p.getResources() + "\n");
                //System.err.print(s);
                cout << "Illegal action executed! resources of player " << p.getID() << " are now " << p.getResources() << endl;
            }
        }
    break;
    }
}



string UnitAction::toString() {
    string tmp = actionName[type] + "(";

    if (type == TYPE_ATTACK_LOCATION) {
        
        tmp += std::to_string(x) + ", " + std::to_string(y);
        
    }
    else if (type == TYPE_NONE) {
        ;
    }
    else {
        if (parameter != DIRECTION_NONE) {
            if (parameter == DIRECTION_UP) {
                tmp += "up";
            }
            if (parameter == DIRECTION_RIGHT) {
                tmp += "right";
            }
            if (parameter == DIRECTION_DOWN) {
                tmp += "down";
            }
            if (parameter == DIRECTION_LEFT) {
                tmp += "left";
            }
        }
        if (parameter != DIRECTION_NONE && unitType != nullptr) {
            tmp += ",";
        }

        if (unitType != nullptr) {
           
            tmp += unitType->name;
        }
    }
   
    return tmp + ")";
}


string UnitAction::getActionName() {
    return actionName[type];
}

 int UnitAction::getDirection() {
    return parameter;
}


  int UnitAction::getLocationX() {
     return this->x;
 }


  int UnitAction::getLocationY() {
     return this->y;
 }


std::string const UnitAction::actionName[] = { "wait", "move",
            "harvest", "return", "produce", "attack_location" };
const int UnitAction::DIRECTION_OFFSET_X[] = { 0, 1, 0, -1 };
const int UnitAction::DIRECTION_OFFSET_Y[] = { -1, 0, 1, 0 };
const string UnitAction::DIRECTION_NAMES[] = { "up", "right", "down", "left" };