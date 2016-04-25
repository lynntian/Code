#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

#pragma loop(hint_parallel(8))

// ?? 
//libc++abi.dylib: terminating with uncaught exception of type std::out_of_range: stoull: out of range
//Abort trap: 6



class Solution{
public:
    static void getinput(string filename, int& n, int& j)
    {
        string line;
        ifstream inFile(filename);

        if(inFile.is_open())
        {
            //first line is # of test cases
            getline(inFile, line);
            auto t = stoi(line);

            getline(inFile, line);
            auto index = line.find(' ');
            n = stoi(line.substr(0, index));
            j = stoi(line.substr(index+1, line.length()));
        }
    }

    static void stringToNumber(string str, int N, int base, unsigned long long& out)
    {
        out = 0ULL;
        auto counter = N-1; // N is length of str
        for(auto& c : str)
        {
            out += (c - '0') * pow(base, counter--);
        }
    }

    static void stringGetNumbers(string str, int N, vector<unsigned long long>& vecOut)
    {
        for(int i= 2; i < 10; i++)
        {
            auto tmp = 0ULL;
            stringToNumber(str, N, i, tmp);
            vecOut.push_back(tmp);
        }
        vecOut.push_back(stoull(str));
    }

    static void loadPrimes(std::vector<unsigned long long>& v)
    {
        auto primeFile = "primeNumbers.txt";

        string line;
        ifstream inFile(primeFile);

        if(inFile.is_open())
        {
            while(getline(inFile, line))
            {
                auto primeVec = std::vector<unsigned long long>();
                parseVector(line, primeVec);
            }
        }
    }

    /*
    static bool binarySearch(unsigned long long target, std::vector<unsigned long long>& v)
    {
        return binary_search(v.begin(), v.end(), target);
    }
    */

    static void parseVector(string line, vector<unsigned long long>& out)
    {
        stringstream ss(line);
        string buf;
        while(ss >> buf)
        {
            out.push_back( stoull(buf));
        }
    }

    //Look up to see if this number is prime, return true if prime
    //is return false, divisor will be provided.
    static bool isPrime(unsigned long long number, unsigned long long& divisor)
    {
        bool isPrime = true;
        auto upperbound = sqrt(number);
        if(number == 1 || number == 2) return true;
        if(number % 2 == 0)
        {
            divisor = 2;
            return false;
        }
        for(auto i = 3ULL; i <= upperbound; i+=2)
        {
            if(number % i == 0)
            {
                isPrime = false;
                divisor = i;
                break;
            }
        }
        return isPrime;
    }


    //pre process, store all prime numbers in file, up to max of unsigned long long (ULLONG_MAX)
    //output file primeNumbers.txt
    //if this number is not prime, output this number and it's divisor speparated by spaces nonPrimes.txt
    static void findPrimes()
    {
        auto primeFile = "primeNumbers.txt";
        //auto nonPrimes = "nonPrimes.txt";
        ofstream pf; //ofstream pnf;
        pf.open (primeFile);
        //pnf.open(nonPrimes);
        for(unsigned long long i = 1ULL; i < ULLONG_MAX; i++)
        {
            auto divisor = 0ULL;
            if(isPrime(i, divisor))
            {
                //write to primeFile
                pf << i << " ";
            }
            //else
            //{
            //    pnf << i << " " << divisor << " ";
            //}
        }
        pf.close();
        //pnf.close();
    }

    static void mainProcess()
    {
        //read in file, generate numbers and produce output
        int N = 0;
        int J = 0;
        auto vec = std::vector<vector<unsigned long long>>();
        getinput("C-large.in", N, J);

        // have a buffer of found non-primes and their divisors
        auto buffer = unordered_map<unsigned long long, unsigned long long>();
        //construct base n
        //start end are "1", n-2 digits in the middle can be represent as binary increse
        auto bin = std::vector<int>(N-2, 0);
        auto resCounter = 1;
        bool skipFirst = true;
        cout << "Case #" << "1" << ": " << endl;
        while(resCounter <= J)
        {
            if(!skipFirst)
                increaseByOne(bin);
            else
                skipFirst = false;

            stringstream ss;
            ss << "1";
            for(auto& it : bin)
            {
                ss << to_string(it);
            }
            ss << "1";
            auto curStr = ss.str();
            //cout << "Current N: " << curStr << endl;

            auto checkNumbers = vector<unsigned long long>();
            stringGetNumbers(curStr, N, checkNumbers);

            auto outDivisors = vector<unsigned long long>();
            if(areAllNonPrime(checkNumbers, outDivisors, buffer))
            {
                cout << curStr << " ";
                printVec(outDivisors);
                resCounter++;
            }
        }

    }

    //return false if any of the numbers are prime
    static bool areAllNonPrime(vector<unsigned long long> in, vector<unsigned long long>& outDivisors, unordered_map<unsigned long long, unsigned long long> buf)
    {
        for(auto inN : in)
        {
            auto tmp = 0ULL;
            //in buffer is non prime, push divisor and move on
            if(buf.count(inN) == 1)
            {
                outDivisors.push_back(buf[inN]);
                continue;
            }

            if(isPrime(inN, tmp))
            {
                return false;
            } 
            else
            {
                outDivisors.push_back(tmp);
                buf[inN] = tmp;
            }
        }
        return true;
    }

    static void printVec(std::vector<unsigned long long> v)
    {
        for(auto n : v)
            {
                cout << n << " ";
            }
            cout << endl;
    }

    static void increaseByOne(vector<int>& bin)
    {
        auto carry = true;
        for(int i = bin.size()-1; i>=0; i--)
        {
            if(bin[i] == 1 && carry)
            {
                bin[i] = 0;
            }
            else if(bin[i] == 0 && carry)
            {
                bin[i] = 1;
                carry = false;
            }
            else
            {
                return;
            }
        }
    }

    static void testString()
    {
        auto N = 6;
        auto curStr = "111111";
        auto buffer = unordered_map<unsigned long long, unsigned long long>();
        //cout << "Current N: " << curStr << endl;

        auto checkNumbers = vector<unsigned long long>();
        stringGetNumbers(curStr, N, checkNumbers);

        auto outDivisors = vector<unsigned long long>();
        if(areAllNonPrime(checkNumbers, outDivisors, buffer))
        {
            cout << "Case #" << "1" << ": " << endl;
            cout << curStr << " ";
            printVec(outDivisors);
            //resCounter++;
        }
    }
};


int main()
{
    //Pre process, generate prime numbers
    //Solution::findPrimes();

    Solution::mainProcess();
    //Solution::testString();
    return 0;
}