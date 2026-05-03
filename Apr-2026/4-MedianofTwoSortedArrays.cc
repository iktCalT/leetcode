#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <vector>

class Solution {
public:
  double findMedianSortedArrays(std::vector<int> &nums1,
                                std::vector<int> &nums2) {
    int length = nums1.size() + nums2.size();
    bool is_even = !(length % 2);

    if (is_even) {
      if (nums1.size() <= nums2.size()) {
        return findMedianNandNPlus1SortedArraysEven(
            nums1, 0, nums1.size() - 1, nums2, 0, nums2.size() - 1, length / 2);
      } else {
        return findMedianNandNPlus1SortedArraysEven(
            nums2, 0, nums2.size() - 1, nums1, 0, nums1.size() - 1, length / 2);
      }
    } else {
      if (nums1.size() <= nums2.size()) {
        return findNthSortedArraysOdd(nums1, 0, nums1.size() - 1, nums2, 0,
                                      nums2.size() - 1, (length + 1) / 2);
      } else {
        return findNthSortedArraysOdd(nums2, 0, nums2.size() - 1, nums1, 0,
                                      nums1.size(), (length + 1) / 2);
      }
    }
  }

private:
  double findMedianNandNPlus1SortedArraysEven(std::vector<int> &nums1,
                                              int start1, int end1,
                                              std::vector<int> &nums2,
                                              int start2, int end2, int n) {
    // Find the median of n-th and n+1th of two sorted subarrays
    int len1 = end1 - start1 + 1; // Consider only a slice of container
    int len2 = end2 - start2 + 1;
    int tlen = len1 + len2; // total length

    // Optimization: if len1 is 0 or 1 (len1 <= len2)
    if (len1 <= 1) {
      int tmp = len1 ? nums1[start1] : INT_MAX;
      if (start2 + n >= 2 && tmp < nums2[start2 + n - 2]) {
        return 1.0 / 2 * (nums2[start2 + n - 2] + nums2[start2 + n - 1]);
      } else if (start2 + n >= nums2.size() || tmp <= nums2[start2 + n]) {
        return 1.0 / 2 * (tmp + nums2[start2 + n - 1]);
      } else {
        return 1.0 / 2 * (nums2[start2 + n - 1] + nums2[start2 + n]);
      }
    }

    // Assign how many to exceed in nums1 and nums2 respectively
    int ex1 = n * len1 / tlen; // an integer rather than a float
    int ex2 = n - ex1;

    int low1 = ex1 ? nums1[start1 - 1 + ex1] : INT_MIN;
    int high1 = nums1[start1 + ex1];
    int low2 = ex2 ? nums2[start2 - 1 + ex2] : INT_MIN;
    int high2 = nums2[start2 + ex2];
    if (std::max(low1, low2) <= std::min(high1, high2)) {
      return 1.0 / 2 * (std::max(low1, low2) + std::min(high1, high2));
    } else {
      if (low1 < low2) {
        // low1 < high1 < low2 < high2
        start1 = start1 + ex1;
        n -= ex1;
        end2 = start2 + ex2 >= 1 ? start2 + ex2 - 1 : 0;
      } else {
        // low2 < high2 < low1 < high1
        start2 = start2 + ex2;
        n -= ex2;
        end1 = start1 + ex1 >= 1 ? start1 + ex1 - 1 : 0;
      }
      if (len1 <= len2) {
        return findMedianNandNPlus1SortedArraysEven(nums1, start1, end1, nums2,
                                                    start2, end2, n);
      } else {
        return findMedianNandNPlus1SortedArraysEven(nums2, start2, end2, nums1,
                                                    start1, end1, n);
      }
    }
  }

  double findNthSortedArraysOdd(std::vector<int> &nums1, int start1, int end1,
                                std::vector<int> &nums2, int start2, int end2,
                                int n) {
    // Find the n-th smallest number in two sorted subarrays
    int len1 = end1 - start1 + 1; // Consider only a slice of container
    int len2 = end2 - start2 + 1;
    int tlen = len1 + len2; // total length

    // Optimization: if len1 is 0 or 1 (len1 <= len2)
    if (len1 <= 1) {
      int tmp = len1 ? nums1[start1] : INT_MAX;
      std::vector<int> possible_values = {
          tmp, start2 + n >= 2 ? nums2[start2 + n - 2] : INT_MIN,
          nums2[start2 + n - 1]};
      std::sort(possible_values.begin(), possible_values.end());
      return possible_values[1];
    }

    // Assign how many to exceed in nums1 and nums2 respectively
    int ex1 = (n - 1) * len1 / tlen; // an integer rather than a float
    int ex2 = n - 1 - ex1;

    int low1 = ex1 ? nums1[start1 - 1 + ex1] : INT_MIN;
    int high1 = nums1[start1 + ex1];
    int low2 = ex2 ? nums2[start2 - 1 + ex2] : INT_MIN;
    int high2 = nums2[start2 + ex2];
    if (std::max(low1, low2) <= std::min(high1, high2)) {
      // low1, low2 < high1, high2
      return (double)std::min(high1, high2);
    } else {
      if (low1 < low2) {
        // low1 < high1 < low2 < high2
        start1 = start1 + ex1;
        n -= ex1;
        end2 = start2 + ex2 >= 1 ? start2 + ex2 - 1 : 0;
      } else {
        // low2 < high2 < low1 < high1
        start2 = start2 + ex2;
        n -= ex2;
        end1 = start1 + ex1 >= 1 ? start1 + ex1 - 1 : 0;
      }
      if (len1 <= len2) {
        return findNthSortedArraysOdd(nums1, start1, end1, nums2, start2, end2,
                                      n);
      } else {
        return findNthSortedArraysOdd(nums2, start2, end2, nums1, start1, end1,
                                      n);
      }
    }
  }
};

int main() {
  Solution demo = Solution();

  std::vector<int> nums1;
  std::vector<int> nums2;

  nums1 = {1, 3};
  nums2 = {2};
  printf("1 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2);

  nums1 = {1, 2};
  nums2 = {3, 4};
  printf("2 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2.5);

  nums1 = {3, 4};
  nums2 = {1, 2, 5};
  printf("3 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 3);

  nums1 = {1, 2, 5};
  nums2 = {0, 3, 4};
  printf("4 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2.5);

  nums1 = {};
  nums2 = {1};
  printf("5 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 1);

  nums1 = {};
  nums2 = {1, 2};
  printf("6 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 1.5);

  nums1 = {1, 3, 5, 7, 8, 9, 10, 11, 12};
  nums2 = {2};
  printf("7 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 7.5);

  nums1 = {2};
  nums2 = {1, 3, 5, 7, 8, 9, 10, 11, 12, 13};
  printf("8 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 8);

  nums1 = {1, 2, 3, 4, 5};
  nums2 = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  printf("9 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 9);

  nums1 = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  nums2 = {1, 2, 3, 4, 5};
  printf("10 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 9);

  nums1 = {1, 2};
  nums2 = {1, 2, 3};
  printf("11 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2);

  nums1 = {1, 2, 4};
  nums2 = {3};
  printf("12 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2.5);

  nums1 = {3, 4, 5};
  nums2 = {1, 2};
  printf("13 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 3);

  nums1 = {1, 2, 6};
  nums2 = {3, 4, 5, 7, 8, 9, 10};
  printf("14 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 5.5);

  nums1 = {1, 6};
  nums2 = {3, 4};
  printf("15 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 3.5);

  nums1 = {0, 0};
  nums2 = {0, 0};
  printf("16 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 0);

  nums1 = {1, 2, 7};
  nums2 = {3, 4, 5, 6, 8, 9, 10};
  printf("17 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 5.5);

  nums1 = {1, 5, 6};
  nums2 = {2, 3, 4, 7, 8, 9, 10};
  printf("18 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 5.5);

  nums1 = {-10, -9, -8};
  nums2 = {1, 2};
  printf("19 %f\n", demo.findMedianSortedArrays(nums1, nums2) - (-8));

  nums1 = {1, 2, 2};
  nums2 = {1, 2, 3};
  printf("20 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 2);

  nums1 = {5, 6};
  nums2 = {1, 2, 3, 4};
  printf("21 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 3.5);

  nums1 = {1};
  nums2 = {1};
  printf("22 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 1);

  nums1 = {2};
  nums2 = {};
  printf("22 %f\n", demo.findMedianSortedArrays(nums1, nums2) - 1);
}