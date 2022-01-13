#ifndef TEXTURE_RESOURCES_H
#define TEXTURE_RESOURCES_H

#include "utils/MapCollection.h"
#include "Texture.h"


class TexRes : public MapPtrCollection<Texture>
{
	public:

		static TexRes* GetInstance();

		void Add(const std::string& key, const std::string pathToResource);
		void Remove(const std::string& key);
		unsigned int Count() { return MapPtrCollection::Count(); };
		bool Find(const std::string& key);
		Texture* Retrive(const std::string& key);

	private:

		TexRes() {};
		TexRes(const TexRes& copy) {};
		~TexRes() {};

		TexRes& operator=(const TexRes& copy);
};



#endif