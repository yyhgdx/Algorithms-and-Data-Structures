//���� 
#include<windows.h> 
#include <ctime>
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex2.h"
#include "../../vector/vector.h"
using namespace std;
int main()
{
	 double time=0;  
    double counts=0;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;  
	Complex A[10000];
	Complex B[10000];
	Complex C[10000];
	Complex D[10000];
	Complex E[10000];
	cout << "�����������������" <<endl; 
	for (int j = 0; j < 10000; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
    }//���ɸ��� 
    cout << endl;
   for (int j = 0; j < 10000; j++){
	   B[j].read_Real(rand() % 200 / 10.0);
	   B[j].read_Imaginary(rand() % 200 / 10.0);
	   B[j].read_modulus();
    }//���ɸ��� 
    Vector<Complex>v(A, 10000);
    Vector<Complex>v1(B, 10000);
    Vector<Complex>v2(C, 10000);
     cout << endl;
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout << "����� ��һ��" <<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    cout << "����� �ڶ���" <<endl; 
    cout<<endl;
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms";
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<endl;cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    
    Vector<Complex>v3(A, 10000);
    Vector<Complex>v4(A, 10000);
    Vector<Complex>v5(A, 10000);
    Vector<Complex>v6(A, 10000);
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.heapSort(10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.InsertionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.quickSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v6.selectionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
	    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
        QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v3.heapSort(10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v4.InsertionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v5.quickSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v6.selectionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
	for (int j = 0; j < v1.size(); j++){
	   v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    	 
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.bubbleSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ð��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
    for (int j = 0; j < v1.size(); j++){
	     v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.mergeSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����鲢ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
        for (int j = 0; j < v1.size(); j++){
	     v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.heapSort(10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        for (int j = 0; j < v1.size(); j++){
	     v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.InsertionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
        for (int j = 0; j < v1.size(); j++){
	     v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.quickSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"�������ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
        for (int j = 0; j < v1.size(); j++){
	     v2.elem(j) = v1.elem(v1.size()-1-j);
	}
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v2.selectionSort(0,10000); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
    cout<<"����ѡ��ִ��ʱ�䣺"<<time*1000<<"ms"<<endl;
    
	
    
}
