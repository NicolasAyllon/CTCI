/*
Zero Matrix:
Write an algorithm such that if an element in an M x N matrix is 0,
its entire row and column are set to 0.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

void propagateZeros(std::vector<std::vector<int> >& m) {
  // Do nothing if there are 0 rows or columns
  if(m.empty() || m[0].empty()) return;
  // Get dimensions
  int rows = m.size();
  int cols = m[0].size();
  
  // Create sets to track rows and columns to clear
  std::set<int> rowsToClear;
  std::set<int> colsToClear;

  // Add rows and cols to cleared to sets
  for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
      if(m[i][j] == 0) {
        rowsToClear.insert(i);
        colsToClear.insert(j);
      }
    }
  }

  // Clear rows
  for(int i : rowsToClear) {
    for(int j = 0; j < cols; ++j) {
      m[i][j] = 0;
    }
  }

  // Clear cols
  for(int j : colsToClear) {
    for(int i = 0; i < rows; ++i) {
      m[i][j] = 0;
    }
  }
}

void printMatrix(const std::vector<std::vector<int> >& m) {
  if(m.size() == 0 || m[0].size() == 0) return;
  for(int i = 0; i < m.size(); ++i) {
    for(int j = 0; j < m[0].size(); ++j) {
      std::cout << m[i][j] << " ";
    }
    std::cout << '\n';
  }
}


int main() {
  std::ifstream testFile("ZeroMatrix_test.txt");
  if(testFile.is_open()) {
    int num_matrices;
    testFile >> num_matrices;
    int rows, cols;
    int test_num;
    for(test_num = 1; test_num <= num_matrices; ++test_num) {
      std::vector<std::vector<int> > matrix;
      testFile >> rows >> cols;
      for(int i = 0; i < rows; ++i) {
        std::vector<int> row;
        for(int j = 0; j < cols; ++j) {
          int val;
          testFile >> val;
          row.push_back(val);
        }
        matrix.push_back(row);
      }
      std::cout << "TEST " << test_num << '\n';
      std::cout << "before:" << '\n';
      printMatrix(matrix); 
      std::cout <<'\n';
      propagateZeros(matrix);
      std::cout << "after:" << '\n';
      printMatrix(matrix);
      std::cout <<'\n';
      std::cout <<'\n';
    }
  }
}