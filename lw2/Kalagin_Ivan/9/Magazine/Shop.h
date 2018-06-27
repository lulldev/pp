#pragma once
#include "Customer.h"
#include "Mutex.h"

class Shop
{
public:
	Shop(std::string shopName);
	~Shop();
	void Serve(Customer &customer);
	std::string GetShopName();
private:
	std::string m_shopName;
	std::unique_ptr<Mutex> m_mutex;
};

