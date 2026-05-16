#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // Almost same as last question
        // But before iteration, we need to sort nums
        // If nums[k] == nums[k-1], we need to find the last nums[k] in permutation,
        // then insert after its position
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans{{nums[0]}};
        ans.reserve(factorial(nums.size())); // important!
                            // otherwise, we will encounter heap-use-after-free

        for (int k = 1; k < nums.size(); k++) {
            int tmp_size = ans.size();
            for (int i = 0; i < tmp_size; i++) {
                vector<int>& permutation = ans[i];
                vector<int>::const_iterator cit;
                if (nums[k] == nums[k-1]) {
                    cit = find(permutation.crbegin(), permutation.crend(), nums[k]).base();
                } else {
                    cit = permutation.cbegin();
                }

                for ( ; cit != permutation.cend(); cit++) {
                    // create a new copy
                    ans.emplace_back(vector<int>(permutation.begin(), permutation.end()));
                    // insert from begin() to end() - 1, permutation.size() times in total
                    auto& last = ans.back();
                    last.insert(last.begin() + (cit - permutation.cbegin()), nums[k]);
                }
                
                // insert the last one to the original permutation
                permutation.insert(permutation.end(), nums[k]);
            }
        }

        return ans;
    }

private:
    int factorial(int num) {
        int frac = 1;
        for (int i = 2; i <= num; i++) {
            frac *= i;
        }
        return frac;
    }
};

int main() {
  Solution demo;
  vector<int> nums {1,1,1, 2,3};
  demo.permuteUnique(nums);
}