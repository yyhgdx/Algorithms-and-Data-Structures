//#ifndef QUEUE
//#define QUEUE
//#include"../list/list.h"
//#include <stdlib.h>
//template <typename T> class Queue:public List<T>{
//public:
//	void enqueue (T const& e ){ insertAsLast ( e );}
//	T dequeue(){ return remove (this->first());}
//	T& front(){ return this->first()->data;}
//};
//#endif
#ifndef QUEUE
#define QUEUE

#include"../list/list.h"
#include <stdlib.h>
using namespace std;

template <typename T> 
class Queue:public List<T>{
public: 
	void enqueue( T const& e){
		insertAsLast( e );
	}
	T dequeue(){
		return remove( this->first() );
	}
	T& front(){
		return this->first()->data;
	}
//    queue(){	//��ʼ��
//        front=0;
//        back=-1;
//        count=0;
//    }
//    bool isEmpty(){	//�п�
//        if(count==0){
////            cout<<"queue is empty.\n";
//            return true;
//        }
//        return false;
//    }
//    bool isFull(){	//����
//        if(count==MAXSIZE||back==MAXSIZE-1){
////            cout<<"queue is full.\n";
//            return true;
//        }
//        return false;
//    }
//    int getFront(){	//ȡ��ͷ
//        if(isEmpty()){
//            return -1;
//        }
//        return data[front];
//    }
//    int getBack(){	//ȡ��β
//        if(isEmpty()){
//            return -1;
//        }
//        return data[back];
//    }
//    bool push(int num){	//���
//        if(isFull()){
//            return false;
//        }
//        back++;
//        data[back]=num; 
//        count++;
//        return true;
//    }
//    bool pop(){	//����
//        if(isEmpty()){
//            return false;
//        }
//        front++;
//        count--;
//        return true;
//    }
//    bool pop2(){	//����
//        if(isEmpty()){
//            return false;
//        }
//        back--;
//        count--;
//        return true;
//    }
//    int getLength(){	//�õ����г���
//        return count;
//    }
//private:
//    int front;
//    int back;
//    int count;
//    int data[MAXSIZE];
};
#endif

