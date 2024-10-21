#pragma once
#if _WIN32
    #ifdef   __KERNEL_SERIALIZE__
        #define  KERNEL_SERIALIZE_API  __declspec(dllexport)
    #else
        #define  KERNEL_SERIALIZE_API  __declspec(dllimport)
    #endif
#else
    #define KERNEL_SERIALIZE_API
#endif

#define _KERNEL_SERIALIZE_BEGIN_   namespace KERNEL_SERIALIZE{
#define _KERNEL_SERIALIZE_END_   }