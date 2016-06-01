/*
Test cases:
“111122335588” true
“1203” false
“12122436” true
“199100199”true
“19910010”false
*/
class Solution {
public:
    bool isAdditiveNumber(string num) {
        auto len = num.length();
        if(len < 3) return false;

        auto first = 0;
        auto second = 0;
        auto third = 0;
        auto endIndex = 0;
        auto maxLen = 0;
        auto flag = false;
        for(int l =1; l <= len / 3; l++)
        {
            first = getNumber(num, 0, l-1, len);
            for(int m =1; m <= (len -l) / 2; m++)
            {
                //cout << "m:" << m <<endl;
                second = getNumber(num, l, l+m-1, len );
                cout << "second: " <<second << endl;
                maxLen = max(m,l);
                if(findThird(num, second, first, l+m, maxLen, endIndex, third))
                {
                    auto tmpEnd = endIndex;
                    auto tmpF = first;
                    auto tmpS = second;
                    auto tmpT = third;
                    cout << "first: " << first << " second: " << second <<endl;
                    while( tmpEnd+maxLen <= len)
                    {
                        auto start = tmpEnd;
                        tmpF = tmpS;
                        tmpS = tmpT;
            //cout << "first: " << first << " second: " << second <<endl;
            //cout << "start from: " << start << endl;
                        if(findThird(num,tmpS, tmpF, start, maxLen, tmpEnd, tmpT))
                        {
                            endIndex = tmpEnd;
                            first = tmpF;
                            second = tmpS;
                            third = tmpT;
                            if(tmpEnd == len)
                            {
                                return true;
                            }
                        }
                        else
                            break;
                    }
                }
            }
        }
        //cout<< "endIndex: " << endIndex << endl;
        if(endIndex == len) return true;

        return false;
    }

    bool findThird(string num,int second, int first, int startIndex, int& maxPreLen, int& endIndex, int& third)
    {
        //if third starts with 0 return false
        if(num.at(startIndex) - '0' == 0) return false;
        third = getNumber(num, startIndex, startIndex + maxPreLen-1, num.length());
        //cout << "third: " << third << endl;
        if(second + first == third)
        {
            endIndex = startIndex + maxPreLen;
            return true;
        }
        else if(second + first > third && startIndex + maxPreLen < num.length())
        {
            auto tmp = third * 10 + (num.at(startIndex + maxPreLen) - '0');
            //cout<<"tmp:" <<tmp<<endl;
            if(tmp == second+first)
            {
                third = tmp;
                endIndex = startIndex + maxPreLen+1;
                maxPreLen++;
                return true;
            }
        }
        return false;
    }

    int getNumber(string num, int i, int j, int len)
    {
        auto res = 0;
        if(i > j || j > len)
        {
            return res;
        }
        for(int a = i; a <= j; a++)
        {
            res = res * 10;
            res += num.at(a) - '0';
        }
        return res;
    }
};