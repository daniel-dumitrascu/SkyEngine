#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include "loader/Loader.h"
#include "Texture.h"
#include "logging/Logging.h"


class TexLoader : public Loader
{
	
	public:

		static TexLoader* GetInstance();
		void* Load(const std::string& file_path);

	private:

		TexLoader();
		TexLoader(const TexLoader& copy) = delete;
		~TexLoader() {};

		TexLoader& operator = (const TexLoader& copy) {};

		Logging log;
};


#endif