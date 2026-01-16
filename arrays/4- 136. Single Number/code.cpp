/*
======================================================================================
LEETCODE 136: Single Number
======================================================================================

PROBLEM STATEMENT:
------------------
Given a non-empty array of integers nums, every element appears TWICE except for 
one element which appears ONCE. Find that single element.

CONSTRAINTS:
- Must implement in O(n) time
- Must use O(1) extra space (no hash maps allowed!)

EXAMPLES:
---------
Input: nums = [2,2,1]
Output: 1

Input: nums = [4,1,2,1,2]
Output: 4

Input: nums = [1]
Output: 1

======================================================================================
APPROACH 1: XOR BIT MANIPULATION ⭐ OPTIMAL ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
This problem is a CLASSIC application of XOR (^) operator!

XOR PROPERTIES (Must memorize!):
1. a ^ a = 0        (any number XORed with itself is 0)
2. a ^ 0 = a        (any number XORed with 0 is itself)
3. XOR is commutative: a ^ b = b ^ a
4. XOR is associative: (a ^ b) ^ c = a ^ (b ^ c)

MAGIC:
If we XOR all numbers together, pairs cancel out (become 0), 
leaving only the single number!

EXAMPLE WALKTHROUGH:
--------------------
nums = [4, 1, 2, 1, 2]

Step by step:
result = 0
result = 0 ^ 4   = 4     (binary: 0000 ^ 0100 = 0100)
result = 4 ^ 1   = 5     (binary: 0100 ^ 0001 = 0101)
result = 5 ^ 2   = 7     (binary: 0101 ^ 0010 = 0111)
result = 7 ^ 1   = 6     (binary: 0111 ^ 0001 = 0110)
result = 6 ^ 2   = 4     (binary: 0110 ^ 0010 = 0100)

Final result = 4 ✓

MATHEMATICAL EXPLANATION:
4 ^ 1 ^ 2 ^ 1 ^ 2
= 4 ^ (1 ^ 1) ^ (2 ^ 2)    [Rearrange using associative property]
= 4 ^ 0 ^ 0                 [Apply a ^ a = 0]
= 4                         [Apply a ^ 0 = a]

ALGORITHM:
----------
1. Initialize result = 0
2. XOR result with each element in array
3. Return result (pairs cancel, single remains)

TIME COMPLEXITY: O(n)
- Single pass through array
- Optimal!

SPACE COMPLEXITY: O(1)
- Only using one variable
- Optimal!

PROS:
- ⭐ Extremely efficient: O(n) time, O(1) space
- ⭐ Elegant one-liner solution
- ⭐ Perfect interview answer
- ⭐ No extra data structures needed
- ⭐ Works for any array size

CONS:
- Requires understanding of XOR operator
- Not immediately obvious to beginners

======================================================================================
ALTERNATIVE APPROACHES (Not Allowed by Constraints):
======================================================================================

APPROACH 2: HASH SET
--------------------
    unordered_set<int> seen;
    for(int num : nums) {
        if(seen.count(num))
            seen.erase(num);    // Seen twice, remove
        else
            seen.insert(num);   // First time seeing
    }
    return *seen.begin();       // Only element left

TIME: O(n)
SPACE: O(n) ❌ Violates space constraint!

APPROACH 3: HASH MAP (FREQUENCY COUNTER)
-----------------------------------------
    unordered_map<int, int> freq;
    for(int num : nums)
        freq[num]++;
    
    for(auto& p : freq)
        if(p.second == 1)
            return p.first;

TIME: O(n)
SPACE: O(n) ❌ Violates space constraint!

APPROACH 4: SORTING
-------------------
Sort array, then check adjacent pairs:

    sort(nums.begin(), nums.end());
    for(int i = 0; i < n-1; i += 2) {
        if(nums[i] != nums[i+1])
            return nums[i];
    }
    return nums[n-1];  // Last element is single

TIME: O(n log n) ❌ Violates time constraint!
SPACE: O(1)

APPROACH 5: SUM METHOD (If range is known)
-------------------------------------------
If values are 1 to n, use math:

    sum_unique = sum of unique elements
    sum_all = sum of all elements
    single = 2 * sum_unique - sum_all

Doesn't work for arbitrary ranges.

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ XOR Magic: a ^ a = 0, a ^ 0 = a
2. ⭐ XOR is commutative & associative (order doesn't matter)
3. ⭐ XORing all elements cancels pairs, leaves single element
4. ⭐ Initialize result = 0 (identity element for XOR)
5. ⭐ This is THE optimal solution: O(n) time, O(1) space
6. ⭐ Works because each number appears exactly twice except one

XOR TRUTH TABLE (Good to remember):
------------------------------------
0 ^ 0 = 0
0 ^ 1 = 1
1 ^ 0 = 1
1 ^ 1 = 0

In short: XOR returns 1 if bits are DIFFERENT, 0 if SAME

BIT MANIPULATION PATTERNS:
--------------------------
- Check if bit is set: (n & (1 << i))
- Set a bit: n | (1 << i)
- Clear a bit: n & ~(1 << i)
- Toggle a bit: n ^ (1 << i)
- XOR to find single element: THIS PROBLEM!

WHY XOR IS PERFECT HERE:
------------------------
Since every number appears EXACTLY twice except one:
- Each pair cancels itself out (becomes 0)
- The single number XORed with 0 remains itself
- Order doesn't matter (commutative property)

COMMON MISTAKES TO AVOID:
--------------------------
❌ Using AND (&) or OR (|) instead of XOR (^)
❌ Initializing result to first element instead of 0
❌ Trying to use extra space (hash map/set) when not needed
❌ Overthinking - this problem has elegant one-line solution!

WHEN TO USE XOR PATTERN:
------------------------
- Finding element that appears odd number of times
- Swapping without temp variable: a ^= b; b ^= a; a ^= b;
- Finding missing number in sequence
- Detecting if two numbers are different
- Problems with "all pairs except one" pattern

RELATED PROBLEMS:
-----------------
- LeetCode 137: Single Number II (appears 3 times)
- LeetCode 260: Single Number III (two unique numbers)
- LeetCode 268: Missing Number (use XOR)
- LeetCode 389: Find the Difference (use XOR)
- LeetCode 461: Hamming Distance (XOR + count bits)

======================================================================================
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // XOR all elements together
        // Pairs cancel out (a ^ a = 0), single element remains (a ^ 0 = a)
        int result = 0;
        
        for (int num : nums) {
            result ^= num;  // XOR operation
        }
        
        return result;
        
        // ONE-LINE VERSION:
        // return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
    }
};