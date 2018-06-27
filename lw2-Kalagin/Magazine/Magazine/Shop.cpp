#include "stdafx.h"
#include "Shop.h"

const int SHOPPING_TIME = 100;

Shop::Shop(std::string shopName) 
	: m_shopName(shopName),
	m_mutex(std::make_unique<Mutex>())
{
}

void Shop::Treat(Customer &customer)
{
	std::printf("Customer #%zd went to the queue to the: %s\n", customer.GetCustomerID(), m_shopName.c_str());
	m_mutex->Join();
	std::printf("Customer #%zd started shopping: %s\n", customer.GetCustomerID(), m_shopName.c_str());
	Sleep(SHOPPING_TIME);
	std::printf("Customer #%zd finished shopping: %s\n", customer.GetCustomerID(), m_shopName.c_str());
	m_mutex->Release();
}

std::string Shop::GetShopName()
{
	return m_shopName;
}


Shop::~Shop()
{
}
