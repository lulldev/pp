#pragma once
class Mutex
{
public:
	Mutex();
	~Mutex();
	void Join();
	void Release();
private:
	HANDLE m_hMutex;
};

