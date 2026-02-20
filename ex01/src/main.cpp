#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if(argc > 1)
        RPN(argv[1]);
    else
        std::cerr << RED << "Error: wrong amount of arguments" << RESET << std::endl;
	return (0);
}

