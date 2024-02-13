#include "PlayerAction.h"


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

}

