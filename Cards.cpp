/**Ian Down 40035062
 Assignment 1
 COMP 345 - D
 9 October 2020
 */

#include <stdlib.h>
#include "Cards.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;


Card::Card() {
    /**
     * Assigns a type to a new card based on a random number generator
    */
    int random = int(rand() % 5);
    switch (random) {
        case 0:
            type = "bomb";
            break;
        case 1:
            type = "reinforcements";
            break;
        case 2:
            type = "blockade";
            break;
        case 3:
            type = "airlift";
            break;
        default:
            type = "diplomacy";
    }
}

Card::Card(const Card &oldCard) {
    type = oldCard.type;
}


ostream& operator<<(ostream &out, const Card &c) {
    out << "Card type: " << c.type;
    return out;
}


string Card::getType() {
    return type;
}

void Card::setType(string x) {
    type = x;
}

/**
 * Initializes 50 pseudo-random cards and sorts them into a vector
 * */
Deck::Deck() {
    for (int i = 0; i < 50; i++) {
        Card *temp = new Card;
        deck.push_back(temp);
    }

}

Deck::Deck(const Deck &oldDeck) {
    for (int i = 0; i < oldDeck.deck.size(); i++) {
        deck.at(i) = oldDeck.deck.at(i);
    }
}

Deck::~Deck() {
    for (int i = 0; i < deck.size(); i++) {
        delete deck[i];
        deck[i] = NULL;
    }

}

ostream& operator<<(ostream &out, const Deck &d) {
    Card *temp = new Card;
    out << "Cards left in the deck: \n";
    for (int i = 0; i < d.deck.size(); i++) {
        temp = d.deck.at(i);
        out << temp->getType() << "\n";
    }
    delete temp;
    temp = NULL;
    return out;
}

vector<Card*> Deck::getDeck() {
    return deck;
}

void Deck::setDeck(vector<Card*> cv) {
    deck = cv;
}

void Deck::add(Card *card) {
    deck.insert(deck.begin(), card);
}

/**
 * Draws a card, puts it in the hand and erases it from the deck 
 */

Card *Deck::draw() {
    Card *oldCard = new Card;
    if (deck.size() == 0) {
        return oldCard;
        delete oldCard;
    }
    cout << "You got " << deck.back()->getType() << "!\n\n";
    oldCard = deck.back();
    deck.pop_back();
    return oldCard;
    delete oldCard;
}

Hand::Hand() {
    /**
     * Initializes a hand with 5 cards
     */
    for (int i = 0; i < 5; i++) {
        Card *temp = new Card;
        hand.push_back(temp);
    }
    bombCounter = 0;
    reinforcementCounter = 0;
    blockadeCounter = 0;
    airliftCounter = 0;
    diplomacyCounter = 0;
}

Hand::Hand(const Hand &oldHand) {
    for (int i = 0; 0 < oldHand.hand.size(); i++) {
        hand.at(i) = oldHand.hand.at(i);
    }
    bombCounter = oldHand.bombCounter;
    reinforcementCounter = oldHand.reinforcementCounter;
    blockadeCounter = oldHand.blockadeCounter;
    airliftCounter = oldHand.airliftCounter;
    diplomacyCounter = oldHand.diplomacyCounter;
}

ostream& operator<<(ostream &out, const Hand &h) {
    out << "\n Bombs: " << h.bombCounter;
    out << "\n Reinforcements: " << h.reinforcementCounter;
    out << "\n Blockades: " << h.blockadeCounter;
    out << "\n Airlifts: " << h.airliftCounter;
    out << "\n Diplomacy: " << h.diplomacyCounter;
    return out;
}

Hand::~Hand() {
    for(int i = 0; i < hand.size();i++){
        delete hand[i];
        hand[i] = NULL;
    }
}

/**
 * Plays a card, returns it to the deck and erases it from the hand
 */
Card *Hand::play(string cardType) {
    Card *oldCard = new Card;
    for (int i = 0; i < hand.size(); i++) {
        if (hand.at(i)->getType() == cardType) {
            oldCard = hand.at(i);
            cout << "You played " << cardType << "! \n\n";
            hand.erase(hand.begin() + i);
            return oldCard;
        }
    }

    cout << "You don't have any " + cardType + "s in your hand!\n\n";
    return oldCard;
}

/**
 * Adds a new card to the hand from the deck (Complementary to "draw" function)
 * */
void Hand::add(Card *card) {
    try {
        hand.push_back(card);

        if (card->getType() == "") {
            throw 99;
        }
    }
    catch (int e) {
        cout << "Error: No more cards left in the deck!";
    }
}

/**
 * Displays the number of each card in the hand after counting them
 */
void Hand::display() {

    for (int i = 0; i < hand.size(); i++) {
        if (hand.at(i)->getType() == "bomb")
            bombCounter += 1;
        else if (hand.at(i)->getType() == "reinforcements")
            reinforcementCounter += 1;
        else if (hand.at(i)->getType() == "blockade")
            blockadeCounter += 1;
        else if (hand.at(i)->getType() == "airlift")
            airliftCounter += 1;
        else if (hand.at(i)->getType() == "diplomacy")
            diplomacyCounter += 1;
    }
    cout << "Here are the cards in your hand:";
    cout << "\n Bombs: " << bombCounter;
    cout << "\n Reinforcements: " << reinforcementCounter;
    cout << "\n Blockades: " << blockadeCounter;
    cout << "\n Airlifts: " << airliftCounter;
    cout << "\n Diplomacy: " << diplomacyCounter << "\n \n";
    bombCounter = 0;
    reinforcementCounter = 0;
    blockadeCounter = 0;
    airliftCounter = 0;
    diplomacyCounter = 0;
}

int Hand::getBombCount() {
    return bombCounter;
}

void Hand::setBombCount(int x) {
    bombCounter = x;
}

int Hand::getReinCount() {
    return reinforcementCounter;
}

void Hand::setReinCount(int x) {
    reinforcementCounter = x;
}

int Hand::getBlockCount() {
    return blockadeCounter;
}

void Hand::setBlockCount(int x) {
    blockadeCounter = x;
}

int Hand::getAirCount() {
    return airliftCounter;
}

void Hand::setAirCount(int x) {
    airliftCounter = x;
}

int Hand::getDiplomCount() {
    return diplomacyCounter;
}

void Hand::setDipCount(int x) {
    diplomacyCounter = x;
}

vector<Card*> Hand::getHand() {
    return hand;
}

void Hand::setHand(vector<Card*> cv) {
    hand = cv;
}






