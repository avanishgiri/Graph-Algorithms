#include "graph.h"

int main(){
	Graph g(FALSE);
	int m, x, y, weight;
	cin >> g.nvertices >> m;
	for(int i = 1; i <=m; i++){
		cin >> x >> y >> weight;
		g.insert_edge(x,y,weight);
	}
	g.print();

	g.connected_components();

	g.kruskal();
}