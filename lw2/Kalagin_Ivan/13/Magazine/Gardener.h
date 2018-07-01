#pragma once
class Gardener
{
public:
	Gardener(size_t gardenerNo);
	~Gardener();
private:
	size_t m_gardenerNo;
	std::unique_ptr<Mutex> m_mutex;
};

