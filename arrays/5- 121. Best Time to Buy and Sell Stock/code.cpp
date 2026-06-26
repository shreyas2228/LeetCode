/*
======================================================================================
LEETCODE 121: Best Time to Buy and Sell Stock
======================================================================================

PROBLEM STATEMENT:
------------------
You are given an array prices where prices[i] is the price of a given stock on 
the i-th day.

Find the maximum profit you can achieve from ONE transaction (buy once, sell once).
- You must BUY before you SELL
- If no profit is possible, return 0

EXAMPLES:
---------
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1), sell on day 5 (price = 6), profit = 6-1 = 5

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: Prices only decrease, no profit possible

Input: prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2), sell on day 2 (price = 4), profit = 4-2 = 2

======================================================================================
APPROACH 1: KADANE'S ALGORITHM VARIANT ⭐ OPTIMAL ⭐ (Current Implementation)
======================================================================================

INTUITION:
----------
KEY INSIGHT: To maximize profit, we want to buy at the LOWEST price seen so far,
             and sell at current price if it gives better profit.

For each day:
1. Track the minimum price seen so far (best buy price)
2. Calculate profit if we sell today (current - minPrice)
3. Update maximum profit if today's profit is better

THINK OF IT AS:
- Always looking for the best buying opportunity (minimum price)
- At each price point, calculate: "What if I sell today?"
- Keep track of the best profit we've seen

VISUALIZATION:
--------------
prices = [7, 1, 5, 3, 6, 4]

Day 1: price=7, bestBuy=7, profit=0     (can't sell on first day)
Day 2: price=1, bestBuy=1, profit=0     (better buy price found!)
Day 3: price=5, bestBuy=1, profit=4     (sell at 5, bought at 1)
Day 4: price=3, bestBuy=1, profit=4     (no better profit)
Day 5: price=6, bestBuy=1, profit=5     (sell at 6, bought at 1) ⭐ Best!
Day 6: price=4, bestBuy=1, profit=5     (no better profit)

Final: maxProfit = 5

ALGORITHM:
----------
1. Initialize:
   - maxProfit = 0 (worst case: no profit)
   - bestBuy = prices[0] (first day is our initial buy price)

2. For each day starting from day 2:
   a. If current price > bestBuy:
      - Calculate profit = current - bestBuy
      - Update maxProfit if this profit is better
   b. Update bestBuy to minimum of (bestBuy, current price)

3. Return maxProfit

TIME COMPLEXITY: O(n)
- Single pass through array
- Optimal!

SPACE COMPLEXITY: O(1)
- Only using two variables
- Optimal!

PROS:
- ⭐ Extremely efficient: O(n) time, O(1) space
- ⭐ Single pass solution
- ⭐ Easy to understand and implement
- ⭐ Perfect for interviews

CONS:
- None! This is the optimal approach.

======================================================================================
ALTERNATIVE APPROACHES:
======================================================================================

APPROACH 2: BRUTE FORCE
-----------------------
Try all possible buy-sell pairs:

    int maxProfit = 0;
    for(int i = 0; i < n; i++) {        // Buy day
        for(int j = i+1; j < n; j++) {  // Sell day
            maxProfit = max(maxProfit, prices[j] - prices[i]);
        }
    }
    return maxProfit;

TIME: O(n²) - nested loops
SPACE: O(1)

❌ Too slow! Not acceptable in interviews.

APPROACH 3: TRACK MIN/MAX WITH EXTRA ARRAY
-------------------------------------------
Precompute minimum price up to each index:

    vector<int> minPrice(n);
    minPrice[0] = prices[0];
    for(int i = 1; i < n; i++)
        minPrice[i] = min(minPrice[i-1], prices[i]);
    
    int maxProfit = 0;
    for(int i = 1; i < n; i++)
        maxProfit = max(maxProfit, prices[i] - minPrice[i]);

TIME: O(n)
SPACE: O(n) ❌ Unnecessary extra space

Works but wastes space. Current solution is better.

APPROACH 4: DYNAMIC PROGRAMMING
--------------------------------
Think of it as: on each day, what's the max profit we can have?

    int minPrice = prices[0];
    int maxProfit = 0;
    for(int i = 1; i < n; i++) {
        maxProfit = max(maxProfit, prices[i] - minPrice);
        minPrice = min(minPrice, prices[i]);
    }

This is essentially the same as current approach!

======================================================================================
KEY INSIGHTS FOR REVISION:
======================================================================================
1. ⭐ Track minimum price seen so far (best buy opportunity)
2. ⭐ At each price, calculate profit if we sell today
3. ⭐ Keep updating maximum profit
4. ⭐ Must buy before sell (process left to right)
5. ⭐ Return 0 if no profit possible (initialization handles this)
6. ⭐ One pass, two variables - can't get more optimal!

PATTERN RECOGNITION:
--------------------
This problem uses the "Keep track of best so far" pattern:
- Track best buy price (minimum)
- Track best profit (maximum)
- Update both as we scan

Similar to:
- Maximum subarray (Kadane's algorithm)
- Sliding window problems
- Running min/max problems

COMMON MISTAKES TO AVOID:
--------------------------
❌ Trying to find global min and global max separately
   (they might not be in correct order!)
❌ Forgetting that you must buy before you sell
❌ Using nested loops (brute force)
❌ Not handling the case when all prices decrease
❌ Initializing bestBuy to 0 instead of prices[0]

WHY THIS WORKS:
---------------
At any point in time:
- We know the minimum price we've seen (best buy point so far)
- We calculate potential profit at current price
- We keep the maximum profit encountered

Since we scan left to right, we automatically ensure buy happens before sell!

EDGE CASES:
-----------
1. All prices decreasing: [5,4,3,2,1] → profit = 0
2. All prices same: [5,5,5,5] → profit = 0
3. Single element: [5] → profit = 0 (can't sell)
4. Best profit at end: [1,2,3,4,5] → profit = 4
5. Best profit in middle: [3,1,5,2,4] → profit = 4 (buy at 1, sell at 5)

WHEN TO USE THIS PATTERN:
--------------------------
- Stock buy/sell problems
- Finding max difference with ordering constraint
- Tracking running minimum/maximum
- Single pass optimization problems

RELATED PROBLEMS:
-----------------
- LeetCode 122: Best Time to Buy and Sell Stock II (multiple transactions)
- LeetCode 123: Best Time to Buy and Sell Stock III (2 transactions)
- LeetCode 188: Best Time to Buy and Sell Stock IV (k transactions)
- LeetCode 309: Best Time to Buy and Sell Stock with Cooldown
- LeetCode 714: Best Time to Buy and Sell Stock with Transaction Fee
- Maximum subarray problem (Kadane's algorithm - similar pattern)

======================================================================================
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Track the maximum profit we can achieve
        int maxProfit = 0;
        
        // Track the best (minimum) price to buy at seen so far
        int bestBuy = prices[0];

        // Scan through all prices starting from day 2
        for(int i = 1; i < prices.size(); i++){
            
            // If current price is higher than our best buy price,
            // we can potentially make a profit by selling today
            if(prices[i] > bestBuy){
                // Calculate profit if we sell at current price
                // Update maxProfit if this is better than previous best
                maxProfit = max(maxProfit, prices[i] - bestBuy);
            }
            
            // Update the best buy price (keep track of minimum price seen)
            // This gives us the best opportunity for future sells
            bestBuy = min(bestBuy, prices[i]);
        }
        
        // Return the maximum profit we can achieve
        // If no profit possible (prices only decrease), this returns 0
        return maxProfit;
    }
};