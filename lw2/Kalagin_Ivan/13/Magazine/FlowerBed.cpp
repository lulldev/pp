#include "stdafx.h"
#include "FlowerBed.h"

const int DRIZZLE_TIME = 1000;
const int WITHER_TIME = 500;

FlowerBed::FlowerBed(size_t flowerCount)
	: m_mutex(std::make_unique<Mutex>())
{
	for (size_t i = 0; i < flowerCount; ++i) {
		m_flowers.emplace_back(Flower());
	}
}

size_t FlowerBed::GetFlowersCount() {
	return m_flowers.size();
}

void FlowerBed::DrizzleFlower(size_t flowerPosition, std::unique_ptr<Gardener>& gardener)
{
	std::printf("Gardener #%d want to start drizzle #%d flower\n", 
		gardener->GetGardenerNo(), flowerPosition);
	m_mutex->Join();

	if (m_flowers.at(flowerPosition).IsWither()) 
	{
		std::printf("Gardener #%d start drizzle #%d flower\n",
			gardener->GetGardenerNo(), flowerPosition);
		m_flowers.at(flowerPosition).Drizzle();
		Sleep(DRIZZLE_TIME);
		std::printf("Gardener #%d finish drizzle #%d flower\n",
			gardener->GetGardenerNo(), flowerPosition);
	}
	else
	{
		std::printf("Flower #%d dont need drizzle \n", flowerPosition);
	}

	m_mutex->Release();
}

void FlowerBed::WitherFlower(size_t flowerPosition)
{
	m_mutex->Join();
	std::printf("Flower #%d is wither!\n", flowerPosition);
	m_flowers.at(flowerPosition).Wither();
	Sleep(WITHER_TIME);
	m_mutex->Release();
}

FlowerBed::~FlowerBed()
{
}
