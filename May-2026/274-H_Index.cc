#include <algorithm>
#include <vector>

class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        sort(citations.begin(), citations.end(), std::greater<int>()); // O(nlog(n))
        int h = 1;
        for ( ; h <= citations.size(); ++h) {
            if (citations[h - 1] < h) break;
        }
        return h - 1;
    }
};