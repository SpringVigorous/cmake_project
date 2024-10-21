#pragma once
#ifndef __TEST_EIGEN3_HM_VECTOR_H___
#define __TEST_EIGEN3_HM_VECTOR_H___
#include "test_eigen3/macro.h"

_TEST_EIGEN3_BEGIN_

#define AXIS_X hm_vector(1,0,0)
#define AXIS_Y hm_vector(0,1,0)
#define AXIS_Z hm_vector(0,0,1)

class TEST_EIGEN3_API hm_vector
{
public:
    hm_vector(double x = 0, double y = 0, double z = 0);
    hm_vector(const double* data, size_t count = 3);
    hm_vector(const hm_vector& other);
    hm_vector& operator=(const hm_vector& other);
    ~hm_vector() {}
public:
    void assign(const double* const data, size_t count = 3);
    void assign(double x_val = 0, double y_val = 0, double z_val = 0);
public:
    hm_vector& operator+=(const hm_vector& other);
    hm_vector& operator-=(const hm_vector& other);
    hm_vector& operator*=(double scalar);
    hm_vector& operator/=(double scalar);
public:
    hm_vector operator+(const hm_vector& other) const;
    hm_vector operator-(const hm_vector& other) const;
    hm_vector operator-() const;
    hm_vector operator*(double scalar) const;
    hm_vector operator/(double scalar) const;
public:
    hm_vector clone()const;
    hm_vector cross(const hm_vector& other) const;
    double dot(const hm_vector& other) const;

    double length()const;
    hm_vector& normalize_self();//单位化
    hm_vector normalize() const;//单位化
public:
    //返回：从 当前向量到 other向量的夹角
    //direct:为近似看的方向，
    double angle(const hm_vector& other,const hm_vector& direct= AXIS_Z) const;
public:
    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }

    void x(double val) { _x = val; }
    void y(double val) { _y = val; }
    void z(double val) { _z = val; }
public:
    double* raw_data() const { return const_cast<double*>(_data); }

protected:
    double& _x;
    double& _y;
    double& _z;
private:
    double _data[3] = {};
};

_TEST_EIGEN3_END_
#endif