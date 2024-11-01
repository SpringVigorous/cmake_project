

#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/Splines>

int test_bcurve() {
    // 定义控制点
    Eigen::Matrix<double, 2, 5> controlPoints;
    controlPoints << 0, 1, 2, 3, 4,
                     0, 1, 2, 1, 0;

    // 创建样条曲线对象
    //Eigen::Spline<double, 2,3> spline(); // 3表示样条曲线的阶数
    //spline.setControlPoints(controlPoints);
    typedef Eigen::Spline<double, 2, 5> splineType;
    auto spline = Eigen::SplineFitting<splineType>::Interpolate(controlPoints, 2);

    // 计算样条曲线上特定位置的值
    double t = 0.0; // 参数值，范围通常是 [0, 1]
    while (t <= 1.0) {
        Eigen::Vector2d position = spline(t);
        std::cout << "t = " << t << ", position = (" << position[0] << ", " << position[1] << ")" << std::endl;
        t += 0.1; // 增量步长
    }

    return 0;
}