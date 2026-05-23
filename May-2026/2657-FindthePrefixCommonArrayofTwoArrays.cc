#include <algorithm>
#include <vector>

class Solution {
public:
    std::vector<int> findThePrefixCommonArray(std::vector<int>& A, std::vector<int>& B) {
        // A and B are both a permutation of n integers
        // I will keep 2 vectors, unmatchedA and unmatchedB 
        // to store unmatched elements before index i
        std::vector<int> prefix(A.size(), 0);
        std::vector<int> unmatchedA;
        unmatchedA.reserve(A.size());
        std::vector<int> unmatchedB;
        unmatchedB.reserve(A.size()); // not B.size() -> spacial locality

        // Initialization: so that we don't need if (i == 0) in loop
        if (A[0] == B[0]) {
            prefix[0] = 1;
        } else {
            unmatchedA.push_back(A[0]);
            unmatchedB.push_back(B[0]);
            // unnecessary: prefix[0] = 0; 
        }

        for (int i = 1; i < A.size(); ++i) {
            if (A[i] == B[i]) {
                prefix[i] = prefix[i - 1] + 1;
                continue;
            }

            prefix[i] = prefix[i - 1];
            auto itB = std::find(unmatchedB.begin(), unmatchedB.end(), A[i]);
            if (itB != unmatchedB.end()) {
                *itB = -1; // mark it as "matched", don't delete it, rearrange is time consuming
                ++prefix[i];
            } else {
                unmatchedA.push_back(A[i]);
            }

            auto itA = std::find(unmatchedA.begin(), unmatchedA.end(), B[i]);
            if (itA != unmatchedA.end()) {
                *itA = -1;
                ++prefix[i];
            } else {
                unmatchedB.push_back(B[i]);
            }
        }

        return prefix;
    }
};