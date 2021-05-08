#ifndef KEY_COLLECTION
#define KEY_COLLECTION

#include <iostream>
#include <map>

enum ResourceKeyType
{
	KEY_TILE,
	KEY_ANIMATION,
	KEY_TEXTURE,
	KEY_SHADER
};

class ResourceKeyCollection
{
	public:

		static ResourceKeyCollection* GetInstance();

		const std::string&  GetNameByKey(const int key_type, int id);
		void AddKey(const int key_type, const int id, const std::string& name);

	private:

		ResourceKeyCollection() : m_undefined("") {}
		ResourceKeyCollection(const ResourceKeyCollection& copy) : m_undefined("") {};
		~ResourceKeyCollection() {};

		ResourceKeyCollection& operator = (const ResourceKeyCollection& copy);

	private:

		/* tile keys */
		std::map<const int, const std::string> m_tile_keys;

		/* animation keys */
		std::map<const int, const std::string> m_animation_keys;

		/* texture keys */
		std::map<const int, const std::string> m_texture_keys;

		/* shader keys */
		std::map<const int, const std::string> m_shader_keys;

		/* undefined string that is returned in the case */
		/* of a wrong ID in GetNameByKey */
		const std::string m_undefined;
};


#endif