#ifndef CALLME_API_H_INCLUDED
#define CALLME_API_H_INCLUDED

// 函数导出
#if !defined(CALLME_STATIC)
	#if defined(_WIN32) && (defined(_MSC_VER) || defined(__MINGW32__))
		#ifdef CALLME_EXPORT
			#define CALLME_API __declspec(dllexport)
		#else
			#define CALLME_API __declspec(dllimport)
		#endif
    #elif defined(_WIN32) && defined(__GNUC__)
        #ifdef CALLME_EXPORT
            #define CALLME_API __attribute__((__dllexport__))
        #else
            #define CALLME_API __attribute__((__dllimport__))
        #endif
    #elif defined(__GNUC__)
        #define CALLME_API __attribute__((__visibility__("default")))
	#endif
#else
    #define CALLME_API
#endif

// 变量导出
#if !defined(CALLME_VARAPI)
    #define CALLME_VARAPI extern CALLME_API
#endif

#endif
