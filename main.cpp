#define CATCH_CONFIG_MAIN
#include <iostream>
#include "Vector.h"
#include "catch.hpp"
#include "Matrix.h"


using namespace mat_vec;
using namespace std;

double e = 0.0000001;

TEST_CASE("vector constructors","[vector]") {
    Vector vec(6, 7);
    REQUIRE(vec.size() == 6);

    for(int i = 0; i < 3; i++){
        REQUIRE(vec[i] - 7 < e);
    }

    /*copy*/
    Vector v(vec);
    REQUIRE(vec.size() == v.size());

    for(int i = 0; i < 6; i++){
        REQUIRE(vec[i] - 7 < e);
    }

    vec[3] = 0;
    REQUIRE(v[3] == 7);
}

TEST_CASE("assignment", "[vector]"){
    Vector vec1(5, 10);
    Vector vec2(6, 8);

    vec1 = vec2;

    REQUIRE(vec1.size() == 6);

    for(int i = 0; i < 6; i++){
        REQUIRE(vec1[i] - 8 < e);
    }
}

TEST_CASE("size", "[vector]"){
    Vector vec(6, 0);
    REQUIRE(vec.size() == 6);
}

TEST_CASE("[]", "[vector]"){
    Vector vec1(5, 10);
    size_t n = 3;
    vec1[n] = 8;
    REQUIRE(vec1[n] - 8 < e);
}

TEST_CASE("norm", "[vector]"){
    Vector vec(4, 2);
    REQUIRE(vec.norm() - 16 < e);
}

TEST_CASE("normalized/normalise", "[vector]") {
    Vector vec1(4, 2);
    Vector vec2 = vec1.normalized();
    double result = 2/vec1.norm();

    for(int i = 0; i < 4; i++){
        REQUIRE(vec2[i] - result < e);
    }

    vec1.normalize();
    for(int i = 0; i < 4; i++){
        REQUIRE(vec1[i] - result < e);
    }
}

TEST_CASE("+, +=, -, -=, *, *=", "[vector]") {
    Vector vec1(3, 12);
    Vector vec2(3, 6);

    Vector result = vec1 + vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(result[i] - 18 < e);
    }

    result = vec1 - vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(result[i] - 6 < e);
    }

    result = vec1 ^ vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(result[i] - 72 < e);
    }

    vec1 += vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(vec1[i] - 18 < e);
    }

    vec1 -= vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(vec1[i] - 12 < e);
    }

    vec1 ^= vec2;
    for(int i = 0; i < 3; i++){
        REQUIRE(vec1[i] - 72 < e);
    }
}

TEST_CASE("Scalar multiplicity", "[vector]"){
    Vector vec1(3, 6);
    Vector vec2(3, 8);
    double result = vec1 * vec2;
    REQUIRE(result - 144 < e);
}

TEST_CASE("k multiplicity", "[vector]"){
    Vector vec(4, 3);
    double k = 6;
    Vector result = vec * k;
    for(int i = 0; i < 4; i++){
        REQUIRE(result[i] - 18 < e);
    }
    vec *= k;
    for(int i = 0; i < 4; i++){
        REQUIRE(vec[i] - 18 < e);
    }
    result = k * vec;
    for(int i = 0; i < 4; i++){
        REQUIRE(result[i] - 108 < e);
    }
}

TEST_CASE("k division", "[vector]"){
    Vector vec(4, 20);
    double k = 5;
    Vector result = vec / k;
    for(int i = 0; i < 4; i++){
        REQUIRE(result[i] - 4 < e);
    }
    vec /= k;
    for(int i = 0; i < 4; i++){
        REQUIRE(vec[i] - 4 < e);
    }
}

TEST_CASE("==, !=", "[vector]"){
    Vector vec1(3, 4);
    Vector vec2(3, 4);
    REQUIRE(vec1 == vec2);
    vec1[1] = 16;
    REQUIRE(vec1 != vec2);
    Vector vec3(4, 6);
    REQUIRE_FALSE(vec1 == vec3);
}


TEST_CASE("vector matrix", "[vector]"){
    Vector vec(4, 3);
    Matrix mat(4, 2, 7);
    Vector result = vec * mat;
    for(int i = 0; i < 2; i++){
        REQUIRE(result[i] - 84 < e);
    }
    vec *= mat;
    for(int i = 0; i < 2; i++){
        REQUIRE(vec[i] - 84 < e);
    }
}

TEST_CASE("matrix constructor", "[matrix]"){
    Matrix mat1(4, 3.0);
    REQUIRE(mat1.shape().first == 4);
    REQUIRE(mat1.shape().second == 4);
    for(int i = 0; i < 4; i++){
        for(int j  = 0; j < 4; j++){
            REQUIRE(mat1.get(i, j) - 3.0 < e);
        }
    }


    mat1 = Matrix::eye(4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j){
                REQUIRE(mat1.get(i, j) == 1);
            }
            else{
                REQUIRE(mat1.get(i, j) == 0);
            }
        }
    }

    Matrix mat2(4, 6, 3.0);
    REQUIRE(mat1.shape().first == 4);
    REQUIRE(mat1.shape().second == 4);
    for(int i = 0; i < 4; i++){
        for(int j  = 0; j < 6; j++){
            REQUIRE(mat2.get(i, j) - 3.0 < e);
        }
    }

    //copy
    Matrix mat3(mat2);
    REQUIRE(mat3.shape().first == 4);
    REQUIRE(mat3.shape().second == 6);
    for(int i = 0; i < 4; i++){
        for(int j  = 0; j < 6; j++){
            REQUIRE(mat3.get(i, j) - 3.0 < e);
        }
    }
}

TEST_CASE("=", "[matrix]"){
    Matrix mat1(4, 5, 3);
    Matrix mat2(6, 7, 4);
    mat1 = mat2;
    REQUIRE(mat1.shape().first == 6);
    REQUIRE(mat1.shape().second == 7);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            REQUIRE(mat1.get(i, j) - 4 < e);
        }
    }
}

TEST_CASE("+, +=, -, -=", "[matrix]"){
    Matrix mat1(4, 3, 5.0);
    Matrix mat2(4, 3, 7.0);

    Matrix result = mat1 + mat2;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(result.get(i, j) - 12 < e);
        }
    }

    result = mat2 - mat1;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(result.get(i, j) - 2 < e);
        }
    }

    mat1 += mat2;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(mat1.get(i, j) - 12 < e);
        }
    }
    mat1 -= mat2;
    for(int i = 0; i < 4; i++){
            for(int j = 0; j < 3; j++){
                REQUIRE(mat1.get(i, j) - 5 < e);
            }
    }
}

TEST_CASE("k multiplicity matrix", "[matrix]"){
    Matrix mat(4, 3, 6);
    double k = 4;
    Matrix result = mat * k;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(result.get(i, j) - 24 < e);
        }
    }
    mat *= k;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(mat.get(i, j) - 24 < e);
        }
    }
}

TEST_CASE("k division matrix", "[matrix]"){
    Matrix mat(4, 3, 6);
    double k = 3;
    Matrix result = mat / k;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(result.get(i, j) - 2 < e);
        }
    }
    mat /= k;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(mat.get(i, j) - 2 < e);
        }
    }
}

TEST_CASE("==, != matrix", "[matrix]"){
    Matrix mat1(3, 4, 7);
    Matrix mat2(3, 4, 7);
    REQUIRE(mat1 == mat2);
    Matrix mat3(3, 4, 8);
    REQUIRE_FALSE(mat1 == mat3);
    Matrix mat4(4, 4, 8);
    REQUIRE(mat1 != mat4);
}

TEST_CASE("get", "[matrix]"){
    Matrix mat(4, 3, 6);
    REQUIRE(mat.get(1, 1) - 6 < e);
}

TEST_CASE("size matrix", "[matrix]"){
    Matrix mat(4, 5, 8);
    pair<size_t, size_t> pr = mat.shape();
    REQUIRE(pr.first == 4);
    REQUIRE(pr.second == 5);
}

TEST_CASE("matrix multiplicity", "[matrix]"){
    Matrix mat1(3, 4, 7);
    Matrix mat2(4, 3, 2);
    Matrix result = mat1 * mat2;
    REQUIRE(result.shape().first == 3);
    REQUIRE(result.shape().second == 3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(result.get(i, j) - 56 < e);
        }
    }

    mat1 *= mat2;
    REQUIRE(mat1.shape().first == 3);
    REQUIRE(mat1.shape().second == 3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            REQUIRE(mat1.get(i, j) - 56 < e);
        }
    }
}

TEST_CASE("matrix vector", "[matrix]"){
    Matrix mat(3, 4, 3);
    Vector vec(4, 2);
    Vector result = mat * vec;
    for(int i = 0; i < 3; i++){
        REQUIRE(vec[i] - 24 < e);
    }
}

TEST_CASE("matrix reshape", "[matrix]"){
    Matrix mat(3, 4, 7);
    mat.reshape(4, 3);
    REQUIRE(mat.shape().first == 4);
    REQUIRE(mat.shape().second == 3);
}

TEST_CASE("transpose", "[matrix]"){
    Matrix mat = Matrix::eye(5);
    Matrix result = mat.transposed();
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(i == j){
                REQUIRE(result.get(i, j) == 1);
            }
            else{
                REQUIRE(result.get(i, j) == 0);
            }
        }
    }
    mat.transpose();
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(i == j){
                REQUIRE(mat.get(i, j) == 1);
            }
            else{
                REQUIRE(mat.get(i, j) == 0);
            }
        }
    }
}

TEST_CASE("det", "[matrix]"){
    Matrix mat(4, 6.0);
    double d = mat.det();
    REQUIRE(d - 0 < e);
    Matrix mat1(2, 0.0);
    mat1.test_func(mat1);
    d = mat1.det();
    REQUIRE(d + 2 < e);
}

TEST_CASE("inv", "[matrix]"){
    Matrix mat(2, 0.0);
    mat.test_func(mat);
    Matrix result = mat.inv();
    REQUIRE(result.get(0, 0) + 2 < e);
    REQUIRE(result.get(0, 1) - 1 < e);
    REQUIRE(result.get(1, 0) - 1.5 < e);
    REQUIRE(result.get(1, 1) + 0.5 < e);
}

//exception

TEST_CASE("size = 0 vector", "[vector]"){
    REQUIRE_THROWS(Vector {0, 3.0});
}

TEST_CASE("out of range", "[vector]"){
    Vector vec(3, 2.0);
    REQUIRE_THROWS(vec[4] = 4.0);
}

TEST_CASE("Division by 0, norm", "[vector]"){
    Vector vec(3, 0.0);
    REQUIRE_THROWS(vec.normalize());
}

TEST_CASE("Wrong size operations vector", "[vector]"){
    Vector vec1(3, 2.0);
    Vector vec2(5, 2.0);
    REQUIRE_THROWS(vec1 + vec2);
    REQUIRE_THROWS(vec1 += vec2);
    REQUIRE_THROWS(vec1 - vec2);
    REQUIRE_THROWS(vec1 -= vec2);
    REQUIRE_THROWS(vec1 ^ vec2);
    REQUIRE_THROWS(vec1 ^= vec2);
    REQUIRE_THROWS(vec1 * vec2);
}

TEST_CASE("k division by 0 vector", "[vector]") {
    Vector vec1(3, 2.0);
    double k = 0;
    REQUIRE_THROWS(vec1 / k);
}


TEST_CASE("Wrong size vector matrix multiplicity", "[vector]"){
    Vector vec(3, 2.0);
    Matrix mat(5, 3, 2.0);
    REQUIRE_THROWS(vec * mat);
    REQUIRE_THROWS(vec *= mat);
}

TEST_CASE("size = 0 matrix", "[matrix]"){
    REQUIRE_THROWS(Matrix {0, 3.0});
    REQUIRE_THROWS(Matrix {0, 1, 3.0});
    REQUIRE_THROWS(Matrix {1, 0, 3.0});
}


TEST_CASE("Wrong size operations matrix", "[matrix]"){
    Matrix mat1(3, 4, 5.0);
    Matrix mat2(2, 8, 6.0);
    REQUIRE_THROWS(mat1 + mat2);
    REQUIRE_THROWS(mat1 += mat2);
    REQUIRE_THROWS(mat1 - mat2);
    REQUIRE_THROWS(mat1 -= mat2);
}

TEST_CASE("k division by 0 matrix", "[matrix]") {
    Matrix mat(3, 4, 2.0);
    double k = 0;
    REQUIRE_THROWS(mat / k);
}

TEST_CASE("get ex", "[matrix]") {
    Matrix mat(3, 4, 2.0);
    REQUIRE_THROWS(mat.get(5, 6));
}

TEST_CASE("matrix multiplicity ex", "[matrix]") {
    Matrix mat1(3, 4, 5.0);
    Matrix mat2(3, 4, 5.0);
    REQUIRE_THROWS(mat1 * mat2);
    REQUIRE_THROWS(mat1 *= mat2);
}

TEST_CASE("Wrong size matrix vector multiplicity", "[matrix]"){
    Matrix mat(2, 3, 5.0);
    Vector vec(2, 4);
    REQUIRE_THROWS(mat * vec);
}

TEST_CASE("det ex", "[matrix]"){
    Matrix mat(3, 4, 6.0);
    REQUIRE_THROWS(mat.det());
}

TEST_CASE("inv ex", "[matrix]") {
    Matrix mat(3, 3, 6.0);
    REQUIRE_THROWS(mat.inv());
}



