#pragma once
#include <queue>
#include <pthread.h>

class CAutoLock
{
public:
	CAutoLock( pthread_mutex_t* mutex )
	{
		m_mutex = mutex;
		pthread_mutex_lock( m_mutex );
	}
	virtual ~CAutoLock()
	{
		pthread_mutex_unlock( m_mutex );
	}
protected:
private:
	pthread_mutex_t* m_mutex;
};

template <class T, typename StorageType=std::deque<T> >
class UnLockedQueue
{
public:
	StorageType _queue;
	pthread_mutex_t _mutex;
	bool _canceled;

	//! Create a LockedQueue.
	UnLockedQueue() : _canceled(false) { pthread_mutex_init(&_mutex, NULL); }

	//! Destroy a LockedQueue.
	virtual ~UnLockedQueue() { }

	//! Adds an item to the queue.
	void add(const T& item)
	{
		// autolock
		CAutoLock lock( &_mutex );
		_queue.push_back(item);
	}

	//! Gets the next result in the queue, if any.
	bool next(T& result)
	{
		// autolock
		CAutoLock lock( &_mutex );
		if (_queue.empty())
			return false;

		result = _queue.front();
		_queue.pop_front();

		return true;
	}

	bool empty()
	{
		// autolock
		CAutoLock lock( &_mutex );
		return _queue.empty();
	}

	//! Cancels the queue.
	void cancel()
	{
		// autolock
		CAutoLock lock( &_mutex );
		_canceled = true;
	}

	//! Checks if the queue is cancelled.
	bool cancelled()
	{
		// autolock
		CAutoLock lock( &_mutex );
		return _canceled;
	}
};