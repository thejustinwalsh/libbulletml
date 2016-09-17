#ifndef bulletmlcommon_h_
#define bulletmlcommon_h_

#if defined(_MSC_VER) && defined(BULLETML_SHARED_LIB)
	#if defined(WIN32_DLL_EXPORT)
		#define BULLETML_API __declspec(dllexport)
	#else
		#define BULLETML_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__) && defined(BULLETML_SHARED_LIB)
    #define BULLETML_API __attribute__((visibility("default")))
#else
    #define BULLETML_API
#endif

#endif // ! bulletmlcommon_h_
