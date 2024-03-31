#include <fstream>
#include <vector>
#include "ems_natural.h"
#include <string>
#include <sstream>
// Функция разделения строки по символу-разделителю
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

// 
struct Consumer
{
	std::string surname;
	std::string name;
	std::string patronymic;
	std::string address;
	std::string job;
	std::string date;
};

std::istream& operator>>(std::istream& lhv, Consumer& rhv)
{
	std::string tmp;
	std::getline(lhv, tmp);

	std::vector<std::string> e;
	split(tmp, ',', e);
	const auto elementsCount = e.size();
	if (elementsCount > 0)
	{
		std::vector<std::string> fio;
		split(e[0], ' ', fio);

		if (fio.size())
		{
			rhv.surname = fio[0];
			rhv.name = fio[1];
			rhv.patronymic = fio[2];
		}

		if (elementsCount >= 2) rhv.address = e[1].substr(1) + ", " + e[2].substr(1);
		if (elementsCount >= 3) rhv.job = e[3].substr(1);
		if (elementsCount >= 4) rhv.date = e[4].substr(1);
	}

	return lhv;
}

std::ostream& operator<<(std::ostream& lhv, Consumer& rhv)
{
	lhv << rhv.surname << " " << rhv.name << " " << rhv.patronymic
		<< ", " << rhv.address << ", " << rhv.job << ", " << rhv.date;
	return lhv;
}

int main(int argc, char** argv)
{
	//setlocale(LC_CTYPE, "rus");
	setlocale(LC_ALL, "Rus");

	const auto input_file = "A";
	std::fstream input(input_file, std::ios_base::in | std::ios_base::out);
	if (!input)
	{
		perror("Error with input file");
		return EXIT_FAILURE;
	}

	NExternalMergeSort<Consumer, '\n'>(input_file).sort(input, [](const Consumer& a, const Consumer& b) { return a.surname < b.surname; });
	input.close();
	system("pause");
	return EXIT_SUCCESS;
}
