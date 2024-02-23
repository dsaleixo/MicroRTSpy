#ifndef UNIT_ACTION_H // include guard
#define UNIT_ACTION_H 

class UnitAction;
class ResourceUsage;
class PhysicalGameState;
class UnitAction;
class UnitActionAssignment;
#include <string>
#include "ResourceUsage.h"
#include "Unit.h"
#include "UnitType.h"
#include "PhysicalGameState.h"
#include "GameState.h"

using namespace std;


class UnitAction {
public:

         /**
        *The 'no-op' action
        */
     static const int TYPE_NONE = 0;
     static int getTYPE_NONE();

    /**
     * Action of moving
     */
    static const int TYPE_MOVE = 1;
    static int getTYPE_MOVE();
    /**
     * Action of harvesting
     */
     static const int TYPE_HARVEST = 2;
     static int getTYPE_HARVEST();

    /**
     * Action of return to base with resource
     */
     static const int TYPE_RETURN = 3;
     static int getTYPE_RETURN();

    /**
     * Action of produce a unit
     */
     static const int TYPE_PRODUCE = 4;
     static int getTYPE_PRODUCE();

    /**
     * Action of attacking a location
     */
     static const int TYPE_ATTACK_LOCATION = 5;
     static int getTYPE_ATTACK_LOCATION();

    /**
     * Total number of action types
     */
     static const int NUMBER_OF_ACTION_TYPES = 6;
     static int getNUMBER_OF_ACTION_TYPES();



     static std::string const actionName[];

    /**
     * Direction of 'standing still'
     */
     static const int DIRECTION_NONE = -1;
     static int getDIRECTION_NONE();

    /**
     * Alias for up
     */
     static const int DIRECTION_UP = 0;
     static int getDIRECTION_UP();

    /**
     * Alias for right
     */
    static const int DIRECTION_RIGHT = 1;
    static int getDIRECTION_RIGHT();

    /**
     * Alias for down
     */
     static const int DIRECTION_DOWN = 2;
     static int getDIRECTION_DOWN();

    /**
     * Alias for left
     */
     static const int DIRECTION_LEFT = 3;
     static int getDIRECTION_LEFT();

    /**
     * The offset caused by each direction of movement in X Indexes correspond
     * to the constants used in this class
     */
     static const int DIRECTION_OFFSET_X[];

    /**
     * The offset caused by each direction of movement in y Indexes correspond
     * to the constants used in this class
     */
     static const int DIRECTION_OFFSET_Y[];

    /**
     * Direction names. Indexes correspond to the constants used in this class
     */
     static const string DIRECTION_NAMES[];

    /**
     * Type of this UnitAction
     */
    int type = TYPE_NONE;

    /**
     * used for both "direction" and "duration"
     */
    int parameter = DIRECTION_NONE;

    /**
     * X and Y coordinates of an attack-location action
     */
    int x = 0, y = 0;

    /**
     * UnitType associated with a 'produce' action
     */
      UnitType *unitType;

    /**
     * Amount of resources associated with this action
     */
    //ResourceUsage r_cache;

    /**
     * Creates an action with specified type
     *
     * @param a_type
     */
    UnitAction(int a_type);
    ~UnitAction();
    /**
     * Creates an action with type and direction
     *
     * @param a_type
     * @param a_direction
     */
    UnitAction(int a_type, int a_direction);

    /**
     * Creates an action with type, direction and unit type
     *
     * @param a_type
     * @param a_direction
     * @param a_unit_type
     */
      UnitAction(int a_type, int a_direction, UnitType *a_unit_type);

    /**
     * Creates a unit action with coordinates
     *
     * @param a_type
     * @param a_x
     * @param a_y
     */
    UnitAction(int a_type, int a_x, int a_y);

    /**
     * Copies the parameters of other unit action
     *
     * @param other
     */
    UnitAction(const UnitAction &other);
    UnitAction();
   
    bool equals(UnitAction o);


     int hashCode();

    /**
     * Returns the type associated with this action
     *
     * @return
     */
    int getType();

        /**
         * Returns the UnitType associated with this action
         *
         * @return
         */
    UnitType* getUnitType();

    /**
     * Returns the ResourceUsage associated with this action, given a Unit and a
     * PhysicalGameState
     *
     * @param u
     * @param pgs
     * @return
     */
     ResourceUsage resourceUsage(Unit *u, PhysicalGameState *pgs);

    

    /**
     * Returns the estimated time of conclusion of this action The Unit
     * parameter is necessary for actions of {@link #TYPE_MOVE},
     * {@link #TYPE_ATTACK_LOCATION} and {@link #TYPE_RETURN}. In other cases it
     * can be null
     *
     * @param u
     * @return
     */
       int ETA(Unit *u);

    /**
     * Effects this action in the game state. If the action is related to a
     * unit, changes it position accordingly
     *
     * @param u
     * @param s
     */
        void execute(Unit *u, GameState& s);

        string toString();

    /**
     * Returns the name of this action
     *
     * @return
     */
      string getActionName();

    /**
     * Returns the direction associated with this action
     *
     * @return
     */

      int getDirection();

    /**
     * Returns the X coordinate associated with this action
     *
     * @return
     */
       int getLocationX();

    /**
     * Returns the Y coordinate associated with this action
     *
     * @return
     */
       int getLocationY();

    /**
     * Writes a XML representation of this action
     *
     * @param w
     */
     //void toxml(XMLWriter w) 

    /**
     * Writes a JSON representation of this action
     *
     * @param w
     * @throws Exception
     */

    // void toJSON(Writer w); 

    /**
     * Creates a UnitAction from a XML element
     *
     * @param e
     * @param utt
     */
    //public UnitAction(Element e, UnitTypeTable utt) 


       void clearResourceUSageCache();

    /**
     * Creates a UnitAction from a XML element (calls the corresponding
     * constructor)
     *
     * @param e
     * @param utt
     * @return
     */
    //static UnitAction fromXML(Element e, UnitTypeTable utt) 

    /**
     * Creates a UnitAction from a JSON string
     *
     * @param JSON
     * @param utt
     * @return
     */
    // static UnitAction fromJSON(String JSON, UnitTypeTable utt);

    /**
     * Creates a UnitAction from a JSON object
     *
     * @param o
     * @param utt
     * @return
     */
     //static UnitAction fromJSON(JsonObject o, UnitTypeTable utt);


       bool operator==(const UnitAction& other);
      
};
/*

 */
#endif