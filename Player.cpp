#include "Player.h"
#include "GameObservers.h"


using namespace std;

//Default constructor
Player::Player() : name(rand()%10), armies(0), reinforcements(0), phase(1), cardFlag(false), allies(), playerTerritories(), playerHand(nullptr), playerOrders(nullptr), Observable() {
}

//Parametrized constructor
Player::Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, vector<Player*> allies) :
        name(name), armies(armies), playerTerritories(playerTerritories), playerHand(playerHand), playerOrders(playerOrders), reinforcements(0), phase(1), cardFlag(false), allies(allies), Observable() {
}

//Copy constructor
Player::Player(const Player &otherPlayer): Observable() {
    for (int i = 0; i < (int)otherPlayer.playerTerritories.size(); i++) {
        playerTerritories.at(i) = *new Territory * (otherPlayer.playerTerritories.at(i));
    }

    for (int i = 0; i < (int)otherPlayer.allies.size(); i++) {
        allies.at(i) = *new Player * (otherPlayer.allies.at(i));
    }

    playerHand = *new Hand * (otherPlayer.playerHand);
    playerOrders = *new OrderList * (otherPlayer.playerOrders);
    armies = 0;
    reinforcements = 0;
    phase = 1;
    name = otherPlayer.name + 1;
    cardFlag = otherPlayer.cardFlag;

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

vector<Territory*> Player::adjacentEnemies(string terrID, Map* map) {
    vector<Territory*> adjacentEnemies;

    for (auto& terr : getMyTerritories()) {
        for (auto& adj : terr->getAdjacentNodes()) {
            for (auto& within : getMyTerritories()) {
                if (within->id != adj) {
                    Territory* toAdd = map->getTerritoryById(adj);
                    adjacentEnemies.push_back(toAdd);
                }
            }
        }
    }
    return adjacentEnemies;
}


vector<Territory*> Player::toDefend(vector<int> &defPriority, Map* map) {
    vector<Territory*> defend;
    int counter = 0;

    for (auto territory : playerTerritories) {
        //Territories that don't border allies get no priority
        vector<Territory*> adjacentEnemy = adjacentEnemies(territory->id, map);
        if (adjacentEnemy.empty()) continue;

        //Priority point distribution (more points = higher priority)

        //Territories with fewer armies get higher priority
        if (territory->getArmies() < 1) defPriority.at(counter) += 3;
        else if (territory->getArmies() < 2) defPriority.at(counter) += 2;
        else if (territory->getArmies() < 3) defPriority.at(counter) += 1;

        defend.push_back(territory);
        counter++;
    }

    return defend;
}

vector<string> Player::toAttack(vector<int>& atkPriority, Map* map) {
    vector<string> attack;
    int counter = 0;

    for (auto territory : playerTerritories) {
        vector<Territory*> adjacentEnemy = adjacentEnemies(territory->id, map);


        for (auto enemies : adjacentEnemy) {

            //If easy to defend once taken, higher priority
            vector<string> adjacentNodes = enemies->getAdjacentNodes();
            if (adjacentNodes.size() < 3) atkPriority.at(counter) += 2; 

            //If player territory has much more armies than enemy, higher priority
            int armyDiff = territory->getArmies() - enemies->getArmies();
            atkPriority.at(counter) += (armyDiff/2);

            attack.push_back(territory->name + " " + enemies->name);
            counter;
        }
        
        
    
    }
    return attack;
}

void Player::issueOrder(Map* map, vector<Territory*> toAttack, vector<string> toDefend) {
    /*Deploy* deploy1 = new Deploy(1, "Alberta", 1, 5);
    Blockade* blockade1 = new Blockade(this->name, "Alberta", 1, 5);
    playerOrders->addOrder(blockade1);
    playerOrders->addOrder(deploy1);*/

    vector <Territory*> deployTo = toDefend(map);

    if (reinforcements > 0) {
        auto it = deployTo.begin();
        advance(it, deployCounter);
        Territory* currTerr = *it;

        playerOrders->addOrder(new Deploy(this, currTerr, 1));
        reinforcements--;
    }

    else {
        //Airlift - If hand contains card, use on highest priority defense
//        if (playerHand.)

        //Blockade - If hand contains card, use on highest priority defense

        //Bomb - If hand contains card, use on highest priority attack

        //Negotiate - If hand contains card, use on next player

        //Advance - Use advance to alternate atk or def by toAttack and toDefend priority
        if ()
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
