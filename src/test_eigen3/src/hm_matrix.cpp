#include <memory>
#include <algorithm>
#include <memory>
#include <xutility>
#include <stdexcept>
#include "test_eigen3/hm_matrix.h"
#include <Eigen/Eigen>

_TEST_EIGEN3_BEGIN_
typedef Eigen::Matrix4d MtxType;
typedef Eigen::Map<MtxType> MapMtxType;
typedef Eigen::Map<const MtxType> MapVMtxTypeConst;

// 构造函数
hm_matrix::hm_matrix(double m00, double m01, double m02, double m03,
    double m10, double m11, double m12, double m13,
    double m20, double m21, double m22, double m23,
    double m30, double m31, double m32, double m33) :
    _m00(_data[0][0]), _m01(_data[0][1]), _m02(_data[0][2]), _m03(_data[0][3]),
    _m10(_data[1][0]), _m11(_data[1][1]), _m12(_data[1][2]), _m13(_data[1][3]),
    _m20(_data[2][0]), _m21(_data[2][1]), _m22(_data[2][2]), _m23(_data[2][3]),
    _m30(_data[3][0]), _m31(_data[3][1]), _m32(_data[3][2]), _m33(_data[3][3]) {

    assign(m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33);

}

// 构造函数（从数组初始化）
hm_matrix::hm_matrix(const double* data, size_t size) :hm_matrix() {

    assign(data, size);

}

// 拷贝构造函数
hm_matrix::hm_matrix(const hm_matrix& other) :hm_matrix() {
    assign(other.raw_data());
}

// 拷贝赋值运算符
hm_matrix& hm_matrix::operator=(const hm_matrix& other) {
    if (this != &other) {
        assign(other.raw_data());
    }
    return *this;
}

// 析构函数
hm_matrix::~hm_matrix() {
    // 如果需要释放资源，可以在这里处理
}

hm_matrix hm_matrix::Zero()
{
    return hm_matrix();
}

hm_matrix hm_matrix::Identify()
{
    auto val=MtxType::Identity().eval();

    return hm_matrix(val.data());
}

void hm_matrix::assign(double m00, double m01, double m02, double m03,
    double m10, double m11, double m12, double m13,
    double m20, double m21, double m22, double m23,
    double m30, double m31, double m32, double m33)
{
    _m00 = m00; _m01 = m01; _m02 = m02; _m03 = m03;
    _m10 = m10; _m11 = m11; _m12 = m12; _m13 = m13;
    _m20 = m20; _m21 = m21; _m22 = m22; _m23 = m23;
    _m30 = m30; _m31 = m31; _m32 = m32; _m33 = m33;
}
void hm_matrix::assign(const double* data, size_t size)
{
    if (data && size > 0) {
        std::copy(data, data+std::min<size_t>(size, 16), (double* )_data);
    }
}


// 下标运算符重载
double& hm_matrix::operator()(int i, int j) {
    if (i < 0 || i > 3 || j < 0 || j > 3) {
        throw std::out_of_range("Index out of range");
    }
    return _data[i][j];
}

// 常量下标运算符重载
const double& hm_matrix::operator()(int i, int j) const {
    if (i < 0 || i > 3 || j < 0 || j > 3) {
        throw std::out_of_range("Index out of range");
    }
    return _data[i][j];
}


_TEST_EIGEN3_END_