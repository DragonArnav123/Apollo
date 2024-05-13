#pragma once

#if defined(APOLLO_CORE)
	#define APOLLO_API __declspec(dllexport)
#else
	#define APOLLO_API __declspec(dllimport)
#endif

#define AP_GLOBAL_VAR 		static
#define AP_LOCAL_PERSIST 	static
#define AP_INTERNAL_FUNC 	static

typedef unsigned char 			APu08;
typedef unsigned short 			APu16;
typedef unsigned int 			APu32;
typedef unsigned long 			APu64;
typedef unsigned long long 		APu128;

typedef 		 char 			APi08;
typedef 		 short 			APi16;
typedef 		 int 			APi32;
typedef 		 long 			APi64;
typedef 		 long long 		APi128;

typedef 		 float 			APf32;
typedef 		 double 		APf64;

typedef 		 char 			APbyte;
typedef unsigned char 			APubyte;

typedef 		 char *			APcstr;
typedef const 	 char * 		APccstr;

typedef unsigned int 			APsize;
