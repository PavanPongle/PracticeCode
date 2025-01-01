#pragma once
#include <iostream>
#include <map>
#include <new>

#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();

public:
	std::map<K, V> m_map;
	V m_valBegin;

	// constructor associates whole range of K with val
	template<typename V_forward>
	interval_map(V_forward&& val)
		: m_valBegin(std::forward<V_forward>(val))
	{
		static_assert(!std::is_default_constructible<K>::value, "A is default constructible");
		static_assert(!std::is_default_constructible<V>::value, "B is not default constructible");
		static_assert(!std::is_nothrow_default_constructible<V>::value, "B is not default constructible");
		static_assert(std::is_nothrow_copy_constructible<V>::value, "B is not default constructible");
		static_assert(std::is_nothrow_move_constructible<V>::value, "B is not default constructible");


		static_assert(std::is_copy_constructible<K>::value && std::is_move_constructible<K>::value,
			"Key type K must support copy and move construction.");
		static_assert(std::is_copy_assignable<K>::value && std::is_move_assignable<K>::value,
			"Key type K must support copy and move assignment.");
		static_assert(std::is_copy_constructible<V>::value && std::is_move_constructible<V>::value,
			"Value type V must support copy and move construction.");
		static_assert(std::is_copy_assignable<V>::value && std::is_move_assignable<V>::value,
			"Value type V must support copy and move assignment.");
		static_assert(std::is_same<decltype(std::declval<K>() < std::declval<K>()), bool>::value,
			"Key type K must implement operator<.");
		static_assert(std::is_same<decltype(std::declval<V>() == std::declval<V>()), bool>::value,
			"Value type V must implement operator==.");
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.

	template<typename V_forward>
	void assign(K const& keyBegin, K const& keyEnd, V_forward&& val)
		requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
	{
		// invalid case
		if (!(keyBegin < keyEnd))
		{
			return;
		}

		//first assignment
		if (m_map.empty())
		{
			if (val == m_valBegin)
				return;

			(void) m_map.emplace(keyBegin, std::forward<V_forward>(val));
			(void) m_map.emplace(keyEnd, std::forward<V_forward>(m_valBegin));

			return;
		}

		using itr_t = std::map<K, V>::iterator;
		const auto& [key_begin_bounds_l, key_begin_bounds_u]  = m_map.equal_range(keyBegin);
		const auto& [key_end_bounds_l, key_end_bounds_u] = m_map.equal_range(keyEnd);

		bool is_key_begin_presend = key_begin_bounds_l != key_begin_bounds_u;
		bool is_key_end_presend = key_end_bounds_l != key_end_bounds_u;

		
		itr_t new_key_begin = key_begin_bounds_l;
		itr_t new_key_end = key_end_bounds_l;

		//If key is present then lower bound is where it found


		//Check if previous node value is same as current val
		bool is_pre_key_begin_val_same = false;
		if (key_begin_bounds_l != m_map.begin())
		{
			// if previous node's value same as current range value then to avoid duplication of val, skip addition of keyBegin
			auto it = key_begin_bounds_l;
			if ((--it)->second == val)
			{
				is_pre_key_begin_val_same = true;
			}
		}

		if (key_end_bounds_u != m_map.end())
		{
			// if next value is end of some range then to avoid duplication of val, skip addition of it
			if (key_end_bounds_u->second == m_valBegin)
			{
				if (is_pre_key_begin_val_same)
					// if it is in same key's range then e
					is_key_end_presend = true;
				else if (is_key_end_presend && key_end_bounds_l->second == val) //means key is being place in existing range
				{
					new_key_end = key_end_bounds_u;
				}
			}
		}

		if (!is_key_begin_presend && key_begin_bounds_l != m_map.begin())
		{
			// if previous node's value same as current range value then to avoid duplication of val, skip addition of keyBegin
			if (is_key_end_presend && is_pre_key_begin_val_same)
				return;
		}

		if (!is_key_end_presend)
		{
			V& last_range_val = m_valBegin;

			auto it = key_end_bounds_u;
			if (it != m_map.begin()) {
				last_range_val = (--it)->second;
			}

			if (!(last_range_val == val))
				// endKey not present in map, insert at end
				new_key_end = m_map.emplace_hint(key_end_bounds_l, keyEnd, last_range_val);
		}

		if (!is_pre_key_begin_val_same)
		{
			if (!is_key_begin_presend)
			{
				new_key_begin = m_map.emplace_hint(key_begin_bounds_l, keyBegin, std::forward<V_forward>(val));
				is_key_begin_presend = true;
			}
			else if ((key_begin_bounds_u == m_map.end() && key_begin_bounds_l != m_map.begin()) ||
				!(key_begin_bounds_l->second == val))
			{
				//its last position modify it here
				new (&key_begin_bounds_l->second) V(std::forward<V_forward>(val));
			}
		}
		else
		{
			// if last key present and incase KeyBeing match with existing keyEnd
			is_key_begin_presend = false;
		}

		//Now travel between
		if (is_key_begin_presend)
			std::advance(new_key_begin, 1);

		m_map.erase(new_key_begin, new_key_end);
	}
	
	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}

	void IntervalMapTest() {

	}

	// a print function for debugging
	void show() {
		std::cout << "\n__________________________\n .... " << m_valBegin << ".....";
		for (auto entry : m_map) {
			std::cout << "(" << entry.first << "," << entry.second << "), ";
		}
		std::cout << "...." << m_valBegin << ".... \n__________________________";
	}

};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, 
// for example using a map of int intervals to char.