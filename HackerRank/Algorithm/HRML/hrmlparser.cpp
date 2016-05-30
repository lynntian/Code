#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <stack>
#include <fstream>

using namespace std;

typedef unordered_map<string, unordered_map<string, string>> MyMap;

void parserhelper(string hrml, MyMap& lookup, string& curTag)
{
	if(hrml.at(0) == '<')
	{
		if(hrml.at(1) == '/')
		{
			//check stack for matching close and store this node into map
			auto closeTag = hrml.substr(2, hrml.length() - 3 );
			auto i = curTag.find_last_of('.');
			if(i != string::npos)
			{
				curTag = curTag.substr(0, i);
				//cout << "current tag: " << curTag << endl;
			}
			else if(curTag == closeTag)
			{
				curTag = "";
			}
		}
		else
		{
			if(hrml.find(' ') == string::npos && hrml.back() == '>')
			{
				//This is to deal with tags that have no attributes
				curTag = curTag.empty() ? hrml.substr(1, hrml.length() -2) : (curTag + "."+hrml.substr(1, hrml.length() -2));
				return;
			}
			//new tag with attributes
			istringstream sst(hrml);
			string curs;
			string name;
			string val;
			int count = 0;
			while(getline(sst, curs, ' '))
			{
				if(curs.at(0) == '<')
				{
					//tag name
					if(!curTag.empty()) curTag = curTag + "." + curs.substr(1);
					else curTag = curs.substr(1);
					
				}
				else if(curs.back() == '>')
				{
					val = curs.substr(1, curs.length() -3);
					count = 0;
				}
				else if(curs == "=")
				{
					continue;
				}
				else
				{
					if(count == 0)
					{
						name = curs;
						count = 1;
					}
					else
					{
						val = curs.substr(1, curs.length() -2);
						count = 0;
					}
				}
				if(count == 0 && !name.empty())
				{
					lookup[curTag][name] = val;
					name = "";
					val = "";
				}
			}
		}
	}
}

void parser(string fileName, vector<string>& queries, MyMap& lookup)
{
	ifstream inFile(fileName);

	auto tags = stack<string>();
	string line;
	getline(inFile, line);
	auto index = line.find(' ');
	int N = stoi(line.substr(0, index));
	int Q = stoi(line.substr(index+1, line.length()));

	string curTag;
	for(int i = N; i > 0; i--)
	{
		//parse HRML
		string hrml;
		getline(inFile, hrml);
		if(hrml.empty()) {continue;}
		parserhelper(hrml, lookup, curTag);
	}

	for(auto m: lookup)
	{
		cout << "Tag: " << m.first << endl;

		for(auto n:m.second)
		{
			cout << "Atrr: " << n.first << "  " << n.second << endl;
		}
	}

	for(int i = Q; i > 0; i--)
	{
		//Queries
		string qs;
		getline(inFile, qs);
		queries.push_back(qs);

		string printStr = "Not Found!";

		auto ind = qs.find('~');
		//check if current query is valid
		if(ind != string::npos)
		{
			auto tag = qs.substr(0, ind);
			auto attr = qs.substr(ind +1);
			if(lookup.count(tag) == 1)
			{
				if(lookup[tag].count(attr) == 1)
				{
					printStr = lookup[tag][attr];
				}
			}
		}
		cout << printStr << endl;
	}
}


int main() {

	string fileName = "in4.txt";
	vector<string> qs;
	MyMap mm;
	parser(fileName, qs, mm);
    return 0;
}
