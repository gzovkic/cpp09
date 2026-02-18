#include "BitcoinExchange.hpp"

std::string parseDate(std::string line)
{
    (void)line;
    return (NULL);
}

void bitcoinExchange(std::string fileName)
{
    std::ifstream inputfile(fileName);
    if(!inputfile.is_open())
    {
        std::cerr << RED << "Error: could not open the file!" << RESET << std::endl;
        return ;
    }

    std::string line;

    std::getline(inputfile, line);
    while(std::getline(inputfile, line))
    {
        std::string date;
        // std::string value;

        std::cout << line << std::endl;
        date = parseDate(line);
        // value = parseValue(line);
    }
}