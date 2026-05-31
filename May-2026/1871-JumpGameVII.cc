#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        // DFS
        // "0111101010" minJump = 5, maxJump = 7: 0->5->9
        // "011111000111000001011111010", minJump = 6, maxJump = 8: 0->6->12->18->26
        if (s.back() != '0') return false;
        // Init global variable
        platforms = vector<int>();
        // Fill in platforms
        for (int i = 0; i < s.size(); ++i) { // include index 0
            if (s[i] == '0') platforms.push_back(i);
        }

        return Jump(minJump, maxJump, 0);
    }

private:
    vector<int> platforms;

    bool Jump(int minJump, int maxJump, int cur) {
        // cur is the index of platforms
        if (cur == platforms.size() - 1) return true;

        int start = -1, end = -1;
        for (int next = cur + 1; next < platforms.size(); ++next) {
            if (platforms[next] < platforms[cur] + minJump) continue;
            if (platforms[next] > platforms[cur] + maxJump) break;

            start = start < 0 ? next : start;
            end = next;
            if (Jump(minJump, maxJump, next)) return true;
        }
        if (start >= 0)
            platforms.erase(platforms.begin() + start, platforms.begin() + end + 1);
        
        return false;
    }
};

// Be careful:
// 4999 * '0' + 4999 * '1' + '0'; minJump = 1, maxJump = 4999  false
// 4999 * '0' + 4998 * '1' + "00"; minJump = 1, maxJump = 4999  true
// 4999 * '0' + 4998 * '1' + "00"; minJump = 2, maxJump = 4999  false (jump over)
// 4999 * '0' + "110" + 4996 * '1' + '0'; minJump = 4, maxJump = 4999  true
// 10000 * '0'; minJump = 1, maxJump = 1  true
// 4999 * '0' + '1' + 4998 * '0'; minJump = 1, maxJump = 1  false

int main() {
  Solution demo;
  std::cout << demo.canReach("011111111111111110", 1, 9) << "\n";
  std::cout << demo.canReach("011111000111000001011111010", 6, 8) << "\n";
}