#include <iostream>
#include <sstream> 
#include <string>
// #include <bits/stdc++.h>
#include <thread>
#include <cmath>
#include <iomanip>
// #include <future>
using namespace std;


class error{
    public:
        int err_nr;
        string err_desc;
        error(int nr, string desc){
            err_nr=nr;
            err_desc=desc;
        };
};



template <size_t N>
auto stringSplit(string (&arr)[N], string eq,char delimiter){
    istringstream ss(eq);
    string token;
    int counter = 0;
    while(getline(ss, token, delimiter)) {
        arr[counter] = token;
        counter++;
    }
}

template <size_t N>
auto equationSplit(string (&arr)[N], string eq,char delimiter){
    int pos1=0, pos2=0, counter=0;

    for(int i = 0; i < eq.length(); i++){
        if(eq[i]=='('){
            int tempc=1;
            i++;
            arr[counter] += '(';
            while(tempc!=0){
                if(eq[i] == ')'){
                    tempc--;
                }
                if(eq[i]=='('){
                    tempc++;
                }
                arr[counter] += eq[i];
                i++;
            }
            if(i < eq.length() && delimiter!='*'){
                if(eq[i]!='*'){
                    counter++;
                }
                else{
                    arr[counter] += '*';
                }
            }
            else if(delimiter=='*'){
                counter++;
            }

        }
        else{
            if(eq[i] == delimiter){
            counter++;   
            }
            else{
                arr[counter] += eq[i];
            }
        }
    }
}

string deleteSpaces(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i] != ' ' && eq[i] != '\\'){
            s += eq[i];
        }
    }
    return s;
}

string minusNormalization(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i] == '-'){
            if(i>0){
                if(eq[i-1]!='*'){
                    s += '+';             
                    
                }
            } 
        }
        s += eq[i];
    }
    return s;
}


template <size_t N>
int equationLength(string (&arr)[N]){
    int x=1;
    while(arr[x]!=""){
        x++;
    }
    return x;
    
}


auto isNum(string s){
    bool test = true;
    for(int i=0;i<s.length();i++){
        if(isdigit(s[i]) == false){
            if(s[i]!='.'){
                if(s[i]!='-'){
                    if(s[i]!=' '){
                        test = false;
                    }
                }
                
            }
        }
    }
    return test;
}

string removeBraces(string eq){
    if(eq[0]=='(' && eq[eq.length()-1]==')'){
        string A[200];
        string B[200];
        equationSplit(A,eq,'+');
        if(equationLength(A) == 1){
            equationSplit(B,eq,'*');
            if(equationLength(B) == 1){
                return eq.substr(1, eq.length()-2);
            }
        }
    }
    return eq;
}


string minusBeforeBracket(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='-' && eq[i+1]=='(' && eq[i-1]!='/'){
            // if(i>0){
            //     if(eq[i-1] != '('){
            //         s+="+";
            //     }
            // }
            s += "-1*";
        }
        else if(eq[i]=='/' && eq[i+1]=='+'){
            s += '/';      
            if(i+2<eq.length()){
                if(eq[i+2]=='-'){
                    s += "-";
                    i += 2;
                }
            }   
        }
        else{
            s+=eq[i];
        }
        
    }
    return s;
}

string removePlus(string eq){
    if(eq[0]=='+'){
        return eq.substr(1,eq.length()-1);
    }
    return eq;
}

// #define PRECISION 0.000000000000000000001
// long double truncate(long double x){
//     x -= fmod(x,PRECISION);
//     return x;
// }
bool isFunction(string fun){
    int n = 12;
    string functions[n] = {"sin","cos","tan","ctg","sqr","log","pow","lna","aco","asi","ata","cbr"};
    if(fun[0]=='-'){
        fun = fun.substr(1,fun.length());
    }
    for(int i=0;i<n;i++){
        if(functions[i] == fun.substr(0,functions[i].length()) ){
            return true;
        }
    }
    return false;
}

long double getFunctionValue(string funct,long double val){
    bool minus = false;
    if(funct[0]=='-'){
        minus = true;
        funct = funct.substr(1,funct.length());
    }
    if("sin"==funct){
        val = sin(val);
        if(minus){
            return -val;
        }
        return val;
    }
    if("cos"==funct){
        val = cos(val);
        if(minus){
            return -val;
        }
        return val;
    }
    if("tan"==funct){
        val = tan(val);
        if( val > 1000000000000000 || val < -1000000000000000 ){
            error* wsk = new error(251,"Dla podanego argumentu wartość tangensa nie istnieje!");
            throw wsk; 
        }
        else{
            if(minus){
                return -val;
            }
            return val;
        }
        
    }
    if("ctg"==funct){
        val = tan(val);
        if( val > 1000000000000000 || val < -1000000000000000 ){
            error* wsk = new error(252,"Dla podanego argumentu wartość cotangensa nie istnieje!");
            throw wsk; 
        }
        else{
            if(minus){
                return -(1/val);
            }
            return 1/val;
        }
    }
    if("sqr"==funct){
        if(val<0){
            error* wsk = new error(261,"Ujemna liczba pod pierwiastkiem kwadratowym!");
            throw wsk;
        }else{
            val = sqrt(val);
            if(minus){
                return -val;
            }
            return val;
        }

    }
    if("log"==funct){
        if(val<0){
            error* wsk = new error(271,"Ujemna liczba w funkcji logarytmicznej!");
            throw wsk;
        }else{
            val = log10(val);
            if(minus){
                return -val;
            }
            return val;
        }
        
    }
    if("lna"==funct){
         if(val<0){
            error* wsk = new error(271,"Ujemna liczba w funkcji logarytmicznej!");
            throw wsk;
        }else{
            val = log(val);
            if(minus){
                return -val;
            }
            return val;
        }
    }
    if("aco"==funct){
        if(val>1 || val<-1){
            error* wsk = new error(253,"Dla podanego argumentu wartość arccosinusa nie istnieje!");
            throw wsk;
        }else{
            val = acos(val);
            if(minus){
                return -val;
            }
            return val;
        }
    }
    if("asi"==funct){
        if(val>1 || val<-1){
            error* wsk = new error(254,"Dla podanego argumentu wartość arcsinusa nie istnieje!");
            throw wsk;
        }else{
            val = asin(val);
            if(minus){
                return -val;
            }
            return val;
        }
    }
    if("ata"==funct){
        if(val>1.57079632679 || val<-1.57079632679){
            error* wsk = new error(255,"Dla podanego argumentu wartość arctangensa nie istnieje!");
            throw wsk;
        }else{
            val = atan(val);
            if(minus){
                return -val;
            }
            return val;
        }
    }
    if("cbr"==funct){
        val = cbrt(val);
        if(minus){
            return -val;
        }
        return val;
    }
    else{
        error* wsk = new error(105,"Błąd wewnętrzny wykrywania funkcji!");
        throw wsk;
    }
}

string getFunctionName(string fun){
    string funct;
    int i=0;

    while(fun[i] != '('){
        funct += fun[i];
        i++;
    }
    return funct;
}

// else if(isFunction(eqArray2[0])){
            //     string funct = getFunctionName(eqArray2[0]);
            //     long double val = calc2(eqArray2[0].substr(funct.length() , eqArray2[0].length()));
            //     sum += getFunctionValue(funct,val);
            // }
// bool multiFunctionDetection(string eq){
//     int p=0;
//     // cout<<"fff: "<<eq;
//     for(int i=0;i<eq.length();i++){
        
//         string k="";
//         k += eq[i];
//         k += eq[i+1];
//         k += eq[i+2];
//         // cout<<k;
//         if(isFunction(k)){
//             p++;
//             i+=4;
//             int tempc=1;
//             while(tempc!=0){
//                 cout<<eq[i];
//                 if(eq[i] == ')'){
//                     tempc--;
//                 }
//                 if(eq[i]=='('){
//                     tempc++;
//                 }
//                 i++;
//             }
//         }
        
//         if(p>1){
//             // cout<<"true";
//             return true;
//         }
//     }
//     // cout<<"false";
//     return false;
// }
bool multiFunctionDetection(string eq){
    int p=0;
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='('){
            i++;
            int tempc=1;
            while(tempc!=0){
                if(eq[i] == ')'){
                    tempc--;
                }
                if(eq[i]=='('){
                    tempc++;
                }
                i++;
            }
        }
        if(eq[i]=='*'){
            p++;
        }
        
        
        if(p>0){
            // cout<<"true";
            return true;
        }
    }
    // cout<<"false";
    return false;
}


long double calc2(string eq){
    long double sum=0;
    string eqArray[200];
    // eq = minusBeforeBracket(eq);
    string test = eq;
    eq = removeBraces(eq);
    while(test!=eq){
        test = eq;
        eq = removeBraces(eq);
    }

    eq = removePlus(eq);
    // cout<<"t: "<<eq<<endl;
    equationSplit(eqArray,eq,'+');
    int eqLen=equationLength(eqArray);
    
    if(eqLen==1){
        string eqArray2[200];
        equationSplit(eqArray2,eqArray[0],'*');
        int eqLen2=equationLength(eqArray2);
        if(eqLen2==1){
            if(isFunction(eqArray2[0])){
                string funct = getFunctionName(eqArray2[0]);
                if(funct!="pow"){
                    long double val = calc2(eqArray2[0].substr(funct.length() , eqArray2[0].length()));
                    sum += getFunctionValue(funct,val);
                }else{
                    string mini = eqArray2[0].substr(funct.length()+1 , eqArray2[0].length()-2);
                    string aaaa, bbbb;
                    bool tr = false;
                    for(int g=0;g<mini.length();g++){
                        if(mini[g] == ';'){
                            tr = true;
                            g++;
                        }
                        if(tr){
                            bbbb += mini[g];
                        }
                        else{
                            aaaa += mini[g];
                        }
                    }
                    long double val1 = calc2(aaaa), val2 = calc2(bbbb);
                    sum += pow(val1,val2);

                }
                
                
            }
            else{
                sum += stod(eqArray2[0]);
            }
            
        }
        else{
            long double subsum = 1;
            for(int i=0; i<eqLen2;i++){
                if(isNum(eqArray2[i])){
                        subsum *= stod(eqArray2[i]);
                    }
                else if(isFunction(eqArray2[i])){
                        string funct = getFunctionName(eqArray2[i]);
                        if(funct!="pow"){
                            long double val = calc2(eqArray2[i].substr(funct.length() , eqArray2[i].length()));
                            subsum *= getFunctionValue(funct,val);
                        }else{
                            string mini = eqArray2[i].substr(funct.length()+1 , eqArray2[i].length()-1);
                            string aaaa, bbbb;
                            bool tr = false;
                            // cout<<mini<<endl;
                            for(int g=0;g<mini.length();g++){
                                if(mini[g] == ';'){
                                    tr = true;
                                    g++;
                                }
                                if(tr){
                                    bbbb += mini[g];
                                }
                                else{
                                    aaaa += mini[g];
                                }
                            }
                            long double val1 = calc2(aaaa), val2 = calc2(bbbb);
                            // cout<<"v1: "<<val1<<" v2: "<<val2<<endl;
                            subsum *= pow(val1,val2);

                        }
                        
                        
                }
                else{
                        // subsum *= calc2(eqArray2[i]);
                        subsum *= calc2(eqArray2[i]);
                    }  
                
            }
            sum += subsum;
        }
    }
    else{
        for(int i=0; i<eqLen;i++){ 
            if(isNum(eqArray[i])){
                    sum += stod(eqArray[i]);
            }
            else if(isFunction(eqArray[i])){
                string funct = getFunctionName(eqArray[i]);
                if(funct!="pow"){
                            if(multiFunctionDetection(eqArray[i])){
                                sum += calc2(eqArray[i]);
                            }
                            else{
                                long double val = calc2(eqArray[i].substr(funct.length() , eqArray[i].length()));
                                sum += getFunctionValue(funct,val);
                            }
                            
                }else{
                            string mini = eqArray[i].substr(funct.length()+1 , eqArray[i].length()-1);
                            string aaaa, bbbb;
                            bool tr = false;
                            // cout<<mini<<endl;
                            for(int g=0;g<mini.length();g++){
                                if(mini[g] == ';'){
                                    tr = true;
                                    g++;
                                }
                                if(tr){
                                    bbbb += mini[g];
                                }
                                else{
                                    aaaa += mini[g];
                                }
                            }
                            long double val1 = calc2(aaaa), val2 = calc2(bbbb);
                            // cout<<"v1: "<<val1<<" v2: "<<val2<<endl;
                            sum += pow(val1,val2);

                        }
            }
            else{
                    sum += calc2(eqArray[i]);
            }     
        }
    }
    // cout<<"sum: "<<sum<<endl;

    return round(sum*1000000000000000)/1000000000000000;
}




string divisionNormalization(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='/'){
            i++;
            bool minus=false;
            string divi;
            
            if(eq[i]=='-' && eq[i+1]=='('){
                divi += "-1*";
                i++;
            }
            if(eq[i]=='('){
                divi += '(';
                i++;
                int tempc=1;
                while(tempc!=0){
                    if(eq[i] == ')'){
                        tempc--;
                    }
                    if(eq[i]=='('){
                        tempc++;
                    }
                    divi += eq[i];
                    i++;
                }
            }

            
            else{
                if(eq[i]=='-'){
                    divi += '-';
                    i++;
                }
                while(isdigit(eq[i]) || eq[i]=='.'){
                    divi += eq[i];
                    i++;
                }
            }
            long double mian = calc2(divi);
            if(abs(mian)*1000000000000000<1){
                error* wsk = new error(201,"Wykryto dzielenie przez zero!");
                throw wsk;
            }

            long double w = 1 / mian;
            ostringstream os;
            os << setprecision(20);
            os << w;
            if(eq[i]=='/'){
                s += '*' + os.str();
                i--;
            }
            else{
                s += '*' + os.str() + eq[i];
            }
            
        }
        else{
            s += eq[i];
        }       
    }   
    return s;
}


auto ct(string eq, long double *sumka, error *errk){
    try{
            *sumka += calc2(eq);
    }
    catch(error * err){
        // cout<<"\n<<< Error: "<<err->err_nr<<" >>>"<<endl;
        // cout<<"Opis: "<<err->err_desc;
        errk->err_nr = err->err_nr;
        errk->err_desc = err->err_desc;
    }
    catch (...){
        // cout << "\nNiezidentyfikowany blad."<<endl;
        // cout << "Sprawdz poprawnosc wprowadzonego dzialania."<<endl;
        errk->err_nr=999;
        errk->err_desc="Niezidentyfikowany błąd!";
    }
    
}



string constantsToValues(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        // liczba pi
        if(eq[i]=='p' && eq[i+1]=='i'){
            bool cos = true;
            if(eq[i-1]==')' || isdigit(eq[i-1])){
                s += "*3.141592653589793238462643383279";
                cos = false;
            }
            if(eq[i+2]=='(' || isdigit(eq[i+2])){
                s += "3.141592653589793238462643383279*";
                cos = false;
            }
            if(cos){
                s += "3.141592653589793238462643383279";
            }
                
            
            i+=1;
        }
        
        // liczba eulera
        else if(eq[i]=='e'){
            bool cos = true;
            if(eq[i-1]==')' || isdigit(eq[i-1])){
                s += "*2.7182818284590452353602874713";
                cos = false;
            }
            if(eq[i+1]=='(' || isdigit(eq[i+1])){
                s += "2.7182818284590452353602874713*";
                cos = false;
            }
            if(cos){
                s += "2.7182818284590452353602874713";
            }
        }
        
        else{
            s += eq[i];
        }
    }
    return s;
}


string operatorFix(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='-' && eq[i+1]=='-'){
            if(i>0){
                s += '+';
            }
            i++;
        }
        else if( eq[i]=='+' && eq[i+1]=='-' || eq[i]=='-' && eq[i+1]=='+'){
            s += '-';
            i++;
        }
        else if(eq[i]=='+' && eq[i+1]=='+'){
            if(i>0){
                s += '+';
            }
            i++;
        }
        else{
            if(i == 0){
                if(eq[i]!='+'){
                    s += eq[i];
                }
            }
            else{
                s += eq[i];
            }
            
        }

    }

    return s;
}



string commaToDot(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]==','){
            s += '.';
        }
        else{
            s += eq[i];
        }
    }
    return s;
}

string deleteWhitespace(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]!='\n' && eq[i]!='\r' && eq[i]!='\t' && eq[i]!='\v' && eq[i]!='\f' && eq[i]!=' '  && eq[i]!='\\' ){
            s+=eq[i];
        }

    }
    return s;
}


void isEverythingOk(string eq){
    // liczba nawiasów          211
    int bracketRight=0,bracketLeft=0,dots=0;
    for(int i=0; i<eq.length();i++){
        if(eq[i]=='('){
            bracketLeft++;
        }
        else if(eq[i]==')'){
            bracketRight++;
        }
        // kropki 1
        if(eq[i]=='.' && eq[i+1]=='.'){
            error* wsk = new error(212,"Nieprawidłowa liczba kropek obok siebie!");
            throw wsk;
        }

    }
    if(bracketLeft != bracketRight){
        error* wsk = new error(211,"Nieprawidłowa liczba nawiasów!");
        throw wsk;
    }
    // kropki 2
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='.' && isdigit(eq[i-1])){
            i++;
            while(isdigit(eq[i])){
                i++;
            }
            if(eq[i]=='.'){
                error* wsk = new error(213,"Wykryto kropkę w nieprawidłowym miejscu!");
                throw wsk;
            }
        }
    }


    // samotne znaki

    // niezidentyfikowane funkcje

    // niezidentyfikowane stałe
    

}

string functionDivisionNormalization(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i]=='/'){
            s += '/';
            i++;
            string k;
            if(eq[i]=='-'){
                k += '-';
                i+=1;
            }
            if(eq[i]=='s' && eq[i+1]=='i' && eq[i+2]=='n'){
                s += '('+k+"sin(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='c' && eq[i+1]=='o' && eq[i+2]=='s'){
                s += '('+k+"cos(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='c' && eq[i+1]=='t' && eq[i+2]=='g'){
                s += '('+k+"ctg(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='t' && eq[i+1]=='a' && eq[i+2]=='n'){
                s += '('+k+"tan(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='l' && eq[i+1]=='o' && eq[i+2]=='g'){
                s += '('+k+"log(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='p' && eq[i+1]=='o' && eq[i+2]=='w'){
                s += '('+k+"pow(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='s' && eq[i+1]=='q' && eq[i+2]=='r'){
                s += '('+k+"sqr(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='l' && eq[i+1]=='n' && eq[i+2]=='a'){
                s += '('+k+"lna(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='a' && eq[i+1]=='c' && eq[i+2]=='o'){
                s += '('+k+"aco(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='a' && eq[i+1]=='s' && eq[i+2]=='i'){
                s += '('+k+"asi(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='a' && eq[i+1]=='t' && eq[i+2]=='a'){
                s += '('+k+"ata(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else if(eq[i]=='c' && eq[i+1]=='b' && eq[i+2]=='r'){
                s += '('+k+"cbr(";
                i += 3;
                    if(eq[i]=='('){
                        i++;
                        int tempc=1;
                        while(tempc!=0){
                            if(eq[i] == ')'){
                                tempc--;
                            }
                            if(eq[i]=='('){
                                tempc++;
                            }
                            s += eq[i];
                            i++;
                        }
                    }
                s+=')';
                s+=eq[i];
            }
            else{
                s += k+eq[i];
            }
        }
        else{
            s += eq[i];
        }
    }
    return s;
}


string multiplicationBrackets(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i] == ')' && eq[i+1] == '('){
            s += ")*(";
            i++;
        }
        else if(isdigit(eq[i]) && eq[i+1] == '(' && eq[i-1] != ')'){
            s += eq[i];
            s += "*(";
            i++;
        }
        else if(eq[i] == ')' && isdigit(eq[i+1]) && eq[i+2] != '('){
            s += ")*";
            s += eq[i+1];
            i++;
        }
        else if(eq[i]==')' && isdigit(eq[i+1]) && eq[i+2]=='('){
            s += ")*";
            s += eq[i+1];
            s += "*(";
            i+=2;
        }
        else if(isalpha(eq[i]) && eq[i+1]=='(' || isalpha(eq[i]) && isdigit(eq[i+1]) ){
            s += eq[i];
            if(i>=2){
                string a;
                a += eq[i-2];
                a += eq[i-1];
                a += eq[i];
                if(!isFunction(a)){
                    s += '*';
                }
            }
            s += eq[i+1];
            i += 1; 
        }
        else if(isalpha(eq[i+1]) && eq[i]==')' || isalpha(eq[i+1]) && isdigit(eq[i]) ){
            s += eq[i];
            s += '*';
            s += eq[i+1];
            i += 1; 
        }
        else{
            s += eq[i];
        }
    }
    return s;
}

string nameNormalization(string eq){
    string s;
    for(int i=0;i<eq.length();i++){
        if(eq[i-1] != 'c' && eq[i] == 't' && eq[i+1] == 'g'){
            s += "tan";
            i+=1;
        }
        else if(eq[i] == 's' && eq[i+1] == 'q' && eq[i+2] == 'r' && eq[i+3] == 't'){
            s += "sqr";
            i+=3;
        }
        else if(eq[i] == 'c' && eq[i+1] == 't' && eq[i+2] == 'a' && eq[i+3] == 'n'){
            s += "ctg";
            i+=3;
        }
        else if(eq[i] == 'l' && eq[i+1] == 'n' && eq[i+2] != 'a'){
            s += "lna";
            i+=1;
        }
        else if(eq[i] == 'a' && eq[i+1] == 's' && eq[i+2] == 'i' && eq[i+3] == 'n'){
            s += "asi";
            i+=3;
        }
        else if(eq[i] == 'a' && eq[i+1] == 'c' && eq[i+2] == 'o' && eq[i+3] == 's'){
            s += "aco";
            i+=3;
        }
        else if(eq[i] == 'a' && eq[i+1] == 't' && eq[i+2] == 'a' && eq[i+3] == 'n'){
            s += "ata";
            i+=3;
        }
        else if(eq[i] == 'c' && eq[i+1] == 'b' && eq[i+2] == 'r' && eq[i+3] == 't'){
            s += "cbr";
            i+=3;
        }
        else if(eq[i] == 'a' && eq[i+1] == 'r' && eq[i+2] == 'c' && eq[i+3] == 's' && eq[i+4] == 'i' && eq[i+5] == 'n'){
            s += "asi";
            i+=5;
        }
        else if(eq[i] == 'a' && eq[i+1] == 'r' && eq[i+2] == 'c' && eq[i+3] == 'c' && eq[i+4] == 'o' && eq[i+5] == 's'){
            s += "aco";
            i+=5;
        }
        else if(eq[i] == 'a' && eq[i+1] == 'r' && eq[i+2] == 'c' && eq[i+3] == 't' && eq[i+4] == 'a' && eq[i+5] == 'n'){
            s += "ata";
            i+=5;
        }
        else if(eq[i] == 'a' && eq[i+1] == 'r' && eq[i+2] == 'c' && eq[i+3] == 't' && eq[i+4] == 'g'){
            s += "ata";
            i+=4;
        }

        else{
            s += eq[i];
        }
    }








    return s;
}

