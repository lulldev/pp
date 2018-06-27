#include "stdafx.h"
#include "ThreadsController.h"

void CThreadsController::Execute()
{
	WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}

void CThreadsController::AddThread(LPTHREAD_START_ROUTINE function, LPVOID data)
{
	m_threadsData.emplace_back(data);
	m_threads.emplace_back(CreateThread(NULL, NULL, function, 
		m_threadsData.back(), 0, NULL));
}

void CThreadsController::CloseThreads()
{
	for (auto thread : m_threads)
	{
		CloseHandle(thread);
	}
}

CThreadsController::~CThreadsController()
{
	CloseThreads();
}
