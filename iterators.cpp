#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>

template<class Iter>
class reverse_iterator
{

private:
	Iter current;

public:
	typedef Iter iterator_type;
	typedef typename std::iterator_traits<Iter>::difference_type 
		difference_type;
	// default cstor
	reverse_iterator() : current() {}
	// cstor with Iter arg
	explicit reverse_iterator(Iter it) : current(it) {}
	// copy cstor
	template<typename Iter>
	reverse_iterator(const reverse_iterator<Iter>& otherIter) 
		: current(otherIter.current) {}
	// base
	iterator_type base() const { return current; }
	// assignment op
	reverse_iterator& operator*() const
	{
		Iter tmp = current;
		return *--tmp;
	}
	reverse_iterator* operator->() const
	{
		return &(operator*());
	}
	// []
	reverse_iterator& operator[](difference_type n) const
		{ return *(*this + n); }
	// ++
	reverse_iterator& operator++()
	{
		--current;
		return *this;
	}
	// ++(int)
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--current;
		return tmp;
	}
	// --
	reverse_iterator& operator--()
	{
		++current;
		return *this;
	}
	// --(int)
	reverse_iterator operator--(int) {
		reverse_iterator __tmp = *this;
		++current;
		return __tmp;
	}
	// +=
	reverse_iterator& operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}
	// -=
	reverse_iterator& operator-=(difference_type n)
	{
		current += n;
		return *this;
	}
	/*
	reverse_iterator& operator=(const reverse_iterator<Iter>& other)
		: current(other.base()) { return *this; }
	*/
	// pointer arithmetic operators
	// *
	// -> 
};
// global operators
// -
template<typename Iter>
inline typename reverse_iterator<Iter>::difference_type 
operator-(const reverse_iterator<Iter>& x, 
					const reverse_iterator<Iter>& y)
		{ return y.base() - x.base(); }
// +
template<typename Iter> inline reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
					const reverse_iterator<Iter>& x)
		{ return reverse_iterator<Iter>(x.base() - n); }
// ==
template<typename Iter>
inline bool operator==(const reverse_iterator<Iter>& x,
					const reverse_iterator<Iter>& y)
		{ return x.base() == y.base(); }
// !=
template<typename Iter>
inline bool operator!=(const reverse_iterator<Iter>& x,
					const reverse_iterator<Iter>& y)
		{ return !(x == y); }
// <
template<typename Iter>
inline bool operator<(const reverse_iterator<Iter>& x,
					const reverse_iterator<Iter>& y)
		{ return y.base() < x.base(); }
// <=
template<typename Iter>
inline bool operator<=(const reverse_iterator<Iter>& x,
		         const reverse_iterator<Iter>& y)
		{ return !(y < x); }
// >
template<typename Iter>
inline bool operator>(const reverse_iterator<Iter>& x,
					const reverse_iterator<Iter>& y)
		{ return y < x; }
// >=
template<typename Iter>
inline bool operator>=(const reverse_iterator<Iter>& x,
	            const reverse_iterator<Iter>& y)
		{ return !(x < y); }
/******************************************************************************/
template<class T, class Ch=char>
class ostream_iterator
{
	std::basic_ostream<Ch>* out_stream;
	const Ch* delim;
public:
	typedef Ch char_type;
	typedef std::basic_ostream<Ch> ostream_type;
	// default cstor
	ostream_iterator(ostream_type& stream) : out_stream(&stream), delim(0) {}
	// cstor ostream arg and delim arg
	ostream_iterator(ostream_type& stream, const Ch* delimiter)
		: out_stream(&stream), delim(delimiter) {}
	// copy cstor
	ostream_iterator(const ostream_iterator<T, Ch>& other)
		: out_stream(other.out_stream), delim(other.delim) {}
	// dstor
	~ostream_iterator() {}
	// assignment operator takes arg type T and is then outputted
	ostream_iterator<T, Ch>& operator=(const T& value)
	{
		*out_stream << value;
		if (delim != 0)
			*out_stream << delim;
		return *this;
	}
	// ptr arithmetic operators
	ostream_iterator& operator*() { return *this; }
	ostream_iterator& operator++() { return *this; }
	ostream_iterator& operator++(int) { return *this; }
};
/******************************************************************************/
template<class T>
class istream_iterator
{
	std::basic_istream<T>* in_stream;
	T value;
public:
	typedef std::basic_istream<T> istream_type;
	// default cstor
	istream_iterator() : in_stream(0) {}
	// cstor with istream arg
	istream_iterator(istream_type& stream) : in_stream(&stream) { ++*this; }
	// copy cstor
	istream_iterator(const istream_iterator<T>& other) 
		: in_stream(other.in_stream), value(other.value) {}
	~istream_iterator() {}
	// pointer arithmetic operators
	const T& operator*() const { return value; }
	const T* operator->() const { return &value; }
	istream_iterator<T>& operator++()
	{
		if (in_stream && !(*in_stream >> value))
			in_stream = 0;
		return *this;
	}
	istream_iterator<T>& operator++(int)
	{
		istream_iterator<T> tmp = *this;
		++*this;
		return tmp;
	}
};
template<class T>
bool operator==(const istream_iterator<T>& lhs, 
			const istream_iterator<T>& rhs) 
{
	return (lhs == rhs);
}
template<class T>
bool operator!=(const istream_iterator<T>& lhs,
			const istream_iterator<T>& rhs) 
{
	return (lhs != rhs);
}
/******************************************************************************/
/*
	insert_iterator
*/
template<class Cont>
class insert_iterator
{
protected:
	Cont* container;
	typename Cont::iterator iter;

public:
	typedef Cont container_type;
	explicit insert_iterator(Cont& c, typename Cont::iterator it) : 
		container(&c), iter(it) {}
	insert_iterator<Cont>& operator=(const typename Cont::value_type& value)
	{
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}
	insert_iterator<Cont>& operator=(typename Cont::value_type&& value)
	{
		iter = container->insert(iter, std::move(value));
		++iter;
		return *this;
	}
	insert_iterator& operator*() { return *this; }
	insert_iterator& operator++() { return *this; }
	insert_iterator& operator++(int) { return *this; }
};
template<class Cont>
insert_iterator<Cont> insertInserter(Cont& c, typename Cont::iterator it)
{
	return insert_iterator<Cont>(c, it);
}
/******************************************************************************/
/*
	front_insert_iterator
*/
template<class Cont>
class front_insert_iterator
{
protected:
	Cont* container;
public:
	explicit front_insert_iterator(Cont& c) : container(&c) {}
	front_insert_iterator<Cont>& operator=(
									const typename Cont::value_type& value)
	{
		container->push_front(value);
		return *this;
	}
	front_insert_iterator<Cont>& operator=(typename Cont::value_type&& value)
	{
		container->push_front(std::move(value));
		return *this;
	}
	front_insert_iterator& operator*() { return *this; }
	front_insert_iterator& operator++() { return *this; }
	front_insert_iterator& operator++(int) { return *this; }
};
template<class Cont>
front_insert_iterator<Cont> frontInserter(Cont& c)
{
	return front_insert_iterator<Cont>(c);
}
/******************************************************************************/
/*
	back_insert_iterator 
*/
template<class Cont>
class back_insert_iterator
{
protected:
	Cont* container;
public:
	   explicit back_insert_iterator(Cont& c) : container(&c) {}
	   back_insert_iterator& operator=(const typename Cont::value_type& value)
	   {
		   container->push_back(value);
		   return *this;
	   }
	   back_insert_iterator& operator=(typename Cont::value_type&& value)
	   {
		   container->push_back(std::move(value));
		   return *this;
	   }
	   back_insert_iterator& operator*() { return *this; }
	   back_insert_iterator& operator++() { return *this; }
	   back_insert_iterator& operator++(int) { return *this; }
};
template<class Cont>
back_insert_iterator<Cont> backInserter(Cont& c)
{
		   return back_insert_iterator<Cont>(c);
}
/******************************************************************************/
