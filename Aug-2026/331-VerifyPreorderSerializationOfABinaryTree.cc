#include <string>
using namespace std;

class Solution {
public:
  bool isValidSerialization(string preorder) {
    // Leaf node complete: next two are '#'
    // Node complete: left and right are complete 
    n = preorder.size();
    if (isValid(preorder, 0) == n) return true;
    return false;
  }

private:
  int n;

  int next(string& preorder, int i) {
    if (preorder[i] == ',') throw runtime_error("check code!");
    while (preorder[i] != ',') {
      ++i;
      if (i >= n - 1) return n;
    }
    return i + 1;
  }

  int isValid(string& preorder, int start) {
    // return the start of next node or -1 if fail
    if (start == n) return -1;
    
    if (preorder[start] == '#') return next(preorder, start);

    int left = next(preorder, start);
    int right;
    int next_node;
    // check left node
    if ((right = isValid(preorder, left)) == -1) return -1;
    // check right node
    if ((next_node = isValid(preorder, right)) == -1) return -1;

    return next_node;
  }
};