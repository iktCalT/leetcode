#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution { // 0ms
public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    // dp
    // 1. Let's create a 2D array dp, where dp[i][j]
    // represents the min health needed from 
    // [i][j] to [m][n]
    // 2. Go reverse order, if we know dp[i+1][j] and 
    // dp[i][j+1], we can know 
    // dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]))
    //
    // Why reverse order? If we don't go reverse order, 
    // dp[i][j] is min hp needed from [0][0] to [i][j].
    // Then, if we know dp[i-1][j] and dp[i][j-1], then
    // we also need to know current hp of [i-1][j] and 
    // [i][j-1] to calculate dp[i][j]
    // But in reverse order, we don't need that, because 
    // dungeon[i][j] must be subtracted from dp[i][j], since
    // it is experienced prior

    int m = dungeon.size();
    int n = dungeon[0].size();

    vector<vector<int>> dp(m + 1, vector(n + 1, INT_MAX));
    dp[m][n - 1] = 1;
    dp[m - 1][n] = 1;

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        dp[i][j] = 
          max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
      }
    }

    return dp[0][0];
  }
};

struct Path1 {
  int his; // min history hp
  int cur; // current hp
};

struct Room1 {
  Path1 pmaxh; // path with max history hp
  Path1 pmaxc; // path with max current hp
};

class Solution1 { // 2ms
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    // If start with 0
    // find out path with maximum minimum health
    // e.g. path 1: -1 -> -5 -> -2 -> 0 ===> min health: -5
    //      path 2: 2 -> -1 -> -2 -> -3 ===> min health: -3
    // choose path 1 -> return -(-5) + 1 = 6

    vector<vector<Room1>> map(dungeon.size(), vector<Room1>(dungeon[0].size()));

    int val = dungeon[0][0];
    map[0][0] = {{val, val}, {val, val}};

    // first col, only one path
    for (int r = 1; r < dungeon.size(); ++r) {
      // only one path
      nextPath(dungeon[r][0], &map[r][0].pmaxc, &map[r - 1][0].pmaxc);
      map[r][0].pmaxh = map[r][0].pmaxc;
    }

    // first row, only one path
    for (int c = 1; c < dungeon[0].size(); ++c) {
      // only one path
      nextPath(dungeon[0][c], &map[0][c].pmaxc, &map[0][c - 1].pmaxc);
      map[0][c].pmaxh = map[0][c].pmaxc;
    }

    for (int r = 1; r < dungeon.size(); ++r) {
      for (int c = 1; c < dungeon[0].size(); ++c) {
        nextRoom(dungeon[r][c], &map[r][c], &map[r - 1][c], &map[r][c - 1]);
      }
    }

    int min_history = map.back().back().pmaxh.his;
    return max(0, -min_history) + 1;
  }

private:
  void nextPath(const int val, Path1* new_p, const Path1* prev_p) {
    new_p->cur = prev_p->cur + val;
    new_p->his = min(new_p->cur, prev_p->his);
  }

  void nextRoom(const int val, Room1* next, const Room1* prev) {
    // one previous room
    Path1 path1, path2;
    nextPath(val, &path1, &prev->pmaxc);
    nextPath(val, &path2, &prev->pmaxh);

    next->pmaxc = path1.cur > path2.cur ? path1 : path2;
    next->pmaxh = path1.his > path2.his ? path1 : path2;
  }

  void renewRoom(Room1* orig, const Room1* new_) {
    if (orig->pmaxc.cur == new_->pmaxc.cur) {
      // don't change pmaxc.cur, only change pmaxc.his
      orig->pmaxc.his = max(orig->pmaxc.his, new_->pmaxc.his);
    } else if (orig->pmaxc.cur < new_->pmaxc.cur) {
      orig->pmaxc = new_->pmaxc;
    } else {}

    if (orig->pmaxh.his == new_->pmaxh.his) {
      orig->pmaxh.cur = max(orig->pmaxh.cur, new_->pmaxh.cur);
    } else if (orig->pmaxh.his < new_->pmaxh.his) {
      orig->pmaxh = new_->pmaxh;
    } else {}
  }

  void nextRoom(const int val, Room1* next, const Room1* prev1, const Room1* prev2) {
    // two previous rooms
    nextRoom(val, next, prev1);

    Room1 tmp_room;
    nextRoom(val, &tmp_room, prev2);
    renewRoom(next, &tmp_room);
  }
};

class Solution0 { // DFS, TLE
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    // If start with 0
    // find out path with maximum minimum health
    // e.g. path 1: -1 -> -5 -> -2 -> 0 ===> min health: -5
    //      path 2: 2 -> -1 -> -2 -> -3 ===> min health: -3
    // choose path 1 -> return -(-5) + 1 = 6

    // DFS
    int max_min_hp = DFS(0, 0, 0, 0, dungeon);
    // Although min_hp > 0 is possible, you cannot return a negative number!
    // For example, path: 3 -> 7 -> 8 -> 9 ===> min health: 3
    // cannot return -2, you should return 1
    return -max_min_hp + 1;
  }

private:
  int DFS(int r, int c, int cur_hp, int min_hp,
          const vector<vector<int>> &dungeon) {
    cur_hp += dungeon[r][c];
    min_hp = min(min_hp, cur_hp);

    if (r == dungeon.size() - 1 && c == dungeon[0].size() - 1) {
      return min_hp;
    }

    int dhp = INT_MIN, rhp = INT_MIN;
    // go down
    if (r < dungeon.size() - 1)
      dhp = DFS(r + 1, c, cur_hp, min_hp, dungeon);

    // go right
    if (c < dungeon[0].size() - 1)
      rhp = DFS(r, c + 1, cur_hp, min_hp, dungeon);

    return max(dhp, rhp);
  }
};

int main() {
  Solution demo;
  vector<vector<int>> dungeon{
      {-2,-3,3},
      {-5,-10,1},
      {10,30,-5}};
  std::cout << demo.calculateMinimumHP(dungeon) << "\n";
}