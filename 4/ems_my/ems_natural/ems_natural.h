#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>


constexpr auto kBlockSeparator = "|";

// SType - ��� ����������� ������
// DSep  - ����������� ������ � �����
template<class SType, char DSep = ' '>
class NExternalMergeSort
{
public:
	// way_count -- ���������� ����� (��������������� ������) ����������
	explicit NExternalMergeSort(const std::string& filename, unsigned int way_count = 2) : seriesLength_{ 0 }, wayCount_{ way_count }, inputFilename_{ filename } {
		if (wayCount_ < 2) wayCount_ = 2;
	};
	virtual ~NExternalMergeSort() = default;

	template<class Compare>
	void sort(std::fstream& input, Compare&& cmp = [](const SType& a, const SType& b) { return a < b; });

private:
	// ���������� ����� ����� 
	void computeSeriesLength(std::fstream& input);

	// ��� ��� ���������������� �����
	std::string getExternalFilename(const unsigned int way);

	// �������� ������ �� wayCount_ ��������������� ������
	std::vector<std::fstream> getExternalFiles();

	// ������� � ������� ��������������� ����� ��� ����������� �����-������
	void reopenExternalFiles(std::vector<std::fstream>& ext, std::ios_base::openmode mode);

	// ������� ��������������� �����
	void removeExternalFiles();

	// ������� � ������� ���� ������� ������ ��� ����������� �����-������
	void reopenInputFile(std::fstream& input, std::ios_base::openmode mode);

	bool fullEOF(std::vector<std::fstream>& ext);

	// �������� ����������������� ������� ������
	template<class Compare>
	bool isSorted(std::fstream& input, Compare& cmp);

	// ���������� ����� � ������������� ��������� �� ������� ���������� ������� ������
	template<class Compare>
	void split(std::fstream& input, std::vector<std::fstream>& ext, Compare& cmp);

	// ������������ ������� �� ��������������� ������
	template<class Compare>
	void merge(std::fstream& input, std::vector<std::fstream>& ext, Compare& cmp);

	unsigned int seriesLength_;  // ����� ����� ����������� ��� ������� ���������� 
	unsigned int wayCount_ = 2;		// ���������� ����� (��������������� ������) ���������� 
	std::string inputFilename_;
};

template<class SType, char DSep>
void NExternalMergeSort<SType, DSep>::computeSeriesLength(std::fstream& input_series)
{
	this->seriesLength_ = 0;
	SType value{};
	while (input_series >> value)
	{
		this->seriesLength_++;
	}
}

template<class SType, char DSep>
std::string NExternalMergeSort<SType, DSep>::getExternalFilename(const unsigned int way)
{
	return "/" + std::to_string(way + 1);
}

template<class SType, char DSep>
std::vector<std::fstream> NExternalMergeSort<SType, DSep>::getExternalFiles()
{
	std::vector<std::fstream> ext(this->wayCount_);
	for(unsigned int i = 0; i < this->wayCount_; ++i)
	{
		const auto filename = getExternalFilename(i);
		std::ofstream f(filename);
		ext[i] = std::fstream(filename);
	}
	return ext;
}

template<class SType, char DSep>
void NExternalMergeSort<SType, DSep>::reopenExternalFiles(std::vector<std::fstream>& ext, std::ios_base::openmode mode)
{
	for (int i = 0; i < ext.size(); ++i)
	{
		ext[i].close();

		const auto filename = getExternalFilename(i);
		ext[i].open(filename, mode);
	}
}

template<class SType, char DSep>
void NExternalMergeSort<SType, DSep>::removeExternalFiles()
{
	for (unsigned int i = 0; i < this->wayCount_; ++i)
	{
		const auto filename = getExternalFilename(i);
		const auto removeResult = std::remove(filename.c_str());
		std::cout << "Remove external file (" << filename << "): " << std::boolalpha << removeResult << std::endl;
	}
}

template<class SType, char DSep>
void NExternalMergeSort<SType, DSep>::reopenInputFile(std::fstream& input, std::ios_base::openmode mode)
{
	input.close();
	input.open(this->inputFilename_, mode);
}

template<class SType, char DSep>
bool NExternalMergeSort<SType, DSep>::fullEOF(std::vector<std::fstream>& ext)
{
	bool fullEOF = true;
	for (auto& f : ext)
	{
		fullEOF &= f.eof();
		if (!fullEOF) break;
	}

	return fullEOF;
}

template<class SType, char DSep>
template<class Compare>
bool NExternalMergeSort<SType, DSep>::isSorted(std::fstream& input, Compare& cmp)
{
	SType value{};
	input >> value;
	SType oldValue = value;

	bool sorted = false;
	while (input >> value)
	{
		// sorted = cmp(oldValue, value); // ������� �����, ���� ��� ��������
		//sorted = cmp(oldValue, value);
		/*const auto cmp1 = cmp(oldValue, value);
		const auto cmp2 = cmp(value, oldValue);
		sorted = (cmp1 == cmp2) || (cmp1 ^ !cmp2);*/
		const auto cmp1 = cmp(oldValue, value);
		const auto cmp2 = cmp(value, oldValue);
		sorted = cmp1 || (cmp1 == false && cmp2 == false);

		oldValue = value;
		if (!sorted) break;
	}

	return sorted;
}

template<class SType, char DSep>
template<class Compare>
void NExternalMergeSort<SType, DSep>::split(
	std::fstream& input_series, std::vector<std::fstream>& ext,
	Compare& cmp
	)
{
	SType value{};
	SType oldValue{};
	unsigned int way = 0;

	if (input_series >> value)
	{
		ext[way] << value << DSep;
		oldValue = value;
		std::cout << value << DSep;
	}

	while(input_series >> value)
	{
		if (!cmp(oldValue, value) && cmp(value, oldValue))
		{
			way = (way + 1) % wayCount_;
		}

		ext[way] << value << DSep;
		oldValue = value;
		std::cout << value << DSep;
	}
	std::cout << std::endl;
}

template<class SType, char DSep>
template<class Compare>
void NExternalMergeSort<SType, DSep>::merge(
	std::fstream& input_series, std::vector<std::fstream>& ext,
	Compare& cmp
)
{
	while(!this->fullEOF(ext))
	{
		std::vector<SType> oldValues(this->wayCount_);
		std::vector<bool> eogs(this->wayCount_, { false }); // end of group (������ end of file)
		for (unsigned int way = 0; way < this->wayCount_; ++way)
		{
			SType value{};
			if(ext[way] >> value) oldValues[way] = value;
			else eogs[way] = true;
		}

		bool fullEOG = false; // ���� ���������� ����� ����� �� ���� �����

		// �������� ����, � �������� ����� �������� �������
		while (!fullEOG)
		{
			int wayWithMin = -1; 
			for (unsigned int checkedWay = 0; checkedWay < this->wayCount_; ++checkedWay)
			{
				if (eogs[checkedWay] || ext[checkedWay].eof()) continue;
				wayWithMin = checkedWay;
			}
			if (-1 == wayWithMin) break;

			for (unsigned int checkedWay = 0; checkedWay < this->wayCount_; ++checkedWay)
			{
				if (eogs[checkedWay] || ext[checkedWay].eof()) continue;
				if (cmp(oldValues[checkedWay], oldValues[wayWithMin])) wayWithMin = checkedWay;
			}

			// �������
			input_series << oldValues[wayWithMin] << DSep;
			std::cout << oldValues[wayWithMin] << DSep;

			// ����. ��������
			SType value{};
			if (ext[wayWithMin] >> value) 
			{
				oldValues[wayWithMin] = value;
			}
			else
			{
				eogs[wayWithMin] = true;
				ext[wayWithMin].clear(); // ������� ���������� ���� ������, ����� ����� ����������� ������ ���������� ������
			}

			// �������� ���������� ����� �����
			fullEOG = true;
			for (auto eog : eogs)
			{
				fullEOG &= eog;
				if (!fullEOG) break;
			}
		}

		// ������� ����� ������� ���������� ������
		for (unsigned int way = 0; way < this->wayCount_; ++way)
		{
			if (eogs[way]) 
			{
				ext[way].get();
				ext[way].get();
			}
		}
	}

	std::cout << std::endl;
}

template<class SType, char DSep>
template<class Compare>
void NExternalMergeSort<SType, DSep>::sort(std::fstream& input_series, Compare&& cmp)
{	 
	this->computeSeriesLength(input_series);
	if (this->seriesLength_ <= 1)
	{
		return;
	}

	auto&& cmp_ = std::forward<Compare>(cmp);
	std::vector<std::fstream> ext = this->getExternalFiles();

	reopenInputFile(input_series, std::ios_base::in);
	bool sorted = isSorted(input_series, cmp_);
	std::cout << "Sorted: " << std::boolalpha << sorted << std::endl;
	while(!sorted)
	{
		reopenInputFile(input_series, std::ios_base::in);
		reopenExternalFiles(ext, std::ios_base::out);

		std::cout << "Subgroup: " << std::endl;
		this->split(input_series, ext, cmp_);

		reopenInputFile(input_series, std::ios_base::out);
		reopenExternalFiles(ext, std::ios_base::in);

		std::cout << "Merge: " << std::endl;
		this->merge(input_series, ext, cmp_);

		reopenInputFile(input_series, std::ios_base::in);
		sorted = isSorted(input_series, cmp_);

		std::cout << "Sorted: " << std::boolalpha << sorted << std::endl;
	}

	input_series.flush();
	this->removeExternalFiles();
}
