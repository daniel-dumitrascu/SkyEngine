#ifndef ANIM_LOADER_H
#define ANIM_LOADER_H

#include "loader/Loader.h"
#include "logging/Logging.h"

class AnimDataLoader : public Loader
{
	public:

		static AnimDataLoader* GetInstance();
		void* Load(const std::string& file_path);

	private:

		AnimDataLoader();
		AnimDataLoader(const AnimDataLoader& copy) = delete;
		~AnimDataLoader() {};

		AnimDataLoader& operator = (const AnimDataLoader& copy) {};

		Logging log;
};

#endif