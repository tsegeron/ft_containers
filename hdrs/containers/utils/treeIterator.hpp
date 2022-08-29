#pragma once

# include "iterator.hpp"

namespace ft {

	/* normal tree iterator */
	template<class nodeType>
	struct tree_iterator : iterator<bidirectional_iterator_tag, nodeType> {
		typedef random_access_iterator_tag		iterator_category;
		typedef tree_iterator<nodeType>			self;
		typedef nodeType						node_type;
		typedef nodeType*						n_pointer;
		typedef nodeType&						n_reference;
		typedef typename nodeType::keyType		key_type;
		typedef typename nodeType::valueType	value_type;
		typedef value_type*						pointer;
		typedef value_type&						reference;
		typedef std::ptrdiff_t					difference_type;

		tree_iterator()
				: _cur_ptr(nullptr), _root(nullptr), _rend(nullptr), _end(nullptr) {};

		tree_iterator(n_pointer ptr)
				: _cur_ptr(ptr), _root(nullptr), _rend(nullptr), _end(nullptr) { managePositions(); };

		tree_iterator(const tree_iterator& ref)
				: _cur_ptr(ref._cur_ptr), _root(ref._root), _rend(ref._rend), _end(ref._end) { managePositions(); };

		tree_iterator& operator=(const tree_iterator& o) { _cur_ptr = o._cur_ptr; return *this; };

		n_pointer	base() const { return _cur_ptr; };


		reference	operator *	() const { return _cur_ptr->value; };
		pointer		operator ->	() const { return &_cur_ptr->value; };

		self	&operator	++	()		{ increment(); return *this; };
		self	operator	++	(int)	{ self tmp(*this); increment(); return tmp; };
		self	&operator	--	()		{ decrement(); return *this;};
		self	operator	--	(int)	{ self tmp(*this); decrement(); return tmp; };

		friend bool	operator	==	(const self& x, const self& y) { return x._cur_ptr == y._cur_ptr; };
		friend bool	operator	!=	(const self& x, const self& y) { return !(x._cur_ptr == y._cur_ptr); };

	private:
		n_pointer	_cur_ptr;
		n_pointer	_root;
		n_pointer	_rend;
		n_pointer	_end;

		void		increment();
		void		decrement();
		void		managePositions();
		n_pointer	min(n_pointer node) const;
		n_pointer	max(n_pointer node) const;
	};


	template<class nodeType>
	void	tree_iterator<nodeType>::increment()
	{
		if (_cur_ptr == _rend)
			managePositions();
		if (_cur_ptr == _end) /* forcing segmentation to disable incrementing end() */
		{
			char *segMePlease	= nullptr;
			*segMePlease		= 0;
		}

		if (_cur_ptr->right && _cur_ptr->right != _end && _cur_ptr->right != _rend)
			_cur_ptr = min(_cur_ptr->right);
		else if (_cur_ptr == _end->parent)
			_cur_ptr = _cur_ptr->right;
		else
		{
			while (_cur_ptr != _root && _cur_ptr == _cur_ptr->parent->right)
				_cur_ptr = _cur_ptr->parent;
			_cur_ptr = _cur_ptr->parent;
		}
	}

	template<class nodeType>
	void	tree_iterator<nodeType>::decrement()
	{
		if (_cur_ptr == _end)
			managePositions();
		if (_cur_ptr == _rend) /* forcing segmentation to disable decrementing begin() */
		{
			char *segMePlease	= nullptr;
			*segMePlease		= 0;
		}

		if (_cur_ptr == min(_root))
			_cur_ptr = _cur_ptr->left;
		else if (_cur_ptr->left && _cur_ptr->left != _rend && _cur_ptr->left != _end) //
			_cur_ptr = max(_cur_ptr->left);
		else
		{
			while (_cur_ptr != _end && _cur_ptr != _root && _cur_ptr == _cur_ptr->parent->left)
				_cur_ptr = _cur_ptr->parent;
			_cur_ptr = _cur_ptr->parent;
		}
	}

	template<class nodeType>
	void	tree_iterator<nodeType>::managePositions()
	{
		if (_cur_ptr == nullptr)
			return;

		_root = _cur_ptr;
		while (_root->parent != nullptr)
			_root = _root->parent;

		_end	= max(_root);
		if (_end->right)
			_end = _end->right;
		_rend	= min(_root);
		if (_rend->left)
			_rend = _rend->left;
	}


	template<class nodeType>
	nodeType*	tree_iterator<nodeType>::min(n_pointer node) const
	{
		if (!node || !node->left)
			return node;
		while (node->left && node->left->left)
			node = node->left;
		return node;
	}

	template<class nodeType>
	nodeType*	tree_iterator<nodeType>::max(n_pointer node) const
	{
		if (!node || !node->right || !node->left)
			return node;
		while (node->right && node->right->left)
			node = node->right;
		return node;
	}
	/* normal tree iterator */



	/* const tree iterator */
	template<class nodeType>
	struct tree_const_iterator : iterator<bidirectional_iterator_tag, nodeType> {
		typedef random_access_iterator_tag		iterator_category;
		typedef tree_const_iterator<nodeType>	self;
		typedef nodeType						node_type;
		typedef nodeType*						n_pointer;
		typedef nodeType&						n_reference;
		typedef typename nodeType::keyType		key_type;
		typedef typename nodeType::valueType	value_type;
		typedef const value_type*				pointer;
		typedef const value_type&				reference;
		typedef std::ptrdiff_t					difference_type;

		tree_const_iterator()
				: _cur_ptr(nullptr), _root(nullptr), _rend(nullptr), _end(nullptr) {};

		tree_const_iterator(n_pointer ptr)
				: _cur_ptr(ptr), _root(nullptr), _rend(nullptr), _end(nullptr) { managePositions(); };

		tree_const_iterator(const tree_iterator<nodeType>& ref)
				: _cur_ptr(ref.base()), _root(nullptr), _rend(nullptr), _end(nullptr) { managePositions(); };

		tree_const_iterator(const tree_const_iterator& ref)
				: _cur_ptr(ref._cur_ptr), _root(ref._root), _rend(ref._rend), _end(ref._end) { managePositions(); };

		tree_const_iterator& operator=(const tree_const_iterator& o) { _cur_ptr = o._cur_ptr; return *this; };

		n_pointer	base() const { return _cur_ptr; };


		reference	operator *	() const { return _cur_ptr->value; };
		pointer		operator ->	() const { return &_cur_ptr->value; };

		self	&operator	++	()		{ increment(); return *this; };
		self	operator	++	(int)	{ n_pointer tmp(*this); operator++(); return tmp; };
		self	&operator	--	()		{ decrement(); return *this;};
		self	operator	--	(int)	{ n_pointer tmp(*this); operator--(); return tmp; };

		friend bool	operator	==	(const self& x, const self& y) { return x._cur_ptr == y._cur_ptr; };
		friend bool	operator	!=	(const self& x, const self& y) { return !(x._cur_ptr == y._cur_ptr); };

	private:
		n_pointer	_cur_ptr;
		n_pointer	_root;
		n_pointer	_rend;
		n_pointer	_end;

		void		increment();
		void		decrement();
		void		managePositions();
		n_pointer	min(n_pointer node) const;
		n_pointer	max(n_pointer node) const;
	};


	template<class nodeType>
	void	tree_const_iterator<nodeType>::increment()
	{
		if (_cur_ptr == _rend)
			managePositions();
		if (_cur_ptr == _end) /* forcing segmentation to disable incrementing end() */
		{
			char *segMePlease	= nullptr;
			*segMePlease		= 0;
		}

		if (_cur_ptr->right && _cur_ptr->right != _end && _cur_ptr->right != _rend) //
			_cur_ptr = min(_cur_ptr->right);
		else if (_cur_ptr == max(_root))
			_cur_ptr = _cur_ptr->right;
		else
		{
			while (_cur_ptr != _root && _cur_ptr == _cur_ptr->parent->right)
				_cur_ptr = _cur_ptr->parent;
			_cur_ptr = _cur_ptr->parent;
		}
	}

	template<class nodeType>
	void	tree_const_iterator<nodeType>::decrement()
	{
		if (_cur_ptr == _end)
			managePositions();
		if (_cur_ptr == _rend) /* forcing segmentation to disable decrementing begin() */
		{
			char *segMePlease	= nullptr;
			*segMePlease		= 0;
		}

		if (_cur_ptr == min(_root))
			_cur_ptr = _cur_ptr->left;
		else if (_cur_ptr->left && _cur_ptr->left != _rend && _cur_ptr->left != _end) //
			_cur_ptr = max(_cur_ptr->left);
		else
		{
			while (_cur_ptr != _end && _cur_ptr != _root && _cur_ptr == _cur_ptr->parent->left)
				_cur_ptr = _cur_ptr->parent;
			_cur_ptr = _cur_ptr->parent;
		}
	}

	template<class nodeType>
	void	tree_const_iterator<nodeType>::managePositions()
	{
		if (_cur_ptr == nullptr)
			return;

		_root = _cur_ptr;
		while (_root->parent != nullptr)
			_root = _root->parent;

		_end	= max(_root);
		if (_end->right)
			_end = _end->right;
		_rend	= min(_root);
		if (_rend->left)
			_rend = _rend->left;
	}


	template<class nodeType>
	nodeType*	tree_const_iterator<nodeType>::min(n_pointer node) const
	{
		if (!node || !node->left)
			return node;
		while (node->left && node->left->left)
			node = node->left;
		return node;
	}

	template<class nodeType>
	nodeType*	tree_const_iterator<nodeType>::max(n_pointer node) const
	{
		if (!node || !node->right || !node->left)
			return node;
		while (node->right && node->right->left)
			node = node->right;
		return node;
	}
	/* const tree iterator */

} // namespace ft
