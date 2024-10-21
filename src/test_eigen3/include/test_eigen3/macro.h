
#pragma once
#if _WIN32
#ifdef __TEST_EIGEN3__
#define TEST_EIGEN3_API __declspec(dllexport)
#else
#define TEST_EIGEN3_API __declspec(dllimport)
#endif
#else
#define TEST_EIGEN3_API
#endif

#define _TEST_EIGEN3_BEGIN_ \
    namespace TEST_EIGEN3   \
    {
#define _TEST_EIGEN3_END_ }