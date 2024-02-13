#include "UnitType.h"
#include <iostream>

using namespace std;

    
    bool UnitType::getCanMove() {
        return this->canMove;
    }

    bool UnitType::getIsStockpile() {
        return this->isStockpile;
    }

    UnitType::UnitType() {
    ;
    }
    UnitType::UnitType(const UnitType &other) {
        this->name = other.name;
    }
  

    string UnitType::getName() {
        return this->name;
    }


    /**
     * Returns the hash code of the name
     * // assume that all unit types have different names:
     */
    //int UnitType::hashCode() {
    //    return name.hashCode();
    //}

    /* (non-Javadoc)
     * @see java.lang.Object#equals(java.lang.Object)
     */
    bool UnitType::equals(UnitType ut) {
        
        return this->name == ut.name;
    }
    
    /**
     * Adds a unit type that a unit of this type can produce
     * @param ut
     */
    void UnitType::produces(UnitType *ut)
    {
        this->produces_v.push_back(ut);
        ut->producedBy_v.push_back(this);
    }

    /**
     * Creates a temporary instance with just the name and ID from a XML element
     * @param unittype_e
     * @return
     
    static UnitType createStub(Element unittype_e) {
        UnitType ut = new UnitType();
        ut.ID = Integer.parseInt(unittype_e.getAttributeValue("ID"));
        ut.name = unittype_e.getAttributeValue("name");
        return ut;
    }
    */

    /**
     * Creates a temporary instance with just the name and ID from a JSON object
     * @param o
     * @return
    
    static UnitType createStub(JsonObject o) {
        UnitType ut = new UnitType();
        ut.ID = o.getInt("ID", -1);
        ut.name = o.getString("name", null);
        return ut;
    }
     */
    /**
     * Updates the attributes of this type from XML
     * @param unittype_e
     * @param utt
     
    void updateFromXML(Element unittype_e, UnitTypeTable utt) {
        cost = Integer.parseInt(unittype_e.getAttributeValue("cost"));
        hp = Integer.parseInt(unittype_e.getAttributeValue("hp"));
        minDamage = Integer.parseInt(unittype_e.getAttributeValue("minDamage"));
        maxDamage = Integer.parseInt(unittype_e.getAttributeValue("maxDamage"));
        attackRange = Integer.parseInt(unittype_e.getAttributeValue("attackRange"));

        produceTime = Integer.parseInt(unittype_e.getAttributeValue("produceTime"));
        moveTime = Integer.parseInt(unittype_e.getAttributeValue("moveTime"));
        attackTime = Integer.parseInt(unittype_e.getAttributeValue("attackTime"));
        harvestTime = Integer.parseInt(unittype_e.getAttributeValue("harvestTime"));
        returnTime = Integer.parseInt(unittype_e.getAttributeValue("returnTime"));

        harvestAmount = Integer.parseInt(unittype_e.getAttributeValue("harvestAmount"));
        sightRadius = Integer.parseInt(unittype_e.getAttributeValue("sightRadius"));

        isResource = Boolean.parseBoolean(unittype_e.getAttributeValue("isResource"));
        isStockpile = Boolean.parseBoolean(unittype_e.getAttributeValue("isStockpile"));
        canHarvest = Boolean.parseBoolean(unittype_e.getAttributeValue("canHarvest"));
        canMove = Boolean.parseBoolean(unittype_e.getAttributeValue("canMove"));
        canAttack = Boolean.parseBoolean(unittype_e.getAttributeValue("canAttack"));

        for (Object o : unittype_e.getChildren("produces")) {
            Element produces_e = (Element)o;
            produces.add(utt.getUnitType(produces_e.getAttributeValue("type")));
        }

        for (Object o : unittype_e.getChildren("producedBy")) {
            Element producedby_e = (Element)o;
            producedBy.add(utt.getUnitType(producedby_e.getAttributeValue("type")));
        }
    }
    */
    /**
     * Updates the attributes of this type from a JSON string
     * @param JSON
     * @param utt
     
    void updateFromJSON(String JSON, UnitTypeTable utt) {
        JsonObject o = Json.parse(JSON).asObject();
        updateFromJSON(o, utt);
    }
    */

    /**
     * Updates the attributes of this type from a JSON object
     * @param o
     * @param utt
     
    void updateFromJSON(JsonObject o, UnitTypeTable utt) {
        cost = o.getInt("cost", 1);
        hp = o.getInt("hp", 1);
        minDamage = o.getInt("minDamage", 1);
        maxDamage = o.getInt("maxDamage", 1);
        attackRange = o.getInt("attackRange", 1);

        produceTime = o.getInt("produceTime", 10);
        moveTime = o.getInt("moveTime", 10);
        attackTime = o.getInt("attackTime", 10);
        harvestTime = o.getInt("produceTime", 10);
        produceTime = o.getInt("produceTime", 10);

        harvestAmount = o.getInt("harvestAmount", 10);
        sightRadius = o.getInt("sightRadius", 10);

        isResource = o.getBoolean("isResource", false);
        isStockpile = o.getBoolean("isStockpile", false);
        canHarvest = o.getBoolean("canHarvest", false);
        canMove = o.getBoolean("canMove", false);
        canAttack = o.getBoolean("canAttack", false);

        JsonArray produces_a = o.get("produces").asArray();
        for (JsonValue v : produces_a.values()) {
            produces.add(utt.getUnitType(v.asString()));
        }

        JsonArray producedBy_a = o.get("producedBy").asArray();
        for (JsonValue v : producedBy_a.values()) {
            producedBy.add(utt.getUnitType(v.asString()));
        }
    }
    */

    /**
     * Writes a XML representation
     * @param w
    
    public void toxml(XMLWriter w) {
        w.tagWithAttributes(
            this.getClass().getName(),
            "ID=\"" + ID + "\" " +
            "name=\"" + name + "\" " +
            "cost=\"" + cost + "\" " +
            "hp=\"" + hp + "\" " +
            "minDamage=\"" + minDamage + "\" " +
            "maxDamage=\"" + maxDamage + "\" " +
            "attackRange=\"" + attackRange + "\" " +

            "produceTime=\"" + produceTime + "\" " +
            "moveTime=\"" + moveTime + "\" " +
            "attackTime=\"" + attackTime + "\" " +
            "harvestTime=\"" + harvestTime + "\" " +
            "returnTime=\"" + returnTime + "\" " +

            "harvestAmount=\"" + harvestAmount + "\" " +
            "sightRadius=\"" + sightRadius + "\" " +

            "isResource=\"" + isResource + "\" " +
            "isStockpile=\"" + isStockpile + "\" " +
            "canHarvest=\"" + canHarvest + "\" " +
            "canMove=\"" + canMove + "\" " +
            "canAttack=\"" + canAttack + "\""
        );

        for (UnitType ut : produces) {
            w.tagWithAttributes("produces", "type=\"" + ut.name + "\"");
            w.tag("/produces");
        }
        for (UnitType ut : producedBy) {
            w.tagWithAttributes("producedBy", "type=\"" + ut.name + "\"");
            w.tag("/producedBy");
        }
        w.tag("/" + this.getClass().getName());
    }

    */
    /**
     * Writes a JSON representation
     * @param w
     * @throws Exception
     
    public void toJSON(Writer w) throws Exception {
        w.write(
            "{" +
            "\"ID\":" + ID + ", " +
            "\"name\":\"" + name + "\", " +
            "\"cost\":" + cost + ", " +
            "\"hp\":" + hp + ", " +
            "\"minDamage\":" + minDamage + ", " +
            "\"maxDamage\":" + maxDamage + ", " +
            "\"attackRange\":" + attackRange + ", " +

            "\"produceTime\":" + produceTime + ", " +
            "\"moveTime\":" + moveTime + ", " +
            "\"attackTime\":" + attackTime + ", " +
            "\"harvestTime\":" + harvestTime + ", " +
            "\"returnTime\":" + returnTime + ", " +

            "\"harvestAmount\":" + harvestAmount + ", " +
            "\"sightRadius\":" + sightRadius + ", " +

            "\"isResource\":" + isResource + ", " +
            "\"isStockpile\":" + isStockpile + ", " +
            "\"canHarvest\":" + canHarvest + ", " +
            "\"canMove\":" + canMove + ", " +
            "\"canAttack\":" + canAttack + ", "
        );

        boolean first = true;
        w.write("\"produces\":[");
        for (UnitType ut : produces) {
            if (!first)
                w.write(", ");
            w.write("\"" + ut.name + "\"");
            first = false;
        }
        first = true;
        w.write("], \"producedBy\":[");
        for (UnitType ut : producedBy) {
            if (!first)
                w.write(", ");
            w.write("\"" + ut.name + "\"");
            first = false;
        }
        w.write("]}");
    }
    */
    /**
     * Creates a unit type from XML
     * @param e
     * @param utt
     * @return
     
    public static UnitType fromXML(Element e, UnitTypeTable utt) {
        UnitType ut = new UnitType();
        ut.updateFromXML(e, utt);
        return ut;
    }
    */

    /**
     * Creates a unit type from a JSON string
     * @param JSON
     * @param utt
     * @return
    
    public static UnitType fromJSON(String JSON, UnitTypeTable utt) {
        UnitType ut = new UnitType();
        ut.updateFromJSON(JSON, utt);
        return ut;
    }

     */
    /**
     * Creates a unit type from a JSON object
     * @param o
     * @param utt
     * @return
    
    public static UnitType fromJSON(JsonObject o, UnitTypeTable utt) {
        UnitType ut = new UnitType();
        ut.updateFromJSON(o, utt);
        return ut;
    }
     */