from typing import List

class Solution:
    def getStrongest(self, arr: list[int], k: int) -> list[int]:
        arr.sort()
        n: int = len(arr)
        m: int = arr[(n-1)//2]
        l = 0
        r = n-1
        ans: List[int] = []

        while (l <= r and k != 0):
            k -= 1
            if (arr[r] - m >= m - arr[l]):
                ans.append(arr[r])
                r -= 1
            else:
                ans.append(arr[l])
                l += 1

        return ans