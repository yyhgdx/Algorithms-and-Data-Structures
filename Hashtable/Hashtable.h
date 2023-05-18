#include "../Bitmap/Bitmap.h"

template<typename K,typename V> struct entry{
	K key;
	V value;
	entry( K k = K(), V v = V()):key(k), value(v){}
	entry(const entry<K,V>&e):key(e.key),value(value){}
 	bool operator< (const entry<K, V>& e);
	bool operator> (const entry<K, V>& e);
	bool operator==(const entry<K, V>& e);
	bool operator!=(const entry<K, V>& e);
};
template<typename K, typename V> bool entry<K,V>::operator<(const entry<K, V>& e)
{return this->key < e.key;}
template<typename K, typename V> bool entry<K, V>::operator>(const entry<K, V>& e)
{return this->key > e.key;}
template<typename K, typename V> bool entry<K, V>::operator==(const entry<K, V>& e)
{return this->key == e.key;}
template<typename K, typename V> bool entry<K, V>::operator!=(const entry<K, V>& e)
{return this->key != e.key;}
template<typename K, typename V> struct Dictionary
{
	virtual int size() const = 0;   
	virtual bool put(K k, V v) = 0;  //插入词条
	virtual V* get(K k) =0;       
	virtual bool remove(K k) = 0;    //删除词条
};
typedef int Rank; //秩
static size_t hashCode ( char c ) { return ( size_t ) c; } 
static size_t hashCode ( int k ) { return ( size_t ) k; } 
static size_t hashCode ( long long i ) { return ( size_t ) ( ( i >> 32 ) + ( int ) i ); }
static size_t hashCode ( char s[] ) {
   int h = 0; 
   for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //自左向右，逐个处理每一字符
      { h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //散列码循环左移5位，再累加当前字符
   return ( size_t ) h; //如此所得的散列码，实际上可理解为近似的“多项式散列码”
}


template <typename K, typename V>
class Hashtable:public Dictionary<K,V>
{
private:
	entry<K,V>** ht;
	int M;
	int N;
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval ->set(x))
protected:
	int probe4Hit( const K& k );
	int probe4Free (const K& k);
	void rehash();
public:
	Hashtable( int c = 5 ) ;
	~Hashtable();
	int size() const{return N;}
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
		
};
template <typename T>
void releases(T& e){
	e = NULL;
}

int primeNLT ( int c, int n, char* file ) { //根据file文件中的记录，在[c, n)内取最小的素数
   Bitmap B ( file, n);                     //file已经按位图格式，记录了n以内的所有素数，因此只要
   while ( c < n)                           //从c开始，逐位地
      if ( B.test ( c )) c++; 
      else return c;                        //返回首个发现的素数
   return c;                                //若没有这样的素数，返回n（实用中不能如此简化处理）
}

template <typename K, typename V> Hashtable<K,V>::Hashtable(int c)
{
	char text[] = "../data/2.txt";
	char* ch = text;
    M = primeNLT ( c, 104729, ch );         //不小于c的素数M
    N = 0; ht = new entry<K, V>*[M]; 
	memset(ht,0,sizeof(entry<K,V>*) *M);
	lazyRemoval = new Bitmap(M);
}

template <typename K,typename V> Hashtable<K,V>::~Hashtable()
{
	for(int i=0;i<M;i++)
	{
		if(ht[i])
			releases(ht[i]);
	}
	releases( ht );
	releases( lazyRemoval );
	delete[] lazyRemoval;
}

template <typename K, typename V>
V* Hashtable<K,V>::get(K k)
{
	int r = probe4Hit(k);
	return ht[r] ?& (ht[r]->value) :NULL; 
}
template <typename K, typename V>
int Hashtable<K,V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while( (ht[r]&&(k!= ht[r]->key))||(!ht[r] && lazilyRemoved(r)))
		r = (r + 1) % M;
	return r;
}
template <typename K, typename V>
int Hashtable<K,V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;
	while(ht[r])
		r = (r + 1) % M;
	return r;
}
template <typename K, typename V>
bool Hashtable<K,V>::remove(K k)
{
	int r = probe4Hit(k);
	if(!ht[r])
		return false;
	releases( ht[r]);
	ht[r] = NULL;
	markAsRemoved(r);
	N--;
	return true;
}

template <typename K, typename V> bool Hashtable<K, V>::put( K k, V v ) { //散列表词条插入
	if ( ht[ probe4Hit( k ) ] ) return false;                             //雷同元素不必重复插入
	Rank r = probe4Free( k );                                             //为新词条找个空桶（只要装填因子控制得当，必然成功）
	ht[ r ] = new entry<K, V>( k, v ); ++N;                               //插入
	if ( N *2 > M ) rehash();                                             //若装填因子高于50%，重散列
return true;
}
template <typename K, typename V>
void Hashtable<K,V>::rehash()
{
	char text[] = "../data/2.txt";
	char* ch = text;
	int old_capacity = M;
	entry<K,V>** old_ht = ht;
	M = primeNLT(2*M, 104729,ch);
	N = 0; ht = new entry<K,V>*[M];
	memset(ht, 0, sizeof(entry<K,V>*) *M);
	releases(lazyRemoval);
	delete[] lazyRemoval;
	lazyRemoval = new Bitmap (M);
	for(int i = 0; i < old_capacity; i++)
		if( old_ht[i] )
			put(old_ht[i]->key,old_ht[i]->value);
	releases(old_ht);

}
