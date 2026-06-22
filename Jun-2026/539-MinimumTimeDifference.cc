#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int findMinDifference(vector<string>& timePoints) {
    // 24 * 60
    #define H24 1440

    array<int, H24> arr;
    fill(arr.begin(), arr.end(), 0);

    for (int i = 0; i < timePoints.size(); ++i) {
      int m = toMinute(timePoints[i]);
      ++arr[m];
    }

    int ans = INT_MAX;
    int first;
    // find first
    for (first = 0; first < H24; ++first) {
      if (arr[first] > 1) return 0;  // > 1
      else if (arr[first]) break;    // == 1
    }

    int prev = first;
    for (int i = prev + 1; i < H24; ++i) {
      int diff;
      switch (arr[i]) {
      case 0: 
        break;
      case 1:
        // i > prev
        diff = min(i - prev, H24 - (i - prev));
        ans = min(ans, diff);
        prev = i;
        break;
      default: // more than 1 same time points with same time
        return 0;
      }
    }

    // first and last
    int diff = min(prev - first, H24 - (prev - first));
    ans = min(ans, diff);

    return ans;
  }

private:
  int toMinute(const string& time) {
    int h = stoi(string{time[0], time[1]}.c_str());
    int m = stoi(string{time[3], time[4]});
    return h * 60 + m;
  }
};

class Solution0 { // 11ms
public:
  int findMinDifference(vector<string>& timePoints) {
    sort(timePoints.begin(), timePoints.end());
    timePoints.push_back(timePoints[0]);
    
    int ans = INT_MAX;
    for (int i = 1; i < timePoints.size(); ++i) {
      ans = min(ans, timeDiff(timePoints[i], timePoints[i - 1]));
    }
    return ans;
  }

private:
  const int H_24 = 24 * 60; 

  int timeDiff(const string& t1, const string& t2) {
    int hour = atoi(string{t1[0], t1[1]}.c_str()) - atoi(string{t2[0], t2[1]}.c_str());
    int minute = atoi(string{t1[3], t1[4]}.c_str()) - atoi(string{t2[3], t2[4]}.c_str());
    int diff = abs(hour * 60 + minute);
    return min(diff, H_24 - diff);
  }
};