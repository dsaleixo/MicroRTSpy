#include "PhysicalGameState.h"
#include "Player.h"
#include "Unit.h"
#include "pugixml.hpp"


int PhysicalGameState::winner() {
    
    int unitcounts[] = { 0,0 };
    int totalunits = 0;
    for (Unit* u : this->units) {
        if (u->getPlayer() >= 0) {
            unitcounts[u->getPlayer()]++;
        }
    }
    int winner = -1;
    for (int i = 0; i < 2; i++) {
        if (unitcounts[i] > 0) {
            if (winner == -1) {
                winner = i;
            }
            else {
                return -1;
            }
        }
    }

    return winner;
}

bool PhysicalGameState::gameover() {
    int unitcounts[] = {0,0};
    int totalunits = 0;
    for (Unit *u : this->units) {
        if (u->getPlayer() >= 0) {
            unitcounts[u->getPlayer()]++;
            totalunits++;
        }
    }

    if (totalunits == 0) {
        return true;
    }

    int winner = -1;
    for (int i = 0; i < 2; i++) {
        if (unitcounts[i] > 0) {
            if (winner == -1) {
                winner = i;
            }
            else {
                return false;
            }
        }
    }

    return winner != -1;
}

void PhysicalGameState::removeUnit(Unit* u) {
    this->units.erase(std::remove(this->units.begin(), this->units.end(), u),
        this->units.end());
    
}

Unit* PhysicalGameState::getUnitAt(int x, int y) {
    for (Unit* u : this->units) {
        if (u->getX() == x && u->getY() == y) {
            return u;
        }
    }
    return nullptr;
}

Player PhysicalGameState::getPlayer(int pID) {
    return this->players[pID];
}

int PhysicalGameState::getWidth() {
    return this->width;
}


int PhysicalGameState::getHeight() {
    return this->height;
}


int PhysicalGameState::getTERRAIN_WALL() {
    return TERRAIN_WALL;
}
/**
         * Returns what is on a given position of the terrain
         *
         * @param x
         * @param y
         * @return
         */
int PhysicalGameState::getTerrain(int x, int y) {

    return this->terrain[x + y * this->width];

}


PhysicalGameState::PhysicalGameState(int a_width, int a_height) {
    this->width = a_width;
    this->height = a_height;
    
}

PhysicalGameState::PhysicalGameState(int a_width, int a_height, vector<int> a_terrain) {
    this->width = a_width;
    this->height = a_height;
    this->terrain = a_terrain;

}


PhysicalGameState::~PhysicalGameState() {
  

}

Unit* PhysicalGameState::getUnit(long ID) {
    for (Unit* u : this->units) {
        if (u->getID() == ID) {
            return u;
        }
    }
    return nullptr;
}


vector<int> PhysicalGameState::getTerrainFromUnknownString(string terrainString, int size) {
    vector<int> terrain;
   //if (terrainString.contains("A") || terrainString.contains("B")) {
   //     terrain = uncompressTerrain(terrainString);
   // }
    //else {
    
        for (int i = 0; i < size; i++) {
            
            terrain.push_back( (int) terrainString[i]-48);
            
        }
       
    //}

    return terrain;
}


PhysicalGameState PhysicalGameState::fromXML(pugi::xml_node &e, UnitTypeTable &utt) {
    pugi::xml_node terrain_e = e.child("terrain");
    pugi::xml_node players_e = e.child("players");
    pugi::xml_node units_e = e.child("units");

    int width = e.attribute("width").as_int();
    int height = e.attribute("height").as_int();
   
    
    string ss = terrain_e.child_value();
   
    vector<int> terrain = getTerrainFromUnknownString(ss, width * height);
    
    PhysicalGameState pgs =  PhysicalGameState(width, height,terrain);
    
    for (pugi::xml_node o : players_e.children()) {
        Player p = Player::fromXML(o);
       
        pgs.addPlayer(p);
    }
    
    
    for (pugi::xml_node o : units_e.children()) {
       
        Unit *u = Unit::fromXML(o, utt);
        // check for repeated IDs:
        if (pgs.getUnit(u->getID()) != nullptr) {
            cout << "error pgs fromXML" << endl;
        }
      
        pgs.addUnit(u);
    }
    
    return pgs;
}

void PhysicalGameState::addPlayer(Player p) {
    this->players.push_back(p);
}

vector<Unit*>& PhysicalGameState::getUnits() {
    return this->units;

}

/**
     * Adds a new {@link Unit} to the map if its position is free
     *
     * @param newUnit
     * @throws IllegalArgumentException if the new unit's position is already
     * occupied
     */
    void PhysicalGameState::addUnit(Unit *newUnit) {
    /*
    for (Unit existingUnit : units) {
        if (newUnit.getX() == existingUnit.getX() && newUnit.getY() == existingUnit.getY()) {
            throw new IllegalArgumentException(
                "PhysicalGameState.addUnit: added two units in position: (" + newUnit.getX() + ", " + newUnit.getY() + ")");
        }
    }
    */
        this->units.push_back(newUnit);
}


PhysicalGameState  PhysicalGameState::load(string fileName, UnitTypeTable &utt) {
     
	 pugi::xml_document doc;
	 pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	 if (!result) {
		 cout<<"Error: Read map"<< fileName<<endl;
     }
     else {
         
         for (pugi::xml_node n : doc.children()) {
             cout << n.name() << endl;
         }
         
         return PhysicalGameState::fromXML(doc.child("rts.PhysicalGameState"), utt);

     }


}
