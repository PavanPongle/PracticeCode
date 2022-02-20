#ifndef _CSV_
#define _CSV_

#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

class MeanGoalPerGame
{
    std::string m_teamName;
    double m_mean = 0;
public:
    MeanGoalPerGame() : m_teamName("") {}
    MeanGoalPerGame(const MeanGoalPerGame&) = delete;
    MeanGoalPerGame& operator=(const MeanGoalPerGame&) = delete;
    MeanGoalPerGame(MeanGoalPerGame&&) = delete;
    MeanGoalPerGame& operator=(MeanGoalPerGame&&) = delete;

    inline void SetTeamName(const std::string& val) { m_teamName.assign(val); }
    inline void SetMean(const double& val) { m_mean = val; }

    inline std::string& GetTeamName() { return m_teamName; }
    inline double GetMean() { return m_mean; }
};

template <class T>
class CSVReadWrite
{
    std::string m_fileName;
    T* arrOfObj = NULL;
    std::vector<std::string> m_cols;
    size_t m_rowCount = 0;
    std::vector<std::string> m_colNames;

public:
    CSVReadWrite(const std::string& fileName, const std::initializer_list<std::string>& colNames) : m_fileName(fileName), m_colNames(colNames) {}
    CSVReadWrite(const std::string& fileName, size_t rows) : m_fileName(fileName), m_rowCount(rows) {}

    inline void SetColName(const std::vector<std::string>& val)
	{ std::move(begin(val), end(val), back_inserter(m_cols)); }
    inline std::vector<std::string> GetColName() { return m_cols; }

    inline size_t GetRowCounts() { return m_rowCount; }

    inline T& GetRowAt(size_t index) { return arrOfObj[index]; }

    bool ReadCSV()
    {
        std::ifstream infile;
        infile.open(m_fileName);
        if (!infile.is_open())
        {
            std::cout << "file does not exist";
            return false;
        }

		std::string line;
		if (!m_rowCount)
		{
			while (std::getline(infile, line))
				++m_rowCount;

            infile.clear();
            infile.seekg(0, std::ios::beg);
		}
        arrOfObj = new T[m_rowCount];

        //skipping column names

        std::getline(infile, line);
        std::stringstream lineStream(line);
        while(std::getline(lineStream, line, ','))
        {
            m_cols.emplace_back(line);
        }

        int index = -1;
        while (std::getline(infile, line))
        {
            std::stringstream lineStream(line);
            
            arrOfObj[++index] << lineStream;
        }
        m_rowCount = index + 1;

        return true;
    }

    void WriteCSV(T& container)
    {
        std::ofstream outfile;
        outfile.open(m_fileName);

        if (!outfile.is_open())
        {
            std::cerr << "fail to write a file";
            return;
        }

        for (auto it : m_colNames)
            outfile << it << ",";
        outfile << std::endl;

        outfile << container;
    }

    ~CSVReadWrite()
    {
        delete[] arrOfObj;
    }
};

MeanGoalPerGame& operator<< (MeanGoalPerGame& obj, std::stringstream& lineStream)
{
    std::string cell;
    if(std::getline(lineStream, cell, ','))
    {
        obj.SetTeamName(cell);
        
        if (std::getline(lineStream, cell, ','))
        {
            obj.SetMean(stod(cell));
        }
    }
    return obj;
}

/*
template <typename... T>
class CSV
{
    std::tuple<std::vector<T>...> m_vectors;
    std::vector<std::string> m_colNames;
    const size_t m_size = sizeof...(T);
    static_assert(sizeof...(T) >= 1, "Column numbers are too small!");

public:

    constexpr explicit CSV(const std::initializer_list<std::string> &colNames) : m_colNames(colNames)
    {
        if (m_colNames.size() != sizeof...(T))
            throw;
    }

    size_t getColSize() { return m_size; }
    size_t getRowSize() { return std::get<1>(m_vectors).size(); }

    double GetValue(int row, int col)
    {
        if (col <= m_size && row <= std::get<1>(m_vectors).size())
            return std::get<1>(m_vectors)[row];
        else
            throw;
    }

    std::string GetValue(int row)
    {
        if (row <= std::get<0>(m_vectors).size())
            return std::get<0>(m_vectors)[row];
        else
            throw;
    }

    CSV(const CSV &) = delete;
    CSV &operator=(const CSV &) = delete;
    CSV(const CSV &&) = delete;
    CSV &&operator=(const CSV &&) = delete;

    void ReadCSVFile(const std::string& fileName)
    {
        std::ifstream infile;
        infile.open(fileName);
        if (!infile.is_open())
        {
            std::cout << "file does not exist";
            return;
        }

        std::string line;
        std::string cell;

        //skipping column names
        std::getline(infile, cell);
        
        while (std::getline(infile, line))
        {
            std::cout.fill(' ');
            std::cout.width(35);
            std::stringstream lineStream(line);
            int index = 0;

            while (std::getline(lineStream, cell, ',') && index < m_size)
            {
                std::get<0>(m_vectors).emplace_back(cell);
                std::cout << std::left << cell << "    ";

                if (std::getline(lineStream, cell, ','))
                {
                    std::get<1>(m_vectors).emplace_back(stod(cell));
                    std::cout << cell ;
                }
                index = 0;
            }
            std::cout << std::endl;
        }
        return;
    }
};
*/

#endif