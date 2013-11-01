#include "graph.h"

bool *Graph::discovered = new bool[MAXV + 1];
bool *Graph::processed = new bool[MAXV + 1];
int *Graph::parent = new int[MAXV + 1];
bool Graph::finished = false;
int Graph::time = -1;
int *Graph::exit_time = new int[MAXV + 1];
int *Graph::entry_time = new int[MAXV + 1];
stack<int>* Graph::lifo = new stack<int>;
int *Graph::color = new int[MAXV + 1];
bool bipartite = TRUE;

/* CALLBACKS*/

void print_vertex(int v){
	cout << v << " " << endl;
}

void print_edge(int v, int y){
	cout << v << " " << y << endl;
}

void do_nothing(int v = -1){
}

void do_nothing(int v = -1, int y = -1){
}

void Graph::color_edge(int v, int y){
	if(color[v] == color[y]){
		bipartite = FALSE;
		cout << "Not bipartite due to " << v <<"," << y << endl;
	}

	color[y] = color[v] == WHITE ? BLACK : WHITE;
}

void Graph::push_stack(int v){
	lifo->push(v);
}
/* END CALLBACKS*/

EdgeNode::EdgeNode(int y, int weight, EdgeNode *next){
	this->y = y;
	this->weight = weight;
	this->next = next;
}

Graph::Graph(bool directed){
	for(int i = 1; i <= MAXV+1; i++){
		edges[i] = 0;
		this->degree[i] = 0;
	}
	this->directed = directed;
}

void Graph::insert_edge(int x, int y, int weight, bool processed){
	EdgeNode *p = new EdgeNode(y,weight,this->edges[x]);
	this->edges[x] = p; //make new node the head of list
	this->degree[x]++;

	if(!processed && !directed)
		insert_edge(y, x, weight, TRUE);
	else
		this->nedges++;
}

void Graph::print(){
	for(int i = 1; i <= nvertices; i++){
		cout << i << ": ";
		EdgeNode *p = this->edges[i];
		while(p){
			cout << p->y << " ";
			p = p->next;
		}
		cout << endl;
	}
}

void Graph::prepare_search(){
	for(int i = 1; i<= this->nvertices; i++){
		processed[i] = FALSE;
		discovered[i] = FALSE;
		parent[i] = -1;
	}
	finished = FALSE;
	time = -1;
}

void Graph::bfs(int start){
	prepare_search();
	bfs_worker(start, &(do_nothing), &(print_vertex), &(do_nothing));
}

void Graph::dfs(int start){
	prepare_search();
	dfs_worker(start, &(do_nothing), &(print_vertex), &(do_nothing));
}

void Graph::bfs_worker(int start, void(*process_vertex_early)(int v), 
				void(*process_vertex_late)(int v), void(*process_edge)(int v, int y))
{
	queue<int> q;
	int v;
	int y;
	EdgeNode *p;

	q.push(start);
	discovered[start] = TRUE;

	while(q.empty() == FALSE){
		v = q.front();
		q.pop();
		process_vertex_early(v);
		processed[v] = TRUE;
		p = this->edges[v];
		while(p){
			y = p->y;
			if(processed[y] == FALSE || this->directed)
				process_edge(v,y);
			if(discovered[y] == FALSE){
				q.push(y);
				discovered[y] = TRUE;
				parent[y] = v;
			}
			p = p->next;
		}
		process_vertex_late(v);
	}
}

void Graph::dfs_worker(int v, void(*process_vertex_early)(int v), 
				void(*process_vertex_late)(int v), void(*process_edge)(int v, int y))
{
	EdgeNode *p;
	int y;

	if(finished) return;

	discovered[v] = TRUE;

	entry_time[v] = ++time;

	process_vertex_early(v);

	p = this->edges[v];

	while(p){
		y = p->y;
		if(!discovered[y]){
			parent[y] = v;
			process_edge(v,y);
			dfs_worker(y,process_vertex_early, process_vertex_late, process_edge);
		}
		else if( (!processed[y] && parent[v] != y) || (this->directed)){
			process_edge(v,y);
		}
		if(finished) return;
		p = p->next;
	}

	process_vertex_late(v);

	exit_time[v] = ++time;

	processed[v] = TRUE;
}

void Graph::topsort(){
	prepare_search();
	if(!lifo->empty()){
		delete lifo;
		lifo = new stack<int>;
	}
	for(int i = 1; i <= this->nvertices; i++)
		if(discovered[i] == FALSE)
			this->dfs_worker(1, &(do_nothing), &push_stack, &(do_nothing));
	while(!lifo->empty()){
		cout << lifo->top() << " ";
		lifo->pop();
	}
	cout << endl;
}

int Graph::edge_classification(int x, int y){
	if(parent[y] == x)
		return TREE;
	if(discovered[y] && !processed[y])
		return BACK;
	if(!processed[y] && entry_time[x] < entry_time[y])
		return FORWARD;
	if(!processed[y] && entry_time[x] > entry_time[y])
		return CROSS;

	cout << "Warning: Unclassified Edge " << x << "," << y << endl;
}

void Graph::find_path(int y){
	if(parent[y] == -1){
		cout << y << " ";
		return;
	}
	find_path(parent[y]);
	cout << y << " ";
}

void Graph::shortest_path(int v, int y){
	prepare_search();
	this->bfs(v);
	find_path(y);
}

void Graph::twocolor(){
	prepare_search();
	for(int i = 1; i <= this->nvertices; i++){
		if(!discovered[i]){
			color[i] = WHITE;
			this->bfs_worker(i, &(do_nothing), &(do_nothing), &(color_edge));
		}
	}
}

void Graph::connected_components(){
	prepare_search();
	int c = 0;
	for(int i = 1; i <= nvertices; i++){
		if(!discovered[i]){
			c = c + 1;
			cout << "Component" << c << ":" << endl;
			bfs_worker(i, &(do_nothing), &(print_vertex), &(do_nothing));
		}
	}
}