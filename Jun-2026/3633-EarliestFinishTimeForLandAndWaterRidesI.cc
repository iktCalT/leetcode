#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
    // for any ls, ld, ws, wd, the time is
    // ls + ld + ws + wd - max(min(ls + ld, ws), min(ws + wd, ls))
    int ans = INT_MAX;
    for (int i = 0; i < landStartTime.size(); ++i) {
      // create copies of ls and ld, because they will be used multiple times
      int ls = landStartTime [i];
      int ld = landDuration[i];
      if (ans < ls + ld) continue;
      for (int j = 0; j < waterStartTime.size(); ++j) {
        // ws and wd are references, because they will be used only once 
        int& ws = waterStartTime[j];
        int& wd = waterDuration[j];
        int min_time = ls + ld + ws + wd - max(min(ls + ld, ws), min(ws + wd, ls));
        ans = min(ans, min_time);
      }
    }
    return ans;
  }
};