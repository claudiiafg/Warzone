/**Ian Down 40035062
 Assignment 1
 COMP 345 - D
 9 October 2020
 */

#include "Cards.h"

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

ostream &cardStream(ostream &cs, const Card c) {
    cout << "Card type: " << c.type;
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
    Card Card1;
    Card Card2;
    Card Card3;
    Card Card4;
    Card Card5;
    Card Card6;
    Card Card7;
    Card Card8;
    Card Card9;
    Card Card10;
    deck.push_back(Card1);
    deck.push_back(Card2);
    deck.push_back(Card3);
    deck.push_back(Card4);
    deck.push_back(Card5);
    deck.push_back(Card6);
    deck.push_back(Card7);
    deck.push_back(Card8);
    deck.push_back(Card9);
    deck.push_back(Card10);
    Card Card11;
    Card Card12;
    Card Card13;
    Card Card14;
    Card Card15;
    Card Card16;
    Card Card17;
    Card Card18;
    Card Card19;
    Card Card20;
    deck.push_back(Card11);
    deck.push_back(Card12);
    deck.push_back(Card13);
    deck.push_back(Card14);
    deck.push_back(Card15);
    deck.push_back(Card16);
    deck.push_back(Card17);
    deck.push_back(Card18);
    deck.push_back(Card19);
    deck.push_back(Card20);
    Card Card21;
    Card Card22;
    Card Card23;
    Card Card24;
    Card Card25;
    Card Card26;
    Card Card27;
    Card Card28;
    Card Card29;
    Card Card30;
    deck.push_back(Card21);
    deck.push_back(Card22);
    deck.push_back(Card23);
    deck.push_back(Card24);
    deck.push_back(Card25);
    deck.push_back(Card26);
    deck.push_back(Card27);
    deck.push_back(Card28);
    deck.push_back(Card29);
    deck.push_back(Card30);
    Card Card31;
    Card Card32;
    Card Card33;
    Card Card34;
    Card Card35;
    Card Card36;
    Card Card37;
    Card Card38;
    Card Card39;
    Card Card40;
    deck.push_back(Card31);
    deck.push_back(Card32);
    deck.push_back(Card33);
    deck.push_back(Card34);
    deck.push_back(Card35);
    deck.push_back(Card36);
    deck.push_back(Card37);
    deck.push_back(Card38);
    deck.push_back(Card39);
    deck.push_back(Card40);
    Card Card41;
    Card Card42;
    Card Card43;
    Card Card44;
    Card Card45;
    Card Card46;
    Card Card47;
    Card Card48;
    Card Card49;
    Card Card50;
    deck.push_back(Card41);
    deck.push_back(Card42);
    deck.push_back(Card43);
    deck.push_back(Card44);
    deck.push_back(Card45);
    deck.push_back(Card46);
    deck.push_back(Card47);
    deck.push_back(Card48);
    deck.push_back(Card49);
    deck.push_back(Card50);
}


Deck::Deck(const Deck &oldDeck) {
    for (int i = 0; i < oldDeck.deck.size(); i++) {
        deck.at(i) = oldDeck.deck.at(i);
    }
}

ostream &deckStream(ostream &ds, const Deck d) {
    cout << "Cards left in the deck: \n";
    for (int i = 0; i < d.deck.size(); i++) {
        Card temp = d.deck.at(i);
        cout << temp.getType() << "\n";
    }
}

vector <Card> Deck::getDeck() {
    return deck;
}

void Deck::setDeck(vector <Card> cv) {
    deck = cv;
}

void Deck::setDeck(vector <Card> cv) {
    deck = cv;
}

void Deck::add(Card card) {
    deck.insert(deck.begin(), card);
}

/**
 * Draws a card, puts it in the hand and erases it from the deck 
 */

Card Deck::draw() {
    Card oldCard;
    if (deck.size() == 0) {
        return oldCard;
    }
    cout << "You got " << deck.back().getType() << "!\n\n";
    oldCard = deck.back();
    deck.pop_back();
    return oldCard;
}

Hand::Hand() {
    /**
     * Initializes a hand with 5 cards
     */
    Card Hand1;
    Card Hand2;
    Card Hand3;
    Card Hand4;
    Card Hand5;
    hand.push_back(Hand1);
    hand.push_back(Hand2);
    hand.push_back(Hand3);
    hand.push_back(Hand4);
    hand.push_back(Hand5);
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

ostream &handStream(ostream &hs, const Hand h) {
    cout << "Cards in hand: \n";
    for (int i = 0; i < h.hand.size(); i++) {
        Card temp = h.hand.at(i);
        cout << temp.getType() << "\n";

    }
}

/**
 * Plays a card, returns it to the deck and erases it from the hand
 */
Card Hand::play(string cardType) {
    Card oldCard;
    for (int i = 0; i < hand.size(); i++) {
        if (hand.at(i).getType() == cardType) {
            oldCard = hand.at(i);
            cout << "You played " << cardType << "! \n\n";
            hand.erase(hand.begin() + i);
            return oldCard;
        }
    }
}

cout << "You don't have any " + cardType + "s in your hand!\n\n";
return
newCard;
}

cout << "You don't have any " + cardType + "s in your hand!\n\n";
return
oldCard;
}

/**
 * Adds a new card to the hand from the deck (Complementary to "draw" function)
 * */
void Hand::add(Card card) {
    try {
        hand.push_back(card);

        if (card.getType() == "") {
            throw 99;
        }
    }
    catch (int e) {
        cout << "Error: No more cards left in the deck!";
    }
}

}
catch (
int e
) {
cout << "Error: No more cards left in the deck!";
}
}

/**
 * Displays the number of each card in the hand after counting them
 */
void Hand::display() {
    for (int i = 0; i < hand.size(); i++) {
        if (hand.at(i).getType() == "bomb")
            bombCounter += 1;
        else if (hand.at(i).getType() == "reinforcements")
            reinforcementCounter += 1;
        else if (hand.at(i).getType() == "blockade")
            blockadeCounter += 1;
        else if (hand.at(i).getType() == "airlift")
            airliftCounter += 1;
        else if (hand.at(i).getType() == "diplomacy")
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

vector <Card> Hand::getHand() {
    return hand;
}

void Hand::setHand(vector <Card> cv) {
    hand = cv;
}

int Hand::getReinCoun() {
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

vector <Card> Hand::getHand() {
    return hand;
}

void Hand::setHand(vector <Card> cv) {
    hand = cv;
}






