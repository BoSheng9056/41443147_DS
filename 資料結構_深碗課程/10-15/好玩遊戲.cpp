```cpp
#include<iostream>
#include<string>
using namespace std;
class GameCharacter{
public:
    string name;
    int hp;
    int level;

	GameCharacter() {
        name = "";
        hp = 100;
        level = 1;
    }

    // ********Constructor
    GameCharacter(string n, int h, int l){
        name=n;// 將 n 存入 name
        hp=h;// 將 h 存入 hp
        level=l;// 將 l 存入 level
    }
	// *******設定角色資料 
	void set(string n, int h, int l){
		name=n;// 將 n 存入 name
        if(h>100){
			hp=100;
		}else {
			hp=h;// 將 h 存入 hp
		}
        level=l;// 將 l 存入 level				
	}

    // ********受到傷害
    void damage(int value){
        this->hp-=value;	// 1. hp 扣掉 value
        if(hp<0){	// 2. 如果 hp 小於 0，將 hp 設為 0
			this->hp=0;
   		}
	}
	// ********回復生命值
    void heal(int value){
        this->hp+=value;		// 1. hp 加上 value
        if(hp>100)	this->hp=100;		// 2. 如果 hp 大於 100，將 hp 設為 100
    	
	}
    // ********升級
    void levelUp(int value){
        this->level+=value;// 1. level 加 1
		this->hp+=100;// 2. hp 回復成 100
		if(hp>100)	this->hp=100;
		
    }

    // *********顯示角色資料
    void show(){
    	cout<<"\n=== 角色資料 ===\n";
        cout<<"名稱: "<<name<<"\n"; 
        cout<<"血量: "<<hp<<"\n";
        cout<<"等級: "<<level<<"\n\n";
	}
};


int main(){	
	string n;
	int i,j,num,x,y,cha;
	int h,l;
	cout<<"請輸入角色數量: ";
	cin>>num;
	GameCharacter* p = new GameCharacter[num];
	for(i=0;i<num;i++){
		cout<<"=== 角色"<<i+1<<" ===\n";
		cout<<"名稱: "; 
		cin>>n;
		cout<<"血量(最大值為100): ";
		cin>>h;
		cout<<"等級: ";
		cin>>l;
		
		p[i].set(n,h,l);		
	}
	
	while(true){
		cout<<"==== 選單 ====\n";
    	cout<<"1.扣血\n";
    	cout<<"2.回血\n";
    	cout<<"3.升級\n";
    	cout<<"4.顯示角色資料\n";
    	cout<<"0.結束程式\n";
    	cout<<"-選擇: ";
    	cin>>x;
    	
    	
    	switch(x){
    		case 1:
    			cout<<"\n*** 扣血 ***\n";
    			cout<<"扣除多少血: ";
    			cin>>y;
				cout<<"選擇角色( 請用數字ex:1 ): ";
    			cin>>cha;
    			p[cha-1].damage(y); 
    			p[cha-1].show();
    			break;
    		case 2:
    			cout<<"\n*** 回血 ***\n";
    			cout<<"恢復多少血: ";
    			cin>>y;
				cout<<"選擇角色( 請用數字ex:1 ): ";
    			cin>>cha;
    			p[cha-1].heal(y); 
    			p[cha-1].show();
    			break;
    		case 3:
    			cout<<"\n*** 升級 ***\n";
    			cout<<"提升多少等級: ";
    			cin>>y;
				cout<<"選擇角色( 請用數字ex:1 ): ";
    			cin>>cha;
    			p[cha-1].levelUp(y); 
    			p[cha-1].show();
    			break;
    		case 4:
    			cout<<"\n*** 顯示角色資料 ***\n";
    			cout<<"選擇角色( 請用數字ex:1 ): ";
    			cin>>cha;
    			p[cha-1].show();
    			break;
    		case 0:	
    			return 0;
		}; 	
  }
	return 0;
}
```
