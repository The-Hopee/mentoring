#pragma once

#if defined (_WIN32)
    #define SUM_DLL_API __declspec(dllexport)
#else
    #define SUM_DLL_API
#endif

namespace lib
{
    SUM_DLL_API int sum(int a,int b);
    SUM_DLL_API double sum(double a,double b);
} // namespace lib