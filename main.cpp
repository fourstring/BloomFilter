#include "BloomFilter.h"
#include "bloom_tests.h"
#include <iostream>
#include <random>
#include <map>
#include <ctime>

using namespace std;

int main() {
	for (int total = 1000; total <= 20000; total += 1000) {
		auto double_total = static_cast<double>(total);
		cout << "Current n is:" << total << endl;
		double two = two_filters_test(total) / double_total * 100;
		double one = one_larger_filter_test(total) / double_total * 100;
		cout << "Two filters false positive rate:" << two << endl;
		cout << "One larger filter false positive rate:" << one << endl;
		cout << endl;
	}
	cin.get();
	return 0;
}