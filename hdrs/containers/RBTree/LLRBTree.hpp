# pragma once

# include <iostream>
# include <string>
# include "RBTreeNodes.hpp"

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"


namespace ft {

	template<	class K,
				class Compare = ft::less<typename K::keyType>,
				class Alloc = std::allocator<typename K::valueType>
	> struct LLRBTree {

		typedef LLRBTree<K, Compare, Alloc>							selfType;
		typedef K													nodeType;
		typedef K*													nodePointer;
		typedef typename K::keyType									keyType;
		typedef Compare												compareType;
		typedef typename Alloc::template rebind<nodeType>::other	allocator_type;
		typedef ft::tree_iterator<nodeType>							iterator;
		typedef ft::tree_const_iterator<nodeType>					const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		LLRBTree()
			: _alloc(allocator_type()), _root(nullptr), _end(_alloc.allocate(1)), _rend(_alloc.allocate(1)), _size(0), _cmp(compareType())
			{
				_alloc.construct(_end, nodeType());
				_alloc.construct(_rend, nodeType());
				updateEnds();
			};
		LLRBTree(const selfType& other);
		LLRBTree& operator=(const LLRBTree& other);
		virtual ~LLRBTree();


		ft::pair<iterator, bool>	push(const typename K::valueType& val);
		iterator					get(const typename K::keyType& key);
		const_iterator				get(const typename K::keyType& key) const;
		bool						erase(const keyType& key);
		void						clear();
		void						swap(selfType& other);

		unsigned					size()							const { return _size; };
		unsigned					height(bool countReds = false)	const { return getTreeHeight(_root, countReds); };
		bool						empty()							const { return !_size; };

		/* Iterators */
		iterator				begin()				{ return iterator(_rend->parent); };
		const_iterator			begin()		const	{ return const_iterator(_rend->parent); };
		iterator				end()				{ return iterator(_end); };
		const_iterator			end()		const	{ return const_iterator(_end); };
		reverse_iterator		rbegin()			{ return reverse_iterator(end()); };
		const_reverse_iterator	rbegin()	const	{ return const_reverse_iterator(end()); };
		reverse_iterator		rend()				{ return reverse_iterator(begin()); };
		const_reverse_iterator	rend()		const	{ return const_reverse_iterator(begin()); };
		/* ------------------- */

		ft::pair<iterator, iterator>				equal_range(const keyType& key);
		ft::pair<const_iterator, const_iterator>	equal_range(const keyType& key) const;
		iterator									lower_bound(const keyType& key);
		const_iterator								lower_bound(const keyType& key) const;
		iterator									upper_bound(const keyType& key);
		const_iterator								upper_bound(const keyType& key) const;


		void			printTree()			const				{ printNodes(_root);};
		void			printTreeInOrder()	const				{ printNodesInOrder(_root); std::cout << "\n"; };

		compareType		getCompare()		const				{ return _cmp; };
		allocator_type	getAllocator()		const				{ return _alloc; };
		void			setCompare(const compareType& cmp)		{ _cmp = cmp; };
		void			setAllocator(const allocator_type& al)	{ _alloc = al; };


	private:
		nodePointer		put(nodePointer &node, nodePointer &newNode, ft::pair<iterator, bool> &ret);
		nodePointer		rotateLeft(nodePointer &node);
		nodePointer		rotateRight(nodePointer &node);
		void			flipColors(nodePointer &node);
		bool			isRed(const nodePointer &node) const { return node != nullptr && node->color; };
		nodePointer		findNode(const keyType& key) const;
		nodePointer		createNode(const typename K::valueType& val);
		void			updateEnds();

		nodePointer		erase(nodePointer node, const keyType& key);
		nodePointer		deleteMin(nodePointer& node);
		nodePointer		moveRedLeft(nodePointer& node);
		nodePointer		moveRedRight(nodePointer& node);
		nodePointer		balance(nodePointer& node);
		nodePointer		min(nodePointer node) const;

		int		getTreeHeight(const nodePointer &n, bool countReds = false) const;
		void	printNodes(const nodePointer &n, const std::string &indent = "") const;
		void	printNodesInOrder(const nodePointer &n) const;
		void	printValue(const nodePointer &n) const;
		void	freeMemory(nodePointer &n);

	protected:
		allocator_type	_alloc;
		nodePointer		_root;
		nodePointer		_end;	// element after the last
		nodePointer		_rend;	// element before the first
		unsigned		_size;
		compareType		_cmp;
	};

	template<class K, class Cmp, class Alloc>
	LLRBTree<K, Cmp, Alloc>::LLRBTree(const selfType& o)
		:  _alloc(o._alloc), _root(nullptr), _end(_alloc.allocate(1)), _rend(_alloc.allocate(1)), _size(0), _cmp(o._cmp)
	{
		_alloc.construct(_end, nodeType());
		_alloc.construct(_rend, nodeType());
		updateEnds();
		LLRBTree<K, Cmp, Alloc>::const_iterator b = o.begin();
		LLRBTree<K, Cmp, Alloc>::const_iterator e = o.end();

		for(; b != e; ++b)
			push(*b);
	}

	template<class K, class Cmp, class Alloc>
	LLRBTree<K, Cmp, Alloc>&	LLRBTree<K, Cmp, Alloc>::operator=(const LLRBTree<K, Cmp, Alloc> &other)
	{
		if (this != &other)
		{
			clear();
			_cmp	= other._cmp;
			_alloc	= other._alloc;

			LLRBTree<K, Cmp, Alloc>::const_iterator b = other.begin();
			LLRBTree<K, Cmp, Alloc>::const_iterator e = other.end();
			for(; b != e; ++b)
				push(*b);
		}
		return *this;
	}

	template<class K, class Cmp, class Alloc>
	LLRBTree<K, Cmp, Alloc>::~LLRBTree()
	{
		freeMemory(_root);

		_end->left		= nullptr;
		_end->right		= nullptr;
		_end->parent	= nullptr;
		_rend->left		= nullptr;
		_rend->right	= nullptr;
		_rend->parent	= nullptr;

		_alloc.destroy(_end);
		_alloc.deallocate(_end, 1);
		_alloc.destroy(_rend);
		_alloc.deallocate(_rend, 1);
		_end	= nullptr;
		_rend	= nullptr;
	}

	/*********************** LLRBTree Functions' Implementation ***********************/

	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::iterator
	LLRBTree<K, Cmp, Alloc>::get(const typename K::keyType& key)
	{
		nodePointer	nodePtr = _root;

		while(nodePtr != nullptr && nodePtr != _end && nodePtr != _rend)
		{
			if (key == nodePtr->getKey())
				break;
			if (_cmp(key, nodePtr->getKey()))
				nodePtr = nodePtr->left;
			else
				nodePtr = nodePtr->right;
		}
		if (nodePtr == _rend)
			nodePtr = _end;
		return iterator(nodePtr);
	}

	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::const_iterator
	LLRBTree<K, Cmp, Alloc>::get(const typename K::keyType& key) const
	{
		nodePointer	nodePtr = _root;

		while(nodePtr != nullptr && nodePtr != _end && nodePtr != _rend)
		{
			if (key == nodePtr->getKey())
				break;
			if (_cmp(key, nodePtr->getKey()))
				nodePtr = nodePtr->left;
			else
				nodePtr = nodePtr->right;
		}
		if (nodePtr == _rend)
			nodePtr = _end;
		return const_iterator(nodePtr);
	}

	template<class K, class Cmp, class Alloc>
	ft::pair<typename LLRBTree<K, Cmp, Alloc>::iterator, bool>
	        LLRBTree<K, Cmp, Alloc>::push(const typename K::valueType& val)
	{
		ft::pair<iterator, bool>	ret;
		nodePointer					newNode = createNode(val);

		_root			= put(_root, newNode, ret);
		_root->color	= nodeType::black;
		_root->parent	= nullptr;
		++_size;
		updateEnds();
		return ret;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::put(nodePointer &node, nodePointer &newNode, ft::pair<iterator, bool> &ret)
	{
		if (!node || node == _end || node == _rend)
		{
			ret.first = iterator(newNode);
			ret.second = true;
			return newNode;
		}
		if (node->getKey() == newNode->getKey())
		{
			ret.first = iterator(node);
			ret.second = false;
			--_size;
			_alloc.destroy(newNode);
			_alloc.deallocate(newNode, 1);
			return node;
		}
		if (_cmp(node->getKey(), newNode->getKey()))
		{
			node->right = put(node->right, newNode, ret);
			node->right->parent = node;
		}
		else
		{
			node->left = put(node->left, newNode, ret);
			node->left->parent = node;
		}

		if (!isRed(node->left) && isRed(node->right))
			node = rotateLeft(node);
		if (isRed(node->left) && isRed(node->left->left))
			node = rotateRight(node);
		if (isRed(node->left) && isRed(node->right))
			flipColors(node);

		return node;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::rotateLeft(nodePointer &node)
	{
		nodePointer	tmp = node->right;

		if (!node || node == _end || node == _rend)
			return node;

		tmp->color			= node->color;
		node->color			= nodeType::red;

		tmp->parent			= node->parent;
		node->parent		= node->right;
		tmp->left->parent	= node;

		node->right			= tmp->left;
		tmp->left			= node;

		return tmp;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::rotateRight(nodePointer &node)
	{
		nodePointer	tmp = node->left;

		if (!node || node == _end || node == _rend)
			return node;

		tmp->color			= node->color;
		node->color			= nodeType::red;

		tmp->parent			= node->parent;
		node->parent		= node->left;
		tmp->right->parent	= node;

		node->left			= tmp->right;
		tmp->right			= node;

		return tmp;
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::flipColors(nodePointer &node)
	{
		if (!node || node == _end || node == _rend)
			return;
		node->color = !node->color;
		if (node->left)
			node->left->color = !node->left->color;
		if (node->right)
			node->right->color = !node->right->color;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::createNode(const typename K::valueType &val)
	{
		nodePointer newNode;
		newNode = _alloc.allocate(1);
		_alloc.construct(newNode, nodeType(val));

		newNode->parent	= nullptr;
		newNode->left	= _end;
		newNode->right	= _end;

		return newNode;
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::updateEnds()
	{
		nodePointer	tmp = _root;

		if(!empty())
		{
			if (_root) {
				while (tmp->left != _end && tmp->left != _rend)
					tmp = tmp->left;
				tmp->left = _rend;
			}
			_rend->left = nullptr;
			_rend->right = _root;
			_rend->parent = tmp;

			tmp = _root;
			if (_root) {
				while (tmp->right != _end && tmp->right != _rend)
					tmp = tmp->right;
				tmp->right = _end;
			}
			_end->left = nullptr;
			_end->right = _root;
			_end->parent = tmp;
		}
		else
		{
			_root			= _end;
			_root->parent	= nullptr;
			_root->left		= _rend;
			_root->right	= nullptr;
			_root->color	= nodeType::black;

			_rend->parent	= _end;
			_rend->left		= nullptr;
			_rend->right	= nullptr;
			_rend->color	= nodeType::black;
		}
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::clear()
	{
		freeMemory(_root);
		_size = 0;
		updateEnds();
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::swap(selfType &other)
	{
		ft::swap(_alloc, other._alloc);
		ft::swap(_root, other._root);
		ft::swap(_end, other._end);
		ft::swap(_rend, other._rend);
		ft::swap(_size, other._size);
		ft::swap(_cmp, other._cmp);
	}

	template<class K, class Cmp, class Alloc>
	bool	LLRBTree<K, Cmp, Alloc>::erase(const keyType& key)
	{
		nodePointer	toDelete = findNode(key);

		if (toDelete == _rend || toDelete == _end || toDelete == nullptr)
			return false;

		_root = erase(_root, key);
		_root->color = nodeType::black;
		_root->parent = nullptr;
		--_size;
		updateEnds();

		return true;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::erase(nodePointer node, const keyType& key)
	{
		if (_cmp(key, node->getKey()))
		{
			if (!isRed(node->left) && !isRed(node->left->left))
				node = moveRedLeft(node);
			node->left = erase(node->left, key);
		}
		else
		{
			if (isRed(node->left))
				node = rotateRight(node);
			if (key == node->getKey() && (node->right == _end || node->right == _rend))
			{
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				return _end;
			}
			if (!isRed(node->right) && !isRed(node->right->left))
				node = moveRedRight(node);
			if (key == node->getKey())
			{
				nodePointer	tmp	= min(node->right);
				tmp->right		= deleteMin(node->right);
				tmp->parent		= node->parent;
				tmp->left		= node->left;
				tmp->color		= node->color; // suka blyat cvet zabyl pomenyat i ebalsya iz-za etogo 2 dnya ebuchih
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				node			= tmp;
				if (node->left && node->left != _rend && node->left != _end)
					node->left->parent = node;
				if (node->right && node->right != _rend && node->right != _end)
					node->right->parent = node;
			}
			else
				node->right = erase(node->right, key);
		}
		return balance(node);
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::deleteMin(nodePointer& node)
	{
		if (!node->left || node->left == _end || node->left == _rend)
		{
			node->left->parent = node;
			return node->left;
		}
		if (!isRed(node->left) && !isRed(node->left->left))
			node = moveRedLeft(node);

		node->left = deleteMin(node->left);

		return balance(node);
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::moveRedLeft(nodePointer &node)
	{
		flipColors(node);
		if (isRed(node->right->left))
		{
			node->right = rotateRight(node->right);
			node = rotateLeft(node);
			flipColors(node);
		}
		return node;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::moveRedRight(nodePointer &node)
	{
		flipColors(node);
		if (isRed(node->left->left))
		{
			node = rotateRight(node);
			flipColors(node);
		}
		return node;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::balance(nodePointer &node)
	{
//		if (!isRed(node->left) && isRed(node->right))
		if (isRed(node->right))
			node = rotateLeft(node);
		if (isRed(node->left) && isRed(node->left->left))
			node = rotateRight(node);
		if (isRed(node->left) && isRed(node->right))
			flipColors(node);

		return node;
	}


	/******************** range, *_bound Functions' Implementation ********************/
	/* case 1: if such key exists:			equal and next bigger
	 * case 2: if key bigger than last:		end()x2
	 * case 3: else:						two same equal to first bigger key
	 */
	template<class K, class Cmp, class Alloc>
	ft::pair<typename LLRBTree<K, Cmp, Alloc>::iterator, typename LLRBTree<K, Cmp, Alloc>::iterator>
			LLRBTree<K, Cmp, Alloc>::equal_range(const keyType &key)
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	template<class K, class Cmp, class Alloc>
	ft::pair<typename LLRBTree<K, Cmp, Alloc>::const_iterator, typename LLRBTree<K, Cmp, Alloc>::const_iterator>
	        LLRBTree<K, Cmp, Alloc>::equal_range(const keyType &key) const
	{
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	/* first equal to key or bigger */
	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::iterator
	        LLRBTree<K, Cmp, Alloc>::lower_bound(const keyType &key)
	{
		iterator	it = --end();
		if (it.base()->getKey() != key && _cmp(it.base()->getKey(), key))
			return ++it;

		it = begin();
		if (_cmp(key, it.base()->getKey()))
			return it;

		while (_cmp(it.base()->getKey(), key))
			++it;
		return it;
	}

	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::const_iterator
	        LLRBTree<K, Cmp, Alloc>::lower_bound(const keyType &key) const
	{
		const_iterator	it = --end();
		if (it.base()->getKey() != key && _cmp(it.base()->getKey(), key))
			return ++it;

		it = begin();
		if (_cmp(key, it.base()->getKey()))
			return it;

		while (_cmp(it.base()->getKey(), key))
			++it;
		return it;
	}

	/* first bigger than key */
	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::iterator
	        LLRBTree<K, Cmp, Alloc>::upper_bound(const keyType &key)
	{
		iterator	it = --end();
		if (!_cmp(key, it.base()->getKey()))
			return ++it;

		it = begin();
		if (_cmp(key, it.base()->getKey()))
			return it;

		while (!_cmp(key, it.base()->getKey()))
			++it;
		return it;
	}

	template<class K, class Cmp, class Alloc>
	typename LLRBTree<K, Cmp, Alloc>::const_iterator
	        LLRBTree<K, Cmp, Alloc>::upper_bound(const keyType &key) const
	{
		const_iterator	it = --end();
		if (!_cmp(key, it.base()->getKey()))
			return ++it;

		it = begin();
		if (_cmp(key, it.base()->getKey()))
			return it;

		while (!_cmp(key, it.base()->getKey()))
			++it;
		return it;
	}


	/*********************** Helper Functions' Implementation ***********************/

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::findNode(const keyType &key) const
	{
		nodePointer	nodePtr = _root;

		while(nodePtr != nullptr && nodePtr != _end && nodePtr != _rend)
		{
			if (key == nodePtr->getKey())
				break;
			if (_cmp(key, nodePtr->getKey()))
				nodePtr = nodePtr->left;
			else
				nodePtr = nodePtr->right;
		}
		return nodePtr;
	}

	template<class K, class Cmp, class Alloc>
	K*	LLRBTree<K, Cmp, Alloc>::min(nodePointer node) const
	{
		while (node->left != nullptr && node->left != _rend && node->left != _end)
			node = node->left;
		return node;
	}

	template<class K, class Cmp, class Alloc>
	int		LLRBTree<K, Cmp, Alloc>::getTreeHeight(const nodePointer &n, bool countReds) const
	{
		if (!n || n == _end || n == _rend)
			return 0;
		if (!n->color || countReds)
			return ft::max(getTreeHeight(n->left, countReds), getTreeHeight(n->right, countReds)) + 1;
		else
			return ft::max(getTreeHeight(n->left), getTreeHeight(n->right));
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::printNodes(const nodePointer &node, const std::string &indent) const
	{
		if (!node || node == _end || node == _rend)
			return;

		printNodes(node->right, indent + "     ");
		std::cout << std::endl << indent;
		printValue(node);
		std::cout << std::endl;
		printNodes(node->left, indent + "     ");
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::printNodesInOrder(const nodePointer &node) const
	{
		if (!node || node == _end || node == _rend)
			return;

		printNodesInOrder(node->left);
		printValue(node);
		printNodesInOrder(node->right);
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::printValue(const nodePointer &n) const
	{
		if (!n || n == _end || n == _rend)
			return;

		std::string	clr = BLACK;
		if (n->color)
			clr = RED;

		std::cout << clr << "[" << RESET;
		if (n == _root)
			std::cout << GREEN << n->getKey() << RESET;
		else
			std::cout << clr << n->getKey() << RESET;
		std::cout << clr << "]" << RESET;
	}

	template<class K, class Cmp, class Alloc>
	void	LLRBTree<K, Cmp, Alloc>::freeMemory(nodePointer &n)
	{
		if (!n || n == _end || n == _rend)
			return;
		freeMemory(n->left);
		freeMemory(n->right);
		n->left		= nullptr;
		n->right	= nullptr;
		n->parent	= nullptr;
		_alloc.destroy(n);
		_alloc.deallocate(n, 1);
		n = nullptr;
	}

}
