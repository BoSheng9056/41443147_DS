#include <iostream>
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
	cout<<"請輸入數值:\n" <<"m = ";
	cin>>m;
	cout<<"n = ";
	cin>>n;
	
	/*- - - 執行運算 - - -*/
	out=ackermann(m,n);
	cout<<"ackermann(m,n) = "<<out;
}
