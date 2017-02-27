//
//  Matrix.hpp
//  HermiteBezier
//
//  Created by Simkó Viktor on 2016. 11. 30..
//  Copyright © 2016. Simkó Viktor. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <vector>
#include <exception>

struct Matrix {
  
  std::vector< std::vector<float> > storage;
  
  Matrix(int rows, int cols);
  Matrix inverse();
  float determinant();
  Matrix operator*(const Matrix& rhs);
  Matrix transposed();
  
};

#endif /* Matrix_hpp */
