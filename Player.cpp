#include "Player.h"

//**REQUIRED METHODS**

//Default constructor
Player::Player() : name(rand()%10), armies(0), reinforcements(0), phase(1), cardFlag(false),  playerTerritories(), playerHand(nullptr), playerOrders(nullptr), strategy() {
}

//Parametrized constructor
Player::Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, PlayerStrategy* strat) :
        name(name), armies(armies), playerTerritories(playerTerritories), playerHand(playerHand), playerOrders(playerOrders), reinforcements(0), phase(1), cardFlag(false), strategy(strat) {
}

//Copy constructor
Player::Player(const Player &otherPlayer) :
        name(otherPlayer.name), armies(otherPlayer.armies), playerHand(*new Hand *(otherPlayer.playerHand)), playerOrders(*new OrderList* (otherPlayer.playerOrders)), 
        reinforcements(otherPlayer.reinforcements), phase(otherPlayer.phase), cardFlag(otherPlayer.cardFlag), strategy(otherPlayer.strategy) {
    for (int i = 0; i < (int)otherPlayer.playerTerritories.size(); i++) {
        playerTerritories.at(i) = *new Territory * (otherPlayer.playerTerritories.at(i));
    }
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

//Stream operator overload
ostream& operator<<(ostream& out, const Player& p) {
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


//**MUTATORS**

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

void Player::setCardFlag(bool flag) {
    this->cardFlag = false;
}

void Player::setStrategy(PlayerStrategy* newStrategy) {
    this->strategy = newStrategy;
}


//**STRATEGY METHODS**

//Return list of territories to defend
vector<Territory*> Player::toDefend() {
    return this->strategy->toDefend(this);
}

//Return list of territories to attack
vector<Territory*> Player::toAttack() {
    return this->strategy->toAttack(this);
}

//Create order and add to orderList
void Player::issueOrder() {
    return this->strategy->issueOrder(this);
}


//**ORDER METHODS**

void Player::deploy(Territory* terr, int units) {
    if (units > reinforcements) units = reinforcements;

    playerOrders->addOrder(new Deploy(this, terr, units)); //Add order to orderList

    reinforcements -= units; //Update reinforcements pool
}


//**HELPER METHODS**

//Returns list of territories owned by the enemy and adjacent to the player
vector<Territory*> Player::adjacentEnemies(Map* map) {
    vector<Territory*> adjacentEnemies;

    for (auto& terr : getMyTerritories()) {
        for (auto& adj : terr->getAdjacentNodes()) {
            if(map->getTerritoryById(adj)->getOwnerID() != 99) {
                for (auto& within : getMyTerritories()) {
                    if (within->id != adj) {
                        Territory* toAdd = map->getTerritoryById(adj);
                        if (find(adjacentEnemies.begin(), adjacentEnemies.end(), toAdd) == adjacentEnemies.end()) adjacentEnemies.push_back(toAdd); //Check if list already contains territory
                    }
                }
            }
        }
    }
    return adjacentEnemies;
}

//Check if player owns given territory
bool Player::hasTerritory(string terrId) {
    for(auto terr: playerTerritories) {
        if(terr->name == terrId) return true;
    }
    return false;
}


/**
 * public:
        Players();
        void add(Player *p);
        Player getPlayerByID(string id);
        Player removeByID(string ID);
    private:
        vector<Player*> playerHolder;
 */

    Players::Players(){

    }

    void Players::add(Player *p){
        playerHolder.push_back(p);
    }

    Player* Players::getPlayerByID(int id){
        for(int i = 0; i < playerHolder.size(); i++){
            if(playerHolder.at(i)->name == id)
                return playerHolder.at(i);
        }
    }