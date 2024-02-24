//***************************************************************************//
//**
//**  Simple Heap implementation
//**
//***************************************************************************//

#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <vector>
#include <stdexcept>      // std::out_of_range
#include <math.h>         // pow()
#include <string>
#include <limits>
#include<algorithm>

/**
 *  Declaring Heap class
 */
template<typename T>
class Heap
{

private:
	std::vector<T> _items;    // Main vector of elements for heap storage. The first item in the array is a placeholder.

	/*********************************************************************/
	/********************* Start Microassignment zone ********************/

		/**
		 *  Percolates the item specified at by index down
		 *   into its proper location within a heap.
		 *  Used for dequeue operations and array to heap conversions
		 *  MA TODO: Implement percolateDown
		 */
	void percolateDown(unsigned int hole)
	{
		//newest value is now the root
		//need to percolate down to put the value in the right place
		//swap stuff every time
		//first check the left side then the right
		while (has_l_child(hole) || has_r_child(hole)) {//while parent has a child...
			
			if (has_r_child(hole) && has_l_child(hole)) {//if it has both children then you can compare

				if (_items[hole] < _items[r_child_idx(hole)] && _items[hole] < _items[l_child_idx(hole)]) {
					break;//this is where it should be!
				}

				if (_items[l_child_idx(hole)] > _items[r_child_idx(hole)] && _items[hole] > _items[r_child_idx(hole)]) {// if it has right child and right is less than left
						swap(r_child_idx(hole), hole);
						hole = r_child_idx(hole);//increment down so parent is the next child
				}
				else if (_items[l_child_idx(hole)] <= _items[r_child_idx(hole)] && _items[hole] > _items[l_child_idx(hole)]) {// if it has left child and right is less than left

					swap(l_child_idx(hole), hole);
					hole = l_child_idx(hole);//increment down so parent is the next child
				}
				
				else {
					//if it goes inside here that means that there is either no more children or that the parent is smaller than both the child
					//which is exaclty what we want.

					break;

				}
			}
			else if (!has_r_child(hole) && has_l_child(hole)) {
				if (_items[hole] > _items[l_child_idx(hole)]) {// if it has right child and right is less than left
					swap(l_child_idx(hole), hole);
					hole = l_child_idx(hole);//increment down so parent is the next child
				}
				else {
					break;
				}
			}
			else if (has_r_child(hole) && !has_l_child(hole)) {
				if (_items[hole] > _items[r_child_idx(hole)]) {// if it has right child and right is less than left
					swap(r_child_idx(hole), hole);
					hole = r_child_idx(hole);//increment down so parent is the next child
				}
				else {
					break;
				}
			}
			else if (!has_r_child(hole) && !has_l_child(hole)) {
				break;
			}

			
		}
	}


	/**
	 *  Add a new item to the end of the heap and percolate up this item to fix heap property
	 *  Used in inserting new nodes into the heap
	 *  MA TODO: Implement percolateUp
	 */
	void percolateUp(T item)
	{
		//next parent
		// insert new value at the low part of the tree
		_items.push_back(item);
		int idx = last_elem_idx();
		//int tem1 = parent_idx(idx);
		//T temp1 = _items[idx];
		//T temp2 = _items[tem1];
		//if (_items.size() != 2) {
			while (has_parent(idx) && _items[idx] < _items[parent_idx(idx)]) {
				swap(idx, parent_idx(idx));
				idx = parent_idx(idx);//incremnt up
			}
		//}

	}

	void swap(T child_idx, T parent_idx) {
		T temp = _items[child_idx];
		_items[child_idx] = _items[parent_idx];
		_items[parent_idx] = temp;
	}

	int last_elem_idx() {
		return _items.end() - _items.begin() - 1;
	}
	int parent_idx(int idx) {
		return idx / 2;
	}
	int l_child_idx(int idx) {
		return idx * 2;
	}
	int r_child_idx(int idx) {
		return idx * 2 + 1;
	}
	bool has_l_child(int idx) {
		if (idx * 2 < _items.end() - _items.begin()) {
			return true;
		}
		return false;
	}
	bool has_r_child(int idx) {
		if (idx * 2 + 1 < _items.end() - _items.begin()) {
			return true;
		}
		return false;
	}
	bool has_parent(int idx) {
		if (idx / 2 >= 1) {
			return true;
		}
		return false;
	}

	/********************** End Microassigment zone *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap() {
		_items.push_back(std::numeric_limits<T>::min()); // Push a placeholder for the first item in the array
	}


	/**
	 *  Adds a new item to the heap
	 */
	void push(T item)
	{
		percolateUp(item);
	}

	/**
	 *  Removes minimum value from heap
	 */
	T pop()
	{
		long unsigned int last_index = _items.size() - 1;	// Calc last item index
		int root_index = 1;                      // Root index (for readability)

		if (size() == 0) {
			throw std::out_of_range("pop() - No elements in heap");
		}

		T minItem = _items[root_index];

		_items[root_index] = _items[last_index]; // Move last item to root
		_items.pop_back();          // Erase last element entry

		if (size() > 0) {			// Only runs if the heap isn't empty now
			percolateDown(1);       // Fix heap property
		}
		return minItem;
	}


	/**
	 *  Returns true if heap is empty, else false
	 *  Consider the first placeholder in the array
	 */
	bool empty() const
	{
		if (_items.size() == 1) {
			return true;
		}
		else {
			return false;
		}
	}


	/**
	 *  Returns current quantity of elements in heap (N)
	 *  Consider the first placeholder in the array
	 */
	long unsigned int size() const
	{
		return _items.size() - 1;
	}


	/**
	 *  Return heap data in order from the _items vector
	 */
	std::string to_string() const
	{
		std::string ret = "";
		for (unsigned int i = 1; i < _items.size(); i++)
		{
			ret += std::to_string(_items[i]) + " ";
		}
		return ret;
	}
};

#endif
