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
		
    sort(S.begin(),S.end());	// 排序
    cout<<"powerset(S) = ";
    powerset(S,0,"");	//傳入陣列、開始處理位子、空字串(紀錄結果) 

    return 0;
}
