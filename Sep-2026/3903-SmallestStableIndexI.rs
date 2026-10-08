use core::num;

struct Solution {}

impl Solution {
    pub fn first_stable_index(nums: Vec<i32>, k: i32) -> i32 {
        // When you move from i-1 to i
        // max(nums[0..i]) could only be either max(nums[0..i-1]) or nums[i]
        // When you move from i + 1 to i
        // min(nums[i..n - 1]) could only be either min(nums[0..i+1]) or nums[i]
        
        // So, just go through the vector in 2 directions respectively and 
        // record the max(nums[0..i]) and min(nums[i..n-1]) in two arrays

        // Because the question asks us to find the smallest stable index, we
        // can start by reverse order, and find out answer in forward order

        let n: usize = nums.len();
        let mut min_num: Vec<i32> = vec![0; n];
        min_num[n - 1] = nums[n - 1];

        for i in (0..n-1).rev() {
            min_num[i] = min_num[i + 1].min(nums[i]);
        }

        let mut cur_max: i32 = i32::MIN;
        for i in (0..n) {
            cur_max = cur_max.max(nums[i]);
            if (cur_max - min_num[i] <= k) {
                return i as i32;
            }
        }

        -1
    }
}