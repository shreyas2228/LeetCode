/*
======================================================================================
PROBLEM: Check for Duplicate Elements in Array
======================================================================================

PROBLEM STATEMENT:
------------------
Given an array of integers, determine if there are any duplicate elements.
Return true if any value appears at least twice, false otherwise.

EXAMPLE:
--------
Input: arr[] = {1,2,3,4,5}
Output: false (no duplicates)

Input: arr[] = {1,2,3,1,5}
Output: true (1 appears twice)

======================================================================================
APPROACH 1: BRUTE FORCE - NESTED LOOPS (Current Implementation)
======================================================================================

INTUITION:
----------
Compare each element with every other element in the array.
If any two elements are equal, we found a duplicate.

ALGORITHM:
----------
1. Use outer loop to pick each element (i from 0 to n-1)
2. Use inner loop to compare it with remaining elements (j from i+1 to n-1)
3. If arr[i] == arr[j], duplicate found → return true
4. If no match found after all comparisons → return false

TIME COMPLEXITY: O(n²)
- Outer loop runs n times
- Inner loop runs (n-1) + (n-2) + ... + 1 = n(n-1)/2 times
- Total: O(n²)

SPACE COMPLEXITY: O(1)
- Only using a few variables (i, j)

PROS:
- Simple to understand and implement
- No extra space required
- Works for any input size

CONS:
- Very slow for large arrays (quadratic time)
- Not optimal for interview settings

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: SORTING + LINEAR SCAN
----------------------------------
Sort the array, then check adjacent elements.
Duplicates will be next to each other after sorting.

    sort(arr, arr + n);
    for(int i = 0; i < n-1; i++) {
        if(arr[i] == arr[i+1])
            return true;
    }
    return false;

TIME: O(n log n) - sorting dominates
SPACE: O(1) if in-place sort, O(n) otherwise

APPROACH 3: HASH SET (OPTIMAL)
-------------------------------
Use an unordered_set to track seen elements in O(1) time.

    unordered_set<int> seen;
    for(int i = 0; i < n; i++) {
        if(seen.count(arr[i])) 
            return true;  // Found duplicate
        seen.insert(arr[i]);
    }
    return false;

TIME: O(n) - single pass
SPACE: O(n) - for hash set

THIS IS THE BEST APPROACH for most cases!

APPROACH 4: HASH MAP/FREQUENCY COUNTER
---------------------------------------
Count frequency of each element.
If any frequency > 1, duplicate exists.

    unordered_map<int, int> freq;
    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if(freq[arr[i]] > 1)
            return true;
    }
    return false;

TIME: O(n)
SPACE: O(n)

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Brute force: Compare all pairs → O(n²) time, O(1) space
2. ⭐ Sorting: Makes duplicates adjacent → O(n log n) time
3. ⭐ Hash Set: Best balance → O(n) time, O(n) space
4. ⭐ Trade-off: Time vs Space (hash set uses more space but much faster)

RELATED PROBLEMS:
-----------------
- LeetCode 217: Contains Duplicate (same problem)
- LeetCode 219: Contains Duplicate II (within k distance)
- LeetCode 220: Contains Duplicate III (value difference)

WHEN TO USE EACH APPROACH:
---------------------------
- Brute Force: Small arrays, no extra space allowed, educational purposes
- Sorting: When you can modify array, moderate space constraints
- Hash Set: When you need optimal time complexity (interviews!)
- Hash Map: When you also need frequency information

======================================================================================
*/

#include<iostream>
using namespace std;

// Function: Check if array contains duplicate elements
// Parameters:
//   arr[] - input array to check
//   n - size of array
// Returns: true if duplicate found, false otherwise
bool search(int arr[], int n){
    // Brute force approach: compare each element with all others
    // Outer loop: pick each element
    for(int i = 0; i < n; i++){
        // Inner loop: compare with remaining elements
        for(int j = i + 1; j < n; j++){
            // If same value found, we have a duplicate
            if(arr[i] == arr[j]){
                return true;
            }
        }
    }
    // No duplicates found after checking all pairs
    return false;
}

int main(){
    // Test case: array without duplicates
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Calculate array size using pointer arithmetic
    // sizeof(arr) gives total bytes, sizeof(int) gives bytes per element
    int n = sizeof(arr) / sizeof(int);
    
    // Check for duplicates and display result
    if(search(arr, n)){
        cout << "Duplicate found" << endl;
    } else {
        cout << "No duplicates" << endl;
    }
}