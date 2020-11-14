//
// Created by Claudia on 2020-11-14.
//

#include "GameEngine.h"
#include <typeinfo>

// default constructor
GameEngine::GameEngine() {
    try{
        selectMap();
        selectPlayers();
        activateObservers();

    } catch(int e) {
        cout << "You exited the game. Goodbye!" << endl;
    }
}

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
    return os;
}

// equality operator
GameEngine &GameEngine::operator=(const GameEngine &_game) {
    map = _game.map;
    players = _game.players;
    return *this;
}

// set map to play
void GameEngine::setMap(Map* mapToSet) {
    map = mapToSet;
}

// create correct amount of players with default parameters
void GameEngine::createPlayers(int amount) {
    for(int i = 0; i < amount; i++) {
        players.push_back(new Player());
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
            exit = true;
        } else {
            cout << "Invalid number of player. Try again!" << endl;
        }
    }

    cout << 'out';
}

void GameEngine::activateObservers() {

}

int main() {

    GameEngine* game = new GameEngine();
    cout << *game << endl;

    cout << "continue" << endl;

    return 0;
}
