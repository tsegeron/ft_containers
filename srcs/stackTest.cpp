# include "../hdrs/containers/stack.hpp"
# include <stack>
# include <iostream>

# define BLUE		"\033[34m"
# define RESET		"\033[0m"

# define printc(msg) std::cout << BLUE << msg << RESET << std::endl;
# define print(msg) std::cout << msg << std::endl;
# define LINE		printc("------------------------------------------------");


int main() {
	std::cout << std::boolalpha;

	ft::stack<std::string>		s;
	std::stack<std::string>		orig;

	std::cout 	<< "s.empty(): " << s.empty() << "\n"
				<< "s.size(): " << s.size() << "\n";
	std::cout	<< "orig.empty(): " << orig.empty() << "\n"
				<< "orig.size(): " << orig.size() << "\n";

	LINE
	printc("push()")
	s.push("one");		orig.push("one");
	s.push("two");		orig.push("two");
	s.push("three");		orig.push("three");
	s.push("four");		orig.push("four");
	s.push("five");		orig.push("five");

	std::cout 	<< "s.empty(): " << s.empty() << "\n"
				 << "s.size(): " << s.size() << "\n";
	std::cout	<< "orig.empty(): " << orig.empty() << "\n"
				 << "orig.size(): " << orig.size() << "\n";


	LINE
	printc("pop()")
	s.pop();	orig.pop();
	s.pop();	orig.pop();
	std::cout 	<< "s.empty(): " << s.empty() << "\n"
				 << "s.size(): " << s.size() << "\n";
	std::cout	<< "orig.empty(): " << orig.empty() << "\n"
				 << "orig.size(): " << orig.size() << "\n";

	LINE
	printc("top()")
	std::cout << "s.top(): " << s.top() << std::endl;
	std::cout << "orig.top(): " << orig.top() << std::endl;

	LINE
	{
		printc("copy constructor")
		ft::stack<std::string> copy1(s);
		std::stack<std::string> copy2(orig);
		std::cout << "copy1.empty(): " << copy1.empty() << "\n"
				  << "copy1.size(): " << copy1.size() << "\n";
		std::cout << "copy2.empty(): " << copy2.empty() << "\n"
				  << "copy2.size(): " << copy2.size() << "\n";
	}
	LINE
	{
		printc("operator = ")
		ft::stack<std::string>		copy1 = s;
		std::stack<std::string>		copy2 = orig;
		std::cout << "copy1.empty(): " << copy1.empty() << "\n"
				  << "copy1.size(): " << copy1.size() << "\n";
		std::cout << "copy2.empty(): " << copy2.empty() << "\n"
				  << "copy2.size(): " << copy2.size() << "\n";

		LINE
		printc("comparison")
		std::cout << "copy1 == s: " << (copy1 == s) << "\n"
				  << "copy2 == orig: " << (copy2 == orig) << "\n";
		std::cout << "copy1 != s: " << (copy1 != s) << "\n"
				  << "copy2 != orig: " << (copy2 != orig) << "\n";
		std::cout << "copy1 <= s: " << (copy1 <= s) << "\n"
				  << "copy2 <= orig: " << (copy2 <= orig) << "\n";
		std::cout << "copy1 >= s: " << (copy1 >= s) << "\n"
				  << "copy2 >= orig: " << (copy2 >= orig) << "\n";

		LINE
		printc("swap()")
		ft::stack<std::string>		black_hole1;
		std::stack<std::string>		black_hole2;
		copy1.swap(black_hole1);
		copy2.swap(black_hole2);
		std::cout << "copy1.empty(): " << copy1.empty() << "\n"
				  << "copy1.size(): " << copy1.size() << "\n";
		std::cout << "copy2.empty(): " << copy2.empty() << "\n"
				  << "copy2.size(): " << copy2.size() << "\n";
		std::cout << "black_hole1.empty(): " << black_hole1.empty() << "\n"
				  << "black_hole1.size(): " << black_hole1.size() << "\n";
		std::cout << "black_hole2.empty(): " << black_hole2.empty() << "\n"
				  << "black_hole2.size(): " << black_hole2.size() << "\n";

		LINE
		printc("comparison again")
		std::cout << "copy1 == s: " << (copy1 == s) << "\n"
				  << "copy2 == orig: " << (copy2 == orig) << "\n";
		std::cout << "copy1 != s: " << (copy1 != s) << "\n"
				  << "copy2 != orig: " << (copy2 != orig) << "\n";
		std::cout << "copy1 <= s: " << (copy1 <= s) << "\n"
				  << "copy2 <= orig: " << (copy2 <= orig) << "\n";
		std::cout << "copy1 >= s: " << (copy1 >= s) << "\n"
				  << "copy2 >= orig: " << (copy2 >= orig) << "\n";
	}
}
