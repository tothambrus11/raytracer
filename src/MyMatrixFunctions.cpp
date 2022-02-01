#include "MyMatrixFunctions.h"
#include "iostream"
#include "Vector3.h"

using namespace std;

Matrix33d inverse(Matrix33d &m) {
    double det = m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
                 m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
                 m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));

    if (det == 0) {
        std::cout << "Zero determinant";
    }

    double invdet = 1 / det;

    Matrix33d inverseMatrix; // inverse of matrix m
    inverseMatrix(0, 0) = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
    inverseMatrix(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
    inverseMatrix(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
    inverseMatrix(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
    inverseMatrix(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
    inverseMatrix(1, 2) = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
    inverseMatrix(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
    inverseMatrix(2, 1) = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
    inverseMatrix(2, 2) = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;

    return inverseMatrix;
}

void printMatrix(Matrix33d &m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << m(i, j) << "\t";
        }
        cout << endl;
    }
}


Vector3 applyMatrix(Vector3 v, Matrix33d &matrix) {
    return {
            matrix(0, 0) * v.x + matrix(1, 0) * v.y + matrix(2, 0) * v.z,
            matrix(0, 1) * v.x + matrix(1, 1) * v.y + matrix(2, 1) * v.z,
            matrix(0, 2) * v.x + matrix(1, 2) * v.y + matrix(2, 2) * v.z
    };
}
