#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "lab5.h"

//Max weight the "bag" can carry
int maxWeight = -1;

//Create the two arrays
std::vector<int> weights;
std::vector<int> values;


int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 5 - Troy Fernandes" << std::endl << std::endl;

	if (argc < 2) {
		printf("No input file specified!\n");
		std::cin.ignore();
		return 0;
	}

	std::string inputFile = argv[1];

	//The first element for both arrays must be an unused value
	weights.push_back(0);
	values.push_back(0);

	//Read the values from the files and place them into the "weights" and "values" arrays
	readFile(inputFile);

	//Solve using the brute force approach (print out ksBF to see value)
	//int ksBF = bruteforceKnapsack(values.size() - 1, maxWeight);

	//Create our memoization array:
	//Rows = # of values
	//Columns = total weight + 1
	//This creates an array with the very top row and leftmost column with zeros
	std::vector<std::vector<int>> arr((values.size()), std::vector<int>((maxWeight + 1)));

	//Solve using the dynamic approach
	int ksD = dynamicKnapsack(arr, values.size(), maxWeight);

	//Gets a list of indexes for the items we chose
	auto res = getItems(arr);

	//Print out those results 
	printResults(arr, res);

	std::cin.ignore();

	return 0;
}

//Read the data.txt file 
void readFile(std::string filename) {

	std::string line;
	std::ifstream myfile(filename);

	std::vector<int> temp;


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
	}


}


//Brute force version for the knapsack problem
int bruteforceKnapsack(int n, int W) {

	//Tree in this case refers to the imaginary decision tree

	if (n < 0 || W == 0) {
		return 0;
	}
	//if item wont fit in our bag ...
	else if (weights[n] > W) {
		//Don't take the item and pursue the item to the left
		return bruteforceKnapsack(n - 1, W);
	}
	else {
		//try the path in the tree where we don't take the item
		int temp1 = bruteforceKnapsack(n - 1, W);
		//try the path in the tree where we do take the item
		int temp2 = bruteforceKnapsack(n - 1, W - weights[n]) + values[n];
		//Take the optimal value
		return std::max(temp1, temp2);
	}

}


//Bottom-up version for the knapsack problem 
int dynamicKnapsack(std::vector<std::vector<int>>& arr, int n, int W) {

	//Pretty much the same as our brute force approach, only this
	//time we are using a memoization array

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
	//Return the bottom right-most item
	return arr[n - 1][W];
}


//Print the memoization matrix
void printMatrix(std::vector<std::vector<int>>& matrix) {
	std::cout << std::endl << std::endl;
	for (auto i : matrix)
	{
		for (auto j : i) {
			std::cout << std::setw(4) << std::left << j;
		}
		std::cout << std::endl;
	}

}

//Returns a list of indexes for the items chosen
//https://www.youtube.com/watch?v=qOUsP4eoYls @ 10:10 gives a good explanation on how to read the matrix
std::vector<int> getItems(std::vector<std::vector<int>>& matrix) {

	std::vector<int> indexes;
	int runningWeight = maxWeight;
	int j = maxWeight;

	//No need to iterate lengthwise, we have our j index to jump to the proper spot
	for (int i = matrix.size(); i-- > 1;) {

		//If the value above it is different, then add the index to the solution
		if (matrix[i][j] != matrix[i - 1][j]) {
			indexes.push_back(i);
			runningWeight = runningWeight - weights[i];
			j = runningWeight;
		}
	}

	return indexes;
}

//Print the final results
void printResults(std::vector<std::vector<int>>& matrix, std::vector<int>& indexes) {

	int weightTotal = 0;

	std::cout << "Items:  ";
	for (int x : indexes) {
		std::cout << "(" << weights[x] << ", " << values[x] << ") ";
		weightTotal = weightTotal + weights[x];
	}
	std::cout << std::endl << "Value:  " << matrix[matrix.size() - 1][maxWeight] << std::endl;
	std::cout << "Weight: " << weightTotal << std::endl;

}