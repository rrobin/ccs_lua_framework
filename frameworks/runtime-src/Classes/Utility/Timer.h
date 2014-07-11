#pragma once

#include "common.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

inline uint32 getMSTime() { return GetTickCount(); }
#elif defined(ANDROID) || defined(LINUX)
#include <sys/time.h>

inline uint32 getMSTime() { struct timespec ts;clock_gettime(CLOCK_MONOTONIC,&ts);return (ts.tv_sec*1000 + ts.tv_nsec/1000000); }
#elif defined(__APPLE__)
#include <sys/time.h>

inline uint32 getMSTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#endif

inline uint32 getMSTimeDiff(uint32 oldMSTime, uint32 newMSTime)
{
	// getMSTime() have limited data range and this is case when it overflow in this tick
	if (oldMSTime > newMSTime)
		return (0xFFFFFFFF - oldMSTime) + newMSTime;
	else
		return newMSTime - oldMSTime;
}

class IntervalTimer
{
public:
	IntervalTimer() : _interval(0), _current(0) {}

	void Update(time_t diff)
	{
		_current += diff;
		if (_current < 0)
			_current = 0;
	}
	bool Passed() const { return _current >= _interval; }
	void Reset()
	{
		// 为了消除断点带来的影响
		_current = 0;
		/*if (_current >= _interval)
			_current -= _interval;*/
	}

	void SetCurrent(time_t current) { _current = current; }
	void SetInterval(time_t interval) { _interval = interval; }
	time_t GetInterval() const { return _interval; }
	time_t GetCurrent() const { return _current; }

private:
	time_t _interval;
	time_t _current;
};

class ShortIntervalTimer
{
public:
	ShortIntervalTimer() : _interval(0), _current(0) {}

	void Update(uint32 diff)
	{
		_current += diff;
	}

	bool Passed() const { return _current >= _interval; }
	void Reset()
	{
		if (_current >= _interval)
			_current -= _interval;
	}

	void SetCurrent(uint32 current) { _current = current; }
	void SetInterval(uint32 interval) { _interval = interval; }
	uint32 GetInterval() const { return _interval; }
	uint32 GetCurrent() const { return _current; }

private:
	uint32 _interval;
	uint32 _current;
};

struct TimeTracker
{
public:
	TimeTracker(time_t expiry) : i_expiryTime(expiry) {}
	void Update(time_t diff) { i_expiryTime -= diff; }
	bool Passed() const { return (i_expiryTime <= 0); }
	void Reset(time_t interval) { i_expiryTime = interval; }
	time_t GetExpiry() const { return i_expiryTime; }

private:
	time_t i_expiryTime;
};

struct ShortTimeTracker
{
public:
	ShortTimeTracker(int32 expiry) : i_expiryTime(expiry) {}
	void Update(int32 diff) { i_expiryTime -= diff; }
	bool Passed() const { return (i_expiryTime <= 0); }
	void Reset(int32 interval) { i_expiryTime = interval; }
	int32 GetExpiry() const { return i_expiryTime; }

private:
	int32 i_expiryTime;
};
