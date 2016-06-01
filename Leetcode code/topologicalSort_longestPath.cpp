class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        auto m = matrix.size();
        if(m == 0) return 0;
        auto n = matrix[0].size();
        if(n == 0 ) return 0;
        //cout << m << " , " << n << endl;
        longest = 0;
        auto visited = vector<vector<int>>(m, vector<int>(n, 0));
        for(int i=0; i< m; i++)
        {
            for(int j=0; j< n; j++)
            {
                //cout << "i,j: " << i << " , " << j << endl;
                longest = max(longest, dfs(matrix, i, j, m, n, visited, INT_MIN));
            }
        }
        return longest;
    }

    int dfs(vector<vector<int>>& matrix, int x, int y, int m, int n, vector<vector<int>>& visited, int last)
    {
        if( x < 0 || y < 0 || x >=m || y >= n) return 0;
        auto p = matrix[x][y];
        if(p > last)
        {
            if( visited[x][y] != 0 ) return visited[x][y];

            int a=  dfs(matrix, x-1, y, m,n, visited, p) +1;
            int b=  dfs(matrix, x+1, y, m,n, visited, p) +1;
            int c=  dfs(matrix, x, y-1, m,n, visited, p) +1;
            int d=  dfs(matrix, x, y+1, m,n, visited, p) +1;
            visited[x][y] = max(a, max(b, max(c,d)));
            return visited[x][y];
        }
        return 0;
    }
private:
    int longest;
};