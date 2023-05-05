#include "../../stack/stack.h"
#include <iostream>
#include <stdlib.h>
#include "../../complex/Complex2.h"
using namespace std;
int FindMaxSquare( int *test, int length ){
		int square[length] = {0};
		Stack<int> height_width;
		Stack<int> height;
		height.push(0);
		height_width.push(-1);
		int i = 0;
		cout << length << endl;
		while( i < length ){
			if (*(test+i) >= height.top()) {
	     		int last = height_width.top();
				height.push(*(test+i));
				cout << height.top() << " ";
	     		height_width.push(i);
	     		square[height_width.top()] = (height_width.top() - last - 1) *height.top();
	     		i++;
			}  		
			else {
				while( *(test+i) < height.top()){
					square[height_width.top()] =square[height_width.top()] + height.top() *(i - height_width.top());
					height_width.pop();
					height.pop();
				}
			}
		}
		while( height_width.top()!=-1 ){
			square[height_width.top()] = square[height_width.top()] + height.top() *(length - height_width.top());
			height.pop();
			height_width.pop();
	}
		int max = square[0]; 
		for(int i=1;i<length; i++)
		{
			if (max < square[i]) max = square[i];
			cout << square[i]<<"  " ;
		}
		cout << max <<endl;
		return max;
}
int main(){
	int length[10];
	for (int i = 0; i < 10; i++) {
		length[i] = rand() % 104 + 1;
}
	int test[length[0]];
	for (int i = 0; i < length[0]; i++){
		test[i] = rand() % 104 + 1;
    }
    int max;
	max = FindMaxSquare( test , length[0]);	
    cout << max <<endl;
    
    int test1[length[1]];
	for (int i = 0; i < length[1]; i++){
		test1[i] = rand() % 104 + 1;
    }
	max = FindMaxSquare( test1 , length[1]);	
    cout << max <<endl;
}
//    length[0] = 6;
//    int test[6]={2,1,5,6,2,3};
    

	
