/*
3Sum

URL: https://leetcode.com/problems/3sum
Tags: ['array', 'two-pointers']
___

Given an array `nums` of n integers, are there elements a , b , c in `nums`
such that a \+ b \+ c = 0? Find all unique triplets in the array which gives
the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

    Given array nums = [-1, 0, 1, 2, -1, -4],
    
    A solution set is:
    [
      [-1, 0, 1],
      [-1, -1, 2]
    ]
*/

#include <vector>
#include <algorithm>
#include "catch.hpp"

using std::vector;

namespace three_sum {

namespace v1 {
// Time Limit Exceeded
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        for (int i = 0; i < nums.size() - 2; i++) {
            for (int j = i + 1; j < nums.size() - 1; j++) {
                for (int k = j + 1; k < nums.size(); k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> v{nums[i], nums[j], nums[k]};
                        std::sort(v.begin(), v.end());
                        auto it =
                            std::lower_bound(result.begin(), result.end(), v);
                        if (it == result.end() || *it != v) {
                            result.insert(it, std::move(v));
                        }
                    }
                }
            }
        }
        return result;
    }
};
} // namespace v1

inline namespace v2 {
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 排序后, 固定三元组最左侧的一个数字, 然后让右侧的数组两端往中间逼近.
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0) {
                if (nums[i] == nums[i - 1]) {
                    continue; // 去重
                }
            }
            int target = -nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                auto sum = nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                }
                bool moveRight = false;
                if (sum >= target) {
                    moveRight = true;
                }
                if (moveRight) {
                    do {
                        right--;
                    } while (left < right && nums[right] == nums[right + 1]);
                } else {
                    do {
                        left++;
                    } while (left < right && nums[left] == nums[left - 1]);
                }
            }
        }
        return result;
    }
};
} // namespace v2

TEST_CASE("3Sum") {
    Solution s;
    vector<int> v = {-1, 0, 1, 2, -1, -4};
    CHECK(s.threeSum(v) == vector<vector<int>>({{-1, -1, 2}, {-1, 0, 1}}));
}

} // namespace three_sum
