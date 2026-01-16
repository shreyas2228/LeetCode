/*
======================================================================================
LEETCODE 88: Merge Sorted Array
======================================================================================

PROBLEM STATEMENT:
------------------
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one 
sorted array.

IMPORTANT CONSTRAINTS:
- nums1 has size m + n (m elements + n extra spaces)
- nums2 has size n
- Merge IN-PLACE into nums1
- Final result should be stored in nums1

EXAMPLES:
---------
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]

Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]

======================================================================================
APPROACH 1: THREE POINTER (BACKWARD) ⭐ OPTIMAL ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
KEY INSIGHT: If we merge from the BACK (right to left), we can use the empty 
             space in nums1 without overwriting any unprocessed elements!

Imagine you have:
nums1 = [1, 2, 3, _, _, _]  (m = 3)
nums2 = [2, 5, 6]           (n = 3)

If we start from front, we'd overwrite elements in nums1.
But if we start from back, the empty spaces are waiting for us!

Compare largest elements from both arrays and place the bigger one at the end.

VISUALIZATION:
--------------
Step-by-step for nums1=[1,2,3,_,_,_], nums2=[2,5,6]:

Initial:  [1, 2, 3, _, _, _]   [2, 5, 6]
           i=2                  j=2      idx=5
Compare 3 vs 6 → 6 larger → [1, 2, 3, _, _, 6]

Step 2:   [1, 2, 3, _, _, 6]   [2, 5, 6]
           i=2                  j=1      idx=4
Compare 3 vs 5 → 5 larger → [1, 2, 3, _, 5, 6]

Step 3:   [1, 2, 3, _, 5, 6]   [2, 5, 6]
           i=2                  j=0      idx=3
Compare 3 vs 2 → 3 larger → [1, 2, 3, 3, 5, 6]

Step 4:   [1, 2, 3, 3, 5, 6]   [2, 5, 6]
           i=1                  j=0      idx=2
Compare 2 vs 2 → equal, take A[i] → [1, 2, 2, 3, 5, 6]

Step 5:   [1, 2, 2, 3, 5, 6]   [2, 5, 6]
           i=0                  j=0      idx=1
Compare 1 vs 2 → 2 larger → [1, 2, 2, 3, 5, 6]

Done! (j < 0, no more B elements)

ALGORITHM:
----------
1. Initialize three pointers:
   - i = m - 1 (last element of nums1's valid portion)
   - j = n - 1 (last element of nums2)
   - idx = m + n - 1 (last position in nums1)

2. While both arrays have elements (i >= 0 && j >= 0):
   - Compare A[i] and B[j]
   - Place larger element at position idx
   - Decrement the pointer of array from which we took element
   - Decrement idx

3. After main loop, if B still has elements, copy them:
   - A[idx--] = B[j--]
   
4. If A still has elements, they're already in place! (no action needed)

TIME COMPLEXITY: O(m + n)
- Process each element exactly once
- m + n comparisons at most

SPACE COMPLEXITY: O(1)
- In-place merging, only using a few pointers
- No extra arrays needed

PROS:
- ⭐ Optimal time and space
- ⭐ In-place solution (no extra array)
- ⭐ Clever use of available space
- ⭐ Perfect for interviews

CONS:
- Slightly less intuitive than forward merging
- Need to be careful with pointer management

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: MERGE INTO TEMP ARRAY, THEN COPY BACK
--------------------------------------------------
Use standard merge logic from merge sort:

    vector<int> temp(m + n);
    int i = 0, j = 0, k = 0;
    
    while(i < m && j < n) {
        if(nums1[i] <= nums2[j])
            temp[k++] = nums1[i++];
        else
            temp[k++] = nums2[j++];
    }
    
    while(i < m) temp[k++] = nums1[i++];
    while(j < n) temp[k++] = nums2[j++];
    
    for(int i = 0; i < m + n; i++)
        nums1[i] = temp[i];

TIME: O(m + n)
SPACE: O(m + n) - extra array

Simpler but uses extra space (not optimal for this problem).

APPROACH 3: INSERT FROM nums2 THEN SORT
----------------------------------------
Copy all nums2 elements to nums1, then sort:

    for(int i = 0; i < n; i++)
        nums1[m + i] = nums2[i];
    sort(nums1.begin(), nums1.end());

TIME: O((m + n) log(m + n))
SPACE: O(1) or O(log n) depending on sort

Simple but slower. Not recommended for interviews.

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Merge from BACK to avoid overwriting unprocessed elements
2. ⭐ Three pointers: i (end of A), j (end of B), idx (end of result)
3. ⭐ Place larger element at current position
4. ⭐ After main loop, only need to copy remaining B elements (if any)
5. ⭐ Remaining A elements are already in correct position
6. ⭐ Time: O(m + n), Space: O(1) - optimal solution

WHY WE DON'T NEED TO COPY REMAINING A ELEMENTS:
------------------------------------------------
If loop ends with j < 0 (all B elements processed), remaining A elements 
are ALREADY at the beginning of nums1 in sorted order. No copying needed!

Only when i < 0 (all A elements processed) do we need to copy remaining B elements.

POINTER MOVEMENT PATTERN:
-------------------------
- Compare A[i] vs B[j]
- Place larger one at idx
- Move pointer of array we took from (i-- or j--)
- Always move idx backward (idx--)

EDGE CASES TO REMEMBER:
-----------------------
1. m = 0 (nums1 empty): Copy all of nums2
2. n = 0 (nums2 empty): nums1 already sorted, do nothing
3. All nums1 elements > all nums2 elements
4. All nums2 elements > all nums1 elements

COMMON MISTAKES TO AVOID:
--------------------------
❌ Starting from front (overwrites unprocessed elements)
❌ Forgetting to copy remaining elements from nums2
❌ Trying to copy remaining elements from nums1 (not needed!)
❌ Using >= when should use > (or vice versa)

RELATED PROBLEMS:
-----------------
- LeetCode 21: Merge Two Sorted Lists (linked list version)
- Merge Sort algorithm
- LeetCode 986: Interval List Intersections
- Two pointer technique problems

======================================================================================
*/

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        // Three pointers approach - merge from back to front
        // idx: current position to fill in A (moving backward)
        // i: last valid element in A's original portion
        // j: last element in B
        
        int idx = m + n - 1;  // Last position in merged array
        int i = m - 1;         // Last element of A's valid portion
        int j = n - 1;         // Last element of B

        // Main merging loop - compare elements from back
        // Continue while both arrays have unprocessed elements
        while(i >= 0 && j >= 0)
        {
            if(A[i] >= B[j])
            {
                // A's element is larger (or equal) - place it at current position
                A[idx--] = A[i--];
            }
            else
            {
                // B's element is larger - place it at current position
                A[idx--] = B[j--];
            }
        }
        
        // Copy any remaining elements from B
        // (If there are remaining elements in A, they're already in place)
        while(j >= 0)
        {
            A[idx--] = B[j--];
        }
        
        // Note: No need to copy remaining A elements because they're
        // already at the beginning of A in their correct sorted positions!
    }
};