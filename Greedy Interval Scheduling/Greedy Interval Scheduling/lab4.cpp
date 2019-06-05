#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "lab4.h"


int availableRooms = NULL;

int main(int argc, char** argv)
{
	std::cout << "CCPS616 - Lab 4 - Troy Fernandes" << std::endl << std::endl;



	if ((argv != NULL) && (argv[1] == '\0')) {
		printf("No input bookings file specified!\n");
		std::cin.ignore();
		return 0;
	}


	//Get the filename passed as a command line argument
	std::string inputFile = argv[1];

	auto bookings = readBookings(inputFile);

	schedule(bookings);


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;
}

std::vector<std::tuple<int, int>*> readBookings(std::string filename) {

	std::string line;
	std::ifstream myfile(filename);

	std::vector<int> temp;

	std::vector<std::tuple<int, int>*> bookings;


	//Discard the available bookings
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

	std::sort(bookings.begin(), bookings.end(), sortbySec);



	for (auto x : bookings) {
		std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << "), ";
	}
	std::cout << std::endl << std::endl;



	return bookings;
}

bool sortbySec(const std::tuple<int, int> *a, const std::tuple<int, int> *b) {
	return (std::get<1>(*a) < std::get<1>(*b));
}

bool canAccommodate(std::vector<std::tuple<int, int>*>& room, const std::tuple<int, int> *toBook) {

	if ((int)(room.size()) - 1 < 0) {
		return true;
	}

	return(

		//The room to be booked dosen't start while another room is booked
		(std::get<0>(*toBook) >= std::get<1>(*(room[room.size() - 1])))

		);

}

void schedule(std::vector<std::tuple<int, int>*> bookings) {
	std::tuple<int, int>* previousBooking = bookings[0];

	std::vector<std::vector<std::tuple<int, int>*>> rooms(availableRooms);
	rooms[0].push_back(bookings[0]);

	std::vector<std::tuple<int, int>*> room1, room2, room3, unavailable;

	room1.push_back(previousBooking);


	//for (size_t x = 1; x < bookings.size(); ++x) {

	//	if (canAccommodate(room1, bookings[x])) {
	//		room1.push_back(bookings[x]);
	//		continue;
	//	}

	//	if (canAccommodate(room2, bookings[x])) {
	//		room2.push_back(bookings[x]);
	//		continue;
	//	}
	//	if (canAccommodate(room3, bookings[x])) {
	//		room3.push_back(bookings[x]);
	//		continue;
	//	}
	//	unavailable.push_back(bookings[x]);
	//}

	for (size_t x = 1; x < bookings.size(); ++x) {

		for (size_t y = 0; y < availableRooms; ++y) {
			if (canAccommodate(rooms[y], bookings[x])) {
				rooms[y].push_back(bookings[x]);
				break;
			}
			if (y + 1 == availableRooms) {
				unavailable.push_back(bookings[x]);

			}


		}

	}



	std::cout << "Bookings: " << std::endl;

	//std::cout << "1 ";
	//for (auto x : room1) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
	//}
	//std::cout << std::endl;
	//std::cout << "2 ";
	//for (auto x : room2) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
	//}
	//std::cout << std::endl;
	//std::cout << "3 ";
	//for (auto x : room3) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
	//}
	//for (auto x : unavailable) {
	//	std::cout << "(" << std::get<0>(*x) << ", " << std::get<1>(*x) << ") ";
	//}
	//std::cout << std::endl;

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