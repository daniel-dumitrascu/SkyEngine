#ifndef TEXTURE_RESOURCES_H
#define TEXTURE_RESOURCES_H

#include "utils/MapCollection.h"
#include "Texture.h"


class TexRes : public MapCollection<Texture*>
{
	public:

		static TexRes* GetInstance();

		void Add(Texture* texture, int key);
		void Remove(const int index);
		unsigned int Count() { return MapCollection::Count(); };
		bool Find(const int index);
		Texture* Retrive(const int index);

	private:

		TexRes() {};
		TexRes(const TexRes& copy) {};
		~TexRes() {};

		TexRes& operator=(const TexRes& copy);
};



#endif