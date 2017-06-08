#include "iterators.cpp"

int main()
{
	std::ofstream outFile("output.txt", std::ios::trunc);
	outFile << "Austin Fouch | OOP Final Project\n";
/*
	back_insert_iterator testing
*/
	outFile << "\n" << "back_insert_iterator using vectors\n";
	std::vector<int> a, b;
	back_insert_iterator<std::vector<int>> backInsertIter(a);

	// assignment overload
	for (int i = 0; i < 10; i++)
		backInsertIter = i;
	outFile << "Vector a created with back_insert_iterator\n";
	for (auto const & i : a)
		outFile << i << ' ';
	outFile << '\n';
	// using my back_inserter function, backInserter(Cont& c), copy a to b
	// while multiplying elements by 2
	for (auto i : a)
		backInserter(b) = i*2;
	outFile << "Vector b = a*2 using backInserter\n";
	for (auto const & i : b)
		outFile << i << ' ';
	outFile << '\n';
/*
	front_insert_iterator testing
*/
	outFile << "\n" << "front_insert_iterator using lists\n";
	std::list<int> c, d;
	front_insert_iterator<std::list<int>> frontInsertIter(c);

	// assignment overload
	for (int i = 0; i < 10; i++)
		frontInsertIter = i;
	outFile << "List c created with front_insert_iterator\n";
	for (auto const & i : c)
		outFile << i << ' ';
	outFile << '\n';

	// using my back_inserter function, backInserter(Cont& c), copy c to d
	// while multiplying elements by 2
	for (auto i : c)
		frontInserter(d) = i * 2;
	outFile << "List d = c*2 using frontInserter\n";
	for (auto const & i : d)
		outFile << i << ' ';
	outFile << '\n';
/*
	insert_iterator
*/
	outFile << "\n" << "insert_iterator using sets\n";
	std::list<int> e;
	std::list<int> f{ 1, 2, 3, 4 };
	insert_iterator<std::list<int>> insertIter(e, e.end());
	// assignment overload
	for (int i = 0; i < 10; i++)
		insertIter = i;
	outFile << "Set e created with insert_iterator at the end of the set\n";
	for (auto const & i : e)
		outFile << i << ' ';
	outFile << '\n';
	// using my inserter function, inserter(), insert e*2 in the middle of f
	outFile << "Set f\n";
	for (auto const & i : f)
		outFile << i << ' ';
	outFile << '\n';
	for (auto i : e)
		insertInserter(f, f.end()) = i * 2;
	outFile << "Set f with set e*2 inserted at f.end()\n";
	for (auto const & i : f)
		outFile << i << ' ';
	outFile << '\n';
/*
	istream_iterator
*/
	outFile << "\n" << "istream_iterator using files\n";
	std::ifstream inFile("input.txt");
	typedef istream_iterator<char> istreamIter;
	for (istreamIter it = istreamIter(inFile); !inFile.eof(); it++)
		outFile << *it << " ";
	outFile << "\n";
	inFile.close();
/*
	ostream_iterator
*/
	outFile << "\n" << "ostream_iterator using files\n";
	ostream_iterator<int> outIter(outFile, ", ");
	for (int i = 0; i < 10; ++i)
		outIter = i;
	ostream_iterator<double> outIter2(outFile);
	*outIter2++ = 3.14;
/*
	reverse iterator
*/
	/*
	outFile << "\n" << "reverse_iterator using files\n";
	std::vector<int> z{1, 2, 3, 4, 5};
	reverse_iterator<int> r = z.end();
	while (r != z.begin)
		--r;
	outFile << &r;
	outFile.close();
	*/
}