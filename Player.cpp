#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

//Default constructor
Player::Player() : name(rand()%10), armies(0), reinforcements(0), phase(1), cardFlag(false), allies(), playerTerritories(), playerHand(nullptr), playerOrders(nullptr) {
}

//Parametrized constructor
Player::Player(int name, int armies, vector<Territory*> playerTerritories, Hand* playerHand, OrderList* playerOrders, vector<Player*> allies) :
        name(name), armies(armies), playerTerritories(playerTerritories), playerHand(playerHand), playerOrders(playerOrders), reinforcements(0), phase(1), cardFlag(false), allies(allies) {
}

//Copy constructor
Player::Player(const Player &otherPlayer) {
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

void Player::setCardFlag(bool flag) {
    this->cardFlag = false;
}

void Player::addAlly(Player* player) {
    this->allies.push_back(player);
}

bool Player::checkForAllies(int playerName) {
    for (auto& i : allies) {
        if (i->name == playerName) {
            return true;
        }
    }
    return false;
}

vector<Territory*> Player::adjacentEnemies(string terrID, Map* map) {
    vector<Territory*> adjacentEnemies;

    for (auto& terr : getMyTerritories()) {
        for (auto& adj : terr->getAdjacentNodes()) {
            if(map->getTerritoryById(adj)->getOwnerID() != 99) {
                for (auto& within : getMyTerritories()) {
                    if (within->id != adj) {
                        Territory* toAdd = map->getTerritoryById(adj);
                        adjacentEnemies.push_back(toAdd);
                    }
                }
            }
        }
    }
    return adjacentEnemies;
}


vector<Territory*> Player::toDefend(Map* map) {
    defPriority.clear();
    vector<Territory*> defend;
    int counter = 0;

    for (auto territory : playerTerritories) {
        defPriority.push_back(0);
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

vector<string> Player::toAttack(Map* map) {
    atkPriority.clear();
    vector<string> attack;
    int counter = 0;

    for (auto territory : playerTerritories) {
        atkPriority.push_back(0);
        vector<Territory*> adjacentEnemy = adjacentEnemies(territory->id, map);
        for (auto enemies : adjacentEnemy) {
            //Priority point distribution (more points = higher priority)

            //If easy to defend once taken, higher priority
            vector<string> adjacentNodes = enemies->getAdjacentNodes();
            if (adjacentNodes.size() < 3) atkPriority.at(counter) += 2;

            //If player territory has much more armies than enemy, higher priority
            int armyDiff = territory->getArmies() - enemies->getArmies();
            atkPriority.at(counter) += (armyDiff/2);

            string toPush = territory->id + " " + enemies->id;
            //Store attacking territory and territory to be attacked
            if (!(std::find(attack.begin(), attack.end(), toPush) != attack.end())) {
                attack.push_back(toPush);
            }
        }
        //Increment counter to store twin priority array at same index
        counter++;
    }
    return attack;
}

int Player::issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend, Player* nextPlayer) {
//    cout << endl << "***Player " << this->name << "***" << endl;

    if (reinforcements > 0 && !toDefend.empty()) {
//        cout << "Reinforcements remaining: " << reinforcements << "\n";
        auto it = toDefend.begin();
        if(deployCounter == toDefend.size()) --deployCounter;
        advance(it, deployCounter);
        Territory* currTerr = *it;
        playerOrders->addOrder(new Deploy(this, currTerr, 1));

        reinforcements--;
        deployCounter++;
        return 0;

    } else {
        //Highest priority defense
        auto defit = max_element(begin(defPriority), end(defPriority)); //Returns pointer to highest priority element
        //Highest priority attack
        auto atkit = max_element(begin(atkPriority), end(atkPriority)); //Returns pointer to highest priority element
        int atkIndex = distance(atkPriority.begin(), atkit); //Returns  index of highest priority element

        Territory* ownedTerrAtk = {};
        Territory* enemyTerrAtk = {};

        if(!toAttack.empty()) {
            //Returns string with highest priority territory attacking and to be attacked
            string atkTerrStr = toAttack.at(atkIndex);

            //Split priority string into relevant territories
            stringstream split(atkTerrStr);
            string intermediate;
            getline(split, intermediate, ' ');
            ownedTerrAtk = map->getTerritoryById(intermediate);
            getline(split, intermediate, ' ');
            enemyTerrAtk = map->getTerritoryById(intermediate);

            //Bomb setup
            vector<string> adjacents = enemyTerrAtk->getAdjacentNodes();
            Territory* adjTerr;

            for (auto adj : adjacents) {
                adjTerr = map->getTerritoryById(adj);
                if (adjTerr->getOwnerID() == name) break;
            }

            //STRATEGY
            //Airlift - If hand contains card, use on highest priority defense
            if (playerHand->getAirCount()!=0) {
                playerHand->play("airlift");
                playerOrders->addOrder(new Airlift(this, ownedTerrAtk, enemyTerrAtk, (ownedTerrAtk->getArmies()) - 1));
                return 0;
            }

            //Blockade - If hand contains card, use on highest priority defense
            if (playerHand->getBlockCount() != 0) {
                playerHand->play("blockade");
                playerOrders->addOrder(new Blockade(this, ownedTerrAtk));
                return 0;
            }

            //Bomb - If hand contains card, use on highest priority attack
            if (playerHand->getBombCount() != 0) {
                playerHand->play("bomb");
                playerOrders->addOrder(new Bomb(this, adjTerr, enemyTerrAtk));
                return 0;
            }

            //Negotiate - If hand contains card, use on next player
            if (playerHand->getDiplomCount() != 0) {
                playerHand->play("diplomacy");
                playerOrders->addOrder(new Negotiate(this, nextPlayer));
                return 0;
            }

            list<Order*> orders = playerOrders->orders;

            //If there are no more territories to attack or defend
            if (toDefend.empty() && toAttack.empty() || orders.size() > 10) {
                //cout << "toAttack and toDefend lists completed, done issuing!" << endl;
                phase++;
                this->Notify();
                return 1;
            }

        //Advance - Defend - Any territory with enough armies should relocate armies to territories in need
        } else if(*defit > * atkit && !(toDefend.empty() && toAttack.empty())) {
//            if(*defit > * atkit) {
                for (auto territory : playerTerritories) {
                    if (territory->getArmies() > 0) {
                        for (auto defending : toDefend) {
                            string terrId = territory->id;
                            if (defending->isAdjacentNode(terrId)) {
                                //cout << "Advance order issued : " << territory->name << " to " << defending->name << " with " << territory->getArmies() - 1 << " units";
                                playerOrders->addOrder(new Advance(this, territory, defending, territory->getArmies() - 1));
                                return 0;
                            }
                        }
                        return 0;

                    }
                }
            //Advance - Attack - Issue attack order on highest priority border
            } else {
                //cout << "Advance order issued : " << ownedTerrAtk->name << " to " << enemyTerrAtk->name << " with " << territory->getArmies() - 1 << " units";
                if (ownedTerrAtk->getArmies() > 1) {
                    playerOrders->addOrder(
                            new Advance(this, ownedTerrAtk, enemyTerrAtk, ownedTerrAtk->getArmies() - 1));
                    return 0;
                }
            }
//        }


        return 1;
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

bool Player::hasTerritory(string terrId) {
    for(auto terr: playerTerritories) {
        if(terr->name == terrId) return true;
    }
    return false;
}

