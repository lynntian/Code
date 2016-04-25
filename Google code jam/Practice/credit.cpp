#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

//https://code.google.com/codejam/contest/351101/dashboard#s=p0

class Solution {
public:
	static void parseInFile(string filename, int& numbers, vector<pair<int, vector<int>>>& out)
	{
		string line;
		ifstream inFile(filename);

		if(inFile.is_open())
		{
			//first line is # of test cases
			getline(inFile, line);
			numbers = stoi(line);

			auto C = 0;
			auto I = 0;
			auto P = vector<int>();
			auto counter = 0;
			while( getline(inFile, line))
			{
				if(counter == 3) 
				{
					counter = 0;
					C=0; I= 0; P.clear(); 
				}

				if(counter == 0)
				{
					C = stoi(line);
				}
				else if(counter == 1)
				{
					I = stoi(line);
				}
				else if(counter == 2)
				{
					parseVector(line, P);
					out.push_back(make_pair(C, P));
				}
				counter++;
			}
		}
	}

	static void parseVector(string line, vector<int>& out)
	{
		stringstream ss(line);
		string buf;
		while(ss >> buf)
		{
			out.push_back( stoi(buf));
		}
	}

	static void printVec(vector<int> v)
	{
		if(v.size())
		{
			for(auto& vc : v)
			{
				cout << vc << " ";
			}
			cout << endl;
		}
	}

	static pair<int, int> Credit(std::vector<int>& v, int size, int credit)
	{
		//have unordered map: key = C-currentNumber; value: bool
		//given a number, first check if map[currentNumber] == true
		// if not found, add to map: map[C- currentNumber] = true

		auto returnPair = make_pair(0,0);
		//First do sanity check
		if(v.empty() || size <= 0 ) return returnPair; // should not happen

		auto map = unordered_map<int, bool>();
		for(auto vc : v)
		{
			if(map.count(vc) == 1)
			{
				//find pair!
				return make_pair((vc <= (credit-vc) ? vc: (credit-vc)), (vc <= (credit-vc) ? (credit-vc):vc));
			}
			//add this element to map
			map[credit-vc] = true;
		}
		return returnPair;
	}
		
};

int main()
{
	int numberOfTestCases = 0;
	auto out = vector<pair<int, vector<int>>>();
	Solution::parseInFile("A-small-practice.in", numberOfTestCases, out);

	cout << "Number of tests: " << numberOfTestCases << endl;
	auto counter = 1;
	for(auto & op : out)
	{
		//cout << "Credit: " << op.first << endl;
		//cout << "Array: " ;
		//Solution::printVec(op.second);
		auto p = Solution::Credit(op.second, op.second.size(), op.first);
		cout << "Case #" << counter++ << ": " << p.first << " " << p.second << endl;

	}

	return 0;
}