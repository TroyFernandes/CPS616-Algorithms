#pragma once
std::vector<std::tuple<int, int>*> readBookings(std::string filename);
bool sortByValue(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
bool sortByWeight(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
void bruteForceKnapsack(std::vector<std::tuple<int, int>*> table);
void printTable(std::vector<std::tuple<int, int>*> table);
void bruteForceKnapsack(std::vector<std::tuple<int, int>*> table);
void recursiveKnapsack(std::vector<std::tuple<int, int>*> table);
int knapsack(int i, int weight);
int dynamicKnapsack(std::vector<std::vector<int>>& arr, int i, int weight);
void printItems(std::vector<std::vector<int>>& arr, int locI, int weight);
void printResult(std::vector<std::vector<int>>& matrix);
int dynamicKnapsack2(std::vector<std::vector<int>>& arr, int n, int W);