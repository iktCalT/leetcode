from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        diffs: list[int] = []
        for i in range(len(nums)):
            diff = target - nums[i]
            if (nums[i] in diffs):
                return [diffs.index(nums[i]), i]
            diffs.append(diff)
        return [-1,-1]
    
if __name__ == "__main__":
    demo = Solution()
    print(demo.twoSum([2,7,11,15], 9))
    print(demo.twoSum([3,2,5], 6))