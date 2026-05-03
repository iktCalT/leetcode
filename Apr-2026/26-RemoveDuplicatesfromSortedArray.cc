#include <vector>

class Solution {
public:
  int removeDuplicates(std::vector<int> &nums) {
    // I need 2 pointers:
    // one for the last occupied (or first unoccupied) position
    // one for the frontier value to examine

    if (nums.size() <= 1) {
      return nums.size();
    }

    int occupied, front;

    for (occupied = 0, front = 1; front < nums.size(); occupied++, front++) {
      while (front < nums.size() && nums[front] == nums[occupied]) {
        front++;
      }

      // Case 1: exit because front reaches the end
      if (front == nums.size()) {
        if (nums[front - 1] != nums[occupied]) {
          nums[occupied + 1] = nums[front - 1];
          occupied++;
          break;
        } else {
          break;
        }
      } 

      // Case 2: exit because front encounters new value
      nums[occupied + 1] = nums[front];
    }

    return occupied + 1;
  }
};