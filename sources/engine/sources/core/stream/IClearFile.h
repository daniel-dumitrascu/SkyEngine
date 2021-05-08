#ifndef ICLEARFILE_H
#define ICLEARFILE_H

#include <iostream>
#include <string>
#include "Stream.h"

class IClearFile : public Stream
{
	public:

		 IClearFile(const char* _path);
		 IClearFile(const std::string& _path);
		~IClearFile();

		/*TODO

			an open and close stream

			Open(const char* _path);
			Close();
		*/

		 void Read(void* buffer, int size);

		 friend std::fstream& operator >>(IClearFile& file, char* message);
};


#endif