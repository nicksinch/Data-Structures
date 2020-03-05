/*
    A very simple implementation of a Hash Table using chaining
    as collision resolution technique just to get the idea.
    Source : GeeksForGeeks
*/

#include <iostream>
#include <list>

using namespace std;

class Hash
{
    int Slots; // Number of slots in the hash table

    list<int> * Table;
public:
    Hash(int Slots);
    void Add(int Key);
    void Delete(int Key);
    int HashFunction(int Key); // Using divison method, maps key to a particular value

    void DisplayHash() const;
};
Hash::Hash(int Slots) : Slots(Slots)
{
    Table = new list<int>[Slots];
}

int Hash::HashFunction(int Key)
{
    return Key % Slots;
}

void Hash::Add(int Key)
{
    int Index = HashFunction(Key);
    Table[Index].push_back(Key);
}

void Hash::Delete(int Key)
{
    int Index = HashFunction(Key);

    std::list<int>::iterator It;
    for(It = Table[Index].begin(); It != Table[Index].end(); ++ It)
    {
        if(*It == Key)
            break;
    }

    if(It != Table[Index].end())
        Table[Index].erase(It);
}
void Hash::DisplayHash() const {
    for (int i = 0; i < Slots; i++) {
        cout << i;
        for (auto x : Table[i])
            cout << " ---> " << x;
        cout << endl;
    }
}

int main()
{
    int arrOfInts[] = {15,11,27,8,12};
    int ArrOfIntsSize = sizeof(arrOfInts) / sizeof(arrOfInts[0]);

    Hash H(7);
    // Creates a Hash Table with 7 slots, so function is key mod 7

    // Inserting all the array elements;

    for(int i = 0; i < ArrOfIntsSize; ++i)
        H.Add(arrOfInts[i]);

    H.DisplayHash();
}



