#include "FileTGA.h"
#include "../../video/GraphicHeaders.h"


FileTGA* FileTGA::GetInstance()
{
	static FileTGA instance;
	return &instance;
}

Texture* FileTGA::LoadTGA(const std::string& file_path)
{
	TGA_header  header;
	Texture*    tex = new Texture;


	/* Open the file */
	Open(file_path, std::ios::in | std::ios::binary);

	/* Read the tga header */
	Read(&header, sizeof(TGA_header));

	tex->h = header.Height;
	tex->w = header.Width;

	/* Read the whole file */
	if (header.ColorDepth == 24)
	{
		int buffer_size = tex->w * tex->h;
		RGBPoint *Buffer24 = new RGBPoint[buffer_size];

		if (Buffer24)
		{
			int i = 0;

			Read(&(Buffer24[0].rgbtBlue), sizeof(RGBPoint)* buffer_size);
			unsigned char* buffer = new unsigned char[3 * buffer_size];

			if (!(header.Descriptor & INVERTED_BIT))
			{
				for (int y = 0; y < tex->h; y++)
					for (int x = 0; x < tex->w; x++)
					{
						int Index = (tex->h - 1 - y) * tex->w + x;

						buffer[(i * 3)] = Buffer24[Index].rgbtRed;
						buffer[(i * 3) + 1] = Buffer24[Index].rgbtGreen;
						buffer[(i * 3) + 2] = Buffer24[Index].rgbtBlue;

						i++;
					}
			}
			else
			{
				for (int y = 0; y < tex->h; y++)
					for (int x = 0; x < tex->w; x++)
					{
						int Index = y * tex->w + x;

						buffer[(i * 3)] = Buffer24[Index].rgbtRed;
						buffer[(i * 3) + 1] = Buffer24[Index].rgbtGreen;
						buffer[(i * 3) + 2] = Buffer24[Index].rgbtBlue;

						i++;
					}
			}

			/* Cleanup */
			delete [] Buffer24;

			// TODO notices that this load function does several things
			// including file upload and loading in OpenGL
			// Normally we should break these operations into as small as possible, namely
			// 1. load from HDD, we return a simple byte-array
			// 2. store in memory (maybe we don't need memory storage and we can skip directly from step 1 to 3)
			// 3. from memory, store in openGL
			// This also applies to LoadPNG

#if(GRAPHICS_OPENGL_ES_2_0 || GRAPHICS_OPENGL_LATEST)
			// Generate a texture ID
			glGenTextures(1, &tex->bind_id);

			// Bind the texture object
			glBindTexture(GL_TEXTURE_2D, tex->bind_id);

			// Load mipmap level 0
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0,
				         GL_RGB, GL_UNSIGNED_BYTE, (const void*)buffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

			delete [] buffer;
			Close();  	/* Close the stream */
			return tex;
		}
	}

	delete [] tex;
	Close();  	/* Close the stream */
	return NULL;	
}