#pragma once
void readFile(std::string filename);
void printMatrix(std::vector<std::vector<int>>& matrix);
void printResults(std::vector<std::vector<int>>& matrix, std::vector<int>& items);
int dynamicKnapsack(std::vector<std::vector<int>>& arr, int n, int W);
int bruteforceKnapsack(int n, int W);
std::vector<int> getItems(std::vector<std::vector<int>>& matrix);
