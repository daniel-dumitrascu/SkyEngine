#include "FilePNG.h"
#include <png.h>
#include "texture/Texture.h"
#include "../../video/GraphicHeaders.h"


FilePNG* FilePNG::GetInstance()
{
	static FilePNG instance;
	return &instance;
}

void* FilePNG::LoadPNG(const std::string& file_path)
{
	/* Open the file */
	m_file = fopen(file_path.c_str(), "rb");

	if (m_file)
	{
		m_isOpen = true;

		/* construct file size, just once */
		int cutt_pos = Tell();
		Seek(0, std::ios::end);
		m_file_size = Tell();
		Seek(cutt_pos, std::ios::beg);
	}
	else
	{
		m_isOpen = false;
		return NULL;
	}

	/* read the header */
	png_byte  header[8];
	Read(header, 8);

	if (png_sig_cmp(header, 0, 8))
	{
		log.message(file_path + " is not a png file.", Logging::MSG_ERROR);
		fclose(m_file);
		m_file = NULL;
		return NULL;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
	{
		log.message("png_create_read_struct returned 0", Logging::MSG_ERROR);
		fclose(m_file);
		m_file = NULL;
		return NULL;
	}

	/* create png info struct */
	png_infop info_ptr = png_create_info_struct(png_ptr);

	if (!info_ptr)
	{
		log.message("png_create_info_struct returned 0", Logging::MSG_ERROR);
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(m_file);
		m_file = NULL;
		return NULL;
	}

	/* create png info struct */
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		log.message("png_create_info_struct returned 0", Logging::MSG_ERROR);
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		fclose(m_file);
		m_file = NULL;
		return NULL;
	}

	/* the code in this if statement gets called if libpng encounters an error */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		log.message("From libpng internals.", Logging::MSG_ERROR);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(m_file);
		m_file = NULL;
		return NULL;
	}

	/* init png reading */
	png_init_io(png_ptr, m_file);

	/* let libpng know you already read the first 8 bytes */
	png_set_sig_bytes(png_ptr, 8);

	/* read all the info up to the image data */
	png_read_info(png_ptr, info_ptr);

	/* variables to pass to get info */
	int bit_depth, color_type;

	/* get info about png */
	Texture* texture_buffer = new Texture;
	png_get_IHDR(png_ptr, info_ptr, &texture_buffer->w, &texture_buffer->h,
		        &bit_depth, &color_type, NULL, NULL, NULL);

	if (bit_depth != 8)
	{
		log.message("Unsupported bit depth: " + std::to_string(bit_depth), Logging::MSG_ERROR);
		return 0;
	}
#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	GLint format;
	switch (color_type)
	{
		case PNG_COLOR_TYPE_RGB:
			format = GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			format = GL_RGBA;
			break;
		case PNG_COLOR_TYPE_PALETTE:
			png_set_expand(png_ptr);
			format = GL_RGB;
			break;
		default:
			log.message("Unknown libpng color type: " + std::to_string(color_type), Logging::MSG_ERROR);
			return 0;
	}
#endif

	/* Update the png info struct */
	png_read_update_info(png_ptr, info_ptr);

	/* Row size in bytes */
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	/* glTexImage2d requires rows to be 4-byte aligned */
	rowbytes += 3 - ((rowbytes - 1) % 4);
#endif
	
	/* Allocate the image_data as a big block */
	unsigned char* buffer = new unsigned char[(rowbytes * texture_buffer->h) + 15];
	png_bytep* row_pointers = new png_bytep[texture_buffer->h];

	if (buffer == NULL || row_pointers == NULL)
	{
		log.message("Could not allocate memory for PNG image data", Logging::MSG_ERROR);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(m_file);
		return NULL;
	}

	/* set the individual row_pointers to point at the correct offsets of image_data */
	/* For the inverted image modify code as follows: row_pointers[texture_buffer->h - 1 - i] */
	for (int i = 0; i < texture_buffer->h; i++)
		row_pointers[texture_buffer->h - 1 - i] = buffer + i * rowbytes;

	/* read the png into image_data through row_pointers */
	png_read_image(png_ptr, row_pointers);
	delete[] row_pointers;

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
	// Generate a texture ID
	glGenTextures(1, &texture_buffer->bind_id);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture_buffer->bind_id);

	// Load mipmap level 0
	glTexImage2D(GL_TEXTURE_2D, 0, format, texture_buffer->w, texture_buffer->h, 0,
		         format, GL_UNSIGNED_BYTE, (const void*)buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

	delete[] buffer;

	/* clean up */
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	fclose(m_file);
	return texture_buffer;
}

void FilePNG::Read(void* buffer, int size)
{
	fread(buffer, sizeof(char), size, m_file);
}

void FilePNG::Seek(int offset, int way)
{
	fseek(m_file, offset, way);
}

int FilePNG::Tell() const
{
	return ftell(m_file);
}