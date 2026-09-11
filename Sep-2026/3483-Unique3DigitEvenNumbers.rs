struct Solution {}

impl Solution {
    pub fn total_numbers(digits: Vec<i32>) -> i32 {
        // Brute force: at most 9 * 10 * 10 = 1000 steps
        let mut hist: [u8; 10] = [0; 10];
        for num in digits {
            hist[num as usize] += 1;
        }

        let mut ans:i32 = 0;
        for first in 1..=9 {
            if hist[first as usize] == 0 { continue; }
            hist[first as usize] -= 1;
            for second in 0..=9 {
                if hist[second as usize] == 0 { continue; }
                hist[second as usize] -= 1;
                for third in 0..=4 { // third * 2 = 0, 2, 4, 6, 8
                    ans += (hist[third * 2 as usize] != 0) as i32;
                }
                hist[second as usize] += 1;
            }
            hist[first as usize] += 1;
        }
        
        ans
    }
}