#include "../stack/stack.h"
#include "../Queue/Queue.h"
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边状态

template <typename Tv, typename Te> //顶点类型、边类型
class Graph { //图Graph模板类
	private:
		void reset() { //全部顶点、边的辅助信息复位
			for (int i = 0; i < n; i++) { //全部顶点的
				status(i) = UNDISCOVERED;
				dTime(i) = fTime(i) = -1; //状态，时间标签
				parent(i) = -1;
				priority(i) = INT_MAX; //（在遍历树中的）父节点，优先级数
				for (int j = 0; j < n; j++) //全部边的
					if (exists(i, j)) 
				    	type(i, j) = UNDETERMINED; //状态
			}
		}
		void BFS(int, int&); //（连通域）广度优先搜索算法
		void DFS(int, int&); //（连通域）深度优先搜索算法
		void BCC(int, int&, Stack<int>&); //（连通域）基于DFS的双连通分量分解算法
		bool TSort(int, int&, Stack<Tv>*); //（连通域）基于DFS的拓扑排序算法
		template <typename PU> void PFS(int, PU); //（连通域）优先级搜索框架
	public:
// 顶点
		int n; //顶点总数
		virtual int insert(Tv const &) = 0; //插入顶点，返回编号
		virtual Tv remove(int) = 0; //删除顶点及其关联边，返回该顶点信息
		virtual Tv& vertex(int) = 0; //顶点v的数据（该顶点的确存在）
		virtual int inDegree(int) = 0; //顶点v的入度（该顶点的确存在）
		virtual int outDegree(int) = 0; //顶点v的出度（该顶点的确存在）
		virtual int firstNbr(int) = 0; //顶点v的首个邻接顶点
		virtual int nextNbr(int, int) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
		virtual VStatus& status(int) = 0; //顶点v的状态
		virtual int& dTime(int) = 0; //顶点v的时间标签dTime
		virtual int& fTime(int) = 0; //顶点v的时间标签fTime
		virtual int& parent(int) = 0; //顶点v在遍历树中的父亲
		virtual int& priority(int) = 0; //顶点v在遍历树中的优先级数
// 边：这里约定。无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
		int e; //边总数
		virtual bool exists(int, int) = 0; //边(v, u)是否存在
		virtual void insert(Te const &, int, int, int) = 0; //在顶点v和u之间插入权重为w的边e
		virtual Te remove(int, int) = 0; //删除顶点v和u之间的边e，返回该边信息
		virtual EType& type(int, int) = 0; //边(v, u)的状态
		virtual Te& edge(int, int) = 0; //边(v, u)的数据（该边的确存在）
		virtual int& weight(int, int) = 0; //边(v, u)的权重
// 算法
		void bfs(int); //广度优先搜索算法
		void dfs(int); //深度优先搜索算法
		void bcc(int); //基于DFS的双连通分量分解算法
		Stack<Tv>* tSort(int); //基于DFS的拓扑排序算法
		void prim(int); //最小支撑树Prim算法
		void dijkstra(int); //最短路径Dijkstra算法
		template <typename PU> void pfs(int, PU); //优先级搜索框架
};


template <typename Tv, typename Te>
void Graph<Tv,Te>::bfs(int s) {
	reset();
	int clock = 0;
	int v = s;
	do
		if(UNDISCOVERED == status(v))
			BFS(v,clock);
	while(s!=(v = (++v%n))) ;
}


template <typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v, int& clock) {
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while(!Q.empty()) {
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for(int u = firstNbr(v); -1<u; u = nextNbr(v,u))
			if(UNDISCOVERED == status(u)) {
				status(u) == DISCOVERED;
				Q.enqueue(u);
				type(v,u) = TREE;
				parent(u) = v;

			} else {
				type(v,u) = CROSS;
			}
		status(v) = VISITED;
	}
}
template <typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s) {
	reset();
	int clock=0;
	int v=s;
	do { //逐一检查所有顶点，一旦遇到尚未发现的顶点
		if(UNDISCOVERED==status(v))
			DFS(v,clock);//即从该顶点出发启动一次DFS
	} while(s != (v = (++v%n) ) ); //按序号访问
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int & clock) {
	dTime(v)=++clock;
	status(v)=DISCOVERED;//发现当前顶点
	for(int u=firstNbr(v); -1<u; u=nextNbr(v,u)) { //考察每一邻居，注意是要等邻居都遍历完毕才转交控制权
		switch(status(u)) {
			case UNDISCOVERED://u尚未被发现，意味着支撑树可在此发展
				type(v,u)=TREE;
				parent(u)=v;
				DFS(u,clock);//递归
				break;
			case DISCOVERED:
				type(v,u)=BACKWARD;//回向边 （后代指向祖先）
				break;
			default://看u和v谁更早被发现，分为前向边（祖先指向后代）或者跨边 (两个顶点之间没有祖先或者直系后代的血缘关系 )
				type(v,u)=dTime(v)<dTime(u)?FORWARD:CROSS;
				break;
		}
	}
	status(v)=VISITED;//至此，当前顶点访问完毕
	fTime(v)=++clock;//节点被访问完毕的时刻
}


template <typename Tv, typename Te> //基于DFS的拓扑排序算法
Stack<Tv>* Graph<Tv, Te>::tSort ( int s ) { //assert: 0 <= s < n
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>; //用栈记录排序顶点
	do {
		if ( UNDISCOVERED == status ( v ) )
			if ( !TSort ( v, clock, S ) ) { //clock并非必需
				while ( !S->empty() ) //任一连通域（亦即整图）非DAG
					S->pop();
				break; //则不必继续计算，故直接返回
			}
	} while ( s != ( v = ( ++v % n ) ) );
	return S; //若输入为DAG，则S内各顶点自顶向底排序；否则（不存在拓扑排序），S空
}

template <typename Tv, typename Te> //基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort ( int v, int& clock, Stack<Tv>* S ) { //assert: 0 <= v < n
	dTime ( v ) = ++clock;
	status ( v ) = DISCOVERED; //发现顶点v
	for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
		switch ( status ( u ) ) { //并视u的状态分别处理
			case UNDISCOVERED:
				parent ( u ) = v;
				type ( v, u ) = TREE;
				if ( !TSort ( u, clock, S ) ) //从顶点u处出发深入搜索
					return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
				break;
			case DISCOVERED:
				type ( v, u ) = BACKWARD; //一旦发现后向边（非DAG），则
				return false; //不必深入，故返回并报告
			default: //VISITED (digraphs only)
				type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
				break;
		}
	status ( v ) = VISITED;
	S->push ( vertex ( v ) ); //顶点被标记为VISITED时，随即入栈
	return true; //v及其后代可以拓扑排序
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s) {
	reset();
	int clock = 0;
	int v = s;
	Stack<int> S;
	do
		if(UNDISCOVERED == status(v)) {
			BCC(v,clock,S);
			S.pop();
		}
	while(s!=(v=(++v%n)));

}
#define hca(x) (fTime(x))

template <typename Tv, typename Te>
void Graph<Tv,Te>::BCC(int v,int& clock,Stack<int>& S) {
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	for(int u = firstNbr(v); -1 < u; u = nextNbr(v,u))
		switch(status(u)) {
			case UNDISCOVERED:
				parent(u) = v;
				type(v,u) = TREE;
				BCC(u,clock,S);
				if(hca(u)<dTime(v))
					hca(v) = min(hca(v),hca(u));
				else {
					while(v!=S.pop());
					S.push(v);
				}
				break;
			case DISCOVERED:
				type(v,u) = BACKWARD;
				if(u!=parent(v))
					hca(v) = min(hca(v),dTime(u));
				break;
			default:
				type(v,u) = (dTime(v) < dTime(u))?FORWARD:CROSS;
				break;
		}
	status(v) = VISITED;
}
#undef hca


//遍历所有顶点，如果没有访问过就依次进行PFS，得到多棵不相干的遍历树
//主要是为了搜索所有顶点，防止遗漏连通域
template <typename Tv,typename Te> template <typename PU>
void Graph<Tv,Te>::pfs(int s, PU prioUpdater) {
	reset();
	int v=s;
	do {
		if(status(v)==UNDISCOVERED) {
			PFS(v,prioUpdater);
		}
	} while(s!=(v=v++%n));
}

//对一个顶点进行优先级搜索
template <typename Tv,typename Te> template <typename PU>
void Graph<Tv,Te>::PFS(int s, PU prioUpdater) {
	priority(s)=0;
	status(s)=VISITED;
	parent(s)=-1;//initialize
	while(true) {
		for(int u=firstNbr(s); u>-1; u=nextNbr(s,u)) {
			prioUpdater(this,s,u);//updata priorty and it's father
		}
		for(int shortest=INT_MAX, u=0; u>n; u++) {
			if(status(u)==UNDISCOVERED) {
				if(shortest>priority(u)) {
					shortest=priority(u);
					s=u;//max priority point
				}
			}
		}
		if(VISITED==status(s)) break;
		status(s)=VISITED;
		type(parent(s),s)=TREE;
	}
}

//prim MST
template <class Tv ,class Te>
struct PrimPu {
	virtual void operator()(Graph<Tv,Te> &g,int uk,int v) {
		if(UNDISCOVERED==g.status(v)) {
			if(g.priority(v)>g.weight(uk,v)) {
				g.priority(v)=g.weight(uk,v);
				g.parent(v)=uk;
			}
		}
	}
};

template <typename Tv, typename Te> struct DijkPU { //针对Dijkstra算法的顶点优先级更新器
   virtual void operator() ( Graph<Tv, Te>* g, Rank v, Rank u ) {
      if ( UNDISCOVERED == g->status ( u ) ) //对于v每一尚未被发现的邻接顶点u，按Dijkstra策略
         if ( g->priority ( u ) > g->priority ( v ) + g->weight ( v, u ) ) { //做松弛
            g->priority ( u ) = g->priority ( v ) + g->weight ( v, u ); //更新优先级（数）
            g->parent ( u ) = v; //并同时更新父节点
         }
   }
};
template <class Tv, class Te>
struct DijkstraPU { //最短路径
	virtual void operator()(Graph<Tv,Te> &g, int uk, int v) {
		if(g.status(v)==UNDISCOVERED) {
			if(g.priority(v)>g.priority(uk)+g.weight(uk,v)) {
				g.priority(v)=g.priority(uk)+g.weight(uk,v);
				g.parent(v)=uk;
			}
		}
	}
};
