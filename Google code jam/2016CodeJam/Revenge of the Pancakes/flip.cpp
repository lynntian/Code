#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

class Solution{
public:
	static void recursiveFlip(vector<char>& inVector, 
								int index, /*current pancake we are working with start, from bottom i.e. size -1*/
								bool currentPlus /*current state to flip to*/, 
								int& deep /*return count*/)
	{
		if(index < 0) return;

		bool currentIndexSymbolIsPlus = inVector[index] == '+';
		int nextIndex = -1;
		auto tempIndex = index -1;
		while(tempIndex >= 0)
		{
			if((inVector[tempIndex] == '+') != currentIndexSymbolIsPlus)
			{
				nextIndex = tempIndex;
				break;
			}
			tempIndex--;
		}

		//if all symbols left are the same and same as target, return without increase deep
		if(nextIndex == -1 && currentIndexSymbolIsPlus == currentPlus) //all symbols left are the same
		{
			return;
		}

		//if all symbols are same and not same as tartget, return with deep increase.
		else if(nextIndex == -1 && currentIndexSymbolIsPlus != currentPlus)
		{
			deep++;
			return;
		}

		//call next step
		deep++;
		recursiveFlip(inVector, nextIndex, !currentPlus, deep);

	}

	static void parseInFile(string filename, int& numbers, std::vector<std::vector<char>>& v)
	{
		string line;
		ifstream inFile(filename);

		if(inFile.is_open())
		{
			//first line is # of test cases
			getline(inFile, line);
			numbers = stoi(line);

			while( getline(inFile, line))
			{
				// read stack
				auto vs = vector<char>(line.begin(), line.end());
				v.push_back(vs);
			}
		}
	}

};

int main()
{
	int numberOfTestCases = 0;
	auto vec = std::vector<vector<char>>();
	Solution::parseInFile("B-large.in", numberOfTestCases, vec);
	auto counter = 1;
	for(auto& v : vec)
	{
		auto size = v.size();
		auto n = 0;
		Solution::recursiveFlip(v, size-1, true, n);
		cout << "Case #" << counter++ << ": " << n << endl; 
	}
	return 0;
}