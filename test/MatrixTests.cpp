//
//  MatrixTests.cpp
//  HermiteBezier
//
//  Created by Simkó Viktor on 2016. 11. 30..
//  Copyright © 2016. Simkó Viktor. All rights reserved.
//

#include "third_party/catch.hpp"
#include "../src/Matrix.hpp"

class MatrixTests {
protected:
    Matrix matrix;

public:
    MatrixTests() : matrix{ 4, 4 } { }
};

TEST_CASE_METHOD(MatrixTests, "We can get the determinant of a 4*4 matrix", "[Matrix::determinant]") {
  matrix.storage[0][0] = 2;
  matrix.storage[0][1] = 6;
  matrix.storage[0][2] = 6;
  matrix.storage[0][3] = 2;
  
  matrix.storage[1][0] = 2;
  matrix.storage[1][1] = 7;
  matrix.storage[1][2] = 3;
  matrix.storage[1][3] = 6;
  
  matrix.storage[2][0] = 1;
  matrix.storage[2][1] = 5;
  matrix.storage[2][2] = 0;
  matrix.storage[2][3] = 1;
  
  matrix.storage[3][0] = 3;
  matrix.storage[3][1] = 7;
  matrix.storage[3][2] = 0;
  matrix.storage[3][3] = 7;
  
  REQUIRE(matrix.determinant() == -168);
}

TEST_CASE_METHOD(MatrixTests, "We can get the inverse of a 4*4 matrix", "[Matrix::inverse]") {
  matrix.storage[0][0] = 2;
  matrix.storage[0][1] = 6;
  matrix.storage[0][2] = 6;
  matrix.storage[0][3] = 2;
  
  matrix.storage[1][0] = 2;
  matrix.storage[1][1] = 7;
  matrix.storage[1][2] = 3;
  matrix.storage[1][3] = 6;
  
  matrix.storage[2][0] = 1;
  matrix.storage[2][1] = 5;
  matrix.storage[2][2] = 0;
  matrix.storage[2][3] = 1;
  
  matrix.storage[3][0] = 3;
  matrix.storage[3][1] = 7;
  matrix.storage[3][2] = 0;
  matrix.storage[3][3] = 7;
  
  Matrix inverse = matrix.inverse();
  
  CHECK(inverse.storage[0][0] == Approx(1.0 / 2.0));
  CHECK(inverse.storage[0][1] == Approx(-1.0));
  CHECK(inverse.storage[0][2] == Approx(-1.0 / 4.0));
  CHECK(inverse.storage[0][3] == Approx(3.0 / 4.0));
  
  CHECK(inverse.storage[1][0] == Approx(-1.0 / 14.0));
  CHECK(inverse.storage[1][1] == Approx(1.0 / 7.0));
  CHECK(inverse.storage[1][2] == Approx(2.0 / 7.0));
  CHECK(inverse.storage[1][3] == Approx(-1.0 / 7.0));
  
  CHECK(inverse.storage[2][0] == Approx(5.0 / 42.0));
  CHECK(inverse.storage[2][1] == Approx(2.0 / 21.0));
  CHECK(inverse.storage[2][2] == Approx(-1.0 / 7.0));
  CHECK(inverse.storage[2][3] == Approx(-2.0 / 21.0));
  
  CHECK(inverse.storage[3][0] == Approx(-1.0 / 7.0));
  CHECK(inverse.storage[3][1] == Approx(2.0 / 7.0));
  CHECK(inverse.storage[3][2] == Approx(-5.0 / 28.0));
  CHECK(inverse.storage[3][3] == Approx(-1.0 / 28.0));
}

TEST_CASE_METHOD(MatrixTests, "We can multiply two matrices", "[Matrix::operator*]") {
  Matrix matrixA{ 4, 4 };

  matrixA.storage[0][0] = 2;
  matrixA.storage[0][1] = 6;
  matrixA.storage[0][2] = 6;
  matrixA.storage[0][3] = 2;
  
  matrixA.storage[1][0] = 2;
  matrixA.storage[1][1] = 7;
  matrixA.storage[1][2] = 3;
  matrixA.storage[1][3] = 6;
  
  matrixA.storage[2][0] = 1;
  matrixA.storage[2][1] = 5;
  matrixA.storage[2][2] = 0;
  matrixA.storage[2][3] = 1;
  
  matrixA.storage[3][0] = 3;
  matrixA.storage[3][1] = 7;
  matrixA.storage[3][2] = 0;
  matrixA.storage[3][3] = 7;
  
  Matrix matrixB{ 2, 4 };
  matrixB.storage[0][0] = 3;
  matrixB.storage[0][1] = 1;
  matrixB.storage[0][2] = 4;
  matrixB.storage[0][3] = 4;
  
  matrixB.storage[1][0] = 9;
  matrixB.storage[1][1] = 2;
  matrixB.storage[1][2] = 5;
  matrixB.storage[1][3] = 3;
  
  Matrix result = matrixB * matrixA;
  
  CHECK(result.storage[0][0] == 24);
  CHECK(result.storage[0][1] == 73);
  CHECK(result.storage[0][2] == 21);
  CHECK(result.storage[0][3] == 44);
  
  CHECK(result.storage[1][0] == 36);
  CHECK(result.storage[1][1] == 114);
  CHECK(result.storage[1][2] == 60);
  CHECK(result.storage[1][3] == 56);
}
