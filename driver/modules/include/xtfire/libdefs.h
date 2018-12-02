#ifndef LIBDEF_H
#define LIBDEF_H

#ifdef _DEBUG
  #define LOG(...) printf("%s", __VA_ARGS__)
#else
  #define LOG()
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
