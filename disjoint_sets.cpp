#include "disjoint_sets.h"
#include <iostream>
#include <iomanip>
using namespace std;

DisjointSets::DisjointSets(int num_sets){
	size = num_sets;
	parent = new int[num_sets+1];
	for(int i = 1; i <= num_sets; i++)
		parent[i] = -1;
}

int DisjointSets::find(int x){
	if(parent[x] < 0)
		return x;
	else
		return find(parent[x]);
}

void DisjointSets::sets_union(int x, int y){
	int root1 = find(x);
	int root2 = find(y);
	if(root1 == root2)
		return;

	if(-root1 < -root2){
		if(parent[root1] == parent[root2])
			parent[root2]--;
		parent[root1] = root2;
	}
	else{
		if(parent[root2] == parent[root1])
			parent[root1]--;
		parent[root2] = root1;
	}
}

void DisjointSets::print(){
	for(int i = 1; i <= size; i++)
		cout  << right << setw(4) << i << " ";
	cout << endl;

	for(int i = 1; i <= size; i++)
		cout << right << setw(4) << parent[i] << " ";
	cout << endl;
}