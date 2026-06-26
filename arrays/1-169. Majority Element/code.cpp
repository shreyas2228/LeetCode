/*
======================================================================================
LEETCODE 169: Majority Element
======================================================================================

PROBLEM STATEMENT:
------------------
Given an array nums of size n, find the majority element.
The majority element is the element that appears MORE than ⌊n/2⌋ times.
You may assume that the majority element always exists in the array.

EXAMPLES:
---------
Input: nums = [3,2,3]
Output: 3 (appears 2 times out of 3, which is > 1.5)

Input: nums = [2,2,1,1,1,2,2]
Output: 2 (appears 4 times out of 7, which is > 3.5)

KEY CONSTRAINT:
The majority element ALWAYS exists (appears > n/2 times)
This guarantees we'll always find an answer.

======================================================================================
APPROACH 1: BRUTE FORCE - COUNT FREQUENCY FOR EACH ELEMENT
======================================================================================

INTUITION:
----------
For each unique element, count how many times it appears.
If count > n/2, that's our majority element.

ALGORITHM:
----------
1. For each element in array (outer loop)
2. Count its frequency by checking against all elements (inner loop)
3. If frequency > n/2, return that element
4. Otherwise, continue checking

TIME COMPLEXITY: O(n²)
- Outer loop: n iterations
- Inner loop: n iterations for each
- Total: n × n = O(n²)

SPACE COMPLEXITY: O(1)
- Only using variables freq and el

PROS:
- Simple and straightforward
- No extra data structures needed
- Easy to understand

CONS:
- Very slow for large arrays (quadratic time)
- Inefficient - recounts same elements multiple times

======================================================================================
APPROACH 2: SORTING + FREQUENCY COUNT
======================================================================================

INTUITION:
----------
After sorting, identical elements are grouped together.
Count consecutive elements to find frequency.
The majority element will appear in a contiguous block of size > n/2.

KEY INSIGHT: Since majority element appears > n/2 times, it MUST occupy 
             the middle position (index n/2) after sorting!
             
SIMPLIFIED VERSION:
    sort(nums.begin(), nums.end());
    return nums[n/2];  // Middle element is always the majority!

YOUR VERSION (with frequency counting):

ALGORITHM:
----------
1. Sort the array
2. Initialize freq = 1, ans = first element
3. Traverse array, comparing adjacent elements
4. If same as previous, increment frequency
5. If different, reset frequency to 1
6. When freq > n/2, we found the answer

TIME COMPLEXITY: O(n log n)
- Sorting: O(n log n)
- Traversing: O(n)
- Dominated by sorting: O(n log n)

SPACE COMPLEXITY: O(1) or O(n)
- Depends on sorting algorithm used
- In-place sort: O(1)
- Merge sort: O(n)

PROS:
- Faster than brute force
- Intuitive approach
- Can be simplified to just return nums[n/2]

CONS:
- Still not optimal (sorting overhead)
- Modifies original array (unless you copy it)

======================================================================================
APPROACH 3: BOYER-MOORE VOTING ALGORITHM ⭐ OPTIMAL ⭐
======================================================================================

INTUITION:
----------
Think of it as a "voting" or "battle" between elements:
- If current element matches candidate, it gets a vote (freq++)
- If it doesn't match, opposing element cancels a vote (freq--)
- When freq drops to 0, change candidate

Since majority element appears > n/2 times, it will "survive" all cancellations!

VISUAL EXAMPLE:
nums = [2,2,1,1,1,2,2]
Step 0: freq=0, ans=?          → Initialize
Step 1: freq=1, ans=2          → Pick 2 as candidate
Step 2: freq=2, ans=2          → Same element, vote++
Step 3: freq=1, ans=2          → Different (1), vote--
Step 4: freq=0, ans=2          → Vote cancelled
Step 5: freq=1, ans=1          → New candidate (1)
Step 6: freq=0, ans=1          → Vote cancelled by 2
Step 7: freq=1, ans=2          → New candidate (2)
Result: ans = 2 (majority element!)

ALGORITHM:
----------
1. Initialize freq = 0, ans = 0
2. For each element in array:
   a. If freq == 0, set current element as candidate (ans)
   b. If current element == candidate, increment freq
   c. If current element != candidate, decrement freq
3. Return ans (the surviving candidate)

TIME COMPLEXITY: O(n)
- Single pass through array
- Optimal time complexity!

SPACE COMPLEXITY: O(1)
- Only two variables: freq and ans
- Optimal space complexity!

WHY IT WORKS:
-------------
The majority element appears MORE than n/2 times.
Even if ALL other elements "vote against" it, the majority element 
will still have votes left over!

MATHEMATICAL PROOF:
If majority element appears m times where m > n/2,
and other elements appear (n - m) times,
then m - (n - m) = 2m - n > 0 (since m > n/2)

PROS:
- ⭐ Optimal O(n) time, O(1) space
- ⭐ Single pass through array
- ⭐ Very efficient for interviews
- ⭐ Elegant algorithm

CONS:
- Less intuitive (requires understanding of algorithm)
- Only works when majority element is GUARANTEED to exist
- If no majority element exists, needs verification pass (not needed here)

======================================================================================
APPROACH 4: HASH MAP (Alternative O(n) Solution)
======================================================================================

Use hash map to count frequencies:

    unordered_map<int, int> freq;
    for(int num : nums) {
        freq[num]++;
        if(freq[num] > n/2)
            return num;
    }

TIME: O(n)
SPACE: O(n) - hash map storage

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Brute Force: O(n²) time, O(1) space - count each element's frequency
2. ⭐ Sorting: O(n log n) time - can simplify to return nums[n/2]
3. ⭐ Boyer-Moore: O(n) time, O(1) space - BEST for interviews!
4. ⭐ Hash Map: O(n) time, O(n) space - easy but uses extra space
5. ⭐ Problem guarantees majority element exists (> n/2 occurrences)

INTERVIEW APPROACH:
-------------------
1. Start with brute force to show understanding
2. Optimize to sorting (mention nums[n/2] trick)
3. Present Boyer-Moore as optimal solution
4. Explain why it works (voting/cancellation concept)

WHEN TO USE BOYER-MOORE:
-------------------------
- Finding majority element (appears > n/2 times)
- When you need O(n) time and O(1) space
- When input guarantees majority exists
- Great pattern for "find dominant element" problems

RELATED PROBLEMS:
-----------------
- LeetCode 229: Majority Element II (appears > n/3 times)
- Finding most frequent element
- Stream processing with limited memory

======================================================================================
*/

// ============================================================================
// APPROACH 1: BRUTE FORCE - COUNT EACH ELEMENT'S FREQUENCY
// TIME: O(n²), SPACE: O(1)
// ============================================================================
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        
        // For each unique value in array
        for(int val : nums) {
            int freq = 0;
            
            // Count how many times it appears
            for(int el : nums) {
                if(el == val) {
                    freq++;
                }
            }
            
            // If appears more than n/2 times, it's the majority element
            if(freq > n / 2) {
                return val;
            }
        }
        
        // This line should never be reached as per problem constraints
        // (majority element always exists)
        return -1;
    }
};


// ============================================================================
// APPROACH 2: SORTING + FREQUENCY COUNT
// TIME: O(n log n), SPACE: O(1) or O(n) depending on sort
// ============================================================================
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();

        // Sort the array - identical elements will be grouped together
        sort(nums.begin(), nums.end());

        // Count frequency of consecutive elements
        int freq = 1, ans = nums[0];
        
        for(int i = 1; i < n; i++) {
            if(nums[i] == nums[i - 1]) {
                // Same as previous element - increment frequency
                freq++;
            } else {
                // Different element - reset frequency
                freq = 1;
                ans = nums[i];
            }

            // If frequency exceeds n/2, we found majority element
            if(freq > n / 2) {
                ans = nums[i];
                break;
            }
        }
        return ans;
        
        // SIMPLIFIED VERSION (recommended):
        // After sorting, majority element MUST be at index n/2
        // return nums[n/2];
    }
};


// ============================================================================
// APPROACH 3: BOYER-MOORE VOTING ALGORITHM ⭐ OPTIMAL ⭐
// TIME: O(n), SPACE: O(1)
// ============================================================================
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int freq = 0;   // Vote count for current candidate
        int ans = 0;    // Current majority candidate
        
        for(int i = 0; i < nums.size(); i++){
            // If no votes left, pick new candidate
            if(freq == 0){
                ans = nums[i];
            }
            
            // If current element matches candidate, add vote
            if(ans == nums[i]){
                freq++;
            } else {
                // Different element - cancel a vote
                freq--;
            }
        }
        
        // The surviving candidate is the majority element
        // (guaranteed to exist per problem constraints)
        return ans;
    }
};

