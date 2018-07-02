#pragma once
#include "Flower.h"
#include "Gardener.h"
#include "Mutex.h"

class FlowerBed
{
public:
	FlowerBed(size_t flowerCount);
	~FlowerBed();
	size_t GetFlowersCount();
	void DrizzleFlower(size_t flowerPosition, std::unique_ptr<Gardener>& gardener);
	void WitherFlower(size_t flowerPosition);
	bool IsAllFlowersDrezzled();
private:
	std::vector<Flower> m_flowers;
	std::unique_ptr<Mutex> m_mutex;
};

