#include "stdafx.h"
#include "Gardener.h"


Gardener::Gardener(size_t gardenerNo)
	: m_gardenerNo(gardenerNo)
{
}

size_t Gardener::GetGardenerNo() 
{
	return m_gardenerNo;
}

Gardener::~Gardener()
{
}
