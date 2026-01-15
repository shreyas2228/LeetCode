// leetcode problem 2965. Find Missing and Repeated Values

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        unordered_set<int> s;
        int n = grid.size();
        int repeated = -1;
        long long actual_sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                actual_sum += grid[i][j];
                if (s.count(grid[i][j])) {
                    repeated = grid[i][j];
                }
                s.insert(grid[i][j]);
            }
        }

        long long total = 1LL * n * n;
        long long expected_sum = total * (total + 1) / 2;
        int missing = expected_sum + repeated - actual_sum;

        return {repeated, missing};
    }
};