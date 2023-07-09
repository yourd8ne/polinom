#pragma once

#include <cmath>
#include "iostream"
#include "sstream"
using namespace std;
const int p = 21;
const int deg = 10;

struct Monom {
    double coef;
    int s;
    Monom(double _c = 1.0, int i = 0, int j = 0, int k = 0) : coef(_c) {
        s = i + deg + (j + deg) * p + (k + deg) * p * p;
    }
    int getI() { return s % p - deg; }
    int getJ() { return (s / p) % p - deg; }
    int getK() { return s / p / p - deg; }

    
    int calculate(int _x, int _y, int _z) {
        int res = coef;
        res *= pow(_x, getI()) * pow(_y, getJ()) * pow(_z, getK());
        return res;
    }
    
    bool isEqual(Monom& m) {
        if (*this == m) return true;

        if (coef == m.coef && s == m.s) return true;
        else return false;
    }

    Monom operator * (Monom& a);

    bool operator == (Monom& a);
    bool operator != (Monom& a);

    bool operator > (Monom& a);
    bool operator < (Monom& a);
    bool operator >= (Monom& a);
    bool operator <= (Monom& a);

    friend ostream& operator << (ostream& out, Monom& m);
    friend istream& operator >> (istream& in, Monom& m);
};


Monom Monom::operator*(Monom& a) {
    int i = getI() + a.getI(); if (i < -deg || i > deg) throw - 1;
    int j = getJ() + a.getJ(); if (j < -deg || j > deg) throw - 1;
    int k = getK() + a.getK(); if (k < -deg || k > deg) throw - 1;

    Monom m;
    m.coef = coef * a.coef;
    m.s = i + deg + (j + deg) * p + (k + deg) * p * p;

    return m;
}

bool Monom::operator==(Monom& a) {
    if (s == a.s) return true;
    else return false;
}

bool Monom::operator!=(Monom& a) {
    if (s == a.s) return false;
    else return true;
}

bool Monom::operator>(Monom& a) {
    if (*this == a) return false;

    if (s > a.s) return true;
    else return false;
}

bool Monom::operator<(Monom& a) {
    if (*this == a) return false;

    if (s < a.s) return true;
    else return false;
}

bool Monom::operator>=(Monom& a) {
    if (*this == a) return true;

    if (s >= a.s) return true;
    else return false;
}

bool Monom::operator<=(Monom& a) {
    if (*this == a) return true;

    if (s <= a.s) return true;
    else return false;
}

istream& operator >> (istream& in, Monom& m) {
    string str;
    in >> str;
    m.s = 0;
    m.coef = 1.0;
    bool ch = false;
    bool x = false, y = false, z = false;
    int s = 0, st = 0, pSt = 0;
    string t = "";
    for (const char& el : str) {
        if (el == '^') {
            t = "";
            continue;
        }
        if (el == 'x') {
            pSt = st;
            st = 1;
            ch = true; x = true;
        }
        if (el == 'y') {
            pSt = st;
            st = 2;
            ch = true; y = true;
        }
        if (el == 'z') {
            pSt = st;
            st = 3;
            ch = true; z = true;
        }
        if (!ch) {
            t += el;
        }
        else {
            if (t.length() == 0 || t == "+") t = "1";
            if (t == "-") t = "-1";
            if (pSt == 0) {
                m.coef = stod(t);
                if (m.coef == 0) {
                    m.s = 0;
                    return in;
                }
            }
            else {
                if (stoi(t) > deg) {
                    cout << "It is impossible to create a monomial with a degree of " << t << endl;
                    throw - 1;
                };
                s += (stoi(t) + deg) * pow(p, pSt - 1);
            }
            t = "";
            ch = false;
        }
    }
    if (t.length() == 0) t = "1";
    if (stoi(t) > deg) {
        cout << "It is impossible to create a monomial with a degree of " << t << endl;
        throw - 1;
    };
    if (st == 0) {
        m.coef = stod(t);
    }
    if (st > 0) {
        s += (stoi(t) + deg) * pow(p, st - 1);
        m.s = s;
    }

    if (!x) m.s += (0 + deg) * pow(p, 0);
    if (!y) m.s += (0 + deg) * pow(p, 1);
    if (!z) m.s += (0 + deg) * pow(p, 2);

    return in;
}

ostream& operator << (ostream& out, Monom& m) {
    if (m.coef == -1.0) out << "-";
    else if (m.coef != 1.0 && m.coef != -1.0) out << m.coef;

    int t;
    t = m.getI(); if (t == 1) out << "x"; else if (t != 0) out << "x^" << t;
    t = m.getJ(); if (t == 1) out << "y"; else if (t != 0) out << "y^" << t;
    t = m.getK(); if (t == 1) out << "z"; else if (t != 0) out << "z^" << t;
    return out;
}