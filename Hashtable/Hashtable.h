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
	virtual bool put(K k, V v) = 0;  //�������
	virtual V* get(K k) =0;       
	virtual bool remove(K k) = 0;    //ɾ������
};
typedef int Rank; //��
static size_t hashCode ( char c ) { return ( size_t ) c; } 
static size_t hashCode ( int k ) { return ( size_t ) k; } 
static size_t hashCode ( long long i ) { return ( size_t ) ( ( i >> 32 ) + ( int ) i ); }
static size_t hashCode ( char s[] ) {
   int h = 0; 
   for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //�������ң��������ÿһ�ַ�
      { h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
   return ( size_t ) h; //������õ�ɢ���룬ʵ���Ͽ����Ϊ���Ƶġ�����ʽɢ���롱
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

int primeNLT ( int c, int n, char* file ) { //����file�ļ��еļ�¼����[c, n)��ȡ��С������
   Bitmap B ( file, n);                     //file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
   while ( c < n)                           //��c��ʼ����λ��
      if ( B.test ( c )) c++; 
      else return c;                        //�����׸����ֵ�����
   return c;                                //��û������������������n��ʵ���в�����˼򻯴���
}

template <typename K, typename V> Hashtable<K,V>::Hashtable(int c)
{
	char text[] = "../data/2.txt";
	char* ch = text;
    M = primeNLT ( c, 104729, ch );         //��С��c������M
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

template <typename K, typename V> bool Hashtable<K, V>::put( K k, V v ) { //ɢ�б��������
	if ( ht[ probe4Hit( k ) ] ) return false;                             //��ͬԪ�ز����ظ�����
	Rank r = probe4Free( k );                                             //Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ���
	ht[ r ] = new entry<K, V>( k, v ); ++N;                               //����
	if ( N *2 > M ) rehash();                                             //��װ�����Ӹ���50%����ɢ��
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
