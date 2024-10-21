#include "test_eigen3/hm_vector.h"
#include <Eigen/Eigen>
#include <math.h>
#include <algorithm>
#include <memory>
#include <xutility>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
_TEST_EIGEN3_BEGIN_
typedef Eigen::Map<Eigen::Vector3d> MapVecType;
typedef Eigen::Map<const Eigen::Vector3d> MapVecTypeConst;
hm_vector::hm_vector(double x_val, double y_val, double z_val) :_x(_data[0]), _y(_data[1]), _z(_data[2]) {
    assign(x_val, y_val, z_val);
};
void hm_vector::assign(double x_val, double y_val, double z_val)
{
    x(x_val);
    y(y_val);
    z(z_val);
}
void hm_vector::assign(const double* const data, size_t count)
{
    if (data && count >= 0) {
        std::copy(data, data + std::min<size_t>(3, count), this->_data);
    }
}
hm_vector::hm_vector(const double* data, size_t count) :hm_vector() {
    assign(data, count);
}
hm_vector::hm_vector(const hm_vector& other) :hm_vector()
{
    assign(other.raw_data(), 3);
}
hm_vector& hm_vector::operator=(const hm_vector& other)
{
    assign(other.raw_data(), 3);
    return *this;
}
hm_vector& hm_vector::operator+=(const hm_vector& other)
{
    MapVecType v1(this->raw_data());
    MapVecTypeConst v2(other.raw_data());
    v1 += v2;
    return *this;
}
hm_vector& hm_vector::operator-=(const hm_vector& other)
{
    return this->operator+=(-other);
}
hm_vector& hm_vector::operator*=(double scalar)
{
    MapVecType v1(this->_data);
    v1 *= scalar;
    return *this;
}
hm_vector hm_vector::operator-() const
{
    return this->operator*(-1);
}
hm_vector& hm_vector::operator/=(double scalar)
{
    return this->operator*=(1.0 / scalar);
}
hm_vector  hm_vector::operator + (const hm_vector& other) const
{
    return hm_vector(*this) += (other);
}
hm_vector  hm_vector::operator - (const hm_vector& other) const
{
    return hm_vector(*this) -= (other);
}
hm_vector  hm_vector::operator* (double scalar) const
{
    return hm_vector(*this) *= scalar;
}
hm_vector  hm_vector::operator / (double scalar) const
{
    return hm_vector(*this) /= scalar;
}
hm_vector hm_vector::clone() const
{
    return hm_vector(raw_data());
}
hm_vector hm_vector::cross(const hm_vector& other) const
{
    MapVecTypeConst v1(raw_data());
    MapVecTypeConst v2(other.raw_data());
    return hm_vector(v1.cross(v2).data());
}
double hm_vector::dot(const hm_vector& other) const
{
    MapVecTypeConst v1(raw_data());
    MapVecTypeConst v2(other.raw_data());
    return v1.dot(v2);
}
double hm_vector::length() const
{
    MapVecTypeConst v1(raw_data());
    return v1.norm();
}
hm_vector& hm_vector::normalize_self()
{
    MapVecType v1(raw_data());
    auto v2 = v1.normalized();
    assign(v2.data());
    return *this;
}
hm_vector hm_vector::normalize() const
{
    return clone().normalize_self();
}
double hm_vector::angle(const hm_vector& other, const hm_vector& direct) const
{
    MapVecTypeConst v1(normalize().raw_data());
    MapVecTypeConst v2(other.normalize().raw_data());
    MapVecTypeConst v3(direct.normalize().raw_data());
    auto cross_val = v1.cross(v2);
    double len = cross_val.norm();
    if (cross_val.dot(v3) < -1e-6)
        len *= -1;


    double angle = std::atan2(
        len,
        v1.dot(v2)
    );
    return angle;
}
_TEST_EIGEN3_END_
