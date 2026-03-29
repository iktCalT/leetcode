#include <cstdio>
#include <vector>

class Solution {
public:
  int maxArea(std::vector<int> &height) {

    int max = 0, area;
    int left = 0, right = height.size() - 1;
    while (right > left) {
      if (height[left] <= height[right]) { // including height[left] == 0
        area = (right - left) * height[left];
        left++;
      } else { // including height[right] == 0
        area = (right - left) * height[right];
        right--;
      }
      if (max < area)
        max = area;
    }
    return max;
  }
};

int main() {
  Solution demo = Solution();
  std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  printf("%d\n", demo.maxArea(height) - 49);

  height = {1};
  printf("%d\n", demo.maxArea(height) - 0);

  height = {0, 2};
  printf("%d\n", demo.maxArea(height) - 0);
}