//
// Created by Claudia on 2020-11-14.
//

#include "GameEngine.h"
#include <typeinfo>

// default constructor
GameEngine::GameEngine() = default;

// copy constructor
GameEngine::GameEngine(const GameEngine &_c) {
    map = _c.map;
    players = _c.players;
}

// destructor
GameEngine::~GameEngine() {
    delete map;
    map = NULL;

    for(int i = 0; i < players.size(); i++) {
        delete players[i];
        players[i] = NULL;
    }
}

// stream operator
ostream &operator<<(ostream &os, const GameEngine &n) {
    os << n.map->name << endl;
    os << n.players.size() << " Players in game:" << endl;
    for(int i = 0; i < n.players.size(); i++) {
        os << *n.players[i] << endl;
    }
    return os;
}

// equality operator
GameEngine &GameEngine::operator=(const GameEngine &_game) {
    map = _game.map;
    players = _game.players;
    return *this;
}

// set map to play
void GameEngine::startupPhase() {
    try{
        selectMap();
        selectPlayers();
//        activateObservers();

    } catch(int e) {
        cout << "You exited the game. Goodbye!" << endl;
    }
}


// set map to play
void GameEngine::setMap(Map* mapToSet) {
    map = mapToSet;
}

// create correct amount of players with default parameters
void GameEngine::createPlayers(int amount) {
    vector<Territory*> tempTerr = map->territories;
    int initialArmies = getInitialArmies(amount);
    vector<vector<Territory*>> playersTerritories = getTerritoriesPerPlayer(amount, tempTerr);

    // for each player, create hands and orders, and create player
    for(int i = 0; i < amount; i++) {
        const int PLAYER_ID = i;

        // get player's territories and set territory owner for each
        vector<Territory*> playerTerr = playersTerritories[PLAYER_ID];
        for(auto & terr:  playerTerr) {
            terr->setOwner(PLAYER_ID);
        }

        //create empty hand and empty orders list
        Hand* playerHand = new Hand();
        OrderList* playerOrders = new OrderList();

        //create player
        players.push_back(new Player(PLAYER_ID, initialArmies, playerTerr, playerHand, playerOrders));
    }
}

/*
 * iterate though all the files, display valid map files and ask to select map
 * check validity of pal selected -> if valid set and continue to next option
 * while not valid or not cancel selection ask for new input
 */
void GameEngine::selectMap() {
    MapLoader loader;
    loader.loadMaps();
    vector<MapFile*> rawMaps = loader.getMaps();

    int option = 0;
    const int EXIT_SELECTION = rawMaps.size() + 1;

    while(option != EXIT_SELECTION) {
        cout << ">>>>>>>> Which Map do you wish to play?" << endl;

        for (int i = 0; i < rawMaps.size(); i++) {
            cout << i << ": "<< *rawMaps[i];
        }

        cout << EXIT_SELECTION << ": EXIT" << endl;

        cin >> option;

        if(option < EXIT_SELECTION) {
            Map* map = new Map(rawMaps[option]->name, rawMaps[option]->content);
            if(map->validate()) {
                cout << *map << endl;
                setMap(map);
                cout << "**** Great selection! ****" << endl;
                option = EXIT_SELECTION;
            } else {
                delete map;
                map = NULL;
                cout << "Please select a different map." << endl;
                cout << endl;
                continue;
            }
        } else {
            throw 99;
        }
    }
    cout << endl;
}

/*
 * request amount of players
 * exit selection by inputting non integer values
 * if valid amount create correct amount of players with defualt parameters
 */
void GameEngine::selectPlayers() {
    int amountOfPlayers = 0;
    const int UPPER_LIMIT = 5;
    const int LOWER_LIMIT = 2;
    bool exit = false;

    while(!exit) {
        cout << ">>>>>>>> Please select the number of players (2-5)" << endl;
        cout << "Select any non-number key to exit selection." << endl;

        cin >> amountOfPlayers;

        // if input is not an integer
        if(cin.fail()) {
            throw 99;

        } else if(amountOfPlayers >= LOWER_LIMIT && amountOfPlayers <= UPPER_LIMIT) {
            createPlayers(amountOfPlayers);
            cout << "**** Players ready! ****" << endl;
            exit = true;
        } else {
            cout << "Invalid number of player. Try again!" << endl;
        }
    }
    cout << endl;
}

void GameEngine::activateObservers() {
    int option = 0;
    const int EXIT = 5;

    while(option != EXIT) {
        cout << ">>>>>>>> Please select the amount of information you wish to receive throughout the game" << endl;
        cout << "1. Phase - displays information happening in the phase you're currently playing" << endl;
        cout << "2. Statistics - displays some useful statistics about the game" << endl;
        cout << "3. Both - turn on both notifications" << endl;
        cout << "4. None - turn off both notifications" << endl;
        cout << "5. EXIT" << endl;

        cin >> option;

        if(option == 1) {
            // activate phase observers
            // TODO
            cout << "**** Phase Observer ON! ****" << endl;
            option = EXIT;

        } else if(option == 2) {
            // activate statistics observer
            // TODO
            cout << "**** Statistics Observer ON! ****" << endl;
            option = EXIT;

        } else if (option == 3) {
            // activate both observers
            // TODO
            cout << "**** All Observer ON! ****" << endl;
            option = EXIT;

        } else if (option == 4) {
            // deactivate both observers
            // TODO
            cout << "**** All Observer OFF! ****" << endl;
            option = EXIT;

        } else if (option == 5) {
            throw 99;

        } else {
            cout << "Invalid selection. Try again!" << endl;
            continue;
        }
    }
    cout << endl;
}

int GameEngine::getInitialArmies(int amount) {
    switch(amount) {
        case 2:
            return 40;
        case 3:
            return 35;
        case 4:
            return 30;
        case 5:
            return 25;
        default:
            return 0;
    }
}

vector<vector<Territory *>> GameEngine::getTerritoriesPerPlayer(int amount, vector<Territory *> tempTerr) {
    vector<vector<Territory*>> playersTerritories = {};

    for(int i = 0; i < amount; i++) {
        playersTerritories.push_back({});
    }
    int playerIndex = 0;

    // assign territories to players in a round-robin method
    while (tempTerr.size() > 0) {
        if(playerIndex == amount) playerIndex = 0;
        int RandIndex = rand() % tempTerr.size();
        playersTerritories[playerIndex].push_back(tempTerr[RandIndex]);
        tempTerr.erase(tempTerr.begin() + RandIndex);
        playerIndex++;
    }

    return playersTerritories;
}

int main() {

    GameEngine* game = new GameEngine();
    game->startupPhase();

    cout << "Current game in engine: " << endl;
    cout << *game << endl;

    return 0;
}
