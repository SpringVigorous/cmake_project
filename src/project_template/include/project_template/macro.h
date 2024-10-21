
#pragma once
#if _WIN32
#ifdef __PROJECT_TEMPLATE__
#define PROJECT_TEMPLATE_API __declspec(dllexport)
#else
#define PROJECT_TEMPLATE_API __declspec(dllimport)
#endif
#else
#define PROJECT_TEMPLATE_API
#endif

#define _PROJECT_TEMPLATE_BEGIN_ \
    namespace PROJECT_TEMPLATE   \
    {
#define _PROJECT_TEMPLATE_END_ }