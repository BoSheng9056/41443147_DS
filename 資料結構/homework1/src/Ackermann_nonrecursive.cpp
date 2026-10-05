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
	if (m == 0) return n + 1;
    if (m == 1) return n + 2;
    if (m == 2) return 2 * n + 3;
    
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
            push_stack(s,top,capacity,m-1);
        }else{
            n--;
            push_stack(s,top,capacity,m-1);
            push_stack(s,top,capacity,m);
        }
    }

    delete[] s;	//釋放記憶體
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
