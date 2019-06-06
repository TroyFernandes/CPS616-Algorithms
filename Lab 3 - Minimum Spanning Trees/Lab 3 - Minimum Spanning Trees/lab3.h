#pragma once
std::vector<std::vector<std::tuple<int, int>*>> readGraph(std::string filename);
void printAdjacencyList(std::vector<std::vector<std::tuple<int, int>*>> list);
void kruskal(std::vector<std::vector<std::tuple<int, int>*>> list);
bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b);

void setVisited(std::vector<std::vector<std::tuple<int, int>*>>& list, int atVertex, int atConnectedVertex, std::tuple<int, int> pair);

bool sortByFirst(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b);
bool sortByFirstReverse(const std::tuple<int, std::tuple<int, int>>& a, const std::tuple<int, std::tuple<int, int>>& b);
void prim(std::vector<std::vector<std::tuple<int, int>*>> list);
void printTable(std::vector<std::tuple<bool, int, int>*> table);
void updateConnectedVertices(std::vector<std::vector<std::tuple<int, int>*>>& list, std::vector<std::tuple<bool, int, int>*>& table, int atVertex);

bool checkIfVisited(std::vector<int>& MST, int vertex);
void addToMST(std::vector<std::tuple<int, int>*>& MST, int vertex, int weight);
void addToMST2(std::vector<std::vector<int>>& MST, int vertex, int toVertex, int weight);
void printMatrix(std::vector<std::vector<int>> matrix);
int findParent(std::vector<std::vector<std::tuple<int, int>*>>& list, std::tuple<int, int>* pair);



