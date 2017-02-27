//
//  Matrix.cpp
//  HermiteBezier
//
//  Created by Simkó Viktor on 2016. 11. 30..
//  Copyright © 2016. Simkó Viktor. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols) {
  storage.resize(rows);
  
  for (auto& row: storage) {
    row.resize(cols);
  }
}

Matrix Matrix::inverse() {
  float det = determinant();
  
  if (det == 0) {
    throw std::invalid_argument{ "The determinant of the matrix is 0!" };
  }
  
  Matrix result{ 4, 4 };
  
  result.storage[0][0] = storage[1][1] * storage[2][2] * storage[3][3]
                       + storage[1][2] * storage[2][3] * storage[3][1]
                       + storage[1][3] * storage[2][1] * storage[3][2]
                       - storage[1][3] * storage[2][2] * storage[3][1]
                       - storage[1][2] * storage[2][1] * storage[3][3]
                       - storage[1][1] * storage[2][3] * storage[3][2];
  
  result.storage[1][0] = storage[1][0] * storage[2][2] * storage[3][3]
                       + storage[1][2] * storage[2][3] * storage[3][0]
                       + storage[1][3] * storage[2][0] * storage[3][2]
                       - storage[1][3] * storage[2][2] * storage[3][0]
                       - storage[1][2] * storage[2][0] * storage[3][3]
                       - storage[1][0] * storage[2][3] * storage[3][2];
  result.storage[1][0] *= -1;
  
  result.storage[2][0] = storage[1][0] * storage[2][1] * storage[3][3]
                       + storage[1][1] * storage[2][3] * storage[3][0]
                       + storage[1][3] * storage[2][0] * storage[3][1]
                       - storage[1][3] * storage[2][1] * storage[3][0]
                       - storage[1][1] * storage[2][0] * storage[3][3]
                       - storage[1][0] * storage[2][3] * storage[3][1];
  
  result.storage[3][0] = storage[1][0] * storage[2][1] * storage[3][2]
                       + storage[1][1] * storage[2][2] * storage[3][0]
                       + storage[1][2] * storage[2][0] * storage[3][1]
                       - storage[1][2] * storage[2][1] * storage[3][0]
                       - storage[1][1] * storage[2][0] * storage[3][2]
                       - storage[1][0] * storage[2][2] * storage[3][1];
  result.storage[3][0] *= -1;
  
  result.storage[0][1] = storage[0][1] * storage[2][2] * storage[3][3]
                       + storage[0][2] * storage[2][3] * storage[3][1]
                       + storage[0][3] * storage[2][1] * storage[3][2]
                       - storage[0][3] * storage[2][2] * storage[3][1]
                       - storage[0][2] * storage[2][1] * storage[3][3]
                       - storage[0][1] * storage[2][3] * storage[3][2];
  result.storage[0][1] *= -1;
  
  result.storage[1][1] = storage[0][0] * storage[2][2] * storage[3][3]
                       + storage[0][2] * storage[2][3] * storage[3][0]
                       + storage[0][3] * storage[2][0] * storage[3][2]
                       - storage[0][3] * storage[2][2] * storage[3][0]
                       - storage[0][2] * storage[2][0] * storage[3][3]
                       - storage[0][0] * storage[2][3] * storage[3][2];
  
  result.storage[2][1] = storage[0][0] * storage[2][1] * storage[3][3]
                       + storage[0][1] * storage[2][3] * storage[3][0]
                       + storage[0][3] * storage[2][0] * storage[3][1]
                       - storage[0][3] * storage[2][1] * storage[3][0]
                       - storage[0][1] * storage[2][0] * storage[3][3]
                       - storage[0][0] * storage[2][3] * storage[3][1];
  result.storage[2][1] *= -1;
  
  result.storage[3][1] = storage[0][0] * storage[2][1] * storage[3][2]
                       + storage[0][1] * storage[2][2] * storage[3][0]
                       + storage[0][2] * storage[2][0] * storage[3][1]
                       - storage[0][2] * storage[2][1] * storage[3][0]
                       - storage[0][1] * storage[2][0] * storage[3][2]
                       - storage[0][0] * storage[2][2] * storage[3][1];
  
  result.storage[0][2] = storage[0][1] * storage[1][2] * storage[3][3]
                       + storage[0][2] * storage[1][3] * storage[3][1]
                       + storage[0][3] * storage[1][1] * storage[3][2]
                       - storage[0][3] * storage[1][2] * storage[3][1]
                       - storage[0][2] * storage[1][1] * storage[3][3]
                       - storage[0][1] * storage[1][3] * storage[3][2];
  
  result.storage[1][2] = storage[0][0] * storage[1][2] * storage[3][3]
                       + storage[0][2] * storage[1][3] * storage[3][0]
                       + storage[0][3] * storage[1][0] * storage[3][2]
                       - storage[0][3] * storage[1][2] * storage[3][0]
                       - storage[0][2] * storage[1][0] * storage[3][3]
                       - storage[0][0] * storage[1][3] * storage[3][2];
  result.storage[1][2] *= -1;
  
  result.storage[2][2] = storage[0][0] * storage[1][1] * storage[3][3]
                       + storage[0][1] * storage[1][3] * storage[3][0]
                       + storage[0][3] * storage[1][0] * storage[3][1]
                       - storage[0][3] * storage[1][1] * storage[3][0]
                       - storage[0][1] * storage[1][0] * storage[3][3]
                       - storage[0][0] * storage[1][3] * storage[3][1];
  
  result.storage[3][2] = storage[0][0] * storage[1][1] * storage[3][2]
                       + storage[0][1] * storage[1][2] * storage[3][0]
                       + storage[0][2] * storage[1][0] * storage[3][1]
                       - storage[0][2] * storage[1][1] * storage[3][0]
                       - storage[0][1] * storage[1][0] * storage[3][2]
                       - storage[0][0] * storage[1][2] * storage[3][1];
  result.storage[3][2] *= -1;

  result.storage[0][3] = storage[0][1] * storage[1][2] * storage[2][3]
                       + storage[0][2] * storage[1][3] * storage[2][1]
                       + storage[0][3] * storage[1][1] * storage[2][2]
                       - storage[0][3] * storage[1][2] * storage[2][1]
                       - storage[0][2] * storage[1][1] * storage[2][3]
                       - storage[0][1] * storage[1][3] * storage[2][2];
  result.storage[0][3] *= -1;
  
  result.storage[1][3] = storage[0][0] * storage[1][2] * storage[2][3]
                       + storage[0][2] * storage[1][3] * storage[2][0]
                       + storage[0][3] * storage[1][0] * storage[2][2]
                       - storage[0][3] * storage[1][2] * storage[2][0]
                       - storage[0][2] * storage[1][0] * storage[2][3]
                       - storage[0][0] * storage[1][3] * storage[2][2];
  
  result.storage[2][3] = storage[0][0] * storage[1][1] * storage[2][3]
                       + storage[0][1] * storage[1][3] * storage[2][0]
                       + storage[0][3] * storage[1][0] * storage[2][1]
                       - storage[0][3] * storage[1][1] * storage[2][0]
                       - storage[0][1] * storage[1][0] * storage[2][3]
                       - storage[0][0] * storage[1][3] * storage[2][1];
  result.storage[2][3] *= -1;
  
  result.storage[3][3] = storage[0][0] * storage[1][1] * storage[2][2]
                       + storage[0][1] * storage[1][2] * storage[2][0]
                       + storage[0][2] * storage[1][0] * storage[2][1]
                       - storage[0][2] * storage[1][1] * storage[2][0]
                       - storage[0][1] * storage[1][0] * storage[2][2]
                       - storage[0][0] * storage[1][2] * storage[2][1];
  
  for (auto& row: result.storage) {
    for (auto& elem: row) {
      elem /= det;
    }
  }

  return result;
}

float Matrix::determinant() {
  if (storage[0].size() != storage.size()) {
    throw std::invalid_argument{ "The matrix is not quadratic!" };
  }
  
  float determinant = 0;
  
  float firstRowFirstCol = storage[1][1] * storage[2][2] * storage[3][3]
                         + storage[1][2] * storage[2][3] * storage[3][1]
                         + storage[1][3] * storage[2][1] * storage[3][2]
                         - storage[1][3] * storage[2][2] * storage[3][1]
                         - storage[1][2] * storage[2][1] * storage[3][3]
                         - storage[1][1] * storage[2][3] * storage[3][2];
  
  firstRowFirstCol *= storage[0][0];
  
  float firstRowSecondCol = storage[1][0] * storage[2][2] * storage[3][3]
                          + storage[1][2] * storage[2][3] * storage[3][0]
                          + storage[1][3] * storage[2][0] * storage[3][2]
                          - storage[1][3] * storage[2][2] * storage[3][0]
                          - storage[1][2] * storage[2][0] * storage[3][3]
                          - storage[1][0] * storage[2][3] * storage[3][2];
  
  firstRowSecondCol *= storage[0][1];
  
  float firstRowThirdCol = storage[1][0] * storage[2][1] * storage[3][3]
                         + storage[1][1] * storage[2][3] * storage[3][0]
                         + storage[1][3] * storage[2][0] * storage[3][1]
                         - storage[1][3] * storage[2][1] * storage[3][0]
                         - storage[1][1] * storage[2][0] * storage[3][3]
                         - storage[1][0] * storage[2][3] * storage[3][1];
  
  firstRowThirdCol *= storage[0][2];
  
  float firstRowFourthCol = storage[1][0] * storage[2][1] * storage[3][2]
                          + storage[1][1] * storage[2][2] * storage[3][0]
                          + storage[1][2] * storage[2][0] * storage[3][1]
                          - storage[1][2] * storage[2][1] * storage[3][0]
                          - storage[1][1] * storage[2][0] * storage[3][2]
                          - storage[1][0] * storage[2][2] * storage[3][1];
  
  firstRowFourthCol *= storage[0][3];
  
  determinant = firstRowFirstCol - firstRowSecondCol + firstRowThirdCol - firstRowFourthCol;
  
  return determinant;
}

Matrix Matrix::operator*(const Matrix& rhs) {
  if (storage[0].size() != rhs.storage.size()) {
    throw std::invalid_argument{ "The number of cols in the first matrix doesn't match the rows in the second one!" };
  }
  
  int resultRows = (int) storage.size();
  int resultCols = (int) rhs.storage[0].size();
  
  Matrix result{ resultRows, resultCols };
  
  for (int row = 0; row < resultRows; row++) {
    for (int col = 0; col < resultCols; col++) {
      for (int i = 0; i < storage[0].size(); i++) {
        result.storage[row][col] += storage[row][i] * rhs.storage[i][col];
      }
    }
  }
  
  return result;
  
}
