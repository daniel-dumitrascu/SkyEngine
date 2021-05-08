#ifndef FILE_TGA_H
#define FILE_TGA_H

#include <iostream>
#include <string>
#include "stream/Stream.h"
#include "texture/Texture.h"

#define INVERTED_BIT            (1 << 5)

#pragma pack(push,x1)         // Byte alignment (8-bit)
#pragma pack(1)

typedef struct
{
	unsigned char  IdSize, 
	               MapType, 
				   ImageType;
	unsigned short PaletteStart, 
		           PaletteSize;
	unsigned char  PaletteEntryDepth;
	unsigned short X, 
		           Y, 
				   Width, 
				   Height;
	unsigned char  ColorDepth, 
		           Descriptor;

}TGA_header;

#pragma pack(pop,x1)


typedef struct
{	
	unsigned char rgbtBlue;
	unsigned char rgbtGreen;
	unsigned char rgbtRed;

}RGBPoint;




class FileTGA : private Stream
{
	public:

		static FileTGA* GetInstance();
		Texture* LoadTGA(const std::string& file_path);

	private:

		FileTGA() {};
		FileTGA(const FileTGA& copy) {};
		~FileTGA() {};
};


#endif