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

int maxWeight = -1;

//Create the two arrays
std::vector<int> weights;
std::vector<int> values;

std::set<int> items;


int ksCalls, ksDynamicCalls = 0;


int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 5 - Troy Fernandes" << std::endl << std::endl;



	if (argc < 2) {
		printf("No input bookings file specified!\n");
		std::cin.ignore();
		return 0;
	}

	std::string inputFile = argv[1];

	auto bookings = readBookings(inputFile);

	//bruteForceKnapsack(bookings);


	recursiveKnapsack(bookings);

	//Wait for keypress before exiting
	std::cin.ignore();


	return 0;
}

//Reads bookings file and returns a list of tuples containing all the pending bookings
std::vector<std::tuple<int, int>*> readBookings(std::string filename) {

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

		std::tuple<int, int>* booking = new std::tuple<int, int>(temp[x], temp[x + step]);
		bookings.push_back(booking);
	}

	//Sort the bookings by finish time
	//std::sort(bookings.begin(), bookings.end(), sortByWeight);


	//for (auto x : bookings) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ")" << std::endl;
	//}
	//std::cout << std::endl << std::endl;

	printTable(bookings);

	return bookings;
}

bool sortByValue(const std::tuple<int, int> *a, const std::tuple<int, int> *b) {
	return (std::get<1>(*a) > std::get<1>(*b));
}
bool sortByWeight(const std::tuple<int, int> *a, const std::tuple<int, int> *b) {
	return (std::get<0>(*a) > std::get<0>(*b));
}

void printTable(std::vector<std::tuple<int, int>*> table) {
	int counter = 1;
	std::cout << std::endl << "Item\tWeight\tValue" << std::endl;

	for (auto x : table) {
		std::cout << counter++ << "\t" << std::get<0>(*x) << "\t" << std::get<1>(*x) << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void bruteForceKnapsack(std::vector<std::tuple<int, int>*> table) {

	//The number of items 
	std::vector<int> items;

	//Add the items
	int counter = 0;
	for (auto item : table) {
		items.push_back(counter);
		counter++;
	}

	//This will hold the different combinations of the items
	std::vector<std::vector<int>> combinations(items.size());

	//Add the single items to the combinations list
	for (size_t i = 0; i < items.size(); ++i) {
		combinations[i].push_back(items[i]);
	}

	//Add all the permutations 
	do
	{
		std::vector<int> temp;
		for (int i = 0; i < items.size(); i += 1)
		{
			//(*temp).insert(items[i]);
			temp.push_back(items[i]);
			//std::cout << items[i];
		}
		combinations.push_back(temp);

		//std::cout << std::endl;
	} while (std::next_permutation(items.begin(), items.end()));



	std::vector<std::tuple<int, int>*> optimalItems;

	int itemWeight = 0;
	int itemValue = 0;

	int highestValueIndex = 0;
	int highestValue = 0;


	for (size_t x = 0; x < combinations.size(); ++x) {
		std::cout << "Items: ";
		for (size_t y = 0; y < combinations[x].size(); ++y) {

			if ((itemWeight + std::get<0>(*table[combinations[x][y]])) <= maxWeight) {

				std::cout << "(" << std::get<0>(*table[combinations[x][y]]) << "," << std::get<1>(*table[combinations[x][y]]) << ") ";
				itemWeight += std::get<0>(*table[combinations[x][y]]);
				itemValue += std::get<1>(*table[combinations[x][y]]);
			}

			//std::cout << std::get<1>(*table[y]) << " + ";

		}
		if (itemValue >= highestValue) {
			highestValue = itemValue;
			highestValueIndex = x;
		}
		std::cout << "Item Weight: " << itemWeight << " , Item Value:" << itemValue << std::endl;
		itemWeight = 0;
		itemValue = 0;
	}

	std::cout << std::endl << std::endl << "Highest Value" << std::endl << "Items:  ";

	int weightCounter = 0;
	int valueCounter = 0;
	for (auto x : combinations[highestValueIndex]) {
		if (weightCounter + std::get<0>(*table[x]) <= maxWeight) {
			weightCounter += std::get<0>(*table[x]);
			valueCounter += std::get<1>(*table[x]);
			std::cout << "(" << std::get<0>(*table[x]) << "," << std::get<1>(*table[x]) << ") ";
		}
	}
	std::cout << std::endl << "Value:  " << valueCounter << std::endl;
	std::cout << "Weight: " << weightCounter << std::endl << std::endl << std::endl;

}

void recursiveKnapsack(std::vector<std::tuple<int, int>*> table) {

	weights.push_back(0);
	values.push_back(0);


	for (auto x : table) {
		weights.push_back(std::get<0>(*x));
		values.push_back(std::get<1>(*x));
	}

	std::cout << "Brute Force: " << knapsack(values.size() - 1, maxWeight);
	std::cout << " Calls: " << ksCalls << std::endl;
	//items.erase(std::prev(items.end()));


	//std::vector<std::vector<int>> arr((table.size() + 1), std::vector<int>((maxWeight + 1)));

	std::vector<std::vector<int>> arr((values.size() + 0), std::vector<int>((maxWeight + 1)));

	std::cout << "Dynamic: " << dynamicKnapsack2(arr, values.size() - 0, maxWeight);
	std::cout << " Calls: " << ksDynamicCalls << std::endl;



	printResult(arr);


}

int knapsack(int i, int weight) {
	ksCalls++;
	if (i < 0 || weight == 0) {
		return 0;
	}
	else if (weights[i] > weight) {
		return knapsack(i - 1, weight);
	}
	else {
		int temp1 = knapsack(i - 1, weight);
		int temp2 = knapsack(i - 1, weight - weights[i]) + values[i];
		int max = std::max(temp1, temp2);
		std::cout << max << std::endl;
		items.insert(max);

		return max;
	}
}


int dynamicKnapsack(std::vector<std::vector<int>>& arr, int i, int weight) {
	ksDynamicCalls++;
	int result;

	if (i == 0 || weight == 0) {
		result = 0;
		return result;
	}
	if (arr[i][weight] != 0) {
		return arr[i][weight];
	}

	if (weights[i] > weight) {
		result = dynamicKnapsack(arr, i - 1, weight);
	}
	else {
		int temp1 = dynamicKnapsack(arr, i - 1, weight);
		int temp2 = dynamicKnapsack(arr, i - 1, weight - weights[i]) + values[i];
		result = std::max(temp1, temp2);
		std::cout << result << std::endl;

	}
	arr[i][weight] = result;
	return result;
}

int dynamicKnapsack2(std::vector<std::vector<int>>& arr, int n, int W) {


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




void printItems(std::vector<std::vector<int>>& arr, int locI, int weight) {
	std::set<int> temp;
	int w = weight + 1;
	int i = locI + 1;
	std::vector<std::vector<int>> K = arr;

	while (w > 0 && i > 0) {

		if ((K[i][w] - K[i - 1][w - weights[i - 1]]) == weights[i - 1]) {
			weight += weights[i - 1];
			i = i - 1;
			w = w - weights[i - 2];
		}
		else {
			weight += weights[i - 1];
			i = i - 1;
			w = w - weights[i];
		}

	}
}

void printResult(std::vector<std::vector<int>>& matrix) {


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