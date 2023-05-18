#include "vector.h" 
template <typename T> 
void Vector<T>::copyForm(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * ( hi - lo )] ; _size = 0 ;//����ռ䣬��ģ����
    while(lo < hi)
        _elem[_size++] = A[lo++] ; //������_elem[0,hi-lo)
}
