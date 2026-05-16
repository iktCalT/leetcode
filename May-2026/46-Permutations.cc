#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // n! in total
        // Recursion: permuting 1 to k (k!) is equivalent to permuting 1 to k-1 ((k-1)!), 
        //            then insert k to all possible positions
        // We need to write a interation version
        vector<vector<int>> ans{{nums[0]}};
        ans.reserve(factorial(nums.size())); // important!
                            // otherwise, we will encounter heap-use-after-free

        for (int k = 1; k < nums.size(); k++) {
            int tmp_size = ans.size();
            for (int i = 0; i < tmp_size; i++) {
                vector<int>& permutation = ans[i];
                for (auto cit = permutation.cbegin(); cit != permutation.cend(); cit++) {
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
  vector<int> nums{1,2,3};
  demo.permute(nums);
}