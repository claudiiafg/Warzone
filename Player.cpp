#include "Player.h"

using namespace std;

//Default constructor
Player::Player() : playerTerritories(), playerHand(nullptr), playerOrders(nullptr) {
}

//Parametrized constructor
Player::Player(vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders) : playerTerritories(playerTerritories), playerHand(playerHand), playerOrders(playerOrders) {
}

//Copy constructor
Player::Player(const Player &otherPlayer) {
    for (int i = 0; i < (int)otherPlayer.playerTerritories.size(); i++) {
        playerTerritories.at(i) = *new Territory * (otherPlayer.playerTerritories.at(i));
    }

    playerHand = *new Hand * (otherPlayer.playerHand);
    playerOrders = *new OrderList * (otherPlayer.playerOrders);
  }

//= operator overload
Player& Player::operator= (const Player& otherPlayer) { //Delete any values already present and assign new ones
    for (int i = 0; i < (int)otherPlayer.playerTerritories.size(); i++) {
        if (playerTerritories.at(i) != NULL) {
            delete playerTerritories.at(i);
        }
        playerTerritories.at(i) = *new Territory*(otherPlayer.playerTerritories.at(i));
    }

    if (playerHand != NULL) {
        delete playerHand;
    }
    playerHand = *new Hand*(otherPlayer.playerHand);

    if (playerOrders != NULL) {
        delete playerOrders;
    }
    playerOrders= *new OrderList*(otherPlayer.playerOrders);

    return *this;
}

//Destructor
Player::~Player() {
    for (int i = 0; i < (int)playerTerritories.size(); i++) {
        delete playerTerritories.at(i);
    }
    delete playerHand;
    playerHand = nullptr;
    delete playerOrders;
    playerOrders = nullptr;
}

//Required methods
vector<Territory*> Player::toDefend() {
//    vector<Territory*> toDefend{new Territory("terr1", "cont1"), new Territory("terr2", "cont2"), new Territory("terr3", "cont3")}; //Create arbitrary list for now
    //vector<Territory*> toDefend;
    return playerTerritories;
}

vector<Territory*> Player::toAttack() {
//    vector<Territory*> toAttack{new Territory("terr4", "cont4"), new Territory("terr5", "cont5"), new Territory("terr6", "cont6")}; //Create arbitrary list for now
    //vector<Territory*> toAttack;
    return playerTerritories;
}

void Player::issueOrder() {
    Order *newOrder = new Order();
    playerOrders->addOrder(newOrder);
    delete newOrder;
}

//Stream operator overload
ostream& operator<<(ostream &out, const Player &p) {
    out << "\nTerritories: ";

    for (int i = 0; i < (int)p.playerTerritories.size(); i++) {
        out << p.playerTerritories.at(i) << ' ';
    }

    out << "\nOrders: " << p.playerOrders
    << "\nHand: " << p.playerHand << "\n";

    return out;
}
