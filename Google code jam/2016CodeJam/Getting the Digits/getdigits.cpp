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


void inputparser(string fileName, int& n, std::vector<string>& strs)
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
			strs.push_back(line);
		}
	}
}

void buildMap(unordered_map<string, string> &map, unordered_map<string, char>& lookup)
{
	vector<string> numbers = {"ONE","THREE", "FOUR", "FIVE", "SEVEN","NINE"};
	for(auto d:numbers)
	{
		auto sub = d.substr(0, 3);
		//cout << "sub: "<< sub << " key: " << d << endl;
		map[sub] = d;
	}
	std::vector<string> v = {"ZERO","ONE", "TWO","THREE", "FOUR", "FIVE", "SIX","SEVEN","EIGHT","NINE"};
	auto counter =0;
	for(auto n : v)
	{
		lookup[n] = counter + '0';
		counter ++; 
	}
}



string solve(string s, unordered_map<string,string> map, unordered_map<string, char> lookup)
{
	auto uniqueS = unordered_map<char, string>();
	uniqueS['Z'] = "ZERO";
	uniqueS['G'] = "EIGHT";
	uniqueS['X'] = "SIX";
	uniqueS['W'] = "TWO";

	auto res = string();
	auto dic = unordered_map<char, int>();

	for(auto& c : s)
	{
		dic[c]++;
	}

	for(auto us : uniqueS)
	{
		//cout << "us: " << us.first << " : " << us.second <<endl;
		if(dic.count(us.first) != 0)
		{
			//remove every char in this word
			int times = dic[us.first];
			//cout << "times: " << times << endl;
			for(auto c : us.second)
			{
				dic[c] -= times;
			}
			for(int i=0; i< times ;i++)
			{
				res+= string(1, lookup[us.second]);
			}
		}
	}

	for(auto m:map)
	{
		auto c0 = m.first.at(0);
		auto c1 = m.first.at(1);
		auto c2 = m.first.at(2);
		//cout << c0 << " : " << c1 << endl;
		if(dic.count(c0) > 0
			&&  dic.count(c1) > 0
			&& dic[c0] > 0
			&& dic[c1] > 0
			&& dic[c2] > 0)
		{
			auto times = min(dic[c0], dic[c1]);
			times = min(times, dic[c2]);

			//cout <<"times: " << times << endl;
			for(int i=0; i< times ;i++)
			{
				res+= string(1, lookup[m.second]);
			}
			//res += string(times, lookup[m.second] * times);
			for(auto& c : m.second)
			{
				dic[c] -= times;
			}
		}
	}

	sort(res.begin(), res.end());
	//sort res
	return res;
}

int main(int argc, char const *argv[])
{
	int numberofcases;
	auto strs = vector<string>();

	inputparser("A-large.in", numberofcases, strs);
	auto map = unordered_map<string, string>();
	auto lookup = unordered_map<string, char>();
	
	buildMap(map, lookup);

	//cout << map.size();
	int counter = 1;
	for(auto str: strs)
	{
		cout << "Case #" << counter << ": " << solve(str, map, lookup) << endl; 
		counter++;
	}

	return 0;
}