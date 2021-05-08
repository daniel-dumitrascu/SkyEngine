#ifndef FILE_PNG_H
#define FILE_PNG_H

#include <iostream>
#include <string>
#include "stream/Stream.h"
#include "logging/Logging.h"


class FilePNG : private Stream
{
	public:

		static FilePNG* GetInstance();
		void* LoadPNG(const std::string& file_path);

	private:

		FilePNG() : m_file(NULL), log("FilePNG") {};
		FilePNG(const FilePNG& copy) = delete;
		~FilePNG() {};

		void Read(void* buffer, int size);
		void Seek(int offset, int way);
		int Tell() const;

		bool PNG_ReadHeader();

		FILE* m_file;
		Logging log;
};


#endif