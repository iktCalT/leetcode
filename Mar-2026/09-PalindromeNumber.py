class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        sx = str(x)
        for i in range(len(sx)//2):
            if (sx[i] != sx[len(sx) - 1 - i]):
                return False
        return True
    
if __name__ == "__main__":
    demo = Solution()
    print(demo.isPalindrome(12321))
    print(demo.isPalindrome(-121))
    print(demo.isPalindrome(12))
    print(demo.isPalindrome(0))