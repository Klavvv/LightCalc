#include <iostream>
#include "equation.cpp"
// #include <stdio.h>
#include <sys/time.h>

using namespace std;

class calculate
{
private:
    string equation;
    long double result;
    double calcTime;
    bool answerExist = false;
    RESULTINFO resultinfo;
    
public:
   void calcOperation(){
        struct timeval begin, end;
        gettimeofday(&begin, 0);

        try{
            result = transformEquation(equation);
            answerExist = true;
            resultinfo.result = result;
        }
        catch(error * err){
            // cout<<"\n<<< Error: "<<err->err_nr<<" >>>"<<endl;
            // cout<<"Opis: "<<err->err_desc<<endl;
            resultinfo.error = true;
            resultinfo.error_desc = err->err_desc;
        }
        catch (...){
            // cout << "\nNiezidentyfikowany blad."<<endl;
            // cout << "Sprawdz poprawnosc wprowadzonego dzialania."<<endl;
            resultinfo.error = true;
            resultinfo.error_desc = "Niezidentifikowany błąd!";
        }


        gettimeofday(&end, 0);
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds + microseconds*1e-6;
        // printf("Czas: %.3f sekund\n", elapsed);
        calcTime = elapsed;

    }
    void showResult(){
        if(answerExist){
            cout<<"\nWynik: "<<setprecision(20)<<result<<endl;
        }
        else{
            cout<<"Wynik: <Brak wyniku>"<<endl;
        }
        
    }
    void showTime(){
        cout<<"\nCzas: "<<setprecision(10)<<calcTime<<" sekund"<<endl;;
    }
    RESULTINFO returnResult(){
        return resultinfo;
    }
    

    calculate(string eqq){
		equation = eqq;
	}
    ~calculate();
};





calculate::~calculate()
{

}
