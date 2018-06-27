#include "stdafx.h"
#include "Mutex.h"


Mutex::Mutex()
{
	m_hMutex = CreateMutex(NULL, false, NULL);
}

Mutex::~Mutex()
{
	CloseHandle(m_hMutex);
}

void Mutex::Join()
{
	WaitForSingleObject(m_hMutex, INFINITE);
}

void Mutex::Release()
{
	ReleaseMutex(m_hMutex);
}

