#ifndef AStar_PATH_FIND_H // include guard
#define AStar_PATH_FIND_H 

#include "UnitAction.h"
#include "GameState.h"
#include "ResourceUsage.h"
#include "Unit.h"
#include "PathFinding.h"

class AStarPathFinding  {
public:
    bool **free;
    int *closed;
    int *open;  // open list
    int *heuristic;     // heuristic value of the elements in 'open'
    int *parents;
    int *cost;     // cost of reaching a given position so far
    int *inOpenOrClosed;
    int openinsert = 0;
    int w = 0;
    int h = 0; 


    AStarPathFinding(int a_width, int height);
    void clear();

    // This fucntion finds the shortest path from 'start' to 'targetpos' and then returns
   // a UnitAction of the type 'actionType' with the direction of the first step in the shorteet path
     UnitAction findPath(Unit *start, int targetpos, GameState &gs, ResourceUsage &ru);


    /*
     * This function is like the previous one, but doesn't try to reach 'target', but just to
     * reach a position that is at most 'range' far away from 'target'
     */
     UnitAction findPathToPositionInRange(Unit *start, int targetpos, int range, GameState &gs);
         

    //virtual Pair<Integer, Integer> findPathToPositionInRange2(Unit start, int targetpos, int range, GameState gs);


    /*
     * This function is like the previous one, but doesn't try to reach 'target', but just to
     * reach a position adjacent to 'target'
     */
   
   
    // and keep the "open" list sorted:
     void addToOpen(int x, int y, int newPos, int oldPos, int h);


     int manhattanDistance(int x, int y, int x2, int y2);

      UnitAction findPathToAdjacentPosition(Unit *start, int targetpos, GameState gs);

    




};

#endif