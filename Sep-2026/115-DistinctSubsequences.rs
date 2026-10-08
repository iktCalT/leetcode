struct Solution {}

impl Solution {
    pub fn num_distinct(s: String, t: String) -> i32 {
        // For every letter in t, record its positions in s
        // Should be O(m*n), where m is s.size(), n is t.size()
        let m = s.len();
        let n = t.len();

        let mut pos: [Vec<usize>; 26] = Default::default();
        for (i, c) in s.as_bytes().iter().enumerate() {
            pos[(c - b'a') as usize].push(i);
        }

        let mut memory:Vec<Vec<i32>> = vec![vec![-1; m]; n];
        
        // DFS
        Self::dfs(0, &t, 0, &pos, &mut memory)
    }

    fn dfs(it: usize, t: &String, is: usize, pos: &[Vec<usize>; 26], memory: &mut Vec<Vec<i32>>) -> i32 {
        if (it == t.len()) { return 1; }

        let target = (t.as_bytes()[it] - b'a') as usize;
        let find = pos[target].partition_point(|&x| x < is);

        if find == pos[target].len() {
            return 0;
        }

        let find = pos[target][find];
        if memory[it][find] >= 0 {
            return memory[it][find];
        }

        0
    }
}