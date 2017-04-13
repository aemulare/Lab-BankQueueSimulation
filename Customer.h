#pragma once
#include <iostream>
using namespace std;

class Customer
{
private:
	int serviceTime;
	int arrivalTime;
	string transactionType;

public:
	Customer()
	{
		serviceTime = 0;
		arrivalTime = 0;
		transactionType = " ";
	}

	
	Customer(int arrival_tick)
	{
		const string alpha[] = {"check deposit", 
								"cash deposit", 
								"loan payment", 
								"transfer", 
								"withdraval", 
								"cash a check",
								"change order",
								"balance inquiry"};

		// generates random transaction from array of transactions
		transactionType = alpha[rand() % (sizeof(alpha) / sizeof(string))];

		arrivalTime = arrival_tick;

		// generates real sevice time depending on transaction, in range [1 ... maxService]
		serviceTime = 1 + rand() % setMaxService(transactionType);
	}

	// sets maxService value depending on transaction type
	static int setMaxService(string transactionType)
	{
		int maxService = 0;
		if (transactionType.compare("check deposit") == 0)
			maxService = 3;
		else if (transactionType.compare("cash deposit") == 0)
			maxService = 7;
		else if (transactionType.compare("loan payment") == 0)
			maxService = 10;
		else if (transactionType.compare("transfer") == 0)
			maxService = 5;
		else if (transactionType.compare("withdraval") == 0)
			maxService = 6;
		else if (transactionType.compare("cash a check") == 0)
			maxService = 8;
		else if (transactionType.compare("change order") == 0)
			maxService = 10;
		else if (transactionType.compare("balance inquiry") == 0)
			maxService = 2;

		return maxService;
	}


	int getServiceTime() const { return serviceTime; }

	int getArrivalTime() const { return arrivalTime; }

	string getTransactionType() const { return transactionType; }
};