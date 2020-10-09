/*
 * Cards.h
 *Ian Down 40035062
 Assignment 1
 COMP 345 - D
 9 October 2020
 */ 

#ifndef CARDS_H
#define CARDS_H
#include <vector>
#include <iostream>
using namespace std;

class Card{

	public:
	    Card();
		string getType();
		void setType(string x);

	private:
		string type;
};


class Hand{

	public:
		Hand();
		void display();
		Card play(string cardType);
		void add(Card card);
		void setBombCount(int x);
		int getBombCount();
		int getReinCoun();
		void setReinCount(int x);
		int getBlockCount();
		void setBlockCount(int x);
		int getAirCount();
		void setAirCount(int x);
		int getDiplomCount();
		void setDipCount(int x);
		vector<Card> getHand();
		void setHand(vector<Card> cv);
	
	private:
		int bombCounter;
		int reinforcementCounter;
		int blockadeCounter;
		int airliftCounter;
		int diplomacyCounter;
		vector<Card> hand;
};

class Deck{
	public:
		Deck();
		Card draw();
		vector<Card> getDeck();
		void setDeck(vector<Card> cv);
		void add(Card card);

	private:
		int nextDraw;
		vector<Card> deck;
};

#endif /* CARDS_H_ */