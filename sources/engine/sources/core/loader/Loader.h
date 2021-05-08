#ifndef LOADER
#define LOADER

#include <iostream>
#include <string>

/* Load a resource into memory */

class Loader
{
	public:

				  Loader() {};
		 virtual ~Loader() {};

		 virtual void* Load(const std::string& file_path) = 0;

	protected:

		 bool  m_is_loaded;

	private:

		 Loader(const Loader& copy) {};
		 Loader&  operator=(const Loader& copy) { return *this; };		
};

#endif