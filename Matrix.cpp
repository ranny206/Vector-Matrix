#include "Base.h"
#include "Matrix.h"
#include "Vector.h"

using namespace mat_vec;



Matrix::Matrix(size_t size, double value) {
    if(size == 0){
        throw std::runtime_error("Size is 0");
    }
    rows = size;
    cols = size;
    matrix = new double*[rows];
    for(int i = 0; i < size; i++){
        matrix[i] = new double[cols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = value;
        }
    }
}

Matrix Matrix::eye(size_t size) {
    Matrix m(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j){
                m.matrix[i][j] = 1;
            }
            else{
                m.matrix[i][j] = 0;
            }
        }
    }
    return m;
}

Matrix::Matrix(size_t rows, size_t cols, double value) {
    if(cols == 0 || rows == 0){
        throw std::runtime_error("Size is 0");
    }
    this->rows = rows;
    this->cols = cols;
    matrix = new double *[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new double[cols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = value;
        }
    }
}

Matrix::Matrix(const mat_vec::Matrix &src) {
    rows = src.rows;
    cols = src.cols;
    matrix = new double*[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new double[cols];
    }
    for(int i = 0; i < rows; i++){
       for(int j = 0; j < cols; j++){
           matrix[i][j] = src.matrix[i][j];
       }
    }
}

Matrix& Matrix::operator=(const mat_vec::Matrix &rhs) {
    if(matrix != nullptr){
        this->~Matrix();
    }
    rows = rhs.rows;
    cols = rhs.cols;
    matrix = new double*[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new double[cols];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
    return *this;
}

Matrix::~Matrix() {
    if(matrix != nullptr){
        for(int i = 0; i < rows; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

Matrix Matrix::operator+(const mat_vec::Matrix &rhs) const {
    if(rows != rhs.rows && cols != rhs.cols){
        throw std::runtime_error("Wrong size");
    }
    Matrix m(rows, cols);
    for(int i = 0;  i < rows; i++){
         for(int j = 0; j < cols; j++){
             m.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
         }
    }
    return m;
}

Matrix& Matrix::operator+=(const mat_vec::Matrix &rhs) {
    if(rows != rhs.rows && cols != rhs.cols){
        throw std::runtime_error("Wrong size");
    }
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] += rhs.matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-(const mat_vec::Matrix &rhs) const {
    if(rows != rhs.rows && cols != rhs.cols){
        throw std::runtime_error("Wrong size");
    }
    Matrix m(rows, cols);
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            m.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
        }
    }
    return m;
}

Matrix& Matrix::operator-=(const mat_vec::Matrix &rhs) {
    if(rows != rhs.rows && cols != rhs.cols){
        throw std::runtime_error("Wrong size");
    }
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] -= rhs.matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(double k) const {
    Matrix m(rows, cols);
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            m.matrix[i][j] = matrix[i][j] * k;
        }
    }
    return m;
}

Matrix& Matrix::operator*=(double k) {
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] *= k;
        }
    }
    return *this;
}

Matrix Matrix::operator/(double k) const {
    if(k == 0){
        throw std::runtime_error("Division by 0");
    }
    Matrix m(rows, cols);
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            m.matrix[i][j] = matrix[i][j] / k;
        }
    }
    return m;
}

Matrix& Matrix::operator/=(double k) {
    for(int i = 0;  i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] /= k;
        }
    }
    return *this;
}

bool Matrix::operator==(const mat_vec::Matrix &rhs) const {
    if(cols != rhs.cols || rows != rhs.rows){
        return false;
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(matrix[i][j] != rhs.matrix[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const mat_vec::Matrix &rhs) const {
    return !(*this == rhs);
}

double Matrix::get(size_t row, size_t col) const {
    if(row >= rows || col >= cols){
        throw std::runtime_error("Out of range");
    }
    return matrix[row][col];
}

//double& Matrix::get_link(size_t row, size_t col) {
//    return matrix[row][col];
//}

std::pair<size_t, size_t> Matrix::shape() const {
    return std::make_pair(rows, cols);
}

Matrix Matrix::operator*(const mat_vec::Matrix &rhs) const {
    if(rows != rhs.cols && cols != rhs.rows){
        throw std::runtime_error("Wrong size");
    }
    Matrix m(rows, rhs.cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rhs.cols; j++){
            for(int k = 0; k < rows; k++){
                m.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }
    return m;
}

Matrix& Matrix::operator*=(const mat_vec::Matrix &rhs) {
    if(rows != rhs.cols && cols != rhs.rows){
        throw std::runtime_error("Wrong size");
    }
    Matrix m(rows, rhs.cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rhs.cols; j++){
            for(int k = 0; k < rows; k++){
                m.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }
    *this = m;
    return *this;
}

Vector Matrix::operator*(const mat_vec::Vector &vec) const {
    if(vec.size() != cols){
        throw std::runtime_error("Wrong size");
    }
    Vector vec1(rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0;  j < cols; j++){
            vec1[i] += matrix[i][j] * vec[j];
        }
    }
    return vec1;
}

void Matrix::reshape(size_t rows, size_t cols) {
     Matrix mat(rows, cols);
     double array[rows * cols];
     int k = 0;
     for(int i = 0; i < this->rows; i++){
         for(int j = 0; j < this->cols; j++){
             array[k] = matrix[i][j];
             k++;
         }
     }
     k = 0;
    for(int i = 0; i < mat.rows; i++){
        for(int j = 0; j < mat.cols; j++){
            mat.matrix[i][j] = array[k];
            k++;
        }
    }
    mat.rows = rows;
    mat.cols = cols;
    *this = mat;
}

Matrix Matrix::transposed() const {
    Matrix mat(cols, rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat.matrix[j][i] = matrix[i][j];
        }
    }
    return mat;
}

void Matrix::transpose() {
    Matrix mat(cols, rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mat.matrix[j][i] = matrix[i][j];
        }
    }
    *this = mat;
}

double Matrix::det() const {
    if(rows != cols){
        throw std::runtime_error("Det doesn`t exist");
    }
    double e = 1E-9;
    double det = 1;
    Matrix mat(*this);
    for(int i = 0; i < rows; i++){
        int k = i;
        for(int j = i + 1; j < rows; j++){
            if (abs (mat.matrix[j][i]) > abs (mat.matrix[k][i]))
                k = j;
            if (abs (mat.matrix[k][i]) < e) {
                det = 0;
                break;
            }
        }
        for(int l = 0; l < cols; l++){
            double buf = mat.matrix[i][l];
            mat.matrix[i][l] = matrix[k][l];
            mat.matrix[k][l] = buf;
        }
        if (i != k)
            det = -det;
        det *= mat.matrix[i][i];
        for (int j = i + 1; j < rows; j++){
            mat.matrix[i][j] /= mat.matrix[i][i];
        }
        for (int j = 0; j < rows; j++)
            if (j != i && abs (mat.matrix[j][i]) > e)
                for (int k = i + 1; k < rows; k++)
                    mat.matrix[j][k] -= mat.matrix[i][k] * mat.matrix[j][i];

    }
    return det;
}

Matrix Matrix::inv() const {
    double d = this->det();
    if(d == 0){
        throw std::runtime_error("Inverse matrix doesn`t exis");
    }
    d = 1 / d;
    Matrix mat(rows - 1, cols - 1, 0.0);
    Matrix T(rows, cols, 0.0);
    double array[(rows - 1) * (cols - 1)];
    int count = 0;

    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){

            for(int k = 0; k < rows; k++){
                for(int l = 0; l < cols; l++){
                    if(k != i && l != j){
                        array[count] = this->matrix[k][l];
                        count++;
                    }
                }
            }
            count = 0;
            for(int k = 0; k < rows - 1; k++) {
                for (int l = 0; l < cols - 1; l++) {
                    mat.matrix[k][l] = array[count];
                    count++;
                }
            }
            count = 0;
            double det = mat.det();
            if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)){
                T.matrix[i][j] = -det;
            }
            else{
                T.matrix[i][j] = det;
            }
        }
    }
    T.transpose();
    T *= d;
    return T;
}
