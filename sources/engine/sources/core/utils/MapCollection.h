#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <map>

template<class T>
class MapCollection
{
	public:

		MapCollection();
		MapCollection(const MapCollection<T>& copy) {/*TODO*/ };
		~MapCollection();

		MapCollection<T> operator=(const MapCollection<T>& copy){/*TODO*/ };

		void Add(const T item, unsigned const int key);
		void Remove(const int index);
		unsigned int Count() const { return m_collection.size(); };
		bool Find(const int index) const;
		T Retrive(const int index) const;

	protected:

		std::map<unsigned int, T>  m_collection;
};

template<class T>
MapCollection<T>::MapCollection()
{

}

template<class T>
MapCollection<T>::~MapCollection()
{
	m_collection.erase(m_collection.begin(), m_collection.end());
}

template<class T>
void MapCollection<T>::Add(const T item, unsigned const int key)
{
	if(!Find(key))
		m_collection.insert(std::pair<unsigned int, T>(key, item));
}

template<class T>
void MapCollection<T>::Remove(const int index)
{
	typename std::map<unsigned int, T>::iterator it = m_collection.find(index);
	if(it != m_collection.end())
		m_collection.erase(it);
}

template<class T>
bool MapCollection<T>::Find(const int index) const
{
	return (m_collection.find(index) != m_collection.end());
}

template<class T>
T MapCollection<T>::Retrive(const int index) const
{
	T result = NULL;

	typename std::map<unsigned int, T>::const_iterator it = m_collection.find(index);
	if (it != m_collection.end())
		result = it->second;

	return result;
}

#endif