#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    struct TireNode {
        // Max memory occupation: 5 * 10 ^ 5 * (4 + 4 + 26 * 8) bytes (64-bit) = 108 Mb
        // We should place them on heap
        int index; // index of shortest string
        int length; // length of shortest string
        array<shared_ptr<TireNode>, 26> next;
        TireNode()
        : index(-1), length(INT_MAX), next(array<std::shared_ptr<TireNode>, 26>()) {}

        void renewInfo(char c, int ind, int len) {
            int i = c - 'a';
            if (len < length) {
                length = len;
                index = ind;
            } else if (len == length) {
                index = min(ind, index);
            }
        }

        inline shared_ptr<TireNode> add(char c) {
            // wordsContainer[i] and wordsQuery[i] consists only of lowercase English letters.
            int i = c - 'a';
            if (!next[i]) {
                next[i] = make_shared<TireNode>();
            }
            return next[i];
        }
    };

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Trie, from end to beginning

        shared_ptr<TireNode> root = make_shared<TireNode>();

        for (int i = 0; i < wordsContainer.size(); ++i) {
            string& word = wordsContainer[i];
            shared_ptr<TireNode> p = root;
            for (auto crit = word.crbegin(); crit != word.crend(); ++crit) {
                p->renewInfo(*crit, i, word.size());
                p = p->add(*crit);
            }
            p->renewInfo(word.front(), i, word.size());
        }

        vector<int> ans;
        ans.reserve(wordsQuery.size());
        for (const string& word : wordsQuery) {
            shared_ptr<TireNode> p = root;
            for (auto crit = word.crbegin(); crit != word.crend(); ++crit) {
                if (p->next[*crit - 'a'] == nullptr) break;
                p = p->next[*crit - 'a'];
            }
            
            ans.push_back(p->index);
        }

        return ans;
    }
};


/* class SolutionUnfinished {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        // Although trie is faster, the length of container and words are too large
        // tire will cause memory explosion

        // Sort by suffix, then find the smallest one with their indices
        map<string, int, smallerSuffix> sorted_container;
        for (int i = 0; i < wordsContainer.size(); ++i) {
            sorted_container.insert({wordsContainer[i], i});
        }

        int lo = 0, hi = sorted_container.size();
        while (hi > lo + 1) {
            int mid = (hi + lo) / 2;
            // Unfinished
        }
    }

private:
    struct smallerSuffix {
        bool operator()(string s1, string s2) {
                // "...baxy" < "...bcxy", because 'a' < 'c'
                for (int i = 0; i < min(s1.size(), s2.size()); ++i) {
                    if (*(s1.end() - i) < *(s2.end() - i)) {
                        return true;
                    } else if (*(s1.end() - i) > *(s2.end() - i)) {
                        return false;
                    }
                }

                // Get out of loop, meaning one is the suffix of another
                if (s1.size() < s2.size()) {
                    return true;
                }
                return false;
          }
    };
}; */

int main() {
    Solution demo;
    vector<string> container{"abcdefgh","poiuygh","ghghgh"};
    vector<string> query{"gh","acbfgh","acbfegh"};
    auto ans = demo.stringIndices(container, query);
    for (int i : ans) {
        std::cout << i << "\n";
    }
}