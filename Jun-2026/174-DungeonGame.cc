#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct Path {
  int his; // min history hp
  int cur; // current hp
};

struct Room {
  Path pmaxh; // path with max history hp
  Path pmaxc; // path with max current hp
};

class Solution { // 2ms
public:
  int calculateMinimumHP(vector<vector<int>> &dungeon) {
    // If start with 0
    // find out path with maximum minimum health
    // e.g. path 1: -1 -> -5 -> -2 -> 0 ===> min health: -5
    //      path 2: 2 -> -1 -> -2 -> -3 ===> min health: -3
    // choose path 1 -> return -(-5) + 1 = 6

    vector<vector<Room>> map(dungeon.size(), vector<Room>(dungeon[0].size()));

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
  void nextPath(const int val, Path* new_p, const Path* prev_p) {
    new_p->cur = prev_p->cur + val;
    new_p->his = min(new_p->cur, prev_p->his);
  }

  void nextRoom(const int val, Room* next, const Room* prev) {
    // one previous room
    Path path1, path2;
    nextPath(val, &path1, &prev->pmaxc);
    nextPath(val, &path2, &prev->pmaxh);

    next->pmaxc = path1.cur > path2.cur ? path1 : path2;
    next->pmaxh = path1.his > path2.his ? path1 : path2;
  }

  void renewRoom(Room* orig, const Room* new_) {
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

  void nextRoom(const int val, Room* next, const Room* prev1, const Room* prev2) {
    // two previous rooms
    nextRoom(val, next, prev1);

    Room tmp_room;
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
      {3,3,3},
      {5,10,1},
      {10,30,5}};
  std::cout << demo.calculateMinimumHP(dungeon) << "\n";
}