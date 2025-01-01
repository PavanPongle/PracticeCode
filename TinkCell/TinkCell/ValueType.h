#pragma once

template < typename T>
class Value
{
public:
	T t_;

	Value(const T& k) : t_(k) {};

	Value(const Value& k) : t_(k.t_) {};
	Value(Value&& k) : t_(std::move(k.t_)) {};

	Value& operator = (const Value&) = default; // l value ref overload, these can be expand to const variant

	bool operator == (const Value& k) const { return std::cmp_equal((int)t_, (int)k.t_); }; // l value ref overload, these can be expand to const variant

	friend std::ostream& operator << (std::ostream& os, const Value& v)
	{
		os << v.t_;
		return os;
	}

	Value() = delete;

	bool operator != (const Value&) = delete;
	bool operator < (const Value&) = delete;
	bool operator >= (const Value&) = delete;
	bool operator <= (const Value&) = delete;
	bool operator > (const Value&) = delete;

	~Value() {}

	//Value& operator=(Value&&) & = delete;
	//Value& operator=(Value&) & = delete;
	//Value& operator=(const Value&&) & = delete;


	//Value& operator=(Value&&) && = delete; // Value{} = Value{}; possible with this operator
	Value& operator=(Value&) && = delete;
	//Value& operator=(const Value&&) && = delete;

	//Value& operator=(Value&&) const& = delete;
	//Value& operator=(Value&) const& = delete;
	//Value& operator=(const Value&&) const& = delete;

	//Value& operator=(Value&&) const&& = delete;
	Value& operator=(Value&) const&& = delete;
	//Value& operator=(const Value&&) const&& = delete;
	
};