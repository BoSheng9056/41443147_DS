# 作業一：阿克曼函數（Ackermann Function）計算

## 解題說明

### 問題描述
本題要求實現阿克曼函數（Ackermann Function）的計算。

### 解題策略
1. **加入簡化條件**：當 $m = 0$ 時回傳 $n + 1$；當 $m = 1$ 時回傳 $n + 2$；當 $m = 2$ 時回傳 $2n + 3$，減少遞迴呼叫次數。
2. **遞迴分解**：對於 $m \ge 3$，依照定義進行遞迴：$n = 0$ 時呼叫 `ackermann(m - 1, 1)`，否則呼叫 `ackermann(m - 1, ackermann(m, n - 1))`。
3. **主程式**：由使用者輸入 $m$ 與 $n$，執行運算後輸出結果。

---

## 程式實作


以下為程式碼：

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
### 效能分析時間複雜度：
當 $m \le 2$ 時為 $O(1)$。
當 $m \ge 3$ 時，隨 $m$ 與 $n$ 增加呈爆炸性成長，時間複雜度為 $O(A(m, n))$。
空間複雜度：
取決於遞迴堆疊深度，當 $m \le 2$ 時為 $O(1)$，當 $m \ge 3$ 時為 $O(A(m, n))$。
