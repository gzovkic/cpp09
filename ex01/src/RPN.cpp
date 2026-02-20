#include "RPN.hpp"

void RPN(char *str)
{
    std::istringstream ss(str);
    std::string token;
    std::stack<int> stack;

    while(ss >> token)
    {
        if(token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
            {
                std::cerr << RED << "Error" << RESET << std::endl;
                return ;
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            if(token == "+")
                stack.push(a + b);
            if(token == "-")
                stack.push(a - b);
            if(token == "*")
                stack.push(a * b);
            if(token == "/")
                stack.push(a / b);
        }
        else
        {
            try
            {
                stack.push(std::stoi(token));
            }
            catch (std::exception &e)
            {
                std::cerr << RED << "Error" << RESET << std::endl;
                return ;
            }
        }
    }
    if (stack.size() != 1)
        std::cerr << RED << "Error" << RESET << std::endl;
    else
        std::cout << stack.top() << std::endl;
}
