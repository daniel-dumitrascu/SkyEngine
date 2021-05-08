#ifndef IOFILE_H_
#define IOFILE_H_

#include <iostream>
#include <string>
#include "Stream.h"


class OClearFile: public Stream
{
	public:

		OClearFile(const char* _path, std::ios_base::openmode mode = std::ios_base::out);
		 OClearFile(const std::string& _path, std::ios_base::openmode mode);
		~OClearFile();

		/*TODO 
		 
		  an open and close stream

		  Open(const char* _path, int mode);   
		  Close();
		*/
 
		 int Size() const { return Tell(); }

		 friend std::fstream& operator <<(OClearFile& file, const std::string& message);
		 friend std::fstream& operator <<(OClearFile& file, const char* message);
};

#endif
