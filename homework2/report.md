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
    - $ e=0 $ : 輸出 $c$ (常數項)
    - $ e=1 $ : 輸出 $cX$ (一次方)
    - $ e>1 $ : 輸出 $cX^e$ (比一次多的次方)

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



## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
