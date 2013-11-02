class DisjointSets{
private:
	int size;
	int *parent;
public:
	DisjointSets(int num_sets);
	void sets_union(int x,int y);
	int find(int x);
	void print();
};