#include<iostream>

#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex2.h"
#include "../../vector/vector.h"
using namespace std;
 
int main(){
	Complex A[100];
    cout << "����ǰ" <<endl; 
	//���ɸ���������� 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();
    }
    cout << endl;
 
    
    Vector<Complex>v(A, 10);
    
	//����
	v.unsort();
    cout << "���Һ�" << endl;
	for (int j = 0; j < 10; j++){
	   v.elem(j).display(); 
    }
    cout << endl;	 

    //����
	int b[10];
	cout << "����ǰÿһ�����������Һ����������λ��Ϊ" <<endl;
	for (int j = 0; j < 10; j++){
		b[j] = v.find(A[j]); 
	    A[j].display(); 
		cout << "��" << b[j]+1 <<"λ"<<endl; 
	} 
	
	//����
	for(int j = 0; j < 10; j++){
	    v.insert(rand()%(10+j),A[rand()%(10)]);
	}
	cout << "�������λ�ò���10�������� �µĸ�������"<<endl; 
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	} 
	
	//ɾ��
	v.remove(4,9);
	cout << "ɾ�����䣨4��9�����µ�����"<<endl; 
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	}  
	cout << endl;
	
	//Ψһ������
	cout << "Ψһ���������µ�����"<<endl; 
	v.deduplicate();
	for (int j = 0; j < v.size(); j++){
		v.elem(j).display();
		if ( j % 10 == 9 )
		cout << endl; 
	}  
    cout << endl; 
    
    int n;
    n = v.disordered();
    cout << "n =  " << n <<" ����������δ����" << endl;
    v.bubbleSort(0,v.size());
    n = v.disordered();  
      cout << "�����" <<endl;
	   
    for (int j = 0; j < v.size(); j++){
	   v.elem(j).display(); 
	   if ( j % 10 == 9 )
		cout << endl; 
    }
    cout << "n =  " << n <<" ����������������" << endl;
}
    
 

