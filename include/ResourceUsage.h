#ifndef ResourceUsage_H // include guard
#define ResourceUsage_H  
class ResourceUsage;
class UnitAction;
#include "GameState.h"
#include <vector>
#include <string>

using namespace std;

class ResourceUsage {
public:
    vector<int> positionsUsed;
    int resourcesUsed[2] = { 0,0 };

    /**
     * Empty constructor
     */
    ResourceUsage();

    /**
     * Returns whether this instance is consistent with another ResourceUsage in
     * a given game state. Resource usages are consistent if they respect the
     * players' resource amount and don't have conflicting uses
     *
     * @param anotherUsage
     * @param gs
     * @return
     */
    bool consistentWith(ResourceUsage &anotherUsage, GameState *gs);
    /**
     * Returns the list with used resource positions
     *
     * @return
     */

    vector<int> getPositionsUsed();

    /**
     * Returns the amount of resources used by the player
     *
     * @param player
     * @return
     */
    int getResourcesUsed(int player);

    /**
     * Merges this and another instance of ResourceUsage into a new one
     *
     * @param other
     * @return
     */
    ResourceUsage mergeIntoNew(ResourceUsage other);

    /**
     * Merges another instance of ResourceUsage into this one
     *
     * @param other
     */
    void merge(ResourceUsage other);

    ResourceUsage clone();

    string toString();


};

#endif