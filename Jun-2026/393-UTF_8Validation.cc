#include <vector>

using namespace std;

class Solution {
public:
  bool validUtf8(vector<int>& data) {
    int start = 0;
    while (start < data.size()) {
      if (!valid(start, data)) return false;
    }
    return true;
  }

private:
  bool valid(int& start, const vector<int>& data) {
    // return if valid and set start to be next start position
    int n = bits(data[start]);
    // cout << "bits: " << n << "\n";

    // 1 to 4 bytes
    if (n == -1 || n > 4 || start + n > data.size()) return false;
    for (int pos = start + 1; pos < start + n; ++pos) {
      if (!startWith10(data[pos])) return false;
    }
    start += n;
    return true;
  }

  inline bool startWith10(unsigned char byte) {
    if (byte >> 6 == 2) return true;
    return false;
  }

  int bits(unsigned char byte) {
    // 1111 1111 and 10xx xxxx are invalid
    if (byte == 255 || startWith10(byte)) return -1;

    // Start with 1, logical right shift, 
    // (notice byte is unsigned char)
    int bits;
    for (int i = 7; i >= 0; --i) {
      if ( !((byte >> i) % 2) ) {
        bits = 7 - i;
        break;
      }
    }
    // if bits == 0 (i == 7) -> 0xxxxxxx -> return 1
    return max(1, bits);
  }
};