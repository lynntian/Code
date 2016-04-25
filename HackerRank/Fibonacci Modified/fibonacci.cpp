#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

class BigNum
{
public:
    BigNum() { }

    ~BigNum() { }
    static void strToNum(string str, vector<int>& out)
    {
        out.clear();
        for(auto& c:str)
        {
            out.push_back( c - '0');
        }
    }

    static void add(string a, string b, vector<int>& out)
    {
        auto va = std::vector<int>();
        auto vb = std::vector<int>();
        strToNum(a, va); strToNum(b, vb);
        add(va, vb, out);
    }

    static void pow2Self(string a, vector<int>& out)
    {
        auto va = vector<int>();
        strToNum(a, va);
        pow2(va, out);
    }

    static void add(vector<int> a, vector<int> b, vector<int>& out)
    {
        int carry = 0;
        out.clear();
        auto as = a.size();
        auto bs = b.size();
        auto outsize = (as > bs ? as : bs);
        //cout << "outside: "<<outsize << endl;
        out = vector<int>(outsize, 0);
        
        unsigned long long i = as - 1;
        unsigned long long j = bs - 1;
        unsigned long long counter = outsize - 1;
        while(i != ULLONG_MAX  || j != ULLONG_MAX)
        {
            auto tmp = 0ULL;
            if(i != ULLONG_MAX && j != ULLONG_MAX)
            {
                //cout << "a: " << a[i] << " b: " << b[j] << " carry: " << carry << endl;
                tmp = a[i] + b[j] + carry;

            }
            else if( i != ULLONG_MAX )
            {
                tmp = a[i] + carry;
            }
            else if(j != ULLONG_MAX )
            {
                tmp = b[j] + carry;
            }

            if(tmp >= 10)
            {
                carry = 1; 
                tmp = tmp % 10;
            }
            else 
            {
                carry = 0;
            }
            //cout <<"tmp: " << tmp << endl;
            out[counter] = tmp;

            if(counter != ULLONG_MAX)
                counter--;
            if(i != ULLONG_MAX)
                i--; 
            if(j != ULLONG_MAX)
                j--;
        }
        //reverse(out.begin(), out.end());
        if(carry == 1)
        {
            out.insert(out.begin(), carry);
        }
     }

    static void pow2Self(vector<int>& in /* in  & out*/)
    {
        auto size = in.size();
        auto resVec = vector<vector<int>>();
        for(unsigned long long i= size-1; i != ULLONG_MAX; i--)
        {
            auto out = in;
            mulWithSingleDigit(out, in[i]);
            shiftleft(out, size -1 -i);

            resVec.push_back(out);
        }
        in.clear();
        if(resVec.size() != 0)
        {
            in = resVec[0];
            for(unsigned long long i = 1; i<resVec.size(); i++)
            {
                auto out = vector<int>();
                add(in, resVec[i], out);
                in = out;
            }
        }
    }

    static void pow2(vector<int>& in, vector<int>& out)
    {
        auto size = in.size();
        auto resVec = vector<vector<int>>();
        for(unsigned long long i= size-1; i != ULLONG_MAX; i--)
        {
            auto tmp = in;
            mulWithSingleDigit(tmp, in[i]);
            shiftleft(tmp, size -1 -i);

            resVec.push_back(tmp);
            //cout << "tmp: ";
            //print(tmp);
        }
        if(resVec.size() != 0)
        {
            out = resVec[0];
            for(unsigned long long i = 1; i<resVec.size(); i++)
            {
                auto tmp = vector<int>();
                //cout << "out: " ;
                //print(out);
                //cout << "resi: " ;
                //print(resVec[i]);

                add(out, resVec[i], tmp);
                //print(tmp);
                out = tmp;
            }
        }
    }

    static void mul(vector<int>& in, vector<int>& mul, vector<int>& out)
    {

    }

    static void shiftleft(vector<int>& in, int numofshifts)
    {
        if(numofshifts == 0 ) return;
        auto tmp = vector<int>(numofshifts, 0);
        in.insert(in.end(), tmp.begin(), tmp.end());
    }

    static void sub(BigNum* other)
    {
        //todo
    }

    static string print(vector<int> num)
    {
        string ret;
        for(auto& c : num)
        {
            cout << c;
            ret += to_string(c);
        }
        cout << endl;
        return ret;
    }

    static void mulWithSingleDigit(vector<int>& in, int dig)
    {
        int carry = 0;
        for(unsigned long long i = in.size() -1; i != ULLONG_MAX; i--)
        {
            auto tmp = in[i] * dig + carry;
            if(tmp >= 10)
            {
                carry = tmp / 10;
                tmp = tmp % 10;
            }
            else
            {
                carry = 0;
            }
            //cout << "tmp: " << tmp << " carry: " << carry << endl;
            in[i] = tmp;
        }
        if(carry != 0)
        {
            in.insert(in.begin(), carry);
        }
    } 

};

void parseInput(string str, int& a, int& b, int& n)
{
    auto index = str.find(' ');
    a = stoi( str.substr(0, index));
    auto nextIndex = str.find(' ', index+1);
    b = stoi( str.substr(index+1, nextIndex));
    n = stoi( str.substr(nextIndex+1, str.length()));
}

void finb(int a, int b, int n)
{
    auto va = vector<int>();
    BigNum::strToNum(to_string(a), va);
    auto vb = vector<int>();
    BigNum::strToNum(to_string(b), vb);

    for(int i = 3; i <= n; i++)
    {
        auto tmp = vector<int>();
        BigNum::pow2(vb, tmp);
        //cout << "tmp: " ;
        //BigNum::print(tmp);
        auto out = vector<int>();
        BigNum::add(tmp, va, out);
        //cout << "out: " ;
        //BigNum::print(out);

        va = vb;
        vb = out;
    }
    BigNum::print(vb);
}

int main() {
    string line;
    getline(cin, line);
    int a, b, n;
    parseInput(line, a, b, n);
    
    finb(a, b, n);
    return 0;
}
