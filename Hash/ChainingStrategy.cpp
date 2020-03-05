
#include <iostream>
#include <algorithm>

#include "ChainingStrategy.h"

ChainingHash :: ChainingHash (HashingFunction* pHashingFunction, size_t ChainsCount) :
Hash(pHashingFunction), ChainsCount(ChainsCount)
{
    pChains = new std::list<int>[ChainsCount];
}

ChainingHash :: ~ChainingHash()
{
    delete [] pChains;
};

bool ChainingHash :: Add(const int Key)
{
    int HashValue = pHashingFunction->CalculateHashValue(Key); // Result from hashing value

    pChains[HashValue].push_back(Key);

    return true;
}

bool ChainingHash :: Search(const int Key)
{
    int HashValue = pHashingFunction->CalculateHashValue(Key); // Taking the slot of the table

    for(auto it = pChains[HashValue].cbegin(); it != pChains[HashValue].cend(); ++it)
    {
        if( *it == Key)
            return true;
    }
    return false;
}

void ChainingHash::PrintInfo() const
{
    size_t maxChainSize = pChains[0].size();
    size_t sumOfSizes = pChains[0].size();
    size_t minChainSize = pChains[0].size();

    for(size_t i = 1; i < ChainsCount; i++)
    {
        size_t size = pChains[i].size();

        sumOfSizes += size;
        maxChainSize = std::max(maxChainSize, size);
        minChainSize = std::min(minChainSize, size);
    }

    // NOTE: Microsoft specific. Assumes we are storing int elements
    // and  using the default allocator.
    static const size_t stlListNodeSize = sizeof(std::list<int>*);

    size_t memoryUsed =
            sizeof(*this) +  // object size
            sizeof(std::list<int>) * ChainsCount + // vector of lists
            sumOfSizes * stlListNodeSize; // Nodes allocated by the lists

    size_t dataSize = sumOfSizes * sizeof(int);
    size_t overhead = ((memoryUsed - dataSize) * 100) / memoryUsed;

    std::cout
            << "Chaining Resolution stats:"
            << "\n   - Max chain size: " << maxChainSize
            << "\n   - Avg chain size: " << (sumOfSizes / ChainsCount)
            << "\n   - Min chain size: " << minChainSize
            << "\n   - std::list node size: " << stlListNodeSize;

    PrintCommonInfo(sumOfSizes, memoryUsed);
}
