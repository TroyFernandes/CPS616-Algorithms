#pragma once
std::vector<std::tuple<int, int>*> readBookings(std::string filename);
bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b);
bool canAccommodate(std::vector<std::tuple<int, int>*>& room, const std::tuple<int, int> *toBook);
void schedule(std::vector<std::tuple<int, int>*> bookings);