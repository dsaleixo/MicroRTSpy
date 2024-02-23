
#ifndef UNIT_TYPE_TABLE_H // include guard
#define UNIT_TYPE_TABLE_H 

#include <vector>
using namespace std;
#include <string>
#include "UnitType.h"

/**
 * The unit type table stores the unit types the game can have.
 * It also determines the attributes of each unit type.
 * The unit type table determines the balance of the game.
 * @author santi
 */

class UnitTypeTable {
	
	public:
        /**
        * Empty type table should not be used!
        */
        static const int EMPTY_TYPE_TABLE = -1;

        /**
         * Version one
         */
        static const int VERSION_ORIGINAL = 1;

        /**
         * Version two (a fine tune of the original)
         */
        static const int VERSION_ORIGINAL_FINETUNED = 2;

        /**
         * A non-deterministic version (damages are random)
         */
        static const int VERSION_NON_DETERMINISTIC = 3;

        /**
         * A conflict resolution policy where move conflicts cancel both moves
         */
        static const int MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH = 1;   // (default)

        /**
         * A conflict resolution policy where move conflicts are solved randomly
         */
        static const int MOVE_CONFLICT_RESOLUTION_CANCEL_RANDOM = 2;   // (makes game non-deterministic)

        /**
         * A conflict resolution policy where move conflicts are solved by
         * alternating the units trying to move
         */
        static const int MOVE_CONFLICT_RESOLUTION_CANCEL_ALTERNATING = 3;

        /**
         * The list of unit types allowed in the game
         */
        vector<UnitType*> unitTypes;

        /**
         * Which move conflict resolution is being adopted
         */
        int moveConflictResolutionStrategy = MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH;

        //destructor
        ~UnitTypeTable();

        /**
         * Creates a UnitTypeTable with version {@link #VERSION_ORIGINAL} and
         * move conflict resolution as {@link #MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH}
         */
        UnitTypeTable();

        /**
         * Creates a unit type table with specified version and move conflict resolution
         * as {@link #MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH}
         * @param version
         */
        UnitTypeTable(int version);

        /**
         * Creates a unit type table specifying both the version and the move conflict
         * resolution strategy
         * @param version
         * @param crs the move conflict resolution strategy
         */
        UnitTypeTable(int version, int crs);


        /*
         * Sets the version and move conflict resolution strategy to use
         * and configures the attributes of each unit type depending on the
         * version
         * @param version
         * @param crs the move conflict resolution strategy
         */
        void setUnitTypeTable(int version, int crs);

        /**
         * Adds a new unit type to the game
         * @param ut
         */
        void addUnitType(UnitType *ut);

        /**
         * Retrieves a unit type by its numeric ID
         * @param ID
         * @return
         */
        UnitType* getUnitType(int ID);

        /**
         * Retrieves a unit type by its name. Returns null if name is not found.
         * @param name
         * @return
         */
        UnitType* getUnitTypeString(string name);

        /**
         * Returns the list of all unit types
         * @return
         */
        vector<UnitType*>* getUnitTypes();

        /*
         * Returns the integer corresponding to the move conflict resolution strategy in use
         * @return
         */
        int getMoveConflictResolutionStrategy();


        /**
         * Writes a XML representation of this UnitTypeTable
         * @param w
         */
        //void toxml(XMLWriter w);
        /**
         * Writes a JSON representation of this UnitTypeTable
         * @param w
         * @throws Exception
         */
        //void toJSON(Writer w);


        /**
         * Reads from XML and creates a UnitTypeTable
         * @param e
         * @return
         */
        //static UnitTypeTable fromXML(Element e);


        /**
         * Reads from a JSON string and creates a UnitTypeTable
         * @param JSON
         * @return
         */
        static UnitTypeTable* fromJSON(string JSON);

};

#endif