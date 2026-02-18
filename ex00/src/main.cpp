#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    (void)argv;
    if (argc < 2)
        std::cout << RED << "Error: could not open file." << RESET << std::endl;
    else if (argc > 2)
        std::cout << RED << "Error: too many arguments." << RESET << std::endl;
    else
        bitcoinExchange(static_cast<std::string>(argv[1]));
	return (0);
}

