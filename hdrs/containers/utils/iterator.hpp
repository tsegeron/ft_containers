# pragma once

# include <string>

/*	iterator_traits	*/
namespace ft {

	/*	iterator tags	*/
	struct input_iterator_tag	{};
	struct output_iterator_tag	{};
	struct forward_iterator_tag			: input_iterator_tag			{};
	struct bidirectional_iterator_tag	: forward_iterator_tag			{};
	struct random_access_iterator_tag	: bidirectional_iterator_tag	{};

	/*	iterator interfaces for inheritance	*/
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;	/* Type of the result of subtracting two iterators */
		typedef typename Iterator::value_type			value_type;			/* Type of element where iterator points */
		typedef typename Iterator::pointer				pointer;			/* Type of pointer to the element where iterator points */
		typedef typename Iterator::reference			reference;			/* Type of reference where iterator points */
		typedef typename Iterator::iterator_category	iterator_category;	/* The iterator category, check for tags */
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef const Pointer	pointer;
		typedef const Reference	reference;
	};


	template<bool valid, typename T>
	struct valid_iterator_tag { typedef T type; static const bool value = valid; };

	template<typename T>
	struct is_iterator_tag_valid : valid_iterator_tag<false, T> {};

	template<>
	struct is_iterator_tag_valid<ft::input_iterator_tag> : valid_iterator_tag<true, input_iterator_tag> {};

	template<>
	struct is_iterator_tag_valid<ft::output_iterator_tag> : valid_iterator_tag<true, output_iterator_tag> {};

	template<>
	struct is_iterator_tag_valid<ft::forward_iterator_tag> : valid_iterator_tag<true, forward_iterator_tag> {};

	template<>
	struct is_iterator_tag_valid<ft::bidirectional_iterator_tag> : valid_iterator_tag<true, bidirectional_iterator_tag> {};

	template<>
	struct is_iterator_tag_valid<ft::random_access_iterator_tag> : valid_iterator_tag<true, random_access_iterator_tag> {};

	struct InvalidIterator : std::exception {
		InvalidIterator() : _err_msg("Invalid iterator: use iterators declared in namespace ft::") {};
		virtual ~InvalidIterator() throw() {};
		virtual const char *what() const throw() { return _err_msg.c_str(); };
	private:
		std::string	_err_msg;
	};


	template<class T>
	struct normal_iterator : iterator<random_access_iterator_tag, T> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef value_type*					pointer;
		typedef value_type&					reference;
		typedef normal_iterator<T>			self;


		normal_iterator()					: _cur_ptr(pointer()) {};
		normal_iterator(pointer ptr)		: _cur_ptr(ptr) {};
		normal_iterator(const T& r)			: _cur_ptr(r) {};
		normal_iterator& operator=(const normal_iterator& o) { _cur_ptr = o._cur_ptr; return *this; };

		operator normal_iterator<const T> () const {
			return (normal_iterator<const T>(this->_cur_ptr));
		};

		reference		operator *	()					const { return *_cur_ptr; }
		pointer			operator ->	()					const { return _cur_ptr; }
		reference		operator []	(size_t n)			const { return *(_cur_ptr + n); }
		difference_type	operator -	(const self& other)	const { return _cur_ptr - other._cur_ptr; }

		self	&operator	++	()		{ ++_cur_ptr; return *this; }
		self	operator	++	(int)	{ self tmp = *this; ++_cur_ptr; return tmp; }
		self 	&operator	--	()		{ --_cur_ptr; return *this; }
		self	operator	--	(int)	{ self tmp = *this; --_cur_ptr; return tmp; }

		self	operator	+	(difference_type n) const	{ return _cur_ptr + n; }
		self	&operator	+=	(difference_type n)			{ _cur_ptr += n; return *this; }
		self	operator	-	(difference_type n) const	{ return _cur_ptr - n; }
		self	&operator	-=	(difference_type n)			{ _cur_ptr -= n; return *this; }

		bool	operator	==	(const self& other) const { return  _cur_ptr == other._cur_ptr; };
		bool	operator	!=	(const self& other) const { return !(*this == other); }
		bool	operator	<	(const self& other) const { return  _cur_ptr < other._cur_ptr; };
		bool	operator	<=	(const self& other) const { return !(other < *this); }
		bool	operator	>	(const self& other) const { return other < *this; }
		bool	operator	>=	(const self& other) const { return !(*this < other); }
		template<class Iter1, class Iter2>
		friend bool	operator == (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y);
		template<class Iter1, class Iter2>
		friend bool	operator < (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y);

		pointer	base() { return _cur_ptr; }

	protected:
		pointer _cur_ptr;
	};

	template<class Iter1, class Iter2>
	bool	operator == (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return y._cur_ptr == x._cur_ptr;
	}

	template<class Iter1, class Iter2>
	bool	operator != (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return !(y == x);
	}

	template<class Iter1, class Iter2>
	bool	operator < (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return x._cur_ptr < y._cur_ptr;
	}

	template<class Iter1, class Iter2>
	bool	operator <= (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return !(y < x);
	}

	template<class Iter1, class Iter2>
	bool	operator > (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return y < x;
	}

	template<class Iter1, class Iter2>
	bool	operator >= (const normal_iterator<Iter1>& x, const normal_iterator<Iter2>& y) {
		return !(x < y);
	}

	template<class Iter>
	normal_iterator<Iter> operator + (typename normal_iterator<Iter>::difference_type n, normal_iterator<Iter>& it)
	{ return it.base() + n; }



	template<class Iterator>
	struct reverse_iterator
			: iterator< typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference >
	{
	protected:
		Iterator _cur_ptr;

	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		reverse_iterator()				: _cur_ptr() {};
		reverse_iterator(Iterator x)	: _cur_ptr(x) {};

		template<class U>
		reverse_iterator(const reverse_iterator<U>& u) : _cur_ptr(u.base()) {};

		operator reverse_iterator<const Iterator> () const {
			return (reverse_iterator<const Iterator>(this->_cur_ptr));
		};

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& u) { _cur_ptr = u._cur_ptr; return *this; };

		Iterator base() const { return _cur_ptr; };

		reference			operator *	()							{ Iterator tmp = _cur_ptr; return *(--tmp); };
		pointer				operator ->	()							{ return &(operator*()); };
		reverse_iterator&	operator ++	()							{ --_cur_ptr; return *this; };
		reverse_iterator	operator ++	(int)						{ reverse_iterator tmp(*this); --_cur_ptr; return tmp; };
		reverse_iterator&	operator --	()							{ ++_cur_ptr; return *this; };
		reverse_iterator	operator --	(int)						{ reverse_iterator tmp(*this); ++_cur_ptr; return tmp; };
		reverse_iterator	operator +	(difference_type n) const	{ return reverse_iterator(_cur_ptr - n); };
		reverse_iterator&	operator +=	(difference_type n)			{ _cur_ptr -= n; return *this; };
		reverse_iterator	operator -	(difference_type n) const	{ return reverse_iterator(_cur_ptr + n); };
		reverse_iterator&	operator -=	(difference_type n)			{ _cur_ptr += n; return *this; };
		reference			operator []	(difference_type n)	const	{ return *(*this + n);};

	};

	template<class Iter1, class Iter2>
	bool operator == (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() == y.base(); }

	template<class Iter1, class Iter2>
	bool operator != (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() != y.base(); }

	template<class Iter1, class Iter2>
	bool operator < (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() > y.base(); }

	template<class Iter1, class Iter2>
	bool operator > (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() < y.base(); }

	template<class Iter1, class Iter2>
	bool operator <= (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() >= y.base(); }

	template<class Iter1, class Iter2>
	bool operator >= (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template<class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator - (const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{ return y.base() - x.base(); }

	template<class Iterator>
	reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
	{ reverse_iterator<Iterator> tmp(x.base() - n); return tmp; }
}
