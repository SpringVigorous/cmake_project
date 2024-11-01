#include <Eigen/Dense>
#include <vector>




inline Eigen::MatrixXd basisFunctions(int degree, const std::vector<double>& knots, double t) {
    int n = knots.size() - degree - 2;
    Eigen::MatrixXd N(n + 1, degree + 1);
    for (int i = 0; i <= n; ++i) {
        if (knots[i] <= t && t < knots[i + 1]) {
            N(i, 0) = 1.0;
        } else {
            N(i, 0) = 0.0;
        }
    }

    for (int j = 1; j <= degree; ++j) {
        for (int i = 0; i <= n - j; ++i) {
            double left = (t - knots[i]) / (knots[i + j] - knots[i]);
            double right = (knots[i + j + 1] - t) / (knots[i + j + 1] - knots[i + 1]);
            N(i, j) = left * N(i, j - 1) + right * N(i + 1, j - 1);
        }
    }

    return N;
}

inline Eigen::VectorXd evaluateBSpline(const Eigen::MatrixXd& controlPoints, const std::vector<double>& knots, int degree, double t) {
    Eigen::MatrixXd N = basisFunctions(degree, knots, t);
    Eigen::VectorXd point(2);
    for (int i = 0; i < 2; ++i) {
        point(i) = N.row(0).dot(controlPoints.row(i));
    }
    return point;
}

int test_bcurve();