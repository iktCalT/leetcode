#include <algorithm>
#include <set>
#include <vector>
using namespace std;

class Solution {
public:
  bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
    // Collide from the smallest asteroid to the largest one
    sort(asteroids.begin(), asteroids.end());
    long long lmass = mass;

    for (int& as : asteroids) {
      if (as > lmass) {
        return false;
      } else { // don't use if (mass >= INT_MAX - as) return true; time-consuming
        lmass += as;
      }
    }

    return true;
  }
};

class SolutionSlow {
public:
  bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
    // Collide from the smallest asteroid to the largest one
    // However, sorting is time-consuming, because asteroids.length <= 10^5
    // Instead, let's have a set (ordered vector) storing asteroids
    // larger than planet
    set<int> waitlist;
    long long lmass = mass;
    for (int as : asteroids) {
      if (as > lmass) {
        waitlist.insert(as);
      } else {
        lmass += as;
      }
    }

    for (int as : waitlist) {
      if (as > lmass) {
        return false;
      } else {
        lmass += as;
      }
    }

    return true;
  }
};