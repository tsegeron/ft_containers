# include "../hdrs/containers/set.hpp"
# include <set>

# define BLUE		"\033[34m"
# define RESET		"\033[0m"

# define printc(msg) std::cout << BLUE << msg << RESET << std::endl
# define print(msg) std::cout << msg << std::endl
# define LINE		printc("------------------------------------------------");

void	constructorsCheck() {
	/* проверка стандартного конструктора */
	{
		printc("empty set");
		ft::set<std::string, ft::less<std::string> >	m;

		std::cout	<< "m.size(): " << m.size() << "\n"
					<< "m.height(): " << m.height(true) << "\n";
		m.printTree();
	}
	LINE
	{
		ft::more<std::string>	more;
		ft::set<std::string, ft::more<std::string> >	m(more);

		std::cout	<< "m.size(): " << m.size() << "\n"
					<< "m.height(): " << m.height(true) << "\n";
		m.printTree();
	}
	LINE
	{
//		ft::set<std::string, int, ft::less<std::string> >	one;
		ft::set<std::string, ft::more<std::string> >	one;
		std::cout	<< "one.size(): " << one.size() << "\n"
					<< "one.height(): " << one.height(true) << "\n";
		printc("set: 'one'");
		one.insert("abc");
		one.insert("bcd");
		one.insert("cde");
		one.insert("def");
		one.insert("efg");
		one.insert("fgh");
		one.insert("ghi");
		std::cout	<< "one.size(): " << one.size() << "\n"
					<< "one.height(): " << one.height(true) << "\n";
		one.printTree();

		LINE

		/* container copy, assignment test */
		ft::set<std::string, ft::more<std::string> >	two(one);
		ft::set<std::string, ft::more<std::string> >	three = two;
		printc("after 'two(one)' and 'one.erase(\"def\")'");
		print("set: 'two'");
		one.erase("def");
		std::cout	<< "two.size(): " << two.size() << "\n"
					<< "two.height(): " << two.height(true) << "\n";
		two.printTree();

		LINE

		printc("after 'three = two'");
		print("set: 'three'");
		std::cout	<< "three.size(): " << three.size() << "\n"
					<< "three.height(): " << three.height(true) << "\n";
		three.printTree();

		LINE

		/* iterator copy, assignment test */
		two.printTreeInOrder();
		ft::set<std::string, ft::more<std::string> >::iterator	it1(two.begin());
		ft::set<std::string, ft::more<std::string> >::iterator	it2 = two.begin();
		std::cout	<< "it1(two.begin()) --> it1: " << *it1 << "\n"
					<< "it2 = two.begin() ---> it2: " << *it1 << "\n";

		LINE

		/* container's constructor by iterators test */
		printc("constructor by iterators test");

		two.printTreeInOrder();
		++it1;
		it2 = ----two.end();
		std::cout	<< "(++it1): " << *it1 << "; "
					<< "(----it2): " << *it2 << std::endl;
		ft::set<std::string, ft::more<std::string> >	four(it1, it2);
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
		ft::set<std::string, ft::more<std::string> >	five;
		five = four;
		printc("After five = four:");
		std::cout	<< "five.size(): " << five.size() << "\n"
					<< "five.height(): " << five.height(true) << "\n";
		five.printTree();
		five.printTreeInOrder();

		LINE

	}

}

void	iteratorsCheck() {
	printc("Iterators Check");

	ft::set<int, ft::less<int> >	m;
	std::set<int, std::less<int> >	orig;

	for (ft::set<int, ft::less<int> >::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << *it << std::endl;
	for (std::set<int, std::less<int> >::iterator it = orig.begin(); it != orig.end(); ++it)
		std::cout << *it << std::endl;

	m.insert(9);	orig.insert(9);
	m.insert(8);	orig.insert(8);
	m.insert(7);	orig.insert(7);
	m.insert(6);	orig.insert(6);
	m.insert(5);	orig.insert(5);
	m.insert(4);	orig.insert(4);
	m.insert(3);	orig.insert(3);
	m.insert(2);	orig.insert(2);
	m.insert(1);	orig.insert(1);

	{
		printc("Normal iterator prefix increment");
		printc("ft::set");
		ft::set<int, ft::less<int> >::iterator it = m.begin();
		for (; it != m.end(); ++it)
			std::cout << *it << "\t";
		std::cout << "\n";

		printc("std::set");
		std::set<int, std::less<int> >::iterator it_orig = orig.begin();
		for (; it_orig != orig.end(); ++it_orig)
			std::cout << *it_orig << "\t";
		std::cout << "\n";

		printc("Normal iterator prefix decrement");
		printc("ft::set");
		for (; it != --m.begin(); --it)
			std::cout << *it << "\t";
		std::cout << "\n";

		printc("std::set");
		for (; it_orig != --orig.begin(); --it_orig)
			std::cout << *it_orig << "\t";
		std::cout << "\n";
	}

	LINE
	{
		printc("Normal iterator postfix increment");
		printc("ft::set");
		ft::set<int, ft::less<int> >::iterator it = m.begin();
		while (it != m.end())
			std::cout << *it++ << "\t";
		std::cout << "\n";

		printc("std::set");
		std::set<int, std::less<int> >::iterator it_orig = orig.begin();
		while (it_orig != orig.end())
			std::cout << *it_orig++ << "\t";
		std::cout << "\n";

		printc("Normal iterator postfix decrement");
		printc("ft::set");
		while(it != --m.begin())
			std::cout << *it-- << "\t";
		std::cout << "\n";

		printc("std::set");
		while (it_orig != --orig.begin())
			std::cout << *it_orig-- << "\t";
		std::cout << "\n";
	}
	LINE
	{
		printc("Reverse iterator check");
		printc("ft::set");
		ft::set<int, ft::less<int> >::reverse_iterator it = m.rbegin();
		for (; it != m.rend(); ++it)
			std::cout << *it << std::endl;

		printc("std::set");
		std::set<int, std::less<int> >::reverse_iterator it_orig = orig.rbegin();
		for (; it_orig != orig.rend(); ++it_orig)
			std::cout << *it_orig << std::endl;

		printc("Reverse iterator decrement");
		printc("ft::set");
		for (; it != m.rbegin(); --it)
			std::cout << *it << std::endl;

		printc("std::set");
		for (; it_orig != orig.rbegin(); --it_orig)
			std::cout << *it_orig << std::endl;
	}
	LINE
}

void	capacityCheck() {
	printc("Capacity funcs check");

	ft::set<int, ft::less<int> >	m;
	std::set<int, std::less<int> >	orig;

	printc("Before insertion");
	std::cout	<< "m.empty(): " << m.empty() << "\n"
				<< "orig.empty(): " << orig.empty() << "\n";
	std::cout	<< "m.size(): " << m.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";
//	std::cout	<< "m.max_size(): " << m.max_size() << "\n"
//				 << "orig.max_size(): " << orig.max_size() << "\n";

	m.insert(9);	orig.insert(9);
	m.insert(8);	orig.insert(8);
	m.insert(7);	orig.insert(7);
	m.insert(6);	orig.insert(6);
	m.insert(5);	orig.insert(5);

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
	ft::set<int, ft::less<int> >	m;
	std::set<int, std::less<int> >	orig;

	ft::pair<ft::set<int, ft::less<int> >::iterator, bool>		m_ret;
	std::pair<std::set<int, std::less<int> >::iterator, bool>	o_ret;

	m_ret = m.insert(9);	o_ret = orig.insert(9);
	m.insert(8);	orig.insert(8);
	m.insert(7);	orig.insert(7);
	m.insert(6);	orig.insert(6);
	m.insert(5);	orig.insert(5);

	printc("Insert by value");
	print("Insertion of non existing element");
	std::cout << *(m_ret.first) << " --> " << m_ret.second << std::endl;
	std::cout << *(o_ret.first) << " --> " << o_ret.second << std::endl;
	m.printTreeInOrder();
	print("Insertion of an existing element");
	m_ret = m.insert(9);	o_ret = orig.insert(9);
	std::cout << *(m_ret.first) << " --> " << m_ret.second << std::endl;
	std::cout << *(o_ret.first) << " --> " << o_ret.second << std::endl;

	printc("Insert by range");
	ft::set<int, ft::less<int> >	n;
	n.insert(m.begin(), m.end());
	printc("After n.insert(m.begin(), m.end()): ");
	n.printTreeInOrder();
	std::cout << "m == n: " << (m == n) << std::endl;

	printc("Erase by range");
	ft::set<int, ft::less<int> >::iterator		it = ++n.begin();
	ft::set<int, ft::less<int> >::iterator		ite = --n.end();

	std::cout << "n.begin(): " << *it << "\tn.end(): " << *ite << std::endl;
	n.printTree();
	n.erase(it, ite);
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;

	printc("Erase by pos");
	n.erase(n.begin());
	print("After n.erase(n.begin()):");
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;

	printc("Erase by key");
	n.erase(9);
	print("After n.erase(9):");
	n.printTreeInOrder();
	std::cout << "n.size(): " << n.size() << std::endl;
}


void	lookupCheck() {
	ft::set<int, ft::less<int> >	m;

	m.insert(9);
	m.insert(7);
	m.insert(5);
	m.insert(3);
	m.insert(1);

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
	std::cout << "m.find(9): " << *m.find(9) << std::endl;
	std::cout << "m.find(7): " << *m.find(7) << std::endl;
	std::cout << "m.find(5): " << *m.find(5) << std::endl;
	std::cout << "m.find(-100): " << *m.find(-100) << ";\tm.find(-100) == m.end(): " << (m.find(-100) == m.end()) << std::endl;
	std::cout << "m.find(0): " << *m.find(0) << ";\t\tm.find(0) == m.end(): " << (m.find(0) == m.end()) << std::endl;
	std::cout << "m.find(100): " << *m.find(100) << ";\t\tm.find(100) == m.end(): " << (m.find(100) == m.end()) << std::endl;

	LINE

	printc("lower_bound() test");
	std::cout << "m.lower_bound(9): " << *m.lower_bound(9) << std::endl;
	std::cout << "m.lower_bound(7): " << *m.lower_bound(7) << std::endl;
	std::cout << "m.lower_bound(6): " << *m.lower_bound(6) << std::endl;
	std::cout << "m.lower_bound(5): " << *m.lower_bound(5) << std::endl;
	std::cout << "m.lower_bound(-100): " << *m.lower_bound(-100) << std::endl;
	std::cout << "m.lower_bound(0): " << *m.lower_bound(0) << std::endl;
	std::cout << "m.lower_bound(100): " << *m.lower_bound(100) << ";\tm.lower_bound(100) == m.end(): " << (m.lower_bound(100) == m.end()) << std::endl;

	LINE

	printc("upper_bound() test");
	std::cout << "m.upper_bound(9): " << *m.upper_bound(9) << ";\tm.upper_bound(9) == m.end(): " << (m.upper_bound(9) == m.end()) << std::endl;
	std::cout << "m.upper_bound(7): " << *m.upper_bound(7) << std::endl;
	std::cout << "m.upper_bound(6): " << *m.upper_bound(6) << std::endl;
	std::cout << "m.upper_bound(5): " << *m.upper_bound(5) << std::endl;
	std::cout << "m.upper_bound(-100): " << *m.upper_bound(-100) << std::endl;
	std::cout << "m.upper_bound(0): " << *m.upper_bound(0) << std::endl;
	std::cout << "m.upper_bound(100): " << *m.upper_bound(100) << ";\tm.upper_bound(100) == m.end(): " << (m.upper_bound(100) == m.end()) << std::endl;

	LINE

	printc("equal_range() test");
	ft::pair<ft::set<int, int>::iterator, ft::set<int, int>::iterator> res = m.equal_range(-100);
	std::cout << "m.equal_range(-100): [" << *res.first << ", " << *res.second << "]" << std::endl;
	res = m.equal_range(1);
	std::cout << "m.equal_range(1): [" << *res.first << ", " << *res.second << "]" << std::endl;
	res = m.equal_range(6);
	std::cout << "m.equal_range(6): [" << *res.first << ", " << *res.second << "]" << std::endl;
	res = m.equal_range(9);
	std::cout << "m.equal_range(9): [" << *res.first << ", " << *res.second << "]\tres.second == m.end(): " << (res.second == m.end()) << std::endl;
	res = m.equal_range(100);
	std::cout << "m.equal_range(100): [" << *res.first << ", " << *res.second << "]\tres.second == m.end(): " << (res.second == m.end()) << std::endl;
}


void	compareFuncsCheck() {
	ft::set<int, ft::less<int> >	m;

	printc("key_comp() test");
	print("key_comp() == ft::less<int>");
	std::cout << "m.key_comp()(1, 3): " << m.key_comp()(1, 3) << std::endl;
	std::cout << "m.key_comp()(5, 5): " << m.key_comp()(5, 5) << std::endl;
	std::cout << "m.key_comp()(100, 5): " << m.key_comp()(100, 5) << std::endl;
	LINE
	print("key_comp() == ft::more<int>");
	ft::set<int, ft::more<int> >	n;
	std::cout << "n.key_comp()(1, 3): " << n.key_comp()(1, 3) << std::endl;
	std::cout << "n.key_comp()(5, 5): " << n.key_comp()(5, 5) << std::endl;
	std::cout << "n.key_comp()(100, 5): " << n.key_comp()(100, 5) << std::endl;
	LINE
	printc("value_comp() test");
	print("key_comp() == ft::less<int>");
	std::cout << "m.value_comp()(1, 10): " << m.value_comp()(1, 10) << std::endl;
	std::cout << "m.value_comp()(5, 5): " << m.value_comp()(5, 5) << std::endl;
	std::cout << "m.value_comp()(100, 50): " << m.value_comp()(100, 50) << std::endl;
	LINE
	print("key_comp() == ft::more<int>");
	std::cout << "m.value_comp()(1, 10): " << n.value_comp()(1, 10) << std::endl;
	std::cout << "m.value_comp()(5, 5): " << n.value_comp()(5, 5) << std::endl;
	std::cout << "m.value_comp()(100, 50): " << n.value_comp()(100, 50) << std::endl;
}

void	iteratorsResistanceCheck() {
	ft::set<int, ft::less<int> >	m;
	std::set<int, std::less<int> >	orig;

	m.insert(9);
	m.insert(7);
	m.insert(5);
	m.insert(3);
	m.insert(1);

	orig.insert(9);
	orig.insert(7);
	orig.insert(5);
	orig.insert(3);
	orig.insert(1);

	ft::set<int, ft::less<int> >::iterator		it_m = m.find(5);
	std::set<int, std::less<int> >::iterator	it_orig = orig.find(5);

	print(*it_m);
	print(*it_orig);

	m.erase(m.begin());
	orig.erase(orig.begin());
	m.insert( 20);
	orig.insert(20);

	print(*it_m);
	print(*it_orig);
}

void	comparisonCheck() {
	ft::set<int, ft::less<int> >	m1;
	ft::set<int, ft::less<int> >	m2;
	std::set<int, std::less<int> >	orig1;
	std::set<int, std::less<int> >	orig2;

	printc("Empty maps");
	std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
	std::cout << "m1 != m2: " << (m1 != m2) << std::endl;
	std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;
	std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;

	orig1.insert(9);	m1.insert(9);
	orig1.insert(7);	m1.insert(7);
	orig1.insert(5);	m1.insert(5);
	orig1.insert(3);	m1.insert(3);
	orig1.insert(1);	m1.insert(1);

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
	orig2.insert(19);	m2.insert(19);
	orig2.insert(17);	m2.insert(17);
	orig2.insert(15);	m2.insert(15);
	orig2.insert(13);	m2.insert(13);
	orig2.insert(11);	m2.insert(11);

	printc("m2, orig2 keys bigger");
	std::cout << "m1 < m2: " << (m1 < m2) << std::endl;
	std::cout << "m2 < m1: " << (m2 < m1) << std::endl;
	std::cout << "m1 > m2: " << (m1 > m2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig2 < orig1: " << (orig2 < orig1) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;

	LINE
	m2.clear(); orig2.clear();
	orig2.insert(9);	m2.insert(9);
	orig2.insert(7);	m2.insert(7);
	orig2.insert(5);	m2.insert(5);
	orig2.insert(3);	m2.insert(3);
	orig2.insert(1);	m2.insert(1);

	printc("equal");
	std::cout << "m1 >= m2: " << (m1 >= m2) << std::endl;
	std::cout << "m1 <= m2: " << (m1 <= m2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;

	orig2.insert(11);	m2.insert(11);

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
	iteratorsCheck();
	capacityCheck();
	modifiersCheck();
	lookupCheck();
	compareFuncsCheck();
	iteratorsResistanceCheck();
	comparisonCheck();

}
