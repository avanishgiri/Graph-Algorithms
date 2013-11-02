#include <iostream>
#define START_SIZE 1000
using namespace std;

template <class T>
class PriorityQueue{
private:
	T *array;
	int size;
	bool (*priority_func)(T, T);
	int max_size;
public:
	// template <class T>
	PriorityQueue(bool(*priority_func)(T, T)){
		this->priority_func = priority_func;
		this->array = new T[START_SIZE+1];
		this->size = 0;
		this->max_size = START_SIZE;
	}

	// template <class T>
	void insert(T x){
		if(size == max_size){
			max_size *= 2;
			T *new_array = new T[max_size+1];
			for(int i = 0; i <= size; i++)
				new_array[i] = this->array[i];
			this->array = new_array;
		}
		this->array[++size] = x;
		this->bubble_up(size);
	}

	// template <class T>
	void bubble_up(int index){
		int parent_index = index / 2;
		if(parent_index == 0) 
			return;
		if(priority_func(this->array[index], this->array[parent_index])){
			swap(this->array[index], this->array[parent_index]);
			bubble_up(parent_index);
		}
	}

	bool empty(){
		return size == 0;
	}

	void bubble_down(int index){
		int left_child_index = index * 2;
		int right_child_index = index * 2 + 1;
		int swapped = 0;
		for(int i = left_child_index; i <= right_child_index && i <=size; i++){
			if(priority_func(this->array[i], this->array[index])){
				swapped = i;
			}
		}
		if(swapped){
			swap(this->array[swapped], this->array[index]);
			bubble_down(swapped);
		}
	}

	T remove_top(){
		T ret = this->array[1];
		this->array[1] = this->array[size--];
		bubble_down(1);
		return ret;
	}

	void print(){
		for(int i = 1; i <= size; i++)
			cout << array[i] << " ";
		cout << endl;
	}

};