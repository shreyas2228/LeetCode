/*
======================================================================================
LEETCODE 21: Merge Two Sorted Lists
======================================================================================

PROBLEM STATEMENT:
------------------
You are given the heads of two sorted linked lists list1 and list2.
Merge the two lists into one sorted list by splicing together the nodes of the 
two lists.

Return the head of the merged linked list.

EXAMPLES:
---------
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = [0]
Output: [0]

Input: list1 = [], list2 = []
Output: []

======================================================================================
APPROACH 1: RECURSIVE ⭐ ELEGANT ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
Think recursively: To merge two lists, pick the smaller head and attach it to 
the result of merging the remaining lists.

KEY INSIGHT:
- Compare the two heads
- The smaller one becomes the next node in merged list
- Recursively merge the rest

RECURSIVE THINKING:
-------------------
merge([1,2,4], [1,3,4]):
  1 <= 1, so take first 1
  1->next = merge([2,4], [1,3,4])
    2 > 1, so take second 1
    1->next = merge([2,4], [3,4])
      2 < 3, so take 2
      2->next = merge([4], [3,4])
        4 > 3, so take 3
        3->next = merge([4], [4])
          4 <= 4, so take first 4
          4->next = merge([], [4])
            Return [4]
Result: 1→1→2→3→4→4

VISUALIZATION:
--------------
List1: 1 → 2 → 4 → NULL
List2: 1 → 3 → 4 → NULL

Step 1: Compare 1 vs 1 → Equal, take list1's 1
        Result: 1 → merge([2,4], [1,3,4])

Step 2: Compare 2 vs 1 → 1 smaller, take list2's 1
        Result: 1 → 1 → merge([2,4], [3,4])

Step 3: Compare 2 vs 3 → 2 smaller, take 2
        Result: 1 → 1 → 2 → merge([4], [3,4])

And so on...

ALGORITHM:
----------
1. Base Case: If either list is NULL
   - Return the other list (it's already sorted)

2. Recursive Case:
   a. Compare heads of both lists (head1->val vs head2->val)
   b. If head1 is smaller or equal:
      - head1->next = merge(head1->next, head2)
      - return head1
   c. Else (head2 is smaller):
      - head2->next = merge(head1, head2->next)
      - return head2

TIME COMPLEXITY: O(m + n)
- m = length of list1, n = length of list2
- Each node is visited exactly once
- Each recursive call processes one node

SPACE COMPLEXITY: O(m + n)
- Recursion stack depth = m + n (total nodes)
- Each call adds one frame to stack

PROS:
- ⭐ Very elegant and concise
- ⭐ Easy to understand conceptually
- ⭐ Natural recursive structure
- ⭐ Good for interviews (shows recursion understanding)

CONS:
- Uses O(m+n) stack space
- Risk of stack overflow for very long lists
- Slightly slower due to function call overhead

======================================================================================
APPROACH 2: ITERATIVE (DUMMY NODE)
======================================================================================

INTUITION:
Use a dummy node to avoid edge cases, build merged list iteratively.

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // Create dummy node to simplify code
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        // While both lists have nodes
        while(l1 != NULL && l2 != NULL) {
            if(l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        // Attach remaining nodes (one list is exhausted)
        tail->next = (l1 != NULL) ? l1 : l2;
        
        return dummy.next;
    }

TIME: O(m + n)
SPACE: O(1) ⭐ More space efficient!

PROS:
- No recursion (no stack space)
- Better for very long lists
- More space efficient

CONS:
- Slightly more code
- Need to manage tail pointer
- Less elegant than recursive

======================================================================================
APPROACH 3: ITERATIVE WITHOUT DUMMY NODE
-----------------------------------------

Track head separately, more edge cases:

    if(!l1) return l2;
    if(!l2) return l1;
    
    ListNode* head = (l1->val <= l2->val) ? l1 : l2;
    ListNode* curr = head;
    
    if(head == l1) l1 = l1->next;
    else l2 = l2->next;
    
    while(l1 && l2) {
        if(l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    
    curr->next = l1 ? l1 : l2;
    return head;

More complex, not recommended.

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Recursive: Pick smaller head, attach to merge(rest)
2. ⭐ Base case: If one list is NULL, return the other
3. ⭐ Comparison: Use <= to handle equal values (either can go first)
4. ⭐ Recursive calls automatically handle all nodes
5. ⭐ Iterative version uses O(1) space but more code
6. ⭐ Both sorted → result is sorted (merging preserves order)

RECURSIVE PATTERN:
------------------
merge(head1, head2):
  if head1 is NULL: return head2
  if head2 is NULL: return head1
  
  if head1 <= head2:
    head1->next = merge(head1->next, head2)
    return head1
  else:
    head2->next = merge(head1, head2->next)
    return head2

EDGE CASES:
-----------
1. Both lists empty → return NULL (handled by base case)
2. One list empty → return other list (handled by base case)
3. Lists of different lengths → works fine
4. Duplicate values → handled by <= comparison
5. Single nodes in each list → base case handles

COMMON MISTAKES TO AVOID:
--------------------------
❌ Not handling NULL lists (missing base case)
❌ Using < instead of <= (doesn't matter but <= is clearer)
❌ Forgetting to return the head
❌ Creating new nodes instead of reusing existing ones
❌ Not understanding that this modifies original lists

WHY RECURSIVE APPROACH WORKS:
------------------------------
1. Lists are already sorted
2. Smallest element is always at one of the heads
3. Pick smaller head, rest of problem is identical (but smaller)
4. Base case: empty list → return other list
5. Recursive calls build the merged list automatically

SIMILAR TO MERGE SORT:
----------------------
This is essentially the "merge" step from merge sort algorithm!
Difference: here we're merging linked lists, in merge sort we merge arrays.

WHEN TO USE EACH APPROACH:
---------------------------
Recursive:
- Clean, readable code priority
- Normal-sized lists
- Demonstrating recursion understanding

Iterative:
- Very long lists (avoid stack overflow)
- Space-critical applications
- Production code

RELATED PROBLEMS:
-----------------
- LeetCode 23: Merge k Sorted Lists (extension of this)
- LeetCode 88: Merge Sorted Array (array version)
- LeetCode 148: Sort List (uses merge sort)
- LeetCode 1634: Merge In Between Linked Lists
- Merge step in Merge Sort

INTERVIEW TIP:
--------------
Mention both approaches! Start with recursive for elegance, then discuss 
iterative for space optimization. This shows breadth of knowledge.

======================================================================================
*/

// ============================================================================
// LEETCODE 21: Merge Two Sorted Lists
// ============================================================================

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        // BASE CASE 1: If either list is empty, return the other
        // The other list is already sorted, so it's our answer
        if(head1 == NULL || head2 == NULL){
            return head1 == NULL ? head2 : head1;
        }
        
        // RECURSIVE CASE: Pick smaller head and recursively merge rest
        
        // Case 1: head1's value is smaller or equal
        if(head1->val <= head2->val){
            // Take head1 as next node in merged list
            // Recursively merge head1's rest with entire head2
            head1->next = mergeTwoLists(head1->next, head2);
            return head1;  // head1 is the current smallest node
        }
        else{  // Case 2: head2's value is smaller
            // Take head2 as next node in merged list
            // Recursively merge entire head1 with head2's rest
            head2->next = mergeTwoLists(head1, head2->next);
            return head2;  // head2 is the current smallest node
        }
        
        // How it works:
        // Each call picks the smaller head and returns it
        // The returned node's next pointer is set to result of merging rest
        // Recursion automatically builds the complete merged list
    }
};