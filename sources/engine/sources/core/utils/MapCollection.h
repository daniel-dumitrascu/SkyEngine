#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include <map>
#include <memory>

template<class T>
class MapPtrCollection
{
	public:

		MapPtrCollection() {};
		MapPtrCollection(const MapPtrCollection<T>& copy) { /*TODO*/ };
		~MapPtrCollection();

		MapPtrCollection<T> operator=(const MapPtrCollection<T>& copy){ /*TODO*/ };

		void Add(const T* item, const std::string& key);
		void Remove(const std::string& key);
		unsigned int Count() const { return m_collection.size(); };
		bool Find(const std::string& key) const;
		T* Retrive(const std::string& key) const;

	protected:

		std::map<const std::string, std::unique_ptr<const T>>  m_collection;
};

template<class T>
MapPtrCollection<T>::~MapPtrCollection()
{
	m_collection.erase(m_collection.begin(), m_collection.end());
}

template<class T>
void MapPtrCollection<T>::Add(const T* item, const std::string& key)
{
	if(!Find(key))
		m_collection.insert(std::pair<const std::string, std::unique_ptr<const T>>(key, item));
}

template<class T>
void MapPtrCollection<T>::Remove(const std::string& key)
{
	typename std::map<const std::string, std::unique_ptr<const T>>::iterator it = m_collection.find(key);
	if(it != m_collection.end())
		m_collection.erase(it);
}

template<class T>
bool MapPtrCollection<T>::Find(const std::string& key) const
{
	return (m_collection.find(key) != m_collection.end());
}

template<class T>
T* MapPtrCollection<T>::Retrive(const std::string& key) const
{
	const T* result = nullptr;

	typename std::map<const std::string, std::unique_ptr<const T>>::const_iterator it = m_collection.find(key);
	if (it != m_collection.end())
		result = it->second.get();

	return const_cast<T*>(result);
}

#endif