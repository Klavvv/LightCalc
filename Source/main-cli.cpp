#include <iostream>
#include "calculate.h"

using namespace std;


int main(int argc, char const *argv[])
{
    // while(true){
        calculate a("2/0");
        a.calcOperation();
        a.showResult();
        a.showTime();
        // long double wynik=a.returnResult();
        // cout<<endl<<wynik;
        cout<<"\n\n\n";
    // }


    // int k;
    // cin>>k;

    return 0;
}
