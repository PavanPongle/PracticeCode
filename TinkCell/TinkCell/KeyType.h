#pragma once
#include <iostream>

template <typename T>
class Key
{
public:
	T t_;

	Key(const T& k) : t_(k) {  };

	Key(const Key& k) : t_(k.t_) {};
	Key(Key&& k) : t_(std::move(k.t_)) {};

	Key& operator = (const Key& k) = default; // l value ref overload, these can be expand to const variant
	Key& operator = (Key&& k) = default; // l value ref overload, these can be expand to const variant

	bool operator < (const Key& k) const { return std::cmp_less(t_, k.t_); }; // l value ref overload, these can be expand to const variant
	//bool operator < (const Key&) && = default; // r value ref overload, these can be	expand to const variant
	//bool operator < (const Key&) const& = default; // l value ref overload, these can	be expand to const variant
	//bool operator < (const Key&) const&& = default; // l value ref overload, these can	be expand to const variant

	Key() = delete;
	~Key() {}

	friend std::ostream& operator << (std::ostream& os, const Key& k)
	{
		os << k.t_;
		return os;
	}

	bool operator != (const Key&) = delete;
	bool operator == (const Key&) = delete;
	bool operator >= (const Key&) = delete;
	bool operator <= (const Key&) = delete;
	bool operator > (const Key&) = delete;

	
	//Key& operator=(Key&&) & = delete;
	//Key& operator=(Key&) & = delete;
	//Key& operator=(const Key&&) & = delete;

	////Key& operator=(Key&&) && = delete; // Key{} = Key{}; possible with this operator
	//Key& operator=(Key&) && = delete;
	//Key& operator=(const Key&&) && = delete;

	////Key& operator=(Key&&) const& = delete;
	//Key& operator=(Key&) const& = delete;
	//Key& operator=(const Key&&) const& = delete;

	////Key& operator=(Key&&) const&& = delete;
	//Key& operator=(Key&) const&& = delete;
	//Key& operator=(const Key&&) const&& = delete;
	
};

namespace std
{
	template<typename T>
	class numeric_limits<Key<T>>
	{
	public:
		static Key<T> lowest()
		{
			return Key(numeric_limits< T >::lowest());
		}

		static Key<T> max()
		{
			return Key(numeric_limits< decltype(declval<Key<T>>().t_) >::max());
		}
		
	};

};