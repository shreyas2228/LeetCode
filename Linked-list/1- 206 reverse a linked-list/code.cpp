/*
======================================================================================
LEETCODE 206: Reverse Linked List
======================================================================================

PROBLEM STATEMENT:
------------------
Given the head of a singly linked list, reverse the list and return the reversed 
list's head.

EXAMPLES:
---------
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Input: head = [1,2]
Output: [2,1]

Input: head = []
Output: []

======================================================================================
APPROACH 1: ITERATIVE (THREE POINTERS) ⭐ OPTIMAL ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
To reverse a linked list, we need to reverse the direction of all pointers.
Original:  1 → 2 → 3 → 4 → 5 → NULL
Reversed:  NULL ← 1 ← 2 ← 3 ← 4 ← 5

KEY IDEA: Traverse the list and change each node's next pointer to point to 
          its previous node.

CHALLENGE: When we change curr->next, we lose the reference to the rest of 
           the list! So we need to save it first.

SOLUTION: Use three pointers:
- prev: points to the previous node (initially NULL)
- curr: points to the current node being processed
- next: temporarily stores the next node before we change curr->next

VISUALIZATION:
--------------
Initial: NULL ← prev  curr → 2 → 3 → 4 → 5 → NULL
                      1

Step 1: Save next, reverse link, move pointers
        NULL ← prev ← curr   next → 3 → 4 → 5 → NULL
                     1        2

Step 2: Move pointers forward
        NULL ← 1 ← prev  curr → 3 → 4 → 5 → NULL
                        2

Step 3: Continue...
        NULL ← 1 ← 2 ← prev  curr → 4 → 5 → NULL
                            3

Step 4: Continue...
        NULL ← 1 ← 2 ← 3 ← prev  curr → 5 → NULL
                                4

Step 5: Last iteration
        NULL ← 1 ← 2 ← 3 ← 4 ← prev  curr → NULL
                                    5

Final: prev points to new head (5), curr is NULL

ALGORITHM:
----------
1. Initialize:
   - prev = NULL (reversed list starts as empty)
   - curr = head (start from first node)
   - next = NULL

2. While curr is not NULL:
   a. Save next node: next = curr->next
   b. Reverse link: curr->next = prev
   c. Move prev forward: prev = curr
   d. Move curr forward: curr = next

3. Return prev (new head of reversed list)

TIME COMPLEXITY: O(n)
- Visit each node exactly once
- n nodes total

SPACE COMPLEXITY: O(1)
- Only using three pointers
- In-place reversal, no extra data structures

PROS:
- ⭐ Optimal time and space
- ⭐ In-place reversal (no extra nodes created)
- ⭐ Easy to understand with practice
- ⭐ Iterative (no stack overflow risk)

CONS:
- Requires careful pointer management
- Easy to make mistakes with pointer updates

======================================================================================
APPROACH 2: RECURSIVE
======================================================================================

INTUITION:
Recursively reverse the rest of the list, then fix current node.

    ListNode* reverseList(ListNode* head) {
        // Base case: empty list or single node
        if(head == NULL || head->next == NULL)
            return head;
        
        // Recursively reverse rest of list
        ListNode* newHead = reverseList(head->next);
        
        // Reverse current node's link
        // head->next currently points to second node
        // Make second node point back to head
        head->next->next = head;
        head->next = NULL;  // Current head becomes tail
        
        return newHead;
    }

VISUALIZATION:
Original: 1 → 2 → 3 → 4 → 5 → NULL

Recursion unwinds:
- Reverse(5): returns 5
- Reverse(4): 5 → 4, returns 5
- Reverse(3): 5 → 4 → 3, returns 5
- Reverse(2): 5 → 4 → 3 → 2, returns 5
- Reverse(1): 5 → 4 → 3 → 2 → 1 → NULL, returns 5

TIME: O(n)
SPACE: O(n) - recursion stack

PROS:
- Elegant and concise
- Good for understanding recursion

CONS:
- Uses O(n) stack space
- Can cause stack overflow for very long lists
- Harder to debug

======================================================================================
APPROACH 3: USING STACK
======================================================================================

Push all nodes to stack, then pop and rebuild:

    stack<ListNode*> st;
    ListNode* temp = head;
    
    while(temp != NULL) {
        st.push(temp);
        temp = temp->next;
    }
    
    if(st.empty()) return NULL;
    
    head = st.top();
    st.pop();
    temp = head;
    
    while(!st.empty()) {
        temp->next = st.top();
        st.pop();
        temp = temp->next;
    }
    temp->next = NULL;
    
    return head;

TIME: O(n)
SPACE: O(n) - stack storage

Not recommended (wastes space).

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Three pointers: prev, curr, next
2. ⭐ Pattern: save next, reverse link, move forward
3. ⭐ prev starts as NULL (new tail), curr starts at head
4. ⭐ Return prev (it becomes new head after loop)
5. ⭐ Each iteration: next = curr->next; curr->next = prev; prev = curr; curr = next
6. ⭐ Iterative: O(1) space, Recursive: O(n) space

POINTER UPDATE ORDER (CRITICAL!):
----------------------------------
1. next = curr->next        (Save next node BEFORE breaking link)
2. curr->next = prev        (Reverse the link)
3. prev = curr              (Move prev forward)
4. curr = next              (Move curr forward)

If you change this order, you'll lose references or create loops!

COMMON MISTAKES TO AVOID:
--------------------------
❌ Forgetting to save next before changing curr->next
❌ Wrong order of pointer updates
❌ Returning curr instead of prev
❌ Not handling empty list (head == NULL)
❌ Creating circular reference (forgetting to set old head->next = NULL in recursion)

EDGE CASES:
-----------
1. Empty list (head = NULL) → return NULL
2. Single node → return same node
3. Two nodes → reverse normally
4. Very long list → iterative preferred (no stack overflow)

WHEN TO USE EACH APPROACH:
---------------------------
- Iterative: Default choice (optimal space)
- Recursive: When code clarity is priority, or learning recursion
- Stack: Never (wastes space for no benefit)

RELATED PROBLEMS:
-----------------
- LeetCode 92: Reverse Linked List II (reverse portion of list)
- LeetCode 25: Reverse Nodes in k-Group
- LeetCode 234: Palindrome Linked List (uses reversal)
- LeetCode 143: Reorder List
- Any problem requiring linked list manipulation

INTERVIEW TIP:
--------------
Always start by explaining the iterative approach first, then mention 
recursive as alternative. Draw diagrams to show pointer movements!

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
    ListNode* reverseList(ListNode* head) {
        // Three pointers for iterative reversal
        
        // prev: points to the previous node in reversed list
        // Initially NULL because reversed list starts empty
        ListNode* prev = NULL;
        
        // curr: points to current node being processed
        // Start from the head of original list
        ListNode* curr = head;
        
        // next: temporarily stores the next node
        // Needed because we'll change curr->next
        ListNode* next = NULL;

        // Traverse the entire list
        while(curr != NULL){
            // Step 1: Save the next node (MUST do this first!)
            // If we don't save it, we'll lose reference to rest of list
            next = curr->next;
            
            // Step 2: Reverse the link
            // Make current node point to previous node instead of next
            curr->next = prev;

            // Step 3: Move prev pointer forward
            // Current node becomes previous for next iteration
            prev = curr;
            
            // Step 4: Move curr pointer forward
            // Process the next node in original list
            curr = next;
        }
        
        // When loop ends:
        // - curr is NULL
        // - prev points to last node of original list
        // - prev is now the head of reversed list
        return prev;
    }
};