# DSA Pattern Playbook (C++17)

A pattern-first guide to master DSA fast for interviews and CP. Each pattern includes: **when to use, intuition, steps, clean C++17, complexity, mistakes, variations, and practice problems**. Explanations are short, focused on **why** the pattern works, and include a **dry run** for every pattern.

---

## 🟢 Array & Two Pointer Patterns

### 1) Two Pointers (Same Direction / Opposite Direction)
**When to Use (Triggers):**
- Sorted array + pair/interval constraints
- Remove duplicates, merge, or “smallest/closest” pair

**Core Idea (Intuition):**
Like two people walking from ends of a corridor to meet. Sorted order tells you which side to move without missing solutions.

**Step-by-Step Logic:**
1. Start `l=0`, `r=n-1` (opposite direction).
2. Compute condition (e.g., sum).
3. Move the pointer that makes you closer to the target.

**Clean & Optimized C++ Code:**
```cpp
int twoSumSorted(vector<int>& a, int target){
    int l=0, r=(int)a.size()-1;
    while(l<r){
        long long sum = (long long)a[l] + a[r];
        if(sum==target) return 1;
        if(sum<target) l++; else r--;
    }
    return 0;
}
```

**Dry Run (a=[1,2,3,7,9], target=10):**
- l=0 r=4 sum=10 → found

**Time & Space:** O(n), O(1)

**Common Mistakes & Edge Cases:**
- Using on unsorted arrays
- Overflow on sum

**Variations:**
- Same-direction two pointers (slow/fast)
- 3-sum / 4-sum

**Practice:** Easy 167, Medium 15, Hard 42

---

### 2) Sliding Window (Fixed & Variable)
**When to Use:**
- Subarray/substring with constraints
- Max/min/count within a window

**Core Idea:**
Window slides like a frame on a film strip. Keep only what you need in the window.

**Step-by-Step Logic:**
1. Expand right to include new elements.
2. Shrink left until constraint satisfied.
3. Update answer each step.

**Code (Variable: Longest Substring Without Repeat):**
```cpp
int lengthOfLongestSubstring(string s){
    vector<int> last(256, -1);
    int l=0, best=0;
    for(int r=0;r<(int)s.size();r++){
        if(last[s[r]]>=l) l = last[s[r]]+1;
        last[s[r]]=r;
        best = max(best, r-l+1);
    }
    return best;
}
```

**Dry Run (s="abca"):**
- r=0 a → l=0 best=1
- r=1 b → best=2
- r=2 c → best=3
- r=3 a seen at 0 → l=1 best=3

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Shrinking too late
- Not updating counts correctly

**Variations:**
- Fixed-size window max sum
- Minimum window substring

**Practice:** Easy 643, Medium 3, Hard 76

---

### 3) Prefix Sum
**When to Use:**
- Range sum queries
- Subarray sum problems

**Core Idea:**
Store cumulative totals so any range sum is two prefix values apart.

**Step-by-Step Logic:**
1. pref[i] = sum of a[0..i-1]
2. Range sum(l,r) = pref[r+1]-pref[l]

**Code:**
```cpp
vector<long long> buildPrefix(vector<int>& a){
    vector<long long> pref(a.size()+1,0);
    for(int i=0;i<(int)a.size();i++) pref[i+1]=pref[i]+a[i];
    return pref;
}
```

**Dry Run (a=[1,2,3,4]):**
- pref=[0,1,3,6,10], sum(1..3)=10-1=9

**Time & Space:** O(n) build, O(1) query, O(n) space

**Common Mistakes:**
- Off-by-one errors

**Variations:**
- 2D prefix sums

**Practice:** Easy 303, Medium 560, Hard 1248

---

### 4) Difference Array
**When to Use:**
- Many range updates

**Core Idea:**
Update only boundaries, rebuild later with prefix.

**Step-by-Step Logic:**
1. diff[i] = a[i]-a[i-1]
2. Update [l,r] by x → diff[l]+=x, diff[r+1]-=x
3. Rebuild via prefix sum

**Code:**
```cpp
void rangeAdd(vector<int>& diff, int l, int r, int val){
    diff[l]+=val;
    if(r+1<(int)diff.size()) diff[r+1]-=val;
}
```

**Dry Run:**
- a=[0,0,0,0], update [1,3]+=5 → rebuild → [0,5,5,5]

**Time & Space:** O(1) update, O(n) rebuild, O(n) space

**Common Mistakes:**
- Forgetting r+1 bounds

**Variations:**
- 2D difference arrays

**Practice:** Medium 370, Medium 1109, Hard 381C

---

### 5) Kadane’s Algorithm
**When to Use:**
- Maximum subarray sum

**Core Idea:**
Either extend previous subarray or start new at current index.

**Step-by-Step Logic:**
1. cur = best ending here
2. best = global best
3. cur = max(a[i], cur+a[i])

**Code:**
```cpp
int maxSubarray(vector<int>& a){
    int cur=a[0], best=a[0];
    for(int i=1;i<(int)a.size();i++){
        cur = max(a[i], cur+a[i]);
        best = max(best, cur);
    }
    return best;
}
```

**Dry Run (a=[-2,1,-3,4]):**
- cur=-2 best=-2 → cur=1 best=1 → cur=-2 best=1 → cur=4 best=4

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Starting best=0 (fails all-negative)

**Variations:**
- Max circular subarray

**Practice:** Easy 53, Medium 918, Hard 2321

---

### 6) Dutch National Flag
**When to Use:**
- Sorting 0/1/2 or 3 categories

**Core Idea:**
Three regions: [0..low-1]=0, [low..mid-1]=1, [high+1..]=2.

**Step-by-Step Logic:**
1. low=0, mid=0, high=n-1
2. Swap based on a[mid]

**Code:**
```cpp
void sortColors(vector<int>& a){
    int low=0, mid=0, high=a.size()-1;
    while(mid<=high){
        if(a[mid]==0) swap(a[low++], a[mid++]);
        else if(a[mid]==1) mid++;
        else swap(a[mid], a[high--]);
    }
}
```

**Dry Run (a=[2,0,2,1,1,0]):**
- becomes [0,0,1,1,2,2]

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Forgetting mid++ in 0/1 case

**Variations:**
- K colors using counting

**Practice:** Easy 75, Medium 912, Hard 215

---

## 🟢 Hashing & Counting

### 7) Frequency Map
**When to Use:**
- Count occurrences
- Duplicates or majority

**Core Idea:**
Counting makes hidden frequency constraints visible.

**Step-by-Step Logic:**
1. Traverse and increment counts
2. Use map for decisions

**Code:**
```cpp
unordered_map<int,int> freqCount(vector<int>& a){
    unordered_map<int,int> mp;
    for(int x: a) mp[x]++;
    return mp;
}
```

**Dry Run (a=[1,2,2,3]):**
- mp: {1:1, 2:2, 3:1}

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Using ordered map unnecessarily

**Variations:**
- Frequency of chars in string

**Practice:** Easy 387, Medium 347, Hard 692

---

### 8) Hash + Prefix
**When to Use:**
- Subarray sum = K (with negatives)

**Core Idea:**
If prefix sum is S at i, we need earlier prefix S-K.

**Step-by-Step Logic:**
1. Maintain running sum
2. Count how many times each sum occurred
3. Add count of sum-K

**Code:**
```cpp
int subarraySumK(vector<int>& a, int k){
    unordered_map<int,int> cnt;
    cnt[0]=1;
    int sum=0, ans=0;
    for(int x: a){
        sum += x;
        if(cnt.count(sum-k)) ans += cnt[sum-k];
        cnt[sum]++;
    }
    return ans;
}
```

**Dry Run (a=[1,2,3], k=3):**
- sum=1 ans=0
- sum=3 ans+=cnt[0]=1
- sum=6 ans+=cnt[3]=1 → ans=2

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Forgetting cnt[0]=1

**Variations:**
- Longest subarray with sum K

**Practice:** Easy 560, Medium 974, Hard 1248

---

### 9) Subarray Sum Equals K
**When to Use:**
- Count subarrays with sum K

**Core Idea:**
Same as Hash+Prefix.

**Code:**
```cpp
int subarraySum(vector<int>& a, int k){
    unordered_map<int,int> cnt; cnt[0]=1;
    int sum=0, ans=0;
    for(int x: a){
        sum+=x;
        if(cnt.count(sum-k)) ans+=cnt[sum-k];
        cnt[sum]++;
    }
    return ans;
}
```

**Dry Run:** Same as above

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Using sliding window with negatives

**Variations:**
- Subarrays divisible by K

**Practice:** Easy 560, Medium 974, Hard 992

---

## 🟢 Binary Search Patterns

### 10) Classic Binary Search
**When to Use:**
- Sorted array, exact search

**Core Idea:**
Halve search space each step.

**Step-by-Step Logic:**
1. mid = (l+r)/2
2. Compare and shrink

**Code:**
```cpp
int binarySearch(vector<int>& a, int x){
    int l=0,r=a.size()-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(a[mid]==x) return mid;
        if(a[mid]<x) l=mid+1; else r=mid-1;
    }
    return -1;
}
```

**Dry Run (a=[1,3,5,7], x=5):**
- mid=1 a=3 → l=2
- mid=2 a=5 found

**Time & Space:** O(log n), O(1)

**Common Mistakes:**
- Overflow in mid

**Variations:**
- First/last occurrence

**Practice:** Easy 704, Medium 34, Hard 410

---

### 11) Binary Search on Answer
**When to Use:**
- Monotonic predicate
- Min/max feasible value

**Core Idea:**
Search the answer space instead of indices.

**Step-by-Step Logic:**
1. Define feasible(mid)
2. Move left/right based on monotonicity

**Code (Minimize max subarray sum):**
```cpp
bool canSplit(vector<int>& a, int m, long long maxSum){
    long long cur=0; int parts=1;
    for(int x: a){
        if(x>maxSum) return false;
        if(cur+x>maxSum){ parts++; cur=x; }
        else cur+=x;
    }
    return parts<=m;
}
long long splitArray(vector<int>& a, int m){
    long long lo=0, hi=0;
    for(int x: a){ lo=max(lo,(long long)x); hi+=x; }
    long long ans=hi;
    while(lo<=hi){
        long long mid=lo+(hi-lo)/2;
        if(canSplit(a,m,mid)){ ans=mid; hi=mid-1; }
        else lo=mid+1;
    }
    return ans;
}
```

**Dry Run (a=[7,2,5,10,8], m=2):**
- mid=21 feasible → hi
- mid=15 not feasible → lo
- mid=18 feasible → ans=18

**Time & Space:** O(n log range), O(1)

**Common Mistakes:**
- Predicate not monotonic

**Variations:**
- Maximize minimum distance

**Practice:** Medium 410, Medium 1011, Hard 774

---

### 12) Lower Bound / Upper Bound
**When to Use:**
- Find first ≥ x or first > x

**Core Idea:**
Binary search on boundary.

**Code:**
```cpp
int lowerBound(vector<int>& a, int x){
    int l=0, r=a.size();
    while(l<r){
        int mid=(l+r)/2;
        if(a[mid]<x) l=mid+1; else r=mid;
    }
    return l;
}
int upperBound(vector<int>& a, int x){
    int l=0, r=a.size();
    while(l<r){
        int mid=(l+r)/2;
        if(a[mid]<=x) l=mid+1; else r=mid;
    }
    return l;
}
```

**Dry Run (a=[1,2,2,2,4], x=2):**
- lower=1, upper=4

**Time & Space:** O(log n), O(1)

**Common Mistakes:**
- Confusing < vs <=

**Variations:**
- Count occurrences = upper-lower

**Practice:** Easy 35, Medium 34, Hard 4

---

### 13) Search in Rotated Array
**When to Use:**
- Sorted array rotated

**Core Idea:**
One half is always sorted; decide which half to discard.

**Code:**
```cpp
int searchRotated(vector<int>& a, int target){
    int l=0, r=a.size()-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if(a[mid]==target) return mid;
        if(a[l]<=a[mid]){
            if(a[l]<=target && target<a[mid]) r=mid-1;
            else l=mid+1;
        }else{
            if(a[mid]<target && target<=a[r]) l=mid+1;
            else r=mid-1;
        }
    }
    return -1;
}
```

**Dry Run (a=[4,5,6,7,0,1,2], target=0):**
- mid=3 -> left sorted, target not in left → l=4
- mid=5 -> left sorted, target in left → r=4
- mid=4 -> found

**Time & Space:** O(log n), O(1)

**Common Mistakes:**
- Not handling duplicates

**Variations:**
- Rotated array with duplicates

**Practice:** Medium 33, Medium 81, Hard 154

---

## 🟢 Recursion & Backtracking

### 14) Subset / Subsequence Pattern
**When to Use:**
- Generate all subsets

**Core Idea:**
At each index, choose include/exclude (binary decision tree).

**Code:**
```cpp
void subsets(int i, vector<int>& a, vector<int>& cur, vector<vector<int>>& res){
    if(i==(int)a.size()){ res.push_back(cur); return; }
    cur.push_back(a[i]);
    subsets(i+1,a,cur,res);
    cur.pop_back();
    subsets(i+1,a,cur,res);
}
```

**Dry Run (a=[1,2]):**
- [] -> [1] -> [1,2] -> [1] -> [] -> [2] -> []

**Time & Space:** O(2^n), O(n) recursion + output

**Common Mistakes:**
- Not backtracking

**Variations:**
- Subsets with duplicates

**Practice:** Easy 78, Medium 90, Hard 784

---

### 15) Permutations
**When to Use:**
- Arrange elements in all orders

**Core Idea:**
Fix one position, permute the rest.

**Code:**
```cpp
void permute(int idx, vector<int>& a, vector<vector<int>>& res){
    if(idx==(int)a.size()){ res.push_back(a); return; }
    for(int i=idx;i<(int)a.size();i++){
        swap(a[idx], a[i]);
        permute(idx+1,a,res);
        swap(a[idx], a[i]);
    }
}
```

**Dry Run (a=[1,2]):**
- swap(0,0) → [1,2]
- swap(0,1) → [2,1]

**Time & Space:** O(n!), O(n) recursion + output

**Common Mistakes:**
- Forgetting to swap back

**Variations:**
- Permutations with duplicates

**Practice:** Medium 46, Medium 47, Hard 943

---

### 16) Combination Sum
**When to Use:**
- Find combos meeting target

**Core Idea:**
Choose element, either reuse or move forward.

**Code:**
```cpp
void comb(int i, vector<int>& a, int target, vector<int>& cur, vector<vector<int>>& res){
    if(target==0){ res.push_back(cur); return; }
    if(i==(int)a.size() || target<0) return;
    cur.push_back(a[i]);
    comb(i, a, target-a[i], cur, res);
    cur.pop_back();
    comb(i+1, a, target, cur, res);
}
```

**Dry Run (a=[2,3], target=5):**
- take 2 → target 3 → take 3 → target 0 → [2,3]

**Time & Space:** Exponential

**Common Mistakes:**
- Not pruning target<0

**Variations:**
- Each element used once

**Practice:** Medium 39, Medium 40, Hard 216

---

### 17) N-Queens
**When to Use:**
- Place items under constraints

**Core Idea:**
Backtrack row by row, track columns and diagonals.

**Code (Count solutions):**
```cpp
int n;
int solveNQ(int r, vector<int>& col, vector<int>& d1, vector<int>& d2){
    if(r==n) return 1;
    int ans=0;
    for(int c=0;c<n;c++){
        if(col[c]||d1[r-c+n-1]||d2[r+c]) continue;
        col[c]=d1[r-c+n-1]=d2[r+c]=1;
        ans += solveNQ(r+1,col,d1,d2);
        col[c]=d1[r-c+n-1]=d2[r+c]=0;
    }
    return ans;
}
```

**Dry Run (n=4):**
- Place (0,1),(1,3),(2,0),(3,2) → valid

**Time & Space:** O(n!), O(n)

**Common Mistakes:**
- Wrong diagonal indexing

**Variations:**
- Return board configs

**Practice:** Medium 51, Medium 52, Hard 980

---

## 🟢 Linked List Patterns

### 18) Fast & Slow Pointers
**When to Use:**
- Middle, cycle, nth from end

**Core Idea:**
Fast moves twice speed; slow at middle when fast ends.

**Code:**
```cpp
ListNode* middleNode(ListNode* head){
    ListNode* slow=head; ListNode* fast=head;
    while(fast && fast->next){ slow=slow->next; fast=fast->next->next; }
    return slow;
}
```

**Dry Run (1->2->3->4->5):**
- slow=1 fast=1 → slow=2 fast=3 → slow=3 fast=5

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Missing fast->next check

**Variations:**
- Cycle detection

**Practice:** Easy 876, Medium 141, Hard 142

---

### 19) Reverse Linked List
**When to Use:**
- Reverse in-place

**Core Idea:**
Flip pointers as you walk.

**Code:**
```cpp
ListNode* reverseList(ListNode* head){
    ListNode* prev=nullptr; ListNode* cur=head;
    while(cur){
        ListNode* nxt=cur->next;
        cur->next=prev;
        prev=cur; cur=nxt;
    }
    return prev;
}
```

**Dry Run (1->2->3):**
- becomes 3->2->1

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Losing next pointer

**Variations:**
- Reverse in k-group

**Practice:** Easy 206, Medium 92, Hard 25

---

### 20) Cycle Detection
**When to Use:**
- Detect loop

**Core Idea:**
If fast meets slow, there is a cycle.

**Code:**
```cpp
bool hasCycle(ListNode* head){
    ListNode* slow=head; ListNode* fast=head;
    while(fast && fast->next){
        slow=slow->next; fast=fast->next->next;
        if(slow==fast) return true;
    }
    return false;
}
```

**Dry Run:**
- On cyclic list, pointers meet

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Not handling null

**Variations:**
- Find cycle start

**Practice:** Easy 141, Medium 142, Hard 287

---

### 21) Merge Lists
**When to Use:**
- Merge sorted lists

**Core Idea:**
Always take smaller head.

**Code:**
```cpp
ListNode* mergeTwoLists(ListNode* a, ListNode* b){
    ListNode dummy(0); ListNode* tail=&dummy;
    while(a && b){
        if(a->val<=b->val){ tail->next=a; a=a->next; }
        else { tail->next=b; b=b->next; }
        tail=tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}
```

**Dry Run (1->3, 2->4):**
- merged: 1->2->3->4

**Time & Space:** O(m+n), O(1)

**Common Mistakes:**
- Forgetting remaining nodes

**Variations:**
- Merge k lists

**Practice:** Easy 21, Medium 23, Hard 148

---

## 🟢 Stack Patterns

### 22) Monotonic Stack (Increasing / Decreasing)
**When to Use:**
- Next greater/smaller
- Histogram

**Core Idea:**
Stack keeps elements in monotonic order to quickly find nearest greater/smaller.

**Code (Next Greater):**
```cpp
vector<int> nextGreater(vector<int>& a){
    int n=a.size();
    vector<int> ans(n,-1);
    stack<int> st;
    for(int i=0;i<n;i++){
        while(!st.empty() && a[i]>a[st.top()]){
            ans[st.top()]=a[i]; st.pop();
        }
        st.push(i);
    }
    return ans;
}
```

**Dry Run (a=[2,1,2,4,3]):**
- ans=[4,2,4,-1,-1]

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Pushing values instead of indices

**Variations:**
- Next smaller

**Practice:** Easy 496, Medium 503, Hard 84

---

### 23) Next Greater / Smaller Element
**When to Use:**
- Nearest greater/smaller to left/right

**Core Idea:**
Pop until the condition becomes valid.

**Code (Next Smaller Right):**
```cpp
vector<int> nextSmallerRight(vector<int>& a){
    int n=a.size();
    vector<int> ans(n,-1);
    stack<int> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top()>=a[i]) st.pop();
        ans[i]= st.empty()? -1 : st.top();
        st.push(a[i]);
    }
    return ans;
}
```

**Dry Run (a=[4,5,2,10]):**
- ans=[2,2,-1,-1]

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Wrong traversal direction

**Variations:**
- Use index to compute distance

**Practice:** Easy 496, Medium 739, Hard 907

---

### 24) Histogram / Stock Span
**When to Use:**
- Largest rectangle or spans

**Core Idea:**
Find nearest smaller on both sides.

**Code (Largest Rectangle):**
```cpp
int largestRectangle(vector<int>& h){
    int n=h.size();
    stack<int> st; long long best=0;
    for(int i=0;i<=n;i++){
        long long cur = (i==n?0:h[i]);
        while(!st.empty() && cur < h[st.top()]){
            int height=h[st.top()]; st.pop();
            int left = st.empty()? -1 : st.top();
            long long width = i - left - 1;
            best = max(best, width*height);
        }
        st.push(i);
    }
    return (int)best;
}
```

**Dry Run (h=[2,1,5,6,2,3]):**
- max area = 10

**Time & Space:** O(n), O(n)

**Common Mistakes:**
- Forgetting sentinel at end

**Variations:**
- Max rectangle in binary matrix

**Practice:** Medium 84, Medium 739, Hard 85

---

## 🟢 Greedy Patterns

### 25) Interval Scheduling
**When to Use:**
- Maximum non-overlapping intervals

**Core Idea:**
Pick earliest finishing interval to leave room for others.

**Code:**
```cpp
int maxNonOverlap(vector<pair<int,int>>& intervals){
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b){
        return a.second < b.second;
    });
    int count=0, lastEnd=INT_MIN;
    for(auto& in: intervals){
        if(in.first >= lastEnd){ count++; lastEnd = in.second; }
    }
    return count;
}
```

**Dry Run:**
- [(1,2),(2,3),(3,4)] → count=3

**Time & Space:** O(n log n), O(1)

**Common Mistakes:**
- Sorting by start time

**Variations:**
- Minimum removals

**Practice:** Medium 435, Medium 452, Hard 1288

---

### 26) Activity Selection
**When to Use:**
- Same as interval scheduling

**Core Idea:**
Earliest finish gives max count.

**Dry Run:**
- Same as above

**Time & Space:** O(n log n), O(1)

**Common Mistakes:**
- Not sorting by finish

**Variations:**
- Weighted intervals (DP)

**Practice:** Medium 435, Medium GFG Activity Selection, Hard 1235

---

### 27) Minimum Platforms
**When to Use:**
- Min resources for overlapping intervals

**Core Idea:**
Sweep line with sorted arrivals/departures.

**Code:**
```cpp
int minPlatforms(vector<int>& arr, vector<int>& dep){
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());
    int i=0,j=0, platforms=0, best=0;
    while(i<(int)arr.size()){
        if(arr[i]<=dep[j]){ platforms++; best=max(best,platforms); i++; }
        else { platforms--; j++; }
    }
    return best;
}
```

**Dry Run:**
- arr=[900,940,950], dep=[910,1200,1120] → best=2

**Time & Space:** O(n log n), O(1)

**Common Mistakes:**
- Using < instead of <=

**Variations:**
- Meeting rooms

**Practice:** Medium 253, Medium GFG Minimum Platforms, Hard 759

---

## 🟢 Heap / Priority Queue

### 28) Top K Elements
**When to Use:**
- Largest/smallest k elements

**Core Idea:**
Keep a min-heap of size k.

**Code:**
```cpp
vector<int> topK(vector<int>& a, int k){
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int x: a){
        pq.push(x);
        if((int)pq.size()>k) pq.pop();
    }
    vector<int> res;
    while(!pq.empty()){ res.push_back(pq.top()); pq.pop(); }
    return res;
}
```

**Dry Run:**
- a=[5,1,3,2,8], k=2 → heap keeps [5,8]

**Time & Space:** O(n log k), O(k)

**Common Mistakes:**
- Using max-heap with wrong logic

**Variations:**
- Top K frequent

**Practice:** Easy 215, Medium 347, Hard 692

---

### 29) Kth Largest / Smallest
**When to Use:**
- Kth order statistic

**Core Idea:**
Same as Top K; heap size k.

**Code:**
```cpp
int kthLargest(vector<int>& a, int k){
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int x: a){
        pq.push(x);
        if((int)pq.size()>k) pq.pop();
    }
    return pq.top();
}
```

**Dry Run:**
- a=[3,2,1,5,6,4], k=2 → 5

**Time & Space:** O(n log k), O(k)

**Common Mistakes:**
- Confusing kth largest vs kth smallest

**Variations:**
- Quickselect

**Practice:** Medium 215, Medium 378, Hard 719

---

### 30) Merge K Sorted Lists
**When to Use:**
- Merge multiple sorted lists

**Core Idea:**
Always extract the smallest head from a min-heap.

**Code:**
```cpp
ListNode* mergeKLists(vector<ListNode*>& lists){
    auto cmp=[](ListNode* a, ListNode* b){ return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for(auto* node: lists) if(node) pq.push(node);
    ListNode dummy(0); ListNode* tail=&dummy;
    while(!pq.empty()){
        auto* cur=pq.top(); pq.pop();
        tail->next=cur; tail=cur;
        if(cur->next) pq.push(cur->next);
    }
    return dummy.next;
}
```

**Dry Run:**
- [1->4],[1->3],[2->6] → 1,1,2,3,4,6

**Time & Space:** O(N log k), O(k)

**Common Mistakes:**
- Not pushing next node

**Variations:**
- Merge k sorted arrays

**Practice:** Hard 23, Hard 632, Hard 373

---

## 🟢 Graph Patterns

### 31) BFS / DFS
**When to Use:**
- Traversal, shortest path in unweighted graph

**Core Idea:**
BFS explores in layers; DFS explores depth.

**Code (BFS on grid):**
```cpp
int bfsGrid(vector<vector<int>>& grid, int sr, int sc){
    int n=grid.size(), m=grid[0].size();
    queue<pair<int,int>> q; q.push({sr,sc});
    vector<vector<int>> vis(n, vector<int>(m,0));
    vis[sr][sc]=1;
    int steps=0; int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1};
    while(!q.empty()){
        int sz=q.size();
        while(sz--){
            auto [r,c]=q.front(); q.pop();
            for(int k=0;k<4;k++){
                int nr=r+dr[k], nc=c+dc[k];
                if(nr<0||nc<0||nr>=n||nc>=m||vis[nr][nc]) continue;
                vis[nr][nc]=1; q.push({nr,nc});
            }
        }
        steps++;
    }
    return steps;
}
```

**Dry Run:**
- BFS expands level by level from start

**Time & Space:** O(V+E), O(V)

**Common Mistakes:**
- Marking visited too late

**Variations:**
- DFS recursion/stack

**Practice:** Easy 733, Medium 200, Hard 127

---

### 32) Topological Sort
**When to Use:**
- DAG ordering, prerequisites

**Core Idea:**
Nodes with indegree 0 are safe to schedule first.

**Code:**
```cpp
vector<int> topoSort(int n, vector<vector<int>>& edges){
    vector<vector<int>> g(n);
    vector<int> indeg(n,0);
    for(auto& e: edges){ g[e[0]].push_back(e[1]); indeg[e[1]]++; }
    queue<int> q; for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i);
    vector<int> order;
    while(!q.empty()){
        int u=q.front(); q.pop();
        order.push_back(u);
        for(int v: g[u]) if(--indeg[v]==0) q.push(v);
    }
    return order;
}
```

**Dry Run:**
- 0->1,0->2,1->3 → [0,1,2,3]

**Time & Space:** O(V+E), O(V)

**Common Mistakes:**
- Not checking if order size < n

**Variations:**
- DFS-based topo sort

**Practice:** Medium 210, Medium 207, Hard 269

---

### 33) Union Find (DSU)
**When to Use:**
- Dynamic connectivity, MST

**Core Idea:**
Compress paths and union by size for near-constant time.

**Code:**
```cpp
struct DSU{
    vector<int> p, sz;
    DSU(int n): p(n), sz(n,1){ iota(p.begin(),p.end(),0); }
    int find(int x){ return p[x]==x? x : p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
        return true;
    }
};
```

**Dry Run:**
- union(1,2), union(2,3) → same set

**Time & Space:** ~O(α(n)) per op, O(n)

**Common Mistakes:**
- Not using path compression

**Variations:**
- DSU with rollback

**Practice:** Medium 547, Medium 684, Hard 1202

---

### 34) Shortest Path (Dijkstra, BFS Grid)
**When to Use:**
- Non-negative weighted graphs

**Core Idea:**
Pick the closest node each step using min-heap.

**Code:**
```cpp
vector<long long> dijkstra(int n, vector<vector<pair<int,int>>>& g, int src){
    const long long INF=1e18;
    vector<long long> dist(n, INF); dist[src]=0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        for(auto [v,w]: g[u]){
            if(dist[v] > d + w){
                dist[v]=d+w; pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

**Dry Run:**
- Distances relax in increasing order of distance

**Time & Space:** O((V+E)logV), O(V)

**Common Mistakes:**
- Using with negative weights

**Variations:**
- 0-1 BFS

**Practice:** Medium 743, Medium 1631, Hard 778

---

## 🟢 Dynamic Programming Patterns

### 35) 0/1 Knapsack
**When to Use:**
- Choose items once with capacity

**Core Idea:**
Each item is either taken or skipped.

**Code:**
```cpp
int knap01(vector<int>& wt, vector<int>& val, int W){
    vector<int> dp(W+1,0);
    for(int i=0;i<(int)wt.size();i++){
        for(int w=W; w>=wt[i]; w--){
            dp[w] = max(dp[w], val[i] + dp[w-wt[i]]);
        }
    }
    return dp[W];
}
```

**Dry Run:**
- wt=[1,3,4], val=[15,20,30], W=4 → 45

**Time & Space:** O(nW), O(W)

**Common Mistakes:**
- Looping w forward (causes reuse)

**Variations:**
- Subset sum

**Practice:** Medium 416, Medium 494, Hard 1049

---

### 36) Unbounded Knapsack
**When to Use:**
- Unlimited use of items

**Core Idea:**
Forward loop allows reuse in same iteration.

**Code:**
```cpp
int unbounded(vector<int>& wt, vector<int>& val, int W){
    vector<int> dp(W+1,0);
    for(int i=0;i<(int)wt.size();i++){
        for(int w=wt[i]; w<=W; w++){
            dp[w] = max(dp[w], val[i] + dp[w-wt[i]]);
        }
    }
    return dp[W];
}
```

**Dry Run:**
- wt=[2], val=[3], W=6 → 9

**Time & Space:** O(nW), O(W)

**Common Mistakes:**
- Using backward loop (breaks reuse)

**Variations:**
- Coin change

**Practice:** Medium 322, Medium 518, Hard 279

---

### 37) LIS (Longest Increasing Subsequence)
**When to Use:**
- Longest increasing sequence

**Core Idea:**
Maintain smallest tail for each length.

**Code:**
```cpp
int LIS(vector<int>& a){
    vector<int> tail;
    for(int x: a){
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if(it==tail.end()) tail.push_back(x);
        else *it = x;
    }
    return tail.size();
}
```

**Dry Run (a=[10,9,2,5,3]):**
- tail: [10],[9],[2],[2,5],[2,3]

**Time & Space:** O(n log n), O(n)

**Common Mistakes:**
- Using upper_bound for strictly increasing

**Variations:**
- Reconstruct LIS

**Practice:** Medium 300, Medium 673, Hard 354

---

### 38) LCS (Longest Common Subsequence)
**When to Use:**
- Compare two sequences

**Core Idea:**
DP over prefixes of both strings.

**Code:**
```cpp
int LCS(string a, string b){
    int n=a.size(), m=b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i-1]==b[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}
```

**Dry Run ("abc", "ac"):**
- LCS=2

**Time & Space:** O(nm), O(nm)

**Common Mistakes:**
- Indexing errors

**Variations:**
- Edit distance

**Practice:** Medium 1143, Hard 1092, Hard 1312

---

### 39) Matrix DP
**When to Use:**
- 2D path counts

**Core Idea:**
Cell depends on top and left.

**Code:**
```cpp
int uniquePaths(int n, int m){
    vector<vector<int>> dp(n, vector<int>(m,1));
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
    return dp[n-1][m-1];
}
```

**Dry Run (2x3):**
- dp end = 3

**Time & Space:** O(nm), O(nm)

**Common Mistakes:**
- Not initializing base row/col

**Variations:**
- With obstacles

**Practice:** Medium 62, Medium 63, Hard 64

---

### 40) DP on Subsequences
**When to Use:**
- Pick or skip elements

**Core Idea:**
Transform to subset sum.

**Code (Target Sum):**
```cpp
int findTargetSumWays(vector<int>& nums, int S){
    int sum=0; for(int x: nums) sum+=x;
    if((sum+S)%2 || sum<S) return 0;
    int target=(sum+S)/2;
    vector<int> dp(target+1,0); dp[0]=1;
    for(int x: nums){
        for(int t=target; t>=x; t--) dp[t]+=dp[t-x];
    }
    return dp[target];
}
```

**Dry Run:**
- nums=[1,1,1,1,1], S=3 → 5

**Time & Space:** O(n*target), O(target)

**Common Mistakes:**
- Forgetting transform formula

**Variations:**
- Partition equal subset

**Practice:** Medium 494, Medium 416, Hard 1049

---

### 41) DP on Grids
**When to Use:**
- Min path sum

**Core Idea:**
Each cell depends on top/left minimal path.

**Code:**
```cpp
int minPathSum(vector<vector<int>>& g){
    int n=g.size(), m=g[0].size();
    vector<vector<int>> dp(n, vector<int>(m,0));
    dp[0][0]=g[0][0];
    for(int i=1;i<n;i++) dp[i][0]=dp[i-1][0]+g[i][0];
    for(int j=1;j<m;j++) dp[0][j]=dp[0][j-1]+g[0][j];
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            dp[i][j]=g[i][j]+min(dp[i-1][j], dp[i][j-1]);
    return dp[n-1][m-1];
}
```

**Dry Run (grid=[[1,3,1],[1,5,1],[4,2,1]]):**
- min sum = 7

**Time & Space:** O(nm), O(nm)

**Common Mistakes:**
- Wrong base initialization

**Variations:**
- With obstacles

**Practice:** Medium 64, Medium 63, Hard 174

---

## 🟢 Tree Patterns

### 42) Tree Traversals
**When to Use:**
- Process all nodes

**Core Idea:**
DFS visits nodes in structured order.

**Code (Inorder):**
```cpp
void inorder(TreeNode* root, vector<int>& res){
    if(!root) return;
    inorder(root->left,res);
    res.push_back(root->val);
    inorder(root->right,res);
}
```

**Dry Run:**
- Inorder of BST yields sorted sequence

**Time & Space:** O(n), O(h)

**Common Mistakes:**
- Missing null check

**Variations:**
- Iterative traversal

**Practice:** Easy 94, Medium 102, Hard 987

---

### 43) Diameter of Tree
**When to Use:**
- Longest path between nodes

**Core Idea:**
Diameter = max(left height + right height).

**Code:**
```cpp
int diameter=0;
int height(TreeNode* root){
    if(!root) return 0;
    int l=height(root->left), r=height(root->right);
    diameter = max(diameter, l+r);
    return 1+max(l,r);
}
```

**Dry Run:**
- Update diameter during height computation

**Time & Space:** O(n), O(h)

**Common Mistakes:**
- Returning diameter instead of height

**Variations:**
- Weighted tree diameter

**Practice:** Easy 543, Medium 124, Hard 687

---

### 44) Lowest Common Ancestor
**When to Use:**
- Find shared ancestor in tree

**Core Idea:**
If a node is p or q, return it; otherwise check both sides.

**Code:**
```cpp
TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q){
    if(!root || root==p || root==q) return root;
    TreeNode* L = LCA(root->left,p,q);
    TreeNode* R = LCA(root->right,p,q);
    if(L && R) return root;
    return L?L:R;
}
```

**Dry Run:**
- Path splits return at first common node

**Time & Space:** O(n), O(h)

**Common Mistakes:**
- Confusing BST LCA with generic tree

**Variations:**
- LCA in BST

**Practice:** Medium 236, Easy 235, Hard 1644

---

### 45) Binary Tree DP
**When to Use:**
- DP over subtrees

**Core Idea:**
Return two states from each node.

**Code (House Robber III):**
```cpp
pair<int,int> dfs(TreeNode* root){
    if(!root) return {0,0};
    auto L=dfs(root->left), R=dfs(root->right);
    int take = root->val + L.second + R.second;
    int skip = max(L.first,L.second) + max(R.first,R.second);
    return {take, skip};
}
int rob(TreeNode* root){
    auto p=dfs(root);
    return max(p.first,p.second);
}
```

**Dry Run:**
- Compute take/skip for each node

**Time & Space:** O(n), O(h)

**Common Mistakes:**
- Mixing take/skip states

**Variations:**
- Max path sum

**Practice:** Medium 337, Medium 968, Hard 124

---

## 🟢 Advanced Patterns

### 46) Bit Manipulation Patterns
**When to Use:**
- XOR tricks, parity

**Core Idea:**
XOR cancels pairs; bit ops represent sets.

**Code (Single Number):**
```cpp
int singleNumber(vector<int>& a){
    int x=0; for(int v: a) x^=v; return x;
}
```

**Dry Run:**
- [4,1,2,1,2] → 4

**Time & Space:** O(n), O(1)

**Common Mistakes:**
- Using XOR when counts aren’t even

**Variations:**
- Two unique numbers

**Practice:** Easy 136, Medium 260, Hard 137

---

### 47) Trie
**When to Use:**
- Prefix search, dictionary

**Core Idea:**
Tree of characters, each edge is a letter.

**Code:**
```cpp
struct Trie{
    struct Node{ int next[26]; bool end=false; Node(){ fill(next,next+26,-1);} };
    vector<Node> t; Trie(){ t.push_back(Node()); }
    void insert(string s){
        int cur=0; for(char c: s){
            int idx=c-'a';
            if(t[cur].next[idx]==-1){ t[cur].next[idx]=t.size(); t.push_back(Node()); }
            cur=t[cur].next[idx];
        } t[cur].end=true; }
    bool search(string s){
        int cur=0; for(char c: s){
            int idx=c-'a'; if(t[cur].next[idx]==-1) return false; cur=t[cur].next[idx];
        } return t[cur].end; }
    bool startsWith(string p){
        int cur=0; for(char c: p){
            int idx=c-'a'; if(t[cur].next[idx]==-1) return false; cur=t[cur].next[idx];
        } return true; }
};
```

**Dry Run:**
- Insert “apple”, search “app” false, startsWith “app” true

**Time & Space:** O(L) per op, O(total letters)

**Common Mistakes:**
- Forgetting end marker

**Variations:**
- Trie for digits

**Practice:** Medium 208, Medium 211, Hard 212

---

### 48) Segment Tree (Basic)
**When to Use:**
- Range query + point update

**Core Idea:**
Binary tree stores segment aggregates.

**Code:**
```cpp
struct SegTree{
    int n; vector<long long> tree;
    SegTree(int n): n(n), tree(4*n,0) {}
    void build(vector<int>& a, int node, int l, int r){
        if(l==r){ tree[node]=a[l]; return; }
        int mid=(l+r)/2;
        build(a,2*node,l,mid);
        build(a,2*node+1,mid+1,r);
        tree[node]=tree[2*node]+tree[2*node+1];
    }
    void update(int node,int l,int r,int idx,int val){
        if(l==r){ tree[node]=val; return; }
        int mid=(l+r)/2;
        if(idx<=mid) update(2*node,l,mid,idx,val);
        else update(2*node+1,mid+1,r,idx,val);
        tree[node]=tree[2*node]+tree[2*node+1];
    }
    long long query(int node,int l,int r,int ql,int qr){
        if(qr<l||r<ql) return 0;
        if(ql<=l&&r<=qr) return tree[node];
        int mid=(l+r)/2;
        return query(2*node,l,mid,ql,qr)+query(2*node+1,mid+1,r,ql,qr);
    }
};
```

**Dry Run:**
- Query [l,r] by merging segment sums

**Time & Space:** O(log n) per op, O(n)

**Common Mistakes:**
- Wrong bounds

**Variations:**
- Lazy propagation

**Practice:** Medium 307, Hard 715, Hard 339D

---

### 49) Fenwick Tree (BIT)
**When to Use:**
- Prefix sum queries + point updates

**Core Idea:**
Binary indexed tree stores partial sums.

**Code:**
```cpp
struct BIT{
    int n; vector<long long> bit;
    BIT(int n): n(n), bit(n+1,0) {}
    void add(int idx, long long val){
        for(; idx<=n; idx += idx&-idx) bit[idx]+=val;
    }
    long long sum(int idx){
        long long s=0;
        for(; idx>0; idx -= idx&-idx) s+=bit[idx];
        return s;
    }
    long long rangeSum(int l,int r){ return sum(r)-sum(l-1); }
};
```

**Dry Run:**
- add(3,5) updates indices 3,4,8...

**Time & Space:** O(log n) per op, O(n)

**Common Mistakes:**
- 1-indexing errors

**Variations:**
- Range update + point query

**Practice:** Medium 307, Hard 1409, Hard SPOJ BIT

---

## Final Interview Thinking
- Start with brute force → show why it’s slow → introduce the pattern.
- Use **two pointers** or **sliding window** when you can maintain a window invariant.
- Use **hash + prefix** when negatives exist (sliding window fails).
- Use **binary search on answer** when feasibility is monotonic.
- Use **DP** for overlapping subproblems + optimal substructure.
- Use **stack** for nearest greater/smaller queries.

This playbook is designed for fast recognition, confident coding, and strong interview performance.
