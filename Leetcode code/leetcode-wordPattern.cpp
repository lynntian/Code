#include <string>
#include <iostream>
#include <map>

using namespace std;
class Solution {
public:
    static bool wordPattern(string pattern, string str) {
        if(pattern.empty() && str.empty())
        {
            return true;
        }
        else if(pattern.empty() || str.empty())
        {
            return false;
        }
        //spliting str
        std::map<char, string> maps;
        int index = 0;
        auto patternLen = pattern.length();
        auto strLen = str.length();
        auto returnIndex = -1;
        for(int i=0; i< patternLen; i++)
        {
            auto matchingStr = getMatching(str, index, strLen, returnIndex);
            cout << "Matching str: " << matchingStr << endl;
            cout << "Return index: " << returnIndex << endl;
            if(matchingStr == "") return false;
            index = returnIndex +1;
            cout << "Index: " << index << endl;
            returnIndex = -1;
            auto res = maps[pattern.at(i)] == "";
            cout<< "matching map : " << res << endl;
            if(maps[pattern.at(i)] == "")
            {
                maps[pattern.at(i)] = matchingStr;   
            }
            else if(maps[pattern.at(i)] != matchingStr)
            {
                return false;
            }
        }
        return true;
        
    }
    
    //get the string until space from startindex
    static string getMatching(string str, int startIndex, int len, int& lastindex)
    {
        auto curIndex = startIndex;

        while((curIndex < len ) && (str.at(curIndex) != ' '))
        {
            cout << "Cur char: " << str.at(curIndex) << endl;
            curIndex++;
        }
        
        if( startIndex != curIndex && curIndex <= len)
        {
            lastindex = curIndex;
            curIndex--;
            return str.substr(startIndex, curIndex-startIndex+1);
        }
        lastindex = -1; 
        return "";
    }
};

int main()
{
    Solution::wordPattern("abba", "dog cat DUM dog");
    return 1;
}