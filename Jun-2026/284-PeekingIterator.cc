/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

#include <vector>

using namespace std;

class Iterator {
  struct Data;
  Data* data;
public:
  Iterator(const vector<int>& nums);
  Iterator(const Iterator& iter);

  // Returns the next element in the iteration.
  int next();

  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

class PeekingIterator : public Iterator { // 3ms
bool has_next;
int nxt;

public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	  // Initialize any member here.
	  // **DO NOT** save a copy of nums and manipulate it directly.
	  // You should only use the Iterator interface methods.
	  has_next = Iterator::hasNext();
    if (has_next) {
      nxt = Iterator::next();
    }
	}
	
  // Returns the next element in the iteration without advancing the iterator.
	int peek() {
    return nxt;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
    int result = nxt;
	  if (has_next) {
      has_next = Iterator::hasNext();
      if (has_next) {
        nxt = Iterator::next();
      }
    } else {
      nxt = 0; // 0 means doesn't exist
    }
    return result;
	}
	
	bool hasNext() const {
	  return has_next;
	}
};

class PeekingIterator0 : public Iterator { // 3ms
private:
  // if is_peeking == false: 
  //    PeekingIterator's pointer == Iterator's pointer
  // else:
  //    PeekingIterator's pointer == Iterator's Pointer - 1
  bool is_peeking;
  // buffer[1 - is_peeking] == PeekingIterator's pointer
  // buffer[1] == Iterator's pointer
  array<int, 2> buffer;
public:
	PeekingIterator0(const vector<int>& nums) : Iterator(nums) {
    // Initialize any member here.
    // **DO NOT** save a copy of nums and manipulate it directly.
    // You should only use the Iterator interface methods.
    buffer = {0, 0};
    is_peeking = false;
	}
	
  // Returns the next element in the iteration without advancing the iterator.
	int peek() {
    if (!is_peeking) {
      this->next();
      is_peeking = true;
    }
    return buffer[1];
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
    if (!is_peeking) {
      buffer[0] = buffer[1];
      buffer[1] = Iterator::hasNext() ? Iterator::next() : 0;
    } else {
      is_peeking = false;
    }
    return buffer[1];
	}
	
	bool hasNext() const {
    if (!is_peeking) {
      return Iterator::hasNext();
    } else {
      return buffer[1]; // if buffer[1] == 0 -> don't have next
    }
	}
};