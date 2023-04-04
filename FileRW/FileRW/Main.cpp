#include <iostream>
#include <fstream>

int main()
{
	std::ofstream out("D:\\Downloads\\hello.txt", std::ios::app);
	if (out.is_open())
	{
		out << "Welcome to CPP" << std::endl;
	}
	out.close();


	return 0;
}