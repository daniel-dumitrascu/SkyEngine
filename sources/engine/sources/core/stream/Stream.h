#ifndef ISTREAM_H_
#define ISTREAM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

class Stream
{
	public:

		Stream() : m_isOpen(false), m_file_size(0) {}
		virtual ~Stream(){}

		virtual bool Open(const std::string& file_path, std::ios_base::openmode mode);
		virtual void Close();
		virtual void Read(void* buffer, const int size) { m_file_stream->read((char*)buffer, size); };
		virtual void Write(const void* buffer, int size) { m_file_stream->write((const char*)buffer, size); };
		virtual void Seek(const int offset, const std::ios_base::seekdir way) { m_file_stream->seekg(offset, way); };
		virtual int  Tell() const { return m_file_stream->tellg(); };
		virtual int  Size() { return m_file_size; };
		

		bool IsOpen() const { return m_isOpen; };

	protected:

		bool m_isOpen;
		std::unique_ptr<std::fstream> m_file_stream;
		int m_file_size;

	private:

		Stream(const Stream&) {}
		Stream& operator=(const Stream&) {}		
};


#endif 
