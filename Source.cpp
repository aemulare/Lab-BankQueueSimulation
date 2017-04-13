/***************************************************************************************************
									CSC 326 Information Structures
												Lab #4
										Queue - Banking Simulation
										  Student: Maria Romanova

***************************************************************************************************/


#include "Teller.h"
#include "Queue.h"
#include "Customer.h"
#include "CustomerStats.h"
#include <string> 
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

void displayHeader();
void tableHeaders();
int captureTime(char s[]);
string formatTime(const int& min_time);
string formatTime_overHour(int w_time);
void processCustomer(Teller& t, const Customer& front_customer, int i, CustomerStats& s, int start, int k);


int main()
{
	displayHeader();

	const int MAX_CUSTOMERS = 100000;
	const int MAX_SERVERS = 100;

	Queue<Customer> *q1 = new Queue<Customer>(MAX_CUSTOMERS);
	Teller t[MAX_SERVERS];
	CustomerStats stats;

	srand(time(nullptr));			// initialize random seed
	int numServer = 1;				// number of servers/tellers
	int i = 0;						// main loop counter
	int start;						// start bank's working hours in min
	int end;						// end bank's working hours in min
	int maxClock;					// length of simulation
	char startHours[10];			// start bank's working hours in hh:mm
	char endHours[10];				// end bank's working hours in hh:mm
	float distribution;				// frequency of customer arrivals
	float time_frame = 0.0;			// one customer arrive in min_frame minutes
	
	// User input ---------------------------------------------------------------------
	cout << "\n   Please, enter start time (in format hh:mm)   ";
		cin >> startHours;
		start = captureTime(startHours);

	cout << "\n   Please, enter end time (in format hh:mm)    ";
		cin >> endHours;
		end = captureTime(endHours);

	maxClock = end - start;

	cout << "\n   Number of servers/tellers: ";
		cin >> numServer;

	cout << "\n   On average, how often does one customer arrive (every X min)?  x = ";
		cin >> time_frame;
		distribution = 1.0 / time_frame;
	// end User input ------------------------------------------------------------------

	
	tableHeaders();
	

	// main loop --------------------------------------------------------------------------------------
	for (i = 0; i < maxClock; i++)
	{
		// calculating probability of a customer arrival
		float arrival = float(rand()) / float(RAND_MAX);
		if(arrival > 0 && arrival <= distribution)
		{
			Customer * x = new Customer (i);
			q1->enqueue(*x);
		}

		for (int k = 0; k < numServer; k++)
		{
			if (t[k].isAvailable() && !q1->IsEmpty())		// teller is free and queue is not empty
			{
				processCustomer(t[k], q1->Front(), i, stats, start, k);
				q1->dequeue();
			}

			else if (!t[k].isAvailable())
				t[k].decrementTimer();;
		}
	} // end main loop ----------------------------------------------------------------------------------


	cout << endl << setfill('-') << setw(90) << "-" << setfill(' ')
		<< "\n    Was there someone left in queue after working hours? "
		<< (q1->IsEmpty() ? "No" : "Yes")
		<< endl << setfill('-') << setw(90) << "-" << endl << setfill(' ');

	// customer service after working hours -----------------------------
	while(!q1->IsEmpty())
	{
		for (int k = 0; k < numServer; k++)
		{
			if (t[k].isAvailable() && !q1->IsEmpty())
			{
				processCustomer(t[k], q1->Front(), i, stats, start, k);
				stats.after_hrs_customerCounter++;
				q1->dequeue();
			}
			else t[k].decrementTimer();
		}
		i++;
	} // end customer service after working hours ------------------------

	cout << endl << setfill('_') << setw(90) << "_" << endl << setfill(' ');
	
	stats.printStatictics(maxClock, start, distribution, numServer);

	delete q1;
	// pause screen
	cout << "\n\t\t";
	system("pause");
	return 0;
}



void displayHeader()
{
	cout << endl << setfill('*') << setw(90) << "*" << "\n\n";
	cout << "\t\t This is a banking queue simulation\n\n";
	cout << setfill('*') << setw(90) << "*" << "\n\n\n";
}

void tableHeaders()
{
	cout << endl << setfill('_') << setw(90) << "_"
		<< endl << right << setfill(' ') 
		<< setw(4) << "#"
		<< setw(10) << "arrival"
		<< setw(10) << "teller#"
		<< setw(15) << "transaction"
		<< setw(17) << "waiting"
		<< setw(15) << "service"
		<< setw(15) << "departure\n"
	
		<< setw(13) << "time"
		<< setw(22) << "type"
		<< setw(21) << "duration"
		<< setw(15) << "duration"
		<< setw(12) << "time"
		<< endl << setfill('_') << setw(90) << "_" << endl << setfill(' ');
}


int captureTime(char s[])
{
	int h, m;
	sscanf(s, "%d:%d", &h, &m);
	int mins = h * 60 + m;

	return (mins);
}

string formatTime(const int& min_time)
{
	int hour1, min1;
	string hour, hour2, min, min2, time;
	hour1 = (min_time / 60) % 24;
	min1 = min_time % 60;
	
	if (hour1 < 10) hour2 = "0";
	hour = hour2 + to_string(hour1);

	if (min1 < 10) min2 = "0";
	min = min2 + to_string(min1);

	time = hour + ":" + min;

	return time;
}

string formatTime_overHour(int waitingTime)
{
	return (waitingTime < 60) ? to_string(waitingTime) : formatTime(waitingTime);
}


void processCustomer(Teller& t, const Customer& front_customer, int i, CustomerStats& s, int start, int k)
{
	t.addCustomer(front_customer, i);

	int arrivalTime = start + front_customer.getArrivalTime();
	int departureTime = start + i + front_customer.getServiceTime();
	int waitingTime = i - front_customer.getArrivalTime();
	int serviceTime = front_customer.getServiceTime();

	s.waitingTime_total += waitingTime;
	s.serviceTime_total += serviceTime;
	s.customerCounter++;
	s.lastDeparture = departureTime;

	// print customer results
	cout << right << setw(4) << s.customerCounter
		<< setw(9) << formatTime(arrivalTime)							// arrival time
		<< setw(7) << k + 1 << setw(8) << " "
		<< setw(15) << left << front_customer.getTransactionType() 		// transaction type
		<< setw(10) << right << formatTime_overHour(waitingTime)		// waiting time
		<< setw(15) << formatTime_overHour(serviceTime)					// service time
		<< setw(15) << formatTime(departureTime) << endl;				// departure time

	t.decrementTimer();
}






