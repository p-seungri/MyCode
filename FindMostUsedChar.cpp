#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>
using namespace std;

int main()
{
	string str;
	vector<int> cnt;
	vector<char> ar;
	int max, maxIndex;
	bool sameness = false;
	vector<char>::size_type i = 0, j = 0;

	cin >> str;

	for (i = 0; i < str.length(); i++)
	{
		str.at(i) = static_cast<char>(toupper(str.at(i)));
	}

	for (i = 0; i < str.length(); i++)
	{
		int flag = 1;

		for (j = 0; j < ar.size(); j++)
		{
			if (ar.at(j) == str.at(i))
			{
				flag = 0;
				break;
			}
		}

		if (flag)	
		{
			ar.push_back(str.at(i));
		}

	}

	cnt.resize(ar.size(), 0);

	for (i = 0; i < ar.size(); i++)
	{

		for (j = 0; j < str.length(); j++)
		{
			if (str.at(j) == ar.at(i))
			{
				cnt.at(i)++;
			}
		}
	}

	max = cnt.at(0);
	maxIndex = 0;

	for (i = 1; i < cnt.size(); i++)
	{
		if (max < cnt.at(i))
		{
			max = cnt.at(i);
			maxIndex = i;
		}
		else if (max == cnt.at(i))
		{
			sameness = true;
			break;
		}
	}


	if (sameness)
	{
		cout << "?" << endl;
	}
	else
	{
		cout <<ar.at(maxIndex) << endl;
	}


	return 0;
}
