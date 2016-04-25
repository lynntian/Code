#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

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
        cout << "outside: "<<outsize << endl;
        out = vector<int>(outsize, 0);
        
        int i = as - 1;
        int j = bs - 1;
        int counter = outsize - 1;
        while(i >= 0 || j >=0)
        {
            auto tmp = 0;
            if(i >= 0 && j >= 0)
            {
                cout << "a: " << a[i] << " b: " << b[j] << " carry: " << carry << endl;
                tmp = a[i] + b[j] + carry;

            }
            else if( i >= 0)
            {
                tmp = a[i] + carry;
            }
            else if(j >=0 )
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
            cout <<"tmp: " << tmp << endl;
            out[counter] = tmp;
            counter--;
            i--; j--;
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
        for(int i= size-1; i >= 0; i--)
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
            for(int i = 1; i<resVec.size(); i++)
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
        for(int i= size-1; i >= 0; i--)
        {
            auto tmp = in;
            mulWithSingleDigit(tmp, in[i]);
            shiftleft(tmp, size -1 -i);

            resVec.push_back(tmp);
            cout << "tmp: ";
            print(tmp);
        }
        if(resVec.size() != 0)
        {
            out = resVec[0];
            for(int i = 1; i<resVec.size(); i++)
            {
                auto tmp = vector<int>();
                cout << "out: " ;
                print(out);
                cout << "resi: " ;
                print(resVec[i]);

                add(out, resVec[i], tmp);
                //print(out);
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
        for(int i = in.size() -1; i >=0; i--)
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

int main() {
    auto out = vector<int>();
    BigNum::add("2936", "22020", out);

    BigNum::print(out);
    out.clear();
    //BigNum::pow2("734", out);
    //BigNum::print(out);
    return 0;
}
