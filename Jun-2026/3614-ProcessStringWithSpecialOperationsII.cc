#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// The previous method is too heavy, causing MLE
// This time, only record the size of each part
// 157ms, still slow
struct Fix {
  // prefix or suffix
  int size_char; // don't need long long, because it <= s.size() <= 10^5
  int size_remove;
};

class Segment {
public:
  // times * [ls + inner + rs].r
  // if (reversed) -> times * [ls + inner + rs]
  // else ->  times * [ls + inner + rs].r or times * [rs.r + inner.r + ls.r]
  long long size;
  long long times;
  bool reversed;
  Segment *inner;
  Fix prefix; 
  Fix suffix;
  int position; // position <= s.size() <= 10^5

  Segment(int position)
      : size(0), times(1), reversed(false), inner(nullptr), 
        prefix(0), suffix(0), position(position) {}

  ~Segment() {
    if (inner != nullptr) {
      delete inner;
    }
  }

  void remove() {
    if (size == 0)
      return;

    --size;
    if (size == 0) {
      delete inner;
      inner = nullptr;
      prefix = {0, 0};
      suffix = {0, 0};
      return;      
    }


    // keep record of removal in ls or rs
    if (inner != nullptr) {
      if (!reversed) {
        if (suffix.size_char == 0) {
          ++suffix.size_remove;
        } else {
          --suffix.size_char;
        }
      } else {
        if (prefix.size_char == 0) {
          ++prefix.size_remove;
        } else {
          --prefix.size_char;
        }
      }
  
      if (prefix.size_remove + suffix.size_remove == inner->size * inner->times) {
        delete inner;
        inner = nullptr;
        prefix.size_remove = 0;
        suffix.size_remove = 0;
      }
    } else {
      if (!reversed) {
        if (suffix.size_char != 0) {
          --suffix.size_char;
        } else {
          // don't need to consider if prefix.size_char == 0,
          // we have considered total size == 0 case;
          --prefix.size_char;
        }
      } else {
        if (prefix.size_char != 0) {
          --prefix.size_char;
        } else {
          --suffix.size_char;
        }
      }
    }

  }

  Segment *duplicate(int position) {    
    Segment *outer = new Segment(position);
    outer->size = size * 2;
    outer->inner = this;
    times *= 2;
    return outer;
  }

  void reverse() { reversed = !reversed; }

  void addChar() {
    ++size;
    if (!reversed)
      ++suffix.size_char;
    else
      ++prefix.size_char;
  }
};

class Solution {
public:
  char processStr(const string s, long long k) {
    // "cd%#*#" -> 2 * [[2 * "cd".r] + 1 * "-"]
    // where '.r' means reverse, '-' means delete
    // or, expend '-': 2 * [1 * ["cd".r] + 1 * ["d"]]
    // I choose to expend when find k-th char,
    // making the structure as small as possible
    Segment *seg = new Segment(-1); // cannot be 0!!!
    for (int pos = 0; pos < s.size(); ++pos) {
      switch (s[pos]) {
      case '*':
        // pop back
        seg->remove();
        break;
      case '#':
        // duplicate
        seg = seg->duplicate(pos);
        break;
      case '%':
        // reverse
        seg->reverse();
        break;
      default:
        // add c
        seg->addChar();
      }
    }

    // find out answer
    if (k >= seg->size)
      return '.';

    for (Segment *p = seg; p != nullptr; p = p->inner) {
      long long rk;
      if (p->reversed) {
        rk = k;
        k = p->size - 1 - k;
      } else {
        rk = p->size - 1 - k; 
      }

      if (k < p->prefix.size_char) {
        string str;
        bool reversed = false;
        int i = p->position + 1;
        while (i < s.size() && s[i] != '#') {
          if (!reversed) {
            reversed = s[i] == '%'; // not reversed -> reversed
            ++i;
            continue;
          }

          switch (s[i]) {
          case '*': // remove
            if (str.empty() || str.front() == '-') {
              str = '-' + str;
            } else {
              str.erase(str.begin());
            }
            break;
          case '#': break; // this won't happen
          case '%': 
            reversed = !reversed;
            break;
          default:
            str = s[i] + str;
          }
          ++i;
        }

        return str[k];
      }

      if (rk < p->suffix.size_char) {
        string str;
        bool reversed = false;
        int i = p->position + 1;
        while (i < s.size() && s[i] != '#') {
          if (reversed) {
            reversed = s[i] != '%'; // reversed -> not reversed
            ++i;
            continue;
          }

          switch (s[i]) {
          case '*': // remove
            if (str.empty() || str.back() == '-') {
              str = '-' + str;
            } else {
              str.pop_back();
            }
            break;
          case '#': break; // this won't happen
          case '%': 
            reversed = !reversed;
            break;
          default:
            str = str + s[i];
          }
          ++i;
        }

        return *(str.rbegin() + rk);
      }

      // We have to verify should we find k in prefix or suffix
      // before finding in inner segment, because prefix and suffix
      // could be "---a" with size = -2
      k = k - p->prefix.size_char + p->prefix.size_remove;
      for (int i = 0; i < p->inner->times; ++i) {
        if (k < p->inner->size) {
          break;
        }
        k -= p->inner->size;
      }
    }

    exit(1); // this should not happen
  }
};

/*        MLE           */
struct Fix0 {
  // prefix and suffix
  long long size;
  string str;

  Fix0() : size(0), str() {}

  void popFront() {
    --size;
    if (str.size() == 0 || str.front() == '-') {
      str = '-' + str;
    } else {
      str.erase(str.begin());
    }
  }

  void popBack() {
    --size;
    if (str.size() == 0 || str.back() == '-') {
      str += '-';
    } else {
      str.pop_back();
    }
  }

  void pushFront(char c) {
    ++size;
    str = c + str;
  }

  void pushBack(char c) {
    ++size;
    str += c;
  }
};

class Segment0 {
public:
  // times * [ls + inner + rs].r
  // if (reversed) -> times * [ls + inner + rs]
  // else ->  times * [ls + inner + rs].r or times * [rs.r + inner.r + ls.r]
  long long size;
  long long times;
  bool reversed;
  Segment0 *inner;
  Fix0 prefix;
  Fix0 suffix;

  Segment0()
      : size(0), times(1), reversed(false), inner(nullptr), prefix(), suffix() {
  }

  void remove() {
    // if (size == 0), this must be a "clean" segment
    // because only "remove()" can make the size become 0
    // and after --size, we will check if size == 0,
    // if true, clean the segment
    if (size == 0)
      return;

    --size;
    if (size == 0) { // clean the segment
      // destroy the children of segment, and reset this to init values
      // size = 0
      times = 1;
      reversed = false;
      delete inner;
      inner = nullptr;
      prefix = Fix0();
      suffix = Fix0();
      return; // no element any more
    }

    // keep record of removal in ls or rs
    if (!reversed) {
      suffix.popBack();
    } else {
      prefix.popFront();
    }
  }

  Segment0 *duplicate() {
    Segment0 *outer = new Segment0;
    outer->size = size * 2;
    outer->inner = this;
    times *= 2;
    return outer;
  }

  void reverse() { reversed = !reversed; }

  void addChar(char c) {
    ++size;
    if (!reversed)
      suffix.pushBack(c);
    else
      prefix.pushFront(c);
  }

private:
  ~Segment0() { delete inner; }
};

class Solution0 {
public:
  char processStr(string s, long long k) {
    // "cd%#*#" -> 2 * [[2 * "cd".r] + 1 * "-"]
    // where '.r' means reverse, '-' means delete
    // or, expend '-': 2 * [1 * ["cd".r] + 1 * ["d"]]
    // I choose to expend when find k-th char,
    // making the structure as small as possible
    Segment0 *seg = new Segment0;
    for (const char &c : s) {
      switch (c) {
      case '*':
        // pop back
        seg->remove();
        break;
      case '#':
        // duplicate
        seg = seg->duplicate();
        break;
      case '%':
        // reverse
        seg->reverse();
        break;
      default:
        // add c
        seg->addChar(c);
      }
    }

    // find out answer
    if (k >= seg->size)
      return '.';

    for (Segment0 *p = seg; p != nullptr; p = p->inner) {
      long long rk;
      if (p->reversed) {
        rk = k;
        k = p->size - 1 - k;
      } else {
        rk = p->size - 1 - k;
      }

      if (k < (p->prefix.size + p->prefix.str.size()) / 2) {
        return p->prefix.str[k];
      }

      if (rk < (p->suffix.size + p->suffix.str.size()) / 2) {
        return *(p->suffix.str.rbegin() + rk);
      }

      // We have to verify should we find k in prefix or suffix
      // before finding in inner segment, because prefix and suffix
      // could be "---a" with size = -2
      k -= p->prefix.size;
      for (int i = 0; i < p->inner->times; ++i) {
        if (k < p->inner->size) {
          break;
        }
        k -= p->inner->size;
      }
    }

    exit(1); // this should not happen
  }
};

/*
  The following is an incorrect answer
        -> encountering problem with duplicate process
  1. I only connected head and tail, actually, we need to connect inner
     nodes.

     e.g.
     A -> B -> C -> D
     after duplicating A -> B -> C -> D -> A x> B x> C x> D
     "x>" means there should be a pointer "->", but in my
     solution, I didn't implement this

     To fix this problem, we need to iterating through the whole linked
     list. However this is time consuming. It is even less efficient than
     just copying.

  2. Secondly, I fix this problem by just shallow iterating,
     we can only create one copy, meaning

     e.g.
     Initial (2 * ABCD): A -> B -> C -> D -> A -> B -> C -> D
     We get (3 * ABCD): A -> B -> C -> D -> A -> B -> C -> D
                        -> A -> B -> C -> D
     We want (4 * ABCD): A -> B -> C -> D -> A -> B -> C -> D
                        -> A -> B -> C -> D -> A -> B -> C -> D

     We need to do deep iteratoring to fix this problem, which is
     even more time consuming. Worse than just copying.
*/
/*
struct Node {
  // If we don't want to cause memory leak,
  // use 4 deques, 2 of which are used to
  // store unused and used pointers
  deque<Node *> right;
  deque<Node *> left;
  string str;

  Node() : right({nullptr}), left({nullptr}) {}
  Node(string str) : right({nullptr}), left({nullptr}), str(str) {}
};

class Solution {
public:
  char processStr(string s, long long k) {
    // doubly linked list, A <-> B <-> C
    bool going_right = true;
    Node *head = new Node();
    Node *tail = head;
    Node *tmp;

    for (char &c : s) {
      switch (c) {
      case '*':
        // remove
        if (!(tail->left.size() == 1 && tail->right.size() == 1)) {
          // create a copy before removal
          tail = copyTail(tail, going_right);
        }
        if (going_right) {
          tail->str.pop_back();
          // if tail == head, just do nothing
          if (tail->str.empty() && tail != head)
            tail = tail->left.back();
        } else {
          tail->str.erase(tail->str.begin());
          if (tail->str.empty() && tail != head)
            tail = tail->right.front();
        }
        break;

      case '#': // INCORRECT!
        // duplicate
        if (tail == head && head->str.empty())
          break;

        if (going_right) {
          tail->right.back() = head;
          tail->right.push_back(nullptr);
          head->left.push_back(tail);
        } else {
          tail->left.front() = head;
          tail->left.push_front(nullptr);
          head->right.push_front(tail);
        }
        break;
      case '%':
        // reverse
        going_right = !going_right;
        tmp = head;
        head = tail;
        tail = tmp;
        break;
      default: // characters
        // add c
        if (!(tail->left.size() == 1 && tail->right.size() == 1)) {
          tail = copyTail(tail, going_right);
        }
        tail->str = going_right ? (tail->str + c) : (c + tail->str);
      }
    }

    // find out c
    char ans;
    test(head, going_right);

    return '0';
  }

private:
  Node *copyTail(Node *tail, bool going_right) {
    // create a copy before removal
    Node *new_node = new Node(tail->str);
    if (going_right) {
      tail->right.pop_back(); // pop out a nullptr
      new_node->left[0] = tail->left.back();
      // tail->left.back() is the previous node
      tail->left.back()->right.back() = new_node;
    } else {
      tail->left.pop_front();
      new_node->right[0] = tail->right.front();
      tail->right.front()->left.front() = new_node;
    }
    return new_node;
  }

  void test(Node *head, bool going_right) {
    Node *p = head;

    if (going_right) {
      cout << "going right: \t";
      while (p != nullptr) {
        cout << p->str << " : ";
        Node *nxt = p->right.front();
        p->right.pop_front();
        p = nxt;
      }
    } else {
      cout << "going left: \t";
      while (p != nullptr) {
        cout << p->str << " | "; // read it in reverse order
        Node *nxt = p->left.back();
        p->left.pop_back();
        p = nxt;
      }
    }
  }
};

*/

int main() {
  Solution demo;
  std::cout << demo.processStr("a#b%*", 1) << "\n";
}