#ifndef LEVEL_LOADER
#define LEVEL_LOADER

#include "loader/Loader.h"
#include "logging/Logging.h"

class LevelLoader : public Loader
{
	public:

		static LevelLoader* GetInstance();
		void* Load(const std::string& file_path);

	private:

		LevelLoader();
		LevelLoader(const LevelLoader& copy) = delete;
		~LevelLoader() {};

		LevelLoader& operator = (const LevelLoader& copy) {};

		Logging log;
};


#endif