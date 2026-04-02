class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        """
            if we append a character to the end of s string
            the longest substring without repeating could be either
            1. the longest substring without repeating of s
            or
            2. the last several characters without repeating of s + 1
               means: the last several characters without repeating
               is the longest substring without repeating
        """
        if len(s) <= 1:
            return len(s)
        longest_count = 0
        end_str : list = [] # list is faster than str
        is_end_longest = True
        for c in s:
            if c in end_str:
                del end_str[:end_str.index(c)+1] # without creating a new List object. Faster than end_str = []
            else:
                longest_count += is_end_longest
            end_str.append(c)
            is_end_longest = (len(end_str) == longest_count)
        return longest_count
    
    def lengthOfLongestSubstring_another(self, s: str) -> int:
        """ 
            The reverse process of the method above 
            But it uses recursion, making it much slower and space consuming than the first method
        
            The longest substring without repeating characters of s must be either
            1. longest substring without repeating characters of s[:-1]
            or 
            2. the last several non-repetitive characters of s 
        """
        if len(s) <= 1:
            return len(s)
        # the number of last non-repetitive characters of s
        end_str = []
        for c in s[::-1]:
            if c not in end_str:
                end_str.append(c)
            else:
                break
        # compare and return
        return max(len(end_str), self.lengthOfLongestSubstring(s[:-1]))

if __name__ == "__main__":
    demo = Solution()
    print(demo.lengthOfLongestSubstring("abcabcbb"))
    print(demo.lengthOfLongestSubstring("bbbbb"))
    print(demo.lengthOfLongestSubstring("pwwkew"))
    print(demo.lengthOfLongestSubstring("dvdf"))