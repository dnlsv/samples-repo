#pragma once

#ifdef DYNAMICDLL_EXPORTS
#define DYNAMICDLL_API __declspec(dllexport)
#else
#define DYNAMICDLL_API __declspec(dllimport)
#endif

extern "C" int DYNAMICDLL_API add(int a, int b);
extern "C" int DYNAMICDLL_API diff(int a, int b);
extern "C" int DYNAMICDLL_API mult(int a, int b);
extern "C" float DYNAMICDLL_API dev(int a, int b);

