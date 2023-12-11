#pragma once
#include <Windows.h>
class FPSControl
{
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequensy;
public:
	FPSControl()
	{
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequensy = t.QuadPart;
		Reset();
	}
	void Reset()
	{
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}
	void Update()
	{
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}
	double GetTimeTotal()
	{
		double d = currentCallToUpdate - startTime;
		return d / (frequensy);
	}
	double GetTimeDelta()
	{
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / frequensy;
	}
	void SetFreq() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequensy = t.QuadPart;
	}

};

