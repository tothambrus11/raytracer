#pragma once

#include "gmtl/Matrix.h"
#include "Vector3.h"

using namespace gmtl;

Matrix33d inverse(Matrix33d &m);

void printMatrix(Matrix33d &m);

Vector3 applyMatrix(Vector3 v, Matrix33d &matrix);
