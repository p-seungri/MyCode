#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

typedef struct _Labor
{
	string start;
	string end;

}Labor;


int main()
{
	int n;
	Labor* time = nullptr;	

	string* sHour = nullptr;
	string* sMinute = nullptr;
	string* eHour = nullptr;
	string* eMinute = nullptr;
	
	int sHours;
	int sMinutes;
	int eHours;
	int eMinutes;

	ios::sync_with_stdio(0);

	cin >> n;

	time = new Labor[n];
	sHour = new string[n];
	sMinute = new string[n];
	eHour = new string[n];
	eMinute = new string[n];

	for (int i = 0; i < n; i++)
	{
		cin >> time[i].start;
		cin >> time[i].end;
	}

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < 2; j++)
		{
			sHour[i].append(1, time[i].start[j]);
			sMinute[i].append(1, time[i].start[j + 3]);

			eHour[i].append(1, time[i].end[j]);
			eMinute[i].append(1, time[i].end[j + 3]);

		}

		sHours = stoi(sHour[i]);
		sMinutes = stoi(sMinute[i]);

		eHours = stoi(eHour[i]);
		eMinutes = stoi(eMinute[i]);

		cout << "Case #" << i + 1 << endl;

			
		if (eMinute < sMinute)
		{
			cout << setfill('0') << setw(2) << eHours - sHours - 1 << ":" << setfill('0') << setw(2) <<  60 - sMinutes + eMinutes << endl;
		}
		else
		{
			cout << setfill('0') << setw(2) << eHours - sHours << ":" << setfill('0') << setw(2) << eMinutes - sMinutes << endl;
		}

	}

	delete[] time;
	delete[] sHour;
	delete[] sMinute;
	delete[] eHour;
	delete[] eMinute;

	return 0;
}
