# include "../hdrs/containers/map.hpp"
# include <map>

# define BLUE		"\033[34m"
# define RESET		"\033[0m"

# define printc(msg) std::cout << BLUE << msg << RESET << std::endl
# define print(msg) std::cout << msg << std::endl
# define LINE		printc("------------------------------------------------");

void	constructorsCheck() {
	/* проверка стандартного конструктора */
	{
		printc("empty map");
		ft::map<std::string, int, ft::less<std::string> >	m;

		std::cout	<< "m.size(): " << m.size() << "\n"
					<< "m.height(): " << m.height(true) << "\n";
		m.printTree();
	}
	LINE
	{
		ft::more<std::string>	more;
		ft::map<std::string, int, ft::more<std::string> >	m(more);

		std::cout	<< "m.size(): " << m.size() << "\n"
					<< "m.height(): " << m.height(true) << "\n";
		m.printTree();

		// value_comp() test
		printc("value_comp() test:");
		print("({'1',1}, {'2', 2})");
		print(m.value_comp()(ft::make_pair("1", 1), ft::make_pair("2", 2))); // false
		print("({'3',1}, {'2', 2})");
		print(m.value_comp()(ft::make_pair("3", 1), ft::make_pair("2", 2))); // true
	}
	LINE
	{
//		ft::map<std::string, int, ft::less<std::string> >	one;
		ft::map<std::string, int, ft::more<std::string> >	one;
		std::cout	<< "one.size(): " << one.size() << "\n"
					<< "one.height(): " << one.height(true) << "\n";
		printc("map: 'one'");
		one.insert(ft::pair<std::string, int>("abc", 1));
		one.insert(ft::pair<std::string, int>("bcd", 2));
		one.insert(ft::make_pair("cde", 3));
		one.insert(ft::make_pair("def", 4));
		one.insert(ft::make_pair("efg", 5));
		one.insert(ft::make_pair("fgh", 6));
		one.insert(ft::make_pair("ghi", 7));
		std::cout	<< "one.size(): " << one.size() << "\n"
					<< "one.height(): " << one.height(true) << "\n";
		one.printTree();

		LINE

		/* container copy, assignment test */
		ft::map<std::string, int, ft::more<std::string> >	two(one);
		ft::map<std::string, int, ft::more<std::string> >	three = two;
		printc("after 'two(one)' and 'one.erase(\"def\")'");
		print("map: 'two'");
		one.erase("def");
		std::cout	<< "two.size(): " << two.size() << "\n"
					<< "two.height(): " << two.height(true) << "\n";
		two.printTree();

		LINE

		printc("after 'three = two'");
		print("map: 'three'");
		std::cout	<< "three.size(): " << three.size() << "\n"
					<< "three.height(): " << three.height(true) << "\n";
		three.printTree();

		LINE

		/* iterator copy, assignment test */
		two.printTreeInOrder();
		ft::map<std::string, int, ft::more<std::string> >::iterator	it1(two.begin());
		ft::map<std::string, int, ft::more<std::string> >::iterator	it2 = two.begin();
		std::cout	<< "it1(two.begin()) --> it1->first: " << it1->first << "\n"
					<< "it2 = two.begin() ---> it2->first: " << it1->first << "\n";

		LINE

		/* container's constructor by iterators test */
		printc("constructor by iterators test");

		two.printTreeInOrder();
		++it1;
		it2 = ----two.end();
		std::cout	<< "(++it1->first): " << it1->first << "; "
					<< "(----it2->first): " << it2->first << std::endl;
		ft::map<std::string, int, ft::more<std::string> >	four(it1, it2);
		printc("After four(it1, it2):");
		std::cout	<< "two.size(): " << two.size() << "\n"
					 << "two.height(): " << two.height(true) << "\n";
		std::cout	<< "four.size(): " << four.size() << "\n"
					<< "four.height(): " << four.height(true) << "\n";
		four.printTree();
		four.printTreeInOrder();


		LINE

		/* 'operator =' test */
		printc("'operator =' test");
		ft::map<std::string, int, ft::more<std::string> >	five;
		five = four;
		printc("After five = four:");
		std::cout	<< "five.size(): " << five.size() << "\n"
					<< "five.height(): " << five.height(true) << "\n";
		five.printTree();
		five.printTreeInOrder();

		LINE

	}

}

void	elementAccessCheck() {
	printc("Element Access Check");
	printc("at()");
	ft::map<int, int, ft::more<int> >	m;
	std::map<int, int, ft::more<int> >	original;

	m.insert(ft::make_pair(9,9));	original.insert(std::make_pair(9,9));
	m.insert(ft::make_pair(8,8));	original.insert(std::make_pair(8,8));
	m.insert(ft::make_pair(7,7));	original.insert(std::make_pair(7,7));
	m.insert(ft::make_pair(6,6));	original.insert(std::make_pair(6,6));
	m.insert(ft::make_pair(5,5));	original.insert(std::make_pair(5,5));
	m.insert(ft::make_pair(4,4));	original.insert(std::make_pair(4,4));
	m.insert(ft::make_pair(3,3));	original.insert(std::make_pair(3,3));
	m.insert(ft::make_pair(2,2));	original.insert(std::make_pair(2,2));
	m.insert(ft::make_pair(1,1));	original.insert(std::make_pair(1,1));
	m.printTree();
	try {
		std::cout	<< "m.at(1): " << m.at(1) << "\n"
					<< "m.at(9): " << m.at(9) << "\n"
					<< "m.at(-100): " << m.at(-100) << "\n";
	} catch (std::exception& ex) { print(ex.what()); }
	try {
		std::cout	<< "original.at(1): " << original.at(1) << "\n"
					 << "original.at(9): " << original.at(9) << "\n"
					 << "original.at(-100): " << original.at(-100) << "\n";
	} catch (std::exception& ex) { print(ex.what()); }
	printc("m.at(5) after 'm.at(5) = 555':");
	m.at(5) = 555;
	original.at(5) = 555;
	std::cout << "m.at(5): " << m.at(5) << "\n";
	std::cout << "original.at(5): " << original.at(5) << "\n";

	LINE

	printc("operator[]");
	std::cout	<< "m[1]: " << m[1] << "\n"
				<< "m[9]: " << m[9] << "\n"
				<< "m[-100]: " << m[-100] << "\n"
				<< "m[100]: " << m[100] << "\n";
	std::cout	<< "original[1]: " << original[1] << "\n"
				 << "original[9]: " << original[9] << "\n"
				 << "original[-100]: " << original[-100] << "\n"
				 << "original[100]: " << original[100] << "\n";
	m.printTree();
}

void	iteratorsCheck() {
	printc("Iterators Check");

	ft::map<int, int, ft::less<int> >	m;
	std::map<int, int, std::less<int> >	orig;

	for (ft::map<int, int, ft::less<int> >::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << ":" << it->second << std::endl;
	for (std::map<int, int, std::less<int> >::iterator it = orig.begin(); it != orig.end(); ++it)
		std::cout << it->first << ":" << it->second << std::endl;

	m.insert(ft::make_pair(9,9));	orig.insert(std::make_pair(9,9));
	m.insert(ft::make_pair(8,8));	orig.insert(std::make_pair(8,8));
	m.insert(ft::make_pair(7,7));	orig.insert(std::make_pair(7,7));
	m.insert(ft::make_pair(6,6));	orig.insert(std::make_pair(6,6));
	m.insert(ft::make_pair(5,5));	orig.insert(std::make_pair(5,5));
	m.insert(ft::make_pair(4,4));	orig.insert(std::make_pair(4,4));
	m.insert(ft::make_pair(3,3));	orig.insert(std::make_pair(3,3));
	m.insert(ft::make_pair(2,2));	orig.insert(std::make_pair(2,2));
	m.insert(ft::make_pair(1,1));	orig.insert(std::make_pair(1,1));

	{
		printc("Normal iterator prefix increment");
		printc("ft::map");
		ft::map<int, int, ft::less<int> >::iterator it = m.begin();
		for (; it != m.end(); ++it)
			std::cout << it->first << ":" << it->second << "\t";
		std::cout << "\n";

		printc("std::map");
		std::map<int, int, std::less<int> >::iterator it_orig = orig.begin();
		for (; it_orig != orig.end(); ++it_orig)
			std::cout << it_orig->first << ":" << it_orig->second << "\t";
		std::cout << "\n";

		printc("Normal iterator prefix decrement");
		printc("ft::map");
		for (; it != --m.begin(); --it)
			std::cout << it->first << ":" << it->second << "\t";
		std::cout << "\n";

		printc("std::map");
		for (; it_orig != --orig.begin(); --it_orig)
			std::cout << it_orig->first << ":" << it_orig->second << "\t";
		std::cout << "\n";
	}

	LINE
	{
		printc("Normal iterator postfix increment");
		printc("ft::map");
		ft::map<int, int, ft::less<int> >::iterator it = m.begin();
		while (it != m.end())
			std::cout << it->first << ":" << (it++)->second << "\t";
		std::cout << "\n";

		printc("std::map");
		std::map<int, int, std::less<int> >::iterator it_orig = orig.begin();
		while (it_orig != orig.end())
			std::cout << it_orig->first << ":" << (it_orig++)->second << "\t";
		std::cout << "\n";

		printc("Normal iterator postfix decrement");
		printc("ft::map");
		while(it != --m.begin())
			std::cout << it->first << ":" << (it--)->second << "\t";
		std::cout << "\n";

		printc("std::map");
		while (it_orig != --orig.begin())
			std::cout << it_orig->first << ":" << (it_orig--)->second << "\t";
		std::cout << "\n";
	}
	LINE
	{
		printc("Reverse iterator check");
		printc("ft::map");
		ft::map<int, int, ft::less<int> >::reverse_iterator it = m.rbegin();
		for (; it != m.rend(); ++it)
			std::cout << it->first << ":" << it->second << std::endl;

		printc("std::map");
		std::map<int, int, std::less<int> >::reverse_iterator it_orig = orig.rbegin();
		for (; it_orig != orig.rend(); ++it_orig)
			std::cout << it_orig->first << ":" << it_orig->second << std::endl;

		printc("Reverse iterator decrement");
		printc("ft::map");
		for (; it != m.rbegin(); --it)
			std::cout << it->first << ":" << it->second << std::endl;

		printc("std::map");
		for (; it_orig != orig.rbegin(); --it_orig)
			std::cout << it_orig->first << ":" << it_orig->second << std::endl;
	}
	LINE
	{
		printc("const_iterator and normal_iterator comparison");
		ft::map<int, int, ft::less<int> >::iterator				it = m.begin();
		ft::map<int, int, ft::less<int> >::const_iterator		cit = m.begin();
		std::map<int, int, std::less<int> >::iterator			ite = orig.begin();
		std::map<int, int, std::less<int> >::const_iterator		cite = orig.begin();

		std::cout << "it == cit: " << (it == cit) << "\n";
		std::cout << "cit == it: " << (cit == it) << "\n";
		std::cout << "it != cit: " << (it != cit) << "\n";
		std::cout << "cit != it: " << (cit != it) << "\n\n";
		std::cout << "ite == cite: " << (ite == cite) << "\n";
		std::cout << "cite == ite: " << (cite == ite) << "\n";
		std::cout << "ite != cite: " << (ite != cite) << "\n";
		std::cout << "cite != ite: " << (cite != ite) << "\n\n";

		printc("after insert and ++it ---> it != cit");
		m.insert(ft::make_pair(1, 1));		orig.insert(std::make_pair(1, 1));
		m.insert(ft::make_pair(2, 1));		orig.insert(std::make_pair(2, 1));
		m.insert(ft::make_pair(3, 1));		orig.insert(std::make_pair(3, 1));

		++it; ++ite;
		std::cout << "it == cit: " << (it == cit) << "\n";
		std::cout << "cit == it: " << (cit == it) << "\n";
		std::cout << "it != cit: " << (it != cit) << "\n";
		std::cout << "cit != it: " << (cit != it) << "\n\n";
		std::cout << "ite == cite: " << (ite == cite) << "\n";
		std::cout << "cite == ite: " << (cite == ite) << "\n";
		std::cout << "ite != cite: " << (ite != cite) << "\n";
		std::cout << "cite != ite: " << (cite != ite) << "\n\n";

		printc("const_reverse_iterator and reverse_iterator comparison");
		ft::map<int, int, ft::less<int> >::reverse_iterator				r_it	= ++m.rbegin();
		ft::map<int, int, ft::less<int> >::const_reverse_iterator		cr_it	= ++++m.rbegin();
		std::map<int, int, std::less<int> >::reverse_iterator			r_ite	= ++orig.rbegin();
		std::map<int, int, std::less<int> >::const_reverse_iterator		cr_ite	= ++++orig.rbegin();

		std::cout << "r_it == cr_it: " << (r_it == cr_it) << "\n";
		std::cout << "cr_it == r_it: " << (cr_it == r_it) << "\n";
		std::cout << "r_it != cr_it: " << (r_it != cr_it) << "\n";
		std::cout << "cr_it != r_it: " << (cr_it != r_it) << "\n\n";
		std::cout << "r_ite == cr_ite: " << (r_ite == cr_ite) << "\n";
		std::cout << "cr_ite == r_ite: " << (cr_ite == r_ite) << "\n";
		std::cout << "r_ite != cr_ite: " << (r_ite != cr_ite) << "\n";
		std::cout << "cr_ite != r_ite: " << (cr_ite != r_ite) << "\n";
	}
}

void	capacityCheck() {
	printc("Capacity funcs check");

	ft::map<int, int, ft::less<int> >	m;
	std::map<int, int, std::less<int> >	orig;

	printc("Before insertion");
	std::cout	<< "m.empty(): " << m.empty() << "\n"
				<< "orig.empty(): " << orig.empty() << "\n";
	std::cout	<< "m.size(): " << m.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";
//	std::cout	<< "m.max_size(): " << m.max_size() << "\n"
//				 << "orig.max_size(): " << orig.max_size() << "\n";

	m.insert(ft::make_pair(9,9));	orig.insert(std::make_pair(9,9));
	m.insert(ft::make_pair(8,8));	orig.insert(std::make_pair(8,8));
	m.insert(ft::make_pair(7,7));	orig.insert(std::make_pair(7,7));
	m.insert(ft::make_pair(6,6));	orig.insert(std::make_pair(6,6));
	m.insert(ft::make_pair(5,5));	orig.insert(std::make_pair(5,5));

	printc("After insertion");
	std::cout	<< "m.empty(): " << m.empty() << "\n"
				 << "orig.empty(): " << orig.empty() << "\n";
	std::cout	<< "m.size(): " << m.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";
//	std::cout	<< "m.max_size(): " << m.max_size() << "\n"
//				 << "orig.max_size(): " << orig.max_size() << "\n";
	LINE

	printc("After clear()");
	m.clear();
	orig.clear();
	std::cout	<< "m.empty(): " << m.empty() << "\n"
				 << "orig.empty(): " << orig.empty() << "\n";
	std::cout	<< "m.size(): " << m.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";


//	printc("Iterators comparision");

}

void	modifiersCheck() {
	ft::map<int, int, ft::less<int> >	m;
	std::map<int, int, std::less<int> >	orig;

	ft::pair<ft::map<int, int, ft::less<int> >::iterator, bool>		m_ret;
	std::pair<std::map<int, int, std::less<int> >::iterator, bool>	o_ret;

	m_ret = m.insert(ft::make_pair(9,9));	o_ret = orig.insert(std::make_pair(9,9));
	m.insert(ft::make_pair(8,8));	orig.insert(std::make_pair(8,8));
	m.insert(ft::make_pair(7,7));	orig.insert(std::make_pair(7,7));
	m.insert(ft::make_pair(6,6));	orig.insert(std::make_pair(6,6));
	m.insert(ft::make_pair(5,5));	orig.insert(std::make_pair(5,5));

	printc("Insert by value");
	print("Insertion of non existing element");
	std::cout << m_ret.first->first << ":" << m_ret.first->second << " --> " << m_ret.second << std::endl;
	std::cout << o_ret.first->first << ":" << o_ret.first->second << " --> " << o_ret.second << std::endl;
	m.printTreeInOrder();
	print("Insertion of an existing element");
	m_ret = m.insert(ft::make_pair(9,9));	o_ret = orig.insert(std::make_pair(9,9));
	std::cout << m_ret.first->first << ":" << m_ret.first->second << " --> " << m_ret.second << std::endl;
	std::cout << o_ret.first->first << ":" << o_ret.first->second << " --> " << o_ret.second << std::endl;

	LINE
	printc("Insert by range");
	ft::map<int, int, ft::less<int> >	n;
	n.insert(m.begin(), m.end());
	printc("After n.insert(m.begin(), m.end()): ");
	n.printTreeInOrder();
	std::cout << "m == n: " << (m == n) << std::endl;

	LINE
	printc("Erase by range");
	ft::map<int, int, ft::less<int> >::iterator		it = ++n.begin();
	ft::map<int, int, ft::less<int> >::iterator		ite = --n.end();

	std::cout << "n.begin(): " << it->first << "\tn.end(): " << ite->first << std::endl;
	n.printTree();
	n.erase(it, ite);
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;

	LINE
	printc("Erase by pos");
	n.erase(n.begin());
	print("After n.erase(n.begin()):");
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;

	LINE
	printc("Erase by key");
	n.erase(9);
	print("After n.erase(9):");
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;

	LINE
	ft::map<int, int, ft::less<int> >	my1;
	ft::map<int, int, ft::less<int> >	my2;
	std::map<int, int, std::less<int> >	orig1;
	std::map<int, int, std::less<int> >	orig2;

	my1.insert(ft::make_pair(8,8));	orig1.insert(std::make_pair(8,8));
	my1.insert(ft::make_pair(7,7));	orig1.insert(std::make_pair(7,7));
	my1.insert(ft::make_pair(6,6));	orig1.insert(std::make_pair(6,6));
	my1.insert(ft::make_pair(5,5));	orig1.insert(std::make_pair(5,5));

	my2.insert(ft::make_pair(108,8));	orig2.insert(std::make_pair(108,8));
	my2.insert(ft::make_pair(107,7));	orig2.insert(std::make_pair(107,7));
	my2.insert(ft::make_pair(106,6));	orig2.insert(std::make_pair(106,6));
	my2.insert(ft::make_pair(105,5));	orig2.insert(std::make_pair(105,5));

	ft::map<int, int, ft::less<int> >::iterator		it1 = my1.begin();
	std::map<int, int, std::less<int> >::iterator	ite1 = orig1.begin();

	printc("my1:");
	my1.printTreeInOrder();
	printc("my2:");
	my2.printTreeInOrder();

	my1.swap(my2);
	orig1.swap(orig2);

	printc("After swap()");
	print("my1:");
	my1.printTreeInOrder();
	print("my2:");
	my2.printTreeInOrder();
	print("orig1:");
	for (std::map<int, int, std::less<int> >::iterator i = orig1.begin(); i != orig1.end(); ++i)
		std::cout << i->first << " ";
	std::cout << "\n";
	print("orig2:");
	for (std::map<int, int, std::less<int> >::iterator i = orig2.begin(); i != orig2.end(); ++i)
		std::cout << i->first << " ";
	std::cout << "\n";

	LINE
	printc("Iterators check");
	std::cout << it1->first << " " << (++it1)->first << std::endl;
	std::cout << ite1->first << " " << (++ite1)->first << std::endl;
}


void	lookupCheck() {
	ft::map<int, int, ft::less<int> >	m;

	m.insert(ft::make_pair(9,9));
	m.insert(ft::make_pair(7,8));
	m.insert(ft::make_pair(5,7));
	m.insert(ft::make_pair(3,6));
	m.insert(ft::make_pair(1,5));

	m.printTreeInOrder();

	printc("count() test");
	std::cout << "m.count(9): " << m.count(9) << std::endl;
	std::cout << "m.count(7): " << m.count(7) << std::endl;
	std::cout << "m.count(5): " << m.count(5) << std::endl;
	std::cout << "m.count(-100): " << m.count(-100) << std::endl;
	std::cout << "m.count(0): " << m.count(0) << std::endl;
	std::cout << "m.count(100): " << m.count(100) << std::endl;

	LINE

	printc("find() test");
	std::cout << "m.find(9): " << m.find(9)->first << std::endl;
	std::cout << "m.find(7): " << m.find(7)->first << std::endl;
	std::cout << "m.find(5): " << m.find(5)->first << std::endl;
	std::cout << "m.find(-100): " << m.find(-100)->first << ";\tm.find(-100) == m.end(): " << (m.find(-100) == m.end()) << std::endl;
	std::cout << "m.find(0): " << m.find(0)->first << ";\t\tm.find(0) == m.end(): " << (m.find(0) == m.end()) << std::endl;
	std::cout << "m.find(100): " << m.find(100)->first << ";\t\tm.find(100) == m.end(): " << (m.find(100) == m.end()) << std::endl;

	LINE

	printc("lower_bound() test");
	std::cout << "m.lower_bound(9): " << m.lower_bound(9)->first << std::endl;
	std::cout << "m.lower_bound(7): " << m.lower_bound(7)->first << std::endl;
	std::cout << "m.lower_bound(6): " << m.lower_bound(6)->first << std::endl;
	std::cout << "m.lower_bound(5): " << m.lower_bound(5)->first << std::endl;
	std::cout << "m.lower_bound(-100): " << m.lower_bound(-100)->first << std::endl;
	std::cout << "m.lower_bound(0): " << m.lower_bound(0)->first << std::endl;
	std::cout << "m.lower_bound(100): " << m.lower_bound(100)->first << ";\tm.lower_bound(100) == m.end(): " << (m.lower_bound(100) == m.end()) << std::endl;

	LINE

	printc("upper_bound() test");
	std::cout << "m.upper_bound(9): " << m.upper_bound(9)->first << ";\tm.upper_bound(9) == m.end(): " << (m.upper_bound(9) == m.end()) << std::endl;
	std::cout << "m.upper_bound(7): " << m.upper_bound(7)->first << std::endl;
	std::cout << "m.upper_bound(6): " << m.upper_bound(6)->first << std::endl;
	std::cout << "m.upper_bound(5): " << m.upper_bound(5)->first << std::endl;
	std::cout << "m.upper_bound(-100): " << m.upper_bound(-100)->first << std::endl;
	std::cout << "m.upper_bound(0): " << m.upper_bound(0)->first << std::endl;
	std::cout << "m.upper_bound(100): " << m.upper_bound(100)->first << ";\tm.upper_bound(100) == m.end(): " << (m.upper_bound(100) == m.end()) << std::endl;

	LINE

	printc("equal_range() test");
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> res = m.equal_range(-100);
	std::cout << "m.equal_range(-100): [" << res.first->first << ", " << res.second->first << "]" << std::endl;
	res = m.equal_range(1);
	std::cout << "m.equal_range(1): [" << res.first->first << ", " << res.second->first << "]" << std::endl;
	res = m.equal_range(6);
	std::cout << "m.equal_range(6): [" << res.first->first << ", " << res.second->first << "]" << std::endl;
	res = m.equal_range(9);
	std::cout << "m.equal_range(9): [" << res.first->first << ", " << res.second->first << "]\tres.second == m.end(): " << (res.second == m.end()) << std::endl;
	res = m.equal_range(100);
	std::cout << "m.equal_range(100): [" << res.first->first << ", " << res.second->first << "]\tres.second == m.end(): " << (res.second == m.end()) << std::endl;
}


void	compareFuncsCheck() {
	ft::map<int, int, ft::less<int> >	m;

	printc("key_comp() test");
	print("key_comp() == ft::less<int>");
	std::cout << "m.key_comp()(1, 3): " << m.key_comp()(1, 3) << std::endl;
	std::cout << "m.key_comp()(5, 5): " << m.key_comp()(5, 5) << std::endl;
	std::cout << "m.key_comp()(100, 5): " << m.key_comp()(100, 5) << std::endl;
	LINE
	print("key_comp() == ft::more<int>");
	ft::map<int, int, ft::more<int> >	n;
	std::cout << "n.key_comp()(1, 3): " << n.key_comp()(1, 3) << std::endl;
	std::cout << "n.key_comp()(5, 5): " << n.key_comp()(5, 5) << std::endl;
	std::cout << "n.key_comp()(100, 5): " << n.key_comp()(100, 5) << std::endl;
	LINE
	printc("value_comp() test");
	print("key_comp() == ft::less<int>");
	std::cout << "m.value_comp()({1,2}, {10,2}): " << m.value_comp()(ft::make_pair(1,2), ft::make_pair(10,2)) << std::endl;
	std::cout << "m.value_comp()({5,10}, {5,2}): " << m.value_comp()(ft::make_pair(5,10), ft::make_pair(5,2)) << std::endl;
	std::cout << "m.value_comp()({100,2}, {50,2}): " << m.value_comp()(ft::make_pair(100,2), ft::make_pair(50,2)) << std::endl;
	LINE
	print("key_comp() == ft::more<int>");
	std::cout << "n.value_comp()({1,2}, {10,2}): " << n.value_comp()(ft::make_pair(1,2), ft::make_pair(10,2)) << std::endl;
	std::cout << "n.value_comp()({5,10}, {5,2}): " << n.value_comp()(ft::make_pair(5,10), ft::make_pair(5,2)) << std::endl;
	std::cout << "n.value_comp()({100,2}, {50,2}): " << n.value_comp()(ft::make_pair(100,2), ft::make_pair(50,2)) << std::endl;

}

void	iteratorsResistanceCheck() {
	ft::map<int, int, ft::less<int> >	m;
	std::map<int, int, std::less<int> >	orig;

	m.insert(ft::make_pair(9,9));
	m.insert(ft::make_pair(7,8));
	m.insert(ft::make_pair(5,7));
	m.insert(ft::make_pair(3,6));
	m.insert(ft::make_pair(1,5));

	orig.insert(std::make_pair(9,9));
	orig.insert(std::make_pair(7,8));
	orig.insert(std::make_pair(5,7));
	orig.insert(std::make_pair(3,6));
	orig.insert(std::make_pair(1,5));

	ft::map<int, int, ft::less<int> >::iterator		it_m = m.find(5);
	std::map<int, int, std::less<int> >::iterator	it_orig = orig.find(5);

	print(it_m->first);
	print(it_orig->first);

	m.erase(m.begin());
	orig.erase(orig.begin());
	m.insert(ft::make_pair(20, 20));
	orig.insert(std::make_pair(20, 20));

	print(it_m->first);
	print(it_orig->first);
}

void	comparisonCheck() {
	ft::map<int, int, ft::less<int> >	m1;
	ft::map<int, int, ft::less<int> >	m2;
	std::map<int, int, std::less<int> >	orig1;
	std::map<int, int, std::less<int> >	orig2;

	printc("Empty maps");
	std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
	std::cout << "m1 != m2: " << (m1 != m2) << std::endl;
	std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;
	std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;

	orig1.insert(std::make_pair(9,9));	m1.insert(ft::make_pair(9,9));
	orig1.insert(std::make_pair(7,8));	m1.insert(ft::make_pair(7,9));
	orig1.insert(std::make_pair(5,7));	m1.insert(ft::make_pair(5,9));
	orig1.insert(std::make_pair(3,6));	m1.insert(ft::make_pair(3,9));
	orig1.insert(std::make_pair(1,5));	m1.insert(ft::make_pair(1,9));

	LINE
	printc("m2, orig2 empty");
	std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
	std::cout << "m1 != m2: " << (m1 != m2) << std::endl;
	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;

	LINE
	printc("m2, orig2 empty");
	std::cout << "m1 < m2: " << (m1 < m2) << std::endl;
	std::cout << "m2 < m1: " << (m2 < m1) << std::endl;
	std::cout << "m1 > m2: " << (m1 > m2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig2 < orig1: " << (orig2 < orig1) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;

	LINE
	orig2.insert(std::make_pair(19,9));	m2.insert(ft::make_pair(19,9));
	orig2.insert(std::make_pair(17,8));	m2.insert(ft::make_pair(17,9));
	orig2.insert(std::make_pair(15,7));	m2.insert(ft::make_pair(15,9));
	orig2.insert(std::make_pair(13,6));	m2.insert(ft::make_pair(13,9));
	orig2.insert(std::make_pair(11,5));	m2.insert(ft::make_pair(11,9));

	printc("m2, orig2 keys bigger");
	std::cout << "m1 < m2: " << (m1 < m2) << std::endl;
	std::cout << "m2 < m1: " << (m2 < m1) << std::endl;
	std::cout << "m1 > m2: " << (m1 > m2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig2 < orig1: " << (orig2 < orig1) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;

	LINE
	m2.clear(); orig2.clear();
	orig2.insert(std::make_pair(9,9));	m2.insert(ft::make_pair(9,9));
	orig2.insert(std::make_pair(7,8));	m2.insert(ft::make_pair(7,9));
	orig2.insert(std::make_pair(5,7));	m2.insert(ft::make_pair(5,9));
	orig2.insert(std::make_pair(3,6));	m2.insert(ft::make_pair(3,9));
	orig2.insert(std::make_pair(1,5));	m2.insert(ft::make_pair(1,9));

	printc("equal");
	std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;
	std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;

	orig2.insert(std::make_pair(11,5));	m2.insert(ft::make_pair(11,9));

	LINE
	printc("*2 bigger");
	std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;
	std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;
}

int main() {
	std::cout << std::boolalpha;

	constructorsCheck();
	elementAccessCheck();
	iteratorsCheck();
	capacityCheck();
	modifiersCheck();
	lookupCheck();
	compareFuncsCheck();
	iteratorsResistanceCheck();
	comparisonCheck();

}
