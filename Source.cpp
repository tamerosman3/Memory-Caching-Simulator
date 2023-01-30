#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <bitset>

using namespace std;

int L, S, cacheC;
int blocks;

int misses = 0;
int hits = 0;
double hitRate = 0;
double missRate = 0;
int accesses = 0;
double AMAT = 0;

int indSize;

int misses_d = 0;
int hits_d = 0;
double hitRate_d = 0;
double missRate_d = 0;
int accesses_d = 0;
double AMAT_d = 0;


string decToBinary(int n)
{
    std::string out = std::bitset<32>(n).to_string();
    out = out.substr(32 - indSize, indSize);
    return out;
}



void getParts(string address, string& tag, string& index, string& disp, string& iORd)
{
    // ezai hn2sm el address eli da5l wel equations
    int offSize, tagSize;
    indSize = log2(blocks);
    offSize = log2(L);
    tagSize = 32 - indSize - offSize;

    tag = address.substr(0, tagSize);
    index = address.substr(tagSize, indSize);
    disp = address.substr(tagSize + indSize, offSize);
    iORd = address.substr(address.size() - 1, 1);
    /*
        cout << "tag is " << tag << endl;
        cout << "index is " << index << endl;
        cout << "offset is " << disp << endl;
        */
}


void accessCache(string tag, string index, map<string, string>& DM, map<string, string>& DM_d, string iORd)
{
    if (iORd == "d")
    {
        accesses_d += 1;
        if (DM_d.find(index) != DM_d.end())
        {
            if (DM_d[index] == tag)
            {
                // if the valid bit is 1 and the required to access is the same
                // as the one in the cache
                hits_d += 1;
                missRate_d = double(misses_d) / accesses_d;
                //cout << "miss rate here is " << missRate << endl;
                //cout << "misses here is " << misses << endl;
                hitRate_d = double(hits_d) / accesses_d;
                //cout << "hit rate here is " << hitRate << endl;
                //cout << "hits here is " << hits << endl;
                AMAT_d = cacheC + (missRate_d * 100);
                //cout << "amat here is " << AMAT << endl;
            }
            else
            {
                // if the valid bit is 1 and the required to access is not the same
                // as the one in the cache
                misses_d += 1;
                missRate_d = double(misses_d) / accesses_d;
                hitRate_d = double(hits_d) / accesses_d;
                AMAT_d = cacheC + (missRate_d * 100);
                DM_d[index] = tag;
            }
        }
        else
        {
            // if the valid bit is 0 and the required to access is not the same
            // as the one in the cache
            misses_d += 1;
            missRate_d = double(misses_d) / accesses_d;
            hitRate_d = double(hits_d) / accesses_d;
            AMAT_d = cacheC + (missRate_d * 100);
            DM_d[index] = tag;
            //cout << "I am here " << endl;
        }
    }
    else if (iORd == "i")
    {
        accesses += 1;
        if (DM.find(index) != DM.end())
        {
            if (DM[index] == tag)
            {
                // if the valid bit is 1 and the required to access is the same
                // as the one in the cache
                hits += 1;
                missRate = double(misses) / accesses;
                //cout << "miss rate here is " << missRate << endl;
                //cout << "misses here is " << misses << endl;
                hitRate = double(hits) / accesses;
                //cout << "hit rate here is " << hitRate << endl;
                //cout << "hits here is " << hits << endl;
                AMAT = cacheC + (missRate * 100);
                //cout << "amat here is " << AMAT << endl;
            }
            else
            {
                // if the valid bit is 1 and the required to access is not the same
                // as the one in the cache
                misses += 1;
                missRate = double(misses) / accesses;
                hitRate = double(hits) / accesses;
                AMAT = cacheC + (missRate * 100);
                DM[index] = tag;
            }
        }
        else
        {
            // if the valid bit is 0 and the required to access is not the same
            // as the one in the cache
            misses += 1;
            missRate = double(misses) / accesses;
            hitRate = double(hits) / accesses;
            AMAT = cacheC + (missRate * 100);
            DM[index] = tag;
            //cout << "I am here " << endl;
        }
    }
}

void Print(map<string, string> DM, map<string, string> DM_d, string iORd)
{
    if (iORd == "i")
    {
        string curr = "";
        for (int i = 0; i < pow(2, indSize); i++)
        {
            curr = decToBinary(i);

            /*
                    cout << "curr is " << curr << endl;
                    for (auto it = DM.begin(); it != DM.end(); it++)
                    {
                        std::cout << it->first    // string (key)
                          << ':'
                          << it->second   // string's value
                          << std::endl;
                    }
                    */

            if (DM.find(curr) != DM.end())
            {
                // valid bit = 1
                cout << curr << ": " << "valid bit is: 1, tag is: " << DM[curr] << endl;
            }
            else
            {
                cout << curr << ": " << "valid bit is: 0" << endl;
            }
        }



        cout << "The number of accesses is " << accesses << endl;
        cout << "The hit rate is " << hitRate << endl;
        cout << "The miss rate is " << missRate << endl;
        cout << "The AMAT is " << AMAT << endl;
    }
    else if (iORd == "d")
    {
        string curr = "";
        for (int i = 0; i < pow(2, indSize); i++)
        {
            curr = decToBinary(i);

            /*
                    cout << "curr is " << curr << endl;
                    for (auto it = DM.begin(); it != DM.end(); it++)
                    {
                        std::cout << it->first    // string (key)
                          << ':'
                          << it->second   // string's value
                          << std::endl;
                    }
                    */

            if (DM_d.find(curr) != DM_d.end())
            {
                // valid bit = 1
                cout << curr << ": " << "valid bit is: 1, tag is: " << DM_d[curr] << endl;
            }
            else
            {
                cout << curr << ": " << "valid bit is: 0" << endl;
            }
        }
        cout << "The number of accesses is " << accesses_d << endl;
        cout << "The hit rate is " << hitRate_d << endl;
        cout << "The miss rate is " << missRate_d << endl;
        cout << "The AMAT is " << AMAT_d << endl;
    }
}




int main()
{
    // {index, {validbit, tag}}
    map<string, string> DM;
    map<string, string> DM_d;


    vector<string> Addresses;
    ifstream input;
    cout << "enter line size: ";
    cin >> L;
    cout << "enter total cache size: ";
    cin >> S;
    cout << "enter the number of cycles needed to access the cache: ";
    cin >> cacheC;

    // calculating the number of blocks in the cache
    blocks = S / L;

    input.open("TC1Addresses.txt");
    if (!input.is_open())
        cout << "Error: file could not be opened" << endl;

    string temp;
    while (!input.eof())
    {
        input >> temp;
        Addresses.push_back(temp);
    }
    input.close();



    for (int i = 0; i < Addresses.size(); i++)
    {
        string tag, index, disp, iORd;
        getParts(Addresses[i], tag, index, disp, iORd);
        accessCache(tag, index, DM, DM_d, iORd);
        cout << "                                   this is the instructions cache" << endl;
        Print(DM, DM_d, "i");
        cout << "                                   this is the data cache" << endl;
        Print(DM, DM_d, "d");



    }

    return 0;
}