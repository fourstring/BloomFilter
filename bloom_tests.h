#pragma once
#include <random>
#include <map>
#include <ctime>
#include "BloomFilter.h"
using namespace std;

auto randint(int a, int b) {
	static auto seed = time(nullptr);
	static auto gen = mt19937_64{ static_cast<unsigned __int64>(seed) };
	static auto rand = uniform_int_distribution<>{ a,b };
	return rand(gen);
}

auto two_filters_test(int n) {
	const int min = 1e8, max = 2e8;
	auto false_positive = 0;
	auto record_set = map<int, int>{};
	auto filter1 = BloomFilter<int>{ 50000,n,10000,2 };
	auto filter2 = BloomFilter<int>{ 50000,n,10002,2 };
	for (int i = 0; i < n; i++)
	{
		// Add elements to two filters, and add it to record_set too to examine false positive.
		auto num = static_cast<int>(randint(min, max));
		filter1.add(num);
		filter2.add(num);
		record_set.insert({ num, 1 });
	}
	for (int i = 0; i < n; i++)
	{
		auto num = static_cast<int>(randint(min, max));
		auto find_in_filters = filter1.find(num) && filter2.find(num);
		auto find_in_records = record_set.find(num) == record_set.end();
		if ( find_in_filters && find_in_records )
			false_positive++;
	}
	return false_positive;
}

auto one_larger_filter_test(int n) {
	const int min = 1e8, max = 2e8;
	auto false_positive = 0;
	auto record_set = map<int, int>{};
	auto filter = BloomFilter<int>{ 100000,n,10000,4 };
	for (int i = 0; i < n; i++)
	{
		auto num = static_cast<int>(randint(min, max));
		filter.add(num);
		record_set.insert({ num,1 });
	}
	for (int i = 0; i < n; i++)
	{
		auto num = static_cast<int>(randint(min, max));
		if (filter.find(num) && record_set.find(num) == record_set.end())
			false_positive++;
	}
	return false_positive;
}