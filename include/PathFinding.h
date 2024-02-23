#ifndef PATH_FIND_H // include guard
#define PATH_FIND_H 

#include "UnitAction.h"
#include "GameState.h"
#include "ResourceUsage.h"
#include "Unit.h"


class PathFinding {
public:

    // This fucntion finds the shortest path from 'start' to 'targetpos' and then returns
   // a UnitAction of the type 'actionType' with the direction of the first step in the shorteet path
    virtual UnitAction findPath(Unit *start, int targetpos, GameState &gs, ResourceUsage &ru);


    /*
     * This function is like the previous one, but doesn't try to reach 'target', but just to
     * reach a position that is at most 'range' far away from 'target'
     */
    virtual UnitAction findPathToPositionInRange(Unit *start, int targetpos, int range, GameState &gs, ResourceUsage &ru);
         

    //virtual Pair<Integer, Integer> findPathToPositionInRange2(Unit start, int targetpos, int range, GameState gs);


    /*
     * This function is like the previous one, but doesn't try to reach 'target', but just to
     * reach a position adjacent to 'target'
     */
       




};
#endif