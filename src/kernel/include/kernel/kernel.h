#pragma once
#if _WIN32
#ifdef __KERNEL__
#define KERNEL_API __declspec(dllexport)
#else
#define KERNEL_API __declspec(dllimport)
#endif
#else
#define KERNEL_API
#endif

#define _KERNEL_BEGIN_ \
    namespace KERNEL   \
    {
#define _KERNEL_END_ }