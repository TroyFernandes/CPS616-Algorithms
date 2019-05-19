#include <iostream> 
#include <iterator>
#include <string>
#include <algorithm> 
#include <random>
#include <chrono>
#include <tuple>
#include <iomanip>
#include <fstream>
#include "main.h"

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
std::vector<int> xVals = { 1,2,5,10,20,50,64,128,256,512,1024,2048,4096 };

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

//Merge two sub arrays
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L = new int[n1];
	int *R = new int[n2];


	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;

}

//Standard Merge Sort
void mergeSortRegular(int arr[], int l, int r, int subArraySize)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortRegular(arr, l, m);
		mergeSortRegular(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

//Modified Merge sort which send the subarrays to selection sort when the size becomes small enough
void mergeSelSort(int arr[], int l, int r, int subArraySize)
{
	// Same as (l+r)/2, but avoids overflow for large l and h 
	int m = l + (r - l) / 2;

	if (l < r) {

		//printf("\nl = %d, r = %d, m = %d", l, r, m);
		//printf(" \nParent Array (length = %d) ", r - l + 1);
		//printArray(arr, r + 1, l);
		//printf(" Left Child: ");
		//printArray(arr, m + 1, l);
		//printf(" Right array is: ");
		//printArray(arr, r + 1, m + 1);
		//printf("\n");


		if (r - l + 1 <= subArraySize) {
			sortAndMerge(arr, l, r);
			merge(arr, l, m, r);
			return;
		}

		mergeSortRegular(arr, l, m);
		mergeSortRegular(arr, m + 1, r);



		merge(arr, l, m, r);

	}

}

//Helper function for the mergeSelSort function
void sortAndMerge(int arr[], int l, int r) {

	int m = l + (r - l) / 2;


	//printf("Left index: %d \n", l);
	//printf("Middle index: %d \n", m);
	//printf("Right index: %d \n", r);
	//printf("Next Middle index: %d \n", 0 + (m - 0) / 2);


	//printf("\nl = %d, r = %d, m = %d", l, r, m);
	//printf(" Left array is: ");
	//printArray(arr, m + 1, l);
	//printf(" Right array is: ");
	//printArray(arr, r + 1, m + 1);

	selectionSort(arr, m + 1, l);
	selectionSort(arr, r + 1, m + 1);

	//printf("\nSorted left array is \n");
	//printArray(arr, m + 1, l);
	//printf("\nSorted right array is \n");
	//printArray(arr, r + 1, m + 1);

	merge(arr, l, m, r);
	//printf(" Merged Array (length = %d): ", r - l + 1);

	//printArrayRanged(arr, l, r);


	//printf("\n\n");

}

//Fill the array with random numbers ranging from the max size of the array times 4 (i.e 50 element array -> max number that can be in the array = 200)
void generateArray(int arr[], size_t n_elements) {
	const int range_from = 1;
	const int range_to = 4 * (int)n_elements;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	for (int i = 0; i < n_elements; ++i) {
		//std::cout << distr(generator) << ' ';
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

		//std::cout << "\nSelection Sort: Finished sorting n= " << arr_size << " in: " << millisecondsSelSort << " milliseconds";
		//printf("\nSelection Sort: Finished sorting n= %d in: %Lf ms", (int)arr_size, millisecondsSelSort);

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
		//std::cout << "\nMerge Sort: Finished sorting n= " << arr_size << " in: " << millisecondsMergSort << "ms";
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
		//std::cout << index << "   " << results.size() << "\n";

		results[index].algoName = "MergeSel";
		results[index].xValue = subArraySize;
		std::string temp = std::to_string(timeTotal / 10) + "ms";

		results[index].results.push_back(temp);

		//std::cout << "\nMerge + Selection Sort: Finished sorting n= " << arr_size << " in: " << millisecondsMergSelSort << "ms";


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