#pragma once
#include "ThreadsController.h"

using Point = std::pair<double, double>;

class CPiCalculator
{
public:
	CPiCalculator(size_t iterations, size_t threads);
	void Calculate();
	double GetCalculatedPi() const;

private:
	static double GetNormalizedRandomNumber();
	static Point GetNextPoint();
	static bool IsInnerPoint(const Point& point);
	static DWORD WINAPI CalculateNumberOfInnerPoints(LPVOID data);

	size_t m_numberOfInnerPoint = 0;
	size_t m_numberOfIterations = 0;
	size_t m_numberOfThreads = 0;
	CThreadsController m_controller;
};
