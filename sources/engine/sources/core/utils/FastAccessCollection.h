#ifndef FAST_ACCESS_COLLECTION
#define FAST_ACCESS_COLLECTION

#include <iostream>
#include <vector>
#include <stack>
#include <memory>

/*
Properties:

- server with a constant number of sessions, number defined in FastAccessCollection.
- internally, the server will immediately access the session because the class that holds this (FastAccessCollection) session also has an index field.
a) deletion is very fast in this design
b) for addition we will have a chained list that will retain the free indexes in the connection vector.

Design:

- initially the connection vector has no stored connection so the list will have 1024 (or how big the vector is) of vacancies
list ---->  0, 1, 2, 3, 4 ... 1023
- at the first connection we call GetNextFreeEntry() which returns the next free index, so 0 and the list becomes 1, 2, 3, 4 ... 1023
- at the next connection returns 1 and the list becomes 2, 3, 4 ... 1023
- at the next connection returns 2 and the list becomes 3, 4 ... 1023
- let's say we lose connection from the position 1, list becomes 1, 3, 4 ... 1023
- if we no longer have vacancies, the function returns - 1
*/

template <class T>
class FastAccessCollection
{
	public:

		FastAccessCollection() = default;
		~FastAccessCollection() = default;

		int Occupy(const T* item);
	    void Free(const int index);
		void FreeAll();
		unsigned int Count() const;
		T* Retrive(const int index) const;
		bool IsSlotFree(const int index) const;
		
	protected:

		struct Wrapper
		{
			Wrapper(const T* item) : item(item), slotFree(false)
			{ }

			std::unique_ptr<const T> item;
			bool slotFree;
		};

		std::vector<Wrapper> m_collection;
		std::stack<int> m_availableSlots;

	private:

		FastAccessCollection(const FastAccessCollection& copy) = delete;
		int GetFreeSlotIfAvailable();
};

template <class T>
void FastAccessCollection<T>::Free(const int index)
{
	// Is this a valid index ? 
	if (index >= 0 && index < m_collection.size())
	{
		if (!(m_collection[index].slotFree))
		{
			// Important - do not remove the Wrapper from the collection
			// because that will be reused when making the isSlotFree true
			m_collection[index].slotFree = true;
			m_collection[index].item.release();
			m_availableSlots.push(index);
		}
	}
}

template <class T>
void FastAccessCollection<T>::FreeAll()
{
	// This iterates in all the occupied slots making them free
	for(int i=0; i < m_collection.size() && !IsSlotFree(i); i++)
		Free(i);
}

template <class T>
int FastAccessCollection<T>::Occupy(const T* item)
{
	// Do we have a free slot ?
	int nextFreeIndex = GetFreeSlotIfAvailable();

	if (nextFreeIndex != -1)
	{
		// We found a free slot and we are going to use it
		m_collection[nextFreeIndex].slotFree = false;
		m_collection[nextFreeIndex].item.reset(item);
	}
	else
	{
		// We don't have a free slot so we need to do a new 
		// insert into the collection 
		m_collection.push_back(Wrapper(item));
		nextFreeIndex = m_collection.size() - 1;
	}

	return nextFreeIndex;
}

template <class T>
T* FastAccessCollection<T>::Retrive(const int index) const
{
	// Is this a valid index ?
	if (index >= 0 && index < m_collection.size())
	{
		if (!(m_collection[index].slotFree))
			return const_cast<T*>(m_collection[index].item.get());
	}

	return nullptr;
}

template <class T>
bool FastAccessCollection<T>::IsSlotFree(const int index) const
{
	return (index >= 0 && index < m_collection.size()) && m_collection[index].slotFree;
}

template <class T>
int FastAccessCollection<T>::GetFreeSlotIfAvailable()
{
	int slot = -1;

	if (!m_availableSlots.empty())
	{
		slot = m_availableSlots.top();
		m_availableSlots.pop();
	}

	return slot;
}

template <class T>
unsigned int FastAccessCollection<T>::Count() const
{
	return m_collection.size();
}

#endif