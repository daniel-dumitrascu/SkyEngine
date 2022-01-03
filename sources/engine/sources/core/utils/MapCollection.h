#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <map>

template<class T>
class MapCollection
{
	public:

		MapCollection();
		MapCollection(const MapCollection<T>& copy) { /*TODO*/ };
		~MapCollection();

		MapCollection<T> operator=(const MapCollection<T>& copy){ /*TODO*/ };

		void Add(const T item, const std::string& key);
		void Remove(const std::string& key);
		unsigned int Count() const { return m_collection.size(); };
		bool Find(const std::string& key) const;
		T Retrive(const std::string& key) const;

	protected:

		std::map<const std::string, T>  m_collection;
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
void MapCollection<T>::Add(const T item, const std::string& key)
{
	if(!Find(key))
		m_collection.insert(std::pair<const std::string, T>(key, item));
}

template<class T>
void MapCollection<T>::Remove(const std::string& key)
{
	typename std::map<const std::string, T>::iterator it = m_collection.find(key);
	if(it != m_collection.end())
		m_collection.erase(it);
}

template<class T>
bool MapCollection<T>::Find(const std::string& key) const
{
	return (m_collection.find(key) != m_collection.end());
}

template<class T>
T MapCollection<T>::Retrive(const std::string& key) const
{
	T result = NULL;

	typename std::map<const std::string, T>::const_iterator it = m_collection.find(key);
	if (it != m_collection.end())
		result = it->second;

	return result;
}

#endif