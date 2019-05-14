#pragma once

#ifdef PARSER_BUILD_DLL
	#define PARSER_API __declspec(dllexport)
#else
	#define PARSER_API __declspec(dllimport)
#endif
	