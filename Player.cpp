#include "Player.h"
#include "GameObservers.h"


using namespace std;

//Default constructor
Player::Player() : name(rand()%10), armies(0), reinforcements(0), phase(1), playerTerritories(), playerHand(nullptr), playerOrders(nullptr), Observable() {
}

//Parametrized constructor
Player::Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders) :
        name(name), armies(armies), playerTerritories(playerTerritories), playerHand(playerHand), playerOrders(playerOrders), reinforcements(0), phase(1), Observable() {
}

//Copy constructor
Player::Player(const Player &otherPlayer): Observable() {
    for (int i = 0; i < (int)otherPlayer.playerTerritories.size(); i++) {
        playerTerritories.at(i) = *new Territory * (otherPlayer.playerTerritories.at(i));
    }

    playerHand = *new Hand * (otherPlayer.playerHand);
    playerOrders = *new OrderList * (otherPlayer.playerOrders);
    armies = 0;
    reinforcements = 0;
    phase = 1;
    name = 0;
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

void Player::setTerritories(vector<Territory*> playerTerritories) {
    this->playerTerritories = playerTerritories;
}

void Player::setHand(Hand* playerHand) {
    this->playerHand = playerHand;
}

void Player::setOrders(OrderList* playerOrders) {
    this->playerOrders = playerOrders;
}

void Player::setReinforcements(int reinforcements) {
    this->reinforcements = reinforcements;
}

void Player::setPhase(int phase) {
    this->phase = phase;
}

vector<Territory*> Player::adjacentEnemies(string terrID) {
    vector<Territory*> adjacentEnemies;

    for (auto& terr : getMyTerritories()) {
        for (auto& adj : terr->getAdjacentNodes()) {
            for (auto& within : getMyTerritories()) {
                if (within->id != adj) {
                    //Territory* toAdd = getTerritoryById(adj);
                }
            }
        }
    }
    return adjacentEnemies;
}

bool compare(const Territory* &x, const Territory* &y) {
    if (x->priority > y->priority)
        return (true);
    else
        return(false);
}

list<Territory*> Player::toDefend(Map* map) {
    list<Territory*> defend;

    for (auto territory : playerTerritories) {
        //Territories that don't border allies get no priority
        //if (!(hasEnemyAdjacent(territory->id))) continue; ;

        //Priority point distribution (more points = higher priority)

        //Territories with fewer armies get higher priority
        if (territory->getArmies() < 1) territory->priority+=3;
        else if (territory->getArmies() < 2) territory->priority+=2;
        else if (territory->getArmies() < 3) territory->priority++;

        defend.push_back(territory);
    }

    //Sort territories from highest to lowest priority
    //defend.sort(compare);

    return defend;
}

list<Territory*> Player::toAttack(Map* map) {
    list<Territory*> attack;

    return attack;
}

void Player::issueOrder(Map* map) {
    /*Deploy* deploy1 = new Deploy(1, "Alberta", 1, 5);
    Blockade* blockade1 = new Blockade(this->name, "Alberta", 1, 5);
    playerOrders->addOrder(blockade1);
    playerOrders->addOrder(deploy1);*/

    list <Territory*> deployTo = toDefend(map);

    if (reinforcements > 0) {
        auto it = deployTo.begin();
        advance(it, deployCounter);
        Territory* currTerr = *it;

        playerOrders->addOrder(new Deploy(name, currTerr->name, name, 1));
        reinforcements--;
    }

    else {
        //Airlift - If hand contains card, use on highest priority defense
        if (playerHand.)

        //Blockade - If hand contains card, use on highest priority defense

        //Bomb - If hand contains card, use on highest priority attack

        //Negotiate - If hand contains card, use on next player

        //Advance - for each owned territory with low defense priority and more than 2 armies, use advance to alternate atk or def
    }

}

//Stream operator overload
ostream& operator<<(ostream &out, const Player &p) {
    out << "Player id: " << p.name << endl;
    out << "Armies in reinforcement pool: " << p.armies << endl;
    out << "Territories: ";
    for (int i = 0; i < p.playerTerritories.size(); i++) {
        out << p.playerTerritories.at(i)->name << ' ';
    }
    out << endl;
    out << "Orders: ";
    list <Order*> ::iterator it;
    for (it = p.playerOrders->orders.begin(); it != p.playerOrders->orders.end(); ++it) {
        out << (*it) << " || ";
    }
    out << endl;
    out << "Hand: " << *p.playerHand << endl;
    return out;
}
