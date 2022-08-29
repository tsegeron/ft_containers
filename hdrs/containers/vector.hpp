# pragma once

# include <memory>
# include "utils/utils.hpp"
# include "utils/iterator.hpp"

namespace ft {

template<typename T, typename Alloc>
struct _vector_base {
protected:
	typedef std::allocator<T>	allocator_type;
	explicit _vector_base(Alloc _al = Alloc()) : _alloc(_al) {};

	allocator_type	_alloc;
}; // struct _vector_base


template<typename T, typename Alloc = std::allocator<T> >
struct vector : _vector_base<T, Alloc> {

	typedef	_vector_base<T, Alloc>					base;
	typedef vector<T, Alloc>						self;
	typedef T										value_type;
	typedef typename base::allocator_type			allocator_type;
	typedef typename Alloc::reference				reference;
	typedef typename Alloc::const_reference			const_reference;
	typedef typename Alloc::pointer					pointer;
	typedef typename Alloc::const_pointer			const_pointer;
	typedef typename Alloc::size_type				size_type;
	typedef typename Alloc::difference_type			difference_type;
	typedef ft::normal_iterator<value_type>			iterator;
	typedef ft::normal_iterator<const value_type>	const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;


private:
	allocator_type	_m_Alloc;
	pointer 		_m_Data;
	pointer			_m_Data_end;

	size_type		_m_Size;
	size_type		_m_Capacity;

public:
	/* Member Functions */
	vector();
	explicit vector(const allocator_type& _al);
	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	template<typename InputIter>
			vector(InputIter first, InputIter last, const allocator_type& alloc = allocator_type(),
				   typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type * = nullptr);
	vector(const vector& other);
	virtual ~vector();

	self& operator = (const self& other);
	void	assign(size_type count, const T& value);
	template<class InputIter>
			void assign(InputIter first, InputIter last,
						typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type * = nullptr);
	allocator_type	get_allocator() const { return _m_Alloc; };
	/* ---------------------------------------------------------------------------- */



	/* Iterators */
	iterator		begin()						{ return iterator(_m_Data); };
	const_iterator	begin() const				{ return const_iterator(_m_Data); };
	iterator		end()						{ return iterator(_m_Data + _m_Size); };
	const_iterator	end() const					{ return const_iterator(_m_Data + _m_Size); };

	reverse_iterator		rbegin()			{ return reverse_iterator(end()); };
	const_reverse_iterator	rbegin() const		{ return const_reverse_iterator(end()); };
	reverse_iterator		rend()				{ return reverse_iterator(begin()); };
	const_reverse_iterator	rend() const		{ return const_reverse_iterator(begin()); };
	/* ---------------------------------------------------------------------------- */



	/* Element Access */
	reference		operator[](size_type index)			{ return _m_Data[index]; };
	const_reference	operator[](size_type index) const	{ return _m_Data[index]; };
	reference		at(size_type index)					{ _m_range_check(index); return _m_Data[index]; };
	const_reference	at(size_type index) const			{ _m_range_check(index); return _m_Data[index]; };
	reference		front()								{ return *begin(); };
	const_reference	front() const						{ return *begin(); };
	reference		back()								{ return _m_Data[_m_Size - 1]; };
	const_reference	back() const						{ return _m_Data[_m_Size - 1]; };
	T*				data()								{ return _m_Data; };
	/* ---------------------------------------------------------------------------- */



	/* Capacity */
	bool	    empty()			const { return !_m_Size; };					/* ^-^ */
	size_type	size()			const { return _m_Size; };					/* ^-^ */
	size_type	capacity()		const { return _m_Capacity; };				/* ^-^ */
	size_type	max_size()		const { return _m_Alloc.max_size(); };		/* ^-^ */
	void		reserve(size_type newCapacity);								/* implemented below */
	/* ---------------------------------------------------------------------------- */



	/* Modifiers */
	void		clear()							/* (˜･ᴗ･˜) */						{ erase(begin(), end()); };
	iterator	insert(iterator pos, const T& value);
	iterator	insert(iterator pos, size_type count, const T& value);
	template<class InputIter>
			void	insert(iterator pos, InputIter first, InputIter last,
						   typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type * = nullptr);
	iterator	erase(iterator pos)				/* (˜･ᴗ･˜) */						{ return erase(pos, pos + 1); };
	iterator	erase(iterator first, iterator last);
	void		push_back(const T& value);
	void		pop_back()						/* (˜･ᴗ･˜) */						{ erase(--end()); };
	void		resize(size_type count, const T& value = T());
	void		swap(vector& other);

	/* ---------------------------------------------------------------------------- */



private:
	/* Helper Functions */
	void	_m_range_check(size_t index) {
		if (index >= _m_Size)
			throw std::out_of_range("ft::vector: Index out of range");
	};

	size_t	_m_destroy(pointer first, pointer last) {
		size_t	i = 0;
		for (; first != last; ++first, ++i)
			_m_Alloc.destroy(first++);
		return i;
	};

	size_t	_m_destroy(iterator first, iterator last) {
		size_t	i = 0;
		for (; first != last; ++first, ++i)
			_m_Alloc.destroy(first.base());
		return i;
	};

	void	_m_realloc(size_type newCapacity) {
		_m_Alloc.deallocate(_m_Data, _m_Capacity);
		_m_Capacity = newCapacity;
		_m_Data = _m_Alloc.allocate(_m_Capacity);
	};

	size_type	_m_get_newCapacity()						const { return _m_Capacity + (_m_Capacity >> 1); };
	size_type	_m_get_newCapacity(size_type oldCapacity)	const { return oldCapacity + (oldCapacity >> 1); };

	struct	IteratorOutOfRange : std::exception {
		IteratorOutOfRange() : _err_msg("Requested iterator refers to a non-existent memory location") {};
		virtual ~IteratorOutOfRange() throw() {};
		virtual const char* what() const throw() { return _err_msg.c_str(); };
	private:
		std::string	_err_msg;
	};

	/* ---------------------------------------------------------------------------- */
}; /* struct vector */

/* ---------------------------------------------------------------------------- */
/* Non-member functions */
template<typename T, typename Alloc>
bool	operator==(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
bool	operator!=(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
bool	operator<(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
bool	operator<=(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
bool	operator>(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
bool	operator>=(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

template<typename T, typename Alloc>
void	swap(const vector<T, Alloc> &l, const vector<T, Alloc> &r);

/* ---------------------------------------------------------------------------- */





/*********************** Vector Functions' Implementation ***********************/

/* ----------------------------- Member Functions ----------------------------- */
template<typename T, typename Alloc>
vector<T, Alloc>::vector()
	: _m_Alloc(), _m_Data(nullptr), _m_Data_end(0), _m_Size(0), _m_Capacity(0)
{
	_m_realloc(2);
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type& _al)
	: _m_Alloc(_al), _m_Data(nullptr), _m_Data_end(0), _m_Size(0), _m_Capacity(0)
{
	_m_realloc(2);
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc)
	: _m_Alloc(alloc), _m_Data(), _m_Data_end(0), _m_Size(0), _m_Capacity(_m_get_newCapacity(n))
{
	_m_Data = _m_Alloc.allocate(_m_Capacity);

	for (; _m_Size < n; ++_m_Size)
		_m_Alloc.template construct(_m_Data + _m_Size, val);
}

template<typename T, typename Alloc>
template<typename InputIter>
vector<T, Alloc>::vector(InputIter first, InputIter last, const allocator_type& alloc,
						 typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type *)
	: _m_Alloc(alloc), _m_Data(nullptr), _m_Data_end(0), _m_Size(0), _m_Capacity(0)
{
	if (!ft::is_iterator_tag_valid<typename ft::iterator_traits<InputIter>::iterator_category>::value)
		throw ft::InvalidIterator();

	if (last < first)
		throw std::length_error("vector");

	_m_Capacity = _m_get_newCapacity(last - first);

	_m_Data = _m_Alloc.allocate(_m_Capacity);

	for (; first != last; ++first, ++_m_Size)
		_m_Data[_m_Size] = *first;

}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const vector& other)
	: _m_Alloc(other._m_Alloc), _m_Data(nullptr), _m_Data_end(0), _m_Size(0), _m_Capacity(0)
{
	*this = other;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector()
{
	clear();
	_m_Alloc.deallocate(_m_Data, _m_Capacity);
	_m_Data		= nullptr;
	_m_Capacity	= 0;
}

template<typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const self &other)
{
	if (this != &other)
	{
		clear();

		if (_m_Capacity != other._m_Capacity)
			_m_realloc(other._m_Capacity);

		for (_m_Size = 0; _m_Size < other._m_Size; _m_Size++)
			_m_Data[_m_Size] = other._m_Data[_m_Size]; // std::move c++11/14

		_m_Alloc	= other._m_Alloc;
		_m_Data_end = other._m_Data_end;
	}
	return *this;
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::assign(size_type count, const T &value)
{
	clear();

	if (count > _m_Capacity)
		_m_realloc(_m_get_newCapacity(count));

	_m_Size = 0;
	for (; _m_Size < count; ++_m_Size)
		_m_Alloc.template construct(_m_Data + _m_Size, value);
}

template<typename T, typename Alloc>
template<class InputIter>
void	vector<T, Alloc>::assign(InputIter first, InputIter last,
								 typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type *)
{
	if (!ft::is_iterator_tag_valid<typename ft::iterator_traits<InputIter>::iterator_category>::value)
		throw ft::InvalidIterator();

	if (last < first)
		throw std::length_error("vector");

	size_type	count = last - first;

	clear();
	_m_Size = 0;
	if (count > _m_Capacity)
		_m_realloc(_m_get_newCapacity(count));

	for (; first != last; ++first, ++_m_Size)
		_m_Data[_m_Size] = *first;
}

/* ---------------------------------------------------------------------------- */



/* --------------------------------- Capacity --------------------------------- */
template<typename T, typename Alloc>
void	vector<T, Alloc>::reserve(size_type newCapacity)
{
	if (newCapacity <= _m_Capacity)
		return;

	T*	newBlock = _m_Alloc.allocate(newCapacity);

	for (size_type i = 0; i < _m_Size; ++i) {
		_m_Alloc.template construct(newBlock + i, _m_Data[i]);
		_m_Alloc.destroy(_m_Data + i);
	}

	_m_Alloc.deallocate(_m_Data, _m_Capacity);
	_m_Data		= newBlock;
	_m_Capacity	= newCapacity;
}
/* ---------------------------------------------------------------------------- */



/* --------------------------------- Modifiers -------------------------------- */
template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, const T &value)
{
	return insert(pos, (size_type)1, value);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, size_type count, const T& value)
{
	if (pos > end() || pos < begin())
		throw IteratorOutOfRange();

	size_type	offset = pos - begin();

	if (_m_Size + count < _m_Capacity)
	{
		if (pos == end())
			while (count-- > 0)
				_m_Alloc.template construct(_m_Data + _m_Size++, value);
		else
		{
			for (size_type j = count; j > 0; --j)
				_m_Alloc.template construct(_m_Data + _m_Size++, T());

			size_type i = _m_Size - 1;
			for (; i > offset + count - 1; --i)
				_m_Data[i] = _m_Data[i - count];
			for (; count > 0; --count, --i)
				_m_Data[i] = value;
		}
	}
	else
	{
		_m_Size += count;
		T*	newBlock = _m_Alloc.allocate(_m_get_newCapacity(_m_Size));

		size_type i = 0;
		for (; i < offset; ++i)
		{
			_m_Alloc.template construct(newBlock + i, *(_m_Data + i));
			_m_Alloc.destroy(_m_Data + i);
		}
		for (size_type j = count; j > 0; --j)
			newBlock[i++] = value;
		for (size_type j = i - count; i < _m_Size; ++i, ++j)
		{
			_m_Alloc.template construct(newBlock + i, *(_m_Data + j));
			_m_Alloc.destroy(_m_Data + j);
		}
		_m_Alloc.deallocate(_m_Data, _m_Capacity);
		_m_Capacity = _m_get_newCapacity(_m_Size);
		_m_Data = newBlock;
	}

	return begin() + offset;
}

template<typename T, typename Alloc>
template<class InputIter>
void	vector<T, Alloc>::insert(iterator pos, InputIter first, InputIter last,
								 typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type *)
{
	if (pos > end() || pos < begin())
		throw IteratorOutOfRange();
	if (first >= last)
		return;

	size_type	offset	= pos - begin();
	size_type	count	= last - first;

	if (_m_Size + count < _m_Capacity)
	{
		if (pos == end())
			for (; first != last; ++first)
				_m_Alloc.template construct(_m_Data + _m_Size++, *first);
		else
		{
			for (size_type j = count; j > 0; --j)
				_m_Alloc.template construct(_m_Data + _m_Size++, T());

			size_type i = _m_Size - 1;
			for (; i > offset + count - 1; --i)
				_m_Data[i] = _m_Data[i - count];
			for (; first != last; ++first, ++i)
				_m_Data[i] = *first;
		}
	}
	else
	{
		_m_Size += count;
		T*	newBlock = _m_Alloc.allocate(_m_get_newCapacity(_m_Size));

		size_type i = 0;
		for (; i < offset; ++i)
		{
			_m_Alloc.template construct(newBlock + i, *(_m_Data + i));
			_m_Alloc.destroy(_m_Data + i);
		}
		for (; first != last; ++first)
			newBlock[i++] = *first;
		for (size_type j = i - count; i < _m_Size; ++i, ++j)
		{
			_m_Alloc.template construct(newBlock + i, *(_m_Data + j));
			_m_Alloc.destroy(_m_Data + j);
		}
		_m_Alloc.deallocate(_m_Data, _m_Capacity);
		_m_Capacity = _m_get_newCapacity(_m_Size);
		_m_Data = newBlock;
	}
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator	vector<T, Alloc>::erase(iterator first, iterator last)
{
	if (first != last && _m_Size && _m_Data != nullptr)
	{
		for(; last != end(); first++, ++last)
			*first = *last;

		_m_Size -= _m_destroy(first, end());
	}
	return first;
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::push_back(const T &value)
{
	insert(end(), value);
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::resize(size_type count, const T& value)
{
	if (count <= _m_Size)
		erase(begin() + count, end());
	else
	{
		if (count > _m_Capacity)
			reserve(_m_get_newCapacity(count));

		while (_m_Size < count)
			_m_Alloc.template construct(_m_Data + _m_Size++, value);
	}
}

template<typename T, typename Alloc>
void	vector<T, Alloc>::swap(vector<T, Alloc> &other)
{
	if (_m_Data == other._m_Data)
	{
		ft::swap(_m_Alloc, other._m_Alloc);
		ft::swap(_m_Data_end, other._m_Data_end);
		ft::swap(_m_Size, other._m_Size);
		ft::swap(_m_Capacity, other._m_Capacity);
	}
	else
		ft::swap(*this, other);
}
/* ---------------------------------------------------------------------------- */



/* Non-member functions */
template<typename T, typename Alloc>
bool	operator==(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return l.size() == r.size() && ft::equal(l.begin(), l.end(), r.begin());
}

template<typename T, typename Alloc>
bool	operator!=(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return !(l == r);
}

template<typename T, typename Alloc>
bool	operator<(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
}

template<typename T, typename Alloc>
bool	operator>(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return r < l;
}

template<typename T, typename Alloc>
bool	operator<=(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return !(r < l);
}

template<typename T, typename Alloc>
bool	operator>=(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	return !(l < r);
}

template<typename T, typename Alloc>
void	swap(const vector<T, Alloc> &l, const vector<T, Alloc> &r) {
	ft::swap(l, r);
}
/* ---------------------------------------------------------------------------- */

} // namespace ft
