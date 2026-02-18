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

void btc::addData(std::string date, float value)
{
    this->data[date] = value;
}

void btc::printAllData()
{
    for (auto it = this->data.begin(); it != this->data.end(); ++it)
    {
        std::cout << it->first << " " << std::fixed << std::setprecision(2) << it->second << std::endl;
    }
}

void parseData(btc &bitcoinData, std::string line)
{
    std::string::iterator iter1 = std::find(line.begin(), line.end(), '-');
    std::string year = std::string(line.begin(), iter1);
    std::string::iterator iter2 = std::find(iter1 + 1, line.end(), '-');
    std::string month = std::string(iter1 + 1, iter2);
    iter1 = std::find(iter2 + 1, line.end(), ',');
    std::string day = std::string(iter2 + 1, iter1);

    // std::cout << year << "-" << month << "-" << day << std::endl;
    std::string date = std::string(line.begin(), iter1);

    std::string value = std::string(iter1 + 1, line.end());

    bitcoinData.addData(date, std::strtof(value.c_str(), NULL));
}

void bitcoinExchange(std::string fileName)
{
    std::ifstream inputfile(fileName);
    if(!inputfile.is_open())
    {
        std::cerr << RED << "Error: could not open the file!" << RESET << std::endl;
        return ;
    }

    btc bitcoinData;
    std::string line;
    std::getline(inputfile, line);
    while(std::getline(inputfile, line))
    {
        parseData(bitcoinData, line);
    }
    bitcoinData.printAllData();

    inputfile.close();
}