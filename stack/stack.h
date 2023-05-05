//#ifndef STACK
//#define STACK
//#include "../vector/vector.h"
//#define N_OPTR 9
//typedef enum { ADD, SUB, MUI, DIV, POW, FAC, L_P, R_P, EOE ,COM,SIN,TAN,COS} Operator;//0-8
//const char pri[13][13] = {
//   //+   -   *   /   ^   !   (   )  /0   i   s   c   t
//	'>','>','<','<','<','<','<','>','>','<','<','<','<', // +
//	'>','>','<','<','<','<','<','>','>','<','<','<','<', // -
//	'>','>','>','>','<','<','<','>','>','<','<','<','<', // *
//	'>','>','>','>','<','<','<','>','>','<','<','<','<', // /
//	'>','>','>','>','>','<','<','>','>','<','<','<','<', // ^
//	'>','>','>','>','>','>',' ','>','>','>','<','<','<', // !
//	'<','<','<','<','<','<','<','=',' ','<','<','<','<', // (
//	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', // )
//	'<','<','<','<','<','<','<',' ','=','<','<','<','<', // /0
//	'>','>','>','>','>','>',' ','>','>','>',' ',' ',' ', // i
//    '>','>','>','>','>',' ','<','>','>','>',' ',' ',' ', // s
//    '>','>','>','>','>',' ','<','>','>','>',' ',' ',' ', // c
//    '>','>','>','>','>',' ','<','>','>','>',' ',' ',' ', // t
//} ;
//
// 
//template <typename T> class Stack: public Vector<T> { //将向量的首/末端作为栈底/顶
//public:
//   void push ( T const& e ) { this->insert(this->size(), e ); }     //入栈：等效于将新元素作为向量的末元素插入
//   T pop() { return this->remove ( this->size() - 1 ); }             //出栈：等效于删除向量的末元素
//   T& top() { return ( *this ) [this->size() - 1]; }           //取顶：直接返回向量的末元素
//};
//#endif
#ifndef STACK
#define STACK
#include <ctype.h>
#include "../vector/vector.h"
#include <iostream>
using namespace std;

template <typename T> class Stack: public Vector<T> { //将向量的首/末端作为栈底/顶
public: //size()、empty()以及其它开放接口，均可直接沿用
   void push ( T const& e ) { this->insert (this->size(), e ); } //入栈：等效于将新元素作为向量的末元素插入
   T pop() { return this->remove ( this->size() - 1 ); } //出栈：等效于删除向量的末元素
   T& top() { return ( *this ) [this->size() - 1]; } //取顶：直接返回向量的末元素
};

#endif
