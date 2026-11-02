#include <vector>
using namespace std;

class Matrix3D {
private:
  vector<vector<__uint128_t>> matrix;
  vector<int> count;
  int n;

public:
  Matrix3D(int n) {
    this->n = n;
    matrix =  vector<vector<__uint128_t>> (n, 
              vector<__uint128_t> (n, 0));
    count = vector<int> (n, 0);
  }
  
  void setCell(int x, int y, int z) {
    count[x] += (matrix[x][y] & ((__uint128_t)1 << z)) == 0;
    matrix[x][y] |= ((__uint128_t)1 << z);
  }
  
  void unsetCell(int x, int y, int z) {
    count[x] -= (matrix[x][y] & ((__uint128_t)1 << z)) != 0;
    matrix[x][y] &= ~((__uint128_t)1 << z);
  }
  
  int largestMatrix() {
    int largest = 0;
    int pos = 0;
    for (auto cit = count.cbegin(); cit != count.cend(); ++cit) {
      if (*cit >= largest) {
        pos = distance(count.cbegin(), cit);
        largest = *cit;
      }
    }
    return pos;
  }
};

/**
 * Your Matrix3D object will be instantiated and called as such:
 * Matrix3D* obj = new Matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */

class Matrix3D_0 {
private:
  vector<vector<vector<bool>>> matrix;
  vector<int> count;
  int n;

public:
  Matrix3D_0(int n) {
    this->n = n;
    matrix =  vector<vector<vector<bool>>> (n, 
              vector<vector<bool>> (n, 
              vector<bool> (n, 0)));
    count = vector<int> (n, 0);
  }
  
  void setCell(int x, int y, int z) {
    if (matrix[x][y][z] == 0) {
      matrix[x][y][z] = 1;
      ++count[x];
    }
  }
  
  void unsetCell(int x, int y, int z) {
    if (matrix[x][y][z] == 1) {
      matrix[x][y][z] = 0;
      --count[x];
    }
  }
  
  int largestMatrix() {
    int largest = 0;
    int pos = 0;
    for (auto cit = count.cbegin(); cit != count.cend(); ++cit) {
      if (*cit >= largest) {
        pos = distance(count.cbegin(), cit);
        largest = *cit;
      }
    }
    return pos;
  }
};

/**
 * Your Matrix3D object will be instantiated and called as such:
 * Matrix3D* obj = new Matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */