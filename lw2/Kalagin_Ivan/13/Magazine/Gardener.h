#pragma once
class Gardener
{
public:
	Gardener(size_t gardenerNo);
	~Gardener();
	size_t GetGardenerNo();
private:
	size_t m_gardenerNo;
};
