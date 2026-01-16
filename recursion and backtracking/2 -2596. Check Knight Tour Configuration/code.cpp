/*
======================================================================================
LEETCODE 2596: Check Knight Tour Configuration
======================================================================================

PROBLEM STATEMENT:
------------------
Given an n x n grid where each cell contains a number from 0 to n²-1, determine if 
the grid represents a valid knight's tour. A valid knight's tour means:
1. The knight starts at cell with value 0 (must be at position [0,0])
2. The knight visits every cell exactly once
3. The knight moves using valid chess knight moves (L-shape: 2 squares in one 
   direction and 1 square perpendicular)
4. The sequence of moves follows the numbers 0 → 1 → 2 → ... → n²-1

EXAMPLE:
--------
Input: grid = [[0,11,16,5,20],[17,4,19,10,15],[12,1,8,21,6],[3,18,23,14,9],[24,13,2,7,22]]
Output: true (valid knight tour)

Input: grid = [[0,3,6],[5,8,1],[2,7,4]]
Output: false (0 is at [0,0] but knight can't reach 1 at [1,2] from 0)

======================================================================================
APPROACH 1: RECURSIVE BACKTRACKING (Current Implementation)
======================================================================================

INTUITION:
----------
- Start from position (0,0) with expected value 0
- At each step, verify current cell has the expected value
- Recursively try all 8 possible knight moves
- If any path leads to the last cell (value n²-1), tour is valid

ALGORITHM:
----------
1. Begin at (0,0) expecting value 0
2. Validate current position:
   - Check if position is within bounds
   - Check if current cell value matches expected value
3. If we've reached the last value (n²-1), tour is complete
4. Try all 8 knight moves recursively with expVal+1
5. Return true if ANY path succeeds (OR operation)

TIME COMPLEXITY: O(8^(n²)) in worst case - exponential
- At each cell, we try up to 8 moves
- Maximum depth is n² cells
- In practice, pruning makes it much faster

SPACE COMPLEXITY: O(n²)
- Recursion stack depth is at most n² (number of cells)

KNIGHT MOVE PATTERN (Important to memorize):
--------------------------------------------
From position (r, c), knight can move to 8 positions:
1. (r-2, c+1) - 2 up,    1 right
2. (r-1, c+2) - 1 up,    2 right
3. (r+1, c+2) - 1 down,  2 right
4. (r+2, c+1) - 2 down,  1 right
5. (r+2, c-1) - 2 down,  1 left
6. (r+1, c-2) - 1 down,  2 left
7. (r-1, c-2) - 1 up,    2 left
8. (r-2, c-1) - 2 up,    1 left

Visualize as an "L" shape: move 2 squares in one direction, then 1 perpendicular

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: ITERATIVE WITH DIRECTIONS ARRAY (Cleaner Code)
-----------------------------------------------------------
Instead of 8 separate recursive calls, use a directions array:
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    for(int i = 0; i < 8; i++) {
        if(isValid(grid, r + dx[i], c + dy[i], n, expVal + 1))
            return true;
    }

PROS: More maintainable, easier to modify
CONS: Same complexity

APPROACH 3: DIRECT VALIDATION (Most Efficient)
-----------------------------------------------
Since we know the exact sequence (0 to n²-1), we can:
1. Create a position map: pos[value] = {row, col}
2. Start from value 0, check if it's at (0,0)
3. For each consecutive pair (i, i+1), verify knight can move from pos[i] to pos[i+1]

TIME: O(n²) - single pass
SPACE: O(n²) - for position map

This is BETTER for this specific problem!

APPROACH 4: BFS/DFS with Visited Tracking
------------------------------------------
Standard graph traversal, marking cells as visited
Not needed here since we follow a predetermined sequence

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Knight moves in L-shape: 2 squares + 1 perpendicular (8 directions total)
2. ⭐ Tour MUST start at (0,0) with value 0
3. ⭐ Values must be consecutive: 0→1→2→...→n²-1
4. ⭐ OR operation (||) means we need ANY valid path, not all paths
5. ⭐ Base case: when expVal == n²-1, we've completed the tour
6. ⭐ For this problem, direct validation is more efficient than backtracking

COMMON MISTAKES TO AVOID:
--------------------------
❌ Forgetting to check if starting position is (0,0)
❌ Not validating that current cell equals expected value
❌ Wrong knight move directions (mixing up +/- signs)
❌ Using AND (&&) instead of OR (||) for combining results
❌ Not handling n = 1 edge case

WHEN TO USE THIS PATTERN:
--------------------------
- Knight's tour problems
- Chess piece movement validation
- Graph traversal with specific movement rules
- Sequence validation problems

======================================================================================
*/

class Solution {
public:
    // Helper function: Recursively validate if knight can complete tour from (r,c)
    // Parameters:
    //   grid: the board configuration
    //   r, c: current position (row, column)
    //   n: board size (n x n)
    //   expVal: expected value at current position
    bool isValid(vector<vector<int>>& grid, int r, int c, int n, int expVal){
        
        // BASE CASE 1: Invalid position or wrong value
        // Check if we're out of bounds OR current cell doesn't have expected value
        if(r < 0 || c < 0 || r >= n || c >= n || grid[r][c] != expVal){
            return false;
        }
        
        // BASE CASE 2: Reached the last cell successfully
        // If current value is the last value (n²-1), tour is complete
        if(expVal == n*n - 1){
            return true;
        }

        // RECURSIVE CASE: Try all 8 possible knight moves
        // Knight moves in L-shape: 2 squares in one direction + 1 perpendicular
        // We need to find if ANY of these moves leads to a valid tour
        
        int ans1 = isValid(grid, r - 2, c + 1, n, expVal + 1);  // 2 up, 1 right
        int ans2 = isValid(grid, r - 1, c + 2, n, expVal + 1);  // 1 up, 2 right
        int ans3 = isValid(grid, r + 1, c + 2, n, expVal + 1);  // 1 down, 2 right
        int ans4 = isValid(grid, r + 2, c + 1, n, expVal + 1);  // 2 down, 1 right
        int ans5 = isValid(grid, r + 2, c - 1, n, expVal + 1);  // 2 down, 1 left
        int ans6 = isValid(grid, r + 1, c - 2, n, expVal + 1);  // 1 down, 2 left
        int ans7 = isValid(grid, r - 1, c - 2, n, expVal + 1);  // 1 up, 2 left
        int ans8 = isValid(grid, r - 2, c - 1, n, expVal + 1);  // 2 up, 1 left
       
        // Return true if ANY of the 8 moves leads to a valid complete tour
        // Short-circuit evaluation: stops at first true value
        return ans1 || ans2 || ans3 || ans4 || ans5 || ans6 || ans7 || ans8;
    }

    // Main function: Check if grid represents a valid knight tour
    bool checkValidGrid(vector<vector<int>>& grid) {
        // Start from (0,0) expecting value 0
        // Knight's tour MUST begin at top-left corner with value 0
        return isValid(grid, 0, 0, grid.size(), 0);
    }
};