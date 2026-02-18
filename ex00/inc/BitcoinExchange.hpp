#pragma once 

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[37m"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iterator>
#include <exception>
#include <vector>
#include <map>

class btc
{
    public:
        btc();
        ~btc();
        btc(const btc &other);
        btc& operator=(const btc &other);
        void addData(std::string date, int value);

    private:
        std::map<std::string, float> data;
};

void bitcoinExchange(std::string fileName);
