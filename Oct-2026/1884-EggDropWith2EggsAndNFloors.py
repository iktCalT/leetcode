class Solution:
  def twoEggDrop(self, n: int) -> int:
    i: int = 0
    while True:
      if (i * (i + 1) >= 2 * n): 
        return i
      i += 1