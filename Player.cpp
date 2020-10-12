#include "Player.h"
#include <vector>
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

Player::Player() : playerTerritories(), playerHand(nullptr), playerOrders(nullptr) {
}

Player::Player(const Player &otherPlayer) {
    for (int i = 0; i < otherPlayer.playerTerritories.size(); i++) {
        playerTerritories.at(i) = new Territory * (otherPlayer.playerTerritories.at(i));
    }

    playerHand = new Hand * (otherPlayer.playerHand);
    playerOrders = new OrdersList * (otherPlayer.playerOrders);
  }

Player::~Player() {
    for (int i = 0; i < otherPlayer.playerTerritories.size(); i++) {
        delete playerTerritories.at(i);
    }
    delete playerHand;
    delete playerOrders;
}

Player& Player::operator= (const Player& otherPlayer) {
    for (int i = 0; i < otherPlayer.playerTerritories.size(); i++) {
        if (playerTerritories.at(i) != NULL) {
            delete playerTerritories.at(i);
        }
        playerTerritories.at(i) = new Territory*(otherPlayer.playerTerritories.at(i));
    }
 
    if (playerHand != NULL) {
        delete playerHand;
    }
    playerHand = new Hand*(otherPlayer.playerHand);

    if (playerOrders != NULL) {
        delete playerOrders;
    }
    playerOrders= new OrdersList*(otherPlayer.playerOrders);
}

vector<Territory*> Player::toDefend() {
    vector<Territory*> toDefend{new Territory("terr1", "cont1"), new Territory("terr2", "cont2"), new Territory("terr3", "cont3")};
    return toDefend;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> toAttack{new Territory("terr4", "cont4"), new Territory("terr5", "cont5"), new Territory("terr6", "cont6")};
    return toAttack;
}

void Player::issueOrder() {
    Order newOrder = new Order();
    playerOrders.add(newOrder);
}



ostream& operator<<(ostream &out, const Player &p) {
    out << "\nTerritories: ";
    
    for (int i = 0; i < p.playerTerritories.size(); i++) {
        out << p.playerTerritories.at(i) << ' ';
    }

    out << "\nOrders: " << p.playerOrders()
    << "\nHand: " << p.playerHand() << "\n";

    return out;
}
