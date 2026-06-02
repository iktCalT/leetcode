class Solution {
public:
  int minimumTotal(vector<vector<int>>& triangle) {
    // graph theory (working problem), for each node, record the min path's length 
    // to save spaces, change the original vector (triangle)
    for (int r = 1; r < triangle.size(); ++r) {
      // two ends
      triangle[r].front() += triangle[r - 1].front();
      triangle[r].back() += triangle[r - 1].back();
      
      // middle 
      for (int c = 1; c < triangle[r].size() - 1; ++c) {
        triangle[r][c] += min(triangle[r - 1][c], triangle[r - 1][c - 1]);
      }
    }
    
    int ans = INT_MAX;
    for (int last : triangle.back()) {
      ans = min(ans, last);
    }
    
    return ans;
  }
};