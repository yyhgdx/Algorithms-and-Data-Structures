#include "../../graph/GraphMatrix.h"
#include <stdlib.h>
int main(){
	 GraphMatrix<char, int> g;
	 int n = 10;
	 int e = 60;
	 char vectex1 = (char) ('A' + rand()%25);
	 char vectex2 = (char) ('A' + rand()%25);
	 char vectex3 = (char) ('A' + rand()%25);
	 char vectex4 = (char) ('A' + rand()%25);
	 char vectex5 = (char) ('A' + rand()%25);
	 char vectex6 = (char) ('A' + rand()%25);
	 char vectex7 = (char) ('A' + rand()%25);
	 char vectex8 = (char) ('A' + rand()%25);
	 char vectex9 = (char) ('A' + rand()%25);
	 char vectex10 = (char) ('A' + rand()%25);	 
	 g.insert ( vectex1 );  
	 g.insert ( vectex2 ); 
	 g.insert ( vectex3 );
	 g.insert ( vectex4 );
	 g.insert ( vectex5 );
	 g.insert ( vectex6 );
	 g.insert ( vectex7 );
	 g.insert ( vectex8 );
	 g.insert ( vectex9 );
	 g.insert ( vectex10 );
	 for(int i = 0; i<10;i++)
	     for(int j = i+1; j <10; j++){
	     	int z = 0;
	     	if (rand()%100 >= 50&&z<=e){
	     		g.insert(z,1,i,j);
	     		g.insert(z+1,1,j,i);
			 }
			z = z+2;
		 } 
	 for(int i = 0; i <10;i++){
	 		printf("%c",g.V[i].data);
	 }
	 printf("\n");
	 for(int i =0; i<10;i++){
	 	for (int j =0; j<10;j++){
	 		 if ( g.exists (i, j))
	 		    printf("1 "); 
	 		 else
	 		     printf("0 ");
		 }printf("\n");
	 }
	 g.dfs(0);
	 
}

   
