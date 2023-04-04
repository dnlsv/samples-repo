#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct Arguments
{
	string KOP;
	string KSO;
	string IP;
	vector<string> kods;

	void printArg()
	{
		cout << "KOP = " << KOP << endl;
		cout << "KSO = " << KSO << endl;
		cout << "IP = " << IP << endl;
		for (unsigned int i = 0; i < kods.size(); i++)
		{
			cout << "KOD" << i + 1 << " = " << kods.at(i) << endl;
		}
	}

	void clear()
	{
		KOP = "";
		KSO = "";
		IP = "";
		kods.clear();
	}
};

int main(int argc, char* argv[])
{
	string arg = string(argv[1]);

	ofstream outlog("Log.txt");

	Arguments arguments;

	int i = 0;
	bool flag = true;
	i = arg.find("(:");
	if (i != -1)
	{
		arg = arg.substr(i);
	}
	else
	{
		outlog << "Incorrect format!" << endl;
		flag = false;
	}

	if (flag)
	{
		i = arg.find(":)");
		if (i != -1)
		{
			arg = arg.substr(0, i + 2);
		}
		else
		{
			outlog << "Incorrect format!" << endl;
			flag = false;
		}
	}

	if (flag)
	{
		if (arg.at(0) == '(' && arg.at(1) == ':' &&
			arg.at(arg.length() - 1) == ')' && arg.at(arg.length() - 2) == ':')
		{
			flag = true;
		}
		else
		{
			outlog << "Incorrect format!" << endl;
			flag = false;
		}
	}

	if (flag)
	{
		i = 2;
		while (arg.at(i) != ' ')
		{
			arguments.KOP += arg.at(i);
			i++;
		}
		if (arguments.KOP.length() < 3 || arguments.KOP.length() > 6)
		{
			outlog << "KOP is invalid!" << endl;
			flag = false;
		}
	}

	if (flag)
	{
		i += 1;
		while (arg.at(i) != ' ')
		{
			arguments.KSO += arg.at(i);
			i++;
		}
		if (arguments.KSO.length() != 6)
		{
			outlog << "KSO is invalid!" << endl;
			flag = false;
		}
	}

	if (flag)
	{
		i += 1;
		while (arg.at(i) != ':')
		{
			arguments.IP += arg.at(i);
			i++;
		}
		if (arguments.IP.length() < 5 || arguments.IP.length() > 6)
		{
			outlog << "IP is invalid!" << endl;
			flag = false;
		}
	}

	if (flag)
	{
		int j = 0;
		i++;
		while (arg.at(i) != ':')
		{
			arguments.kods.push_back("");
			while (arg.at(i) != ',')
			{
				arguments.kods.at(j) += arg.at(i);
				i++;
				if (arg.at(i) == ':')
				{
					i--;
					break;
				}
			}
			if (arguments.kods.at(j).length() != 3)
			{
				outlog << "KOD is invalid!" << endl;
				flag = false;
				break;
			}
			j++;
			i++;
		}
	}

	if (flag)
	{
		arguments.printArg();
	}
	else
	{
		arguments.clear();
		cout << "Error!";
	}

	/*
	if (arg.at(0) != '(' && arg.at(1) != ':' &&
		arg.at(arg.length() - 1) != ')' && arg.at(arg.length() - 2) != ':')
	{
		outlog << "Incorrect format!" << endl;
	}
	else
	{
		int i = 2;
		while (arg.at(i) != ' ')
		{
			arguments.KOP += arg.at(i);
			i++;
		}
		if (arguments.KOP.length() < 3 || arguments.KOP.length() > 6)
		{
			outlog << "KOP is invalid!" << endl;
		}
		else
		{
			i += 1;
			while (arg.at(i) != ' ')
			{
				arguments.KSO += arg.at(i);
				i++;
			}
			if (arguments.KSO.length() != 6)
			{
				outlog << "KSO is invalid!" << endl;
			}
			else
			{
				i += 1;
				while (arg.at(i) != ':')
				{
					arguments.IP += arg.at(i);
					i++;
				}
				if (arguments.IP.length() < 5 || arguments.IP.length() > 6)
				{
					outlog << "IP is invalid!" << endl;
				}
				else
				{
					if (arg.at(i) != ':')
					{
						outlog << "Incorrect format!" << endl;
					}
					else
					{
						int j = 0;
						i += 1;
						while (arg.at(i) != ':')
						{
							arguments.kods.push_back("");
							while (arg.at(i) != ',')
							{
								if (arg.at(i) == ':')
								{
									i--;
									break;
								}
								arguments.kods.at(j) += arg.at(i);
								i++;
							}
							j++;
							i++;
							if (arguments.kods.at(j - 1).length() != 3)
							{
								outlog << "KOD is invalid!" << endl;
								break;
							}
						}
					}
				}
			}
		}
	}

	arguments.printArg();
	*/

	outlog.close();
}