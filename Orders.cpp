
#include "Orders.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
///   ORDERS					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Default constructor
Order::Order() {
    priority = NULL;
}

//Copy constructor
Order::Order(const Order& b) {
    priority = b.priority;
}

//Assignment operator
Order& Order::operator = (const Order& d2) {
    return *this;
}

//Get priority
int Order::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Order::operator <(const Order& playerObj) const {
    return priority < playerObj.priority;
}

//Validates an order
bool Order::validate() {
    return false;
}

//Executes an order
void Order::execute() {
}


ostream &Order::operator<<(ostream &out) const {
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   DEPLOY					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Deploy::Deploy(Player* pl, Territory* terr, int theUnits) {
    countryOwner = terr->getOwnerID();
    units = theUnits;
    playerID = pl->name;
    player = pl;
    territory = terr;

}

//Copy constructor
Deploy::Deploy(const Deploy& d2) {
    countryOwner = d2.countryOwner;
    units = d2.units;
    playerID = d2.playerID;
    player = d2.player;
    territory = d2.territory;
}

//Assignment operator
Deploy& Deploy::operator = (const Deploy& d2) {
    countryOwner = d2.countryOwner;
    units = d2.units;
    playerID = d2.playerID;
    player = d2.player;
    territory = d2.territory;
    return *this;
}

//Get priority
int Deploy::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Deploy::operator <(const Deploy& playerObj) const {
    return priority < playerObj.priority;
}

//Validates a deploy order
bool Deploy::validate() {
    bool playerOwnsCountry = false;
    bool validUnits = false;

    if (playerID == countryOwner) {
        playerOwnsCountry = true;
    }
    if (units >= 1) {
        validUnits = true;
    }
    return (playerOwnsCountry && validUnits);
}

//Executes a deploy order
void Deploy::execute() {

    if (validate()) {
        int tempArmies = territory->getArmies();
        tempArmies += units;
        territory->setArmiesNumber(tempArmies);

        cout << "Player " << playerID << " has deployed " << units << " units to " << territory->name << ".\n";
    }

}

ostream& operator<<(std::ostream& out, const Deploy& b)
{
    out << "A Deploy order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryOwner: "
        << b.countryOwner << "\n\tunits: " << b.units << "}\n";
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   ADVANCE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Advance::Advance(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith) {
    countryOwner = terr->getOwnerID();
    units = unitsAttackingWith;
    playerID = pl->name;
    player = pl;
    territory = terr;
    attTerritory = attTerr;
    attCountryOwner = attTerr->getOwnerID();
}

//Copy constructor
Advance::Advance(const Advance& b) {
    playerID = b.playerID;
    units = b.units;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
}

//Assignment operator
Advance& Advance::operator = (const Advance& b) {
    playerID = b.playerID;
    units = b.units;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
    return *this;
}

//Get priority
int Advance::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Advance::operator <(const Advance& playerObj) const {
    return priority < playerObj.priority;
}

//Validates an advance order
bool Advance::validate() {
    bool playerOwnsCountry = false;
    bool validUnitsToMoveOrAtt = false;
    bool validMove = false;
    bool validOpponent = false;

    //check if the player owns the country
    if (playerID == countryOwner) {
        playerOwnsCountry = true;
    }
    //check if player has more 1 or more units to attack with and if they are advancing with valid units
    if (units >= 1 && territory->getArmies() >= units) {
        validUnitsToMoveOrAtt = true;
    }
    //needed: assure the 2 countries and ajdacent
    if (territory->isAdjacentNode(attTerritory->id)) {
        validMove = true;
    }
    //check if negotiating
    if (!(player->checkForAllies(attTerritory->getOwnerID()))) {
        validOpponent = true;
    }

    return (playerOwnsCountry && validUnitsToMoveOrAtt && validMove && validOpponent);
}

//Executes an advance order
void Advance::execute() {

    if (validate()) {

        //player move
        if (playerID == attCountryOwner) {

            int tempArmies = territory->getArmies();
            tempArmies -= units;
            territory->setArmiesNumber(tempArmies);
            int tempAttArmies = attTerritory->getArmies();
            tempAttArmies += units;
            attTerritory->setArmiesNumber(tempAttArmies);

            cout << "Player " << playerID << " moved " << units << " units to " << attTerritory->name << ".\n";
        }

        //player attack
        else {

            int tempArmies = territory->getArmies();
            tempArmies -= units;
            territory->setArmiesNumber(tempArmies);

            //dice rolling
            int att = units;
            int def = attTerritory->getArmies();
            srand(time(0));

            while (att > 0 && def > 0) {
                int result = 1 + (rand() % 10);
                if (result >= 6)
                    --att;

                result = 1 + (rand() % 10);
                if (result >= 7)
                    --def;
            }

            if (att > 0) {
                attTerritory->setArmiesNumber(att);
                attTerritory->setOwner(territory->getOwnerID());

                cout << "Player " << playerID << " attacked " << attTerritory->name << " owned by player " <<
                     attCountryOwner << " with " << units << " units and conquered the territory with " << attTerritory->getArmies()
                     << " attackers remaining on the new territory.\n";

                Deck* deck = new Deck();
                player->getMyHand()->add(deck->draw());
                player->setCardFlag(true);
            }
            if (def > 0) {
                attTerritory->setArmiesNumber(def);

                cout << "Player " << playerID << " attacked " << attTerritory->name << " owned by player " <<
                     attCountryOwner << " with " << units << " units and failed to conquer the territory with " <<
                     attTerritory->getArmies() << " defenders remaining.\n";
            }

        }
    }

}

ostream& operator<<(std::ostream& out, const Advance& b)
{
    out << "An Advance order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryOwner: "
        << b.countryOwner << "\n\tunits: " << b.units << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: "
        << b.attCountryOwner << "}\n";
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   BOMB					   	                                          ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Bomb::Bomb(Player* pl, Territory* terr, Territory* attTerr) {
    countryOwner = terr->getOwnerID();
    playerID = pl->name;
    player = pl;
    territory = terr;
    attTerritory = attTerr;
    attCountryOwner = attTerr->getOwnerID();
}

//Copy constructor
Bomb::Bomb(const Bomb& b) {
    playerID = b.playerID;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
}

//Assignment operator
Bomb& Bomb::operator = (const Bomb& b) {
    playerID = b.playerID;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
    return *this;
}

//Get priority
int Bomb::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Bomb::operator <(const Bomb& playerObj) const {
    return priority < playerObj.priority;
}

//Validates a bomb order
bool Bomb::validate() {
    bool playerOwnsCountry = false;
    bool enemyTerritory = false;
    bool validMove = false;

    //check if the player owns the country
    if (playerID == countryOwner) {
        playerOwnsCountry = true;
    }
    //check if other territory is owned by another player
    if (playerID != attCountryOwner) {
        enemyTerritory = true;
    }
    //needed: assure the 2 countries and ajdacent
    if (territory->isAdjacentNode(attTerritory->id)) {
        validMove = true;
    }
    //needed: check if players are negotiating

    return (playerOwnsCountry && enemyTerritory && validMove);
}

//Executes a bomb order
void Bomb::execute() {
    if (validate()) {

        int armies = attTerritory->getArmies();
        attTerritory->setArmiesNumber((armies+1)/2); //rounding up

        cout << "Player " << this->playerID << " bombed " << attTerritory->name << " it has only " << attTerritory->getArmies() << " units remaining.\n";
        if(attTerritory->getArmies() == 0){
            cout << "Congrats, you conquered: " << attTerritory->name << endl;
            attTerritory->setOwner(this->playerID);
        }
    }
}

ostream& operator<<(std::ostream& out, const Bomb& b)
{
    out << "A Bomb order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << "" << "\n\tcountryOwner: "
        << b.countryOwner << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: " << "" << "}\n";
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   BLOCKADE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Blockade::Blockade(Player* pl, Territory* terr) {
    countryOwner = terr->getOwnerID();
    playerID = pl->name;
    player = pl;
    territory = terr;
}

//Copy constructor
Blockade::Blockade(const Blockade& d2) {
    countryOwner = d2.countryOwner;
    playerID = d2.playerID;
    player = d2.player;
    territory = d2.territory;
}

//Assignment operator
Blockade& Blockade::operator = (const Blockade& d2) {
    countryOwner = d2.countryOwner;
    playerID = d2.playerID;
    player = d2.player;
    territory = d2.territory;
    return *this;
}

//Get priority
int Blockade::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Blockade::operator <(const Blockade& playerObj) const {
    return priority < playerObj.priority;
}

//Validates a blockade order
bool Blockade::validate() {
    bool playerOwnsCountry = false;

    if (playerID == countryOwner) {
        playerOwnsCountry = true;
    }
    return (playerOwnsCountry);
}

//Executes a blockade order
void Blockade::execute() {

    if (validate()) {
        int tempArmies = territory->getArmies();
        territory->setArmiesNumber(tempArmies * 2);
        territory->setOwner(99);

        cout << "Player " << playerID << " has blockaded " << territory->name << ", it now has " << territory->getArmies() << ".\n";
    }

}

ostream& operator<<(std::ostream& out, const Blockade& b)
{
    out << "A Blockade order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryName: " << b.countryName << "\n\tcountryOwner: "
        << b.countryOwner << "}\n";
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   AIRLIFT					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Airlift::Airlift(Player* pl, Territory* terr, Territory* attTerr, int unitsAttackingWith) {
    countryOwner = terr->getOwnerID();
    units = unitsAttackingWith;
    playerID = pl->name;
    player = pl;
    territory = terr;
    attTerritory = attTerr;
    attCountryOwner = attTerr->getOwnerID();
}

//Copy constructor
Airlift::Airlift(const Airlift& b) {
    playerID = b.playerID;
    units = b.units;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
}

//Assignment operator
Airlift& Airlift::operator = (const Airlift& b) {
    playerID = b.playerID;
    units = b.units;
    countryOwner = b.countryOwner;
    player = b.player;
    territory = b.territory;
    attTerritory = b.attTerritory;
    attCountryOwner = b.attCountryOwner;
    return *this;
}

//Get priority
int Airlift::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Airlift::operator <(const Airlift& playerObj) const {
    return priority < playerObj.priority;
}

//Validates an airlift order
bool Airlift::validate() {
    bool playerOwnsCountry = false;
    bool validUnitsToMoveOrAtt = false;
    bool validOpponent = false;

    //check if the player owns the country
    if (playerID == countryOwner) {
        playerOwnsCountry = true;
    }
    //check if player has more 1 or more units to attack with and if they are advancing with valid units
    if (units >= 1 && territory->getArmies() >= units) {
        validUnitsToMoveOrAtt = true;
    }
    //check if negotiating
    if (!player->checkForAllies(attTerritory->getOwnerID())) {
        validOpponent = true;
    }

    return (playerOwnsCountry && validUnitsToMoveOrAtt && validOpponent);
}

//Executes an airlift order
void Airlift::execute() {

    if (validate()) {

        //player move
        if (playerID == attCountryOwner) {
            int tempArmies = territory->getArmies();
            tempArmies -= units;
            territory->setArmiesNumber(tempArmies);
            int tempAttArmies = attTerritory->getArmies();
            tempAttArmies += units;
            attTerritory->setArmiesNumber(tempAttArmies);

            cout << "Player " << playerID << " moved " << units << " units to " << attTerritory->name << ".\n";

        //player attack
        } else {

            int tempArmies = territory->getArmies();
            tempArmies -= units;
            territory->setArmiesNumber(tempArmies);

            //dice rolling
            int att = units;
            int def = attTerritory->getArmies();
            srand(time(0));

            while (att > 0 && def > 0) {
                int result = 1 + (rand() % 10);
                if (result >= 6)
                    --att;

                result = 1 + (rand() % 10);
                if (result >= 7)
                    --def;
            }

            if (att > 0) {
                attTerritory->setArmiesNumber(att);
                attTerritory->setOwner(territory->getOwnerID());

                cout << "Player " << playerID << " attacked " << attTerritory->name << " via airlift, owned by player " <<
                     attCountryOwner << " with " << units << " units and conquered the territory with " <<
                     attTerritory->getArmies() << " attackers remaining on the new territory.\n";

                Deck* deck = new Deck();
                player->getMyHand()->add(deck->draw());
                player->setCardFlag(true);
            }
            if (def > 0) {
                attTerritory->setArmiesNumber(def);

                cout << "Player " << playerID << " attacked " << attTerritory->name << " via airlift, owned by player " <<
                     attCountryOwner << " with " << units << " units and failed to conquer the territory with " <<
                     attTerritory->getArmies() << " defenders remaining.\n";
            }

        }
    }

}

ostream& operator<<(std::ostream& out, const Airlift& b)
{
    out << "An Airlift order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\tcountryOwner: "
        << b.countryOwner << "\n\tunits: " << b.units << "\n\tattCountryOwner: " << b.attCountryOwner << "\n\tattCountryName: "
        << b.attCountryOwner << "}\n";
    return out;
}

/////////////////////////////////////////////////////////////////////////////
///   NEGOTIATE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Overloaded constructor
Negotiate::Negotiate(Player* pl, Player* otherPl) {
    playerID = pl->name;
    otherPlayerID = otherPl->name;
    player = pl;
    otherPlayer = otherPl;
}

//Copy constructor
Negotiate::Negotiate(const Negotiate& b) {
    playerID = b.playerID;
    otherPlayerID = b.otherPlayerID;
    player = b.player;
    otherPlayer = b.otherPlayer;
}

//Assignment operator
Negotiate& Negotiate::operator = (const Negotiate& b) {
    playerID = b.playerID;
    otherPlayerID = b.otherPlayerID;
    player = b.player;
    otherPlayer = b.otherPlayer;
    return *this;
}

//Get priority
int Negotiate::getPriority() {
    return priority;
}

//Less than operator for priority comparison
bool Negotiate::operator <(const Negotiate& playerObj) const {
    return priority < playerObj.priority;
}


//Validates a negotiate order
bool Negotiate::validate() {
    bool validOpponent = false;

    if (playerID != otherPlayerID) {
        validOpponent = true;
    }

    return (validOpponent);
}

//Executes a negotiate order
void Negotiate::execute() {

    if (validate()) {

        player->addAlly(otherPlayer);
        otherPlayer->addAlly(player);

        cout << "Player " << playerID << " and Player " << otherPlayerID << " are now negotiating" << ".\n";
    }
}

ostream& operator<<(std::ostream& out, const Negotiate& b)
{
    out << "A Negotiate order has been created {" << "\n\tPlayerID: " << b.playerID << "\n\totherPlayer: " << b.otherPlayerID << "}\n";
    return out;
}


///   ORDERLIST					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

//Default Constructor
OrderList::OrderList() = default;

//destructor
OrderList::~OrderList() {
    list <Order*> ::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        delete* it;
    }
    orders.clear();
}

//Add order to list
void OrderList::addOrder(Order* x) {
    orders.push_back(x);
}

//Remove order from list
void OrderList::removeOrder(Order* x) {
    list <Order*> ::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        if (*it == x) {
            orders.remove(x);
            break;
        }
    }
}

//Swap order x with order y in the list
void OrderList::swapOrder(Order* x, Order* y) {
    list <Order*> ::iterator it;
    list <Order*> ::iterator jt;
    list <Order*> ::iterator temp1;
    list <Order*> ::iterator temp2;
    bool check1 = false;
    bool check2 = false;

    for (it = orders.begin(); it != orders.end(); ++it) {
        if (*it == x) {
            temp1 = it;
            check1 = true;
        }
        if (*it == y) {
            temp2 = it;
            check2 = true;
        }
        if (check1 && check2) {
            *temp1 = y;
            *temp2 = x;
        }
    }
}

//Move order up or down in the list
void OrderList::moveOrder(Order* x, string move) {
    list <Order*> ::iterator it;
    list <Order*> ::iterator hold_it;
    list <Order*> ::iterator it_pos;
    bool check1 = false;
    bool check2 = true;
    for (it = orders.begin(); it != orders.end(); ++it) {
        if (move == "down") {
            it_pos = it;
        }
        if (check1) {
            Order* o = (*it_pos);
            if (move == "down") {
                *it = x;
                *hold_it = o;
            }
            break;
        }
        if (*it == x) {
            if (check2 && move == "up") {
                break;
            }
            hold_it = it;
            if (move == "up") {
                Order* o = (*it_pos);
                *it_pos = x;
                *it = o;
            }
            check1 = true;
        }
        check2 = false;
        if (move == "up") {
            it_pos = it;
        }
    }
}

//Return first order in list
Order* OrderList::front() {
    return orders.front();
}

//Returns true if list is empty, false otherwise
bool OrderList::isEmpty() {
    if (orders.empty()) return true;
    else return false;
}

//Compare priority of orders in list
bool compare(Order* x,Order* y) {
    if (x->getPriority() < y->getPriority())
        return (true);
    else
        return(false);
}

//View the list of orders
void OrderList::viewOrderList() {
    list <Order*> ::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        cout << (*it) << endl;
    }
}

//Check if OrderList contains any Deploy orders
bool OrderList::containsDeployOrders() {
    list <Order*> ::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        if ((*it)->getPriority()==1) return true;
    }
    return false;
}


//Execute orders then deletes pointers to objects and clears list
void OrderList::executeOrderList() {
    list <Order*> ::iterator it;
    for (it = orders.begin(); it != orders.end(); ++it) {
        (*it)->execute();
        delete *it;
    }
    orders.clear();
}

void OrderList::sortOrderList() {
    orders.sort(compare);
}