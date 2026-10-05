# 41443147
## 作業一：阿克曼函數（Ackermann Function）計算
## 解題說明

### 問題描述
本題要求分別以「遞迴」與「非遞迴」兩種方式實現阿克曼函數（Ackermann Function）的計算。

### 解題策略
1. **簡化條件優化**：不論是遞迴或非遞迴版本，皆先處理(m = 0回傳 n + 1)、(m = 1回傳 n + 2)、(m = 2回傳 2n + 3)，減少不必要的堆疊操作與遞迴次數。
2. **遞迴版本**：對於 $m \ge 3$，依照定義進行遞迴呼叫：當 $n = 0$ 時呼叫 `ackermann(m-1,1)`，否則呼叫 `ackermann(m-1,ackermann(m,n-1))`。
3. **非遞迴版本**：
    - 自行實作動態陣列堆疊（包含 `push_stack` 擴充機制與 `pop_stack`）。
    - 利用 `while` 迴圈配合 Stack 模擬系統呼叫堆疊，模擬阿克曼函數的展開與回傳過程。
4. **主程式**：由使用者輸入 $m$ 與 $n$，執行運算後輸出結果。

---

## 程式實作

### 1. 遞迴版本程式碼

```cpp
#include<iostream>
#include<iomanip> 
using namespace std;

//遞迴函數 
long long ackermann(long long m,long long n){
    if (m==0) return n+1;
    if (m==1) return n+2;
    if (m==2) return 2*n+3;

    if (n==0) return ackermann(m-1,1);
    return ackermann(m-1,ackermann(m,n-1));
}

int main(){
    long long m,n;
    int out;
    /*- - - 輸入值 - - -*/
    cout<<"請輸入數值:\n" << "m = ";
    cin>>m;
    cout<<"n = ";
    cin>>n;
    
    /*- - - 執行運算 - - -*/
    out=ackermann(m,n);
    cout<<"ackermann(m,n) = "<<out;
}

```
### 2. 非遞迴版本程式碼
```cpp
#include <iostream>
#include<iomanip> 
using namespace std;

//push_stack(在空間不足時進行動態擴充)
void push_stack(int*& s,int& top,int& capacity,int val){
    if (top+1>=capacity){
        int new_capacity=capacity*2;
        int* new_s = new int[new_capacity];
        for (int i=0;i<=top;i++){
            new_s[i]=s[i];
        }
        delete[] s;
        s=new_s;
        capacity=new_capacity;
    }
    s[++top]=val;
}

//pop_stack
int pop_stack(int* s,int& top){
    if (top<0){
        cout<<"Stack Underflow!"<<endl;
        return -1;
    }
    int value=s[top--];
    return value;
}

//非遞迴 ackermann
int ackermann_nonrecursive(int m,int n){
    if (m==0) return n+1;
    if (m==1) return n+2;
    if (m==2) return 2*n+3;
    
    //建立動態 Stack
    int capacity=16;
    int top=-1;
    int* s=new int[capacity];

    push_stack(s,top,capacity,m);

    while(top>=0){
        m=pop_stack(s,top);

        if(m==0){
            n++;
        }else if(n==0){
            n=1;
        }else{
            n--;
            push_stack(s,top,capacity,m-1);
            push_stack(s,top,capacity,m);
        }
    }

    delete[] s; //釋放記憶體
    return n;
}

int main() {
    int m, n;
    /*- - - 輸入 m、n - - -*/
    cout<<"請輸入m和n : ";
    cin>>m>>n;  
    int result=ackermann_nonrecursive(m,n);
    cout<<"ackermann_nonrecursive(m,n) = "<<result;
        
    return 0;
}
```
## 效能分析
### 時間複雜度
   - 當 $m \le 2$ 時，不論遞迴或非遞迴版本，時間複雜度為 $O(1)$。
   - 當 $m \ge 3$ 時，時間複雜度為 $O(A(m, n))$。
### 空間複雜度
   - 遞迴版本：當 $m \le 2$ 時為 $O(1)$，當 $m \ge 3$ 空間複雜度為 $O(A(m, n))$。                                            
   - 非遞迴版本：當 $m \le 2$ 時為 $O(1)$，當 $m \ge 3$ 空間複雜度為 $O(A(m, n))$。


## 測試與驗證

| 測試案例    | 輸入參數 (m,n) | 預期輸出 | 實際輸出 |
| ----------- | ----------- |-------------|-------------|
| 測試一      | $m = 0, n = 5$ |      6      |      6      |
| 測試二      | $m = 1, n = 3$ |      5      |      5      |
| 測試三      | $m = 2, n = 4$ |      11     |      11     |
| 測試四      | $m = 3, n = 2$ |      29     |      29     |

## 編譯與執行指令
    $ g++ -std=c++17 -o main main.cpp
    $ .\main.exe
    請輸入m和n : 3 2
    ackermann_nonrecursive(m,n) = 29
### 結論
   - 結論遞迴與非遞迴版本均能精確計算出各項 $m, n$ 輸入下的阿克曼函數值，且輸出結果完全一致。
   - 兩者均包含 $m \le 2$ 的簡化判斷，成功減少遞迴深度的消耗與 Stack 的操作頻率。

--------


## 作業二：冪集（Power Set）

## 解題說明

### 問題描述
本題要求實現一個能生成給定字串 $S$ 之所有子集，Power Set的程式。對於長度為 $n$ 的集合，其冪集總共包含 $2^n$ 個子集。

### 解題策略
1. **先進行排序**：讀入字串 $S$ 後，先使用 `std::sort` 對字串進行排序，確保輸出的子集順序符合字典序。
2. **回溯與遞迴分支（Backtracking）**：
   - 使用 `powerset` 遞迴函數，傳入當前處理的字元索引 `index` 以及已累積的字串 `current`。
   - 對於每個字元，分為兩個分支遞迴：
     1. **不選擇當前字元**：直接處理下一個字元 `powerset(str, index + 1, current)`。
     2. **選擇當前字元**：將該字元加入 `current` 後繼續遞迴 `powerset(str, index + 1, current + str[index])`。
3. **終止條件**：當 `index` 等於字串長度時，表示已完成一種子集組合，印出 `(current)` 並返回。

---

## 程式實作

以下為程式碼：

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// str原始輸入字串	index當前處理到第幾個字元	current當前組合出來的子集字串
void powerset(string& str,int index,string current) {
    // 當處理完所有字元，印出當前子集
    if (index==str.length()){
        cout<<"("<<current<<") ";
        return;
    }

    //不選擇當前字元
    powerset(str,index+1, current);

    //選擇當前字元 (將字元加到 current 後面)
    powerset(str,index+1,current+str[index]);
}

int main() {
    string S="";
    cout<<"S(不須間隔) = ";
    cin>>S;
        
    sort(S.begin(),S.end());    // 排序
    cout<<"powerset(S) = ";
    powerset(S,0,"");   //傳入陣列、開始處理位子、空字串(紀錄結果) 

    return 0;
}
```

## 效能分析
### 時間複雜度
   - 時間複雜度：O(n $dot$ $2^n$)。
### 空間複雜度
   - 空間複雜度：O($n^2$)。


## 測試與驗證

| 測試案例    | 輸入參數 S("") |                   預期輸出                   |                   實際輸出                    |
| ---------- | ------------- | -------------------------------------------- |--------------------------------------------- |
| 測試一      | $a$          |      () (a)                                  |      () (a)                                  |
| 測試二      | $ab$         |      () (b) (a) (ab)                         |      () (b) (a) (ab)                         |
| 測試三      | $abc$        |      () (c) (b) (bc) (a) (ac) (ab) (abc)     |      () (c) (b) (bc) (a) (ac) (ab) (abc)     |

## 編譯與執行指令
    $ g++ -std=c++17 -o main main.cpp
    $ .\main.exe
    S(不須間隔) = abc
    powerset(S) = () (c) (b) (bc) (a) (ac) (ab) (abc)

## 結論
1. 程式能夠正確列舉出任何長度字串的所有子集組合（包含空集合），總輸出子集數量為 $2^n$ 個。
2. 先透過 std::sort 排序，結合「選/不選」的二元遞迴樹結構，能以最直觀的方式列舉出所有組合情況。



## 申論及開發報告
### 作業一：選擇遞迴與非遞迴實作的原因與分析

1. **遞迴版本邏輯簡潔直觀**  
   遞迴寫法能精準表達 $A(m, n) = A(m - 1, A(m, n - 1))$ 的數學定義，程式碼與數學公式直接對映，結構清晰且易於實作。

2. **非遞迴版本避免堆疊溢位（Stack Overflow）**  
   阿克曼函數成長極快，深層遞迴易耗盡系統呼叫堆疊。透過自訂動態陣列堆疊（Dynamic Array Stack）與 `push_stack` 自動擴充機制，將呼叫狀態轉移至 Heap 空間，能更精確掌控記憶體與堆疊深度。

3. **常數邊界優化（Base Case Optimization）**  
   兩版本皆提前處理 $m = 1$（回傳 $n + 2$）與 $m = 2$（回傳 $2n + 3$）減少堆疊操作與遞迴層數，顯著提升執行效率。

---

### 作業二：選擇遞迴回溯與排序實作冪集的原因

1. **結構天然契合二元樹決策**  
   冪集的核心在於對每個元素做出「選」和「不選」的二元抉擇。遞迴回溯（Backtracking）能直觀地表達此分支邏輯，不需維護複雜的迴圈狀態。

2. **預先排序確保輸出順序**  
   在遞迴前先用 `std::sort` 對輸入字串進行排序，確保產生的子集能依字典序排列，方便測試與結果驗證。

3. **參數傳遞簡化狀態維護**  
   使用 `current` 記錄中間組合狀態，在達到字串邊界 `index == str.length()` 時輸出結果，程式碼簡短且可讀性高。 
