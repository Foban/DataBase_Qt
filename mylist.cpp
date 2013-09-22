#include "mylist.h"

MyList::MyList():
    front(0), back(0),current(0)
{}

MyList::~MyList()
{
    clear();
}

/////////////////////////////////////////////////////

bool cmp_mark(Cartage &a, Cartage &b){
    return a.getMark() < b.getMark();
}

bool cmp_color(Cartage &a, Cartage &b){
    return a.getColor() < b.getColor();
}

bool cmp_year(Cartage &a, Cartage &b){
    return a.getYear() > b.getYear();
}

bool cmp_status(Cartage &a, Cartage &b){
    return a.getStatus() < b.getStatus();
}

bool cmp_date(Cartage &a, Cartage &b){
    Data aa = a.getRepairTime(), bb = b.getRepairTime();
    return aa.year*365+aa.month*31+aa.day > bb.year*365+bb.month*31+aa.day;
}

bool (*cmp[])(Cartage&,Cartage&) = {cmp_mark, cmp_color, cmp_year, cmp_status, cmp_date};

void MyList::push_back()
{
    Node* newItem = new Node;
    newItem->previous = back;
    newItem->next = 0;
    if(!front){
        front = newItem;
        current = newItem;
    }
    else
    {
        back->next = newItem;
    }
    back = newItem;
}

void MyList::push_back(Cartage newCartage)
{
    Node* newItem = new Node;
    newItem->data.putMark(newCartage.getMark());
    newItem->data.putColor(newCartage.getColor());
    newItem->data.putYear(newCartage.getYear());
    newItem->data.putStatus(newCartage.getStatus());
    newItem->data.putRepairTime(newCartage.getRepairTime());
    newItem->previous = back;
    newItem->next = 0;
    if(!front){
        front = newItem;
        current = newItem;
    }
    else
    {
        back->next = newItem;
    }
    back = newItem;
}

void MyList::push_front(Cartage newCartage)
{
    Node* newItem = new Node;
    newItem->data.putMark(newCartage.getMark());
    newItem->data.putColor(newCartage.getColor());
    newItem->data.putYear(newCartage.getYear());
    newItem->data.putStatus(newCartage.getStatus());
    newItem->data.putRepairTime(newCartage.getRepairTime());
    newItem->next = front;
    newItem->previous = 0;
    if(!back){
        back = newItem;
        current = newItem;
    }
    else
    {
        front->previous = newItem;
    }
    front = newItem;
}

void MyList::set_current(int n)
{
    Node *need = front;
    for(int i = 0; i < n && need; ++i)
        need = need->next;
    if(!need)
        need = front;
    current = need;
}

Cartage MyList::read(MLC direction)
{
    switch(direction){
    case Next:
    {
        if(current->next)
            current = current->next;
        else
            current = front;
    }
        break;
    case Previous:
    {
        if(current->previous)
            current = current->previous;
        else
            current = back;
    }
        break;
    }
    if(current)
        return current->data;
    return Cartage();
}

Cartage MyList::read(int n)
{
    Node *need = front;
    for(int i = 0; i < n && need; ++i)
        need = need->next;
    if(!need)
        need = front;
    if(need)
        return need->data;
    return Cartage();
}

Cartage* MyList::to_change(MLC comand)
{
    switch (comand) {
    case Next:
    {
        if(current)
            return &current->data;
    }
        break;
    case Default:
    {
        if(front)
            return &front->data;
    }
        break;
    }
    return 0;
}

Cartage* MyList::to_change(int n)
{
    Node *need = front;
    for(int i = 0; i < n && need; ++i)
        need = need->next;
    return &need->data;
}

void MyList::deleting(int n)
{
    Node *removed = front;
    for(int i = 0; i < n; ++i){
        if(!removed) return;
        removed = removed->next;
    }
    if(removed->next)
    removed->next->previous=removed->previous;
    else back = removed->previous;
    if(removed->previous)
    removed->previous->next=removed->next;
    else front = removed->next;
    delete removed;
}

void MyList::clear()
{
    Node *removed = front;
    while(removed){
        front = front->next;
        delete removed;
        removed = front;
    }
    back = 0;
}

int MyList::count()
{
    int i = 0;
    for(;front; ++i){
        front = front->next;
    }
    return i;
}

void swap(Node *a, Node *b)
{
    Cartage tmp = b->data;
    b->data = a->data;
    a->data = tmp;
}

Node * min_node(Node *n, int a, bool der){
    Node * minNode = n;
    while ( n = n->next )
        if (cmp[a](n->data, minNode->data) == der)
            minNode = n;
    return minNode;
}


void sort_nodes(Node *n, int a, bool der){
    if(!n) return;
    Node * minNode;
    while ( n->next ){
        if ( ( minNode = min_node(n, a, der) ) != n )
            swap(n, minNode);
        n = n->next;
    }
}

void insert_sort(Node *n, int a, bool der)
{
    if(!n) return;
    Node * minNode;
    while ( n->next ){
        minNode = n->next;
        while(minNode->previous && cmp[a](minNode->data, minNode->previous->data) == der){
            swap(minNode, minNode->previous);
            minNode = minNode->previous;
        }
        n = n->next;
    }
}



void MyList::sort(int field)
{
    static bool der = true;
    static int col = -1;
    if(col == field){
        der = !der;
    }
    col = field;
    //sort_nodes(front, field, der);
    insert_sort(front, field, der);
}
