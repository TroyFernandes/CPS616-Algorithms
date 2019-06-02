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

#include "lab3.h"

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

	//printAdjacencyList(x);

	kruskal(x);


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;

}


void kruskal(std::vector<std::vector<std::tuple<int, int>*>> list) {

	std::vector<std::string> result;

	//bool *vertexVisited = new bool[list.size()]();
	std::vector<bool> vertexVisited(list.size());

	int vertexCount = list.size() - 1;
	int MSTEdgesMax = vertexCount - 1;
	int MSTEdges = 0;

	//Choose any random vertex
	int startVertex = 1;
	vertexVisited[0] = true;
	vertexVisited[startVertex] = true;


	//Choose the edge with the lowest weight
	int lowestWeight = INT_MAX;
	int lowestWeightVertex = -1;
	int listIndex = 0;
	int otherCounter = 0;
	int otherIndex = 0;

	int setIndex = 0;
	//for (auto connectedVertexes : list[startVertex]) {
	//	if (std::get<1>(*connectedVertexes) < lowestWeight) {
	//		lowestWeight = std::get<1>(*connectedVertexes);
	//	}
	//}

	//Find the lowest weight in entire graph

	//Change this to only loop through the max # of verticies
	//while (!(std::all_of(vertexVisited.begin(), vertexVisited.end(), [](bool v) { return v; }))) {
	while (MSTEdges != MSTEdgesMax) {


		//for (auto connectedVertexes : list) {
		//	otherIndex = 0;
		//	for (auto connectedTo : connectedVertexes) {
		//		if (std::get<1>(*connectedTo) < lowestWeight) {
		//			lowestWeightVertex = std::get<0>(*connectedTo);
		//			lowestWeight = std::get<1>(*connectedTo);
		//			listIndex++;
		//			otherIndex = otherCounter;
		//		}
		//		otherCounter++;
		//		//std::cout << "(" << std::get<0>(*connectedTo) << ", " << std::get<1>(*connectedTo) << ")" << std::endl;
		//	}
		//}


		//for (auto it = list.begin(); it != list.end(); ++it) {

		//	auto x = *it;

		//	for (auto it2 = x.begin(); it2 != x.end(); ++it2) {

		//		auto y = *it2;

		//		if (std::get<1>(*y) < lowestWeight) {
		//			lowestWeightVertex = std::get<0>(*y);
		//			lowestWeight = std::get<1>(*y);
		//			listIndex++;
		//			otherIndex = otherCounter;
		//		}
		//	}
		//}

		for (size_t i = 0; i < list.size(); ++i) {
			for (size_t j = 0; j < list[i].size(); ++j) {
				auto m = list[i][j];
				if (std::get<1>(*m) < lowestWeight) {
					lowestWeightVertex = std::get<0>(*m);
					lowestWeight = std::get<1>(*m);
					listIndex++;
					otherIndex = otherCounter;
					setIndex = i;
				}
			}
		}









		setVisited(list, setIndex, otherIndex, std::make_tuple(lowestWeightVertex, lowestWeight));
		vertexVisited[setIndex] = true;
		vertexVisited[lowestWeightVertex] = true;
		MSTEdges++;
		std::cout << std::endl << setIndex << " -> " << lowestWeightVertex << " Weight: " << lowestWeight << std::endl;

		//std::cout << std::endl << "Connected To:  " << lowestWeightVertex << " With Weight: " << lowestWeight << std::endl;
		//std::cout << std::endl << "List Index:   " << setIndex << std::endl;
		//std::cout << std::endl << "Inner Index:  " << otherIndex << std::endl;

		result.emplace_back(std::to_string(setIndex) + std::string(" -> ") + std::to_string(lowestWeightVertex) + std::string(" Weight: ") + std::to_string(lowestWeight));

		printAdjacencyList(list);

		lowestWeight = INT_MAX;
		lowestWeightVertex = -1;
		setIndex = 0;
		otherCounter = 0;
		otherIndex = 0;


	}


	//setVisited(list, listIndex, otherIndex);
	//vertexVisited[listIndex] = true;

	//Checks if all vertex visited
	//std::cout << std::all_of(vertexVisited.begin(), vertexVisited.end(), [](bool v) { return v; }) << std::endl;






	//printAdjacencyList(list);

	//delete[] vertexVisited;
	std::cout << "MST Found" << std::endl;

	for (auto s : result) {
		std::cout << s << std::endl;
	}

}

void test(std::vector<std::vector<std::tuple<int, int>*>> list) {
	std::vector<std::tuple<int, int, int>> edges;
	std::vector<std::tuple<int, std::tuple<int, int>>> edges2;


	int vertexCounter = 0;
	int connectedToCounter = 0;

	for (auto x : list) {
		std::cout << vertexCounter << std::endl;

		for (auto y : x) {
			//std::cout << "(" << std::get<0>(*y) << ", " << std::get<1>(*y) << ")" << std::endl;
			edges.emplace_back(std::make_tuple(std::get<1>(*y), vertexCounter, std::get<0>(*y)));

			edges2.emplace_back(std::make_tuple(std::get<1>(*y), std::make_tuple(vertexCounter, std::get<0>(*y))));


			connectedToCounter++;
		}
		vertexCounter++;
	}



	std::cout << std::endl << std::endl;




	std::sort(edges2.begin(), edges2.end(), sortByFirstReverse);

	for (auto z : edges2) {
		auto x = std::get<1>(z);
		std::cout << std::get<0>(z) << " (" << std::get<0>(std::get<1>(z)) << ", " << std::get<1>(std::get<1>(z)) << ")" << std::endl;
	}


	std::stack<std::tuple<int, std::tuple<int, int>>> toDo;

	for (auto x : edges2) {
		toDo.push(x);
	}

	while (!toDo.empty()) {

	}



	//for (auto z : edges) {
	//	//Vertex1 to vertex2 with weight of
	//	std::cout << std::get<0>(z) << " (" << std::get<1>(z) << ", " << std::get<2>(z) << ")" << std::endl;
	//}

	//std::sort(edges.begin(), edges.end(), sortByFirst);
	//std::cout << std::endl << std::endl;

	//for (auto z : edges) {
	//	//Vertex1 to vertex2 with weight of
	//	std::cout << std::get<0>(z) << " (" << std::get<1>(z) << ", " << std::get<2>(z) << ")" << std::endl;
	//}

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

