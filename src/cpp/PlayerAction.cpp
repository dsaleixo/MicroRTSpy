#include "PlayerAction.h"

vector<pair<Unit*, UnitAction>>& PlayerAction::getActions() {
	return this->actions;
}

void PlayerAction::setResourceUsage(ResourceUsage& a_r) {
	this->r = new ResourceUsage(a_r);
}


bool PlayerAction::consistentWith(ResourceUsage &u, GameState* gs) {
	return this->r->consistentWith(u, gs);
}

void PlayerAction::fillWithNones(GameState* s, int pID, int duration) {
	PhysicalGameState *pgs = s->getPhysicalGameState();
	for (Unit* u : pgs->getUnits()) {
		if (u->getPlayer() == pID) {
			if (s->unitActions.find(u) == s->unitActions.end()) {
				bool found = false;
				for (auto& pa : this->actions) {
					if (pa.first == u) {
						found = true;
						break;
					}
				}
				if (!found) {
					actions.push_back(make_pair<>(u, UnitAction(UnitAction::TYPE_NONE, duration)));
				}
			}
		}
	}
}

ResourceUsage* PlayerAction::getResourceUsage() {
	return this->r;
}

void PlayerAction::addUnitAction(Unit* u, UnitAction a) {
	this->actions.push_back(make_pair<>(u, a));
}


bool PlayerAction::integrityCheck() {
	int player = -1;
	
	for (pair<Unit*, UnitAction> uaa : actions) {
		Unit *u = uaa.first;
		if (player == -1) {
			player = u->getPlayer();
		}
		else {
			if (player != u->getPlayer()) {
				cout << "integrityCheck: units from more than one player!" << endl;
				return false;
			}
		}
	}
	return true;
}

PlayerAction::PlayerAction(){
	this->r = new ResourceUsage();
}

