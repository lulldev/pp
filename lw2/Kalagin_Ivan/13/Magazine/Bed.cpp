#include "stdafx.h"
#include "Shop.h"
#include "Customer.h"
#include "ThreadHandler.h"

using namespace std;

const string helpMessage = "Use Shop.exe <customer count>";
const string errorMessage = "Error of arguments! Use Shop.exe help to find startup parameters";

struct ThreadData {
	ThreadData()
	{
		m_shop1 = make_unique<Shop>("Fishing world");
		m_shop2 = make_unique<Shop>("Jewerly");
		m_shop3 = make_unique<Shop>("ReStore");
	}
	unique_ptr<Shop> m_shop1, m_shop2, m_shop3;
};


DWORD WINAPI ThreadProc(LPVOID param) 
{
	ThreadData *data = (ThreadData *)param;
	Customer customer;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	const int rnd = distribution(randomEngine) % 10;

	if (rnd <= 3)
	{
		data->m_shop1->Serve(customer);
	}
	else if (rnd > 3 && rnd <= 6) 
	{
		data->m_shop2->Serve(customer);
	}
	else if (rnd > 6 && rnd <= 10) 
	{
		data->m_shop3->Serve(customer);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << errorMessage << endl;
		return 1;
		
	}
	else {
		if (string(argv[1]) == "help") {
			cout << helpMessage << endl;
			return 0;
		}
			
	}
	size_t customerCount = atoi(argv[1]);

	ThreadHandler threadHandler;
	ThreadData threadData;

	for (size_t i = 0; i < customerCount; ++i) {
		threadHandler.PushThread(ThreadProc, &threadData);
	}

	threadHandler.JoinAll();

	return 0;
}