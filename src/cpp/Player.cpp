#include "Player.h"
#include "pugixml.hpp"

Player::Player(int a_ID, int a_resources) {
    this->ID = a_ID;
    this->resources = a_resources;
}

/**
 * Returns the player ID
 * @return
 */
 int Player::getID() {
    return this->ID;
}

/**
 * Returns the amount of resources owned by the player
 * @return
 */
int Player::getResources() {
    return this->resources;
}

/**
 * Sets the amount of resources owned by the player
 * @param a_resources
 */
 void Player::setResources(int a_resources) {
    this->resources = a_resources;
}

/* (non-Javadoc)
 * @see java.lang.Object#toString()
 */
string Player::toString() {
    return "player " + to_string(ID) + "(" + to_string(resources) + ")";
}

/* (non-Javadoc)
 * @see java.lang.Object#clone()
 */
 Player Player::clone() {
    return  Player(ID, resources);
}

/**
 * Writes a XML representation of the player
 * @param w
 
public void toxml(XMLWriter w) {
    w.tagWithAttributes(this.getClass().getName(), "ID=\"" + ID + "\" resources=\"" + resources + "\"");
    w.tag("/" + this.getClass().getName());
}
*/
/**
 * Writes a JSON representation of the player
 * @param w
 * @throws Exception

public void toJSON(Writer w) throws Exception {
    w.write("{\"ID\":" + ID + ", \"resources\":" + resources + "}");
}
*/
/**
 * Constructs a player from a XML player element
 * @param e
 * @return
 */
 Player Player::fromXML(pugi::xml_node &e) {
     int id = e.attribute("ID").as_int();
     int resources = e.attribute("resources").as_int();
    Player p =  Player(id, resources);
    return p;
}

/**
 * Constructs a Player from a JSON object
 * @param o
 * @return
 
  Player Player::fromJSON(JsonObject o) {
    Player p = new Player(o.getInt("ID", -1),
        o.getInt("resources", 0));
    return p;
    
}

*/