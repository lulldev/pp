#include "stdafx.h"
#include "FlowerBed.h"
#include "Gardener.h"
#include "ThreadHandler.h"

using namespace std;

const string helpMessage = "Use GardenBed.exe <flowers count>";
const string errorMessage = "Error of arguments! Use GardenBed.exe help to find startup parameters";

struct GardenerThreadData 
{
	GardenerThreadData(shared_ptr<FlowerBed> flowerBed, shared_ptr<Gardener> gardener)
	{
		m_flowerBed = std::move(flowerBed);
		m_gardener = std::move(gardener);
	}
	shared_ptr<FlowerBed> m_flowerBed;
	shared_ptr<Gardener> m_gardener;
};

struct FlowerThreadData 
{
	FlowerThreadData(shared_ptr<FlowerBed> flowerBed)
	{
		m_flowerBed = std::move(flowerBed);
	}
	shared_ptr<FlowerBed> m_flowerBed;
};

DWORD WINAPI GardenerThreadProc(LPVOID param)
{
	GardenerThreadData *data = (GardenerThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	while (true) 
	{
		const int rndGardener = distribution(randomEngine) % 2;
		const int rndFlowerPosition = distribution(randomEngine) % data
			->m_flowerBed->GetFlowersCount();

		data->m_flowerBed->DrizzleFlower(rndFlowerPosition, data->m_gardener);
	}

	return 0;
}

DWORD WINAPI FlowerThreadProc(LPVOID param)
{
	FlowerThreadData *data = (FlowerThreadData *)param;

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());
	std:uniform_int_distribution<> distribution;

	while (true) {
		const int rndFlowerPosition = distribution(randomEngine) % data
			->m_flowerBed->GetFlowersCount();

		data->m_flowerBed->WitherFlower(rndFlowerPosition);
		Sleep(4000);
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


	std::shared_ptr<FlowerBed> flowerBed(new FlowerBed(flowersCount));
	std::shared_ptr<Gardener> gardener1(new Gardener(1));
	std::shared_ptr<Gardener> gardener2(new Gardener(2));

	FlowerThreadData flowerData(flowerBed);
	GardenerThreadData gardenerThreadData1(flowerBed, gardener1);
	GardenerThreadData gardenerThreadData2(flowerBed, gardener2);

	threadHandler.PushThread(GardenerThreadProc, &gardenerThreadData1);
	threadHandler.PushThread(GardenerThreadProc, &gardenerThreadData2);
	threadHandler.PushThread(FlowerThreadProc, &flowerData);

	threadHandler.JoinAll();

	return 0;
}