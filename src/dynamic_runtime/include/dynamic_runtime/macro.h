
#pragma once
#if _WIN32
#ifdef __DYNAMIC_RUNTIME__
#define DYNAMIC_RUNTIME_API __declspec(dllexport)
#else
#define DYNAMIC_RUNTIME_API __declspec(dllimport)
#endif
#else
#define DYNAMIC_RUNTIME_API
#endif

#define _DYNAMIC_RUNTIME_BEGIN_ \
    namespace DYNAMIC_RUNTIME   \
    {
#define _DYNAMIC_RUNTIME_END_ }