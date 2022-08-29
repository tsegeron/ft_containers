# pragma once

# include "utils/treeIterator.hpp"
# include "utils/utils.hpp"
# include "RBTree/LLRBTree.hpp"

namespace ft {

	template<typename Key,
			typename T,
			typename Compare = ft::less<Key>,
			typename Allocator = std::allocator<ft::pair<const Key, T> >
	> struct map {
		typedef map<Key, T, Compare, Allocator>				self;
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef Compare										key_compare;
		typedef ft::mapTreeNode<key_type, T>				treeNodeType;
		typedef ft::LLRBTree<treeNodeType, Compare>			treeType;
		typedef typename treeType::allocator_type			allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef ft::pair<const Key, T>						value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef typename treeType::iterator					iterator;
		typedef typename treeType::const_iterator			const_iterator;
		typedef typename treeType::reverse_iterator			reverse_iterator;
		typedef typename treeType::const_reverse_iterator	const_reverse_iterator;

		struct value_compare {
			template<typename, typename, typename, typename> friend struct map;
			value_compare() : _comp(Compare()) {};
			bool	operator()(const value_type& l, const value_type& r) const { return _comp(l.first, r.first); };
		protected:
			value_compare(Compare c) : _comp(c) {};
			Compare	_comp;
		};


		map() : RBTree() {};
		explicit map(const Compare& comp, const Allocator& alloc = Allocator());
		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
		map(const map& other) : RBTree(other.RBTree) {};
		virtual ~map() {};

		map& operator = (const map& other);
		allocator_type	get_allocator() const	{ return RBTree._alloc; };

		T&			at(const Key& key)			{ return _range_check(key); };
		const T&	at(const Key& key) const	{ return _range_check(key); };
		T& operator	[](const Key& key);

		iterator				begin()				{ return RBTree.begin(); };
		const_iterator			begin() const		{ return RBTree.begin(); };
		iterator				end()				{ return RBTree.end(); };
		const_iterator			end() const			{ return RBTree.end(); };
		reverse_iterator		rbegin()			{ return RBTree.rbegin(); };
		const_reverse_iterator	rbegin() const		{ return RBTree.rbegin(); };
		reverse_iterator		rend()				{ return RBTree.rend(); };
		const_reverse_iterator	rend() const		{ return RBTree.rend(); };

		bool		empty()		const	{ return RBTree.empty(); };
		size_type	size()		const	{ return RBTree.size(); };
		size_type	max_size()	const	{ return RBTree.getAllocator().max_size(); };

		void						clear()							{ RBTree.clear(); };
		ft::pair<iterator, bool>	insert(const value_type& value)	{ return RBTree.push(value); };
		iterator					insert(iterator hint, const value_type& value);
		template<class InputIt>
		void						insert(InputIt first, InputIt last);
		void						erase(iterator first, iterator last);
		void						erase(iterator pos);
		size_type					erase(const Key& key)	{ return RBTree.erase(key); };
		void						swap(map& other)		{ RBTree.swap(other.RBTree); };

		size_type		count(const Key& key) const;
		iterator		find(const Key& key)		{ return RBTree.get(key); };
		const_iterator	find(const Key& key) const	{ return RBTree.get(key); };

		ft::pair<iterator, iterator>				equal_range(const Key& key)			{ return RBTree.equal_range(key); };
		ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const	{ return RBTree.equal_range(key); };
		iterator									lower_bound(const Key& key)			{ return RBTree.lower_bound(key); };
		const_iterator								lower_bound(const Key& key) const	{ return RBTree.lower_bound(key); };
		iterator									upper_bound(const Key& key)			{ return RBTree.upper_bound(key); };
		const_iterator								upper_bound(const Key& key) const	{ return RBTree.upper_bound(key); };

		key_compare			key_comp()		const { return RBTree.getCompare(); };
		value_compare		value_comp()	const { return value_compare(); };

		/* these functions below are added for demonstration purposes */
		void		printTree()						const { RBTree.printTree(); };
		void		printTreeInOrder()				const { RBTree.printTreeInOrder(); };
		unsigned	height(bool countReds = false)	const { return RBTree.height(countReds); }

	private:
		treeType		RBTree;

		T&	_range_check(const Key& key) {
			iterator	tmp = find(key);
			if (tmp == end())
				throw std::out_of_range("ft::map::at:  key not found");
			return tmp->second;
		};

	};

	template<class Key, class T, class Comp, class Alloc>
	map<Key, T, Comp, Alloc>::map(const Comp& comp, const Alloc& alloc) : RBTree()
	{
		RBTree.setCompare(comp);
		RBTree.setAllocator(alloc);
	}

	template<class Key, class T, class Comp, class Alloc>
	template<class InputIt>
	map<Key, T, Comp, Alloc>::map(InputIt f, InputIt l, const Comp& comp, const Alloc& alloc) : RBTree()
	{
		RBTree.setCompare(comp);
		RBTree.setAllocator(alloc);
		for (; f != l; ++f)
			RBTree.push(*f);
	}

	template<class Key, class T, class Comp, class Alloc>
	map<Key, T, Comp, Alloc> &map<Key, T, Comp, Alloc>::operator=(const map<Key, T, Comp, Alloc> &other)
	{
		if (this != & other)
			RBTree = other.RBTree;
		return *this;
	}


	template<class Key, class T, class Comp, class Alloc>
	T&	map<Key, T, Comp, Alloc>::operator[](const Key &key)
	{
		return RBTree.push(ft::make_pair(key, T())).first->second;
	}

	// Inserts value in the position as close as possible, just prior, to hint. Wtf? Just push, idc
	template<class Key, class T, class Comp, class Alloc>
	typename map<Key, T, Comp, Alloc>::iterator
	        map<Key, T, Comp, Alloc>::insert(iterator hint, const value_type &value)
	{
		if (hint) {} // just for -Wall -Wextra -Werror
		return RBTree.push(value).first;
	}

	template<class Key, class T, class Comp, class Alloc>
	template<class InputIt>
	void	map<Key, T, Comp, Alloc>::insert(InputIt first, InputIt last)
	{
		for (; first != last; ++first)
			RBTree.push(*first);
	}

	template<class Key, class T, class Comp, class Alloc>
	void	map<Key, T, Comp, Alloc>::erase(iterator first, iterator last)
	{
		while(first != last)
			erase(first++);
	}

	template<class Key, class T, class Comp, class Alloc>
	void	map<Key, T, Comp, Alloc>::erase(iterator pos)
	{
		iterator	it = RBTree.get(pos->first);
		if (it == end())
			return;
		if (it != pos || pos == end())
		{
			char *segMePlease = nullptr; // in case we accept iterator of other map
			*segMePlease = 0;
		}
		RBTree.erase(pos->first);
	}


	template<class Key, class T, class Comp, class Alloc>
	typename map<Key, T, Comp, Alloc>::size_type
	        map<Key, T, Comp, Alloc>::count(const Key& key) const
	{
		return RBTree.get(key) != RBTree.end();
	}


	/* Non-member functions */
	template<class Key, class T, class Comp, class Alloc>
	bool	operator==(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return l.size() == r.size() && ft::equal(l.begin(), l.end(), r.begin());
	}

	template<class Key, class T, class Comp, class Alloc>
	bool	operator!=(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return !(l == r);
	}

	template<class Key, class T, class Comp, class Alloc>
	bool	operator<(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
	}

	template<class Key, class T, class Comp, class Alloc>
	bool	operator<=(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return !(r < l);
	}

	template<class Key, class T, class Comp, class Alloc>
	bool	operator>(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return r < l;
	}

	template<class Key, class T, class Comp, class Alloc>
	bool	operator>=(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		return !(l < r);
	}

	template<class Key, class T, class Comp, class Alloc>
	void	swap(const ft::map<Key, T, Comp, Alloc>& l, const ft::map<Key, T, Comp, Alloc>& r) {
		l.swap(r);
	}
/* ---------------------------------------------------------------------------- */

} // namespace ft
