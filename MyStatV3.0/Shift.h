#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <conio.h>
#include <regex>
#include <chrono>
#include <thread>
namespace shift
{ 
	std::string tolower(const std::string& str)
	{
		std::string res;
		for (const auto& i : str)
		{
			res += i >= 65 and i <= 90 ? i + 32 : i;
		}
		return res;
	}
	std::string toupper(const std::string& str)
	{
		std::string res;
		for (const auto& i : str)
		{
			res += i >= 97 and i <= 122 ? i - 32 : i;
		}
		return res;
	}
	long long findnums(const std::string& mes)
	{
		long long num=0;
		long long count = 0;
		for (long long i{ (long long)mes.size() - 1 }; i >= 0; i--)
		{
			if (mes[i] >= 48 and mes[i] <= 57)
			{
				num += ((size_t)mes[i] - 48) * (size_t)pow(10, count);
				count++;
			}
		}
		return count == 0 ? -1 : num;
	}
	int chtonum(const char& elem)
	{
		return elem - 48;
	}
	long randomize(const long &start, const long& end)
	{
		return 1+start + rand() % end - start;
	}
	template<typename t>
	std::vector<t> subvector(const std::vector<t>& arr, size_t from, size_t to)
	{
		std::vector<t> res;
		for (size_t i{ from }; i <= to;i++)
		{
			res.push_back(arr[i]);	
		}
		return res;
	}
	template<typename t>
	std::string veccompare(const std::vector<t>& arr1, const std::vector<t>& arr2)
	{
	if(arr1.size()>arr2.size())
	{
		return "bigger";
	}
	else if (arr1.size() < arr2.size())
	{
		return "lower";
	}
	else
	{
		long long sum = 0;
		for (size_t i{}; i < arr1.size(); i++)
		{
			sum += arr1[i] > arr2[i] ? 1 : -1;
		}
		return sum>0 ? "bigger" : sum == 0 ? "same" : "lower";
	}
	}
	int getdigitcount(long long num)
	{
		int sum = 0;
		for (; num; num /= 10)sum++;
		return sum;
	}
}
template<typename t>
std::ostream& operator <<(std::ostream& out, const std::vector<t>& arr)
{
	for (const auto& i : arr)
	{
		out << i << ' ';
	}
	out << '\n';
	return out;
}
template<typename t>
bool operator >(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "bigger";
}
template<typename t>
bool operator ==(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "same";
}
template<typename t>
bool operator <(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "lower";
}