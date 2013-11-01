#include <iostream>

#include <queue>
#include <stack>
#define MAXV 1000
#define TRUE 1
#define FALSE 0

enum {TREE, BACK, FORWARD, CROSS};
enum {WHITE, BLACK};

using namespace std;

class Graph;

class EdgeNode {
private:
	friend class Graph;
	int y;
	int weight;
	EdgeNode *next;
public:
	EdgeNode(int y, int weight, EdgeNode *next);
};

class Graph {
private:
	EdgeNode *edges[MAXV+1];
	int degree[MAXV+1];
	int nedges;
	bool directed;
	static bool *processed;
	static bool *discovered;
	static int *parent;
	static bool finished;
	static int time;
	static int *entry_time;
	static int *exit_time;
	static stack<int>* lifo;
	static int* color;
public:
	int nvertices;
	Graph(bool directed);
	void insert_edge(int x, int y, int weight = -1, bool processed = FALSE);
	void print();
	void bfs(int start);
	void bfs_worker(int start, void(*process_vertex_early)(int v), 
				void(*process_vertex_late)(int v), void(*process_edge)(int v, int y));
	void prepare_search();
	void dfs(int start);
	void dfs_worker(int start, void(*process_vertex_early)(int v), 
				void(*process_vertex_late)(int v), void(*process_edge)(int v, int y));
	void topsort();
	int edge_classification(int x, int y);
	void find_path(int y);
	void shortest_path(int v, int y);
	void twocolor();
	void connected_components();
	static void color_edge(int v, int y);
	static void push_stack(int v);
};