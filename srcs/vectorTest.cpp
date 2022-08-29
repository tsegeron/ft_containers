# include "../hdrs/containers/vector.hpp"
# include <vector>
# include <iostream>

# define BLUE		"\033[34m"
# define RESET		"\033[0m"

# define printc(msg) std::cout << BLUE << msg << RESET << std::endl;
# define print(msg) std::cout << msg << std::endl;
# define LINE		printc("------------------------------------------------");

template<class Vec>
void	printVec(const Vec& v) {
	for (typename Vec::size_type i = 0; i != v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

void	memberFunctionsCheck() {
	{
		printc("empty vector")
		ft::vector<std::string>		vec;
		std::vector<std::string>	orig;

		std::cout	<< "vec.empty(): " << vec.empty() << "\n"
					<< "vec.size(): " << vec.size() << "\n"
					<< "vec.capacity(): " << vec.capacity() << "\n\n";
		std::cout	<< "orig.empty(): " << orig.empty() << "\n"
					<< "orig.size(): " << orig.size() << "\n"
					<< "orig.capacity(): " << orig.capacity() << "\n";
	}
	LINE
	{
		printc("vector with quantity and no value")
		ft::vector<std::string>		vec(100);
		std::vector<std::string>	orig(100);

		std::cout	<< "vec.empty(): " << vec.empty() << "\n"
					<< "vec[0]: " << vec[0] << "\n"
					<< "vec.size(): " << vec.size() << "\n"
					<< "vec.capacity(): " << vec.capacity() << "\n\n";
		std::cout	<< "orig.empty(): " << orig.empty() << "\n"
					<< "orig[0]: " << orig[0] << "\n"
					<< "orig.size(): " << orig.size() << "\n"
					<< "orig.capacity(): " << orig.capacity() << "\n";
	}
	LINE
	{
		printc("vector with quantity and default value")
		ft::vector<std::string>		vec(20, "hello");
		std::vector<std::string>	orig(20, "hello");

		std::cout	<< "vec.size(): " << vec.size() << "\n"
					<< "vec.capacity(): " << vec.capacity() << "\n\n";
		std::cout	<< "orig.size(): " << orig.size() << "\n"
					<< "orig.capacity(): " << orig.capacity() << "\n";

		printVec(vec);
		printVec(orig);


		LINE
		printc("range based constructor")
		ft::vector<std::string>		vec2(++++vec.begin(), ----vec.end());
		std::vector<std::string>	orig2(++++orig.begin(), ----orig.end());
		std::cout	<< "vec.size(): " << vec2.size() << "\n"
					<< "vec.capacity(): " << vec2.capacity() << "\n\n";
		std::cout	<< "orig.size(): " << orig2.size() << "\n"
					<< "orig.capacity(): " << orig2.capacity() << "\n";

		LINE
		printc("copy constructor")
		ft::vector<std::string>		vec3(vec2);
		std::vector<std::string>	orig3(orig2);
		std::cout	<< "vec.size(): " << vec3.size() << "\n"
					 << "vec.capacity(): " << vec3.capacity() << "\n\n";
		std::cout	<< "orig.size(): " << orig3.size() << "\n"
					 << "orig.capacity(): " << orig3.capacity() << "\n";
		printVec(vec3);
		printVec(orig3);

	}
	{
		LINE
		printc("copy constructor")
		ft::vector<int>		copy;
		ft::vector<int>		vec(5, 1);
		std::vector<int>	copy_orig;
		std::vector<int>	orig(5, 1);
		std::cout	<< "copy.size(): " << copy.size() << "\n"
					 << "copy.capacity(): " << copy.capacity() << "\n";
		std::cout	<< "copy_orig.size(): " << copy_orig.size() << "\n"
					 << "copy_orig.capacity(): " << copy_orig.capacity() << "\n\n";
		std::cout	<< "vec.size(): " << vec.size() << "\n"
					 << "vec.capacity(): " << vec.capacity() << "\n";
		std::cout	<< "orig.size(): " << orig.size() << "\n"
					 << "orig.capacity(): " << orig.capacity() << "\n";

		printc("After copy = vec, copy_orig = orig:")
		copy = vec;
		copy_orig = orig;
		std::cout	<< "copy.size(): " << copy.size() << "\n"
					 << "copy.capacity(): " << copy.capacity() << "\n";
		std::cout	<< "copy_orig.size(): " << copy_orig.size() << "\n"
					 << "copy_orig.capacity(): " << copy_orig.capacity() << "\n";

		LINE
		printc("assign(count, value) test")
		copy.assign(2, 3);
		copy_orig.assign(2, 3);
		for (ft::vector<int>::iterator i = copy.begin(); i != copy.end(); ++i)
			std::cout << *i << " ";
		std::cout << "\n";
		for (std::vector<int>::iterator i = copy_orig.begin(); i != copy_orig.end(); ++i)
			std::cout << *i << " ";
		std::cout << "\n";

		LINE
		printc("assign(iterator, iterator) test")
		copy.assign(++vec.begin(), --vec.end());
		copy_orig.assign(++orig.begin(), --orig.end());
		for (ft::vector<int>::iterator i = copy.begin(); i != copy.end(); ++i)
			std::cout << *i << " ";
		std::cout << "\n";
		for (std::vector<int>::iterator i = copy_orig.begin(); i != copy_orig.end(); ++i)
			std::cout << *i << " ";
		std::cout << "\n";
	}

}

void	iteratorsCheck() {
	ft::vector<std::string>		vec;
	std::vector<std::string>	orig;

	vec.push_back("one");		orig.push_back("one");
	vec.push_back("two");		orig.push_back("two"); // what
	vec.push_back("three");	orig.push_back("three");
	vec.push_back("four");	orig.push_back("four");
	vec.push_back("five");	orig.push_back("five");
	vec.push_back("six");		orig.push_back("six");
	vec.push_back("seven");	orig.push_back("seven");
	vec.push_back("eight");	orig.push_back("eight");
	vec.push_back("nine");	orig.push_back("nine");

	ft::vector<std::string>::iterator	it = vec.begin();
	std::vector<std::string>::iterator	ite = orig.begin();

	printc("prefix iterator increment") // just to show that works
	for (; it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	for (; ite != orig.end(); ++ite)
		std::cout << *ite << " ";
	std::cout << "\n\n";

	printc("prefix iterator decrement")
	for (; it != vec.begin(); --it)
		std::cout << *it << " ";
	std::cout << "\n";
	for (; ite != orig.begin(); --ite)
		std::cout << *ite << " ";
	std::cout << "\n\n";

	printc("postfix iterator increment")
	for (; it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	for (; ite != orig.end(); ite++)
		std::cout << *ite << " ";
	std::cout << "\n\n";

	printc("postfix iterator decrement")
	for (; it != vec.begin(); it--)
		std::cout << *it << " ";
	std::cout << "\n";
	for (; ite != orig.begin(); ite--)
		std::cout << *ite << " ";
	std::cout << "\n\n";




	LINE
	ft::vector<std::string>::reverse_iterator	rit = vec.rbegin();
	std::vector<std::string>::reverse_iterator	rite = orig.rbegin();
	printc("prefix reverse iterator increment") // just to show that works
	for (; rit != vec.rend(); ++rit)
		std::cout << *rit << " ";
	std::cout << "\n";
	for (; rite != orig.rend(); ++rite)
		std::cout << *rite << " ";
	std::cout << "\n\n";

	std::cout << *--rit << "\n";
	std::cout << *rite << "\n";

	printc("prefix reverse iterator decrement")
	for (; rit != vec.rbegin(); --rit)
		std::cout << *rit << " ";
	std::cout << "\n";
	for (; rite != orig.rbegin(); --rite)
		std::cout << *rite << " ";
	std::cout << "\n\n";

	printc("postfix reverse iterator increment")
	for (; rit != vec.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << "\n";
	for (; rite != orig.rend(); rite++)
		std::cout << *rite << " ";
	std::cout << "\n\n";

	printc("postfix reverse iterator decrement")
	for (; rit != vec.rbegin(); rit--)
		std::cout << *rit << " ";
	std::cout << "\n";
	for (; rite != orig.rbegin(); rite--)
		std::cout << *rite << " ";
	std::cout << "\n\n";





	LINE
	printc("prefix/postfix iterator increment/decrement")
	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n\n";

	std::cout << "++it: " << *++it << "\n";
	std::cout << "++ite: " << *++ite << "\n\n";

	std::cout << "it++: " << *it++ << "\n";
	std::cout << "ite++: " << *ite++ << "\n\n";

	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n\n";

	std::cout << "--it: " << *--it << "\n";
	std::cout << "--ite: " << *--ite << "\n\n";

	std::cout << "it--: " << *it-- << "\n";
	std::cout << "ite--: " << *ite-- << "\n\n";

	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n\n";

	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n\n";

	it += 5;
	ite += 5;
	std::cout << "it += 5: " << *it << "\n";
	std::cout << "ite += 5: " << *ite << "\n\n";

	it -= 2;
	ite -= 2;
	std::cout << "it -= 2: " << *it << "\n";
	std::cout << "ite -= 2: " << *ite << "\n\n";

	std::cout << "it + 4: " << *(it + 4) << "\n";
	std::cout << "ite + 4: " << *(ite + 4) << "\n\n";

	std::cout << "it - 4: " << *(it - 4) << "\n";
	std::cout << "ite - 4: " << *(ite - 4) << "\n";


	LINE
	printc("iterator assignment")
	ft::vector<std::string>::iterator	asig_it	= it;
	std::vector<std::string>::iterator	asig_ite = ite;

	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n";
	std::cout << "asig_it = it: " << *asig_it << "\n";
	std::cout << "asig_ite = ite: " << *asig_ite << "\n";

	LINE
	printc("iterator's copy constructor")
	ft::vector<std::string>::iterator	copy_it(it);
	std::vector<std::string>::iterator	copy_ite(ite);

	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n";
	std::cout << "copy_it(it): " << *copy_it << "\n";
	std::cout << "copy_ite(ite): " << *copy_ite << "\n";

	LINE
	printc("iterator's copy constructor")
	std::cout << "it - copy_it: " << it - copy_it << "\n";
	std::cout << "ite - copy_ite: " << ite - copy_ite << "\n";
	printc("After it += 4, ite += 4:")
	it += 4;
	ite += 4;
	std::cout << "it - copy_it: " << it - copy_it << "\n";
	std::cout << "ite - copy_ite: " << ite - copy_ite << "\n";

	LINE
	std::cout << "copy_it: " << *copy_it << "\n";
	std::cout << "copy_ite: " << *copy_ite << "\n";
	std::cout << "copy_it[4]: " << copy_it[4] << "\n";
	std::cout << "copy_ite[4]: " << copy_ite[4] << "\n";

	LINE
	std::cout << "it: " << *it << "\n";
	std::cout << "ite: " << *ite << "\n";
	std::cout << "copy_it: " << *copy_it << "\n";
	std::cout << "copy_ite: " << *copy_ite << "\n\n";

	std::cout << "it == copy_it: " << (it == copy_it) << "\n";
	std::cout << "it != copy_it: " << (it != copy_it) << "\n";
	std::cout << "ite == copy_ite: " << (ite == copy_ite) << "\n";
	std::cout << "ite != copy_ite: " << (ite != copy_ite) << "\n\n";
	std::cout << "it < copy_it: " << (it < copy_it) << "\n";
	std::cout << "it > copy_it: " << (it > copy_it) << "\n";
	std::cout << "ite < copy_ite: " << (ite < copy_ite) << "\n";
	std::cout << "ite > copy_ite: " << (ite > copy_ite) << "\n\n";

	copy_it += 4;
	copy_ite += 4;
	printc("after += 4")
	std::cout << "it <= copy_it: " << (it <= copy_it) << "\n";
	std::cout << "it >= copy_it: " << (it >= copy_it) << "\n";
	std::cout << "ite <= copy_ite: " << (ite <= copy_ite) << "\n";
	std::cout << "ite >= copy_ite: " << (ite >= copy_ite) << "\n\n";

	copy_it++;
	copy_ite++;
	printc("after ++")
	std::cout << "it <= copy_it: " << (it <= copy_it) << "\n";
	std::cout << "it >= copy_it: " << (it >= copy_it) << "\n";
	std::cout << "ite <= copy_ite: " << (ite <= copy_ite) << "\n";
	std::cout << "ite >= copy_ite: " << (ite >= copy_ite) << "\n\n";

	copy_it -= 3;
	copy_ite -= 3;
	printc("after -= 3")
	std::cout << "it <= copy_it: " << (it <= copy_it) << "\n";
	std::cout << "it >= copy_it: " << (it >= copy_it) << "\n";
	std::cout << "ite <= copy_ite: " << (ite <= copy_ite) << "\n";
	std::cout << "ite >= copy_ite: " << (ite >= copy_ite) << "\n\n";

	printc("const_iterator and normal_iterator comparison")
	ft::vector<std::string>::const_iterator				cit		= it;
	std::vector<std::string>::const_iterator			cite	= ite;

//	cit = "11111"; // shouldn't be doable
//	ite = "11111";
	std::cout << "it == cit: " << (it == cit) << "\n";
	std::cout << "cit == it: " << (cit == it) << "\n";
	std::cout << "it != cit: " << (it != cit) << "\n";
	std::cout << "cit != it: " << (cit != it) << "\n";
	std::cout << "it <= cit: " << (it <= cit) << "\n";
	std::cout << "cit <= it: " << (cit <= it) << "\n";
	std::cout << "it >= cit: " << (it >= cit) << "\n";
	std::cout << "cit >= it: " << (cit >= it) << "\n\n";

	std::cout << "ite == cite: " << (ite == cite) << "\n";
	std::cout << "cite == ite: " << (cite == ite) << "\n";
	std::cout << "ite != cite: " << (ite != cite) << "\n";
	std::cout << "cite != ite: " << (cite != ite) << "\n";
	std::cout << "ite <= cite: " << (ite <= cite) << "\n";
	std::cout << "cite <= ite: " << (cite <= ite) << "\n";
	std::cout << "ite >= cite: " << (ite >= cite) << "\n";
	std::cout << "cite >= ite: " << (cite >= ite) << "\n\n";

	printc("const_reverse_iterator and reverse_iterator comparison")
	ft::vector<std::string>::reverse_iterator			r_it	= ++vec.rbegin();
	ft::vector<std::string>::const_reverse_iterator		cr_it	= ++++vec.rbegin();
	std::vector<std::string>::reverse_iterator			r_ite	= ++orig.rbegin();
	std::vector<std::string>::const_reverse_iterator	cr_ite	= ++++orig.rbegin();

	std::cout << "r_it == cr_it: " << (r_it == cr_it) << "\n";
	std::cout << "cr_it == r_it: " << (cr_it == r_it) << "\n";
	std::cout << "r_it != cr_it: " << (r_it != cr_it) << "\n";
	std::cout << "cr_it != r_it: " << (cr_it != r_it) << "\n";
	std::cout << "r_it <= cr_it: " << (r_it <= cr_it) << "\n";
	std::cout << "cr_it <= r_it: " << (cr_it <= r_it) << "\n";
	std::cout << "r_it >= cr_it: " << (r_it >= cr_it) << "\n";
	std::cout << "cr_it >= r_it: " << (cr_it >= r_it) << "\n\n";

	std::cout << "r_ite == cr_ite: " << (r_ite == cr_ite) << "\n";
	std::cout << "cr_ite == r_ite: " << (cr_ite == r_ite) << "\n";
	std::cout << "r_ite != cr_ite: " << (r_ite != cr_ite) << "\n";
	std::cout << "cr_ite != r_ite: " << (cr_ite != r_ite) << "\n";
	std::cout << "r_ite <= cr_ite: " << (r_ite <= cr_ite) << "\n";
	std::cout << "cr_ite <= r_ite: " << (cr_ite <= r_ite) << "\n";
	std::cout << "r_ite >= cr_ite: " << (r_ite >= cr_ite) << "\n";
	std::cout << "cr_ite >= r_ite: " << (cr_ite >= r_ite) << "\n\n";

}

void	elementAccessCheck() {
	ft::vector<std::string>		vec;
	std::vector<std::string>	orig;

	vec.push_back("one");		orig.push_back("one");
	vec.push_back("two");		orig.push_back("two");
	vec.push_back("three");	orig.push_back("three");
	vec.push_back("four");	orig.push_back("four");
	vec.push_back("five");	orig.push_back("five");
	vec.push_back("six");		orig.push_back("six");
	vec.push_back("seven");	orig.push_back("seven");
	vec.push_back("eight");	orig.push_back("eight");
	vec.push_back("nine");	orig.push_back("nine");

	printc("operator []")
	printVec(vec);
	printVec(orig);

	LINE
	printc("at()")
	std::cout << vec.at(5) << "\n";
	std::cout << orig.at(5)<< "\n";
	try {
		std::cout << vec.at(15) << "\n";
	} catch (const std::exception &ex) { print(ex.what()) }
	try {
		std::cout << orig.at(15)<< "\n";
	} catch (const std::exception &ex) { print(ex.what()) }

	LINE
	printc("front()")
	std::cout << vec.front() << "\n";
	std::cout << orig.front()<< "\n";

	LINE
	printc("back()")
	std::cout << vec.back() << "\n";
	std::cout << orig.back()<< "\n";

	LINE
	printc("data()")
	std::cout << "vec.data(): " << vec.data() << "\n";
	std::cout << "orig.data(): " << orig.data()<< "\n";
	std::cout << "*vec.data(): " << *vec.data() << "\n";
	std::cout << "*orig.data(): " << *orig.data()<< "\n";
}

void	capacityCheck() {
	ft::vector<std::string>		vec;
	std::vector<std::string>	orig;

	printc("Empty containers")
	std::cout	<< "vec.empty(): " << vec.empty() << "\n"
				<< "vec.size(): " << vec.size() << "\n"
				<< "vec.capacity(): " << vec.capacity() << "\n"
				<< "vec.max_size(): " << vec.max_size() << "\n\n";
	std::cout	<< "orig.empty(): " << orig.empty() << "\n"
				<< "orig.size(): " << orig.size() << "\n"
				<< "orig.capacity(): " << orig.capacity() << "\n"
				<< "orig.max_size(): " << orig.max_size() << "\n";

	vec.reserve(20);
	orig.reserve(20);

	vec.push_back("one");		orig.push_back("one");
	vec.push_back("two");		orig.push_back("two");
	vec.push_back("three");	orig.push_back("three");
	vec.push_back("four");	orig.push_back("four");
	vec.push_back("five");	orig.push_back("five");
	vec.push_back("six");		orig.push_back("six");
	vec.push_back("seven");	orig.push_back("seven");
	vec.push_back("eight");	orig.push_back("eight");
	vec.push_back("nine");	orig.push_back("nine");

	printc("After insertion")
	std::cout	<< "vec.empty(): " << vec.empty() << "\n"
				<< "vec.size(): " << vec.size() << "\n"
				<< "vec.capacity(): " << vec.capacity() << "\n"
				<< "vec.max_size(): " << vec.max_size() << "\n\n";
	std::cout	<< "orig.empty(): " << orig.empty() << "\n"
				<< "orig.size(): " << orig.size() << "\n"
				<< "orig.capacity(): " << orig.capacity() << "\n"
				<< "orig.max_size(): " << orig.max_size() << "\n";
}


void	modifiersCheck() {
	ft::vector<int>		vec;
	std::vector<int>	orig;

	vec.push_back(1);		orig.push_back(1);
	vec.push_back(2);		orig.push_back(2);
	vec.push_back(3);		orig.push_back(3);
	vec.push_back(4);		orig.push_back(4);
	vec.push_back(5);		orig.push_back(5);
	vec.push_back(6);		orig.push_back(6);
	vec.push_back(7);		orig.push_back(7);
	vec.push_back(8);		orig.push_back(8);
	vec.push_back(9);		orig.push_back(9);
	vec.push_back(10);	orig.push_back(10);
	vec.push_back(11);	orig.push_back(11);
	vec.push_back(12);	orig.push_back(12);

	printc("push_back()")
	printVec(vec);
	printVec(orig);

	LINE
	printc("pop_back()")
	vec.pop_back();		orig.pop_back();
	vec.pop_back();		orig.pop_back();
	vec.pop_back();		orig.pop_back();

	printVec(vec);
	printVec(orig);

	LINE
	printc("resize(n)  n >= vec.size(n)")
	std::cout	<< "vec.size(): " << vec.size() << "\n"
				<< "orig.size(): " << orig.size() << "\n";

	vec.resize(12);		orig.resize(12);

	printVec(vec);
	printVec(orig);

	std::cout	<< "vec.size(): " << vec.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";
	LINE
	printc("resize(n, val)  n >= vec.size(n, val)")
	std::cout	<< "vec.size(): " << vec.size() << "\n"
				<< "orig.size(): " << orig.size() << "\n";

	vec.resize(15, 69);		orig.resize(15, 69);

	printVec(vec);
	printVec(orig);

	std::cout	<< "vec.size(): " << vec.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";

	LINE
	printc("resize(n)  n < vec.size()")
	std::cout	<< "vec.size(): " << vec.size() << "\n"
				<< "orig.size(): " << orig.size() << "\n";

	vec.resize(8);		orig.resize(8);

	printVec(vec);
	printVec(orig);

	std::cout	<< "vec.size(): " << vec.size() << "\n"
				 << "orig.size(): " << orig.size() << "\n";

	LINE
	printc("insert(pos, val)")
	vec.insert(vec.begin() + 4, 42);
	orig.insert(orig.begin() + 4, 42);
	printVec(vec);
	printVec(orig);

	LINE
	printc("insert(pos, count, val)")
	vec.insert(vec.begin() + 2, 4, 21);
	orig.insert(orig.begin() + 2, 4, 21);
	printVec(vec);
	printVec(orig);

	LINE
	printc("insert(pos, it1, it2)")
	ft::vector<int>		tmp1(5, -21);
	std::vector<int>	tmp2(5, -21);
	vec.insert(vec.begin() + 11, ++++tmp1.begin(), --tmp1.end());
	orig.insert(orig.begin() + 11, ++++tmp2.begin(), --tmp2.end());
	printVec(vec);
	printVec(orig);

	LINE
	printc("swap()")
	ft::vector<int>		copy1(5, -21);
	std::vector<int>	copy2(5, -21);
	printc("copy1 and copy2 before swap");
	printVec(copy1);
	printVec(copy2);

	copy1.swap(vec);
	copy2.swap(orig);
	
	printc("After swap");
	printc("copy1")
	printVec(copy1);
	printc("copy2")
	printVec(copy2);
	printc("vec")
	printVec(vec);
	printc("orig")
	printVec(orig);
	
}

void	comparisonCheck() {
	ft::vector<int>		vec1(5, 21);
	ft::vector<int>		vec2(5, 21);
	std::vector<int>	orig1(5, 21);
	std::vector<int>	orig2(5, 21);

	printc("vec1 == vec2")
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl << std::endl;

	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl << std::endl;


	printc("vec1.size() < vec2.size()")
	vec1.pop_back();
	orig1.pop_back();
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl << std::endl;

	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl << std::endl;

	printc("vec1.size() == vec2.size() && 1 value is diff")
	vec1.push_back(42);
	orig1.push_back(42);
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl << std::endl;

	std::cout << "orig1 == orig2: " << (orig1 == orig2) << std::endl;
	std::cout << "orig1 != orig2: " << (orig1 != orig2) << std::endl;
	std::cout << "orig1 < orig2: " << (orig1 < orig2) << std::endl;
	std::cout << "orig1 <= orig2: " << (orig1 <= orig2) << std::endl;
	std::cout << "orig1 > orig2: " << (orig1 > orig2) << std::endl;
	std::cout << "orig1 >= orig2: " << (orig1 >= orig2) << std::endl << std::endl;
}

int main() {
	std::cout << std::boolalpha;

	memberFunctionsCheck();
	iteratorsCheck();
	elementAccessCheck();
	capacityCheck();
	modifiersCheck();
	comparisonCheck();
}