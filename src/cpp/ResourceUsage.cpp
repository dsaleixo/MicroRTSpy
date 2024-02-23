#include "ResourceUsage.h"


void ResourceUsage::merge(ResourceUsage& other) {
    for (auto pos : other.positionsUsed) {
        this->positionsUsed.push_back(pos);
    }
    
    for (int i = 0; i < 2; i++) {
        resourcesUsed[i] += other.resourcesUsed[i];
    }
}

ResourceUsage::ResourceUsage() {

}

bool ResourceUsage::consistentWith(ResourceUsage &anotherUsage, GameState* gs) {

 
    for (int pos : anotherUsage.positionsUsed) {
        if (std::find(this->positionsUsed.begin(), this->positionsUsed.end(), pos) != this->positionsUsed.end()) {
            return false;
        }
    }
   
    for (int i = 0; i < 2; i++) { // conferir
        if (anotherUsage.resourcesUsed[i] == 0) continue;
        if (resourcesUsed[i] + anotherUsage.resourcesUsed[i] > 0
            && // this extra condition (which should not be needed), is because
            // if an AI has a bug and allows execution of actions that
            // brings resources below 0, this code would fail.
            resourcesUsed[i] + anotherUsage.resourcesUsed[i] > gs->getPlayer(i).getResources()) {
            return false;
        }
    }
   
    return true;
}


vector<int> ResourceUsage::getPositionsUsed() {
	return this->positionsUsed;
}

string ResourceUsage::toString() {
    return "não feito";
}