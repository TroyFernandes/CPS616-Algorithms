#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>

#include <climits>

#include "lab3.h"



int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 3 - Troy Fernandes" << std::endl << std::endl;


	//if ((argv != NULL) && (argv[1] == '\0')) {
	if (argc < 2) {
		printf("No input graph file specified!\n");
		std::cin.ignore();
		return 0;
	}

	std::string inputFile = argv[1];


	//Read the graph into an adjacency list
	auto x = readGraph(inputFile);

	//Print out the list
	printAdjacencyList(x);

	//Run prim's algo on the adjacency list
	prim(x);

	std::cin.ignore();
	return 0;
}


/*
	Use Prim's algorithim to find a Minimum spanning tree.
*/
void prim(std::vector<std::vector<std::tuple<int, int>*>> list) {

	//The resulting adjacency matrix
	std::vector<std::vector<int>> matrix(list.size() - 1, std::vector<int>(list.size() - 1));

	//Table in the form of: Vertex | isVisited | Distance from Parent | Parent Vertex
	std::vector<std::tuple<bool, int, int>*> table;


	//Initialize the table to the default values
	for (auto x = 0; x < list.size(); ++x) {
		std::tuple<bool, int, int>* row = new std::tuple<bool, int, int>(false, INT_MAX, 0);
		table.push_back(row);
	}


	//Mark the root node as visited
	std::get<0>(*(table[1])) = true;
	std::get<1>(*(table[1])) = 0;
	std::get<2>(*(table[1])) = 0;


	//Update connected vertices
	updateConnectedVertices(list, table, 1);


	int lowestVertexWeight = INT_MAX;
	int lowestWeightVertex = 0;
	int parentVertex = 0;

	//We know a MST has n-1 edges, where n = # of vertecies 
	for (size_t i = 0; i < list.size() - 1 - 1; i++) {
		lowestVertexWeight = INT_MAX;
		//Start at index 2 since the 0th entry is never used, and since vertex 1 is already marked as visited
		for (size_t x = 2; x < table.size(); ++x) {
			//If the vertex isnt visited yet
			if (!std::get<0>(*(table[x]))) {
				//Find the lowest weight vertex
				if (std::get<1>(*(table[x])) < lowestVertexWeight) {
					lowestVertexWeight = std::get<1>(*(table[x]));
					lowestWeightVertex = x;
					parentVertex = std::get<2>(*(table[x]));
				}
			}

		}
		//std::cout << "Lowest vertex Weight: " << lowestVertexWeight << std::endl;
		//std::cout << "Lowest weight vertex: " << lowestWeightVertex << std::endl;

		std::cout << "Vertex: " << parentVertex << " connected to: " << lowestWeightVertex << " weight: " << lowestVertexWeight << std::endl;;

		updateMatrix(matrix, parentVertex, lowestWeightVertex, lowestVertexWeight);

		updateConnectedVertices(list, table, lowestWeightVertex);
		//printTable(table);

	}

	printResult(matrix);

	std::cout << std::endl << "MST Found" << std::endl;

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
		myfile.close();

		return adjacencyList;

	}


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

//Print our table in a more readable format
//The 0th entry is never used. This is for readability purposes
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

//Print our resulting matrix to file. 
//NOTE: start reading the matrix if it were indexed starting at 1.
//i.e, normally you would read 0 0 1 0 0 as "vertex 0, vertex 1, ...". Instead start reading the first line as "vertex 1, vertex 2 ..."
void printResult(std::vector<std::vector<int>> matrix) {

	std::cout << std::endl << "Result Adjacency Matrix" << std::endl;

	for (auto i : matrix)
	{
		for (auto j : i) {
			std::cout << std::setw(4) << std::left << j;
		}
		std::cout << std::endl;
	}
}

//Update our resulting matrix
void updateMatrix(std::vector<std::vector<int>>& resultMatrix, int vertex, int toVertex, int weight) {
	resultMatrix[vertex - 1][toVertex - 1] = weight;
	resultMatrix[toVertex - 1][vertex - 1] = weight;
}