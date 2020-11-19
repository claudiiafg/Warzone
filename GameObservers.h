#pragma once
#include <iostream>
#include <list>
#include "GameObservers.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;

class Player;
class OrderList;
class Map;

class Observer {

    public:
        ~Observer();
        Observer(const Observer& o);
        virtual void Update() = 0;
    protected:
        Observer();

    friend ostream& operator<<(ostream &os, const Observer& o);
    Observer& operator = (const Observer& _file);
};

class Observable {

    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        Observable();
        ~Observable();
        Observable(const Observable& o);
        list<Observer*> getObservers();

        friend ostream& operator<<(ostream &os, const Observable& o);
        Observable& operator = (const Observable& _file);
    private:
        list<Observer*> *_observers;

};

class PhaseObserver: public Observer {

    public:
        PhaseObserver();
        PhaseObserver(Player* p);
        ~PhaseObserver();
        PhaseObserver(const PhaseObserver& po);
        void Update();
        void display();

    friend ostream& operator<<(ostream &os, const PhaseObserver& po);
    PhaseObserver& operator = (const PhaseObserver& _file);

    private:
        Player *playerSubject;

};

class GameStatObserver: public Observer {

    public:
        GameStatObserver();
        GameStatObserver(Map* m);
        ~GameStatObserver();
        GameStatObserver(const GameStatObserver& gso);
        void Update();
        void display();

        friend ostream& operator<<(ostream &os, const GameStatObserver& o);
        GameStatObserver& operator = (const GameStatObserver& _file);
    private:
        Map *mapSubject;
        
};