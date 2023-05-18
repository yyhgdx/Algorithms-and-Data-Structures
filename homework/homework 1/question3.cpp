#include<iostream>

#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex2.h"
#include "../../vector/vector.h"
using namespace std;
int main(){
	Complex A[100];
    cout << "随机生成无序向量" <<endl; 
	//生成复数类的数组 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();
	}
	cout<<endl;
	 Vector<Complex>v(A, 10);
	 v.findem1m2(0,10,10.0,20.0);
	 cout << "符合标准的数据" <<endl; 
	 for (int j = 0; j <v.size(); j++){
       v.elem(j).display();
	}

}
