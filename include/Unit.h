
#ifndef UNIT_H // include guard
#define UNIT_H

class GameState;
class UnitAction;
#include "UnitType.h"
#include "UnitTypeTable.h"
#include "pugixml.hpp"


#include "string"


using namespace std;
/**
 * Represents an instance of any unit in the game.
 * @author santi
 */





class Unit {

	public:

        static Unit unit_null;

        /*
         *The type of this unit(worker, ranged, barracks, etc.)
         */
        UnitType *type;

        /**
         * Indicates the ID to assign to a new unit.
         * It is incremented when the constructor without explicit ID is used
         */
        static  long   next_ID ;

        /**
         * The unique identifier of this unit
         */
        long ID;

        /**
         * Owner ID
         */
        int player;

        /**
         * Coordinates
         */
        int x, y;

        /**
         * Resources this unit is carrying
         */
        int resources;

        /**
         * Unit hit points
         */
        int hitpoints = 0;


        //destructor
        ~Unit();

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

        Unit();
        
        bool operator==(const Unit& u)const ;
        bool operator!=(const Unit& u) const;
        Unit(long a_ID, int a_player, UnitType *a_type, int a_x, int a_y, int a_resources);

        /**
         * Creates a unit without specifying its ID. It is automatically assigned from
         * {@link #next_ID}, which is incremented.
         * @param a_player
         * @param a_type
         * @param a_x
         * @param a_y
         * @param a_resources
         */
        Unit(int a_player, UnitType *a_type, int a_x, int a_y, int a_resources);

        /**
         * Creates a unit without specifying resources, which receive zero
         * @param a_player
         * @param a_type
         * @param a_x
         * @param a_y
         */
        Unit(int a_player, UnitType *a_type, int a_x, int a_y);

        /**
         * Copies the attributes from other unit
         * @param other
         */
        Unit(const  Unit &other);

        /**
         * Returns the owner ID
         * @return
         */
        int getPlayer() const;

        /**
         * Returns the type
         * @return
         */
        UnitType* getType();

        /**
         * Sets the type of this unit.
         * Note: this should not be done lightly. It is currently thought to be used
         * only when the GUI changes the unit type table, and tries to create a clone
         * of the current game state, but changing the UTT.
         * @param a_type
         */
        void setType(UnitType *a_type);

        /**
         * Returns the unique identifier
         * @return
         */
        long getID();

        /**
         * Changes the unique identifier
         * Note: Do not use this function unless you know what you are doing!
         * @param a_ID
         */
        void setID(long a_ID);

        /*
         * Returns the index of this unit in a {@link PhysicalGameState}
         * (as it is an 'unrolled matrix')
         * @param pgs
         * @return
        
        int getPosition(PhysicalGameState &pgs);
         */
        /**
         * Returns the x coordinate
         * @return
         */
        int getX() const;

        /**
         * Returns the y coordinate
         * @return
         */
        int getY() const ;

        /**
         * Sets x coordinate
         * @param a_x
         */
        void setX(int a_x);

        /**
         * Sets y coordinate
         * @param a_y
         */
        void setY(int a_y);



        


        /**
         * Returns the amount of resources this unit is carrying
         * @return
         */
        int getResources();

        /**
         * Sets the amount of resources the unit is carrying
         * @param a_resources
         */
        void setResources(int a_resources);

        /**
         * Returns the current HP
         * @return
         */
        int getHitPoints();

        /**
         * Returns the maximum HP this unit could have
         * @return
         */
        int getMaxHitPoints();

        /**
         * Sets the amount of HP
         * @param a_hitpoints
         */
        void setHitPoints(int a_hitpoints);

        /**
         * The cost to produce this unit
         * @return
         */
        int getCost();

        /**
         * The time this unit gets to move
         * @return
         */
        int getMoveTime();

        /**
         * The time it takes to perform an attack
         * @return
         */
        int getAttackTime();

        /**
         * Returns the attack range
         * @return
         */
        int getAttackRange();

        /**
         * Returns the minimum damage this unit's attack inflict
         * @return
         */
        int getMinDamage();

        /**
         * Returns the maximum damage this unit's attack inflict
         * @return
         */
        int getMaxDamage();

        /**
         * Returns the amount of resources this unit can harvest
         * @return
         */
        int getHarvestAmount();

        /**
         * The time it takes to harvest
         * @return
         */
        int getHarvestTime();

        /**
         * Returns a list of actions this unit can perform in a given game state.
         * An idle action for 10 cycles is always generated
         * @param s
         * @return
           */
        vector<UnitAction>* getUnitActions(GameState& s);
      
        /**
         * Returns a list of actions this unit can perform in a given game state.
         * An idle action for noneDuration cycles is always generated
         * @param s
         * @param noneDuration the amount of cycles for the idle action that is always generated
         * @return
        */ 
        vector<UnitAction>* getUnitActionsINT(GameState &s, int noneDuration);
        
        /**
         * Indicates whether this unit can perform an action in a given state
         * @param ua
         * @param gs
         * @return
          */
        bool canExecuteAction(UnitAction& ua, GameState& gs);
       

        string toString();


        Unit& clone();

        /**
         * Returns the unique ID
         */
        int hashCode();


        /**
         * Writes the XML representation of this unit
         * @param w
         
        void toxml(XMLWriter w);
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
        static  Unit fromXML(pugi::xml_node &e, UnitTypeTable &utt);

        /**
         * Constructs a unit from a JSON object
         * @param o
         * @param utt
         * @return
         
        static  Unit fromJSON(JsonObject o, UnitTypeTable utt);
        */

};



#endif