#include "PmergeMe.hpp"

int parseNumber(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if(!isdigit(str[i]))
        {
            std::cerr << RED << "Error" << RESET << std::endl;
            exit(1);
        }
    }
    long num = std::stol(str);
    if(num <= 0 || num > INT32_MAX)
    {
        std::cerr << RED << "Error" << RESET << std::endl;
        exit(1);
    }
    return(static_cast<int>(num));

}

void printVector(std::vector<int> numbers)
{
    std::cout << "Before: ";
    for (int num : numbers)
        std::cout << num << " ";
    std::cout << std::endl;
}

void PmergeMe(char *argv[])
{
    std::vector<int> numbers;

    for(int i = 1; argv[i] != NULL; i++)
        numbers.push_back(parseNumber(argv[i]));

    printVector(numbers);
}