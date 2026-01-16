/*
======================================================================================
LEETCODE 876: Middle of the Linked List
======================================================================================

PROBLEM STATEMENT:
------------------
Given the head of a singly linked list, return the middle node.
If there are TWO middle nodes (even length), return the SECOND middle node.

EXAMPLES:
---------
Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: Middle node is 3 (position 2 in 0-indexed)

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Two middle nodes are 3 and 4, return second one (4)

Input: head = [1]
Output: [1]

======================================================================================
APPROACH 1: SLOW-FAST POINTER (TORTOISE & HARE) ⭐ OPTIMAL ⭐
======================================================================================

INTUITION:
----------
CLASSIC Two-Pointer Technique!

KEY IDEA: 
- Use two pointers moving at different speeds
- Slow pointer moves 1 step at a time
- Fast pointer moves 2 steps at a time
- When fast reaches the end, slow is at the middle!

WHY IT WORKS:
-------------
If fast moves 2x speed of slow:
- When fast travels n steps, slow travels n/2 steps
- When fast reaches end (n steps), slow is at middle (n/2)

VISUALIZATION (ODD LENGTH):
---------------------------
List: 1 → 2 → 3 → 4 → 5 → NULL

Step 0: slow → 1, fast → 1
Step 1: slow → 2, fast → 3
Step 2: slow → 3, fast → 5
Step 3: slow → 3, fast → NULL (loop ends)

Middle = 3 ✓

VISUALIZATION (EVEN LENGTH):
----------------------------
List: 1 → 2 → 3 → 4 → 5 → 6 → NULL

Step 0: slow → 1, fast → 1
Step 1: slow → 2, fast → 3
Step 2: slow → 3, fast → 5
Step 3: slow → 4, fast → NULL (loop ends)

Middle = 4 (second middle) ✓

ALGORITHM:
----------
1. Initialize both slow and fast pointers to head
2. While fast is not NULL AND fast->next is not NULL:
   a. Move slow one step: slow = slow->next
   b. Move fast two steps: fast = fast->next->next
3. Return slow (it's at the middle)

LOOP CONDITIONS EXPLAINED:
--------------------------
- fast != NULL: Handles odd-length lists (fast reaches last node)
- fast->next != NULL: Handles even-length lists (fast reaches NULL)

Both conditions needed to avoid NULL pointer access!

TIME COMPLEXITY: O(n)
- Visit approximately n/2 nodes with slow pointer
- Visit approximately n nodes with fast pointer
- Overall: O(n)

SPACE COMPLEXITY: O(1)
- Only using two pointers
- No extra data structures

PROS:
- ⭐ Optimal time and space
- ⭐ Single pass solution
- ⭐ Elegant two-pointer technique
- ⭐ No need to count list length
- ⭐ Very common interview pattern

CONS:
- None! This is the standard optimal solution.

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: TWO-PASS (COUNT LENGTH FIRST)
------------------------------------------
Count total length, then traverse to middle:

    // First pass: count length
    int length = 0;
    ListNode* temp = head;
    while(temp != NULL) {
        length++;
        temp = temp->next;
    }
    
    // Second pass: go to middle
    int mid = length / 2;
    temp = head;
    for(int i = 0; i < mid; i++) {
        temp = temp->next;
    }
    
    return temp;

TIME: O(n) - two passes
SPACE: O(1)

PROS: Easy to understand
CONS: Two passes (slow-fast is more elegant)

APPROACH 3: STORE IN ARRAY
---------------------------
Store all nodes in array, return middle index:

    vector<ListNode*> nodes;
    ListNode* temp = head;
    while(temp != NULL) {
        nodes.push_back(temp);
        temp = temp->next;
    }
    return nodes[nodes.size() / 2];

TIME: O(n)
SPACE: O(n) ❌ Wastes space!

Not recommended.

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Classic Slow-Fast Pointer Pattern (Tortoise & Hare)
2. ⭐ Slow moves 1 step, Fast moves 2 steps
3. ⭐ When fast reaches end, slow is at middle
4. ⭐ Loop while (fast != NULL && fast->next != NULL)
5. ⭐ For even length, returns SECOND middle node
6. ⭐ Single pass, O(1) space - optimal!

WHY TWO CONDITIONS IN LOOP:
----------------------------
fast != NULL:
- Prevents accessing NULL->next
- Needed for odd-length lists
- Example: [1,2,3] → fast reaches node 3 (not NULL)

fast->next != NULL:
- Prevents accessing NULL->next->next in loop body
- Needed for even-length lists
- Example: [1,2,3,4] → fast reaches node 4, next is NULL

ODD vs EVEN LENGTH:
-------------------
Odd (5 nodes): [1,2,3,4,5]
- Fast ends at node 5 (fast != NULL, fast->next == NULL)
- Slow at node 3 (middle)

Even (6 nodes): [1,2,3,4,5,6]
- Fast ends at NULL (fast == NULL)
- Slow at node 4 (second middle)

COMMON MISTAKES TO AVOID:
--------------------------
❌ Only checking fast != NULL (causes NULL->next access)
❌ Only checking fast->next != NULL (incomplete)
❌ Moving fast only once (both pointers same speed)
❌ Starting pointers at different positions
❌ Forgetting to return slow pointer

VARIATIONS OF THIS PATTERN:
----------------------------
1. Find 1/3 point: fast moves 3x speed
2. Find 1/4 point: fast moves 4x speed
3. Detect cycle: slow-fast will meet if cycle exists
4. Find nth from end: gap between pointers

EDGE CASES:
-----------
1. Single node: [1] → returns 1 (slow = fast = head, loop doesn't run)
2. Two nodes: [1,2] → returns 2 (second middle)
3. Odd length: [1,2,3,4,5] → returns 3
4. Even length: [1,2,3,4,5,6] → returns 4

WHEN TO USE SLOW-FAST PATTERN:
-------------------------------
- Finding middle of linked list ⭐
- Detecting cycle in linked list (Floyd's algorithm)
- Finding start of cycle
- Checking if linked list is palindrome
- Finding nth node from end (with variation)
- Any "proportion" finding in linked list

RELATED PROBLEMS:
-----------------
- LeetCode 141: Linked List Cycle (detect cycle)
- LeetCode 142: Linked List Cycle II (find cycle start)
- LeetCode 234: Palindrome Linked List (uses middle finding)
- LeetCode 143: Reorder List
- LeetCode 19: Remove Nth Node From End

INTERVIEW TIP:
--------------
This is one of THE MOST COMMON linked list patterns!
Master it well - practice explaining why it works.
Draw diagrams showing both pointers' movements.

======================================================================================
*/

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
    ListNode* middleNode(ListNode* head) {
        // Two pointers: slow and fast (Tortoise and Hare algorithm)
        
        // Slow pointer: moves 1 step at a time
        ListNode* slow = head;
        
        // Fast pointer: moves 2 steps at a time
        ListNode* fast = head;

        // Continue while fast can move 2 steps
        // Two conditions needed:
        // 1. fast != NULL: for odd-length lists
        // 2. fast->next != NULL: for even-length lists
        while(fast != NULL && fast->next != NULL){
            // Move slow pointer one step forward
            slow = slow->next;
            
            // Move fast pointer two steps forward
            // When fast reaches end, slow will be at middle
            fast = fast->next->next;
        }
        
        // When loop ends:
        // - For odd length: fast is at last node, slow at middle
        // - For even length: fast is NULL, slow at second middle
        return slow;
    }
};