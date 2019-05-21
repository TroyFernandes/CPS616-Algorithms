#include <iostream> 
#include <iterator>
#include <string>
#include <algorithm> 
#include <random>
#include <chrono>
#include <tuple>
#include <iomanip>
#include <fstream>
#include "lab1.h"

enum SortingAlgo { MERGE = 1, SELECTION = 2, MERGSEL = 3 };

enum N_Elements { N1 = 0, N2 = 1, N3 = 2, N4 = 3, N5 = 4 };

//Size of the arrays to be sorted
const int arr_size = 500;
const int arr2_size = 1000;
const int arr3_size = 5000;
const int arr4_size = 10000;
const int arr5_size = 50000;

//Arrays to be sorted
int arr[arr_size] = {};
int arr2[arr2_size] = {};
int arr3[arr3_size] = {};
int arr4[arr4_size] = {};
int arr5[arr5_size] = {};

//Minimum size of the sub array before being sent to selection sort
//Add values to this vector if you want to test different subarray sizes
std::vector<int> xVals = { 1,2,5,10,20,50,64,128,250,500,1000,2500,5000 };

int main()
{
	std::cout << "CCPS616 - Lab 1 - Troy Fernandes \n\n";


	std::vector<Results> results;
	results.push_back(Results()); // Selection Sort Results (index = 0)
	results.push_back(Results()); // Merge Sort Results (index = 1)
	results[0].algoName = "Selection";
	results[1].algoName = "Merge";

	//Empty and refill array
	reinitializeArray();



	//Run selection sort on the 5 arrays
	runFunction(SELECTION, arr, arr_size, results);
	runFunction(SELECTION, arr2, arr2_size, results);
	runFunction(SELECTION, arr3, arr3_size, results);
	runFunction(SELECTION, arr4, arr4_size, results);
	runFunction(SELECTION, arr5, arr5_size, results);

	//Empty and refill array
	reinitializeArray();

	//Run merge sort on the 5 arrays
	runFunction(MERGE, arr, arr_size, results);
	runFunction(MERGE, arr2, arr2_size, results);
	runFunction(MERGE, arr3, arr3_size, results);
	runFunction(MERGE, arr4, arr4_size, results);
	runFunction(MERGE, arr5, arr5_size, results);


	//loop through the xVals array (i.e the minimum size of the array before it's sent to selection sort)
	for (auto it = xVals.begin(); it != xVals.end(); ++it) {
		const auto index = std::distance(xVals.begin(), it) + 2;
		results.push_back(Results());
		auto & x = *it;
		//Empty and refill array
		reinitializeArray();
		//Run merge + selection sort on the 5 arrays
		runFunction(MERGSEL, arr, arr_size, results, x, index);
		runFunction(MERGSEL, arr2, arr2_size, results, x, index);
		runFunction(MERGSEL, arr3, arr3_size, results, x, index);
		runFunction(MERGSEL, arr4, arr4_size, results, x, index);
		runFunction(MERGSEL, arr5, arr5_size, results, x, index);
	}


	//Print the results to file
	printResults(results);


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;
}

/*
Selection sort taken from https://en.wikipedia.org/wiki/Selection_sort
*/

//Standard Selection Sort
void selectionSort(int arr[], size_t arr_size, int startIndex) {

	int n = arr_size;

	for (int j = startIndex; j < n - 1; j++) {

		int iMin = j;

		for (int i = j + 1; i < n; i++) {
			if (arr[i] < arr[iMin]) {
				iMin = i;

			}
		}

		if (iMin != j) {
			std::swap(arr[j], arr[iMin]);
		}

	}

}

/*
The base implementation for the mergeSortRegular and merge functions are taken
from https://www.geeksforgeeks.org/merge-sort/
*/

//Merge two sub arrays
void merge(int arr[], int leftIndex, int middleIndex, int rightIndex)
{
	int i, j, k;
	int leftArrSize = middleIndex - leftIndex + 1;
	int rightArrSize = rightIndex - middleIndex;

	/* create temp arrays */
	int *tempArrL = new int[leftArrSize];
	int *tempArrR = new int[rightArrSize];


	/* Copy data to temp arrays tempArrL[] and tempArrR[] */
	for (i = 0; i < leftArrSize; i++)
		tempArrL[i] = arr[leftIndex + i];
	for (j = 0; j < rightArrSize; j++)
		tempArrR[j] = arr[middleIndex + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = leftIndex; // Initial index of merged subarray 
	while (i < leftArrSize && j < rightArrSize)
	{
		if (tempArrL[i] <= tempArrR[j])
		{
			arr[k] = tempArrL[i];
			i++;
		}
		else
		{
			arr[k] = tempArrR[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of tempArrL[], if there
	   are any */
	while (i < leftArrSize)
	{
		arr[k] = tempArrL[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of tempArrR[], if there
	   are any */
	while (j < rightArrSize)
	{
		arr[k] = tempArrR[j];
		j++;
		k++;
	}
	delete[] tempArrL;
	delete[] tempArrR;

}

//Standard Merge Sort
void mergeSortRegular(int arr[], int leftIndex, int rightIndex)
{

	if (leftIndex < rightIndex)
	{
		//Calculate middle index
		int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

		// Sort first and second halves using the standard Merge Sort
		mergeSortRegular(arr, leftIndex, middleIndex);
		mergeSortRegular(arr, middleIndex + 1, rightIndex);

		//Merge the arrays
		merge(arr, leftIndex, middleIndex, rightIndex);
	}
}

//Modified Merge sort which sends the subarrays to selection sort when the size becomes small enough
void mergeSelSort(int arr[], int leftIndex, int rightIndex, int subArraySize)
{

	int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

	if (leftIndex < rightIndex) {

		/*
		subArraySize is the minimum sub array size before the array gets sorted.
		Normally Merge sort would continue to recurse until the sub array size equals 1.
		The default value for subArraySize = 64
		*/
		if (rightIndex - leftIndex + 1 <= subArraySize) {
			sortAndMerge(arr, leftIndex, rightIndex);
			return;
		}

		mergeSelSort(arr, leftIndex, middleIndex, subArraySize);
		mergeSelSort(arr, middleIndex + 1, rightIndex, subArraySize);

		merge(arr, leftIndex, middleIndex, rightIndex);

	}

}

//Helper function for the mergeSelSort function
void sortAndMerge(int arr[], int leftIndex, int rightIndex) {

	int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

	selectionSort(arr, middleIndex + 1, leftIndex);
	selectionSort(arr, rightIndex + 1, middleIndex + 1);

	merge(arr, leftIndex, middleIndex, rightIndex);

}

//Fill the array with random numbers ranging from the max size of the array times 4 (i.e 50 element array -> max value that can be in the array = 200)
void generateArray(int arr[], size_t n_elements) {
	const int range_from = 1;
	const size_t range_to = 4 * n_elements;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	for (size_t i = 0; i < n_elements; ++i) {
		arr[i] = distr(generator);
	}
}

//Helper function to print a whole array
void printArray(int input[], size_t input_size) {
	std::cout << "[ ";
	for (size_t i = 0; i < input_size; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << "]";
}

//Helper function to print a whole array starting at a certain index
void printArray(int input[], size_t input_size, int startIndex) {
	std::cout << "[ ";
	for (size_t i = startIndex; i < input_size; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << "]";
}

//Helper function to print an array between a range of indexes
void printArrayRanged(int input[], int startIndex, int endIndex) {
	std::cout << "[ ";
	for (int i = startIndex; i <= endIndex; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << "]";
}

void runFunction(int function, int arr[], size_t arr_size, std::vector<Results>& results, int subArraySize, int index) {

	switch (function) {

	case SELECTION:
	{
		double timeTotal = 0;

		for (int i = 0; i < 10; i++) {

			auto startSelTimer = std::chrono::high_resolution_clock::now();
			selectionSort(arr, arr_size, 0);
			auto elapsedSelTimer = std::chrono::high_resolution_clock::now() - startSelTimer;
			double millisecondsSelSort = std::chrono::duration<double, std::milli>(elapsedSelTimer).count();
			timeTotal += millisecondsSelSort;

			reinitializeArray();
		}

		std::string temp = std::to_string(timeTotal / 10) + "ms";
		results[0].results.push_back(temp);
		return;
	}
	case MERGE:
	{
		double timeTotal = 0;
		for (int i = 0; i < 10; i++) {

			auto startMergTimer = std::chrono::high_resolution_clock::now();
			mergeSortRegular(arr, 0, arr_size - 1);
			auto elapsedMergTimer = std::chrono::high_resolution_clock::now() - startMergTimer;
			double millisecondsMergSort = std::chrono::duration<double, std::milli>(elapsedMergTimer).count();
			timeTotal += millisecondsMergSort;

			reinitializeArray();

		}
		std::string temp = std::to_string(timeTotal / 10) + "ms";

		results[1].results.push_back(temp);

		return;
	}
	case MERGSEL:
	{
		double timeTotal = 0;
		for (int i = 0; i < 10; i++) {

			auto startMergSelTimer = std::chrono::high_resolution_clock::now();
			mergeSelSort(arr, 0, arr_size - 1, subArraySize);
			auto elapsedMergSelTimer = std::chrono::high_resolution_clock::now() - startMergSelTimer;
			double millisecondsMergSelSort = std::chrono::duration<double, std::milli>(elapsedMergSelTimer).count();
			timeTotal += millisecondsMergSelSort;

			reinitializeArray();
		}

		results[index].algoName = "MergeSel";
		results[index].xValue = subArraySize;
		std::string temp = std::to_string(timeTotal / 10) + "ms";

		results[index].results.push_back(temp);

		return;
	}
	}


}

void printResults(std::vector<Results>& results) {

	//Replace outfile with std::cout if you want results to be printed to the console


	std::ofstream outfile("CCPS616_Lab1_TroyFernandes.txt");

	outfile <<
		std::setw(20) << std::left << "n = "
		<< std::setw(20) << std::left << arr_size
		<< std::setw(20) << std::left << arr2_size
		<< std::setw(20) << std::left << arr3_size
		<< std::setw(20) << std::left << arr4_size
		<< std::setw(20) << std::left << arr5_size << std::endl;

	//Selection Sort
	outfile
		<< std::setw(20) << std::left << results[0].algoName
		<< std::setw(20) << std::left << results[0].results[N1]
		<< std::setw(20) << std::left << results[0].results[N2]
		<< std::setw(20) << std::left << results[0].results[N3]
		<< std::setw(20) << std::left << results[0].results[N4]
		<< std::setw(20) << std::left << results[0].results[N5] << std::endl;

	//Merge Sort
	outfile
		<< std::setw(20) << std::left << results[1].algoName
		<< std::setw(20) << std::left << results[1].results[N1]
		<< std::setw(20) << std::left << results[1].results[N2]
		<< std::setw(20) << std::left << results[1].results[N3]
		<< std::setw(20) << std::left << results[1].results[N4]
		<< std::setw(20) << std::left << results[1].results[N5] << std::endl;

	outfile << std::setw(20) << std::left << "MergeSel" << std::endl;

	for (std::vector<Results>::size_type i = 2; i != results.size(); i++)
	{
		//Merge + Selection Sort
		std::string temp = "x=" + std::to_string(results[i].xValue);
		outfile
			<< std::setw(20) << std::left << temp
			<< std::setw(20) << std::left << results[i].results[N1]
			<< std::setw(20) << std::left << results[i].results[N2]
			<< std::setw(20) << std::left << results[i].results[N3]
			<< std::setw(20) << std::left << results[i].results[N4]
			<< std::setw(20) << std::left << results[i].results[N5] << std::endl;
	}
	outfile.close();
	std::cout << "Finished. Created output file";
}

void reinitializeArray() {
	std::fill_n(arr, arr_size, 0);
	std::fill_n(arr2, arr2_size, 0);
	std::fill_n(arr3, arr3_size, 0);
	std::fill_n(arr4, arr4_size, 0);
	std::fill_n(arr5, arr5_size, 0);


	generateArray(arr, arr_size);
	generateArray(arr2, arr2_size);
	generateArray(arr3, arr3_size);
	generateArray(arr4, arr4_size);
	generateArray(arr5, arr5_size);
}