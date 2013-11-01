#include "graph.h"

int main(){
	Graph g(FALSE);
	int m, x, y;
	cin >> g.nvertices >> m;
	for(int i = 1; i <=m; i++){
		cin >> x >> y;
		g.insert_edge(x,y);
	}
	g.print();

	g.connected_components();
}