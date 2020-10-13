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

class Card {

public:
    Card();

    Card(const Card &oldCard);

    string getType();

    void setType(string x);

    friend ostream &cardStream(ostream &cs, const Card *c);

private:
    string type;
};


class Hand {

public:
    Hand();

    Hand(const Hand &oldHand);

    ~Hand();

    void display();

    Card *play(string cardType);

    void add(Card *card);

    void setBombCount(int x);

    int getBombCount();

    int getReinCount();

    void setReinCount(int x);

    int getBlockCount();

    void setBlockCount(int x);

    int getAirCount();

    void setAirCount(int x);

    int getDiplomCount();

    void setDipCount(int x);

    vector<Card*> getHand();

    void setHand(vector<Card*> cv);

    friend ostream &handStream(ostream &hs, const Hand *h);

private:
    int bombCounter;
    int reinforcementCounter;
    int blockadeCounter;
    int airliftCounter;
    int diplomacyCounter;
    vector<Card*> hand;
};

class Deck {
public:
    Deck();

    Deck(const Deck &oldDeck);

    ~Deck();

    Card *draw();

    vector<Card*> getDeck();

    void setDeck(vector<Card*> cv);

    void add(Card *card);

    friend ostream &deckStream(ostream &ds, const Deck *d);

private:
    int nextDraw;
    vector<Card*> deck;
};

#endif /* CARDS_H_ */