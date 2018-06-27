#pragma once
#include <vector>

class ThreadHandler
{
public:
	ThreadHandler();
	~ThreadHandler();
	void JoinAll();
	void PushThread(LPTHREAD_START_ROUTINE functionPointer, LPVOID param);
private:
	std::vector<HANDLE> m_threads;
};

