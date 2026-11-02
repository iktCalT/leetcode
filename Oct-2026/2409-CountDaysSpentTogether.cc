#include <algorithm>
#include <array>
#include <string>
using namespace std;

class Solution {
public:
  int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
    // prefix sum of days
    // days -> {0, 31, 31+28, 31+28+31, ...}
    for (int i = 0; i < 12; ++i) {
      days[i + 1] += days[i];
    }

    // String to date
    int aa = date(arriveAlice);
    int la = date(leaveAlice);
    int ab = date(arriveBob);
    int lb = date(leaveBob);

    // cout << aa << " " << la << " " << ab << " " << lb << "\n";

    return max(0, min(la, lb) - max(aa, ab) + 1);
  }
private:
  array<int, 13> days = array<int, 13> {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int date(const string& s) {
    int m = atoi(s.substr(0, 2).c_str());
    int d = atoi(s.substr(3, 2).c_str());

    return days[m - 1] + d; 
  }
};