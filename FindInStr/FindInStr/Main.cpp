#include <iostream>
#include <string>

using namespace std;

int main()
{
	string text;

	cout << "Entry text" << endl;
	getline(cin, text);

	int counter = 0;
	int max = 0;
	char symbol = ' ';
	for (int i = 0; i < text.size() - 1; i++)
	{
		if (text.at(i) == text.at(i + 1))
		{
			counter++;
			if (counter > max)
			{
				max = counter;
				symbol = text.at(i);
			}
		}
		else
		{
			counter = 0;
		}
	}

	if (max != 0)
	{
		max++;
		string str(max, symbol);
		cout << endl << "max line = " << str << endl
			<< "length = " << max << endl;
	}
	else
	{
		cout << endl << "not found!" << endl;
	}
	
}