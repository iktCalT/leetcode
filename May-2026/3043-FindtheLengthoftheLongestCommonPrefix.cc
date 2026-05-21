#include <algorithm>
#include <array>
#include <string>
#include <vector>
using namespace std;

class Solution {
struct Node {
    array<Node, 10>* next;
    Node() : next(nullptr) {}
};

public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        // trie 
        // 1 <= arr1[i], arr2[i] <= 10^8, at most 10^8 nodes
        if (arr1.size() > arr2.size()) return longestCommonPrefix(arr2, arr1); //m ake trie smaller

        int len = 0;
        array<Node, 10> trie;
        // insert
        for (const int& num1 : arr1) {
            string str1 = to_string(num1);
            array<Node, 10>* p = &trie;
            for (const char& c : str1) {
                if (!(*p)[c - '0'].next) {
                    (*p)[c - '0'].next = new array<Node, 10>;
                }
                p = (*p)[c - '0'].next;
            }
        }

        // loop up
        for (const int& num2 : arr2) {
            string str2 = to_string(num2);
            if (str2.size() <= len) continue;

            array<Node, 10>* p = &trie;
            int tmp_len = 0;
            for (const char& c : str2) {
                if (!(*p)[c - '0'].next) break;
                ++tmp_len;
                p = (*p)[c - '0'].next;
            }

            len = max(len, tmp_len);
        }

        return len;
    }
};

int main() {
  Solution demo;
  vector<int> num1{1,10,3,4};
  vector<int> num2{444, 100};
  demo.longestCommonPrefix(num1, num2);
}