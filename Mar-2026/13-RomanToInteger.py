class Solution:
    def romanToInt(self, s: str) -> int:
        ONES = ['I', 'X', 'C', 'M']
        FIVES = ['V', 'L', 'D']
        result = 0
        last = 0
        is_ones = False
        for c in s:
            # if c in FIVES: add it
            # if c in ONES: add it
            # else: return
            if c in FIVES:
                current = 5 * 10 ** FIVES.index(c)
            elif c in ONES:
                current = 10 ** ONES.index(c)
                is_ones = True
            else:
                return 0  # Or: raise ValueError
            result += current
            
            # if last == 0: skip
            # if last == c's value /5 or /10: minus 2 * last
            if is_ones and ((last == current / 5) or (last == current / 10)):
                result -= 2 * last
                
            # set last
            last = current
            
        return result
    
if __name__ == "__main__":
    demo = Solution()
    print(demo.romanToInt("III"))
    print(demo.romanToInt("IV"))
    print(demo.romanToInt("LVIII"))     # 58
    print(demo.romanToInt("MCMXCIV"))   # 1994