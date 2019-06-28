#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "lab4.h"


int availableRooms = -1;

int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 4 - Troy Fernandes" << std::endl << std::endl;



	if (argc < 2) {
		printf("No input bookings file specified!\n");
		std::cin.ignore();
		return 0;
	}

	std::string inputFile = argv[1];

	auto bookings = readBookings(inputFile);

	schedule(bookings);

	std::cin.ignore();
	return 0;
}

//Reads bookings file and returns a list of tuples containing all the pending bookings
std::vector<std::tuple<int, int>*> readBookings(std::string filename) {

	std::string line;
	std::ifstream myfile(filename);

	std::vector<int> temp;

	std::vector<std::tuple<int, int>*> bookings;

	//Save the available number of rooms
	std::getline(myfile, line);
	availableRooms = std::stoi(line);

	while (getline(myfile, line))
	{
		std::istringstream ss(line);
		std::string token;
		while (getline(ss, token, ' ')) {
			temp.push_back(std::stoi(token));
		}
	}

	int step = temp.size() / 2;

	for (size_t x = 0; x < step; ++x) {

		std::tuple<int, int>* booking = new std::tuple<int, int>(temp[x], temp[x + step]);
		bookings.push_back(booking);
	}

	//Sort the bookings by finish time
	std::sort(bookings.begin(), bookings.end(), sortbySec);


	//for (auto x : bookings) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << "), ";
	//}
	//std::cout << std::endl << std::endl;

	return bookings;
}


bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b) {
	return (std::get<1>(*a) < std::get<1>(*b));
}

bool canAccommodate(std::vector<std::tuple<int, int>*>& room, const std::tuple<int, int> *toBook) {

	//If the room's empty, then the room can accomodate a booking
	if (room.empty()) {
		return true;
	}

	return(
		//Return true if the pending booking ends after (or right when) the previous booking ends
		(std::get<0>(*toBook) >= std::get<1>(*(room.back())))
		);

}

void schedule(std::vector<std::tuple<int, int>*> bookings) {

	//Create a vector containing all the rooms
	std::vector<std::vector<std::tuple<int, int>*>> rooms(availableRooms);
	rooms[0].push_back(bookings[0]);

	//Bookings that can't be accommodated
	std::vector<std::tuple<int, int>*> unavailable;


	for (size_t x = 1; x < bookings.size(); ++x) {

		for (size_t y = 0; y < availableRooms; ++y) {
			if (canAccommodate(rooms[y], bookings[x])) {
				rooms[y].push_back(bookings[x]);
				break;
			}
			//After checking all the rooms, we can't accomodate the booking
			if (y + 1 == availableRooms) {
				unavailable.push_back(bookings[x]);

			}


		}

	}



	std::cout << "Bookings: " << std::endl;

	for (size_t x = 0; x < rooms.size(); ++x) {
		std::cout << x + 1 << " ";
		for (auto x : rooms[x]) {
			std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
		}
		std::cout << std::endl;
	}
	for (auto x : unavailable) {
		std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
	}
	std::cout << std::endl;
}