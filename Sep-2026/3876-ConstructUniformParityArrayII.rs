use core::num;
use std::cmp::min;

struct Solution {}

impl Solution {
    pub fn uniform_array(nums1: Vec<i32>) -> bool {
        let mut smallest_odd: i32 = i32::MAX;
        let mut smallest_even: i32 = i32::MAX;
        let mut count_smallest_odd: i32 = 1;

        for num in nums1 {
            if num % 2 == 0 { // even
                smallest_even = i32::min(smallest_even, num);
            } else { // odd
                if num < smallest_odd {
                    smallest_odd = num;
                    count_smallest_odd = 1;
                } else if num == smallest_odd {
                    count_smallest_odd += 1;
                }
            }
        }

        if smallest_odd == i32::MAX || smallest_even == i32::MAX {
            return true;
        }
        if smallest_odd < smallest_even && count_smallest_odd == 1 {
            return true;
        }
        false
    }
}