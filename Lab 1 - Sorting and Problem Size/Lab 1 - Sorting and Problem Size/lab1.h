#pragma once
#include <vector>
struct Results {
	std::string algoName;
	std::vector<std::string> results;
	int xValue;
};

void selectionSort(int arr[], size_t arr_size, int startIndex);
void merge(int arr[], int leftIndex, int middleIndex, int rightIndex);
void mergeSortRegular(int arr[], int leftIndex, int rightIndex);
void mergeSelSort(int arr[], int leftIndex, int rightIndex, int subArraySize = 64);
void runFunction(int function, int arr[], size_t arr_size, std::vector<Results>& results, int subArraySize = 64, int index = -1);
void generateArray(int arr[], size_t n_elements);
void printArray(int input[], size_t input_size);
void printArray(int input[], size_t input_size, int startIndex);
void printArrayRanged(int input[], int startIndex, int endIndex);
void sortAndMerge(int arr[], int leftIndex, int rightIndex);
void printResults(std::vector<Results>& results);
void reinitializeArray();