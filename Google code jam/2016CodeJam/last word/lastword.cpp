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
#include <queue>

using namespace std;

#pragma loop(hint_parallel(8))

class Solution
{
public:
    static void getinput(string filename, int& n, vector<string>& ss)
    {
        string line;
        ifstream inFile(filename);

        if(inFile.is_open())
        {
            //first line is # of test cases
            getline(inFile, line);
            n = stoi(line);

            for(int i=0; i< n; i++)
            {
                getline(inFile, line);
                ss.push_back(line);
            }
        }
    }

    static void lastword(string s, string& out)
    {
        if(s.empty()) return;

        auto vec = vector<string>();
        string res;
        for(auto& c : s)
        {
            auto ch = string(1,c);
            if(res.length() == 0){
                res = ch;
                continue;
            }
            else
                helper(ch, res);
        }
        out = res;

    }

    static void helper(string ch, string& res /*in and out*/)
    {
        if(res.length() == 0) return;

        //two possiblities, chose one
        auto tmp = res;
        res = (tmp +ch) > (ch + tmp) ? (tmp + ch) :(ch + tmp);

        //cout << "return str: " << res << endl;
    }
};

int main(int argc, char const *argv[])
{
    int numofcases = 0;
    auto ss = vector<string>();
    Solution::getinput("A-large.in", numofcases, ss);
    int counter = 1;
    for(auto& s : ss)
    {
        string temp = "";
        Solution::lastword(s, temp);
        cout << "Case #" << counter<< ": "<< temp << endl;
        counter++;
    }
    return 0;
}