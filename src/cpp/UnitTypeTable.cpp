
#include <vector>
#include "UnitTypeTable.h"

   
    UnitTypeTable::~UnitTypeTable() {

    }
    

    /**
     * Creates a UnitTypeTable with version {@link #VERSION_ORIGINAL} and
     * move conflict resolution as {@link #MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH}
     */
    UnitTypeTable::UnitTypeTable() {
        setUnitTypeTable(VERSION_ORIGINAL, MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH);
    }

    /**
     * Creates a unit type table with specified version and move conflict resolution
     * as {@link #MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH}
     * @param version
     */
    UnitTypeTable::UnitTypeTable(int version) {
        setUnitTypeTable(version, MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH);
    }

    /**
     * Creates a unit type table specifying both the version and the move conflict
     * resolution strategy
     * @param version
     * @param crs the move conflict resolution strategy
     */
    UnitTypeTable::UnitTypeTable(int version, int crs) {
        setUnitTypeTable(version, crs);
    }


    /**
     * Sets the version and move conflict resolution strategy to use
     * and configures the attributes of each unit type depending on the
     * version
     * @param version
     * @param crs the move conflict resolution strategy
     */
    void UnitTypeTable::setUnitTypeTable(int version, int crs) {
        moveConflictResolutionStrategy = crs;

        if (version == EMPTY_TYPE_TABLE) return;

        // Create the unit types:
        // RESOURCE:
        UnitType resource =  UnitType();
        resource.name = "R	esource";
        resource.isResource = true;
        resource.isStockpile = false;
        resource.canHarvest = false;
        resource.canMove = false;
        resource.canAttack = false;
        resource.sightRadius = 0;
        addUnitType(resource);

        // BASE:
        UnitType base =  UnitType();
        base.name = "Base";
        base.cost = 10;
        base.hp = 10;
        switch (version) {
        case VERSION_ORIGINAL: base.produceTime = 250;
            break;
        case VERSION_ORIGINAL_FINETUNED: base.produceTime = 200;
            break;
        }
        base.isResource = false;
        base.isStockpile = true;
        base.canHarvest = false;
        base.canMove = false;
        base.canAttack = false;
        base.sightRadius = 5;
        addUnitType(base);

        // BARRACKS: 
        UnitType barracks =  UnitType();
        barracks.name = "Barracks";
        barracks.cost = 5;
        barracks.hp = 4;
        switch (version) {
        case VERSION_ORIGINAL:
            barracks.produceTime = 200;
            break;
        case VERSION_ORIGINAL_FINETUNED:
        case VERSION_NON_DETERMINISTIC:
            barracks.produceTime = 100;
            break;
        }
        barracks.isResource = false;
        barracks.isStockpile = false;
        barracks.canHarvest = false;
        barracks.canMove = false;
        barracks.canAttack = false;
        barracks.sightRadius = 3;
        addUnitType(barracks);

        // WORKER: 
        UnitType worker =  UnitType();
        worker.name = "Worker";
        worker.cost = 1;
        worker.hp = 1;
        switch (version) {
        case VERSION_ORIGINAL:
        case VERSION_ORIGINAL_FINETUNED:
            worker.minDamage = worker.maxDamage = 1;
            break;
        case VERSION_NON_DETERMINISTIC:
            worker.minDamage = 0;
            worker.maxDamage = 2;
            break;
        }
        worker.attackRange = 1;
        worker.produceTime = 50;
        worker.moveTime = 10;
        worker.attackTime = 5;
        worker.harvestTime = 20;
        worker.returnTime = 10;
        worker.isResource = false;
        worker.isStockpile = false;
        worker.canHarvest = true;
        worker.canMove = true;
        worker.canAttack = true;
        worker.sightRadius = 3;
        addUnitType(worker);

        // LIGHT: 
        UnitType light =  UnitType();
        light.name = "Light";
        light.cost = 2;
        light.hp = 4;
        switch (version) {
        case VERSION_ORIGINAL:
        case VERSION_ORIGINAL_FINETUNED:
            light.minDamage = light.maxDamage = 2;
            break;
        case VERSION_NON_DETERMINISTIC:
            light.minDamage = 1;
            light.maxDamage = 3;
            break;
        }
        light.attackRange = 1;
        light.produceTime = 80;
        light.moveTime = 8;
        light.attackTime = 5;
        light.isResource = false;
        light.isStockpile = false;
        light.canHarvest = false;
        light.canMove = true;
        light.canAttack = true;
        light.sightRadius = 2;
        addUnitType(light);

        // HEAVY: 
        UnitType heavy =  UnitType();
        heavy.name = "Heavy";
        switch (version) {
        case VERSION_ORIGINAL:
        case VERSION_ORIGINAL_FINETUNED:
            heavy.minDamage = heavy.maxDamage = 4;
            break;
        case VERSION_NON_DETERMINISTIC:
            heavy.minDamage = 0;
            heavy.maxDamage = 6;
            break;
        }
        heavy.attackRange = 1;
        heavy.produceTime = 120;
        switch (version) {
        case VERSION_ORIGINAL:
            heavy.moveTime = 12;
            heavy.hp = 4;
            heavy.cost = 2;
            break;
        case VERSION_ORIGINAL_FINETUNED:
        case VERSION_NON_DETERMINISTIC:
            heavy.moveTime = 10;
            heavy.hp = 8;
            heavy.cost = 3;
            break;
        }
        heavy.attackTime = 5;
        heavy.isResource = false;
        heavy.isStockpile = false;
        heavy.canHarvest = false;
        heavy.canMove = true;
        heavy.canAttack = true;
        heavy.sightRadius = 2;
        addUnitType(heavy);

        // RANGED: 
        UnitType ranged =  UnitType();
        ranged.name = "Ranged";
        ranged.cost = 2;
        ranged.hp = 1;
        switch (version) {
        case VERSION_ORIGINAL:
        case VERSION_ORIGINAL_FINETUNED:
            ranged.minDamage = ranged.maxDamage = 1;
            break;
        case VERSION_NON_DETERMINISTIC:
            ranged.minDamage = 1;
            ranged.maxDamage = 2;
            break;
        }
        ranged.attackRange = 3;
        ranged.produceTime = 100;
        ranged.moveTime = 10;
        ranged.attackTime = 5;
        ranged.isResource = false;
        ranged.isStockpile = false;
        ranged.canHarvest = false;
        ranged.canMove = true;
        ranged.canAttack = true;
        ranged.sightRadius = 3;
        addUnitType(ranged);


        base.produces(worker);
        barracks.produces(light);
        barracks.produces(heavy);
        barracks.produces(ranged);
        worker.produces(base);
        worker.produces(barracks);
    }

    /**
     * Adds a new unit type to the game
     * @param ut
     */
    void UnitTypeTable::addUnitType(UnitType ut) {
        ut.ID = unitTypes.size();
        unitTypes.push_back(ut);
    }

    /**
     * Retrieves a unit type by its numeric ID
     * @param ID
     * @return
     */
     UnitType UnitTypeTable::getUnitType(int ID) {
        return unitTypes[ID];
    }

    /**
     * Retrieves a unit type by its name. Returns null if name is not found.
     * @param name
     * @return
     */
     UnitType UnitTypeTable::getUnitType(string name) {
        for (UnitType ut : unitTypes) {
            if (ut.name == name) return ut;
        }
       
    }

    /**
     * Returns the list of all unit types
     * @return
     */
    vector<UnitType>* UnitTypeTable::getUnitTypes() {
        return &unitTypes;
    }

    /**
     * Returns the integer corresponding to the move conflict resolution strategy in use
     * @return
     */
    int UnitTypeTable::getMoveConflictResolutionStrategy() {
        return moveConflictResolutionStrategy;
    }


    /**
     * Writes a XML representation of this UnitTypeTable
     * @param w
     
    public void toxml(XMLWriter w) {
        w.tagWithAttributes(
            this.getClass().getName(),
            "moveConflictResolutionStrategy=\"" + moveConflictResolutionStrategy + "\""
        );

        for (UnitType ut : unitTypes)
            ut.toxml(w);

        w.tag("/" + this.getClass().getName());
    }
    */
    /**
     * Writes a JSON representation of this UnitTypeTable
     * @param w
     * @throws Exception
     
    public void toJSON(Writer w) throws Exception {
        boolean first = true;
        w.write("{\"moveConflictResolutionStrategy\":" + moveConflictResolutionStrategy + ",");
        w.write("\"unitTypes\":[");
        for (UnitType ut : unitTypes) {
            if (!first)
                w.write(", ");
            ut.toJSON(w);
            first = false;
        }
        w.write("]}");
    }
    */

    /**
     * Reads from XML and creates a UnitTypeTable
     * @param e
     * @return
    
    public static UnitTypeTable fromXML(Element e) {
        UnitTypeTable utt = new UnitTypeTable(EMPTY_TYPE_TABLE);
        utt.moveConflictResolutionStrategy = Integer.parseInt(
            e.getAttributeValue("moveConflictResolutionStrategy")
        );

        for (Object o : e.getChildren()) {
            Element unittype_e = (Element)o;
            utt.unitTypes.add(UnitType.createStub(unittype_e));
        }
        for (Object o : e.getChildren()) {
            Element unittype_e = (Element)o;
            utt.getUnitType(unittype_e.getAttributeValue("name")).updateFromXML(unittype_e, utt);
        }
        return utt;
    }
    */

    /**
     * Reads from a JSON string and creates a UnitTypeTable
     * @param JSON
     * @return
     
    public static UnitTypeTable fromJSON(String JSON) {
        JsonObject o = Json.parse(JSON).asObject();
        UnitTypeTable utt = new UnitTypeTable(EMPTY_TYPE_TABLE);
        utt.moveConflictResolutionStrategy = o.getInt(
            "moveConflictResolutionStrategy",
            MOVE_CONFLICT_RESOLUTION_CANCEL_BOTH
        );

        JsonArray a = o.get("unitTypes").asArray();

        for (JsonValue v : a.values()) {
            JsonObject uto = v.asObject();
            utt.unitTypes.add(UnitType.createStub(uto));
        }
        for (JsonValue v : a.values()) {
            JsonObject uto = v.asObject();
            utt.getUnitType(uto.getString("name", null)).updateFromJSON(uto, utt);
        }
        return utt;
    }
    */