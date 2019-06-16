#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include "lab5.h"

//Max weight the "bag" can carry
int maxWeight = -1;

//Create the two arrays
std::vector<int> weights;
std::vector<int> values;

std::set<int> items;


int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 5 - Troy Fernandes" << std::endl << std::endl;



	if (argc < 2) {
		printf("No input file specified!\n");
		std::cin.ignore();
		return 0;
	}

	std::string inputFile = argv[1];

	//Create the dummy initial inputs
	weights.push_back(0);
	values.push_back(0);

	auto items = readFile(inputFile);


	recursiveKnapsack(items);

	//Wait for keypress before exiting
	std::cin.ignore();


	return 0;
}

std::vector<std::tuple<int, int>*> readFile(std::string filename) {

	std::string line;
	std::ifstream myfile(filename);

	std::vector<int> temp;

	std::vector<std::tuple<int, int>*> bookings;

	//Save the available number of rooms
	std::getline(myfile, line);
	maxWeight = std::stoi(line);

	while (getline(myfile, line))
	{
		std::istringstream ss(line);
		std::string token;
		while (getline(ss, token, ' ')) {
			temp.push_back(std::stoi(token));
		}
	}

	int step = temp.size() / 2;

	for (size_t x = 0; x < step; ++x) {
		weights.push_back(temp[x]);
		values.push_back(temp[x + step]);
		//std::tuple<int, int>* booking = new std::tuple<int, int>(temp[x], temp[x + step]);
		//bookings.push_back(booking);
	}

	//printTable(bookings);

	return bookings;
}

void printTable(std::vector<std::tuple<int, int>*> table) {
	int counter = 1;
	std::cout << std::endl << "Item\tWeight\tValue" << std::endl;

	for (auto x : table) {
		std::cout << counter++ << "\t" << std::get<0>(*x) << "\t" << std::get<1>(*x) << std::endl;
	}
	std::cout << std::endl << std::endl;
}


void recursiveKnapsack(std::vector<std::tuple<int, int>*> table) {




	//for (auto x : table) {
	//	weights.push_back(std::get<0>(*x));
	//	values.push_back(std::get<1>(*x));
	//}
	std::vector<std::vector<int>> arr((values.size() + 0), std::vector<int>((maxWeight + 1)));

	std::cout << "Dynamic: " << dynamicKnapsack(arr, values.size() - 0, maxWeight);



	printMatrix(arr);

	auto res = getItems(arr);

	printResults(arr, res);

}

int bruteforceKnapsack(int i, int weight) {
	if (i < 0 || weight == 0) {
		return 0;
	}
	else if (weights[i] > weight) {
		return bruteforceKnapsack(i - 1, weight);
	}
	else {
		int temp1 = bruteforceKnapsack(i - 1, weight);
		int temp2 = bruteforceKnapsack(i - 1, weight - weights[i]) + values[i];
		int max = std::max(temp1, temp2);
		std::cout << max << std::endl;
		items.insert(max);

		return max;
	}
}



int dynamicKnapsack(std::vector<std::vector<int>>& arr, int n, int W) {

	for (int i = 1; i < n; ++i) {
		for (int w = 0; w <= W; ++w) {
			if (weights[i] > w) {
				arr[i][w] = arr[i - 1][w];
			}
			else {
				arr[i][w] = std::max(arr[i - 1][w], values[i] + arr[i - 1][w - weights[i]]);
			}
		}
	}

	return arr[n - 1][W];

}





void printMatrix(std::vector<std::vector<int>>& matrix) {


	std::cout << std::endl << std::endl;
	//std::cout << std::setw(4) << std::left << matrix.size() << std::endl;
	for (auto i : matrix)
	{
		for (auto j : i) {
			std::cout << std::setw(4) << std::left << j;
		}
		std::cout << std::endl;
	}

}

std::vector<int> getItems(std::vector<std::vector<int>>& matrix) {

	std::vector<int> solution;
	int runningWeight = maxWeight;
	int j = maxWeight;



	for (int i = matrix.size(); i-- > 1;) {

		//If the value above it is different, then add the index to the solution and exit this loop
		if (matrix[i][j] != matrix[i - 1][j]) {
			solution.push_back(i);
			runningWeight = runningWeight - weights[i];
			j = runningWeight;
			//break;
		}
	}

	return solution;
}

void printResults(std::vector<std::vector<int>>& matrix, std::vector<int>& items) {
	int weightTotal = 0;

	std::cout << "Items:  ";
	for (int x : items) {
		//std::cout << "(" << std::get<0>(*table[x]) << "," << std::get<1>(*table[x]) << ") ";
		std::cout << "(" << weights[x] << ", " << values[x] << ") ";
		weightTotal = weightTotal + weights[x];
	}
	std::cout << std::endl << "Value:  " << matrix[matrix.size() - 1][maxWeight] << std::endl;
	std::cout << "Weight: " << weightTotal << std::endl;
}