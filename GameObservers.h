#pragma once
#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include <iostream>
#include <list>
using namespace std;

class Observer {

    public:
        ~Observer();
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
    private:
        list<Observer*> *_observers;

};

class MapSubject: public Observable{

    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        MapSubject();
        MapSubject(Map* m);
        ~MapSubject();
    private:
        list<Observer*> *_observers;
};

class PlayerSubject: public Observable {
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        PlayerSubject();
        PlayerSubject(Player* p);
        ~PlayerSubject();
    private:
        list<Observer*> *_observers;

};

class OrderListSubject: public Observable {
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        OrderListSubject();
        OrderListSubject(OrderList* ol);
        ~OrderListSubject();
    private:
        list<Observer*> *_observers;

};

class PhaseObserver: public Observer {

    public:
        PhaseObserver();
        ~PhaseObserver();
        void Update();
        void display();

    private:

};

class GameStatObserver: public Observer {

    public:
        GameStatObserver();
        GameStatObserver(MapSubject* ms, PlayerSubject* ps, OrderListSubject* ols);
        ~GameStatObserver();
        void Update();
        void display();
    private:

};