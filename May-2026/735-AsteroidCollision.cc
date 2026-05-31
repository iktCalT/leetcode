#include <vector>

using namespace std;

class Solution { // 7ms
public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    for (int i = 0; i < asteroids.size(); ) {
      // asteroids from 0 to i - 1 are stable
      if (asteroids.size() <= 1) return asteroids;
      if (i == 0 || !(asteroids[i - 1] > 0 && asteroids[i] < 0)) {
        ++i;
        continue;
      }

      int rmass = -asteroids[i]; // create a copy, because asteroids will change
      int j;
      bool exist = true;
      for (j = i - 1; ; --j) {
        int lmass = asteroids[j];
        if (lmass < 0) {
          ++j;
          break;
        }

        if (lmass == rmass) {
          exist = false;
          break;
        } else if (lmass > rmass) {
          ++j;
          exist = false;
          break;
        }
        if (j == 0) {
          break;
        }
      }
      // delete [j, i)
      asteroids.erase(asteroids.begin() + j, asteroids.begin() + i + !exist);
      i = j + exist;
    }
    return asteroids;
  }
};

class Solution3 { // 7ms
public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    // all asteroids after division_line are going right
    int division_line = asteroids.size();
    for (int i = division_line - 1; i >= 0; --i) {
      if (asteroids[i] < 0) {
        continue;
      }
      // asteroids[i] > 0
      if (i == division_line - 1) {
        --division_line;
        continue;
      }
      // this one goes right, and there are 
      // asteroids after this going left -> collision
      bool exist = true; // existance of the asteroid going right
      while (i + 1 < division_line) {
        if (asteroids[i] < -asteroids[i + 1]) {
          asteroids.erase(asteroids.begin() + i);
          --division_line;
          exist = false;
          break;
        } else if (asteroids[i] == -asteroids[i + 1]) {
          asteroids.erase(asteroids.begin() + i + 1);
          asteroids.erase(asteroids.begin() + i);
          division_line -= 2;
          exist = false;
          break;
        } else {
          asteroids.erase(asteroids.begin() + i + 1);
          --division_line;
        }
      }
      if (exist) {
        --division_line;
      }
    }
    return asteroids;
  }
};

class Solution2 { // 7ms
public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> ans;
    for (int i = asteroids.size() - 1; i >= 0; --i) {
      if (asteroids[i] < 0) {
        continue;
      }
      // asteroids[i] > 0
      if (i == asteroids.size() - 1) {
        ans.insert(ans.begin(), asteroids.back());
        asteroids.pop_back();
        continue;
      }
      // this one goes right, and there are 
      // asteroids after this going left -> collision
      bool exist = true; // existance of the asteroid going right
      while (i + 1 < asteroids.size()) {
        if (asteroids[i] < -asteroids[i + 1]) {
          asteroids.erase(asteroids.begin() + i);
          exist = false;
          break;
        } else if (asteroids[i] == -asteroids[i + 1]) {
          asteroids.erase(asteroids.begin() + i + 1);
          asteroids.erase(asteroids.begin() + i);
          exist = false;
          break;
        } else {
          asteroids.erase(asteroids.begin() + i + 1);
        }
      }
      if (exist) {
        ans.insert(ans.begin(), asteroids.back());
        asteroids.pop_back();
      }
    }
    ans.insert(ans.begin(), asteroids.begin(), asteroids.end());
    return ans;
  }
};

class Solution1 { // 3ms
public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    // Final state: there is a index n (0 <= n < ans.size())
    // ans[i] < 0 (i <= n); ans[i] > 0 (i > n)
    int last_right = -1;
    for (int i = 0; i < asteroids.size(); ++i) {
      if (asteroids[i] > 0) {
        last_right = i;
      } else if (asteroids[i] < 0 && last_right != -1) {
        // collision
        // there is a asteroids with mass = asteroids[i] going left
        for (; last_right >= 0; --last_right) {
          if (asteroids[last_right] < 0) {
            break;
          }
          // remember asteroids[i] < 0, so its mass is (-asteroids[i])
          if (-asteroids[i] == asteroids[last_right]) {
            asteroids[i] = 0;
            asteroids[last_right] = 0;
            break;
          } else if (-asteroids[i] < asteroids[last_right]) {
            asteroids[i] = 0;
            break;
          } else {
            asteroids[last_right] = 0;
          }
        }

        // find new last_right
        while (last_right >= 0) {
          if (asteroids[last_right] > 0) {
            break;
          } else if (asteroids[last_right] < 0) {
            last_right = -1;
            break;
          }
          --last_right;
        }

      }
    }
    erase(asteroids, 0);
    
    return asteroids;
  }
};

int main() {
  Solution demo;
  vector<int> as = {2, -1, -2, 1};
  demo.asteroidCollision(as);
}