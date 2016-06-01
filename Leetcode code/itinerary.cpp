/*

[["JFK", "KUL"], ["NRT", "JFK"], ["JFK", "NRT"]]
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
[["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
[["ADL","EZE"],["AUA","AXA"],["ADL","TIA"],["TIA","ADL"],["AXA","CNS"],["CNS","ADL"],["CBR","ANU"],["JFK","AUA"],["JFK","ADL"],["JFK","CNS"],["BNE","ANU"],["AUA","BNE"],["ANU","BNE"],["ANU","AXA"],["CBR","OOL"],["EZE","CNS"],["CNS","ADL"],["BNE","CNS"],["ANU","AXA"],["OOL","CNS"],["AUA","EZE"],["ANU","AUA"],["CBR","BNE"],["BNE","AXA"],["CNS","BNE"],["TIA","CNS"],["TIA","BNE"],["AUA","AXA"],["TIA","EZE"],["CNS","AXA"],["EZE","OOL"],["ADL","AXA"],["ADL","EZE"],["BNE","AXA"],["AXA","TIA"],["OOL","AUA"],["EZE","AXA"],["OOL","JFK"],["ADL","AUA"],["TIA","OOL"],["TIA","CNS"],["ANU","AUA"],["AXA","OOL"],["JFK","BNE"],["AUA","ANU"],["AUA","BNE"],["CNS","CBR"],["AXA","ADL"],["TIA","EZE"],["CNS","CBR"],["ADL","BNE"],["AUA","CBR"],["EZE","CNS"],["EZE","CNS"],["OOL","TIA"],["OOL","EZE"],["EZE","ADL"],["EZE","JFK"],["EZE","AUA"],["CNS","EZE"],["OOL","CNS"],["AXA","BNE"],["AXA","ADL"],["BNE","CNS"],["BNE","OOL"],["AUA","TIA"],["CBR","OOL"],["ANU","TIA"],["TIA","OOL"],["JFK","EZE"],["OOL","AXA"],["AXA","ANU"],["TIA","ANU"],["OOL","CBR"],["AXA","JFK"],["ADL","OOL"],["AXA","CBR"],["ADL","CBR"],["CNS","EZE"],["CBR","ANU"],["BNE","CNS"],["AXA","OOL"],["CNS","AUA"],["CNS","JFK"],["CBR","TIA"],["OOL","TIA"],["EZE","JFK"],["CNS","CBR"],["EZE","BNE"],["BNE","EZE"],["TIA","CBR"],["CBR","TIA"],["BNE","ADL"],["ANU","AUA"],["CBR","AXA"],["AXA","AUA"],["BNE","DRW"],["JFK","BNE"],["CNS","AUA"],["ADL","ANU"],["AUA","TIA"],["JFK","BNE"],["BNE","JFK"],["AUA","ADL"],["EZE","AXA"],["BNE","OOL"],["AXA","ANU"],["ANU","EZE"],["OOL","TIA"]]
*/
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        auto size = tickets.size();
        auto res = vector<string>();
        if(size == 0) return res;

        auto al = unordered_map<string, vector<pair<string, bool>>>();
        for(auto& p : tickets)
        {
            al[p.first].push_back(make_pair(p.second,false));
        }
        for(auto& a : al)
        {
            auto& arr = a.second;
            if(arr.size() > 1)
                sort(arr.begin(), arr.end(),[](const pair<string, bool>& a1, const pair<string,bool>& a2) -> bool{
                    return a1.first < a2.first;
                });
        }

        auto start = al["JFK"];
        for(auto& p : start)
        {
            //each end vertex in start could be the starting edge
            //do dfs on this node:
            res = vector<string>();
            res.push_back("JFK");
            if(dfs(al, "JFK",res, size+1))
                break;
        }
        return res;
    }

    bool dfs(unordered_map<string, vector<pair<string, bool>>>& al, string cur,vector<string>& res, int size)
    {
        if(res.size() == size) return true;
        //cout << "cur: " << cur << endl;
        //res.push_back(cur);
        //if al[cur] are all visited and last node is "JFK" return true
        for(auto& n : al[cur])
        {
            if(n.second) continue;
            //cout << "n: " << n.first << endl;
            //temp mark n as visited
            n.second = true;
            //cout << "push_back: " << n.first << endl;
            res.push_back(n.first);
            if (dfs(al, n.first, res,size))
            {
                return true;
            }
            n.second = false;

            if(res.size()) {
                //cout << "pop_back: " << res[res.size()-1];
                res.pop_back();
            }
        }

        return false;
    }
};