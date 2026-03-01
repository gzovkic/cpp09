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

void printPairs(std::vector<std::pair<int,int>> &pairs)
{
    for (size_t i = 0; i < pairs.size(); i++)
        std::cout << "{" << pairs[i].first << "," << pairs[i].second << "} ";
    std::cout << std::endl;
}

void fordJohnson(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;


        
    bool hasStraggler = false;
    if(arr.size() % 2 != 0)
        hasStraggler = true;

    int straggler = -1;
    if (hasStraggler)
        straggler = arr.back();

    std::vector<std::pair<int, int>> pairs;
    size_t limit = arr.size();
    if (hasStraggler)
        limit = arr.size() - 1;

    for (size_t i = 0; i + 1 < limit; i += 2)
    {
        if (arr[i] >= arr[i + 1])
            pairs.push_back({arr[i], arr[i + 1]});
        else
            pairs.push_back({arr[i + 1], arr[i]});
    }

    std::cout << "--- going down ---" << std::endl;
    std::cout << "arr:   "; printVector(arr);
    std::cout << "pairs: "; printPairs(pairs);

    std::vector<int> bigs;
    for (const std::pair<int, int> &p : pairs)
        bigs.push_back(p.first);
    std::cout << "bigs:  "; printVector(bigs);

    fordJohnson(bigs);

    std::cout << "--- coming back up ---" << std::endl;
    std::cout << "bigs sorted: "; printVector(bigs);


    std::map<int, int> bigToSmall;
    for (const std::pair<int, int> &p : pairs)
        bigToSmall[p.first] = p.second;

    pairs.clear();
    for (int big : bigs)
        pairs.push_back({big, bigToSmall[big]});
    std::cout << "pairs realigned: "; printPairs(pairs);

    std::vector<int> chain;
    chain.push_back(pairs[0].second);
    for (const std::pair<int, int> &p : pairs)
        chain.push_back(p.first);
    std::cout << "chain start: "; printVector(chain);

    std::vector<size_t> order = jacobsthalOrder(pairs.size());
    for (size_t idx : order)
    {
        int toInsert = pairs[idx - 1].second;
        int boundVal = pairs[idx - 1].first;
        auto boundPos = std::find(chain.begin(), chain.end(), boundVal);
        auto pos      = std::lower_bound(chain.begin(), boundPos, toInsert);
        chain.insert(pos, toInsert);
        std::cout << "inserted " << toInsert << " (bound=" << boundVal << ") -> chain: "; printVector(chain);
    }

    if (hasStraggler)
    {
        auto pos = std::lower_bound(chain.begin(), chain.end(), straggler);
        chain.insert(pos, straggler);
    }
    arr = chain;
    std::cout << "arr = chain: "; printVector(arr);
    std::cout << std::endl;
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