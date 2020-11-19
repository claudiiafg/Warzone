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
            //Priority point distribution (more points = higher priority)

            //If easy to defend once taken, higher priority
            vector<string> adjacentNodes = enemies->getAdjacentNodes();
            if (adjacentNodes.size() < 3) atkPriority.at(counter) += 2; 

            //If player territory has much more armies than enemy, higher priority
            int armyDiff = territory->getArmies() - enemies->getArmies();
            atkPriority.at(counter) += (armyDiff/2);

            //Store attacking territory and territory to be attacked
            attack.push_back(territory->id + " " + enemies->id); 

            //Increment counter to store twin priority array at same index
            counter;
        }
        
        
    
    }
    return attack;
}

void Player::issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, vector<int> defPriorities, vector<int> atkPriorities) {
    /*Deploy* deploy1 = new Deploy(1, "Alberta", 1, 5);
    Blockade* blockade1 = new Blockade(this->name, "Alberta", 1, 5);
    playerOrders->addOrder(blockade1);
    playerOrders->addOrder(deploy1);*/

    if (reinforcements > 0) {
        auto it = toDefend.begin();
        advance(it, deployCounter);
        Territory* currTerr = *it;

        playerOrders->addOrder(new Deploy(this, currTerr, 1));
        reinforcements--;
    }

    else {
        //Highest priority defense
        vector<int>::iterator defit = max_element(begin(defPriorities), end(defPriorities)); //Returns pointer to highest priority element
        int atkIndex = distance(defPriorities.begin(), defit); //Returns  index of highest priority element
        Territory* defTerr = toDefend.at(atkIndex); //Returns highest defence priority territory
        
        //Highest priority attack
        vector<int>::iterator atkit = max_element(begin(atkPriorities), end(atkPriorities)); //Returns pointer to highest priority element
        int defIndex = distance(defPriorities.begin(), atkit); //Returns  index of highest priority element
        string atkTerrStr = toAttack.at(defIndex); //Returns string with highest priority territory attacking and to be attacked

        //Split priority string into relevant territories
        stringstream split(atkTerrStr);
        string intermediate;
        getline(split, intermediate, ' ');
        Territory* ownedTerrAtk = map->getTerritoryById(intermediate);
        getline(split, intermediate, ' ');
        Territory* enemyTerrAtk = map->getTerritoryById(intermediate);


        //Bomb setup
        vector<string> adjacents = enemyTerrAtk->getAdjacentNodes();
        Territory* adjTerr;

        for (auto adj : adjacents) {
            adjTerr = map->getTerritoryById(adj);
            if (adjTerr->getOwnerID() == name) break;
        }

        //STRATEGY 
        vector<Card*> hand = playerHand->getHand();
        if (!(hand.empty())) {
            for (auto card : playerHand->getHand()) {
                string cardType = card->getType();

                //Airlift - If hand contains card, use on highest priority defense
                if (cardType.compare("airlift") == 0) {
                    playerOrders->addOrder(new Airlift(this, ownedTerrAtk, enemyTerrAtk, (ownedTerrAtk->getArmies()) - 1));
                    break;
                }

                //Blockade - If hand contains card, use on highest priority defense
                if (cardType.compare("blockade") == 0) {
                    playerOrders->addOrder(new Blockade(this, ownedTerrAtk));
                    break;
                }

                //Bomb - If hand contains card, use on highest priority attack
                if (cardType.compare("bomb") == 0) {
                    playerOrders->addOrder(new Bomb(this, adjTerr, enemyTerrAtk));
                    break;
                }

                //Negotiate - If hand contains card, use on next player
                if (cardType.compare("negotiate") == 0) {
                    playerOrders->addOrder(new Negotiate(name, name++));
                    break;
                }
            }
        }
        else {
            //Advance - Use advance to alternate atk or def by toAttack and toDefend priority
            for (auto territory : playerTerritories) {
                if (territory->getArmies() > 2) {

                    //If there are no more territories to attack or defend
                    if (toDefend.empty() && toAttack.empty()) {
                        phase++;
                        this->Notify();
                    }

                    //If attack if empty or defense is higher priority
                    else if (toDefend.empty() || *defit < *atkit) {
                        for (auto defending : toDefend) {
                            string terrId = territory->id;
                            if (defending->isAdjacentNode(terrId)) {
                                playerOrders->addOrder(new Advance(this, territory, defending, territory->getArmies() - 1));
                            }
                        }
                    }

                    else {
                        playerOrders->addOrder(new Advance(this, ownedTerrAtk, enemyTerrAtk, territory->getArmies() - 1));
                    }

                    
                }
            }
        }
            
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
