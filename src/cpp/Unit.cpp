#include "pugixml.hpp"
#include "Unit.h"
#include "UnitType.h"
#include <iostream>

long  Unit::next_ID = 0;


Unit::~Unit() {
    this->type = nullptr;
}

vector<UnitAction>* Unit::getUnitActions(GameState& s) {
    return  this->getUnitActionsINT(s, 10);
}


vector<UnitAction>* Unit::getUnitActionsINT(GameState& s, int noneDuration){
    vector<UnitAction> *l = new vector< UnitAction>;
    
    PhysicalGameState *pgs = s.getPhysicalGameState();
    Player p = pgs->getPlayer(this->player);

    
   // Unit uup = pgs.getUnitAt(x,y-1);
    //Unit uright = pgs.getUnitAt(x+1,y);
    //Unit udown = pgs.getUnitAt(x,y+1);
    //Unit uleft = pgs.getUnitAt(x-1,y);
   
   
    // retrieves units around me
    Unit *uup = nullptr, *uright = nullptr, *udown = nullptr, *uleft = nullptr;
    for (Unit *u : pgs->getUnits()) {
        if (u->x == x) {
            if (u->y == y - 1) {
                uup = u;
            }
            else if (u->y == y + 1) {
                udown = u;
            }
        }
        else {
            if (u->y == y) {
                if (u->x == x - 1) {
                    uleft = u;
                }
                else if (u->x == x + 1) {
                    uright = u;
                }
            }
        }
    }
   
    // if this unit can attack, adds an attack action for each unit around it
    if (this->type->canAttack) {
        if (this->type->attackRange == 1) {

            if (y > 0 && uup != nullptr && uup->player != player && uup->player >= 0) l->push_back( UnitAction(UnitAction::TYPE_ATTACK_LOCATION, uup->x, uup->y));
            if (x < pgs->getWidth() - 1 && uright != nullptr && uright->player != player && uright->player >= 0) l->push_back( UnitAction(UnitAction::TYPE_ATTACK_LOCATION, uright->x, uright->y));
            if (y < pgs->getHeight() - 1 && udown != nullptr && udown->player != player && udown->player >= 0) l->push_back( UnitAction(UnitAction::TYPE_ATTACK_LOCATION, udown->x, udown->y));
            if (x > 0 && uleft != nullptr && uleft->player != player && uleft->player >= 0) l->push_back( UnitAction(UnitAction::TYPE_ATTACK_LOCATION, uleft->x, uleft->y));
        }
        else {
            int sqrange = this->type->attackRange * this->type->attackRange;
            for (Unit* u : pgs->getUnits()) {
                if (u->player < 0 || u->player == player) continue;
                int sq_dx = (u->x - x) * (u->x - x);
                int sq_dy = (u->y - y) * (u->y - y);
                if (sq_dx + sq_dy <= sqrange) {
                   
                    l->push_back( UnitAction(UnitAction::TYPE_ATTACK_LOCATION, u->getX(), u->getY()));
                }
            }
        }
    }
    
    // if this unit can harvest, adds a harvest action for each resource around it
    // if it is already carrying resources, adds a return action for each allied base around it
    if (this->type->canHarvest) {
        // harvest:
        if (resources == 0) {
            if (y > 0 && uup != nullptr && uup->type->isResource) l->push_back( UnitAction(UnitAction::TYPE_HARVEST, UnitAction::DIRECTION_UP));
            if (x < pgs->getWidth() - 1 && uright != nullptr && uright->type->isResource) l->push_back( UnitAction(UnitAction::TYPE_HARVEST, UnitAction::DIRECTION_RIGHT));
            if (y < pgs->getHeight() - 1 && udown != nullptr && udown->type->isResource) l->push_back( UnitAction(UnitAction::TYPE_HARVEST, UnitAction::DIRECTION_DOWN));
            if (x > 0 && uleft != nullptr && uleft->type->isResource) l->push_back( UnitAction(UnitAction::TYPE_HARVEST, UnitAction::DIRECTION_LEFT));
        }
        // return:
        if (resources > 0) {
            if (y > 0 && uup != nullptr && uup->type->isStockpile && uup->player == player) l->push_back( UnitAction(UnitAction::TYPE_RETURN, UnitAction::DIRECTION_UP));
            if (x < pgs->getWidth() - 1 && uright != nullptr && uright->type->isStockpile && uright->player == player) l->push_back( UnitAction(UnitAction::TYPE_RETURN, UnitAction::DIRECTION_RIGHT));
            if (y < pgs->getHeight() - 1 && udown != nullptr && udown->type->isStockpile && udown->player == player) l->push_back( UnitAction(UnitAction::TYPE_RETURN, UnitAction::DIRECTION_DOWN));
            if (x > 0 && uleft != nullptr && uleft->type->isStockpile && uleft->player == player) l->push_back( UnitAction(UnitAction::TYPE_RETURN, UnitAction::DIRECTION_LEFT));
        }
    }
   
    // if the player has enough resources, adds a produce action for each type this unit produces.
    // a produce action is added for each free tile around the producer 
    for (UnitType *ut : this->type->produces_v) {
        if (p.getResources() >= ut->cost) {
            int tup = (y > 0 ? pgs->getTerrain(x, y - 1) : PhysicalGameState::TERRAIN_WALL);
            int tright = (x < pgs->getWidth() - 1 ? pgs->getTerrain(x + 1, y) : PhysicalGameState::TERRAIN_WALL);
            int tdown = (y < pgs->getHeight() - 1 ? pgs->getTerrain(x, y + 1) : PhysicalGameState::TERRAIN_WALL);
            int tleft = (x > 0 ? pgs->getTerrain(x - 1, y) : PhysicalGameState::TERRAIN_WALL);

            if (tup == PhysicalGameState::TERRAIN_NONE && pgs->getUnitAt(x, y - 1) == nullptr) l->push_back( UnitAction(UnitAction::TYPE_PRODUCE, UnitAction::DIRECTION_UP, ut));
            if (tright == PhysicalGameState::TERRAIN_NONE && pgs->getUnitAt(x + 1, y) == nullptr) l->push_back( UnitAction(UnitAction::TYPE_PRODUCE, UnitAction::DIRECTION_RIGHT, ut));
            if (tdown == PhysicalGameState::TERRAIN_NONE && pgs->getUnitAt(x, y + 1) == nullptr) l->push_back( UnitAction(UnitAction::TYPE_PRODUCE, UnitAction::DIRECTION_DOWN, ut));
            if (tleft == PhysicalGameState::TERRAIN_NONE && pgs->getUnitAt(x - 1, y) == nullptr) l->push_back( UnitAction(UnitAction::TYPE_PRODUCE, UnitAction::DIRECTION_LEFT, ut));
        }
    }
    
    // if the unit can move, adds a move action for each free tile around it
    if (this->type->canMove) {
        int tup = (y > 0 ? pgs->getTerrain(x, y - 1) : PhysicalGameState::TERRAIN_WALL);
        int tright = (x < pgs->getWidth() - 1 ? pgs->getTerrain(x + 1, y) : PhysicalGameState::TERRAIN_WALL);
        int tdown = (y < pgs->getHeight() - 1 ? pgs->getTerrain(x, y + 1) : PhysicalGameState::TERRAIN_WALL);
        int tleft = (x > 0 ? pgs->getTerrain(x - 1, y) : PhysicalGameState::TERRAIN_WALL);

        if (tup == PhysicalGameState::TERRAIN_NONE && uup == nullptr) l->push_back( UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_UP));
        if (tright == PhysicalGameState::TERRAIN_NONE && uright == nullptr) l->push_back( UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_RIGHT));
        if (tdown == PhysicalGameState::TERRAIN_NONE && udown == nullptr) l->push_back( UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_DOWN));
        if (tleft == PhysicalGameState::TERRAIN_NONE && uleft == nullptr) l->push_back( UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_LEFT));
    }
   
    // units can always stay idle:
    l->push_back( UnitAction(UnitAction::TYPE_NONE, noneDuration));
    
    return l;

}


bool Unit::canExecuteAction(UnitAction& ua, GameState& gs) {
   
    vector<UnitAction> *l = getUnitActionsINT(gs, ua.ETA(this));
  
   // bool aux = std::find(l->begin(), l->end(), ua) == l->end();
  
    for (auto& it : *l) {
        
        
            
            if (it == ua) {
                return true;
            }
        
        
    }
   
    delete l;
    return false;
    
    
}



/**
     * Constructs a unit, specifying with all parameters, including the ID.
     * {@link #next_ID} gets ID+1 if ID >= {@link #next_ID}
     * @param a_ID
     * @param a_player
     * @param a_type
     * @param a_x
     * @param a_y
     * @param a_resources
     */
Unit::Unit(long a_ID, int a_player, UnitType *a_type, int a_x, int a_y, int a_resources) {
    this->player = a_player;
    this->type = a_type;
    this->x = a_x;
    this->y = a_y;
    this->resources = a_resources;
    this->hitpoints = a_type->hp;
    this->ID = a_ID;
    if (ID >= next_ID) this->next_ID = ID + 1;
  
}

/**
 * Creates a unit without specifying its ID. It is automatically assigned from
 * {@link #next_ID}, which is incremented.
 * @param a_player
 * @param a_type
 * @param a_x
 * @param a_y
 * @param a_resources
 */
Unit::Unit(int a_player, UnitType *a_type, int a_x, int a_y, int a_resources) {
    this->player = a_player;
    this->type = a_type;
    this->x = a_x;
    this->y = a_y;
    this->resources = a_resources;
    this->hitpoints = a_type->hp;
    this->ID = next_ID++;
  
}

/**
 * Creates a unit without specifying resources, which receive zero
 * @param a_player
 * @param a_type
 * @param a_x
 * @param a_y
 */
Unit::Unit(int a_player, UnitType *a_type, int a_x, int a_y) {
    this->player = a_player;
    this->type = a_type;
    this->x = a_x;
    this->y = a_y;
    this->resources = 0;
    this->hitpoints = a_type->hp;
    this->ID = next_ID++;
 
}

/**
 * Copies the attributes from other unit
 * @param other
 */
Unit::Unit(const Unit &other) {
    this->player = other.player;
    this->type = other.type;
    this->x = other.x;
    this->y = other.y;
    this->resources = other.resources;
    this->hitpoints = other.hitpoints;
    this->ID = other.ID;
    
    
    
}

/**
 * Returns the owner ID
 * @return
 */
int Unit::getPlayer() {
    return this->player;
}

/**
 * Returns the type
 * @return
 */
UnitType* Unit::getType() {
    return this->type;
}




/**
 * Sets the type of this unit.
 * Note: this should not be done lightly. It is currently thought to be used
 * only when the GUI changes the unit type table, and tries to create a clone
 * of the current game state, but changing the UTT.
 * @param a_type
 */
void Unit::setType(UnitType *a_type) {
    this->type = a_type;
}

/**
 * Returns the unique identifier
 * @return
 */
long Unit::getID() {
    return this->ID;
}

/**
 * Changes the unique identifier
 * Note: Do not use this function unless you know what you are doing!
 * @param a_ID
 */
void Unit::setID(long a_ID) {
    this->ID = a_ID;
}

/**
 * Returns the index of this unit in a {@link PhysicalGameState}
 * (as it is an 'unrolled matrix')
 * @param pgs
 * @return

int Unit::getPosition(PhysicalGameState &pgs) {
    return this->x + pgs.getWidth() * this->y;
}
 */


/**
 * Returns the x coordinate
 * @return
 */
int Unit::getX() {
    return this->x;
}

/**
 * Returns the y coordinate
 * @return
 */
int Unit::getY() {
    return this->y;
}

/**
 * Sets x coordinate
 * @param a_x
 */
void Unit::setX(int a_x) {
    this->x = a_x;
}

/**
 * Sets y coordinate
 * @param a_y
 */
void Unit::setY(int a_y) {
    y = a_y;
}

/**
 * Returns the amount of resources this unit is carrying
 * @return
 */
int Unit::getResources() {
    return this->resources;
}

/**
 * Sets the amount of resources the unit is carrying
 * @param a_resources
 */
void Unit::setResources(int a_resources) {
    resources = a_resources;
}

/**
 * Returns the current HP
 * @return
 */
int Unit::getHitPoints() {
    return this->hitpoints;
}

/**
 * Returns the maximum HP this unit could have
 * @return
 */
int Unit::getMaxHitPoints() {
    return this->type->hp;
}

/**
 * Sets the amount of HP
 * @param a_hitpoints
 */
void Unit::setHitPoints(int a_hitpoints) {
    hitpoints = a_hitpoints;
}

/**
 * The cost to produce this unit
 * @return
 */
int Unit::getCost() {
    return this->type->cost;
}

/**
 * The time this unit gets to move
 * @return
 */
int Unit::getMoveTime() {
    return this->type->moveTime;
}

/**
 * The time it takes to perform an attack
 * @return
 */
int Unit::getAttackTime() {
    return this->type->attackTime;
}

/**
 * Returns the attack range
 * @return
 */
int Unit::getAttackRange() {
    return this->type->attackRange;
}

/**
 * Returns the minimum damage this unit's attack inflict
 * @return
 */
int Unit::getMinDamage() {
    return this->type->minDamage;
}

/**
 * Returns the maximum damage this unit's attack inflict
 * @return
 */
int Unit::getMaxDamage() {
    return this->type->maxDamage;
}

/**
 * Returns the amount of resources this unit can harvest
 * @return
 */
int Unit::getHarvestAmount() {
    return this->type->harvestAmount;
}

/**
 * The time it takes to harvest
 * @return
 */
int Unit::getHarvestTime() {
    return this->type->harvestTime;
}

/**
 * Returns a list of actions this unit can perform in a given game state.
 * An idle action for 10 cycles is always generated
 * @param s
 * @return
 
vector<UnitAction> Unit::getUnitActions(GameState &s) {
    // Unless specified, generate "NONE" actions with duration 10 cycles
    return this->getUnitActions(s, 10);
}
*/


/**
 * Indicates whether this unit can perform an action in a given state
 * @param ua
 * @param gs
 * @return
 
public boolean canExecuteAction(UnitAction ua, GameState gs)
{
    List<UnitAction> l = getUnitActions(gs, ua.ETA(this));
    return l.contains(ua);
}
*/

string Unit::toString() {
    return type->name + "(" + to_string(ID) + ")" +
        "(" + to_string(player) + ", (" + to_string(x) + "," + to_string(y) + "), " + to_string(hitpoints) + ", " + to_string(resources) + ")";
}


 Unit& Unit::clone() {
    return  Unit(*this);
}

/**
 * Returns the unique ID
 */
     int Unit::hashCode() {
    return (int)ID;
}


/**
 * Writes the XML representation of this unit
 * @param w
 
void Unit::toxml(pugi::xml_node w) {
    w.tagWithAttributes(
        this.getClass().getName(), "type=\"" + type.name + "\" " +
        "ID=\"" + ID + "\" " +
        "player=\"" + player + "\" " +
        "x=\"" + x + "\" " +
        "y=\"" + y + "\" " +
        "resources=\"" + resources + "\" " +
        "hitpoints=\"" + hitpoints + "\" "
    );

    w.tag("/" + this.getClass().getName());
}
*/
/**
 * Writes a JSON representation of this unit
 * @param w
 * @throws Exception

public void toJSON(Writer w) throws Exception {
    w.write(
        "{\"type\":\"" + type.name + "\", " +
        "\"ID\":" + ID + ", " +
        "\"player\":" + player + ", " +
        "\"x\":" + x + ", " +
        "\"y\":" + y + ", " +
        "\"resources\":" + resources + ", " +
        "\"hitpoints\":" + hitpoints +
        "}"
    );
}
 */
/**
 * Constructs a unit from a XML element
 * @param e
 * @param utt
 * @return
 */
 Unit* Unit::fromXML(pugi::xml_node &e, UnitTypeTable &utt) {
    string typeName = e.attribute("type").as_string();
    string IDStr = e.attribute("ID").as_string();
    string playerStr = e.attribute("player").as_string();
    string xStr = e.attribute("x").as_string();
    string yStr = e.attribute("y").as_string();
    string resourcesStr = e.attribute("resources").as_string();
    string hitpointsStr = e.attribute("hitpoints").as_string();

    long ID = stol(IDStr);
    if (ID >= next_ID) next_ID = ID + 1;
    
    UnitType *type = utt.getUnitType(typeName);
    
    int player = atol(playerStr.c_str());
    int x = atol(xStr.c_str());
    int y = atol(yStr.c_str());
    int resources = atol(resourcesStr.c_str());
    int hitpoints = atol(hitpointsStr.c_str());

    Unit *u = new  Unit(ID, player, type, x, y, resources);
 
    u->hitpoints = hitpoints;
    
    return u;
}

/**
 * Constructs a unit from a JSON object
 * @param o
 * @param utt
 * @return

public static  Unit fromJSON(JsonObject o, UnitTypeTable utt) {

    Unit u = new Unit(
        o.getLong("ID", -1),
        o.getInt("player", -1),
        utt.getUnitType(o.getString("type", null)),
        o.getInt("x", 0),
        o.getInt("y", 0),
        o.getInt("resources", 0)
    );

    u.hitpoints = o.getInt("hitpoints", 1);
    return u;
}

 */