#pragma once

struct ThreadData
{
	ThreadData(size_t iterations, size_t* innerPoints)
		: numberOfIterations(iterations)
		, numberOfInnerPoints(innerPoints)
	{
	}
	size_t numberOfIterations;
	size_t* numberOfInnerPoints;
};

class CThreadsController
{
public:
	void Execute();
	void AddThread(LPTHREAD_START_ROUTINE function, LPVOID data);
	~CThreadsController();

private:
	void CloseThreads();

	std::vector<HANDLE> m_threads;
	std::vector<LPVOID> m_threadsData;
};
