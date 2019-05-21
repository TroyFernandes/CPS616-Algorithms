#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "lab2.h"
//https://stackoverflow.com/questions/16347313/how-to-print-out-2d-arrays-with-function-in-c
template< typename T, size_t N, size_t M >
void printArray(T(&theArray)[N][M]) {
	std::cout << std::endl;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			std::cout << theArray[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

template< typename T, size_t N, size_t M >
void fillArray(T(&theArray)[N][M]) {
	int counter = 0;
	std::cout << std::endl;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			theArray[x][y] = counter;
			counter++;
		}
		std::cout << std::endl;
	}
}

template< typename T, size_t N, size_t M >
void printArrayReverse(T(&theArray)[N][M]) {
	std::cout << std::endl;
	for (size_t x = N; x--;) {
		for (size_t y = M; y--;) {
			std::cout << theArray[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

template< typename T, size_t N, size_t M >
void fillArrayReverse(T(&theArray)[N][M]) {
	int counter = 0;
	std::cout << std::endl;
	for (size_t x = N; x--;) {
		for (size_t y = M; y--;) {
			theArray[x][y] = counter;
			counter++;
		}
		std::cout << std::endl;
	}
}


void printVector(std::vector<std::string> vec) {
	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << '\n';

	}
}

int main()
{
	std::cout << "CCPS616 - Lab 2 - Troy Fernandes";


	//mult4("46339", "46339");
	//mult4("234", "222");

	mult4("35634742561435633563474256143563", "89765584587189763563474256143563");

	//std::string str = "1111111111111111111111111111111111111111111111111111111111";


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;
}

void mult4(std::string num1, std::string num2) {


	std::vector<std::string> adds;

	std::vector<std::string> preSum;


	std::cout << "\n\n" << std::endl;
	std::cout << std::setw(num1.length() + num2.length()) << std::right << num1 << std::endl << "x";
	std::cout << std::setw(num1.length() + num2.length() - 1) << std::right << num2 << std::endl;
	std::cout << std::string(num1.length() + num2.length(), '_') << std::endl;


	size_t counter = 0;
	size_t counter3 = num2.length() + num1.length();
	//int_fast64_t  sum = 0;
	std::string sum;
	size_t counter2 = 0;
	for (size_t j = num2.size(); j--;) {
		for (size_t i = num1.size(); i--;) {

			std::string stuff(counter, '0');
			counter++;


			std::string result = num1[i] + stuff;

			sum = std::to_string((num1[i] - '0') * (num2[j] - '0')) + stuff;


			preSum.push_back(std::string(std::max(int(num1.length() + 1), int(num2.length() + 1)) - (sum.length()), '0') + sum);


		}
		std::string ret = longAddition(preSum);
		preSum.clear();
		std::string rightPadding = std::string(counter2, '0');
		std::string sumString = ret + rightPadding;
		std::string leftPadding = std::string(counter3 - sumString.length(), '0');
		sumString = leftPadding + sumString;


		sum.clear();

		adds.push_back(sumString);

		std::cout << std::right << sumString << std::endl;

		counter2++;
		counter = 0;
	}


	//std::cout << "Final result: " << totalSum << std::endl;


	size_t maxNumLength = adds[0].length();
	//std::cout << "Max Num length = " << maxNumLength << std::endl;

	size_t maxHeight = adds.size();
	//std::cout << "Max Size = " << maxHeight << std::endl;



	std::string summation;


	int i, j, sum2 = 0;
	int carry = 0;

	for (i = maxNumLength; i--;)
	{
		for (j = 0; j < maxHeight; ++j) {
			adds[j][i] = ((adds[j][i] - '0') + carry) + '0';
			carry = 0;
			sum2 += (adds[j][i] - '0');
		}
		summation += std::to_string(sum2 % 10);
		carry = sum2 / 10;
		sum2 = 0;
	}


	std::cout << "= " << std::endl;
	for (auto it = summation.rbegin(); it != summation.rend(); ++it) {
		std::cout << *it;
	}
}

std::string longAddition(std::vector<std::string> &operands) {
	std::string summation;


	int i, j, sum2 = 0;
	int carry = 0;

	for (i = operands[0].length(); i--;)
	{
		for (j = 0; j < operands.size(); ++j) {
			operands[j][i] = ((operands[j][i] - '0') + carry) + '0';
			carry = 0;
			sum2 += (operands[j][i] - '0');
		}
		summation.insert(0, std::to_string(sum2 % 10));
		carry = sum2 / 10;
		sum2 = 0;
	}
	return summation;
}