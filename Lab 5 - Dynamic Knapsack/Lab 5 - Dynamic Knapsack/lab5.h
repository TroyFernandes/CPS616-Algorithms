#pragma once
std::vector<std::tuple<int, int>*> readFile(std::string filename);
bool sortByValue(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
bool sortByWeight(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
void bruteForceKnapsack(std::vector<std::tuple<int, int>*> table);
void printTable(std::vector<std::tuple<int, int>*> table);
void bruteForceKnapsack(std::vector<std::tuple<int, int>*> table);
void recursiveKnapsack(std::vector<std::tuple<int, int>*> table);
int bruteforceKnapsack(int i, int weight);
int dynamicKnapsack(std::vector<std::vector<int>>& arr, int i, int weight);
void printMatrix(std::vector<std::vector<int>>& matrix);
int dynamicKnapsack(std::vector<std::vector<int>>& arr, int n, int W);
std::vector<int> getItems(std::vector<std::vector<int>>& matrix);
void printResults(std::vector<std::vector<int>>& matrix, std::vector<int>& items);