#pragma once
std::vector<std::vector<std::tuple<int, int>*>> readGraph(std::string filename);
void printAdjacencyList(std::vector<std::vector<std::tuple<int, int>*>> list);
void kruskal(std::vector<std::vector<std::tuple<int, int>*>> list);
bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b);

void setVisited(std::vector<std::vector<std::tuple<int, int>*>>& list, int atVertex, int atConnectedVertex, std::tuple<int, int> pair);

void test(std::vector<std::vector<std::tuple<int, int>*>> list);
bool sortByFirst(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b);
bool sortByFirstReverse(const std::tuple<int, std::tuple<int, int>>& a, const std::tuple<int, std::tuple<int, int>>& b);
void readMatrix(std::string filename);