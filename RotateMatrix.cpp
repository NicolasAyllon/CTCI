/*
Rotate Matrix:
Given an image represented by an N x N matrix, where each pixel in the image
is 4 bytes, write a method to rotate the image by 90 degrees.
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

// In-place counterclockwise rotation 
// For square (N x N) matrices
void rotateSquareMatrixCounterclockwise(std::vector< std::vector<int> >& m) {
  // Do nothing if matrix is empty or not square
  if (m.empty()) return;
  int rows = m.size();
  int cols = m[0].size();
  if(rows != cols) return;

  int N = rows;
  int temp;

  /*
        0           j          N-1 
        |                    -i |
    0->(*)  *   *  ...  *   *<-(*)
        |+i                 |    
        *-->*->(*) ...  *   *   *
             +j             |+j
        *   *   *  ...  *  (*)   *
    i              ...      
        *  (*)  *  ...  *   *   *
          -j|              -j
        *   *   *  ... (*)<-*<--*
            |                   | -i
  N-1->(*)->*   *  ...  *   *  (*)
          +i
  */
 
  for(int i = 0; i < N/2; ++i) {
    for(int j = 0; j < (N+1)/2; ++j) {
      temp = m[i][j];
      m[0  +i][0  +j] = m[0  +j][N-1-i];
      m[0  +j][N-1-i] = m[N-1-i][N-1-j];
      m[N-1-i][N-1-j] = m[N-1-j][0  +i];
      m[N-1-j][0  +i] = temp;
    }
  }
}

void printMatrix(const std::vector< std::vector<int> >& m) {
  int rows = m.size();
  int cols = m[0].size();
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      std::cout << m[i][j] << " ";
    }
    std::cout << '\n';
  }
}

int main() {
  std::ifstream testFile("RotateMatrix_test.txt");
  int num_matrices;
  int N;
  if(testFile.is_open()) {
    testFile >> num_matrices;

    while(num_matrices--) {
      testFile >> N;
      std::vector<std::vector<int> > matrix;

      for(int i = 0; i < N; ++i) {
        std::vector<int> row;
        int val;
        for(int j = 0; j < N; ++j) {
          testFile >> val;
          row.push_back(val);
        }
        matrix.push_back(row);
      }
      std::cout << "before:" << '\n';
      printMatrix(matrix);
      std::cout << '\n';
      rotateSquareMatrixCounterclockwise(matrix);
      std::cout << "after:" << '\n';
      printMatrix(matrix);
      std::cout << '\n';
      std::cout << '\n';
    }
  }
}
