#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <deque>

using namespace std;
typedef deque<int> BigNum;

void strToNum(string str, BigNum& out)
{
    out.clear();
    for(auto& c:str)
    {
        out.push_back( c - '0');
    }
}

void shiftleft(BigNum& in, int numofshifts)
{
    if(numofshifts == 0 ) return;
    for(int i = 0; i < numofshifts; i++)
    {
        in.push_back(0);
    }
}

void addToFront(BigNum& num, int digit, int times)
{
    if(digit < 10 && times > 0)
    {
        for(int i = 0; i < times; i++)
        {
            num.push_front(digit);
        }
    }
}

string print(BigNum num)
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

void add(BigNum a, BigNum b, BigNum& out)
{
    int carry = 0;
    out.clear();

    auto asize = a.size();
    auto bsize = b.size();
    if(asize > bsize) { addToFront(b, 0, asize - bsize);}
    else if(asize < bsize) {addToFront(a, 0, bsize - asize);}

    auto size = a.size();
    for(int i = size -1; i >=0 ; i--)
    {
        auto tmp = a[i] + b[i] + carry;
        carry = tmp / 10;
        out.push_front(tmp%10);
    }

    if(carry == 1)
    {
        out.push_front(1);
    }
}

void mulWithSingleDigit(BigNum& in, int dig)
{
    int carry = 0;
    for(int i = in.size() -1; i >=0; i--)
    {
        auto tmp = in[i] * dig + carry;

        carry = tmp / 10;
        tmp = tmp % 10;
        //cout << "tmp: " << tmp << " carry: " << carry << endl;
        in[i] = tmp;
    }

    if(carry != 0)
    {
        in.push_front(carry);
    }
} 

void pow2(BigNum& in, BigNum& out)
{
    out.clear();
    auto size = in.size();
    BigNum last;
    for(int i= size-1; i >= 0; i--)
    {
        auto tmp = in;
        mulWithSingleDigit(tmp, in[i]);
        shiftleft(tmp, size -1 -i);

        add(tmp, last, out);
        last = out;
        //cout << "tmp: ";
        //print(tmp);
    }
}

void mul(BigNum& in, BigNum& mul, BigNum& out)
{

}

void sub(BigNum* other)
{
    //todo
}

void add(string a, string b, BigNum& out)
{
    BigNum va;
    BigNum vb;
    strToNum(a, va); strToNum(b, vb);
    add(va, vb, out);
}

void pow2(string a, BigNum& out)
{
    BigNum va;
    strToNum(a, va);
    pow2(va, out);
}

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
    BigNum va;
    strToNum(to_string(a), va);
    BigNum vb;
    strToNum(to_string(b), vb);

    for(int i = 3; i <= n; i++)
    {
        BigNum tmp;
        pow2(vb, tmp);
        //cout << "tmp: " ;
        //BigNum::print(tmp);
        BigNum out;
        add(tmp, va, out);
        //cout << "out: " ;
        //BigNum::print(out);

        va = vb;
        vb = out;
    }
    print(vb);
}

int main() {
    string line;
    getline(cin, line);
    int a, b, n;
    parseInput(line, a, b, n);
    
    finb(a, b, n);
    return 0;
}
