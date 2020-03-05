#pragma once

#include <iostream>

class HashingFunction
{
    public:
        virtual ~HashingFunction() = default;

        virtual int CalculateHashValue(int Key) = 0; // Calculates the hash of an int

};

// The hash value for a specific key K is calculated as K % Mod
class ModHashingFunction : public HashingFunction
{
private:
    int Mod;

public:
    ModHashingFunction(int Mod) : Mod(Mod)
    {

    }
    int CalculateHashValue(int Key) override
    {
        return Key % Mod;
    }
};

class MultiplyMethodHashingFunction : public HashingFunction
{
private:
    int Mod;
    int Multiplier;

public:
    MultiplyMethodHashingFunction(int Mod, int Multiplier) : Mod (Mod), Multiplier(Multiplier)
    {
        // Intentionally Empty
    }
    int CalculateHashValue(int Key) override
    {
        return (Key % Mod) * Multiplier;
    }
};

// A Parent class for all Hash Functions

class Hash
{
protected:
    HashingFunction * pHashingFunction;

public:
    Hash(HashingFunction* pHashingFunction = nullptr) : pHashingFunction(pHashingFunction)
    {
        // Intentionally Empty
    }

    virtual ~Hash() = default;

    virtual bool Add(const int Key) = 0;

    virtual bool Search(const int Key) = 0;

    virtual void PrintInfo() const = 0;

    void PrintCommonInfo(size_t ElementsCount, size_t MemoryUsed) const
    {
        size_t ElementsSize = ElementsCount * sizeof(int);

        size_t Data = (ElementsSize * 100) / MemoryUsed;

        std::cout
                << "\n   - Stored elements: " << ElementsCount
                << "\n   - Space required for elements: " << ElementsCount << " x sizeof(int) = " << ElementsSize << " bytes"
                << "\n   - Memory used: " << MemoryUsed << " byte(s) (~ " << (MemoryUsed / ElementsCount) << " bytes per element)"
                << "\n   - Data vs Representation: " << Data << "% data, " << (100 - Data) << "% representation"
                << std::endl << std::endl;
    }
};

