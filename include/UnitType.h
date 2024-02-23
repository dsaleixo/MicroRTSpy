
#ifndef UNIT_TYPE_H // include guard
#define UNIT_TYPE_H 


#include <vector>
using namespace std;
#include <string>

/**
 * A general unit definition that could turn out to be anything
 * @author santi, inspired in the original UnitDefinition class by Jeff Bernard
 *
 */

class UnitType{
    public:
        /**
         * The unique identifier of this type
         */
        int ID = 0;

        /**
         * The name of this type
         */
        string name;

        /**
         * Cost to produce a unit of this type
         */
        int cost = 1;

        /**
         * Initial Hit Points of units of this type
         */
        int hp = 1;


        /**
         * Minimum damage of the attack from a unit of this type
         */
        int minDamage = 1;

        /**
         * Maximum damage of the attack from a unit of this type
         */
        int maxDamage = 1;

        /**
         * Range of the attack from a unit of this type
         */
        int attackRange = 1;

        /**
         * Time that each action takes to accomplish
         */
        int produceTime = 10,
            moveTime = 10,
            attackTime = 10,
            harvestTime = 10,
            returnTime = 10;

        /**
         * How many resources the unit can carry.
         * Each time the harvest action is executed, this is
         * how many resources does the unit gets
         */
        int harvestAmount = 1;

        /**
         * the radius a unit can see for partially observable game states.
         */
        int sightRadius = 4;

        /**
         * Can this unit type be harvested?
         */
        bool isResource = false;

        /**
         * Can resources be returned to this unit type?
         */
        bool isStockpile = false;

        /**
         * Is this a harvester type?
         */
        bool canHarvest = false;

        /**
         * Can a unit of this type move?
         */
        bool canMove = true;

        /**
         * Can a unit of this type attack?
         */
        bool canAttack = true;

        /**
         * Units that this type of unit can produce
         */
        vector<UnitType*> produces_v;

        /**
         * Which unit types produce a unit of this type
         */
        vector<UnitType*> producedBy_v;

        /**
         * Returns the hash code of the name
         * // assume that all unit types have different names:
         
        int hashCode();
        */
public:
         UnitType();
         UnitType(const UnitType &other);
         bool getCanMove();
         bool getIsStockpile();
         bool getCanAttack();
         bool getcanHarvest();
         bool getisResource();
        /* (non-Javadoc)
         * @see java.lang.Object#equals(java.lang.Object)
         */
        bool equals(UnitType ut);

        /**
         * Adds a unit type that a unit of this type can produce
         * @param ut
         */
        void produces(UnitType *ut);

        /**
         * Creates a temporary instance with just the name and ID from a XML element
         * @param unittype_e
         * @return
        
        static UnitType createStub(Element unittype_e);
         */

        /**
         * Creates a temporary instance with just the name and ID from a JSON object
         * @param o
         * @return
         
        static UnitType createStub(JsonObject o);
        */
        /**
         * Updates the attributes of this type from XML
         * @param unittype_e
         * @param utt
         
        void updateFromXML(Element unittype_e, UnitTypeTable utt);
        */
        /**
         * Updates the attributes of this type from a JSON string
         * @param JSON
         * @param utt
         
        void updateFromJSON(string JSON, UnitTypeTable utt);
        */

        string getName();

       


       


        


        
};


#endif