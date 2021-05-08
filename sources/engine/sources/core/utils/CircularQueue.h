#pragma once
#include <vector>

template<class T>
class CircularQueue
{
	public:

		CircularQueue() = delete;
		CircularQueue(const int size);
		~CircularQueue() {};

		// Add to rear
		bool add(T item);

		// Remove from front
		T remove();

		// Make the queue empty
		void reset();

		bool isFull();
		bool isEmpty();
		int size() { return queueSize;  }

	private:

		int queueSize = 0;
		int queueFront = -1;
		int queueRear = -1;
		std::vector<T> queueData;
};


template<class T>
CircularQueue<T>::CircularQueue(const int size) : queueSize(size)
{
	queueData.resize(queueSize);
}

template<class T>
bool CircularQueue<T>::add(T item)
{
	if (isFull())
	{
		// The circular queue is full so we don't add the element
		return false;
	}
	else
	{
		if (queueFront == -1)
			queueFront = 0;
		
		queueRear = (queueRear + 1) % queueSize;
		queueData[queueRear] = item;
		return true;
	}
}

template<class T>
T CircularQueue<T>::remove() 
{
	if (isEmpty()) 
	{
		//TODO what happens here if the template T is a string?
		return -1;
	}
	else
	{
		T item = queueData[queueFront];
		if (queueFront == queueRear)
		{
			queueFront = -1;
			queueRear = -1;
		}
		else 
		{
			queueFront = (queueFront + 1) % queueSize;
		}
		return item;
	}
}

template<class T>
void CircularQueue<T>::reset()
{
	queueFront = -1;
	queueRear = -1;
}

template<class T>
bool CircularQueue<T>::isFull() 
{
	if (queueFront == 0 && queueRear == (queueSize - 1))
		return true;

	if (queueFront == queueRear + 1)
		return true;

	return false;
}

template<class T>
bool CircularQueue<T>::isEmpty() 
{
	if (queueFront == -1)
		return true;
	else
		return false;
}