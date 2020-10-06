using namespace std;

class Player {
	#include <vector>
	#include "Map.h"
	#include "Orders.h"
	#include "Cards.h"
	#include "Player.h"

	Player() {
		
	}

	Player(Player otherPlayer) {

	}

	vector<Territory> toDefend() {
		vector<Territory> toDefend{new Territory(), new Territory(), new Territory()};
		return toDefend;
	}

	vector<Territory> toAttack() {
		return vector<Territory> = {new Territory(), new Territory(), new Territory() };
	}

	void issueOrder(Order newOrder) {
		myOrders.add(newOrder); 
