#pragma once

#include <iostream>
#include "Monom.h"
using namespace std;




struct Link {
    Monom m;
    Link* next;
    Link(Monom _m, Link* _n = nullptr) : m(_m), next(_n) {};
};

class List {
    Link* start;
    Link* end;
public:
    List() {
        start = new Link(0);
        start->next = start;
        end = start;
    };
    Link* Exist(Monom a){
        Link* tmp = start->next;
        while (tmp != start) {
            if (tmp->m.s == a.s) {
                return tmp;
            };
            tmp = tmp->next;
        }
        return nullptr;
    }
    void add(Monom a, double param = 1.0)
    {
        Link* tmp = start;
        while (tmp->next != start) {
            if (tmp->next->m == a) {
                tmp->next->m.coef += a.coef * param;
                if (tmp->next->m.coef == 0) {
                    Link* el = tmp->next;
                    tmp->next = tmp->next->next;
                    delete el;
                }
                return;
            }
            else if (tmp->next->m < a) {
                Monom newA(a);
                newA.coef *= param;
                Link* b = new Link(newA, tmp->next);
                tmp->next = b;
                return;
            }
            tmp = tmp->next;
        }
        pushBack(a);
    }
    void pushBack(Monom a) {
        if (a.coef == 0) return;
        Link* el = new Link(a, start);
        end->next = el;
        end = end->next;
    }

    Link* getStart() const { return start;}

    void delFirst() {
        if (start != start->next) {
            Link* tmp = new Link(start->next->m, start->next->next);
            start->next = tmp->next;
            delete tmp;
        }
    }

    void clear() {
        while (start != start->next) {
            delFirst();
        }
    }

    List(const List& p)
    {
        start = new Link(0);
        start->next = start;
        end = start;

        clear();
        Link* tmp = p.start;
        while (tmp->next != p.start) {
            add(tmp->next->m);
            tmp = tmp->next;
        }
    }
    List& operator = (const List& list)
    {
        if (this == &list) {
            return *this;
        }

        clear();
        Link* l = list.start;
        while (l->next != list.start) {
            add(l->next->m);
            l = l->next;
        }
        return *this;
    }

    friend ostream& operator << (ostream& out, List& list) {
        Link* tmp = list.start->next;
        out << tmp->m;
        while (tmp->next != list.start) {
            tmp = tmp->next;
            if (tmp->m.coef >= 0) out << "+" << tmp->m;
            else out << tmp->m;
        }
        return out;
    }

    friend istream& operator >> (istream& in, List& list) {
        list.clear();
        string tmp;
        in >> tmp;
        string sep = "$";
        while (tmp != sep) {
            list.add(atoi(tmp.c_str()));
            in >> tmp;
        }
        return in;
    }


    ~List() {
        clear();
        delete start;
    }
};

