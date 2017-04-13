#pragma once
#include "Customer.h"

class Teller
{
private:
	bool status;
	Customer customer;
	int teller_timer;

public:
	Teller()
	{
		status = true;
		teller_timer = 0;
	}

	bool isAvailable() const { return (teller_timer == 0) ? true : false; }

	// sets teller's status as busy and initialized teller timer = customer's real service time
	void addCustomer(Customer C, int i)
	{
		customer = C;
		status = false;
		teller_timer = C.getServiceTime();
	}

	void decrementTimer() { teller_timer--; }
};
