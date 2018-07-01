#include "stdafx.h"
#include "FlowerBed.h"
#include "Gardener.h"
#include "ThreadHandler.h"

using namespace std;

const string helpMessage = "Use GardenBed.exe <flowers count>";
const string errorMessage = "Error of arguments! Use GardenBed.exe help to find startup parameters";

struct ThreadData {
	ThreadData(size_t flowersCount)
	{
		m_gardener_1 = make_unique<Gardener>(1);
		m_gardener_2 = make_unique<Gardener>(2);
		m_flowerBed = make_unique<FlowerBed>(flowersCount);
	}
	unique_ptr<Gardener> m_gardener_1, m_gardener_2;
	unique_ptr<FlowerBed> m_flowerBed;
};


DWORD WINAPI DrizzleThreadProc(LPVOID param) 
{
	ThreadData *data = (ThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	const int rnd = distribution(randomEngine) % 2;

	if (rnd % 2 == 0)
	{
		data->m_flowerBed->DrizzleFlower(0, data->m_gardener_1);
	}
	else
	{
		data->m_flowerBed->DrizzleFlower(0, data->m_gardener_2);
	}

	return 0;
}

DWORD WINAPI FlowerThreadProc(LPVOID param)
{
	ThreadData *data = (ThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	while (true) {
		const int rndFlowerPosition = distribution(randomEngine) % data
			->m_flowerBed->GetFlowersCount();

		data->m_flowerBed->WitherFlower(rndFlowerPosition);
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
	else 
	{
		if (string(argv[1]) == "help") {
			cout << helpMessage << endl;
			return 0;
		}
			
	}
	size_t flowersCount = atoi(argv[1]);

	ThreadHandler threadHandler;
	ThreadData threadData(flowersCount);

	for (size_t i = 0; i < flowersCount; ++i) {
		threadHandler.PushThread(DrizzleThreadProc, &threadData);
	}

	threadHandler.PushThread(FlowerThreadProc, &threadData);

	threadHandler.JoinAll();

	return 0;
}