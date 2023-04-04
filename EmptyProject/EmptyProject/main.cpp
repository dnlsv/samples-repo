#include <iostream>
//#include "pch.h"
#include <Windows.h>

using namespace std;

typedef int (*function)(int a, int b);
typedef float (*function_f)(int a, int b);

int main()
{

	HMODULE hm = LoadLibrary(L"DynamicLib.dll");
	if (hm == nullptr)
	{
		printf("DynamicLib.dll not found!\n");
	}
	else
	{
		function add = (function)GetProcAddress(hm, "add");
		if (add == nullptr)
		{
			printf("DynamicLib.dll doesn't export add\n");
		}
		else
		{
			cout << "add: " << add(5, 8) << endl;
		}

		function diff = (function)GetProcAddress(hm, "diff");
		if (diff == nullptr)
		{
			printf("DynamicLib.dll doesn't export diff\n");
		}
		else
		{
			cout << "diff: " << diff(5, 8) << endl;
		}

		function mult = (function)GetProcAddress(hm, "mult");
		if (mult == nullptr)
		{
			printf("DynamicLib.dll doesn't export mult\n");
		}
		else
		{
			cout << "mult: " << mult(5, 8) << endl;
		}

		function_f dev = (function_f)GetProcAddress(hm, "dev");
		if (dev == nullptr)
		{
			printf("DynamicLib.dll doesn't export dev\n");
		}
		else
		{
			cout << "dev: " << dev(5, 8) << endl;
		}
	}

	return 0;
}