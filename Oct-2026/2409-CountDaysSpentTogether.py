class Solution:
    def __init__(self):
        self.dates: list = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        for i in range(12):
            self.dates[i+1] += self.dates[i]

    def countDaysTogether(self, arriveAlice: str, leaveAlice: str, arriveBob: str, leaveBob: str) -> int:
        aa: int = self.date(arriveAlice)
        la: int = self.date(leaveAlice)
        ab: int = self.date(arriveBob)
        lb: int = self.date(leaveBob)

        # print(f"{aa} {la} {ab} {lb}")
        return max(0, min(la, lb) - max(aa, ab) + 1)
        
    def date(self, s: str) -> int:
        m: int = int(s[:2])
        d: int = int(s[3:5])
        
        return self.dates[m-1] + d
