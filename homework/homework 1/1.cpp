#include "../../vector/vector.h"

#include<iostream>
#include <stdlib.h>
int main(){
    Vector<int>v;
    for (int i = 0; i < 9; i++){
    	v.insert(rand() % 200);
	}
    for (int i = 0; i < 9; i++){
    	printf("%d ",v[i]);
	}
	printf("\n");
	v.selectionSort(0,v.size());
	for (int i = 0; i < 9; i++){
    	printf("%d ",v[i]);
	}
	for (int i = 0; i < 9; i++){
    	v.insert(rand() % 200);
	}
	
	printf("\n");
	v.selectionSort(0,v.size());
    for (int i = 0; i < v.size(); i++){
    	printf("%d ",v[i]);
	}
	
	
	printf("\n");
	for (int i = 0; i < 9; i++){
    	v.insert(rand() % 200);
	}
	v.selectionSort(0,v.size());
	for (int i = 0; i < v.size(); i++){
    	printf("%d ",v[i]);
	}
}
