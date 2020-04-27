#include <iostream>
#include <sstream>
#include <string>
#include<cmath>
#include "utility.h"

bool IsPrime(int x)
{
	bool prime = true;
	for (int i = 2; i <= x / i; i = i + 1)
	{
		int factor = x / i;
		if (factor * i == x)
		{
			prime = false;
			break;
		}
	}
	return prime;
}


bool check_each_digit_isnt(int x, int reject)
{
	bool result = true;
	int num_digits = floor(log10(abs(x ? x : 1)) + 1);
	for (; num_digits; num_digits--, x /= 10)
	{
		if (x % 10 == reject)
		{
			result = false;
		}
	}
	return result;
}


bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

