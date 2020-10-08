#include <vector>
#include "Map.h"
//#include "Orders.h"
//#include "Cards.h"
#include "Player.h"
#include "Map.cpp"

using namespace std;

Player::Player() {}

Player::Player(Player const &otherPlayer) {}

Player::~Player() {}

vector<Territory> Player::toDefend() {
    vector<Territory> toDefend{new Territory("terr1", "cont1"), new Territory("terr2", "cont2"), new Territory("terr3", "cont3")};
    return toDefend;
}

vector<Territory> Player::toAttack() {
    return vector<Territory> = {new Territory("terr4", "cont4"), new Territory("terr5", "cont5"), new Territory("terr6", "cont6")};
}

void Player::issueOrder() {
    Order newOrder = new Order();
    myOrders.add(newOrder);
}
