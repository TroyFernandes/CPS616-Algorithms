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


	//mult4("46339", "46339");
	//mult4("234", "222");

	//mult4("3563474256143563", "897655845");

	//int result = mult3a("3563474256143563", "8976558458718976");
	//long long int x = 321321321321321321;
	//long long int y = 321321321321321321;

	//std::string xString = std::to_string(x);
	//std::string yString = std::to_string(y);

	//long long int result = mult3a_String(x, y);


	//std::string result = mult3a_String("1234145671", "4567112341");
	std::string result = mult3a_String("321321654987", "123456789123");
	std::cout << std::endl << result;
	//std::cout << std::endl << x * y << std::endl;

	//std::vector<std::string> toSub = { {"99"} };
	//std::string res = longSubtraction("9999", toSub);
	//std::cout << res << std::endl;

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



long long int mult3a_OLD(std::string num1, std::string num2) {
	std::cout << std::endl;
	// num < 10 == num.length < 2
	if (num1.length() < 2 || num2.length() < 2) {
		//return num1 * num2;
		//std::cout << num1 << " * " << num2 << " = " << (std::stoi(num1) * std::stoi(num2)) << std::endl;
		return (std::stoi(num1) * std::stoi(num2));
	}

	int numLength = std::min((num1).length(), (num2).length());
	int midpoint = std::floor(float(numLength) / 2);


	std::string x_H = (num1.substr(0, midpoint));
	std::string x_L = (num1.substr(midpoint, num1.length()));

	std::string y_H = (num2.substr(0, midpoint));
	std::string y_L = (num2.substr(midpoint, num2.length()));


	std::string x = x_H + std::string(midpoint, '0') + " + " + x_L;
	std::string y = y_H + std::string(midpoint, '0') + " + " + y_L;

	long long int a = std::stoi(x_H);
	long long int b = std::stoi(x_L);
	long long int c = std::stoi(y_H);
	long long int d = std::stoi(y_L);

	std::cout << "a = " << a << " , b = " << b << std::endl;
	std::cout << "c = " << c << " , d = " << d << std::endl;
	std::cout << "ac = " << a * c << std::endl;
	std::cout << "bd = " << b * d << std::endl;
	std::cout << "(a+b)(c+d) = " << (a + b)*(c + d) << std::endl;
	std::cout << "3 - 2 - 1  = " << (a + b)*(c + d) - (b * d) - (a*c) << std::endl;

	std::cout << a * c << std::string(midpoint * 2, '0') << std::endl;
	std::cout << b * d << std::endl;
	std::cout << (a + b)*(c + d) - (b * d) - (a*c) << std::string(midpoint, '0') << std::endl;

	std::string acString = std::to_string(a * c) + std::string(midpoint * 2, '0');
	std::string bdString = std::to_string(b * d);
	std::string resString = std::to_string((a + b)*(c + d) - (b * d) - (a*c)) + std::string(midpoint, '0');


	std::vector<std::string> dothis = {
		{acString},
		{std::string(acString.length() - bdString.length(),'0') + bdString},
		{std::string(acString.length() - resString.length(),'0') + resString}
	};

	std::string result = longAddition(dothis);

	std::cout << result;
	return 1;
}

long long int mult3a(long long int x, long long int y)
{
	long long int a, b, c, d;								//  These local variables are used to parse the integers passed as parameters
										//  to this function into 4 almost equal parts later in this function. 
	if ((x < 10) && (y < 10))						//  If the integer is less than 10 or has only a unit position then both are simply multiplied .
		return x * y;

	long long int max_num_of_digits = std::max(std::to_string(x).length(), std::to_string(y).length());	//  This uilizes the size_base10 and max functions created above to calculate the number of digits
	long long int half_of_digits = std::ceil(max_num_of_digits / 2);							//  in the larger integer.


	//long long int a = std::stoi(std::to_string(x).substr(0, half_of_digits));
	//long long int b = std::stoi(std::to_string(x).substr(half_of_digits, std::to_string(x).length()));

	//long long int c = std::stoi(std::to_string(y).substr(0, half_of_digits));
	//long long int d = std::stoi(std::to_string(y).substr(half_of_digits, std::to_string(y).length()));


	//if (max_num_of_digits % 2 == 0)
	//	half_of_digits = max_num_of_digits / 2;				//  This if statement makes sure that if the number of digits in the larger integer is odd then the
	//else													//  half of the max number of digits will be rounded up. (The built in round up function can also be
	//	half_of_digits = (max_num_of_digits / 2) + 1;			//  used here)

	a = x / (long long int)pow(10, half_of_digits);							//  Local Variables are parsed into 4 almost equal parts. For example, if the two integers are 1234 
	b = x % (long long int)pow(10, half_of_digits);							//  and 567 then they will be parsed as: a = 12, b = 34, c = 05, d = 67.
	c = y / (long long int)pow(10, half_of_digits);							//  Note: If the size of integer is not equal, the smaller integer is padded with zeros.
	d = y % (long long int)pow(10, half_of_digits);

	// The function recursively called in these statement according to the 
	long long int z0 = mult3a(b, d);									// divide and conquer technique until the breaking condition is returned  
	long long int z1 = mult3a((a + b), (c + d));
	long long int z2 = mult3a(a, c);// i.e. if an integer is less than 10.
	long long int step4 = z1 - z2 - z0;								// This step has reduced the recursive call by 1 and thus reducing the 
	//long long int step5 = (step1 * pow(10, 2 * half_of_digits)) + step2 + (step4 * pow(10, half_of_digits));	// time complexity from O(n^2) to O(n^log3).


	int res1 = z1 + z2 + z0;

	long long int testing = (z2 * pow(10, half_of_digits * 2)) + ((z1 - z2 - z0) * pow(10, half_of_digits)) + z0;

	std::string z0PaddedRight = std::to_string(z0);
	std::string z1PaddedRight = std::to_string(z1) + std::string(half_of_digits, '0');
	std::string z2PaddedRight = std::to_string(z2) + std::string(half_of_digits * 2, '0');
	std::string s4String = (std::to_string(step4) + std::string(half_of_digits, '0'));


	std::string z0Padded = std::string(z2PaddedRight.length() - z0PaddedRight.length(), '0') + (z0PaddedRight);
	std::string z2Padded = (z2PaddedRight); // stays the same 
	std::string s4Padded = std::string(z2PaddedRight.length() - s4String.length(), '0') + s4String;



	//std::vector<std::string> dothis = {
	//{acString},
	//{std::string(acString.length() - bdString.length(),'0') + bdString},
	//{std::string(acString.length() - resString.length(),'0') + resString}
	//};
	std::string leftTerm = std::to_string((z2 * pow(10, half_of_digits * 2)));
	std::string middleTerm;
	std::string rightTerm;
	std::cout << "z0 = " << z0Padded << std::endl << "s4 = " << s4Padded << std::endl << "z2 = " << z2Padded << std::endl << std::endl;
	//std::cout << "z0 = " << z0Padded << std::endl << "z1 = " << z1PaddedRight << std::endl << "z2 = " << z2Padded << " =  " << res1 << std::endl << std::endl;


	//std::cout << "Step 4: " << step4 << std::endl << std::endl;
	//std::cout << "Result: " << testing << std::endl << std::endl;
	//std::cout << "Result: " << std::to_string((int)(z2 * pow(10, half_of_digits * 2))) << " + " << (int)((z1 - z2 - z0) * pow(10, half_of_digits)) << " + " << (int)z0 << " = " << testing << std::endl << std::endl;
	std::cout << "\t  z1 = " << z1 << ", z2 = " << z2 << ", z0 = " << z0 << std::endl;
	std::cout << "Result: " << std::to_string((int)(z2 * pow(10, half_of_digits * 2))) << " + " << "(" << z1 << " - " << z2 << " - " << z0 << ") * " << pow(10, half_of_digits) << " + " << (int)z0 << " = " << testing << std::endl << std::endl;


	return testing;
}


std::string mult3a_String(std::string x, std::string y)
{


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

	//long long int step4 = std::stoll(z1) - std::stoll(z2) - std::stoll(z0);
	std::string step4 = longSubtraction(z1, subtrahend);





	std::string z0PaddedRight = z0;
	std::string z1PaddedRight = z1 + std::string(half_of_digits, '0');
	std::string z2PaddedRight = z2 + std::string(half_of_digits * 2, '0');
	std::string s4PaddedRight = step4 + std::string(half_of_digits, '0');

	int zRightPadMax = std::max(std::max(z0PaddedRight.length(), z1PaddedRight.length()), std::max(z2PaddedRight.length(), s4PaddedRight.length()));


	std::string z0Padded = std::string(zRightPadMax - z0PaddedRight.length(), '0') + (z0PaddedRight);
	std::string z2Padded = z2PaddedRight; // stays the same 
	std::string s4Padded = std::string(zRightPadMax - s4PaddedRight.length(), '0') + s4PaddedRight;


	//send z1, z2, z3 to get added as strings
	std::vector<std::string> toAdd = { {z0Padded,s4Padded,z2Padded} };

	std::string vecRes = longAddition(toAdd);

	//std::cout << "Vector : " << vecRes << std::endl;

	std::cout << "z0 = " << z0Padded << std::endl << "z1 = " << s4Padded << std::endl << "z2 = " << z2Padded << " =  " << "testing" << std::endl << std::endl;


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
		size_t padding = minuend.length() - temp.length();
		if (padding < 0 || padding == 18446744073709551615) {
			padding = 0;
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

std::string mult3a_String2(std::string x, std::string y) {


	if ((x.length() < 2) && (y.length() < 2)) {
		return std::to_string(std::stoi(x) * std::stoi(y));
	}

	long long int max_num_of_digits = std::max(x.length(), y.length());
	long long int half_of_digits = std::ceil(max_num_of_digits / 2);

	std::string a = std::to_string(std::stoi(x) / (long long int)pow(10, half_of_digits)); //high 1
	std::string b = std::to_string(std::stoi(x) % (long long int)pow(10, half_of_digits));// low1
	std::string c = std::to_string(std::stoi(y) / (long long int)pow(10, half_of_digits));//high2
	std::string d = std::to_string(std::stoi(y) % (long long int)pow(10, half_of_digits));//low2

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

	a = std::string(abMax - a.length(), '0') + a;
	b = std::string(abMax - b.length(), '0') + b;
	c = std::string(abMax - c.length(), '0') + c;
	d = std::string(abMax - d.length(), '0') + d;



	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;

	std::string z0 = mult3a_String2(charToString(b), charToString(d));
	std::string z1 = mult3a_String2(charToString(longAddition(aPlusB)), charToString(longAddition(dPlusC))) + std::string(half_of_digits, '0');
	std::string z2 = mult3a_String2(charToString(a), charToString(c)) + std::string(half_of_digits * 2, '0');


	int zMax = std::max(z2.length(), std::max(z0.length(), z1.length()));

	std::string z0RightPadded = z0 + std::string(zMax - z0.length(), '0');
	std::string z1RightPadded = z1 + std::string(zMax - z1.length(), '0');
	std::string z2RightPadded = z2 + std::string(zMax - z2.length(), '0');





	int zRightPadMax = std::max(z2RightPadded.length(), std::max(z0RightPadded.length(), z1RightPadded.length()));

	std::string z0FullPad = std::string(zRightPadMax - z0RightPadded.length(), '0') + z0RightPadded;
	std::string z1FullPad = std::string(zRightPadMax - z1RightPadded.length(), '0') + z1RightPadded;
	std::string z2FullPad = std::string(zRightPadMax - z2RightPadded.length(), '0') + z2RightPadded;

	std::vector<std::string> midTermSubtrahends = { {z2FullPad},{z0FullPad} };
	std::string middleTerm = longSubtraction(z1RightPadded, midTermSubtrahends);

	std::vector<std::string> toAdd = {
		{z2FullPad},
		{middleTerm},
		{z0FullPad}
	};

	return longAddition(toAdd);

}