#include "stdafx.h"
#include "PiCalculator.h"

namespace
{
const double CIRCLE_RADIUS = 1;
const int COORDINATE_DEGREE = 2;
const int PI_COEFFICIENT = 4;
} // namespace

CPiCalculator::CPiCalculator(size_t iterations, size_t threads)
	: m_numberOfIterations(iterations)
	, m_numberOfThreads(threads)
{
	std::srand(std::time(0));
}

void CPiCalculator::Calculate()
{
	size_t numberOfIterationsAtThread = m_numberOfIterations / m_numberOfThreads;

	ThreadData data(numberOfIterationsAtThread, &m_numberOfInnerPoint);

	if (m_numberOfThreads == 1)
	{
		CalculateNumberOfInnerPoints(&data);
	}
	else
	{
		std::vector<ThreadData> threadsData = std::vector<ThreadData>(m_numberOfThreads, data);
		size_t freeIterations = m_numberOfIterations % m_numberOfThreads;
		for (size_t i = 0; i < freeIterations; ++i)
		{
			++(threadsData.at(i).numberOfIterations);
		}
		for (size_t i = 0; i < m_numberOfThreads; ++i)
		{
			if (threadsData.at(i).numberOfIterations != 0)
			{
				m_controller.AddThread(CalculateNumberOfInnerPoints, &threadsData.at(i));
			}
		}
		m_controller.Execute();
	}
}

double CPiCalculator::GetCalculatedPi() const
{
	return PI_COEFFICIENT * (double)m_numberOfInnerPoint / m_numberOfIterations;
}

double CPiCalculator::GetNormalizedRandomNumber()
{
	return (double)std::rand() / RAND_MAX;
}

Point CPiCalculator::GetNextPoint()
{
	return Point(GetNormalizedRandomNumber(), GetNormalizedRandomNumber());
}

bool CPiCalculator::IsInnerPoint(const Point& point)
{
	return std::pow(point.first, COORDINATE_DEGREE) + std::pow(point.second, COORDINATE_DEGREE) <= CIRCLE_RADIUS;
}

DWORD CPiCalculator::CalculateNumberOfInnerPoints(LPVOID data)
{
	ThreadData* threadData = static_cast<ThreadData*>(data);
	for (size_t i = 0; i < threadData->numberOfIterations; ++i)
	{
		if (IsInnerPoint(GetNextPoint()))
		{
			InterlockedIncrement(threadData->numberOfInnerPoints);
		}
	}

	return 0;
}
