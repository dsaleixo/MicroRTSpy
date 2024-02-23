#include "AStarPathFinding.h"


 UnitAction AStarPathFinding::findPathToAdjacentPosition(Unit *start, int targetpos, GameState gs) {
    return findPathToPositionInRange(start, targetpos, 1, gs);
}

AStarPathFinding::AStarPathFinding(int a_width, int a_height) {
    this->h = a_height;
    this->w = a_width;
    this->free = new bool*[this->w];
    for (int i = 0; i < this->w; i++) this->free[i] = new bool[this->h];
    this->closed = new int[this->w * this->h];
    this->open = new int[this->w * this->h];
    this->heuristic = new int[this->w * this->h];
    this->parents = new int[this->w * this->h];
    this->inOpenOrClosed = new int[this->w * this->h];
    this->cost = new int[this->w * this->h];
}



void AStarPathFinding::clear() {
    for (int y = 0, i = 0; y < this->h; y++) {
        for (int x = 0; x < this->w; x++, i++) {
            free[x][y] = NULL;
            closed[i] = -1;
            inOpenOrClosed[i] = 0;
        }
    }
    /*
    for (int pos : ru.getPositionsUsed()) {
        free[pos % this->w][pos / this->w] = false;
    }
   */
}

 UnitAction AStarPathFinding::findPath(Unit* start, int targetpos, GameState& gs, ResourceUsage& ru) {
     return this->findPathToPositionInRange(start, targetpos, 0, gs);
}


 UnitAction AStarPathFinding::findPathToPositionInRange(Unit* start, int targetpos, int range, GameState& gs) {
     this->clear();
     PhysicalGameState *pgs = gs.getPhysicalGameState();
     
     int targetx = targetpos % this->w;
     int targety = targetpos / this->w;
     int sq_range = range * range;
     int startPos = start->getY() * this->w + start->getX();


     openinsert = 0;
     open[openinsert] = startPos;
     heuristic[openinsert] = this->manhattanDistance(start->getX(), start->getY(), targetx, targety);
     parents[openinsert] = startPos;
     inOpenOrClosed[startPos] = 1;
     cost[startPos] = 0;
     openinsert++;


     while (openinsert > 0) {

         openinsert--;
         int pos = open[openinsert];
         int parent = parents[openinsert];
         if (closed[pos] != -1) continue;
         closed[pos] = parent;

         int x = pos % w;
         int y = pos / w;

         if (((x - targetx) * (x - targetx) + (y - targety) * (y - targety)) <= sq_range) {
             // path found, backtrack:
             int last = pos;
             //                System.out.println("- Path from " + start.getX() + "," + start.getY() + " to " + targetpos%w + "," + targetpos/w + " (range " + range + ") in " + iterations + " iterations");
             while (parent != pos) {
                 last = pos;
                 pos = parent;
                 parent = closed[pos];
            
                 //                    System.out.println("    " + pos%w + "," + pos/w);
             }
             if (last == pos + w) return  UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_DOWN);
             if (last == pos - 1) return  UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_LEFT);
             if (last == pos - w) return  UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_UP);
             if (last == pos + 1) return  UnitAction(UnitAction::TYPE_MOVE, UnitAction::DIRECTION_RIGHT);
             return UnitAction(UnitAction::TYPE_NONE);
         }
         if (y > 0 && inOpenOrClosed[pos - w] == 0) {
             if (free[x][y - 1] == NULL) free[x][y - 1] = gs.free(x, y - 1);
             
             if (free[x][y - 1]) {
                 addToOpen(x, y - 1, pos - w, pos, manhattanDistance(x, y - 1, targetx, targety));
             }
         }
         if (x < pgs->getWidth() - 1 && inOpenOrClosed[pos + 1] == 0) {
             if (free[x + 1][y] == NULL) free[x + 1][y] = gs.free(x + 1, y);
             
             if (free[x + 1][y]) {
                 addToOpen(x + 1, y, pos + 1, pos, manhattanDistance(x + 1, y, targetx, targety));
             }
         }
         if (y < pgs->getHeight() - 1 && inOpenOrClosed[pos + w] == 0) {
             if (free[x][y + 1] == NULL) free[x][y + 1] = gs.free(x, y + 1);
             
             if (free[x][y + 1]) {
                 addToOpen(x, y + 1, pos + w, pos, manhattanDistance(x, y + 1, targetx, targety));
             }
         }
         if (x > 0 && inOpenOrClosed[pos - 1] == 0) {
             if (free[x - 1][y] == NULL) free[x - 1][y] = gs.free(x - 1, y);
             
             if (free[x - 1][y]) {
                 addToOpen(x - 1, y, pos - 1, pos, manhattanDistance(x - 1, y, targetx, targety));
             }
         }


     }
     return UnitAction(UnitAction::TYPE_NONE);

  }

 void AStarPathFinding::addToOpen(int x, int y, int newPos, int oldPos, int h) {
     cost[newPos] = cost[oldPos] + 1;

     // find the right position for the insert:
     for (int i = openinsert - 1; i >= 0; i--) {
         if (heuristic[i] + cost[open[i]] >= h + cost[newPos]) {
             //                System.out.println("Inserting at " + (i+1) + " / " + openinsert);
                             // shift all the elements:
             for (int j = openinsert; j >= i + 1; j--) {
                 open[j] = open[j - 1];
                 heuristic[j] = heuristic[j - 1];
                 parents[j] = parents[j - 1];
             }

             // insert at i+1:
             open[i + 1] = newPos;
             heuristic[i + 1] = h;
             parents[i + 1] = oldPos;
             openinsert++;
             inOpenOrClosed[newPos] = 1;
             return;
         }
     }
     // i = -1;
//        System.out.println("Inserting at " + 0 + " / " + openinsert);
        // shift all the elements:
     for (int j = openinsert; j >= 1; j--) {
         open[j] = open[j - 1];
         heuristic[j] = heuristic[j - 1];
         parents[j] = parents[j - 1];
     }

     // insert at i+1:
     open[0] = newPos;
     heuristic[0] = h;
     parents[0] = oldPos;
     openinsert++;
     inOpenOrClosed[newPos] = 1;
 }



 int AStarPathFinding::manhattanDistance(int x, int y, int x2, int y2) {
     return abs(x - x2) + abs(y - y2);
 }
