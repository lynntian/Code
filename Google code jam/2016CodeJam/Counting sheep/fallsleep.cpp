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
	static void parseInFile(string filename, int& numbers, vector<long>& out)
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
				long N = 0;
				N = stoi(line);
				out.push_back(N);
			}
		}
	}
	static long sleep(long n)
	{
		if( n == 0 ) return -1;
		//a map to keep track of numbers
		auto v =  std::vector<int>(10, 0); // ten elements all with value 0 indicate that it hasn't been marked
		//at most loop 100
		for (int i = 1; i <= 100; ++i)
		{
			auto tmp = i * n;
			while(tmp >= 10)
			{
				long x = tmp / 10 * 10;
				v[tmp - x] = 1;
				tmp = tmp / 10;
			}
			v[tmp] = 1;

			auto isAsleep = 0;
			//check array
			for(auto vT : v)
			{
				isAsleep+= vT;
			}
			if(isAsleep == 10) return i*n;
		}
		return -1;
	}
};

int main()
{
	int numberOfTestCases = 0;
	auto vec = std::vector<long>();
	Solution::parseInFile("A-large.in", numberOfTestCases, vec);
	auto counter = 1;
	for(auto& v : vec)
	{
		auto ret = Solution::sleep(v);
		if(ret == -1)
		{
			cout << "Case #" << counter++ << ": INSOMNIA" << endl; 
		}
		else
			cout << "Case #" << counter++ << ": " << ret << endl;
	}
	return 0;
}