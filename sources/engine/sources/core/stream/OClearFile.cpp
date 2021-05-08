#include "OClearFile.h"
#include "time/Time.h"

OClearFile::OClearFile(const char* _path, std::ios_base::openmode mode/* = std::ios_base::out*/)
{
	/* We need to do this for 2 reasons                       */
	/* 1. if the file is not created fopen will create it     */
	/* 2. if the file exists, fopen will erase the content    */

	FILE* _file = NULL;

	switch (mode)
	{
		case std::ios_base::out:
		{
			/* Write to new file */
			_file = fopen(_path, "w");
			fclose(_file);
			Open(_path, std::ios::out);
			break;
		}
		case std::ios_base::app:
		{
			/* Append to an already created file */
			if((_file = fopen(_path, "r")) == NULL)
			   _file = fopen(_path, "w");

			fclose(_file);

			Open(_path, std::ios::app);
			break;
		}
		default:
		{
			/* Default: write to new file */
			FILE* fcreate = fopen(_path, "w");
			fclose(fcreate);
			Open(_path, std::ios::out);
		}
	}
}

OClearFile::OClearFile(const std::string& _path, std::ios_base::openmode mode = std::ios_base::out)
{
	/* We need to do this for 2 reasons                       */
	/* 1. if the file is not created fopen will create it     */
	/* 2. if the file exists, fopen will erase the content    */

	switch (mode)
	{
		case std::ios_base::out:
		{
			/* Write to new file */
			FILE* _file = fopen(_path.c_str(), "w");
			fclose(_file);
			Open(_path, std::ios::out);
			break;
		}
		case std::ios_base::app:
		{
			/* Append to an already created file */
			FILE* _file = fopen(_path.c_str(), "r");

			if (_file == NULL)
			{
				/* If the file doesn't exist then we create it */
				_file = fopen(_path.c_str(), "w");
				fclose(_file);
			}	

			Open(_path, std::ios::app);
			break;
		}
		default:
		{
			/* Default: write to new file */
			FILE* fcreate = fopen(_path.c_str(), "w");
			fclose(fcreate);
			Open(_path, std::ios::out);
		}
	}
}

OClearFile::~OClearFile()
{
	Close();
}

std::fstream& operator <<(OClearFile& file, const std::string& message)
{
	std::string outMess = CoreTime::GetDateAndTimeAsString();
	
	outMess += " - ";
	outMess += message;

	file.Write(outMess.c_str(), outMess.size());
	return *(file.m_file_stream);
}

std::fstream& operator <<(OClearFile& file, const char* message)
{
	std::string outMess = CoreTime::GetDateAndTimeAsString();

	outMess += " - ";
	outMess += message;

	file.Write(outMess.c_str(), outMess.size());
	return *(file.m_file_stream);
}