#include "stdafx.h"
#include "Customer.h"

size_t Customer::m_nextCustomerID = 1;

Customer::Customer():
	m_customerID(m_nextCustomerID++)
{
}

Customer::~Customer()
{
}


size_t Customer::GetCustomerID() const
{
	return m_customerID;
}
