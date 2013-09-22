#ifndef MYLIST_H
#define MYLIST_H

#include "cartage.h"

enum MLC{Next,Previous,Current,Default};

struct Node{
    Cartage data;
    Node* previous;
    Node* next;
};

class MyList
{
public:
    MyList();
    ~MyList();

    void push_back();
    void push_back(Cartage);
    void push_front(Cartage);
    void set_current(int);
    Cartage read(MLC);//if list over but we also use this function it return elment from other side of the list
                      //never use with empty list
    Cartage read(int);//never use with empty list
                      //if list end it return front element
    Cartage* to_change(MLC = Default); //return front element
    Cartage* to_change(int);
    int count();
    void put_on(int, Cartage);
    void deleting(int);
    void clear();
    void sort(int);

private:
    Node* front;
    Node* back;
    Node* current;
};

#endif // MYLIST_H
