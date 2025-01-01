// TinkCell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "KeyType.h"
#include "ValueType.h"
#include "IntervalMap.h"

using namespace std;

using K = Key<int>;
using V = Value<char>;

int main()
{

	//interval_map<K, V> imap{ V('E') };
	//imap.assign(K(10), K(20), V('I'));
	//imap.assign(K(std::numeric_limits<K>::lowest()), K(10), V('I'));

	//map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('I')}, { K(20), V('E')}, };

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(std::numeric_limits<K>::lowest()), K(10), V('L'));

	map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('L')}, { K(10), V('I')}, { K(20), V('E')}, };

	imap.show();
	return 0;    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
