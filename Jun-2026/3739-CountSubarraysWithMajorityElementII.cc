#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  long long countMajoritySubarrays(vector<int>& nums, int target) {
    // A O(n) method

    // Array arr: arr[i] = nums[i] == target ? 1 : -1;
    // Then consider how many subarray's sum > 0
    // Prefix sum pre: pre[i] = pre[i - 1] + arr[i]; pre[0] = arr[0]

    // Case 1: for i from 0 to n, how many j (0 <= j < i) fulfills 
    // pre[j] < pre[i]. Case 2: how many i fulfills pre[i] > 0.
    // Return case 1 + case 2
    // We can simplify these two cases into one, by adding a leading
    // element 0 to pre, then only consider case 1 (in this case 
    // replace pre[i] with pre[i + 1]), actually, since pre[i + 1]
    // only uses once, we need to use a integer "prefix" to record it

    // We also need a ordered_map (I will make it faster by translating
    // it into a vector) cnt. When we are investigating nums[i], 
    // cnt[k] is k occurs how many times in pre so far. So, our answer
    // should add cnt[-size] + ... + cnt[prefix]

    // But adding them up every time is time consuming, we can record the
    // prefix sum of cnt in sum_cnt

    // e.g. arr = {-1, 1, 1, 1, -1, -1, 1}, 7 elemets
    //   pre = {0, -1, 0, 1, 2,  1,  0, 1}, 8 elements
    //   cnt(i == 0) = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, 2 * 7 + 1 elements
    //   cnt(i == 1) = {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0}
    //   cnt(i == 2) = {0,0,0,0,0,0,1,2,0,0,0,0,0,0,0}
    //   ...
    //   cnt_sum(i == 0) = {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1}
    //   cnt_sum(i == 1) = {0,0,0,0,0,0,1,2,2,2,2,2,2,2,2}
    //   cnt_sum(i == 2) = {0,0,0,0,0,0,1,3,3,3,3,3,3,3,3}

    // But renewing cnt_sum is also time consuming, because we need to 
    // modify every index after prefix. Now, notice that every time,
    // prefix only changes 1 (add 1 or subtract 1), we know that 
    // cnt_sum[prefix] = cnt[-size] + ... + cnt[prefix - 1]
    // when new_prefix = prefix + 1: cnt_sum[prefix + 1] = cnt_sum[prefix - 1] + cnt[prefix]
    // when new_prefix = prefix - 1: cnt_sum[prefix - 1] = cnt_sum[prefix - 1] - cnt[prefix - 1]
    // So, we only need a integer cnt_sum and an array cnt to represent it

    const int size = nums.size();
    int prefix = 0;
    vector<int> cnt(2 * size + 1, 0); // min: -size, max: size
    cnt[0 + size] = 1; // we have assumed that pre[0] = 0
    int cnt_sum = 0;

    long long ans = 0;
    for (int i = 0; i < size; ++ i) {
      int equal = nums[i] == target ? 1 : -1;
      cnt_sum += equal > 0 ? cnt[prefix + size] : -cnt[prefix + size - 1];
      prefix += equal;
      ans += cnt_sum;

      ++cnt[prefix + size];
    }

    return ans;
  }
};

int main() {
  Solution demo;
  vector<int> nums{1,2,2,3,2,3,3};
  int target = 2;
  std::cout << demo.countMajoritySubarrays(nums, target) << "\n";
}