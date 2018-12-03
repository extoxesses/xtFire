#ifndef LIBDEF_H
#define LIBDEF_H

#include <iostream>

#ifdef _DEBUG
  #define LOGGER(...) std::cout << "[LOGGER] " << __VA_ARGS__ << std::endl;
#else
  #define LOGGER(...)
#endif


#if defined(_MSC_VER)
  #ifdef _DEBUG
    #ifdef xtFireHIDDriverd_EXPORTS
      #define EXPORT_API __declspec(dllexport)
    #else
      #define EXPORT_API __declspec(dllimport)
    #endif
  #else
    #ifdef xtFireHIDDriver_EXPORTS
      #define EXPORT_API __declspec(dllexport)
    #else
      #define EXPORT_API __declspec(dllimport)
    #endif
  #endif

  #define MANAGED public ref

#elif defined(__GNUC__)
  #define EXPORT_API __attribute__((visibility("default")))
  #define MANAGED
#endif

#endif // !LIBDEF_H
