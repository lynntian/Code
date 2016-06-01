//If next number is larger than current, current is negative value.
class Solution {
public:
    int romanToInt(string s) {
        auto map = std::unordered_map<char, int>();
        map['I'] = 1;
        map['V'] = 5;
        map['X'] = 10;
        map['L'] = 50;
        map['C'] = 100;
        map['D'] = 500;
        map['M'] = 1000;

        auto size = s.length();
        int res = 0;
        for(int i = 0; i < size; i++)
        {
            int current = map[std::toupper(s.at(i))];
            if(i+1 < size && map[std::toupper(s.at(i+1))] > current)
            {
                current = -current;
            }
            res+= current;
        }
        return res;
    }
};

//Need to improve running time
//---------------------------------------
//WIP use switch instead of map??
class Solution {
public:

    int findValue(char& c)
    {
        auto upc = std::toupper(c);
        switch(upc)
        {
            case 'I':
                return 1;
            case 'V':
                return 5;
            case 'X':
                return 10;
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;
            case 'M':
                return 1000;
            default:
                return 0;
        }
    }
    int romanToInt(string s) {
        auto size = s.length();
        int res = 0;
        for(int i = 0; i < size; i++)
        {
            int current = findValue(s.at(i));
            if(i+1 < size && findValue(s.at(i+1)) > current)
            {
                current = -current;
            }
            res+= current;
        }
        return res;
    }
};

//Accepted