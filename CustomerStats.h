#pragma once
#include <iostream>
#include <iomanip>
#include <string>

struct CustomerStats
{
	int waitingTime_total = 0;
	int serviceTime_total = 0;
	int lastDeparture = 0;
	int customerCounter = 0;
	int after_hrs_customerCounter = 0;


	double waitingAvearage() const { return static_cast<double> (waitingTime_total) / customerCounter; }

	double serviceAvearage() const { return static_cast<double> (serviceTime_total) / customerCounter; }
	
	string hours(int x) const { return to_string(x / 60) + " hours "; }
	
	string min(int x) const { return to_string(x % 60) + " min "; }
	

	void printStatictics(int maxClock, int start, float dist, int server) const
	{
		int overtime = (lastDeparture - start - maxClock < 0) ? 0 : (lastDeparture - start - maxClock);

		cout << left;

		cout << setw(40) << fixed << setprecision(3) << "\n   Time distribution" << dist << endl;
		cout << setw(40) << "\n   Length of simulation" << maxClock << " min" << endl;
		cout << setw(40) << "\n   Number of servers/tellers" << server << endl;

		cout << setw(40) << "\n   Scheduled work duration" << hours(maxClock) << min(maxClock) << endl;
		cout << setw(40) << "\n   Real work duration" << hours(lastDeparture - start) << min(lastDeparture - start) << endl;
		cout << setw(40) << "\n   Overtime work" << hours(overtime) << min(overtime) << endl;

		cout << setw(40) << "\n   Total served" << customerCounter << " customers" << endl;
		cout << setw(40) << "\n   Were in queue after working hours" << after_hrs_customerCounter << " customers" << endl;
		
		cout << setw(40) << fixed << setprecision(2);
		cout << setw(40) << "\n   Average waiting duration" << waitingAvearage() << " min\n";
		cout << setw(40) << "\n   Average service duration" << serviceAvearage() << " min\n\n";
	}
};
