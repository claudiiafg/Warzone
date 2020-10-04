/*
 * Cards.h
 *
 *  Created on: Sep 29, 2020
 *      Author: ian
 */

#ifndef CARDS_H_
#define CARDS_H_

#include <iostream>
using namespace std;

class Card{

public:

    Card(){}
	string getType(){}
	void setType(string type){}

private:
string type;
};

class Deck{
public:

	Deck(){
	} 
    

private:
	static int nextDraw;
	Card deck[50];

};

class Hand{

public:


	Hand(int bombCounter, int reinforcementCounter, int blockadeCounter,
			int airliftCounter, int diplomacyCounter);

	Card hand[];

	void draw(Deck deck);
	void display();

private:
	int bombCounter;
	int reinforcementCounter;
	int blockadeCounter;
	int airliftCounter;
	int diplomacyCounter;

};

#endif /* CARDS_H_ */