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
    this->data[date] = value;
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

bool isValidDate(std::tuple<int, int, int> date)
{
    struct tm t = {};
    t.tm_year = std::get<0>(date) - 1900;
    t.tm_mon = std::get<1>(date) - 1;
    t.tm_mday = std::get<2>(date);

    struct tm original = t;
    mktime(&t);

    return (t.tm_year == original.tm_year &&
            t.tm_mon  == original.tm_mon  &&
            t.tm_mday == original.tm_mday);
}

btc getDatabase(void)
{
    btc bitcoinData;
    std::ifstream dataFile("data.csv");
    if(!dataFile.is_open())
    {
        std::cerr << RED << "Error: could not open data.csv file!" << RESET << std::endl;
        return (btc());
    }
    std::string line;
    std::getline(dataFile, line);
    while(std::getline(dataFile, line))
        parseData(bitcoinData, line);
    dataFile.close();
    return(bitcoinData);
}

float btc::getbtcprice(std::tuple<int, int, int> date)
{
    auto it = this->data.lower_bound(date);

    if(it != this->data.end() && it->first == date)
        return (it->second);

	if(it == this->data.begin())
		return (-1);
	--it;
	return (it->second);
}

void    parseInput(btc &bitcoinData, std::string line)
{
    std::regex pattern("^(\\d{4})-(\\d{2})-(\\d{2}) \\| (-?[\\d.]+)$");
    std::smatch matches;

    if(!std::regex_match(line, matches, pattern))
    {
        std::cerr << RED << "Error: bad input => " << line << RESET << std::endl;
        return ;
    }

    int year = std::stoi(matches[1]);
    int month = std::stoi(matches[2]);
    int day = std::stoi(matches[3]);
    float value = std::stof(matches[4]);

    std::tuple<int, int, int> date = std::make_tuple(year, month, day);

    if(!isValidDate(date))
    {
        std::cerr << RED << "Error: bad input => " << line << RESET << std::endl;
        return ;
    }
    if(value < 0)
    {
        std::cerr << RED << "Error: not a positive number." << RESET << std::endl;
        return ;
    }
    if(value > 1000)
    {
        std::cerr << RED << "Error: too large a number." << RESET << std::endl;
        return ;
    }

    float btcPrice = bitcoinData.getbtcprice(date);
	if (btcPrice < 0)
	{
    	std::cerr << RED << "Error: no data for this date." << RESET << std::endl;
    	return;
	}
	std::cout << std::get<0>(date) << "-"
       		  << std::setw(2) << std::setfill('0') << std::get<1>(date) << "-"
    	      << std::setw(2) << std::setfill('0') << std::get<2>(date)
        	  << " => " << std::defaultfloat << value << " = "
          	  << std::fixed << std::setprecision(2) << (value * btcPrice) << std::endl;
}

void bitcoinExchange(std::string fileName)
{
    btc bitcoinData = getDatabase();
    // bitcoinData.printAllData();
    
    std::ifstream inputfile(fileName);
    if(!inputfile.is_open())
    {
        std::cerr << RED << "Error: could not open " << fileName << "!" << RESET << std::endl;
        return ;
    }
    std::string inputline;
    std::getline(inputfile, inputline);
    while(std::getline(inputfile, inputline))
        parseInput(bitcoinData, inputline);
    
    inputfile.close();
}