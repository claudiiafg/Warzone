/**Ian Down 40035062
 Assignment 1
 COMP 345 - D
 9 October 2020
 */ 

#include "Cards.h"
#include <iostream>
#include <vector>

using namespace std;
int main(){
    cout << "Welcome to the world's greatest card displayer! \n\n";

    Hand *hand = new Hand();
    Deck *deck = new Deck();

    int menu = 0;

    while(menu != 4) {
        cout << "What do you want to do? \n 1. Play a card \n 2. Draw a card \n 3. Display your hand \n 4. Quit \n";
        cin >> menu;

        if(menu == 1){
            cout << "What card do you want to play? \n1. Bomb \n2. Blockade\n3. Airlift \n4. Reinforcements \n5. Diplomacy\n\n";
            int option;
            cin >> option;

            if(option == 1)
                deck->add(hand->play("bomb"));

            else if(option == 2)
                deck->add(hand->play("blockade"));

            else if(option == 3)
                deck->add(hand->play("airlift"));

            else if(option == 4)
                deck->add(hand->play("reinforcements"));

            else if(option == 5)
                deck->add(hand->play("diplomacy"));

            else
                cout << "Error: Please enter a valid menu option.\n\n";

        } else if(menu == 2){
            hand->add(deck->draw());

        } else if(menu == 3){
            hand->display();

        } else if(menu == 4){
            break;

        } else{
            cout << "Error: Please select a valid menu option. \n";
        }
    }

    delete hand;
    hand = NULL;
    delete deck;
    deck = NULL;

    cout << "Thanks for playing!";
    return 0;
}