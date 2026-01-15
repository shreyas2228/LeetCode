// leetcode 169. Majority Element.
// Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2

//1 -- brute force approach: count occurrences of each element using a hash map
// time complexity: O(n^2), space complexity: O(1)


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        
        for(int val : nums) {
            int freq = 0;
            for(int el : nums) {
                if(el == val) {
                    freq++;
                }
            }
            if(freq > n / 2) {
                return val;
            }
        }
        return -1; // This line should never be reached as per problem constraints

    }
}


// 2 -- optimal approach: sorting the array and returning the middle element
// time complexity: O(n log n), space complexity: O(1)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();

        // sort the array
        sort(nums.begin(), nums.end());

        // freq count
        int freq = 1, ans = nums[0];
        for(int i = 1; i < n; i++) {
            if(nums[i] == nums[i - 1]) {
                freq++;
            } else {
                freq = 1;
            }

            if(freq > n / 2) {
                ans = nums[i];
                break;
            }
        }
        return ans;
    }
};


// 3 -- optimal approach: Boyer-Moore Voting Algorithm
// time complexity: O(n), space complexity: O(1)

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int freq = 0, ans = 0;

        for(int i=0; i<nums.size(); i++){
            if(freq == 0){
                ans = nums[i];
            }
            if(ans == nums[i]){
                freq++;
            } else {
                freq--;
            }
        }
        return ans;
    }
};

