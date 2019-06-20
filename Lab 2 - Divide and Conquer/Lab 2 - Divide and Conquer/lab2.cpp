#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cmath>
#include "lab2.h"

void printVector(std::vector<std::string> vec) {
	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << '\n';

	}
}

int main()
{
	std::cout << "CCPS616 - Lab 2 - Troy Fernandes" << std::endl;

	std::string x1 = "123456789321654987";
	std::string y1 = "987456123321987654";

	std::string x2 = "133970496007220139";
	std::string y2 = "746645028294248337";

	std::string x3 = "872777275638311384";
	std::string y3 = "632021347626727141";

	std::string x4 = "623813767823830495";
	std::string y4 = "879120379304319216";

	std::string x5 = "173272819731896350";
	std::string y5 = "742813639931194919";

	std::string x6 = "933113971301375130";
	std::string y6 = "790624153519637757";

	std::string x7 = "989643469266811014";
	std::string y7 = "183567640201876679";

	std::string x8 = "753098475584844728";
	std::string y8 = "195128092088853064";

	std::string x9 = "525437479812145538";
	std::string y9 = "584198787306725740";

	std::string x10 = "971699898535807985";
	std::string y10 = "537963772279965100";


	for (int n = 0; n < 8; n++) {

		std::cout << std::endl << "k = " << x1.length() << " digits" << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		mult4(x1, y1);
		mult4(x2, y2);
		mult4(x3, y3);
		mult4(x4, y4);
		mult4(x5, y5);
		mult4(x6, y6);
		mult4(x7, y7);
		mult4(x8, y8);
		mult4(x9, y9);
		mult4(x10, y10);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << std::endl << "Time taken by Schoolbook Method:         " << duration.count() / 10 << " microseconds" << std::endl;

		start = std::chrono::high_resolution_clock::now();
		mult3a(x1, y1);
		mult3a(x2, y2);
		mult3a(x3, y3);
		mult3a(x4, y4);
		mult3a(x5, y5);
		mult3a(x6, y6);
		mult3a(x7, y7);
		mult3a(x8, y8);
		mult3a(x9, y9);
		mult3a(x10, y10);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << std::endl << "Time taken by Karatsuba Algo:            " << duration.count() / 10 << " microseconds" << std::endl;


		start = std::chrono::high_resolution_clock::now();
		mult3b(x1, y1);
		mult3b(x2, y2);
		mult3b(x3, y3);
		mult3b(x4, y4);
		mult3b(x5, y5);
		mult3b(x6, y6);
		mult3b(x7, y7);
		mult3b(x8, y8);
		mult3b(x9, y9);
		mult3b(x10, y10);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << std::endl << "Time taken by Karatsuba Algo (Modified): " << duration.count() / 10 << " microseconds" << std::endl;

		//Reduce the string length by two
		x1.erase(x1.size() - 2);
		y1.erase(y1.size() - 2);
		x2.erase(x2.size() - 2);
		y2.erase(y2.size() - 2);
		x3.erase(x3.size() - 2);
		y3.erase(y3.size() - 2);
		x4.erase(x4.size() - 2);
		y4.erase(y4.size() - 2);
		x5.erase(x5.size() - 2);
		y5.erase(y5.size() - 2);
		x6.erase(x6.size() - 2);
		y6.erase(y6.size() - 2);
		x7.erase(x7.size() - 2);
		y7.erase(y7.size() - 2);
		x8.erase(x8.size() - 2);
		y8.erase(y8.size() - 2);
		x9.erase(x9.size() - 2);
		y9.erase(y9.size() - 2);
		x10.erase(x10.size() - 2);
		y10.erase(y10.size() - 2);
	}

	std::cout << "Finished." << std::endl;

	//Wait for keypress before exiting
	std::cin.ignore();

	return 0;

}

//TODO: instead of going through each indivdual element in the vector, maybe step larger and index directly?
void mult4(std::string num1, std::string num2) {


	std::vector<std::string> adds;

	std::vector<std::string> preSum;


	//std::cout << "\n\n" << std::endl;
	//std::cout << std::setw(num1.length() + num2.length()) << std::right << num1 << std::endl << "x";
	//std::cout << std::setw(num1.length() + num2.length() - 1) << std::right << num2 << std::endl;
	//std::cout << std::string(num1.length() + num2.length(), '_') << std::endl;

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

		//std::cout << std::right << sumString << std::endl;

		counter2++;
		counter = 0;
	}


	//std::cout << "Final result: " << totalSum << std::endl;


	size_t maxNumLength = adds[0].length();
	size_t maxHeight = adds.size();

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


	//std::cout << "= " << std::endl;
	//for (auto it = summation.rbegin(); it != summation.rend(); ++it) {
	//	std::cout << *it;
	//}
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

//Karatsuba Algorithm
//Pseudocode: https://en.wikipedia.org/wiki/Karatsuba_algorithm#Pseudocode
std::string mult3a(std::string x, std::string y)
{
	if (x.empty() || y.empty()) {
		return "0";
	}

	if ((x.length() < 2) && (y.length() < 2)) {
		return std::to_string(std::stoi(x) * std::stoi(y));
	}

	long long int max = std::max(x.length(), y.length());
	long long int half = std::ceil(max / 2);


	std::string a = std::to_string(std::stoll(x) / (long long int)pow(10, half));
	std::string b = std::to_string(std::stoll(x) % (long long int)pow(10, half));
	std::string c = std::to_string(std::stoll(y) / (long long int)pow(10, half));
	std::string d = std::to_string(std::stoll(y) % (long long int)pow(10, half));


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


	std::string z0 = mult3a(charToString(b), charToString(d));
	std::string z1 = mult3a(charToString(longAddition(aPlusB)), charToString(longAddition(dPlusC)));
	std::string z2 = mult3a(charToString(a), charToString(c));

	//z3 = z1 - z2 - z0
	std::vector<std::string> subtrahend = { {z2},{z0} };
	std::string z3 = longSubtraction(z1, subtrahend);





	std::string z0PaddedRight = z0;
	std::string z1PaddedRight = z1 + std::string(half, '0');
	std::string z2PaddedRight = z2 + std::string(half * 2, '0');
	std::string s4PaddedRight = z3 + std::string(half, '0');

	int zRightPadMax = std::max(std::max(z0PaddedRight.length(), z1PaddedRight.length()), std::max(z2PaddedRight.length(), s4PaddedRight.length()));


	std::string z0Padded = std::string(zRightPadMax - z0PaddedRight.length(), '0') + z0PaddedRight;
	std::string z2Padded = std::string(zRightPadMax - z2PaddedRight.length(), '0') + z2PaddedRight;
	std::string s4Padded = std::string(zRightPadMax - s4PaddedRight.length(), '0') + s4PaddedRight;


	std::vector<std::string> toAdd = { {z0Padded,s4Padded,z2Padded} };

	std::string result = longAddition(toAdd);
	//std::cout << "z0 = " << z0Padded << std::endl << "s4 = " << s4Padded << std::endl << "z2 = " << z2Padded << std::endl << std::endl;

	return result;
}

//Karatsuba Algorithm
//Pseudocode: https://en.wikipedia.org/wiki/Karatsuba_algorithm#Pseudocode
std::string mult3b(std::string x, std::string y)
{

	//Since we know our input is symmetric, the max "length" we can have is 9999*9999, since 99999*99999 would overflow the integer type (2^31)

	if (x.empty() || y.empty()) {
		return "0";
	}

	if ((x.length() < 5) && (y.length() < 5)) {
		return std::to_string(std::stoi(x) * std::stoi(y));
	}

	long long int max = std::max(x.length(), y.length());
	long long int half = std::ceil(max / 2);


	std::string a = std::to_string(std::stoll(x) / (long long int)pow(10, half));
	std::string b = std::to_string(std::stoll(x) % (long long int)pow(10, half));
	std::string c = std::to_string(std::stoll(y) / (long long int)pow(10, half));
	std::string d = std::to_string(std::stoll(y) % (long long int)pow(10, half));


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


	std::string z0 = mult3b(charToString(b), charToString(d));
	std::string z1 = mult3b(charToString(longAddition(aPlusB)), charToString(longAddition(dPlusC)));
	std::string z2 = mult3b(charToString(a), charToString(c));

	//z3 = z1 - z2 - z0
	std::vector<std::string> subtrahend = { {z2},{z0} };
	std::string z3 = longSubtraction(z1, subtrahend);





	std::string z0PaddedRight = z0;
	std::string z1PaddedRight = z1 + std::string(half, '0');
	std::string z2PaddedRight = z2 + std::string(half * 2, '0');
	std::string s4PaddedRight = z3 + std::string(half, '0');

	int zRightPadMax = std::max(std::max(z0PaddedRight.length(), z1PaddedRight.length()), std::max(z2PaddedRight.length(), s4PaddedRight.length()));


	std::string z0Padded = std::string(zRightPadMax - z0PaddedRight.length(), '0') + z0PaddedRight;
	std::string z2Padded = std::string(zRightPadMax - z2PaddedRight.length(), '0') + z2PaddedRight;
	std::string s4Padded = std::string(zRightPadMax - s4PaddedRight.length(), '0') + s4PaddedRight;


	std::vector<std::string> toAdd = { {z0Padded,s4Padded,z2Padded} };

	std::string result = longAddition(toAdd);
	//std::cout << "z0 = " << z0Padded << std::endl << "s4 = " << s4Padded << std::endl << "z2 = " << z2Padded << std::endl << std::endl;

	return result;
}

long long int mult3c(long long int x, long long int y) {
	if (x < 10 || y < 10) {
		return x * y;
	}

	int max = std::min(std::to_string(x).length(), std::to_string(y).length());
	int half = std::floor(max / 2);

	long long int a = ((x) / (long long int)pow(10, half));
	long long int b = ((x) % (long long int)pow(10, half));
	long long int c = ((y) / (long long int)pow(10, half));
	long long int d = ((y) % (long long int)pow(10, half));

	long long int z0 = mult3c(b, d);
	long long int z1 = mult3c((a + b), (c + d));
	long long int z2 = mult3c(a, c);

	return (z2 * pow(10, half * 2)) + ((z1 - z2 - z0) *  pow(10, half)) + z0;
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

//Instead of making another routine to subtract numbers, we can use this method to change our subtraction into an addition
//https://www.mathsisfun.com/numbers/subtraction-by-addition.html
std::string longSubtraction(std::string minuend, std::vector<std::string> subtrahend) {

	std::vector<std::string> toAdd = { {minuend} };
	std::string temp;
	for (std::string operation : subtrahend) {
		temp = findComplement(operation);
		if (temp == "0") {
			continue;
		}
		size_t padding;

		if (temp.length() > minuend.length()) {
			padding = 0;
		}
		else {
			padding = minuend.length() - temp.length();
		}


		std::string ninePadding = std::string(padding, '9');
		temp = ninePadding + temp;


		toAdd.push_back(temp);
	}

	std::string subResult = longAddition(toAdd);
	return subResult.erase(0, 1);

}

//Equalize the two strings
void padString(std::string &s1, std::string &s2) {
	int sMax = std::max(s1.length(), s2.length());
	s1 = std::string(sMax - s1.length(), '0') + s1;
	s2 = std::string(sMax - s2.length(), '0') + s2;
}