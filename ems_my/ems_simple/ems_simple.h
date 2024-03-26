#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>


// SType - тип сортируемых данных
// DSep  - разделитель данных в файле
template<class SType, char DSep = ' '>
class SExternalMergeSort
{
public:
	// way_count -- количество путей (вспомогательных файлов) сортировки
	explicit SExternalMergeSort(const std::string& filename, unsigned int way_count = 2) : seriesLength_{ 0 }, wayCount_{ way_count }, inputFilename_{ filename } {
		if (wayCount_ < 2) wayCount_ = 2;
	};
	virtual ~SExternalMergeSort() = default;

	template<class Compare>
	void sort(std::fstream& input, Compare&& cmp = [](const SType& a, const SType& b) { return a < b; });

private:
	// вычисление длины серии 
	void computeSeriesLength(std::fstream& input);

	// имя для вспомогательного файла
	std::string getExternalFilename(const unsigned int way);

	// получить список из wayCount_ вспомогательных файлов
	std::vector<std::fstream> getExternalFiles();

	// закрыть и открыть вспомогательные файлы для корректного ввода-вывода
	void reopenExternalFiles(std::vector<std::fstream>& ext, std::ios_base::openmode mode);

	// удалить вспомогательные файлы
	void removeExternalFiles();

	// закрыть и открыть файл входных данных для корректного ввода-вывода
	void reopenInputFile(std::fstream& input, std::ios_base::openmode mode);

	// разделение серии во вспомогательные файлы подгруппами длинны subgroup_length
	void split(std::fstream& input, std::vector<std::fstream>& ext, const unsigned int subgroup_length);

	// слияние из вспомогательных файлов подгруппами длинны subgroup_length
	template<class Compare>
	void merge(std::fstream& input, std::vector<std::fstream>& ext, const unsigned int subgroup_length, Compare& cmp);

	unsigned int seriesLength_;  // длина серии вычисляется при запуске сортировки 
	unsigned int wayCount_;		// количество путей (вспомогательных файлов) сортировки 
	std::string inputFilename_;
};

template<class SType, char DSep>
void SExternalMergeSort<SType, DSep>::computeSeriesLength(std::fstream& input_series)
{
	this->seriesLength_ = 0;
	SType value{};
	while (input_series >> value)
	{
		this->seriesLength_++;
	}
}

template<class SType, char DSep>
std::string SExternalMergeSort<SType, DSep>::getExternalFilename(const unsigned int way)
{
	return "/" + std::to_string(way + 1);
}

template<class SType, char DSep>
std::vector<std::fstream> SExternalMergeSort<SType, DSep>::getExternalFiles()
{
	std::vector<std::fstream> ext(this->wayCount_);
	for (unsigned int i = 0; i < this->wayCount_; ++i)
	{
		const auto filename = this->getExternalFilename(i);
		std::ofstream f(filename);
		ext[i] = std::fstream(filename);
	}
	return ext;
}

template<class SType, char DSep>
void SExternalMergeSort<SType, DSep>::reopenExternalFiles(std::vector<std::fstream>& ext, std::ios_base::openmode mode)
{
	for (int i = 0; i < ext.size(); ++i)
	{
		ext[i].close();

		const auto filename = getExternalFilename(i);
		ext[i].open(filename, mode);
	}
}

template<class SType, char DSep>
void SExternalMergeSort<SType, DSep>::removeExternalFiles()
{
	for (unsigned int i = 0; i < this->wayCount_; ++i)
	{
		const auto filename = getExternalFilename(i);
		const auto removeResult = std::remove(filename.c_str());
		std::cout << "Remove external file (" << filename << "): " << std::boolalpha << removeResult << std::endl;
	}
}

template<class SType, char DSep>
void SExternalMergeSort<SType, DSep>::reopenInputFile(std::fstream& input, std::ios_base::openmode mode)
{
	input.close();
	input.open(this->inputFilename_, mode);
}

template<class SType, char DSep>
void SExternalMergeSort<SType, DSep>::split(std::fstream& input_series, std::vector<std::fstream>& ext, const unsigned int subgroup_length)
{
	while (!input_series.eof())
	{
		for (auto&& f : ext)
		{
			SType value{};
			unsigned int step = 0;
			while (input_series >> value)
			{
				f << value << DSep;
				std::cout << value << "\t";
				++step;
				if (step == subgroup_length) break;
			}
			std::cout << " | ";
		}
		std::cout << std::endl;
	}
}

template<class SType, char DSep>
template<class Compare>
void SExternalMergeSort<SType, DSep>::merge(
	std::fstream& input_series, std::vector<std::fstream>& ext,
	const unsigned int subgroup_length,
	Compare& cmp)
{
	if (subgroup_length == 0) return;

	std::vector<SType> buf;
	buf.reserve(subgroup_length * this->wayCount_);

	// количество полных групп в путях
	const unsigned int fullGroupCount = this->seriesLength_ / subgroup_length / this->wayCount_;

	// учет возможного отсутствия полной последней группы в некоторых путях
	const unsigned int add = (this->seriesLength_ / subgroup_length) % this->wayCount_ == 0 ? 0 : 1;

	// количество шагов алгоритма
	const unsigned int stepsCount = fullGroupCount + add;
	unsigned int step = 0;
	while (step < stepsCount)
	{
		for (auto& f : ext)
		{
			SType value{};
			unsigned int substep = 0;
			while (substep < subgroup_length && f >> value)
			{
				buf.push_back(value);
				++substep;
			}
		}

		std::sort(std::begin(buf), std::end(buf), cmp);

		const auto bufLength = buf.size();
		for (int i = 0; i < bufLength; ++i)
		{
			input_series << buf[i] << DSep;
			std::cout << buf[i] << DSep;
		}
		std::cout << "\t";

		buf.clear();
		buf.resize(0);
		step++;
	}
	std::cout << std::endl;
}

template<class SType, char DSep>
template<class Compare>
void SExternalMergeSort<SType, DSep>::sort(std::fstream& input_series, Compare&& cmp)
{
	this->computeSeriesLength(input_series);
	if (this->seriesLength_ <= 1)
	{
		return;
	}

	auto&& cmp_ = std::forward<Compare>(cmp);
	std::vector<std::fstream> ext = this->getExternalFiles();

	// Сортируем пока длина подгруппы меньше длины серии
	for (unsigned int subgroup_length = 1; subgroup_length < this->seriesLength_; subgroup_length *= 2)
	{
		reopenInputFile(input_series, std::ios_base::in);
		reopenExternalFiles(ext, std::ios_base::out);

		std::cout << "Subgroup with length " << std::to_string(subgroup_length) << ":" << std::endl;
		this->split(input_series, ext, subgroup_length);

		reopenInputFile(input_series, std::ios_base::out);
		reopenExternalFiles(ext, std::ios_base::in);

		std::cout << "Merge to groups with length " << std::to_string(subgroup_length) << std::endl;
		this->merge(input_series, ext, subgroup_length, cmp_);
	}

	input_series.flush();
	this->removeExternalFiles();
}
