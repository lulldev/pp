#include "stdafx.h"
#include "Flower.h"

Flower::Flower() : m_isWither(true)
{
}

bool Flower::IsWither() {
	return m_isWither;
}

void Flower::Drizzle() {
	m_isWither = false;
}

void Flower::Wither() {
	m_isWither = true;
}

Flower::~Flower()
{
}
