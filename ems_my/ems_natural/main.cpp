#include <fstream>
#include <vector>

#include "ems_natural.h"


struct A
{
	std::string n;
	int a = 0;
	int b = 0;
	int c = 0;
};

std::istream& operator>>(std::istream& lhv, A& rhv)
{
	std::string n;
	while (true)
	{
		const auto c = lhv.get();
		if (c == -1 || c == ',') break;
		if (c >= 0) n += (char)c;
	}
	rhv.n = n;

	int value = 0;
	lhv >> value;
	rhv.a = value;

	lhv.get();
	lhv >> value;
	rhv.b = value;

	lhv.get();
	lhv >> value;
	rhv.c = value;

	lhv.get(); // считывание \n

	return lhv;
}

std::ostream& operator<<(std::ostream& lhv, const A& rhv)
{
	lhv << rhv.n << ", " << rhv.a << ", " << rhv.b << ", " << rhv.c;
	return lhv;
}


int main(int argc, char** argv)
{
	const auto input_file = "A";
	std::fstream input(input_file, std::ios_base::in | std::ios_base::out);
	if (!input)
	{
		perror("Error with input file");
		return EXIT_FAILURE;
	}

	NExternalMergeSort<A, '\n'>(input_file).sort(input, [](const A& a, const A& b) { return a.n < b.n; });
	input.close();
	system("pause");
	return EXIT_SUCCESS;
}
