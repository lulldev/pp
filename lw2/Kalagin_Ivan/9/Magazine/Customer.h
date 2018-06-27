#pragma once

class Customer
{
public:
	Customer();
	~Customer();
	size_t GetCustomerID() const;
private:
	size_t m_customerID;
	static size_t m_nextCustomerID;
};

