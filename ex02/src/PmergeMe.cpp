#include "PmergeMe.hpp"

int parseNumber(const std::string &str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            std::cerr << RED << "Error" << RESET << std::endl;
            exit(1);
        }
    }
    long num = std::stol(str);
    if (num < 0 || num > INT32_MAX)
    {
        std::cerr << RED << "Error" << RESET << std::endl;
        exit(1);
    }
    return static_cast<int>(num);
}

void printVector(std::vector<int> &numbers)
{
    for (int num : numbers)
        std::cout << num << " ";
    std::cout << std::endl;
}

std::vector<size_t> jacobsthalOrder(size_t n)
{
    std::vector<size_t> jac = {1, 3};
    while (jac.back() < n)
        jac.push_back(jac[jac.size() - 1] * 2 + jac[jac.size() - 2]);

    std::vector<size_t> order;
    size_t prev = 1; // a1 is already in chain (free), so start after it
    for (size_t j : jac)
    {
        size_t cur = std::min(j, n);       // clamp to actual number of pairs
        for (size_t k = cur; k > prev; k--) // insert group RIGHT TO LEFT
            order.push_back(k);
        prev = cur;
        if (cur >= n)
            break;
    }
    return order;
}


void fordJohnson(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    bool hasStraggler = false;

    if(arr.size() % 2 != 0)
        hasStraggler = true;
    
    // int straggler = -1;
    // if(hasStraggler)
    //     straggler = arr.back();

    std::vector<std::pair<int, int>> pairs;
    size_t limit = arr.size();
    if (hasStraggler)
        limit = arr.size() - 1;

    // look which on is bigger and then switch if needed else copy the order.
    for (size_t i = 0; i + 1 < limit; i += 2)
    {
        if (arr[i] >= arr[i + 1])
            pairs.push_back({arr[i], arr[i + 1]});
        else
            pairs.push_back({arr[i + 1], arr[i]});
    }

    // create vector for recursion with the big numbers.
    std::vector<int> bigs;
    for (const std::pair<int, int> &p : pairs)
        bigs.push_back(p.first);
    printVector(bigs);
    fordJohnson(bigs);

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int,int> &a, const std::pair<int,int> &b){
        return a.first < b.first;
    });

    std::vector<int> chain;
    chain.push_back(pairs[0].second);
    for (const std::pair<int, int> &p : pairs)
        chain.push_back(p.first);

    std::vector<size_t> order = jacobsthalOrder(pairs.size());
    for (size_t idx : order)
    {
        int toInsert = pairs[idx - 1].second;
        int boundVal = pairs[idx - 1].first;
        auto boundPos = std::find(chain.begin(), chain.end(), boundVal);
        auto pos      = std::lower_bound(chain.begin(), boundPos, toInsert);
        chain.insert(pos, toInsert);
    }

    arr = chain;
}

void PmergeMe(char *argv[])
{
    std::vector<int> numbers;

    for (int i = 1; argv[i] != NULL; i++)
        numbers.push_back(parseNumber(argv[i]));

    std::cout << "before: " << std::endl;
    printVector(numbers);

    fordJohnson(numbers);

    std::cout << "after: " << std::endl;
    printVector(numbers);

}