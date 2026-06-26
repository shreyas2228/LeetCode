/*
======================================================================================
LEETCODE 90: Subsets II
======================================================================================

PROBLEM STATEMENT:
------------------
Given an integer array nums that may contain DUPLICATES, return all possible 
subsets (the power set).

The solution set must NOT contain duplicate subsets. Return the solution in any order.

EXAMPLES:
---------
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Input: nums = [0]
Output: [[],[0]]

DIFFERENCE FROM SUBSETS I (LeetCode 78):
-----------------------------------------
- Subsets I: No duplicates in input → all subsets unique
- Subsets II: Duplicates in input → need to avoid duplicate subsets

For example, with [1,2,2]:
- Wrong: [[1,2],[1,2]] (duplicate subsets)
- Correct: [[1,2]] (appears once)

======================================================================================
APPROACH 1: BACKTRACKING WITH DUPLICATE SKIPPING ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
Use standard backtracking to generate all subsets, but SKIP duplicates smartly.

KEY IDEA TO AVOID DUPLICATES:
1. SORT the array first (brings duplicates together)
2. When we decide to EXCLUDE an element, skip ALL consecutive duplicates
3. When we INCLUDE an element, process normally

WHY SORTING HELPS:
------------------
After sorting [1,2,2], duplicates are adjacent.
When we skip one '2', we can skip all consecutive '2's in one go.

DECISION TREE (for [1,2,2] after sorting):
-------------------------------------------
                          []
                /                    \
          include 1                 exclude 1 (skip to end)
              [1]                        []
         /         \                /         \
    include 2   exclude 2      include 2   exclude 2
      [1,2]        [1]            [2]          []
    /      \         \              \
inc 2   exc 2     exc 2           exc 2
[1,2,2]  [1,2]     [1]            [2]

Notice: When we exclude an element, we skip to next DIFFERENT element!

VISUALIZATION OF SKIPPING:
--------------------------
nums = [1, 2, 2, 3] (sorted)
        0  1  2  3  (indices)

At index 1 (value 2):
- Include 2: Process normally, move to index 2
- Exclude 2: Skip ALL 2's, move to index 3 (next different value)

This prevents generating duplicate subsets like [1,3] twice.

ALGORITHM:
----------
1. SORT the input array (crucial for duplicate detection)

2. Define recursive function getAllSubsets(nums, ans, i, allSubsets):
   - nums: input array
   - ans: current subset being built
   - i: current index
   - allSubsets: collection of all subsets

3. Base case: if i == nums.size()
   - Add current subset to result
   - Return

4. Recursive case:
   a. INCLUDE current element:
      - Add nums[i] to ans
      - Recurse with i+1
      - Remove nums[i] from ans (backtrack)
   
   b. EXCLUDE current element:
      - Find next index with DIFFERENT value
      - Skip all duplicates of current element
      - Recurse with that index

TIME COMPLEXITY: O(2^n × n)
- 2^n possible subsets
- Each subset takes O(n) time to copy
- Sorting: O(n log n) (negligible compared to 2^n)

SPACE COMPLEXITY: O(n × 2^n)
- Storing 2^n subsets
- Each subset has average size n/2
- Recursion depth: O(n)

NOTE: There's a typo in the original code - "vextor" should be "vector"

PROS:
- ⭐ Handles duplicates elegantly
- ⭐ Natural backtracking structure
- ⭐ Efficient duplicate skipping
- ⭐ Common interview pattern

CONS:
- Requires sorting first
- Slightly complex logic for skipping duplicates

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: USING SET TO REMOVE DUPLICATES
-------------------------------------------
Generate all subsets (including duplicates), use set to filter:

    void backtrack(vector<int>& nums, int i, vector<int>& curr,
                   set<vector<int>>& result) {
        if(i == nums.size()) {
            result.insert(curr);  // Set automatically removes duplicates
            return;
        }
        // Include
        curr.push_back(nums[i]);
        backtrack(nums, i+1, curr, result);
        curr.pop_back();
        // Exclude
        backtrack(nums, i+1, curr, result);
    }

TIME: O(2^n × n log n) - set operations add log factor
SPACE: O(2^n × n)

Simpler but less efficient (set operations are costly).

APPROACH 3: ITERATIVE WITH DUPLICATE TRACKING
----------------------------------------------
Build subsets iteratively, skip duplicates:

    sort(nums.begin(), nums.end());
    vector<vector<int>> result = {{}};
    int prevSize = 0;
    
    for(int i = 0; i < nums.size(); i++) {
        int size = result.size();
        int start = (i > 0 && nums[i] == nums[i-1]) ? prevSize : 0;
        
        for(int j = start; j < size; j++) {
            vector<int> subset = result[j];
            subset.push_back(nums[i]);
            result.push_back(subset);
        }
        prevSize = size;
    }

TIME: O(2^n × n)
SPACE: O(2^n × n)

Iterative approach, avoids recursion.

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ ALWAYS sort array first (critical for duplicate detection)
2. ⭐ Include element → process normally, move to next index
3. ⭐ Exclude element → skip ALL consecutive duplicates
4. ⭐ Skipping pattern: while(nums[idx] == nums[idx-1]) idx++
5. ⭐ Backtracking: add → recurse → remove (standard pattern)
6. ⭐ Duplicates in INPUT → need special handling
7. ⭐ Without sorting, duplicate detection becomes much harder

DUPLICATE SKIPPING LOGIC:
--------------------------
When excluding nums[i], find next different element:

    int idx = i + 1;
    while(idx < n && nums[idx] == nums[idx-1]) {
        idx++;
    }
    // Now idx points to first different element (or end of array)

This ensures we don't generate duplicate subsets.

WHY INCLUDE DOESN'T SKIP:
--------------------------
When we INCLUDE an element, we want to explore all possibilities with it.
For [2,2], we need:
- [2] (include first 2, exclude second)
- [2,2] (include both 2's)

Skipping when including would miss [2,2].

COMMON MISTAKES TO AVOID:
--------------------------
❌ Forgetting to sort the array first
❌ Skipping duplicates when INCLUDING (only skip when EXCLUDING)
❌ Wrong skip logic (comparing nums[idx] with nums[i] instead of nums[idx-1])
❌ Typos like "vextor" instead of "vector"
❌ Not backtracking (forgetting to pop_back)

BACKTRACKING TEMPLATE:
----------------------
1. Base case → store result
2. Make choice → modify state
3. Recurse → explore with choice
4. Undo choice → backtrack (restore state)

This problem follows this template perfectly!

PATTERN RECOGNITION:
--------------------
Use this approach when:
- Generating all combinations/subsets/permutations
- Input may have duplicates
- Need to avoid duplicate results
- Backtracking is natural fit

RELATED PROBLEMS:
-----------------
- LeetCode 78: Subsets (no duplicates in input)
- LeetCode 39: Combination Sum (can reuse elements)
- LeetCode 40: Combination Sum II (duplicates, can't reuse)
- LeetCode 46: Permutations
- LeetCode 47: Permutations II (with duplicates)
- Any backtracking problem with duplicates

======================================================================================
*/

class Solution {
public:
    // Recursive backtracking function to generate all unique subsets
    // Parameters:
    //   nums: sorted input array
    //   ans: current subset being built
    //   i: current index in nums
    //   allSubsets: collection of all unique subsets
    void getAllSubsets(vector<int>& nums, vector<int>& ans, int i, 
                       vector<vector<int>>& allSubsets){  // Fixed: vextor → vector
        
        // BASE CASE: Reached end of array
        // Current subset (ans) is complete, add it to result
        if(i == nums.size()){
            allSubsets.push_back(ans);
            return;
        }

        // CHOICE 1: INCLUDE current element nums[i]
        ans.push_back(nums[i]);                    // Make choice
        getAllSubsets(nums, ans, i + 1, allSubsets);  // Recurse
        ans.pop_back();                            // Backtrack (undo choice)

        // CHOICE 2: EXCLUDE current element nums[i]
        // KEY: Skip all consecutive duplicates of nums[i]
        // This prevents generating duplicate subsets
        int idx = i + 1;
        while(idx < nums.size() && nums[idx] == nums[idx-1]){
            idx++;  // Skip to next different element
        }
        
        // Recurse with next different element (or end of array)
        getAllSubsets(nums, ans, idx, allSubsets);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // STEP 1: Sort array (CRITICAL for duplicate detection)
        // Sorting brings duplicate elements together
        sort(nums.begin(), nums.end());

        // Result storage
        vector<vector<int>> allSubsets;
        
        // Current subset being built
        vector<int> ans;

        // Generate all unique subsets starting from index 0
        getAllSubsets(nums, ans, 0, allSubsets);
        
        return allSubsets;
    }
};