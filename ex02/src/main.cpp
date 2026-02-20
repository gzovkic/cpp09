#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << RED << "Error" << RESET << std::endl;
        return (1);
    }
    PmergeMe(argv);
	return (0);
}

