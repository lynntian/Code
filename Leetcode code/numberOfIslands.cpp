class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        auto m = grid.size();
        if(!m) return 0;

        auto n = grid[0].size();
        if(!n) return 0;
        auto result= 0;
        for(int i=0; i< m; i++)
        {
            for(int j=0; j<n;j++)
            {
                if(grid[i][j] == '1')
                {
                    cout<<"dfs"<<endl;
                    dfs(i, j, grid);

                    result++;
                }

            }
        }
        return result;
    }
    void dfs(int i, int j, vector<vector<char>>& grid)
    {
        if(i <0 || j <0 || i >=grid.size() || j >= grid[0].size() || grid[i][j] == '0') return;
        grid[i][j] = '0';
        dfs(i+1, j,grid);
        dfs(i-1,j,grid);
        dfs(i, j+1,grid);
        dfs(i, j-1,grid);
    }
};