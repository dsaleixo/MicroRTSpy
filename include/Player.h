#ifndef PLAYER_H // include guard
#define PLAYER_H  

#include <string>
#include "pugixml.hpp"
using namespace std;

class Player {

    /**
     * An integer that identifies the player
     */
    int ID = 0;

    /**
     * The amount of resources owned by the player
     */
    int resources = 0;


    public:
        /**
         * Creates a Player instance with the given ID and resources
         * @param a_ID
         * @param a_resources
         */
        Player(int a_ID, int a_resources);

        /**
         * Returns the player ID
         * @return
         */
        int getID();

        /**
         * Returns the amount of resources owned by the player
         * @return
         */
         int getResources();

        /**
         * Sets the amount of resources owned by the player
         * @param a_resources
         */
         void setResources(int a_resources);



             /* (non-Javadoc)
              * @see java.lang.Object#toString()
              */
           string toString();

        /* (non-Javadoc)
         * @see java.lang.Object#clone()
         */
           Player clone();

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
           static Player fromXML(pugi::xml_node &e);

        /**
         * Constructs a Player from a JSON object
         * @param o
         * @return
     
        public static Player fromJSON(JsonObject o) {
            Player p = new Player(o.getInt("ID", -1),
                o.getInt("resources", 0));
            return p;
        }
        */
};

#endif