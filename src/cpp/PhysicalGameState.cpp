#include "PhysicalGameState.h"
#include "Player.h"
#include "Unit.h"
#include "pugixml.hpp"

long Unit::next_ID = 0;

PhysicalGameState::PhysicalGameState(int a_width, int a_height) {
    width = a_width;
    height = a_height;
    
}

PhysicalGameState::~PhysicalGameState() {
  

}

Unit* PhysicalGameState::getUnit(long ID) {
    for (Unit u : this->units) {
        if (u.getID() == ID) {
            return &u;
        }
    }
    return nullptr;
}


int* PhysicalGameState::getTerrainFromUnknownString(string terrainString, int size) {
    int *terrain = new int[size];
   //if (terrainString.contains("A") || terrainString.contains("B")) {
   //     terrain = uncompressTerrain(terrainString);
   // }
    //else {
    
        for (int i = 0; i < size; i++) {
            
            terrain[i] = (int) terrainString[i]-48;
            
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
    cout << height << " " << height << endl;
    
    string ss = terrain_e.child_value();
    cout<<ss << endl;
    int *terrain = getTerrainFromUnknownString(ss, width * height);
    
    PhysicalGameState pgs =  PhysicalGameState(width, height);
    
    for (pugi::xml_node o : players_e.children()) {
        Player p = Player::fromXML(o);
        cout << p.toString() << endl;
        pgs.addPlayer(p);
    }
    
    
    for (pugi::xml_node o : units_e.children()) {
       
        Unit u = Unit::fromXML(o, utt);
        // check for repeated IDs:
        if (pgs.getUnit(u.getID()) != nullptr) {
            cout << "error pgs fromXML" << endl;
        }
        pgs.addUnit(u);
    }
    
    return pgs;
}

void PhysicalGameState::addPlayer(Player p) {
    this->players.push_back(p);
}

vector<Unit>& PhysicalGameState::getUnits() {
    return this->units;

}

/**
     * Adds a new {@link Unit} to the map if its position is free
     *
     * @param newUnit
     * @throws IllegalArgumentException if the new unit's position is already
     * occupied
     */
    void PhysicalGameState::addUnit(Unit &newUnit) {
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
