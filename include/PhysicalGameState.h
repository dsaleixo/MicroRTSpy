
#ifndef PHYSICAL_GAMESTATE_H // include guard
#define PHYSICAL_GAMESTATE_H  



#include <vector>

#include <iostream>
#include "UnitTypeTable.h"
#include "pugixml.hpp"
#include "Player.h"
#include "Unit.h"

/**
 * The physical game state (the actual 'map') of a microRTS game
 *
 * @author santi
 */
using namespace  std;

class PhysicalGameState {

    /**
     * Indicates a free tile
     */
    static  const int TERRAIN_NONE =0;

    /**
     * Indicates a blocked tile
     */
    static const  int TERRAIN_WALL=1;

    int width = 8;
    int height = 8;
    int* terrain = {};
    vector<Player> players;
    vector<Unit> units;


    //destructor
    public:
        ~PhysicalGameState();


    /**
     * Constructs the game state map from a XML
     *
     * @param fileName
     * @param utt
     * @return
     * @throws JDOMException
     * @throws IOException
     */
    
        static PhysicalGameState load(string fileName, UnitTypeTable &utt);
        /**
         * Creates a new game state map with the informed width and height.
         * Initializes an empty terrain.
         *
         * @param a_width
         * @param a_height
         */
        PhysicalGameState(int a_width, int a_height);

            /**
             * Creates a new game state map with the informed width and height.
             * Initializes with the received terrain.
             *
             * @param a_width
             * @param a_height
             * @param t
             */
            PhysicalGameState(int a_width, int a_height, int t[]);

        /**
         * @return
         */
            int getWidth();

        /**
         * @return
         */
            int getHeight();

        /**
         * Sets a new width. This do not change the terrain array, remember to
         * change that when you change the map width or height
         *
         * @param w
         */
            void setWidth(int w);

        /**
         * Sets a new height. This do not change the terrain array, remember to
         * change that when you change the map width or height
         *
         * @param h
         */
         void setHeight(int h);

        /**
         * Returns what is on a given position of the terrain
         *
         * @param x
         * @param y
         * @return
         */
         int getTerrain(int x, int y);

        /**
         * Puts an entity in a given position of the terrain
         *
         * @param x
         * @param y
         * @param v
         */
         void setTerrain(int x, int y, int v);

        /**
         * Sets the whole terrain
         *
         * @param t
         */
         void setTerrain(int t[]);

        /**
         * Adds a player
         *
         * @param p
         */
         void addPlayer(Player p);

        /**
         * Adds a new {@link Unit} to the map if its position is free
         *
         * @param newUnit
         * @throws IllegalArgumentException if the new unit's position is already
         * occupied
         */
         void addUnit(Unit &newUnit);

        /**
         * Removes a unit from the map
         *
         * @param u
         */
         //void removeUnit(Unit u);

        /**
         * Returns the list of units in the map
         *
         * @return
         */
         vector<Unit>& getUnits();

        /**
         * Returns a list of players
         *
         * @return
         */
         //vector<Player> getPlayers();

             /**
              * Returns a player given its ID
              *
              * @param pID
              * @return
              */
          //Player getPlayer(int pID);

        /**
         * Returns a {@link Unit} given its ID or null if not found
         *
         * @param ID
         * @return
         */
          Unit* getUnit(long ID);

        /**
         * Returns the {@link Unit} at a given coordinate or null if no unit is
         * present
         *
         * @param x
         * @param y
         * @return
         */
          //Unit getUnitAt(int x, int y);

        /**
         * Returns the units within a squared area centered in the given coordinates
         *
         * @param x center coordinate of the square
         * @param y center coordinate of the square
         * @param squareRange square size
         * @return
         */
         //Collection<Unit> getUnitsAround(int x, int y, int squareRange);

        /**
         * Returns units within a rectangular area centered in the given coordinates
         * @param x center coordinate of the rectangle
         * @param y center coordinate of the square
         * @param width rectangle width
         * @param height rectangle height
         * @return
         */
         //Collection<Unit> getUnitsAround(int x, int y, int width, int height);

        /**
         * Returns units within a rectangle with the given top-left vertex and dimensions
         * Tests for x <= unitX < x+width && y <= unitY < y+height
         * Notice that the test is inclusive in top and left but exclusive on bottom and right
         * @param x top left coordinate of the rectangle
         * @param y top left coordinate of the rectangle
         * @param width rectangle width
         * @param height rectangle height
         * @return
         */
         //public Collection<Unit> getUnitsInRectangle(int x, int y, int width, int height);



        /**
         * Returns the winner of the game, given the unit counts or -1 if the game
         * is not over TODO: verify where unit counts are being compared!
         *
         * @return
         */
         int winner();

        /* (non-Javadoc)
         * @see java.lang.Object#clone()
         */
         PhysicalGameState clone();

        /**
         * Clone the physical game state, but does not clone the units The terrain
         * is shared amongst all instances, since it never changes
         *
         * @return
         */
         PhysicalGameState cloneKeepingUnits();

        /**
         * Clones the physical game state, including its terrain
         *
         * @return
         */
         PhysicalGameState cloneIncludingTerrain();

        /* (non-Javadoc)
         * @see java.lang.Object#toString()
         */
         string toString();

        /**
         * This function tests if two PhysicalGameStates are identical (I didn't
         * name this method "equals" since I don't want Java to use it)
         *
         * @param pgs
         * @return
         */
         bool equivalents(PhysicalGameState pgs);

        /**
         * This function tests if two PhysicalGameStates are identical, including their terrain
         *      *
         * @param pgs
         * @return
         */
         bool equivalentsIncludingTerrain(PhysicalGameState pgs);

        /**
         * Returns an array with true if the given position has
         * {@link PhysicalGameState.TERRAIN_NONE}
         *
         * @return
         */
         bool** getAllFree();

        /**
         * Create a compressed String representation of the terrain vector.
         * <p>
         *     The terrain vector is an array of Integers, whose elements only assume 0 and 1 as
         *     possible values. This method compresses the terrain vector by counting the number of
         *     consecutive occurrences of a value and appending this to a String.
         *     Since 0 and 1 may appear in the counter, 0 is replaced by A and 1 is replaced by B.
         * </p>
         * <p>
         *     For example, the String <code>00000011110000000000</code> is transformed into
         *     <code>A6B4A10</code>.
         * </p>
         * <p>
         *     This method is useful when the terrain composes part of a message, to be shared between
         *     client and server.
         * </p>
         *
         * @return compressed String representation of the terrain vector
         */
         private:

             string compressTerrain();
                

        /**
         * Create an uncompressed int array from a compressed String representation of
         * the terrain.
         * @param t a compressed String representation of the terrain
         * @return int array representation of the terrain
         */
             static int* uncompressTerrain(string t); 
    

        /**
         * Writes a XML representation of the map
         *
         * @param w
         */
        //void toxml(XMLWriter w);

         //void toxml(XMLWriter w, bool includeConstants, bool compressTerrain);
        /**
         * Constructs a map from XML
         *
         * @param e
         * @param utt
         * @return 
         */
         static PhysicalGameState fromXML(pugi::xml_node &e, UnitTypeTable &utt);

   
        /**
         * Transforms a compressed or uncompressed String representation of the terrain into an integer
         * array
         * @param terrainString the compressed or uncompressed String representation of the terrain
         * @param size size of the resulting integer array
         * @return the terrain, in its integer representation
         */
         static int* getTerrainFromUnknownString(string terrainString, int size);

        /**
         * Reset all units HP to their base value
         */
         void resetAllUnitsHP();
};



#endif