#include "stdafx.h"
#include "PiCalculator.h"

namespace
{
	const double CIRCLE_RADIUS = 1;
	const int COORDINATE_DEGREE = 2;
	const int PI_COEFFICIENT = 4;
}

CPiCalculator::CPiCalculator(size_t iterations)
	: m_numberOfIterations(iterations)
{
	std::srand(std::time(0));
}

void CPiCalculator::Calculate()
{
	#pragma omp parallel for
	for (int i = 0; i < m_numberOfIterations; ++i)
	{
		if (IsInnerPoint(GetNextPoint()))
		{
			#pragma omp atomic
			++m_numberOfInnerPoint;
		}
	}
}

double CPiCalculator::GetCalculatedPi() const
{
	return PI_COEFFICIENT * (double) m_numberOfInnerPoint / m_numberOfIterations;
}

double CPiCalculator::GetNormalizedRandomNumber()
{
	return (double)std::rand() / RAND_MAX;
}

Point CPiCalculator::GetNextPoint()
{
	return Point(GetNirmalizedRandomNumber(), GetNirmalizedRandomNumber());
}

bool CPiCalculator::IsPointInside(const Point& point)
{
	return std::pow(point.first, COORDINATE_DEGREE) + std::pow(point.second, COORDINATE_DEGREE) <= CIRCLE_RADIUS;
}
