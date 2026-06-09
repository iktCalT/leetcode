#include <string>

using namespace std;

class Solution {
public:
  int totalWaviness(int num1, int num2) {
    // method 1 brute force 
    if (num1 > num2) return 0;
    int cnt = 0;
    for (int i = num1; i <= num2; ++i) {
      cnt += countWaviness(i);
    }
    
    return cnt;
  }
  
 private:
   int countWaviness (int num) {
     int cnt = 0;
     string str = to_string(num);
      for (int i = 1; i < str.size() - 1; ++i) {
        cnt += (str[i] - str[i - 1]) * (str[i] - str[i + 1]) > 0;
      }
      return cnt;
   }
};