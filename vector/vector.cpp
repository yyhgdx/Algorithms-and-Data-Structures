#include "vector.h" 
template <typename T> 
void Vector<T>::copyForm(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * ( hi - lo )] ; _size = 0 ;//分配空间，规模清零
    while(lo < hi)
        _elem[_size++] = A[lo++] ; //复制至_elem[0,hi-lo)
}
