#define _CRT_SECURE_NO_WARNINGS 1
void backtrack(vector<vector<int>>& res, vector<int>& nums, int position, int len)
{
	if (position == len)
	{
		res.emplace_back(nums); // 和push_back()一样的结果
		return;
	}
	for (int i = position; i < len; i++)
	{
		swap(nums[position], nums[i]);
		backtrack(res, nums, position + 1, len);
		swap(nums[position], nums[i]);
	}
}

class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		backtrack(res, nums, 0, (int)nums.size());
		return res;
	}
};