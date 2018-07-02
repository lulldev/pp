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


DWORD WINAPI Gardener1ThreadProc(LPVOID param) 
{
	ThreadData *data = (ThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	while (true) {
		const int rndGardener = distribution(randomEngine) % 2;
		const int rndFlowerPosition = distribution(randomEngine) % data
			->m_flowerBed->GetFlowersCount();
		data->m_flowerBed->DrizzleFlower(rndFlowerPosition, data->m_gardener_1);
	}

	return 0;
}

DWORD WINAPI Gardener2ThreadProc(LPVOID param)
{
	ThreadData *data = (ThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
std:uniform_int_distribution<> distribution;

	while (true) {
		const int rndGardener = distribution(randomEngine) % 2;
		const int rndFlowerPosition = distribution(randomEngine) % data
			->m_flowerBed->GetFlowersCount();
		data->m_flowerBed->DrizzleFlower(rndFlowerPosition, data->m_gardener_2);
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
		Sleep(6000);
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

	threadHandler.PushThread(Gardener1ThreadProc, &threadData);
	threadHandler.PushThread(Gardener2ThreadProc, &threadData);
	threadHandler.PushThread(FlowerThreadProc, &threadData);

	threadHandler.JoinAll();

	return 0;
}