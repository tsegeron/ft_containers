# pragma once

# include "../utils/utils.hpp"
# include "../utils/treeIterator.hpp"


namespace ft {

//# define RBTreeNode_BLACK    false
//# define RBTreeNode_RED  	  true

	template<typename K, typename V>
	struct mapTreeNode {
		enum { black, red };
		typedef	K						keyType;
		typedef	ft::pair<const K, V>	valueType;
		typedef	mapTreeNode<K, V>		self;
		typedef	mapTreeNode<K, V>*		selfPtr;

		mapTreeNode()
				: value(valueType()), parent(nullptr), left(nullptr), right(nullptr), color(red) {};
		explicit mapTreeNode(const ft::pair<K, V>& p)
				: value(p), parent(nullptr), left(nullptr), right(nullptr), color(red) {};

		mapTreeNode(const ft::pair<K, V>& p, const selfPtr& parent)
				: value(p), parent(parent), left(nullptr), right(nullptr), color(red) {};

		mapTreeNode(const mapTreeNode& o)
				: value(o.value), parent(o.parent), left(o.left), right(o.right), color(o.color) {};

		mapTreeNode&	operator=(const mapTreeNode& other);

		virtual ~mapTreeNode() {};


		const keyType&	getKey() const { return value.first; };


		valueType	value;
		selfPtr		parent;
		selfPtr		left;
		selfPtr		right;
		bool		color;

	};

	template<typename K, typename V>
	mapTreeNode<K, V>&	mapTreeNode<K, V>::operator=(const self &other)
	{
		if (this != &other)
		{
			value 	= other.value;
			parent	= other.parent;
			left	= other.left;
			right	= other.right;
			color	= other.color;
		}
		return *this;
	}






	template<typename K>
	struct setTreeNode {
		enum { black, red };
		typedef	K					keyType;
		typedef	const K				valueType;
		typedef	setTreeNode<K>		self;
		typedef	setTreeNode<K>*		selfPtr;


		setTreeNode()
				: value(), parent(nullptr), left(nullptr), right(nullptr), color(red) {};
		explicit setTreeNode(const keyType& k)
				: value(k), parent(nullptr), left(nullptr), right(nullptr), color(red) {};

		setTreeNode(const keyType& p, const selfPtr& parent)
				: value(p), parent(parent), left(nullptr), right(nullptr), color(red) {};

		setTreeNode(const setTreeNode& o)
				: value(o.value), parent(o.parent), left(o.left), right(o.right), color(o.color) {};

		setTreeNode& operator=(const setTreeNode& other);

		virtual ~setTreeNode() {};

		const keyType&	getKey() const { return value; };


		valueType	value;
		selfPtr		parent;
		selfPtr		left;
		selfPtr		right;
		bool		color;

	};

	template<typename K>
	setTreeNode<K>&	setTreeNode<K>::operator=(const self &other)
	{
		if (this != &other)
		{
			value 	= other.value;
			parent	= other.parent;
			left	= other.left;
			right	= other.right;
			color	= other.color;
		}
		return *this;
	}

}
