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


vector<Territory*> Player::toDefend(Map* map) {
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

            //Store attacking territory and territory to be attacked
            attack.push_back(territory->id + " " + enemies->id);

            //Increment counter to store twin priority array at same index
            counter;
        }
    }
    return attack;
}

int Player::issueOrder(Map* map, vector<string> toAttack, vector<Territory*> toDefend) {
    cout << endl << "***Player " << this->name << "***" << endl;

    if (reinforcements > 0) {
        cout << "Reinforcements remaining: " << reinforcements << "\n";
        cout << "Deploying armies...\n";
        auto it = toDefend.begin();
        advance(it, deployCounter);
        Territory* currTerr = *it;

        playerOrders->addOrder(new Deploy(this, currTerr, 1));
        cout << "1 army deployed to " << currTerr->name << "\n";

        reinforcements--;
        deployCounter++;
        return 0;

    } else {
        cout << "Non-deploy orders:" << endl;
        //Highest priority defense
        vector<int>::iterator defit = max_element(begin(defPriority), end(defPriority)); //Returns pointer to highest priority element
        int defIndex = distance(defPriority.begin(), defit); //Returns  index of highest priority element
        Territory* defTerr = toDefend.at(defIndex); //Returns highest defence priority territory

        //Highest priority attack
        vector<int>::iterator atkit = max_element(begin(atkPriority), end(atkPriority)); //Returns pointer to highest priority element
        int atkIndex = distance(atkPriority.begin(), atkit); //Returns  index of highest priority element
        string atkTerrStr = toAttack.at(atkIndex); //Returns string with highest priority territory attacking and to be attacked

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
        //Airlift - If hand contains card, use on highest priority defense
        if (playerHand->getAirCount()!=0) {
            cout << "Player has airlift card, card will be played" << endl;
            playerHand->play("airlift");
            playerOrders->addOrder(new Airlift(this, ownedTerrAtk, enemyTerrAtk, (ownedTerrAtk->getArmies()) - 1));
            return 0;
        }

        //Blockade - If hand contains card, use on highest priority defense
        if (playerHand->getBlockCount() != 0) {
            cout << "Player has blockade card, card will be played" << endl;
            playerHand->play("blockade");
            playerOrders->addOrder(new Blockade(this, ownedTerrAtk));
            return 0;
        }

        //Bomb - If hand contains card, use on highest priority attack
        if (playerHand->getBombCount() != 0) {
            cout << "Player has bomb card, card will be played" << endl;
            playerHand->play("bomb");
            playerOrders->addOrder(new Bomb(this, adjTerr, enemyTerrAtk));
            return 0;
        }

        //Negotiate - If hand contains card, use on next player
        if (playerHand->getDiplomCount() != 0) {
            cout << "Player has negotiate card, card will be played" << endl;
            Player* otherP = this;
            otherP->name = this->name + 1;
            playerHand->play("diplomacy");
            playerOrders->addOrder(new Negotiate(this, otherP));
            return 0;
        }

        list<Order*> orders = playerOrders->orders;

        //Advance - Use advance to alternate atk or def by toAttack and toDefend priority
        for (auto territory : playerTerritories) {
            if (territory->getArmies() > 0) {
                //If there are no more territories to attack or defend
                if (toDefend.empty() && toAttack.empty() || orders.size() > 10) {
                    cout << "toAttack and toDefend lists completed, done issuing!" << endl;
                    phase++;
                    this->Notify();
                    return 1;
                }

                //If attack if empty or defense is higher priority
                else if (toDefend.empty() || *defit < *atkit) {
                    cout << "Defense is highest priority at priority " << *defit << ". Taking highest priority defense order..." << endl;
                    for (auto defending : toDefend) {
                        string terrId = territory->id;
                        if (defending->isAdjacentNode(terrId)) {
                            playerOrders->addOrder(new Advance(this, territory, defending, territory->getArmies() - 1));
                        }
                    }
                    return 0;
                }

                else {
                    cout << "Attack is highest priority at priority " << *atkit << ". Taking highest priority attack order..." << endl;
                    playerOrders->addOrder(new Advance(this, ownedTerrAtk, enemyTerrAtk, territory->getArmies() - 1));
                    return 0;
                }
            }
        }

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

