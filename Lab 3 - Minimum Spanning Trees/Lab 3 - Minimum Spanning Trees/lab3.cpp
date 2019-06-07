#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <stack>
#include <set>
#include <climits>

#include "lab3.h"

#pragma region BinaryHeap

////
// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MinHeapify(int);

	int parent(int i) { return (i - 1) / 2; }

	// to get index of left child of node at index i
	int left(int i) { return (2 * i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2 * i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0]; }

	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k'
	void insertKey(int k);
};


// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		std::cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

// A utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
//// END OF BINARY HEAP CLASS
#pragma endregion BinaryHeap


int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 3 - Troy Fernandes" << std::endl << std::endl;



	if ((argv != NULL) && (argv[1] == '\0')) {
		printf("No input graph file specified!\n");
		std::cin.ignore();
		return 0;
	}

	//Get the filename passed as a command line argument
	std::string inputFile = argv[1];


	auto x = readGraph(inputFile);

	printAdjacencyList(x);

	prim(x);


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;

}



void prim(std::vector<std::vector<std::tuple<int, int>*>> list) {


	std::vector<int> MSTPrev;

	std::vector<std::tuple<int, int>*> connectedComponents;


	std::vector<std::vector<int>> matrix(list.size() - 1, std::vector<int>(list.size() - 1));


	//Create a priority queue of size n, where n = # of verticies
	MinHeap queue(list.size() - 1);

	//Initialize
	std::vector<std::tuple<bool, int, int>*> table;
	for (auto x = 0; x < list.size(); ++x) {
		std::tuple<bool, int, int>* row = new std::tuple<bool, int, int>(false, INT_MAX, 0);
		//std::cout << "(" << toVertex << ", " << token << ")" << std::endl;
		table.push_back(row);
	}


	//Visit Root Node
	std::get<0>(*(table[1])) = true;
	std::get<1>(*(table[1])) = 0;
	std::get<2>(*(table[1])) = 0;
	MSTPrev.push_back(1);


	//Update connected verticies
	updateConnectedVertices(list, table, 1);


	int lowestVertexWeight = INT_MAX;
	int lowestWeightVertex = 0;

	int parentVertex = 0;

	for (size_t i = 0; i < list.size() - 1 - 1; i++) {
		lowestVertexWeight = INT_MAX;
		for (size_t x = 2; x < table.size(); ++x) {
			if (!std::get<0>(*(table[x]))) {
				if (std::get<1>(*(table[x])) < lowestVertexWeight) {
					lowestVertexWeight = std::get<1>(*(table[x]));
					lowestWeightVertex = x;
					parentVertex = std::get<2>(*(table[x]));
				}
			}

		}
		printTable(table);
		//std::cout << "Lowest vertex Weight: " << lowestVertexWeight << std::endl;
		//std::cout << "Lowest weight vertex: " << lowestWeightVertex << std::endl;

		std::cout << "Vertex: " << parentVertex << " connected to: " << lowestWeightVertex << " weight: " << lowestVertexWeight << std::endl;;

		addToMST2(matrix, parentVertex, lowestWeightVertex, lowestVertexWeight);

		updateConnectedVertices(list, table, lowestWeightVertex);
		printTable(table);
		MSTPrev.push_back(lowestWeightVertex);

	}

	printMatrix(matrix);


}

//Read graph into an adjacency list
std::vector<std::vector<std::tuple<int, int>*>> readGraph(std::string filename) {


	std::string line;
	std::ifstream myfile(filename);

	int vertex = 1;
	int toVertex = 1;


	if (myfile.is_open())
	{

		std::getline(myfile, line);
		int maxVerticies = std::stoi(line);
		//The indexes are gonna be off for now. 0 is going to be empty
		std::vector< std::vector<std::tuple<int, int>*>> adjacencyList(maxVerticies + 1);

		//std::cout << maxVerticies << std::endl;

		while (getline(myfile, line))
		{
			//std::cout << std::endl << "Line: " << vertex << std::endl;


			std::istringstream ss(line);
			std::string token;

			std::vector<std::tuple<int, int>*> row;

			while (getline(ss, token, ' ')) {


				//(toVertex, token)
				if (std::stoi(token) > 0) {

					std::tuple<int, int>* pair = new std::tuple<int, int>(toVertex, std::stoi(token));
					//std::cout << "(" << toVertex << ", " << token << ")" << std::endl;
					row.push_back(pair);
				}

				toVertex++;
			}

			std::sort(row.begin(), row.end(), sortbySec);
			adjacencyList[vertex] = row;


			//Reset the vertex counter;
			toVertex = 1;
			vertex++;
		}

		return adjacencyList;

	}
	else {
		//error and return empty?
	}



	myfile.close();

}

//Print the adjacency list in a readable format
void printAdjacencyList(std::vector<std::vector<std::tuple<int, int>*>> list) {
	std::cout << std::endl << "|Vertex| -> (Connected To Vertex, With Weight Of)" << std::endl;
	int vertex = 0;
	for (auto adjacentVertexes : list) {
		std::cout << std::endl << "|" << vertex << "| -> ";
		for (auto connectedTo : adjacentVertexes) {

			std::cout << "(" << std::get<0>(*connectedTo) << ", " << std::get<1>(*connectedTo) << "), ";
		}
		vertex++;
	}
	std::cout << std::endl;
}

//https://www.geeksforgeeks.org/sorting-vector-tuple-c-ascending-order/
bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b) {
	return (std::get<1>(*a) < std::get<1>(*b));
}

bool sortByFirst(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b)
{
	return (std::get<0>(a) < std::get<0>(b));
}

bool sortByFirstReverse(const std::tuple<int, std::tuple<int, int>>& a, const std::tuple<int, std::tuple<int, int>>& b)
{
	return (std::get<0>(a) > std::get<0>(b));
}


void setVisited(std::vector<std::vector<std::tuple<int, int>*>>& list, int atVertex, int atConnectedVertex, std::tuple<int, int> pair) {

	//atVertex is connected to atConnectedVertex
	//But atConnectedVertex is also connected to atVertex

	size_t locCounter = 0;



	for (auto it = list[atVertex].begin(); it != list[atVertex].end(); ) {

		auto x = *it;

		if ((*x) == std::make_tuple(std::get<0>(pair), std::get<1>(pair))) {
			delete * it;
			it = list[atVertex].erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = list[std::get<0>(pair)].begin(); it != list[std::get<0>(pair)].end(); ) {

		auto x = *it;

		if ((*x) == std::make_tuple(atVertex, std::get<1>(pair))) {
			delete * it;
			it = list[std::get<0>(pair)].erase(it);
		}
		else {
			++it;
		}
	}

	//printAdjacencyList(list);


	//1 is connected to 2
	//atvertex is connected to atconnectedvertex

	//2 is connected to 1
	//tuple[0] is connected to atvertex


}

void printTable(std::vector<std::tuple<bool, int, int>*> table) {
	int counter = 0;
	std::cout << std::endl << "\tV?\tD\tP" << std::endl;

	for (auto x : table) {
		int var = (std::get<1>(*x) == INT_MAX) ? -1 : std::get<1>(*x);
		std::cout << counter++ << "\t" << std::get<0>(*x) << "\t" << var << "\t" << std::get<2>(*x) << std::endl;
	}
}

void updateConnectedVertices(std::vector<std::vector<std::tuple<int, int>*>>& list, std::vector<std::tuple<bool, int, int>*>& table, int atVertex) {
	int vertex;
	std::get<0>(*(table[atVertex])) = true;
	for (auto y : list[atVertex]) {
		//Update the table if the current distance in the table isn't already the lowest
		if (!(std::get<1>(*table[std::get<0>(*y)]) < std::get<1>(*y))) {
			std::get<1>(*table[std::get<0>(*y)]) = std::get<1>(*y);
			std::get<2>(*table[std::get<0>(*y)]) = atVertex;
		}

	}
}

//bool checkIfVisited(std::vector<int>& MST, int vertex) {
//	return std::find(MST.begin(), MST.end(), vertex) != MST.end();
//}

void addToMST(std::vector<std::tuple<int, int>*>& MST, int vertex, int weight) {
	std::tuple< int, int>* temp = new std::tuple< int, int>(vertex, weight);
	MST.push_back(temp);
}

void printMatrix(std::vector<std::vector<int>> matrix) {

	std::ofstream outfile("CCPS616_Lab3_TroyFernandes.txt");



	//outfile << std::endl << std::endl;
	outfile << std::setw(4) << std::left << matrix.size() << std::endl;
	for (auto i : matrix)
	{
		for (auto j : i) {
			outfile << std::setw(4) << std::left << j;
		}
		outfile << std::endl;
	}
	outfile.close();
}


void addToMST2(std::vector<std::vector<int>>& MST, int vertex, int toVertex, int weight) {
	MST[vertex - 1][toVertex - 1] = weight;
	MST[toVertex - 1][vertex - 1] = weight;
}