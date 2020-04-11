#include <iostream>
#include <vector>
#include <string>
using namespace std;
double takeEmission(int pos, vector<string> emissions)
{
    int slashes =  1;
    int strLen = emissions[pos].length();
    int i = 0;
    string em;
    while(i < strLen && slashes != 0)
    {
        if(emissions[pos][i]=='-')
            slashes--;
        i++;
    }
    while(i < strLen)
    {
        em+=emissions[pos][i];
        i++;
    }
    return stod(em);
}
int takeKms(int pos, vector<string> itineraries)
{
    int slashes = 2;
    int strLen = itineraries[pos].length();
    int i = 0;
    while(i < strLen && slashes != 0)
    {
        if(itineraries[pos][i]=='-')
            slashes--;
        i++;
    }
    string kms;
    while(itineraries[pos][i]!='-') {
        kms += itineraries[pos][i];
        i++;
    }
    return stoi(kms);

}
string takeAirCraft(int pos, vector<string> itineraries)
{
    int slashes =  3;
    int strLen = itineraries[pos].length();
    int i = 0;
    while(i < strLen && slashes != 0)
    {
        if(itineraries[pos][i]=='-')
            slashes--;
        i++;
    }
    string aircraft;
    while(i < strLen)
    {
        aircraft+=itineraries[pos][i];
        i++;
    }
    return aircraft;
}
bool hasFlight(string origin, string dest, int pos, vector<string> iternaries)
{
    return (iternaries[pos].find(origin) != std::string::npos) && (iternaries[pos].find(dest) != std::string::npos);
}

double takeLeastEmissions(string aircraft, vector<string> emissions)
{
    int i = 0;
    int emissionsLen = emissions.size();
    double minEmission = 0.0,currEmission;
    while(i < emissionsLen)
    {
        if(emissions[i].find(aircraft) != std::string::npos)
        {
            currEmission = takeEmission(i, emissions);
            if(minEmission == 0.0)
                minEmission = currEmission;
        }
        if(currEmission < minEmission)
            minEmission = currEmission;
        i++;
    }
    return minEmission;
}


double solution(vector< string > aircraftEmissions, vector< string > flightItineraries, string origin, string destination) {

    int itinerariesLength = flightItineraries.size();
    int emissionsLength = aircraftEmissions.size();
    int i = 0;
    string aircraft;
    double minEmission;
    bool zeroEmission = false;
    double mostOptimal = 0.0, currOptimal;
    while(i < itinerariesLength)
    {
        if(hasFlight(origin,destination,i,flightItineraries))
        {
            aircraft = takeAirCraft(i, flightItineraries);
            int kms = takeKms(i,flightItineraries);
            minEmission = takeLeastEmissions(aircraft,aircraftEmissions);
            currOptimal = minEmission * kms;
            if(mostOptimal == 0.0)
                mostOptimal = currOptimal;
            if(minEmission == 0.0)
                zeroEmission = true;
        }
        if(currOptimal < mostOptimal && !zeroEmission)
            mostOptimal = currOptimal;
        i++;
    }

    int dummy = (int)(mostOptimal * 100.0);
    mostOptimal = ((double)dummy) / 100.0;
    return mostOptimal;

}

//int main() {
//    vector<string> v1;
//    vector<string> v2;
//
//    v1.push_back("LON-EDI-534-boeing_737");
//    v1.push_back("LON-EDI-534-boeing_787");
//    v1.push_back("-LON-464-embraer_190");
//
//    v2.push_back("boeing_737-0.101");
//    v2.push_back("boeing_747-0.12");
//    string s1 = "LON";
//    string s2 = "EDI";
//
//    double answer = solution(v2,v1,s1,s2);
//    printf("%.2f", answer);
//    //cout<<takeLeastEmissions("boeing_747", v2);
//}
