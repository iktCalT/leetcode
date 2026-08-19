#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
private:
  vector<unsigned char> occupied;

  const unsigned char one =   0b00001111;
  const unsigned char two =   0b00111100;
  const unsigned char three = 0b11110000;
  
  void genOccupied() {
    occupied = vector<unsigned char>(1<<8);
    for (int i = 0; i < (1<<8); ++i) {
      if ((i & one) && (i & two) && (i & three))
        occupied[i] = 2;
      else if (!(i & one) && !(i & two) && !(i & three)) 
        // if (i == 0)
        occupied[i] = 0;
      else 
        occupied[i] = 1;
    }
  }

public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    // Maximum: 2 * n <= 2e9 < INT_MAX -> using int is enough

    // Bit manipulation
    // Let only consider seats 2 to 9
    // All seats are reserved: 1111 1111
    // None seat is reserved: 0000 0000

    genOccupied();

    unordered_map<int, unsigned char> bitmap;
    for (const vector<int>& seat : reservedSeats) {
      if (seat[1] == 1 || seat[1] == 10) continue;

      int row = seat[0] - 1;
      int col = seat[1] - 2;

      auto it = bitmap.find(row);
      if (it == bitmap.end()) {
        bitmap.emplace(row, (1 << col));
      } else {
        bitmap[row] = bitmap[row] | (1 << col);
      }
    }

    int cnt = 2 * n;
    for (const auto& [row, bits] : bitmap) {
      cnt -= occupied[bits];
    }
    return cnt;
  }
};

/* Memory Limit Exceeded */
class Solution1 {
private:
  const char one =   0b00001111;
  const char two =   0b00111100;
  const char three = 0b11110000;
  
  int check(int i) {
    if ((i & one) && (i & two) && (i & three))
      return 0;
    else if (!(i & one) && !(i & two) && !(i & three))
      return 2;
    else
      return 1;
  }

public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    // Maximum: 2 * n <= 2e9 < INT_MAX -> using int is enough

    // Bit manipulation
    // All seats are reserved: 11 1111 1111
    // None seat is reserved: 00 0000 0000
    // Let only consider seats 2 to 9

    vector<char> resv(n, 0);
    for (const vector<int>& seat : reservedSeats) {
      int row = seat[0] - 1;
      int col = seat[1] - 2;
      resv[row] = col == -1 || col == 8 
                  ? resv[row] 
                  : resv[row] | (1 << col);
    }

    int cnt = 0;
    for (const char& r : resv) {
      cnt += check(r);
    }
    return cnt;
  }
};

/* Memory Limit Exceeded */
class Solution0 {
private:
  vector<char> check_table;

  const char one =   0b00001111;
  const char two =   0b00111100;
  const char three = 0b11110000;
  
  void genCheckTable() {
    check_table = vector<char>(1<<8);
    for (int i = 0; i < (1<<8); ++i) {
      if ((i & one) && (i & two) && (i & three))
        check_table[i] = 0;
      else if (!(i & one) && !(i & two) && !(i & three))
        check_table[i] = 2;
      else 
        check_table[i] = 1;
    }
  }

public:
  int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
    // Maximum: 2 * n <= 2e9 < INT_MAX -> using int is enough

    // Bit manipulation
    // All seats are reserved: 11 1111 1111
    // None seat is reserved: 00 0000 0000
    // Let only consider seats 2 to 9

    genCheckTable();

    vector<char> resv(n, 0);
    for (const vector<int>& seat : reservedSeats) {
      int row = seat[0] - 1;
      int col = seat[1] - 2;
      resv[row] = col == -1 || col == 8 
                  ? resv[row] 
                  : resv[row] | (1 << col);
    }

    int cnt = 0;
    for (const char& r : resv) {
      cnt += check_table[r];
    }
    return cnt;
  }
};

int main() {
  Solution demo;
  vector<vector<int>> r{{1,2},{1,3},{1,8},{2,6},{3,1},{3,10}};
  demo.maxNumberOfFamilies(3, r);
}