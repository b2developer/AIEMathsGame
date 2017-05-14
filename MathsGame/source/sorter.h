#pragma once
#include <vector>

//type that contains a value with the original index position that it had before being sorted
template
<typename T>
struct IndexedItem
{
	T value;
	int index;
};

/*
* quickSort
* template with typename T
*
* sorts an array of indexed items using quicksort
* https://en.wikipedia.org/wiki/Quicksort
*
* @param std::vector<IndexedItem<T>> - the array of indexed items
* @returns void
*/
template
<typename T>
std::vector<IndexedItem<T>> quickSort(std::vector<IndexedItem<T>> arr)
{
	size_t size = arr.size();
	quickSortRecursive<T>(&arr, 0, size - 1);

	return arr;
}

/*
* quickSortRecursive
* template with typename T
*
* partitions an array recursively from the index start to the index end 
* until the interval between start and end becomes too small to perform the operation
*
* @param std::vector<IndexedItem<T>> arr - the array of indexed items
* @param int start - the start of the range to apply the algorithm to
* @param int end - the end of the range to apply the algorithm to
* @returns std::vector<IndexedItem<T>> - the sorted array
*/
template
<typename T>
std::vector<IndexedItem<T>> quickSortRecursive(std::vector<IndexedItem<T>>* arr, int start, int end)
{
	//check that the start and end points have items in between them
	if (start >= end)
	{
		return;
	}

	int part = partition(&arr, start, end);

	quickSortRecursive(arr, start, part - 1); //quick sort the lower half
	quickSortRecursive(arr, part + 1, end); //quick sort the upper half

	return arr;
}

/*
* partition
* template with typename T
*
* a sub-algorithm of quicksort, modifies an array (from start to end)
* so every number that proceeds the pivot is
* lower than it and every number that follows the pivot is higher than it
* the pivot will move, so it's new index is returned
*
* @param std::vector<IndexedItem<T>>* arr - the array of indexed items
* @param int start - the start of the range to apply the algorithm to
* @param int end - the end of the range to apply the algorithm to
* @returns int - the new position of the pivot
*/
template
<typename T>
int partition(std::vector<IndexedItem<T>>* arr, int start, int end)
{

	int closed = start;
	int open = start;

	//define a variable to hold a temp when swapping
	IndexedItem<T> temp = {};

	//iterate from start to end
	for (int i = start; i <= end; i++)
	{
		//if the current value is higher than the starting value
		if (arr[i].value > arr[start].value)
		{
			//swap it with the open value
			temp = arr[i];
			arr[i] = arr[open];
			arr[open] = temp;

			//the closed index becomes the open index
			closed = open;

			//the open index gets incremented
			open++;
		}
	}

	//swap the last closed item with the starting item
	temp = arr[closed];
	arr[closed] = arr[start];
	arr[start] = temp;

	return closed;
}

/*
* heapSort
* template with typename T
*
* converts an unsorted array into a binary heap and generates the sorted array by continously
* sifting the largest number from the tree and disgarding it in the next iteration
* https://en.wikipedia.org/wiki/Heapsort
*
* @param std::vector<IndexedItem<T> arr - the array of indexed items
* @returns std::vector<IndexedItem<T>> - the sorted array
*/
template
<typename T>
std::vector<IndexedItem<T>> heapSort(std::vector<IndexedItem<T>> arr)
{
	//create
	arr = heapifyUp<T>(arr, arr.size());

	size_t size = arr.size();

	//transforms a heap into a sorted array by placing the smallest element (always the first in the heap) 
	//at the back and then ignoring it in the next iteration

	for (int i = size - 1; i > 0; i--)
	{
		//"delete" the first heap value (highest) by swapping it with the last and reheapifying the list without it
		IndexedItem<T> temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		//reheapify the heap
		arr = heapifyDown<T>(arr, i);
	}

	return arr;
}


/*
* heapifyUp
* template with typename T
*
* a recursive O(n) sub-algorithm of heapsort that shifts elements
* from the bottom of the heap to the top to achieve a heap structure
*
* @param std::vector<IndexedItem<T>> arr - the array of indexed items
* @param int len - the length of the indexed items array to heapify
* @returns std::vector<IndexedItem<T>> - the new array heapified up
*/
template
<typename T>
std::vector<IndexedItem<T>> heapifyUp(std::vector<IndexedItem<T>> arr, int len)
{
	bool swapped = false;
	
	for (int i = len / 2; i >= 1; i--)
	{
		int left = 2 * i; //the left child in a heap structure
		int right = 2 * i + 1; //the right child in a heap structure

		//check if there is a child node that is more than the current parent
		//swap the nodes if this occurs
		if (left < len && arr[left - 1].value > arr[i - 1].value)
		{
			swapped = true;

			//swap the largest node out of the two children
			if (right < len && arr[right - 1].value > arr[left - 1].value)
			{
				IndexedItem<T> temp = arr[i - 1];
				arr[i - 1] = arr[right - 1];
				arr[right - 1] = temp;				
			}
			else
			{

				IndexedItem<T> temp = arr[i - 1];
				arr[i - 1] = arr[left - 1];
				arr[left - 1] = temp;
			}
		}
		else if (right < len && arr[right - 1].value > arr[i - 1].value)
		{

			IndexedItem<T> temp = arr[i - 1];
			arr[i - 1] = arr[right - 1];
			arr[right - 1] = temp;

			swapped = true;
		}
	}

	//redo the heapify if there was a swap
	if (swapped)
	{
		return heapifyUp(arr, len);
	}

	return arr;
}

/*
* heapifyDown
* template with typename T
*
* a recursive O(n) sub-algorithm of heapsort that shifts elements
* from the top of the heap to the bottom to achieve a heap structure
*
* @param std::vector<IndexedItem<T>> arr - the array of indexed items
* @param int len - the length of the indexed items array
* @returns std::vector<IndexedItem<T>> - the new array heapified up
*/
template
<typename T>
std::vector<IndexedItem<T>> heapifyDown(std::vector<IndexedItem<T>> arr, int len)
{
	bool swapped = false;

	for (int i = 1; i <= len / 2; i++)
	{
		int left = 2 * i; //left child node of the parent
		int right = 2 * i + 1; //right child node of the parent

		//check if there a child node that is more than the current parent
		//swap the nodes if this occurs
		if (left < len && arr[left - 1].value > arr[i - 1].value)
		{
			swapped = true;

			//swap the largest node out of the two children
			if (right < len && arr[right - 1].value > arr[left - 1].value)
			{
				IndexedItem<T> temp = arr[i - 1];
				arr[i - 1] = arr[right - 1];
				arr[right - 1] = temp;
			}
			else
			{

				IndexedItem<T> temp = arr[i - 1];
				arr[i - 1] = arr[left - 1];
				arr[left - 1] = temp;
			}
		}
		else if (right < len && arr[right - 1].value > arr[i - 1].value)
		{

			IndexedItem<T> temp = arr[i - 1];
			arr[i - 1] = arr[right - 1];
			arr[right - 1] = temp;

			swapped = true;
		}
	}

	//redo the heapify if there was a swap
	if (swapped)
	{
		return heapifyUp(arr, len);
	}

	return arr;
}

/*
* shellSort
* template with typename T
*
* observes elements across a gap and swaps them, the gap size decreases (/= 2) until
* it reaches a size of 1, the algorithm behaves like insertion sort when the gap size = 1
* https://en.wikipedia.org/wiki/Shellsort
*
* @param std::vector<IndexedItem<T>> arr - the array of indexed items
* @returns std::vector<IndexedItem<T>> - the sorted array
*/
template
<typename T>
std::vector<IndexedItem<T>> shellSort(std::vector<IndexedItem<T>> arr)
{
	//floor division
	int gap = len / 2;

	while (gap > 0)
	{
		size_t size = arr.size();
		//one pass occurs when end reaches the end of the lost
		for (int end = 0; end < size; end++)
		{
			//tidier and easier to read
			//start is the len rounded down to the nearest multiple of gap
			int start = len + (gap - (len % gap));

			for (; start >= 0; start -= gap)
			{
				int first = start;
				int other = start + gap;

				//if checking a valid pair and the pair are not in order
				if (other < len && arr[first].value > arr[other].value)
				{
					IndexedItem<T> temp = arr[first];
					arr[first] = arr[other];
					arr[other] = temp;
				}
			}
		}

		//floor division
		gap /= 2;
	}

	return arr;
}
