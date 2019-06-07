#pragma once
void prim(std::vector<std::vector<std::tuple<int, int>*>> list);
std::vector<std::vector<std::tuple<int, int>*>> readGraph(std::string filename);
void printAdjacencyList(std::vector<std::vector<std::tuple<int, int>*>> list);
bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
void printTable(std::vector<std::tuple<bool, int, int>*> table);
void updateConnectedVertices(std::vector<std::vector<std::tuple<int, int>*>>& list, std::vector<std::tuple<bool, int, int>*>& table, int atVertex);
void printResult(std::vector<std::vector<int>> matrix);
void updateMatrix(std::vector<std::vector<int>>& resultMatrix, int vertex, int toVertex, int weight);
