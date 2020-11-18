#pragma once
#include <iostream>
#include <list>
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
    private:
        list<Observer*> *_observers;

};

class PhaseObserver: public Observer {

    public:
        PhaseObserver();
        ~PhaseObserver();
        PhaseObserver(const PhaseObserver& po);
        void Update();
        void display();

    private:
        Player *playerSubject;

};

class GameStatObserver: public Observer {

    public:
        GameStatObserver();
        GameStatObserver(Map* m, Player* p, OrderList* ol);
        ~GameStatObserver();
        GameStatObserver(const GameStatObserver& gso);
        void Update();
        void display();
    private:
        Player *playerSubject;
        Map *mapSubject;
        OrderList *orderListSubject;
};