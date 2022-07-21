#include <iostream>
#include <sstream> 
#include "additional.cpp"
// #include <typeinfo>
#include <iomanip>
#include <thread>
// #include <future>
// #include <ctime>
using namespace std;

struct RESULTINFO{
    double result=0;
    bool error = false;
    string error_desc = "";
};



long double transformEquation(string eq){
    // eq = deleteSpaces(eq);
    // cout<<" dS: "<<eq<<endl;
    eq = deleteWhitespace(eq);
    eq = nameNormalization(eq);
    // cout<<" nN: "<<eq<<endl; 
    eq = functionDivisionNormalization(eq);
    // cout<<"fDN: "<<eq<<endl;
    eq = multiplicationBrackets(eq);
    // cout<<" mB: "<<eq<<endl;
    eq = operatorFix(eq);
    // cout<<" oF: "<<eq<<endl;
    eq = commaToDot(eq);
    // cout<<"cTD: "<<eq<<endl;
    eq = constantsToValues(eq);
    // cout<<"cTV: "<<eq<<endl;
    eq = minusNormalization(eq);
    // cout<<" mN: "<<eq<<endl;
    eq = minusBeforeBracket(eq);
    // cout<<"mBB: "<<eq<<endl;
    eq = divisionNormalization(eq);
    // cout<<" dN: "<<eq<<endl;
    isEverythingOk(eq);

    string eqArray[200];
    equationSplit(eqArray,eq,'+');
    int eqLen=equationLength(eqArray);

    thread t[4];
    long double sumka[eqLen] = {0.0};
    long double finalSum = 0.0;

    error errk(999,"none");
    
    
    if(eqLen<4){
        for(int i=0;i<eqLen;i++){
            t[i] = thread(ct, eqArray[i], &(sumka[i]), &(errk));
        }

        for(int i=0;i<eqLen;i++){
            t[i].join();
            finalSum += sumka[i];
        }
    }
    else{
        int a=3;
        while(a<eqLen){
            t[0] = thread(ct, eqArray[a-3], &(sumka[a-3]), &(errk));
            t[1] = thread(ct, eqArray[a-2], &(sumka[a-2]), &(errk));
            t[2] = thread(ct, eqArray[a-1], &(sumka[a-1]), &(errk));
            t[3] = thread(ct, eqArray[a], &(sumka[a]), &(errk));
            t[0].join();
            t[1].join();
            t[2].join();
            t[3].join();
            finalSum += sumka[a-3]+sumka[a-2]+sumka[a-1]+sumka[a];
            a+=4;
        }
        for(int i=a-3;i<eqLen;i++){
            t[i%4] = thread(ct, eqArray[i], &(sumka[i]), &(errk));
        }

        for(int i=a-3;i<eqLen;i++){
            t[i%4].join();
            finalSum += sumka[i];
        }
        

    }
    if(errk.err_desc != "none"){
        error* wsk = new error(errk.err_nr,errk.err_desc);
        throw wsk;
    }

    
    // cout<<"\nWynik: "<<setprecision(20)<<finalSum<<endl;


    return finalSum;
}

