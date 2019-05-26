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
	std::cout << "CCPS616 - Lab 2 - Troy Fernandes" << std::endl;
	std::string x = "12345";
	std::string y = "56785";
	mult4(x, y);
	std::cout << std::endl << std::endl;

	std::string result = mult3a_String(x, y);
	std::cout << std::endl << result;


	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;

}

//TODO: instead of going through each indivdual element in the vector, maybe step larger and index directly?
void mult4(std::string num1, std::string num2) {


	std::vector<std::string> adds;

	std::vector<std::string> preSum;


	std::cout << "\n\n" << std::endl;
	std::cout << std::setw(num1.length() + num2.length()) << std::right << num1 << std::endl << "x";
	std::cout << std::setw(num1.length() + num2.length() - 1) << std::right << num2 << std::endl;
	std::cout << std::string(num1.length() + num2.length(), '_') << std::endl;

	//Since the loop counts in reverse, we need to keep an incrementing counter as well to know how many zeros to pad
	size_t counter = 0;
	//Same as the above counter, but this counter is for the outer for loop
	size_t counter2 = 0;
	//The maximum # of digits the product of num1 & num2 is either M + N or M + N + 1. In this case its M + N
	size_t maxDigits = num2.length() + num1.length();
	//int_fast64_t  sum = 0;
	std::string sum;
	for (size_t j = num2.size(); j--;) {
		for (size_t i = num1.size(); i--;) {

			std::string productRightPadding(counter, '0');
			counter++;


			std::string result = num1[i] + productRightPadding;

			sum = std::to_string((num1[i] - '0') * (num2[j] - '0')) + productRightPadding;


			preSum.push_back(std::string(std::max(int(num1.length() + 1), int(num2.length() + 1)) - (sum.length()), '0') + sum);


		}
		std::string ret = longAddition(preSum);
		preSum.clear();
		std::string rightPadding = std::string(counter2, '0');
		std::string sumString = ret + rightPadding;
		std::string leftPadding = std::string(maxDigits - sumString.length(), '0');
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

	if (operands[0] == "15" && operands[1] == "04") {
		;
	}

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
	if (carry >= 1) {
		summation.insert(0, std::to_string(carry));
	}
	return summation;
}


std::string mult3a_String(std::string x, std::string y)
{
	if (x.empty() || y.empty()) {
		return "0";
	}

	if ((x.length() < 2) && (y.length() < 2)) {
		return std::to_string(std::stoi(x) * std::stoi(y));
	}

	long long int max_num_of_digits = std::max(x.length(), y.length());
	long long int half_of_digits = std::ceil(max_num_of_digits / 2);


	std::string a = std::to_string(std::stoi(x) / (long long int)pow(10, half_of_digits));
	std::string b = std::to_string(std::stoi(x) % (long long int)pow(10, half_of_digits));
	std::string c = std::to_string(std::stoi(y) / (long long int)pow(10, half_of_digits));
	std::string d = std::to_string(std::stoi(y) % (long long int)pow(10, half_of_digits));


	int abMax = std::max(a.length(), b.length());
	int dcMax = std::max(d.length(), c.length());


	std::vector<std::string> aPlusB = {
		{std::string(abMax - a.length(),'0') + a},
		{std::string(abMax - b.length(),'0') + b}
	};

	std::vector<std::string> dPlusC = {
	{std::string(dcMax - d.length(),'0') + d},
	{std::string(dcMax - c.length(),'0') + c}
	};


	std::string z0 = mult3a_String(charToString(b), charToString(d));
	std::string z1 = mult3a_String(charToString(longAddition(aPlusB)), charToString(longAddition(dPlusC)));

	std::string z2 = mult3a_String(charToString(a), charToString(c));

	std::vector<std::string> subtrahend = { {z2},{z0} };

	std::string step4 = longSubtraction(z1, subtrahend);





	std::string z0PaddedRight = z0;
	std::string z1PaddedRight = z1 + std::string(half_of_digits, '0');
	std::string z2PaddedRight = z2 + std::string(half_of_digits * 2, '0');
	std::string s4PaddedRight = step4 + std::string(half_of_digits, '0');

	int zRightPadMax = std::max(std::max(z0PaddedRight.length(), z1PaddedRight.length()), std::max(z2PaddedRight.length(), s4PaddedRight.length()));


	std::string z0Padded = std::string(zRightPadMax - z0PaddedRight.length(), '0') + z0PaddedRight;
	std::string z2Padded = std::string(zRightPadMax - z2PaddedRight.length(), '0') + z2PaddedRight;
	std::string s4Padded = std::string(zRightPadMax - s4PaddedRight.length(), '0') + s4PaddedRight;


	//send z1, z2, z3 to get added as strings
	std::vector<std::string> toAdd = { {z0Padded,s4Padded,z2Padded} };

	std::string vecRes = longAddition(toAdd);


	//std::cout << "z0 = " << z0Padded << std::endl << "s4 = " << s4Padded << std::endl << "z2 = " << z2Padded << std::endl << std::endl;


	return vecRes;
}
std::string charToString(char charachter) {
	return std::string(1, charachter);
}
std::string charToString(std::string charachter) {
	return charachter;
}

//Find the complement of a number
std::string findComplement(std::string number) {

	std::string complement;
	int counter = 0;
	bool firstDigitDone = false;
	size_t startIndex = number.length();

	for (size_t i = number.length(); i--;) {
		if ((number[i] - '0') != 0) {
			startIndex = i;
			break;
		}
		counter++;
	}

	if (number == std::string(counter, '0')) {
		return "0";
	}
	for (size_t i = startIndex + 1; i--;)
	{
		int difference;

		if (!firstDigitDone) {
			difference = 10 - (number[i] - '0');
			firstDigitDone = true;
			complement = std::to_string(difference) + complement;
			//std::cout << difference;
		}
		else {
			difference = 9 - (number[i] - '0');
			complement = std::to_string(difference) + complement;
			//std::cout << difference;
		}


	}

	//std::cout << std::endl;

	complement = complement + std::string(counter, '0');


	return complement;

}

std::string longSubtraction(std::string minuend, std::vector<std::string> subtrahend) {

	std::vector<std::string> toAdd = { {minuend} };
	std::string temp;
	for (std::string operation : subtrahend) {
		temp = findComplement(operation);
		if (temp == "0") {
			continue;
		}
		size_t padding;

		//if (padding < 0 || padding == 18446744073709551615) {
		//	padding = 0;
		//}


		if (temp.length() > minuend.length()) {
			padding = 0;
		}
		else {
			padding = minuend.length() - temp.length();
		}


		std::string ninePadding = std::string(padding, '9');
		temp = ninePadding + temp;
		//std::cout << temp << std::endl;



		toAdd.push_back(temp);
	}

	std::string subResult = longAddition(toAdd);
	return subResult.erase(0, 1);
	//return subResult;

}

void padString(std::string &s1, std::string &s2) {
	int sMax = std::max(s1.length(), s2.length());
	s1 = std::string(sMax - s1.length(), '0') + s1;
	s2 = std::string(sMax - s2.length(), '0') + s2;
}