#ifndef GAMESTATE_H // include guard
#define GAMESTATE_H  

class PlayerAction;
class GameState;
class UnitActionAssignment;
#include <unordered_map>

#include "UnitActionAssignment.h"

#include "PhysicalGameState.h"

using namespace std;

class GameState {
public:
    static const bool REPORT_ILLEGAL_ACTIONS = false;

    
    int unitCancelationCounter = 0;  // only used if the action conflict resolution strategy is set to alternating

    int time = 0;
    PhysicalGameState *pgs;
    unordered_map<long, UnitActionAssignment> unitActions;
    UnitTypeTable *utt;
    bool** _free;

    /**
     * Initializes the GameState with a PhysicalGameState and a UnitTypeTable
     * @param a_pgs
     * @param a_utt
     */
     GameState(PhysicalGameState* a_pgs, UnitTypeTable* a_utt);

        /**
         * Current game timestep (frames since beginning)
         * @return
         */
         int getTime();

    /**
     * Removes a unit from the game
      @param u
     */
      void removeUnit(Unit &u);

    /**
     * @see PhysicalGameState#getPlayer(int)
     * @param ID
     * @return
     */
      Player& getPlayer(int ID);

    /**
     * @see PhysicalGameState#getUnit(long)
     * @param ID
     * @return
     */
     // Unit* getUnit(long ID);

    /**
     * @see PhysicalGameState#getUnits()
     * @return
     */
     // vector<Unit*>* getUnits();

    /**
     * Returns a map with the units and the actions assigned to them
     * @return
     */
     // unordered_map<Unit*, UnitActionAssignment>* getUnitActions();


    //UnitTypeTable* getUnitTypeTable();


    /**
     * Returns the action of a unit
     * @param u
     * @return
     */
     //UnitAction getUnitAction(Unit *u);

    /*
      Returns the action assigned to a unit
      @param u
      @return
     */

     UnitActionAssignment* getActionAssignment(Unit &u);

    /**
     * Indicates whether all units owned by the players have a valid action or not
     * @return
     */
     // bool isComplete();

    /**
     * @see PhysicalGameState#winner()
     * @return
     */
     int winner();

    /**
     * @see PhysicalGameState#gameover()
     *@return
     */

      bool gameover();

    /**
     * Returns the {@link PhysicalGameState} associated with this state
     * @return
     */
     PhysicalGameState* getPhysicalGameState();


    /**
     * Returns true if there is no unit in the specified position and no unit is executing
     * an action that will use that position
     * @param x coordinate of the position
     * @param y coordinate of the position
     * @return
     */
     bool free(int x, int y);


    /**
     * Returns a boolean array with true if there is no unit in
     * the specified position and no unit is executing an action that will use that position
     * @return
     */
   // bool** getAllFree();
     void calculateFree();


    /**
     * Returns whether the cell is observable.
     * For fully observable game states, all the cells are observable.
     * @param x
     * @param y
     * @return
     */
     //bool observable(int x, int y);


    /**
     * Issues a player action
     * @param pa
     * @return "true" is any action different from NONE was issued
     */
     bool issue(PlayerAction &pa);


    /**
     * Issues a player action, with additional checks for validity. This function is slower
     * than "issue", and should not be used internally by any AI. It is used externally in the main loop
     * to verify that the actions proposed by an AI are valid, before sending them to the game.
     * @param pa
     * @return "true" is any action different from NONE was issued
     */
     bool issueSafe(PlayerAction &pa);

        /**
         * Indicates whether a player can issue an action in this state
         * @param pID the player ID
         * @return true if the player can execute any action
         */
         bool canExecuteAnyAction(int pID);


    /**
     *  This function checks whether the intended unit action  has any conflicts with some
     *  other action. It assumes that the UnitAction ua is valid (i.e. one of the
     *  actions that the unit can potentially execute)
     * @param u
     * @param ua
     * @return
     */
     bool isUnitActionAllowed(Unit &u, UnitAction &ua);


    /**
     *
     * @param unit
     * @return
     */
     //vector<PlayerAction*>* getPlayerActionsSingleUnit(Unit unit);


    /**
     * Returns the list of {@link PlayerAction} for a given player
     * @param playerID the player ID
     * @return
     */
     //  vector<PlayerAction*>* getPlayerActions(int playerID);


    /**
     * Returns the time the next unit action will complete, or current time
     * if a player can act
     * @return
     */
      int getNextChangeTime();
      bool updateScream();

    /**
     * Runs a game cycle, execution all assigned actions
     * @return whether the game was over
     */
        bool cycle();


    /**
     * Forces the execution of all assigned actions
     */
     //    void forceExecuteAllActions();

    /*
     * @see java.lang.Object#clone()
     */
     //   GameState clone();


    /**
     * This method does a quick clone, that shares the same PGS, but different unit assignments
     * @param pa
     * @return
     */
     //   GameState cloneIssue(PlayerAction pa);

    /**
     * Clone this game state, replacing the active {@link UnitTypeTable}
     * @param new_utt
     * @return the new GameState
     */
     //   GameState cloneChangingUTT(UnitTypeTable* new_utt);


    /**
     * Returns the resources being used for all actions issued
     * in current cycle
     * @return
     */
     ResourceUsage getResourceUsage();


    /*
     * @see java.lang.Object#equals(java.lang.Object)
     */
     //   bool equals(GameState gs);


    /**
     * Verifies integrity: if an action was assigned to non-existing unit
     * or two actions were assigned to the same unit, integrity is violated
     * @return
     */
      bool integrityCheck();


    /**
     * Shows {@link UnitActionAssignment}s on the terminal
     */
     //    void dumpActionAssignments();

    /*
     * @see java.lang.Object#toString()
     */
     //   string toString();

    /**
     * Writes a XML representation of this state into a XMLWriter
     *
     * @param w
     */
     //void toxml(XMLWriter w) 

    /**
     * Writes a XML representation of this state into a XMLWriter
     *
     * @param w
     */
     //void toxml(XMLWriter w, boolean includeConstants, boolean compressTerrain); 
    
     /**
     * Dumps this state to a XML file.
     * It can be reconstructed later (e.g. with {@link #fromXML(String, UnitTypeTable)}
     * @param path
     */
      //void toxml(String path);

    /**
     * Writes a JSON representation of this state
     *
     * @param w
     * @throws Exception
     */
      // void toJSON(Writer w);

    /**
     * Writes a JSON representation of this state
     *
     * @param w
     * @throws Exception
     */
     //void toJSON(Writer w, boolean includeConstants, boolean compressTerrain);
    
     /**
     * Constructs a GameState from a XML Element
     * @param e
     * @param utt
     * @return
     */
      //static GameState fromXML(Element e, UnitTypeTable utt);

             /**
              * Returns the GameState previously dumped (e.g. with {@link #toxml(String)} from the specified file.
              * @param utt
              * @param path
              * @return
              */
             //static GameState fromXML(string path, UnitTypeTable utt);
     
    /**
     * Constructs a GameState from JSON
     * @param JSON
     * @param utt
     * @return
     */
     // static GameState fromJSON(string JSON, UnitTypeTable utt);


};

#endif