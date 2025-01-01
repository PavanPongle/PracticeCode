#include "pch.h"

#include <iostream>
#include <map>
#include "KeyType.h"
#include "ValueType.h"
#include "IntervalMap.h"

using namespace std;

using K = Key<int>;
using V = Value<char>;

TEST(TestCaseName, TestName) {

	interval_map<K,V> imap{ V('A') };


	//cout << "first insert" << '\n';
	//imap.assign(K(8), K(10), V('b'));

	//// invalid insert
	//imap.assign(K(18), K(12), V('c'));
	//imap.assign(K(std::numeric_limits<K>::max()), K(std::numeric_limits<K>::lowest()), V('d'));



	////whole assignment
	//imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('D'));
	//imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));
	//imap.assign(K(7), K(9), V('c'));

	////Insert beyond last
	//imap.assign(K(10), K(12), V('d'));

	////Insert beging last
	//imap.assign(K(0), K(3), V('f'));

	/*

	cout << "start of overlapping cases" << '\n';
	// clear the map
	imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));
	imap.assign(K(7), K(9), V('c'));

	//either end insertion

	//End overlap
	imap.assign(K(9), K(11), V('d'));

	//Begin overlap
	imap.assign(K(5), K(7), V('f'));

	cout << "extending range" << '\n';
	// clear the map
	imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));
	imap.assign(K(7), K(9), V('c'));

	cout << "Both direction expansion" << '\n';
	imap.assign(K(5), K(11), V('d'));

	cout << "insert between a range" << '\n';
	imap.assign(K(7), K(9), V('h'));

	cout << "just change value of existing range" << '\n';
	imap.assign(K(7), K(9), V('I'));

	cout << "expansion of in between range to end" << '\n';
	imap.assign(K(7), K(10), V('I'));

	cout << "expansion of in between range to begin" << '\n';
	imap.assign(K(6), K(10), V('I'));

	cout << "overlap expansion of in between range to begin" << '\n';
	imap.assign(K(5), K(10), V('I'));


	cout << "overlap expansion of in between range to extream end" << '\n';
	imap.assign(K(6), K(std::numeric_limits<K>::max()), V('L'));


	cout << "overlap expansion of in between range to extream begin" << '\n';
	imap.assign(K(std::numeric_limits<K>::lowest()), K(7), V('K'));

	// clear the map
	imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));

	*/

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


void CheckMaps(map<K,V>& res,
			   map<K,V>& imap)
{
	EXPECT_EQ(res.size(), imap.size());

	if (res.size() != imap.size())
		return;

	auto imapItr = imap.begin();
	for (auto& [k, v] : res)
	{
		EXPECT_EQ(k.t_, imapItr->first.t_);
		EXPECT_EQ(v, imapItr->second);
		++imapItr;
	}
}

/************************************************************************************************************/
TEST(EmptyInsertion, ValidInsertion) {

	interval_map<K,V> imap{ V('A') };
	imap.assign(K(8), K(10), V('b'));

	map<K,V> res { { K(8), V('b')}, { K(10), V('A')} };

	CheckMaps(res, imap.m_map);
}

TEST(EmptyInsertion, InValidInsertion) {

	interval_map<K,V> imap{ V('A') };
	imap.assign(K(18), K(10), V('b'));

	map<K,V> res{ };

	CheckMaps(res, imap.m_map);
}

//TEST(EmptyInsertion, OverwriteEmptyMemberVal) {
//
//	interval_map<K, V> imap{ V('A') };
//	imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));
//
//	map<K, V> res{ };
//
//	CheckMaps(res, imap.m_map);OverwriteMemberVal
//	EXPECT_EQ(V('E'), imap.m_valBegin);
//}

//TEST(EmptyInsertion, OverwriteMemberVal) {
//
//	interval_map<K,V> imap{ V('A') };
//	imap.assign(K(7), K(9), V('c'));
//	imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));
//
//	map<K,V> res{ };
//
//	CheckMaps(res, imap.m_map);
//	EXPECT_EQ(V('E'), imap.m_valBegin);
//}
/************************************************************************************************************/
TEST(NonEmptyInsertion, InsertEnd) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(10), K(12), V('d'));

	map<K,V> res{ { K(7), V('c')}, { K(9), V('E')}, { K(10), V('d')}, { K(12), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(NonEmptyInsertion, InsertBegin) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(0), K(3), V('d'));

	map<K,V> res{ { K(0), V('d')}, { K(3), V('E')}, { K(7), V('c')}, { K(9), V('E')} };

	CheckMaps(res, imap.m_map);
}

/************************************************************************************************************/

TEST(OverLap, End) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(9), K(11), V('d'));

	map<K,V> res{ { K(7), V('c')}, { K(9), V('d')}, { K(11), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(OverLap, Begin) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(0), K(7), V('d'));

	map<K,V> res{ { K(0), V('d')}, {K(7), V('c')}, { K(9), V('E')} };

	CheckMaps(res, imap.m_map);
}


/************************************************************************************************************/

TEST(ExtendRange, BothDirectionExpansion) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(9), K(12), V('d'));
	imap.assign(K(5), K(15), V('e'));

	map<K,V> res{ { K(5), V('e')}, {K(15), V('E')}};

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, RightDirectionExpansion) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(9), K(12), V('d'));
	imap.assign(K(7), K(15), V('e'));

	map<K,V> res{ { K(7), V('e')}, {K(15), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, LeftDirectionExpansion) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(9), K(12), V('d'));
	imap.assign(K(5), K(12), V('e'));

	map<K,V> res{ { K(5), V('e')}, {K(12), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(MvalueChange, ToI) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('c'));
	imap.assign(K(7), K(9), V('I'));

	map<K,V> res{ { K(7), V('I')}, {K(9), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, ToEnd) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('I'));
	imap.assign(K(7), K(12), V('I'));

	map<K,V> res{ { K(7), V('I')}, {K(12), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, ToEndChangeVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('I'));
	imap.assign(K(7), K(12), V('F'));

	map<K,V> res{ { K(7), V('F')}, {K(12), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBegin) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('I'));
	imap.assign(K(5), K(9), V('I'));

	map<K,V> res{ { K(5), V('I')}, {K(9), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBeginChangeVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(7), K(9), V('I'));
	imap.assign(K(5), K(9), V('F'));

	map<K,V> res{ { K(5), V('F')}, {K(9), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenDiffVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(11), K(19), V('F'));

	map<K,V> res{ { K(10), V('I')}, { K(11), V('F')}, {K(19), V('I')}, {K(20), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenSameVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(11), K(19), V('I'));

	map<K, V> res{ { K(10), V('I')}, {K(20), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenDiffValLargeGap) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(13), K(17), V('F'));

	map<K,V> res{ { K(10), V('I')}, { K(13), V('F')}, {K(17), V('I')}, {K(20), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenSameValLargeGap) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(13), K(17), V('I'));

	map<K,V> res{ { K(10), V('I')}, {K(20), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenBeginToEndSameVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(15), K(std::numeric_limits<K>::max()), V('I'));

	map<K,V> res{ { K(10), V('I')}, {K(std::numeric_limits<K>::max()), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenBeginToEndDiffVal) {

	interval_map<K,V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(15), K(std::numeric_limits<K>::max()), V('L'));

	map<K, V> res{ { K(10), V('I')}, { K(15), V('L')}, {K(std::numeric_limits<K>::max()), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InEndBeginToEndSameVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(20), K(std::numeric_limits<K>::max()), V('I'));

	map<K, V> res{ { K(10), V('I')}, {K(std::numeric_limits<K>::max()), V('E')} };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InEndBeginToEndDiffVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(20), K(std::numeric_limits<K>::max()), V('L'));

	map<K, V> res{ { K(10), V('I')}, { K(20), V('L')}, {K(std::numeric_limits<K>::max()), V('E')} };

	CheckMaps(res, imap.m_map);
}

/************************************************************/


TEST(ExtendRange, InBetweenToBeginSameVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(std::numeric_limits<K>::lowest()), K(15), V('I'));

	map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('I')}, { K(20), V('E')}, };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBetweenToBeginDiffVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(std::numeric_limits<K>::lowest()), K(15), V('L'));

	map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('L')}, { K(15), V('I')}, { K(20), V('E')}, };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBeginToBeginSameVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(std::numeric_limits<K>::lowest()), K(10), V('I'));

	map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('I')}, { K(20), V('E')}, };

	CheckMaps(res, imap.m_map);
}

TEST(ExtendRange, InBeginToBeginDiffVal) {

	interval_map<K, V> imap{ V('E') };
	imap.assign(K(10), K(20), V('I'));
	imap.assign(K(std::numeric_limits<K>::lowest()), K(10), V('L'));

	map<K, V> res{ {K(std::numeric_limits<K>::lowest()), V('L')}, { K(10), V('I')}, { K(20), V('E')}, };

	CheckMaps(res, imap.m_map);
}

/*
cout << "extending range" << '\n';

cout << "just change value of existing range" << '\n';
imap.assign(K(7), K(9), V('I'));

cout << "expansion of in between range to end" << '\n';
imap.assign(K(7), K(10), V('I'));

cout << "expansion of in between range to begin" << '\n';
imap.assign(K(6), K(10), V('I'));

cout << "overlap expansion of in between range to begin" << '\n';
imap.assign(K(5), K(10), V('I'));

cout << "overlap expansion of in between range to extream end" << '\n';
imap.assign(K(6), K(std::numeric_limits<K>::max()), V('L'));


cout << "overlap expansion of in between range to extream begin" << '\n';
imap.assign(K(std::numeric_limits<K>::lowest()), K(7), V('K'));

// clear the map
imap.assign(K(std::numeric_limits<K>::lowest()), K(std::numeric_limits<K>::max()), V('E'));

*/