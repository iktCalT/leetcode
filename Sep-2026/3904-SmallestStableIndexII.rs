
impl Solution {
    pub fn first_stable_index(nums: Vec<i32>, k: i32) -> i32 {
        // Exactly same yesterday's question (only change the 
        // input scale)
        let n: usize = nums.len();
        let mut min_num: Vec<i32> = vec![0; n];
        min_num[n - 1] = nums[n - 1];

        // Change it to 
        // `for (index, &number) in nums.iter().enumerate().rev().skip(1) {}`
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