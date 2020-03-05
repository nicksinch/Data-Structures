#pragma once

#include <list>

#include "Hash.h"

class ChainingHash : public Hash
{
private:
    size_t ChainsCount;
    std::list<int> * pChains;

public:
    ChainingHash(HashingFunction* pHashingFunction, size_t ChainsCount);

    virtual ~ChainingHash();

    bool Add(const int Key) override;

    bool Search (const int Key) override;

    void PrintInfo() const override;
};
