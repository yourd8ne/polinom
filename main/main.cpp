#include <iostream>
#include "List.h"
#include "Polinom.h"

using namespace std;

int main()
{

    Polinom p1("3+x^2yz-y^6");
    Polinom p2("x^2yz-3+xyz");
    
    Polinom res(p1 + p2);
    cout << res;
    return 0;
}
