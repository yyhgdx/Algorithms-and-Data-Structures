#include "../../stack/stack.h"
#include "../../binary tree/BinTree.h"
#include "../../vector/vector.h"
#include "../../Bitmap/Bitmap.h"
#include "../../Hashtable/Hashtable.h"
#define N_CHAR (0x80 - 0x20)
#include <iostream>
using namespace std;
struct HuffChar {
	char ch; int weight;
	HuffChar ( char c= '^', int w = 0 ) : ch (c) ,weight ( w ){	};
	bool operator < ( HuffChar const& hc ) {return weight > hc.weight;}
	bool operator == ( HuffChar const& hc ) {return weight == hc.weight;} 
	bool operator > (HuffChar const& hc) {return weight < hc.weight;}
	bool operator <= (HuffChar const& hc) {return weight >= hc.weight;}
	bool operator >= (HuffChar const& hc) {return weight <= hc.weight;}
	bool operator != ( HuffChar const& hc){return weight != hc.weight;}
};
#define HuffTree BinTree<HuffChar>
#include "../../list/List.h"
typedef List<HuffTree*> HuffForest;
typedef Bitmap HuffCode;
typedef Hashtable<char, char*> HuffTable;

int* statistics ( char* sample_text_file ){
	int* freq = new int[N_CHAR];
	memset ( freq, 0, sizeof (int)* N_CHAR);
	FILE* fp = fopen ( sample_text_file,"r");
	for ( char ch; 0 < fscanf ( fp, "%c", &ch);)
	    if ( ch >= 0x20 ) freq[ch- 0x20]++;
	fclose ( fp ); return freq;
}
HuffForest* initForest ( int* freq ){
	HuffForest* forest = new HuffForest;
	for ( int i=0; i<N_CHAR; i++){
		forest->insertAsLast ( new HuffTree );
		forest->last()->data->insertAsRoot ( HuffChar ( 0x20 +i,freq[i]));
	}
	return forest;
}
HuffTree* minHChar (HuffForest* forest ){
	ListNodePosi ( HuffTree* ) p = forest -> first();
	ListNodePosi ( HuffTree* ) minChar = p;
	int minWeight= p->data->root()->data.weight;
	while ( forest->valid ( p= p->succ))
	    if ( minWeight > p->data->root()->data.weight )
	        { minWeight= p->data->root()->data.weight; minChar=p;}
	return forest->remove ( minChar );
}
HuffTree* generateTree( HuffForest* forest )
{
	while( 1 < forest->size( ) )
	{
		HuffTree* T1 = minHChar( forest );
		HuffTree* T2 = minHChar( forest );
		HuffTree* S = new HuffTree();
		S->insertAsRoot( HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC( S->root(), T1 );S->attachAsRC( S->root(), T2 );
		forest->insertAsLast( S );
	}
	return forest->first()->data;
}
static void generateCT ( Bitmap* code, int length, HuffTable* table, BinNodePosi ( HuffChar) v ){
	if ( IsLeaf ( *v ) ){table->put ( v->data.ch, code->bits2string(length)); return; }
	if ( HasLChild( *v)){ code->clear(length); generateCT ( code, length+1,table,v->lc);}
	if ( HasRChild( *v )){ code->set(length); generateCT ( code, length+1,table,v->rc);}
}
HuffTable* generateTable ( HuffTree* tree ){
	HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
	generateCT ( code , 0,table,tree->root()); releases(code); return table;
};


int encode ( HuffTable* table, Bitmap* codeString, char* s){
	int n = 0;
	for ( size_t m = strlen(s), i = 0; i < m ;i++){
		char** pCharCode = table->get ( s[i]);
		if (!pCharCode ) pCharCode = table->get (s[i] + 'A' - 'a');
		if(!pCharCode ) pCharCode = table->get (' ');
		printf ("%s", *pCharCode );
	    for ( size_t m=strlen(*pCharCode ), j = 0; j<m ; j++)
	        '1' == * ( *pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
	}
	printf ( "\n"); return n;
}
void decode ( HuffTree* tree, Bitmap* code, int n){
	BinNodePosi ( HuffChar ) x= tree->root();
	for ( int i = 0;i<n;i++){
		x = code->test(i) ? x->rc:x->lc;
		if (IsLeaf ( *x) ) {
		     printf ( "%c", x->data.ch); x = tree->root();
		} 
	} 
} 

int main(int argc, char* argv[]) {                                     //哈夫曼编码算法统一测试
    
    char text[] = "dream";
	char* ch = text;
	char text2[] = "I have a dream";
	char* ch2 = text2;
    char t[] = "../../data/2.txt";

    int* freq = statistics(t);                                         //根据样本文件，统计各字符的出现频率
    HuffForest* forest = initForest(freq);                             //创建哈夫曼森林
    releases(freq); 
    HuffTree* tree = generateTree(forest);                             //生成哈夫曼编码树
    releases(forest);
    
    HuffTable* table = generateTable(tree);                            //将哈夫曼编码树转换为编码表
    for (int i = 0;i < N_CHAR; i++)                                    //输出编码表
        printf(" %c: %s\n", i + 0x20, *( table->get( i + 0x20) ) );
    for (int i = 2;i<3; i++) {                                         //对于命令行传入的每一明文串
        printf("\nEncoding : %s\n", ch);                               
        Bitmap* codeString = new Bitmap;                               //二进制编码串
        int n = encode(table, codeString, text);                       //将根据编码表生成长度为n
        printf("Decoding: \n");                                       
        decode(tree, codeString, n);                                   //利用哈夫曼编码树，对长度为n的二进制编码串解码
        releases(codeString);
    }
    printf("\nEncoding : %s\n", ch2);                                 
    Bitmap* codeString = new Bitmap;                                   //二进制编码串
    int n = encode(table, codeString, text2);                          //将根据编码表生成长度为n
    printf("Decoding: \n");                                          
    decode(tree, codeString, n);                                       //利用哈夫曼编码树，对长度为n的二进制编码串解码
    releases(codeString);
    system("pause");
    releases(table); 
    releases(tree);
    return 0;
}
