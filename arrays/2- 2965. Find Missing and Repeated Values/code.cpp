/*
======================================================================================
LEETCODE 2965: Find Missing and Repeated Values
======================================================================================

PROBLEM STATEMENT:
------------------
You are given a n x n 2D matrix grid where each cell contains a number from 1 to n².
Exactly ONE number appears TWICE (repeated), and exactly ONE number from 1 to n² 
is MISSING.

Return a vector {repeated, missing}.

EXAMPLES:
---------
Input: grid = [[1,3],[2,2]]
Output: [2,3]
Explanation: 2 appears twice, 3 is missing

Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
Output: [9,5]
Explanation: 9 appears twice, 5 is missing (range is 1-9)

======================================================================================
APPROACH 1: HASH SET + MATH (Current Implementation) ⭐ OPTIMAL ⭐
======================================================================================

INTUITION:
----------
1. Use hash set to detect the repeated value
2. Calculate what the sum SHOULD be (1+2+3+...+n²)
3. Calculate what the sum ACTUALLY is
4. Use formula: missing = expected_sum - actual_sum + repeated

WHY IT WORKS:
-------------
If we have numbers 1 to 9, and 5 is missing but 9 appears twice:
- Expected sum: 1+2+3+4+5+6+7+8+9 = 45
- Actual sum:   1+2+3+4+9+6+7+8+9 = 49
- Difference: 49 - 45 = 4 (this is: repeated - missing = 9 - 5)
- Rearranging: missing = expected_sum - actual_sum + repeated
                       = 45 - 49 + 9 = 5 ✓

ALGORITHM:
----------
1. Create hash set to track seen numbers
2. Traverse grid:
   a. Add each value to actual_sum
   b. If value already in set → it's the repeated number
   c. Insert value into set
3. Calculate expected_sum = n² × (n² + 1) / 2  (sum formula: n(n+1)/2)
4. Calculate missing = expected_sum - actual_sum + repeated

TIME COMPLEXITY: O(n²)
- Visit each cell once: O(n²)
- Set operations (insert, count): O(1) average

SPACE COMPLEXITY: O(n²)
- Hash set stores up to n² elements

PROS:
- ⭐ Clean and elegant solution
- ⭐ Single pass through grid
- ⭐ Easy to understand
- ⭐ Good for interviews

CONS:
- Uses O(n²) extra space for set

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: SORTING
-------------------
1. Flatten grid to 1D array
2. Sort the array
3. Find repeated by checking adjacent elements
4. Find missing by checking if nums[i] != i+1

TIME: O(n² log n) - sorting overhead
SPACE: O(n²) - for flattened array

Slower than hash set approach.

APPROACH 3: FREQUENCY ARRAY
----------------------------
Use array to count frequency (if values fit in array range):

    vector<int> freq(n*n + 1, 0);
    int repeated = -1;
    for(each cell in grid) {
        freq[grid[i][j]]++;
        if(freq[grid[i][j]] == 2)
            repeated = grid[i][j];
    }
    for(int i = 1; i <= n*n; i++) {
        if(freq[i] == 0)
            return {repeated, i};
    }

TIME: O(n²)
SPACE: O(n²)

Similar to hash set but uses array.

APPROACH 4: MATHEMATICAL (XOR Method)
--------------------------------------
Use XOR properties:
- a ^ a = 0
- a ^ 0 = a
- XOR is commutative and associative

XOR all grid values with all expected values (1 to n²):
Result = repeated ^ missing

Then use additional logic to separate them.

TIME: O(n²)
SPACE: O(1) - most space efficient!

More complex to implement but optimal space.

APPROACH 5: IN-PLACE MARKING (Modifies Grid)
---------------------------------------------
If allowed to modify grid, mark visited cells:

    for each cell value v:
        if grid[v-1] is negative: v is repeated
        else: mark grid[v-1] as negative
    
Find missing by checking which position is still positive.

TIME: O(n²)
SPACE: O(1) - but modifies input!

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Use hash set to detect repeated value in O(n²) time
2. ⭐ Mathematical formula: missing = expected_sum + repeated - actual_sum
3. ⭐ Sum formula for 1 to N: N × (N + 1) / 2
4. ⭐ In grid problems, total elements = n × n = n²
5. ⭐ Long long is used to prevent integer overflow for large sums
6. ⭐ Hash set count() returns 1 if element exists, 0 otherwise

MATHEMATICAL FORMULAS TO REMEMBER:
-----------------------------------
Sum of 1 to N: N × (N + 1) / 2

For this problem with n×n grid:
Expected sum = n² × (n² + 1) / 2

Relationship:
actual_sum = expected_sum - missing + repeated
Therefore:
missing = expected_sum - actual_sum + repeated

COMMON MISTAKES TO AVOID:
--------------------------
❌ Integer overflow - use long long for sum calculations
❌ Forgetting total elements is n², not n
❌ Off-by-one errors in sum formula
❌ Not checking if element exists in set before marking as repeated

WHEN TO USE THIS PATTERN:
--------------------------
- Finding missing/duplicate in range 1 to N
- Array manipulation with mathematical properties
- Problems involving expected vs actual sums
- Detection of anomalies in sequences

RELATED PROBLEMS:
-----------------
- LeetCode 287: Find the Duplicate Number
- LeetCode 268: Missing Number
- LeetCode 645: Set Mismatch
- LeetCode 448: Find All Numbers Disappeared in Array

======================================================================================
*/

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        unordered_set<int> s;      // Hash set to track seen numbers
        int n = grid.size();        // Grid dimension (n × n)
        int repeated = -1;          // Store the repeated value
        long long actual_sum = 0;   // Sum of all values in grid (use long long to avoid overflow)

        // Traverse the entire grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Add current value to actual sum
                actual_sum += grid[i][j];
                
                // Check if this value was already seen
                if (s.count(grid[i][j])) {
                    repeated = grid[i][j];  // Found the repeated value
                }
                
                // Add value to set for future checks
                s.insert(grid[i][j]);
            }
        }

        // Calculate expected sum of numbers from 1 to n²
        // Formula: sum of 1 to N = N × (N + 1) / 2
        long long total = 1LL * n * n;  // Total elements (n²)
        long long expected_sum = total * (total + 1) / 2;
        
        // Calculate missing number using the relationship:
        // actual_sum = expected_sum - missing + repeated
        // Therefore: missing = expected_sum - actual_sum + repeated
        int missing = expected_sum + repeated - actual_sum;

        // Return result as {repeated, missing}
        return {repeated, missing};
    }
};