#pragma once
#ifndef __TEST_EIGEN3_HM_MATRIX_H___
#define __TEST_EIGEN3_HM_MATRIX_H___
#include "test_eigen3/macro.h"

_TEST_EIGEN3_BEGIN_

class TEST_EIGEN3_API hm_matrix
{
public:

    hm_matrix(double m00 = 0, double m01 = 0, double m02 = 0, double m03 = 0,
        double m10 = 0, double m11 = 0, double m12 = 0, double m13 = 0,
        double m20 = 0, double m21 = 0, double m22 = 0, double m23 = 0,
        double m30 = 0, double m31 = 0, double m32 = 0, double m33 = 0);
    hm_matrix(const double* data, size_t size = 16);
    hm_matrix(const hm_matrix& other);
    hm_matrix& operator=(const hm_matrix& other);
    ~hm_matrix();
public:
    static hm_matrix Zero();
    static hm_matrix Identify();
public:
    void assign(double m00 = 0, double m01 = 0, double m02 = 0, double m03 = 0,
        double m10 = 0, double m11 = 0, double m12 = 0, double m13 = 0,
        double m20 = 0, double m21 = 0, double m22 = 0, double m23 = 0,
        double m30 = 0, double m31 = 0, double m32 = 0, double m33 = 0);
    void assign(const double* data, size_t size = 16);

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

public:
    double* raw_data() const { return const_cast<double*>((const double*)_data); }

protected:
    double& _m00;
    double& _m01;
    double& _m02;
    double& _m03;
    double& _m10;
    double& _m11;
    double& _m12;
    double& _m13;
    double& _m20;
    double& _m21;
    double& _m22;
    double& _m23;
    double& _m30;
    double& _m31;
    double& _m32;
    double& _m33;
private:
    double _data[4][4]{};
};

_TEST_EIGEN3_END_
#endif