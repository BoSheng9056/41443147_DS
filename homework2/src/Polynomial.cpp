#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

class Polynomial;

class Term{
    friend class Polynomial;
    friend ostream& operator<<(ostream& os,Polynomial& poly);
    friend istream& operator>>(istream& is,Polynomial& poly);
private:
    float coef;
    int exp;
};

class Polynomial{
private:
    Term *termArray;
    int capacity;
    int terms;

public:
    Polynomial():capacity(4),terms(0){
        termArray= new Term[capacity];
    }

    ~Polynomial(){
        delete[] termArray;
    }

    void newTerm(const float theCoef, const int theExp);
    void Add(const Polynomial &b, Polynomial &c);
    void Mult(const Polynomial &b, Polynomial &c);
    float Eval(float x);

    friend ostream& operator<<(ostream& os,Polynomial& poly);
    friend istream& operator>>(istream& is,Polynomial& poly);
};

// ******newTerm
void Polynomial::newTerm(const float theCoef, const int theExp){
    if (theCoef==0) return;
    if (terms==capacity){
        capacity*=2;
        Term *temp= new Term[capacity];
        copy(termArray,termArray+terms,temp);
        delete[] termArray;
        termArray=temp;
    }
    termArray[terms].coef=theCoef;
    termArray[terms++].exp=theExp;
}

// *Add
void Polynomial::Add(const Polynomial &b,Polynomial &c){
    int aPos=0, bPos=0;
    while ((aPos<terms)&&(bPos<b.terms)){
        if(termArray[aPos].exp==b.termArray[bPos].exp){
            float t =termArray[aPos].coef+b.termArray[bPos].coef;
            if(t) c.newTerm(t,termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if(termArray[aPos].exp<b.termArray[bPos].exp){
            c.newTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
        else{
            c.newTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
    }
    for(;aPos<terms;aPos++) c.newTerm(termArray[aPos].coef,termArray[aPos].exp);
    for(;bPos<b.terms;bPos++) c.newTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
}

// **Mult
void Polynomial::Mult(const Polynomial &b,Polynomial &c){
    for(int i=0;i<terms;i++){
        for(int j=0;j<b.terms;j++){
            float coef = termArray[i].coef*b.termArray[j].coef;
            int exp = termArray[i].exp+b.termArray[j].exp;
            
            bool found=false;
            for(int k=0;k<c.terms;k++){
                if(c.termArray[k].exp==exp){
                    c.termArray[k].coef+=coef;
                    found=true;
                    break;
                }
            }
            if(!found) {
                c.newTerm(coef,exp);
            }
        }
    }
}

// ***Eval
float Polynomial::Eval(float x){
    float ans=0;
    for(int i=0;i<terms;i++){
        ans+=termArray[i].coef*pow(x, termArray[i].exp);
    }
    return ans;
}

// ******operator	輸入 
istream& operator>>(istream& is,Polynomial& poly){
    string line;
    while(getline(is, line)){
        if(!line.empty()) break;
    }

    stringstream ss(line);
    float coef;
    int exp;

    while(ss>>coef>>exp){
        poly.newTerm(coef,exp);
    }

    return is;
}

// ******operator	輸出 
ostream& operator<<(ostream& os,Polynomial& poly){
    if (poly.terms==0) {
        os <<"0";
        return os;
    }

    for(int i=0;i<poly.terms;i++){
        float c =poly.termArray[i].coef;
        int e =poly.termArray[i].exp;

        if(i>0)os<<" ";

        if(e==0){
            os<<c;
        }else if(e==1){
            os<<c<<"X";
        }else{
            os<<c<<"X^"<<e;
        }
    }
    return os;
}

int main(){
    Polynomial p1,p2;

    cout << "=== 輸入多項式 P1 (輸入 係數 指數  案Enter結束) ===\n";
    cin >> p1;

    cout << "\n=== 輸入多項式 P2 (輸入 係數 指數 案Enter結束) ===\n";  
    cin >> p2;

    cout << "\n-----------------------------------" << endl;
    cout << "P1 = " << p1 << endl;
    cout << "P2 = " << p2 << endl;
    cout << "-----------------------------------" << endl;

    int choice;
    do{
        cout << "\n==============================\n請選擇要執行的項目：\n";
        cout << "1. 多項式相加 (P1 + P2)\n";
        cout << "2. 多項式相乘 (P1 * P2)\n";
        cout << "3. 代入 x 計算值\n";
        cout << "0. 結束程式\n";
        cout << "請輸入選項 (0-3): ";
        cin >> choice;

        switch(choice){
            case 1:{
                Polynomial sum;
                p1.Add(p2, sum);
                cout << "\n>>> P1 + P2 = "<<sum<<"\n";
                break;
            }
            case 2:{
                Polynomial prod;
                p1.Mult(p2,prod);
                cout <<"\n>>> P1 * P2 = "<<prod<<"\n";
                break;
            }
            case 3:
                float x;
                cout <<"\n請輸入要代入的x值: ";
                cin >> x;
                cout <<"P1(" << x << ") = "<<p1.Eval(x)<<"\n";
                cout <<"P2(" << x << ") = "<<p2.Eval(x)<<"\n";
                break;
            
            case 0:
                cout <<"\n程式已結束。\n";
                break;
            default:
                cout <<"\n無效的選項，請重新選擇\n";
                break;
        }
    } while(choice!=0);

    return 0;
}
