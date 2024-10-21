#include "test_eigen3/project.h"
#include "test_eigen3/hm_vector.h"
#include "test_eigen3/hm_matrix.h"
using namespace TEST_EIGEN3;
void test_vector()
{
    hm_vector v1(1, 2, 0);
    hm_vector v2(-4, 5, 0);
    hm_vector v3 = v1.cross(v2);
    auto v4 = v1.dot(v2);

    v3.normalize_self();
    auto len = v3.length();

    hm_vector z_axis(3, 5, -10);
    auto angle = v1.angle(v2, z_axis);
    auto angle1 = v2.angle(v1, z_axis);
}


int main()
{
    
  auto mtx1=  hm_matrix::Identify();



    return 0;
}


