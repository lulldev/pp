#pragma once

using Point = std::pair<double, double>;

class CPiCalculator
{
public:
	CPiCalculator(size_t iterations);
	void Calculate();
	double GetCalculatedPi() const;

private:
	static double GetNormalizedRandomNumber();
	static Point GetNextPoint();
	static bool IsPointInside(const Point& point);

	size_t m_numberOfInnerPoint = 0;
	size_t m_numberOfIterations = 0;
};
