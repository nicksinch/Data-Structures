/*
    This problem was asked by Amazon.

    Run-length encoding is a fast and simple method of encoding strings.
    The basic idea is to represent repeated successive characters as a single count
    and character. For example, the string "AAAABBBCCDAA" would be encoded as "4A3B2C1D2A".

    Implement run-length encoding and decoding.
    You can assume the string to be encoded have no digits and consists solely
    of alphabetic characters. You can assume the string to be decoded is valid.

    Solution for both functions works in O(n) time.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

void Encode(string Encode)
{
    map<char,int> HashTable;

    int EncodeLen = Encode.size();

    char currLetter, letter=Encode[0];
    HashTable[letter]++;
    string Encoded = "";

    for(int i = 1;i <= EncodeLen;++i)
    {
        currLetter = Encode[i];
        if(currLetter != letter)
        {
            Encoded += to_string(HashTable[letter]);
            Encoded += letter;
            HashTable.erase(letter);
            letter = currLetter;
        }
        HashTable[currLetter]++;
    }
    cout<<"Encoded string: "<<endl<<Encoded<<endl;
}
void Decode(string Decode)
{
    int DecodeLen = Decode.length();
    int i = 0,digit = 0; // i for letter and digit for the times the digits occurs

    cout<<"Decoded string: "<<endl;

    while(i < DecodeLen)
    {
        char letter = Decode.at(i+1);
        int occurences = (Decode[digit]) - '0';
        std::cout<<std::string(occurences,letter);
        digit+=2;
        i+=2;
    }
}
int main()
{
    Encode("AAAABBBCCDAAAOOOO");
    Decode("4A3B2C1D3A4O");
}

