#include "Stream.h"

bool Stream::Open(const std::string& file_path, std::ios_base::openmode mode)
{
	/* Do we have an already opened stream ? */
	if (m_isOpen)
	{
		// close it
		Close();
		delete m_file_stream;
	}

	/* Open the new stream */
	m_file_stream = new std::fstream(file_path, mode);

	if (m_file_stream)
	{
		if (m_file_stream->is_open())
		{
			m_isOpen = true;

			// construct file size
			int cutt_pos = Tell();

#if(WINDOWS_PLATFORM)
			Seek(0, std::ios_base::end);
#elif(LINUX_PLATFORM)
			Seek(0, std::ios_base::seekdir::_S_end);
#endif
	
			m_file_size = Tell();

#if(WINDOWS_PLATFORM)
			Seek(cutt_pos, std::ios_base::beg);
#elif(LINUX_PLATFORM)
			Seek(cutt_pos, std::ios_base::seekdir::_S_beg);
#endif
		}
		else
		{
			delete m_file_stream;
		}
	}

	return m_isOpen;
}

void Stream::Close()
{ 
	if (m_isOpen)
	{
		m_file_stream->close();
		delete m_file_stream;
		m_isOpen = false;
	}
}