#ifndef PlayerAction_H // include guard
#define PlayerAction_H  
class UnitAction;
#include "UnitAction.h"
#include "Unit.h"
#include "ResourceUsage.h"
#include <vector>

#include "GameState.h"

using namespace std;


class PlayerAction {

public:

    /**
     * A list of unit actions
     */
    vector<pair<Unit*, UnitAction>> actions;
   
    /**
     * Represents the resources used by the player action
     * TODO rename the field
     */
     // ResourceUsage r;

    /**
     *
     */
     PlayerAction();


    /* (non-Javadoc)
     * @see java.lang.Object#equals(java.lang.Object)
     */
     //bool equals(PlayerAction o);


    /**
     * Returns whether there are no player actions
     * @return
     */
     //bool isEmpty();

    /**
     * Returns whether the player has assigned any action different
     * than {@link UnitAction#TYPE_NONE} to any of its units
     * @return
     */
     //bool hasNonNoneActions();

    /**
     * Returns the number of actions different than
     * {@link UnitAction#TYPE_NONE}
     * @return
     */

     //int hasNamNoneActions();


    /**
     * Returns the usage of resources
     * @return
     */
     // ResourceUsage getResourceUsage();

    /**
     * Sets the resource usage
     * @param a_r
     */

     //void setResourceUsage(ResourceUsage a_r);

    /**
     * Adds a new {@link UnitAction} to a given {@link Unit}
     * @param u
     * @param a
     */
     void addUnitAction(Unit *u, UnitAction a);

    /**
     * Removes a pair of Unit and UnitAction from the list
     * @param u
     * @param a
     */
     //void removeUnitAction(Unit *u, UnitAction a);

    /**
     * Merges this with another PlayerAction
     * @param a
     * @return
     */
     //PlayerAction merge(PlayerAction a);


    /**
     * Returns a list of pairs of units and UnitActions
     * @return
     */

     //vector<pair<Unit*, UnitAction>> getActions();

    /**
     * Searches for the unit in the collection and returns the respective {@link UnitAction}
     * @param u
     * @return
     */

     //UnitAction getAction(Unit *u);

    /**
     * @param lu
     * @param u
     * @param s
     * @return
     */

     //vector<PlayerAction> cartesianProduct(vector<UnitAction>* lu, Unit* u, GameState* s);

    /**
     * Returns whether this PlayerAction is consistent with a
     * given {@link ResourceUsage} and a {@link GameState}
     * @param u
     * @param gs
     * @return
     */
     //bool consistentWith(ResourceUsage u, GameState *gs);


    /**
     * Assign "none" to all the units that need an action and do not have one
     * for the specified duration
     * @param s
     * @param pID the player ID
     * @param duration the number of frames the 'none' action should last
     */
     //void fillWithNones(GameState *s, int pID, int duration);


    /**
     * Returns true if this object passes the integrity check.
     * It fails if the unit is being assigned an action from a player
     * that does not owns it
     * @return
     */
    bool integrityCheck();

    /* (non-Javadoc)
     * @see java.lang.Object#clone()
     */

     //PlayerAction clone();
    

    /**
     * Resets the PlayerAction
     */

     //void clear();


    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
     //string toString();


    /**
     * Writes to XML
     * @param w
     */
     // void toxml(XMLWriter w);


    /**
     * Writes to JSON
     * @param w
     * @throws Exception
     */
     //void toJSON(Writer w);
    


    /**
     * Creates a PlayerAction from a XML element
     * @param e
     * @param gs
     * @param utt
     * @return
     */
     //static PlayerAction fromXML(Element e, GameState gs, UnitTypeTable utt) 
    
         
         /**
     * Creates a PlayerAction from a JSON object
     * @param JSON
     * @param gs
     * @param utt
     * @return
     */
     //static PlayerAction fromJSON(String JSON, GameState gs, UnitTypeTable utt);


};

#endif