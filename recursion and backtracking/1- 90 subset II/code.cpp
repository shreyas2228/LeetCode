// leetcode 90: Subsets II

class Solution {
public:

    void getAllSubsets(vector<int>& nums,vector<int>& ans, int i, vector<vextor<int>> &allSubets){
        if(i == nums.size()){
            allSubets.push_back(ans);
            return;
        }

        // include the element
        ans.push_back(nums[i]);
        getAllSubsets(nums, ans, i + 1, allSubets);

        ans.pop_back();

        int idx = i+1;
        while(idx < nums.size() && nums[idx] == nums[idx-1]){
            idx++;
        }
        // exclude the element
        getAllSubsets(nums, ans, idx, allSubets);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> allSubets;
        vector<int> ans;

        getAllSubsets(nums, ans, 0, allSubets);
        return allSubets;
    }
};