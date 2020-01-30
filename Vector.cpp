#include <cmath>
#include "Base.h"
#include "Vector.h"
#include "Matrix.h"

using namespace mat_vec;

Vector::Vector(size_t size, double vec_value){
    if(size == 0){
        throw std::runtime_error("Size is 0");
    }
    vec_size = size;
    vec_coord = new double[vec_size];
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] = vec_value;
    }
}

Vector::Vector(const mat_vec::Vector &src){
    vec_size = src.vec_size;
    vec_coord = new double[vec_size];
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] = src.vec_coord[i];
    }
}

Vector& Vector::operator=(const mat_vec::Vector &rhs) {
    delete[]vec_coord;
    vec_size = rhs.vec_size;
    vec_coord = new double[vec_size];
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] = rhs.vec_coord[i];
    }
    return *this;
}

Vector::~Vector() {
    delete[]vec_coord;
}

size_t Vector::size() const {
    return vec_size;
}

double Vector::operator[](size_t n) const {
    if(n >= vec_size){
        throw std::runtime_error("Out of range");
    }
    return vec_coord[n];
}

double& Vector::operator[](size_t n) {
    if(n >= vec_size){
        throw std::runtime_error("Out of range");
    }
    return vec_coord[n];
}

double Vector::norm() const {
    double sum = 0;
    for(int i = 0; i < vec_size; i++){
        sum += vec_coord[i] * vec_coord[i];
    }
    double norm = sqrt(sum);
    return norm;
}

Vector Vector::normalized() const {
    Vector vec(vec_size);
    double tmp = norm();
    if(tmp == 0){
        throw std::runtime_error("Division by 0");
    }
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i]/tmp;
    }
    return vec;
}

void Vector::normalize() {
    double tmp = norm();
    if(tmp == 0){
        throw std::runtime_error("Division by 0");
    }
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] = vec_coord[i]/tmp;
    }
}

Vector Vector::operator+(const mat_vec::Vector &rhs) const {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    Vector vec(vec_size);
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i] + rhs.vec_coord[i];
    }
    return vec;
}

Vector& Vector::operator+=(const mat_vec::Vector &rhs) {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] += rhs.vec_coord[i];
    }
    return *this;
}

Vector Vector::operator-(const mat_vec::Vector &rhs) const {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    Vector vec(vec_size);
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i] - rhs.vec_coord[i];
}
    return vec;
}

Vector& Vector::operator-=(const mat_vec::Vector &rhs) {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] -= rhs.vec_coord[i];
    }
    return *this;
}

Vector Vector::operator^(const mat_vec::Vector &rhs) const {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    Vector vec(vec_size);
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i] * rhs.vec_coord[i];
    }
    return vec;
}

Vector& Vector::operator^=(const mat_vec::Vector &rhs) {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] *= rhs.vec_coord[i];
    }
    return *this;
}

double Vector::operator*(const mat_vec::Vector &rhs) const {
    if(vec_size != rhs.vec_size){
        throw std::runtime_error("Wrong size");
    }
    double result = 0;
    for(int i = 0; i < vec_size; i++){
        result += vec_coord[i] * rhs.vec_coord[i];
    }
    return result;
}

Vector Vector::operator*(double k) const {
    Vector vec(vec_size);
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i] * k;
    }
    return vec;
}

Vector& Vector::operator*=(double k) {
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] *= k;
    }
    return *this;
}

Vector Vector::operator/(double k) const {
    if(k == 0){
        throw std::runtime_error("Division by 0");
    }
    Vector vec(vec_size);
    for(int i = 0; i < vec_size; i++){
        vec.vec_coord[i] = vec_coord[i] / k;
    }
    return vec;
}

Vector& Vector::operator/=(double k) {
    for(int i = 0; i < vec_size; i++){
        vec_coord[i] /= k;
    }
    return *this;
}

bool Vector::operator==(const mat_vec::Vector &rhs) const {
    if(vec_size != rhs.vec_size){
        return false;
    }
    for(int i = 0; i < vec_size; i++){
        if(vec_coord[i] != rhs.vec_coord[i]){
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const mat_vec::Vector &rhs) const {
    return !((*this) == rhs);
}

Vector Vector::operator*(const mat_vec::Matrix &mat) const {
    if(vec_size != mat.shape().first){
        throw std::runtime_error("Wrong size");
    }
    Vector vec(mat.shape().second);
    for(int i = 0; i < mat.shape().second; i++){
        for(int j = 0;  j < mat.shape().first; j++){
            vec[i] += mat.get(j, i) * vec_coord[j];
        }
    }
    return vec;
}

Vector& Vector::operator*=(const mat_vec::Matrix &mat) {
    if(vec_size != mat.shape().first){
        throw std::runtime_error("Wrong size");
    }
    Vector vec(mat.shape().second);
    for(int i = 0; i < mat.shape().second; i++){
        for(int j = 0;  j < mat.shape().first; j++){
            vec[i] += mat.get(j, i) * vec_coord[j];
        }
    }
    *this = vec;
    return *this;
}

Vector mat_vec::operator*(double k, const Vector &v){
    return v * k;
}

