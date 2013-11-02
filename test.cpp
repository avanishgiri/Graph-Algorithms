#include "priority_queue.h"
#include <iostream>
using namespace std;
bool less_than(int x, int y){
	return x < y;
}

int main(){
	PriorityQueue<int> pq(&(less_than));

	pq.insert(1);
	pq.insert(5);
	pq.insert(-3);
	pq.insert(9);
	pq.insert(7);

	while(!pq.empty())
		cout << pq.remove_top() << endl;
}