#include "Stream.h"

bool Stream::Open(const std::string& file_path, std::ios_base::openmode mode)
{
	/* Do we have an already opened stream ? */
	if (m_isOpen)
		Close();

	/* Open the new stream */
	m_file_stream = std::make_unique<std::fstream>(file_path, mode);

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
			m_file_stream.release();
		}
	}

	return m_isOpen;
}

void Stream::Close()
{ 
	if (m_isOpen)
	{
		m_file_stream->close();
		m_file_stream.release();
		m_isOpen = false;
	}
}