//
// Created by Grubbly Ernesto on 8/9/22.
//

# pragma once

namespace ft {

	template<typename T>
	struct	less
	{
		bool	operator()(const T& l, const T& r) const {
				return l < r;
		};
	};

	template<typename T>
	struct	more
	{
		bool	operator()(const T& l, const T& r) const {
			return l > r;
		};
	};

	template<typename T>
	T	max(const T l, const T r)
	{
		return l >= r ? l : r;
	}

	template<typename T1, typename T2>
	void swap(T1 &t1, T2 &t2) {
		T1 tmp(t1);

		t1 = t2;
		t2 = tmp;
	}

/*	integral_constant	*/
	template<typename T, T val>
	struct integral_constant {
		static const T value = val;
		typedef T val_type;
		typedef integral_constant<T, val> type;

		operator val_type() const { return value; };
	};

	typedef integral_constant<bool, false> false_type;
	typedef integral_constant<bool, true> true_type;


/*	ft::pair	*/
	template<typename T1, typename T2>
	struct pair {
		T1 first;
		T2 second;

		pair() : first(), second() {};

		pair(T1 const &t1, T2 const &t2) : first(t1), second(t2) {};

		template<typename Other1, typename Other2>
		pair(const pair<Other1, Other2> &other) : first(other.first), second(other.second) {};

		pair &operator=(const pair &other) {
			first = other.first;
			second = other.second;

			return *this;
		}

		void swap(pair &p) {
			ft::swap(*this, p);
		};
	};


/*	ft::make_pair	*/
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t1, T2 t2) {
		return ft::pair<T1, T2>(t1, t2);
	}


/*	ft::pair operators	*/
	template<class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return p1.first == p2.first && p1.second == p2.second;
	}

	template<class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return !(p1 == p2);
	}

	template<class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second);
	}

	template<class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return p2 < p1;
	}

	template<class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return !(p1 > p2);
	}

	template<class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &p1, const ft::pair<T1, T2> &p2) {
		return !(p1 < p2);
	}


/*	equal	*/
	template<class InputIter1, class InputIter2>
	bool	equal(InputIter1 start1, InputIter1 end1, InputIter2 start2) {
		for (; start1 != end1; ++start1, ++start2)
			if (*start1 != *start2)
				return false;
		return true;
	}

	template<class InputIter1, class InputIter2, class BinaryPredicate>
	bool	equal(InputIter1 start1, InputIter1 end1, InputIter2 start2, BinaryPredicate pred) {
		for (; start1 != end1; ++start1, ++start2)
			if (!pred(*start1, *start2))
				return false;
		return true;
	}


/*	lexicographical_compare	*/
/*
 *	Two ranges are compared element by element.
 *	The first mismatching element defines which range is lexicographically less or greater than the other.
 *	If one range is a prefix of another, the shorter range is lexicographically less than the other.
 *	If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
 *	An empty range is lexicographically less than any non-empty range.
 *	Two empty ranges are lexicographically equal.
 */
	template<class InputIter1, class InputIter2>
	bool	lexicographical_compare(InputIter1 start1, InputIter1 end1, InputIter2 start2, InputIter2 end2) {
		for (; start1 != end1 && start2 != end2; ++start1, ++start2)
		{
			if (*start1 < *start2)
				return true;
			if (*start2 < *start1)
				return false;
		}
		return start1 == end1 && start2 != end2;
	}

	template<class InputIter1, class InputIter2, class Compare>
	bool	lexicographical_compare(InputIter1 start1, InputIter1 end1, InputIter2 start2, InputIter2 end2, Compare comp) {
		for (; start1 != end1 && start2 != end2; ++start1, ++start2)
		{
			if (comp(*start1, *start2))
				return true;
			if (comp(*start2, *start1))
				return false;
		}
		return start1 == end1 && start2 != end2;
	}


/*	enable_if	*/
	template<class T, class O> struct is_same	: false_type	{ };
	template<class T> struct is_same<T, T>		: true_type		{ };

	template<bool, class T = void> struct enable_if	{ };
	template<class T> struct enable_if<true, T>		{ typedef T type; };

	template<typename T, typename O>
	bool	is_same_types(T, O) { return false; }
	template<typename T>
	bool	is_same_types(T, T) { return true; }



/*	is_integral	*/
	template<class>		struct is_integral			: false_type { };
	template<class T>	struct is_integral<const T>	: is_integral<T> { };

	template<> struct is_integral<bool>				: true_type	{ };
	template<> struct is_integral<char>				: true_type	{ };
	template<> struct is_integral<wchar_t>			: true_type	{ };
	template<> struct is_integral<const bool>		: true_type	{ };
	template<> struct is_integral<const char>		: true_type	{ };
	template<> struct is_integral<const wchar_t>	: true_type	{ };

	template<> struct is_integral<unsigned char>			: true_type	{ };
	template<> struct is_integral<unsigned short>			: true_type	{ };
	template<> struct is_integral<unsigned int>				: true_type	{ };
	template<> struct is_integral<unsigned long>			: true_type	{ };
	template<> struct is_integral<unsigned long long>		: true_type	{ };
	template<> struct is_integral<const unsigned char>		: true_type	{ };
	template<> struct is_integral<const unsigned short>		: true_type	{ };
	template<> struct is_integral<const unsigned int>		: true_type	{ };
	template<> struct is_integral<const unsigned long>		: true_type	{ };
	template<> struct is_integral<const unsigned long long>	: true_type	{ };

	template<> struct is_integral<signed char>			: true_type	{ };
	template<> struct is_integral<short>				: true_type	{ };
	template<> struct is_integral<int>					: true_type	{ };
	template<> struct is_integral<long>					: true_type	{ };
	template<> struct is_integral<long long>			: true_type	{ };
	template<> struct is_integral<const signed char>	: true_type	{ };
	template<> struct is_integral<const short>			: true_type	{ };
	template<> struct is_integral<const int>			: true_type	{ };
	template<> struct is_integral<const long>			: true_type	{ };
	template<> struct is_integral<const long long>		: true_type	{ };

//	template<> struct is_integral<char16_t>			: true_type	{ };
//	template<> struct is_integral<char32_t>			: true_type	{ };
//	template<> struct is_integral<const char16_t>	: true_type	{ };
//	template<> struct is_integral<const char32_t>	: true_type	{ };

}
