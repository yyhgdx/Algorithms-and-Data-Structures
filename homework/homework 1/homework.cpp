#include<iostream>

#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex2.h"
#include "../../vector/vector.h"
using namespace std;
 
int main(){
	Complex A[100];
    cout << "排序前" <<endl; 
	//生成复数类的数组 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();
    }
    cout << endl;
 
    
    Vector<Complex>v(A, 10);
    
	//置乱
	v.unsort();
    cout << "置乱后" << endl;
	for (int j = 0; j < 10; j++){
	   v.elem(j).display(); 
    }
    cout << endl;	 

    //查找
	int b[10];
	cout << "置乱前每一个复数在置乱后向量组里的位置为" <<endl;
	for (int j = 0; j < 10; j++){
		b[j] = v.find(A[j]); 
	    A[j].display(); 
		cout << "第" << b[j]+1 <<"位"<<endl; 
	} 
	
	//插入
	for(int j = 0; j < 10; j++){
	    v.insert(rand()%(10+j),A[rand()%(10)]);
	}
	cout << "生成随机位置插入10个复数后 新的复数向量"<<endl; 
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	} 
	
	//删除
	v.remove(4,9);
	cout << "删除区间（4，9）后新的向量"<<endl; 
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	}  
	cout << endl;
	
	//唯一化操作
	cout << "唯一化操作后新的向量"<<endl; 
	v.deduplicate();
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	}  
    cout << endl; 
    
    int n;
    n = v.disordered();
    cout << "n =  " << n <<" 复数向量组未排完" << endl;
    v.bubbleSort(0,v.size());
    n = v.disordered();  
      cout << "排序后" <<endl;
	   
    for (int j = 0; j < v.size(); j++){
	   v.elem(j).display(); 
	   if ( j % 10 == 9 )
		cout << endl; 
    }
    cout << "n =  " << n <<" 复数向量组已排完" << endl;
}
    
 

