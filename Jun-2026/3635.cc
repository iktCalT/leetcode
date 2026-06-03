class Solution {
public:
  int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
    map<int, int> landmap;
    for (int i = 0; i < landStartTime.size(); ++i) {
    
   if (landmap.find(landStartTime[i] + landDuration[i]) != landmap.end()) {
     landmap[landStartTime[i] + landDuration[i]] = max(landStartTime[i], landmap[landStartTime[i] + landDuration[i]]);
   } else {
     landmap.insert({landStartTime[i] + landDuration[i], landStartTime[i]});
   } 
    }
    
    int ans = INT_MAX;
    for (int i = 0; i < waterStartTime.size(); ++i) {
      int ws = waterStartTime[i];
      int we = waterStartTime[i] + waterDuration[i];
      if (ans <= we) continue;
      for (auto [le, ls] : landmap) {
        if (ans <= le) break;
        int min_time = le + we - max(min(le, ws), min(we, ls));
        ans = min(ans, min_time);
      }
    }
    
    return ans;
  }
};