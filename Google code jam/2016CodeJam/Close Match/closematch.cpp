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


void inputparser(string fileName, int& n, std::vector<pair<string,string>>& strs)
{
	string line;
	ifstream inFile(fileName);

	if(inFile.is_open())
	{
		//first line is # of test cases
		getline(inFile, line);
		n = stoi(line);

		while( getline(inFile, line))
		{
            auto index = line.find(' ');
            auto s1 = line.substr(0, index);
            auto s2 = line.substr(index+1, line.length());
			strs.push_back(make_pair(s1, s2));
		}
	}
}

string solve(string s0, string s1)
{
	int fSs = 0; // +1 First smaller than second
				// +2 First larger than second
				// 0 unknow
	string o0 = "";
	string o1 = "";

	for(int i = 0; i< s0.length(); i++)
	{
		if(s0.at(i) == '?' && s1.at(i) == '?')
		{
			if(fSs == 0)
			{
				//unknown
				o0 += "0";
				o1 += "0";
			}
			else if(fSs == 1)
			{
				o0 += "9";
				o1 += "0";
			}
			else if(fSs == 2)
			{
				o0 += "0";
				o1 += "9";
			}
		}
		else if(s0.at(i) == '?' || s1.at(i) == '?')
		{
			if(fSs == 0)
			{
				if(s0.at(i) == '?')
				{
					o0 += s1.substr(i, 1);
					o1 += s1.substr(i, 1);
				}
				else 
				{
					o0 += s0.substr(i, 1);
					o1 += s0.substr(i, 1);
				}
			}
			else if(fSs == 1)
			{
				if(s0.at(i) == '?')
				{
					o0 += "9";
					o1 += s1.substr(i, 1);
				}
				else 
				{
					o0 += s0.substr(i, 1);
					o1 += "0";
				}
			}
			else if(fSs == 2)
			{
				if(s0.at(i) == '?')
				{
					o0 += "0";
					o1 += s1.substr(i, 1);
				}
				else 
				{
					o0 += s0.substr(i, 1);
					o1 += "9";
				}
			}
		}
		else
		{
			o0 += s0.substr(i, 1);
			o1 += s1.substr(i, 1);
		}
		//compare o0, o1
		if(o0 > o1)
		{
			fSs = 2;
		}
		else if(o0 < o1)
		{
			fSs = 1;
		}
		else if(o0 == o1)
		{
			fSs = 0;
		}
	}
	return o0 + " " + o1;
}

int main(int argc, char const *argv[])
{
	int numberofcases;
	auto strs = std::vector<pair<string,string>>();

	inputparser("B-small-attempt2.in", numberofcases, strs);

	int counter = 1;
	for(auto str: strs)
	{
		cout << "Case #" << counter << ": " << solve(str.first, str.second) << endl; 
		counter++;
	}

	return 0;
}