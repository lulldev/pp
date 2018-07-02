#pragma once

class Flower
{
public:
	Flower();
	~Flower();
	bool IsWither();
	void Drizzle();
	void Wither();
private:
	bool m_isWither;
};

