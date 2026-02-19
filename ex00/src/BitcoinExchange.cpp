#include "BitcoinExchange.hpp"

btc::btc()
{
}

btc::~btc()
{
}

btc::btc(const btc &other)
{
    this->data = other.data;
}

btc& btc::operator=(const btc &other)
{
    if(this == &other)
        return(*this);
    this->data = other.data;
    return(*this);
}

void btc::addData( std::tuple<int, int, int> date,  float value)
{
    this->data.insert(std::make_pair(date, value));
}

void btc::printAllData()
{
    std::cout << GREEN << "Printing All Data" << RESET << std::endl;

    for (auto it = this->data.begin(); it != this->data.end(); ++it)
    {
        int year = std::get<0>(it->first);
        int month = std::get<1>(it->first);
        int day = std::get<2>(it->first);

        std::cout << year << "-"
                  << std::setw(2) << std::setfill('0') << month << "-"
                  << std::setw(2) << std::setfill('0') << day
                  << " | "
                  << std::fixed << std::setprecision(2) << it->second << std::endl;
    }
}

void parseData(btc &bitcoinData, std::string line)
{
    float value;
    int year, month, day;
    int result = sscanf(line.c_str(), "%d-%d-%d,%f", &year, &month, &day, &value);

    if (result != 4)
    {
        std::cout << "Error: invalid format in data.csv!\n";
        return ;
    }
    std::tuple<int, int, int> date = std::make_tuple(year, month, day);
    bitcoinData.addData(date, value);
}

bool isValidDate(int year, int month, int day)
{
    struct tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;

    struct tm original = t;
    mktime(&t);

    return (t.tm_year == original.tm_year &&
            t.tm_mon  == original.tm_mon  &&
            t.tm_mday == original.tm_mday);
}

void    parseInput(btc &inputData, std::string line)
{
    float value;
    int year, month, day;
    int result = sscanf(line.c_str(), "%d-%d-%d | %f", &year, &month, &day, &value);

    if (result != 4)
    {
        std::cerr << RED << "Error: invalid format in input.txt!" << RESET << std::endl;
        return ;
    }
    if(!isValidDate(year, month, day))
    {
        std::cerr << RED << "Error: bad input => " << line << RESET << std::endl;
        return ;
    }
    std::tuple<int, int, int> date = std::make_tuple(year, month, day);
    inputData.addData(date, value);
}

void bitcoinExchange(std::string fileName)
{
    std::ifstream dataFile("data.csv");
    if(!dataFile.is_open())
    {
        std::cerr << RED << "Error: could not open data.csv file!" << RESET << std::endl;
        return ;
    }

    btc bitcoinData;
    std::string line;
    std::getline(dataFile, line);
    while(std::getline(dataFile, line))
        parseData(bitcoinData, line);
    bitcoinData.printAllData();

    std::ifstream inputfile(fileName);
    if(!inputfile.is_open())
    {
        std::cerr << RED << "Error: could not open the file!" << RESET << std::endl;
        return ;
    }
    btc inputData;
    std::string inputline;
    std::getline(inputfile, inputline);
    while(std::getline(inputfile, inputline))
        parseInput(inputData, inputline);
    inputData.printAllData();

    inputfile.close();
    dataFile.close();
}