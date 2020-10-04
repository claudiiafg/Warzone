/*
 * Cards.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: ian
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Cards.h"
using namespace std;

string type;

Card::Card(){

    srand (time(NULL));
    int random = rand() % 5;
    
    switch (random){

        case 0:
                type = "bomb";
        case 1:
                type = "reinforcement";
        case 2:
                type = "blockade";
        case 3:
                type = "airlift";
        default:
                type = "diplomacy";
         }

}

string getType(){
                return type;
        }

void setType(string typeString){
        type = typeString;
        }

Deck::Deck(){

    static int nextDraw;
    Card deck[50];

}

