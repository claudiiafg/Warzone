#include "Player.h"
#include <vector>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

Player::Player() {}

Player::Player(Player const &otherPlayer) {
    myTerritories = otherPlayer.myTerritories;
    myHand = otherPlayer.myHand;
    myOrders = otherPlayer.myOrders;
}

Player::~Player() {

}

vector<Territory> Player::toDefend() {
    vector<Territory> toDefend{new Territory("terr1", "cont1"), new Territory("terr2", "cont2"), new Territory("terr3", "cont3")};
    return toDefend;
}

vector<Territory> Player::toAttack() {
    vector<Territory> toAttack{new Territory("terr4", "cont4"), new Territory("terr5", "cont5"), new Territory("terr6", "cont6")};
    return toAttack;
}

void Player::issueOrder() {
    Order newOrder = new Order();
    myOrders.add(newOrder);
}

ostream& operator<<(ostream &out, const Player &p) {
    out << "Territories: " << p.myTerritories()
        << "\nOrders: " << p.myOrders()
        << "\nHand: " << p.myHand() << "\n";
    return out;
}
