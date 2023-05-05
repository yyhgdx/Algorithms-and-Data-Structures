
#ifndef LISTNODE
#define LISTNODE
#define ListNodePosi(T) ListNode<T>*
#include <cstddef>
typedef int Rank;//����
template <typename T> struct ListNode{
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;
	ListNode() {}
	ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
		: data ( e ),  pred (p) , succ(s){	}
	ListNodePosi(T) insertAsPred ( T const& e );
	ListNodePosi(T) insertAsSucc ( T const& e );
};
#endif
//#ifndef LISTNODE
//#define LISTNODE
//#include <cstddef>
//
//#define ListNodePosi(T) ListNode<T>*
//typedef int Rank;
//
//template <typename T>
//struct ListNode	{
//	
//	T data;                                                   //������ 
//	ListNodePosi(T) pred;                                     //ֱ��ǰ��ָ�� 
//	ListNodePosi(T) succ;                                     //ֱ�Ӻ��ָ�� 
//	
//	ListNode() {}                                             //Ĭ�Ϲ��캯�� ���header��trailer�ڵ�Ĺ��� Ĭ��ΪNULL 
//	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
//		:data(e), pred(p), succ(s) {}
//	
//	ListNodePosi(T) insertAsPred(T const& e);                 //�ڵ�ǰ�ڵ�ǰ�����½ڵ� 
//	ListNodePosi(T) insertAsSucc(T const& e);                 //�ڵ�ǰ�ڵ������½ڵ� 
//	
//};
//
//#endif 
