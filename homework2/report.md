# 41443147

作業二

## 解題說明

1. 實作Polynomial類別的ADT、如作業二圖1和圖2中的private資料成員。
2. 寫一個 C++ 函式用來輸出和輸入多項式。函式可多載<< 跟 >> 運算子。
3. 實作Add、Mult、Eval三個功能。

### 解題策略

#### 1. 使用動態記憶體配置
- 使用termArray存非零項，當原儲存空間(capacity=4)不夠使用時，執行 _newTerm()_ ，用意是將原儲存空間(capacity)*2，增加兩倍，後透過copy把原本的資料複製到新的termArray裡。
#### 2.運算子多載與輸入處理
##### A. 輸入運算子
- 利用 _is >> ws_ 先自動清除輸入的空白跟換行，再透過 _getline_ 讀入整行文字
- 將文字轉為 _stringstream_ ，利用 _ss >> coef >> exp_ 迴圈持續讀入"係數"、"指數"，並且呼叫 _newTerm()_ 建立多項式。
##### B. 輸出運算子
- 根據指數e分為三種輸出
    - $e=0$ : 輸出 $c$ (常數項)
    - $e=1$ : 輸出 $cX$ (一次方)
    - $e>1$ : 輸出 $cX^e$ (比一次多的次方)

## 程式實作

以下為程式碼：

```cpp
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

// class**********
class Polynomial;

class Term{
    friend class Polynomial;
    friend ostream& operator<<(ostream& os,const Polynomial& poly);
    friend istream& operator>>(istream& is,Polynomial& poly);
private:
    float coef; // 係數 
    int exp;    // 指數 
};

class Polynomial{
private:
    Term *termArray;    // 動態陣列，放非零項 
    int capacity;   // 初始容量 
    int terms;  // 目前存非零項個數 

public:
    // 建構子 
    Polynomial():capacity(4),terms(0){
        termArray= new Term[capacity];
    }

    // 解構子 
    ~Polynomial(){
        delete[] termArray;
    }

    // 複製建構子
    Polynomial(const Polynomial &b){
        capacity=b.capacity;
        terms=b.terms;
        termArray=new Term[capacity];
        for(int i=0;i<terms;i++){
            termArray[i]=b.termArray[i];
        }
    }

    // 複製指派運算子
    Polynomial& operator=(const Polynomial &b){
        if(this!= &b){
            delete[] termArray;	//釋放舊記憶體
            capacity=b.capacity;
            terms=b.terms;
            termArray=new Term[capacity];	//配置新記憶體
            for(int i=0;i<terms;i++){	 
                termArray[i]=b.termArray[i];
            }
        }
        return *this;
    }

    // 函式宣告
    void newTerm(const float theCoef, const int theExp);
    Polynomial Add(const Polynomial &b);
    Polynomial Mult(const Polynomial &b);
    float Eval(float x);

    // 運算子多載 friend宣告 
    friend ostream& operator<<(ostream& os,const Polynomial& poly);
    friend istream& operator>>(istream& is,Polynomial& poly);
};
// **********class 


// ******newTerm
void Polynomial::newTerm(const float theCoef,const int theExp){
    if(theCoef==0) return;
    if(terms==capacity){
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
Polynomial Polynomial::Add(const Polynomial &b){
    Polynomial c;	//放多項式的結果 
    int aPos=0,bPos=0;
    while ((aPos<terms)&&(bPos<b.terms)){
    	//指數相同係數相加 
        if(termArray[aPos].exp==b.termArray[bPos].exp){
            float t=termArray[aPos].coef+b.termArray[bPos].coef;
            if(t) c.newTerm(t,termArray[aPos].exp);
            aPos++; bPos++;
        }
        //多項式 b 的指數較大	放入多項式 b 的項 
        else if(termArray[aPos].exp<b.termArray[bPos].exp){
            c.newTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
        //多項式 a 的指數較大	放入多項式 a 的項
        else{
            c.newTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
    }
    for(;aPos<terms;aPos++) c.newTerm(termArray[aPos].coef,termArray[aPos].exp);	//將 a 剩餘的項放入 
    for(;bPos<b.terms;bPos++) c.newTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);	//將 b 剩餘的項放入
    return c;
}

// **Mult
Polynomial Polynomial::Mult(const Polynomial &b){
    Polynomial c; // 放多項式的結果 
    for(int i=0;i<terms;i++){
        for(int j=0;j<b.terms;j++){
            float coef =termArray[i].coef*b.termArray[j].coef;
            int exp =termArray[i].exp+b.termArray[j].exp;
            
            // 檢查結果中有無已有相同指數的項，有的話把係數加起來 
            bool found=false;
            for(int k=0;k<c.terms;k++){
                if(c.termArray[k].exp==exp){
                    c.termArray[k].coef+=coef;
                    found=true;
                    break;
                }
            }
            // 如果是新的指數項，新增到結果裡面 
            if(!found) {
                c.newTerm(coef,exp);
            }
        }
    }
    return c;
}

// ***Eval	 
float Polynomial::Eval(float x){
    float ans=0;
    for(int i=0;i<terms;i++){
        ans+=termArray[i].coef*pow(x, termArray[i].exp);
    }
    return ans;
}

// ******operator   輸入 
istream& operator>>(istream& is,Polynomial& poly){
    string line;
    if (getline(is>>ws, line)){
        stringstream ss(line);
        float coef;
        int exp;
        while(ss>>coef>>exp){	//只要有成對的coef、exp就繼續執行 
            poly.newTerm(coef,exp);
        }
    }
    return is;
}

// ******operator   輸出 
ostream& operator<<(ostream& os, const Polynomial& poly){
    if (poly.terms==0){
        os<<"0";
        return os;
    }

    for(int i=0;i<poly.terms;i++){
        float c =poly.termArray[i].coef;
        int e =poly.termArray[i].exp;

        if(i>0)os<<" ";

        if(e==0){
            os<<c;		//常數 
        }else if(e==1){
            os<<c<<"X";		//1次方 
        }else{
            os<<c<<"X^"<<e;		//比1多的次方 
        }
    }
    return os;
}

int main(){
    Polynomial p1,p2;

    cout<<"=== 輸入多項式 P1 (輸入 係數 指數  案Enter結束) ===\n";
    cin>>p1;

    cout<<"\n=== 輸入多項式 P2 (輸入 係數 指數 案Enter結束) ===\n";  
    cin>>p2;

    cout<<"\n-----------------------------------" << endl;
    cout<<"P1 = " << p1 << endl;
    cout<<"P2 = " << p2 << endl;
    cout<<"-----------------------------------" << endl;

    int choice;
    do{
        cout<<"\n==============================\n請選擇要執行的項目：\n";
        cout<<"1. 多項式相加 (P1 + P2)\n";
        cout<<"2. 多項式相乘 (P1 * P2)\n";
        cout<<"3. 代入 x 計算值\n";
        cout<<"0. 結束程式\n";
        cout<<"請輸入選項 (0-3): ";
        cin>>choice;

        switch(choice){
            case 1:{
                Polynomial sum = p1.Add(p2);
                cout<<"\n>>> P1 + P2 = "<<sum<<"\n";
                break;
            }
            case 2:{
                Polynomial prod = p1.Mult(p2);
                cout<<"\n>>> P1 * P2 = "<<prod<<"\n";
                break;
            }
            case 3:{
                float x;
                cout<<"\n請輸入要代入的x值: ";
                cin>>x;
                cout<<"P1(" << x << ") = "<<p1.Eval(x)<<"\n";
                cout<<"P2(" << x << ") = "<<p2.Eval(x)<<"\n";
                break;
            }
            case 0:
                cout<<"\n程式已結束。\n";
                break;
            default:
                cout<<"\n無效的選項，請重新選擇\n";
                break;
        }
    }while(choice!=0);

    return 0;
}
```

## 效能分析

| 運算or函式 |   時間複雜度(Time)   | 空間複雜度(Space) |             說明              |
| ---------- | -----------------  | ---------------- | ------------------------------ |
| newTerm()  | $O(1)$/最壞 $O(n)$ | $O(n)$            | 擴充記憶體時需複製原n個項目      |
| Add()      | $O(m+n)$           | $O(m+n)$         | m、n分別為兩多項式的非零項的數量  |
| Mult()     | $O(m * n * k)$     | $O(m+n)$         | k是目前結果多項式的項數          |
| Eval()     | $O(nlog E)$        | $O(1)$           | E是最大指數，其取決於 $pow$ 計算 |
| operator>> | $O(n)$             | $O(n)$           | n為輸入行內解析出的總項數        |
| operator<< | $O(n)$             | $O(1)$           | 單次印出所有非零項               |

## 測試與驗證

### 測試案例

| 測試案例  | 輸入多項式p1 | 輸入多項式p2| x為多少 |      Add輸出     |      Mult輸出      |     Eval輸出     |
|----------|--------------|-----------|---------|-----------------|--------------------|------------------|
| 測試一   | 3 2 1 1      | 2 1 3 0    | 2       | 3X^2+3X+3      | 6X^3+11X^2+3X       | p1=14,p2=7       |
| 測試二   | 2 5 1 0      | 1 1 2 0    | 1       | 2X^5+1X+3      | 2X^6+4X^5+1X+2      | p1=3,p2=3        |
| 測試三   | -1 3         | -2 1       | 3       | -1X^3-2X       | 2X^4                | p1=-27,p2=-6     |
| 測試四   | 3 3 2 2 1 0  | 2 1 1 0    | 0       | 3X^3+2X^2+2X+2 | 6X^4+7X^3+2X^2+2X+1 | p1=1,p2=1        |


### 編譯與執行指令

```shell
$ g++ -std=c++11 -O2 Polynomial.cpp -o Polynomial.exe
$ Polynomial.exe
6
```


## 申論及開發報告

### 使用陣列與動態記憶體配置的原因

在做業中，使用"陣列 $termArray$ 搭配動態記憶體配置"來實作多項式ADT的原因:

1. **記憶體使用效率高且連續存取速度快**  
    透過只記錄非零項的 $coef$（係數）與 $exp$（指數），能大幅節省記憶體空間，並且列在記憶體中具備連續性，可以提高運算時的速度。

   
2. **動態記憶體配置**  
   為了避免預先配置過大空間造成的浪費，建構子初始化僅分配容量 4 的陣列（capacity = 4）。當陣列容量不夠用時(terms == capacity），把陣列的容量增加到原本的兩倍(capacity*=2)，這個機制可將新增單項（newTerm）的平均分攤時間複雜度維持在 $O(1)$，確保動態配置時的系統效能。  

   
3. **語意清楚且可多載(operator Overloading)**  
   多載operator>> 和 operator<< 串流運算子，讓使用者可以直接以 cin>>p1 跟 cout<<p1 的標準介面進行輸入與格式化輸出。再來搭配Add、Mult的物件化回傳設計，讓程式介面乾淨、容易維護。

