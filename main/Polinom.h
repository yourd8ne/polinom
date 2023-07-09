#pragma once

#include <cmath>
#include "iostream"
#include "sstream"
#include "Monom.h"
#include "List.h"

using namespace std;

class Polinom {
    List list;
public:
    Polinom() {
        list = List();
    };
    Polinom(string str) {
        istringstream p_in(str);
        p_in >> *this;
    }
    Polinom(Polinom* p) {
        list = p->list;
    }
    int calculate(int _x, int _y, int _z);
    List getList() { return list; }

    friend ostream& operator << (ostream& out, Polinom& p);
    friend istream& operator >> (istream& out, Polinom& p);

    Polinom operator + (const Polinom& p);
    Polinom operator + (const Monom& m);
    Polinom operator - (const Polinom& p);
    Polinom operator - (const Monom& m);

    template<typename T>
    Polinom operator * (const T& a);
    
};


int Polinom::calculate(int _x, int _y, int _z) {
    int res = 0;
    for (Link* el = list.getStart()->next; el != list.getStart(); el = el->next) {
        res += el->m.calculate(_x, _y, _z);
    }
    return res;
}

ostream& operator << (ostream& out, Polinom& p) {
    out << p.list;
    return out;
}

istream& operator >> (istream& in, Polinom& p) {
    string str;
    in >> str;
    string t = "";
    Monom m;
    for (const char& el : str) {
        if ((el == '-' || el == '+') && t.length() > 0) {
            istringstream m_in(t);
            if (el == '-') t = "-";
            else t = "";
            m_in >> m;

            p.list.add(m);
            continue;
        }
        if (el != ' ') t += el;
    }
    istringstream m_in(t);
    m_in >> m;
    p.list.add(m);
    return in;
}

Polinom Polinom::operator+(const Polinom& p) {
    Polinom newP;

    Link* tList = list.getStart();
    Link* pList = p.list.getStart();

    while (tList->next != list.getStart() && pList->next != p.list.getStart()) {
        if (tList->next->m > pList->m) {
            newP.list.pushBack(tList->next->m);
            tList = tList->next;
        }
        else if (tList->next->m < pList->next->m) {
            newP.list.pushBack(pList->next->m);
            pList = pList->next;
        }
        else if (tList->next->m == pList->next->m) {
            Monom m;
            m.coef = pList->next->m.coef + tList->next->m.coef;
            m.s = pList->next->m.s;
            newP.list.pushBack(m);
            tList = tList->next;
            pList = pList->next;
        }
    }

    return newP;
}

Polinom Polinom::operator+(const Monom& m) {
    Polinom newP(*this);

    newP.list.add(m);
    return newP;
}

Polinom Polinom::operator-(const Polinom& p) {
    Polinom newP;

    Link* tList = list.getStart();
    Link* pList = p.list.getStart();

    Monom m;
    while (tList->next != list.getStart() && pList->next != p.list.getStart()) {
        if (tList->next->m > pList->m) {
            newP.list.pushBack(tList->next->m);
            tList = tList->next;
        }
        else if (tList->next->m < pList->next->m) {
            m.coef = -pList->next->m.coef;
            m.s = pList->next->m.s;
            newP.list.pushBack(m);
            pList = pList->next;
        }
        else if (tList->next->m == pList->next->m) {
            m.coef = tList->next->m.coef - pList->next->m.coef;
            m.s = pList->next->m.s;
            newP.list.pushBack(m);
            tList = tList->next;
            pList = pList->next;
        }
    }
    return newP;
}

Polinom Polinom::operator-(const Monom& m) {
    Polinom newP(*this);

    newP.list.add(m, -1);
    return newP;
}

template <typename T>
Polinom Polinom::operator*(const T& a) {
    for (Link* m = list.getStart()->next; m != list.getStart(); m = m->next) {
        m->m.coef *= a;
    }
}

template<>
Polinom Polinom::operator*(const Polinom& a) {
    Polinom p;

    for (Link* i = list.getStart()->next; i != list.getStart(); i = i->next) {
        for (Link* j = a.list.getStart()->next; j != a.list.getStart(); j = j->next) {
            try {
                p.list.add(i->m * j->m);
            }
            catch (string err) {
                cout << err << endl;
            }
        }
    }
    return p;
}
