# pragma once

# include "vector.hpp"

namespace ft {

template<class T, class Container = ft::vector<T> >
struct stack {
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;
	typedef typename Container::size_type		size_type;

protected:
	container_type	c;

public:
	/* Member Functions */
	explicit stack(const Container& cont = Container())	: c(cont)		{};
	stack(const stack& other)							: c(other.c)	{};
	stack& operator=(const stack& other) { c = other.c; };
	virtual ~stack() {};


	/* Element access */
	reference		top()		{ return c.back();};
	const_reference	top() const	{ return c.back(); };


	/* Capacity */
	bool		empty()	const { return c.empty(); };
	size_type	size()	const { return c.size(); };


	/* Modifiers */
	void	push(const value_type& value)	{ c.push_back(value); };
	void	pop()							{ c.pop_back(); };
	void	swap(stack& other)				{ ft::swap(c, other.c); };


	template<typename Y, typename C>
	friend bool	operator==(const stack<Y, C> &l, const stack<Y, C> &r);

	template<typename Y, typename C>
	friend bool	operator<(const stack<Y, C> &l, const stack<Y, C> &r);
};


/* Non-member functions */
template<typename T, typename Cont>
bool	operator==(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return l.c == r.c;
}

template<typename T, typename Cont>
bool	operator!=(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return !operator==(l, r);
}

template<typename T, typename Cont>
bool	operator<(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return l.c < r.c;
}

template<typename T, typename Cont>
bool	operator>(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return operator<(r, l);
}

template<typename T, typename Cont>
bool	operator<=(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return !operator<(r, l);
}

template<typename T, typename Cont>
bool	operator>=(const stack<T, Cont> &l, const stack<T, Cont> &r) {
	return !operator<(l, r);
}
/* ---------------------------------------------------------------------------- */

} // namespace ft
