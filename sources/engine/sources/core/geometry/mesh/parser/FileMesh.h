#ifndef FILE_XML_H
#define FILE_XML_H

#include "stream/Stream.h"
#include "../WireFrame.h"
#include "../../../logging/Logging.h"

class FileMesh : private Stream
{
	public:

		static FileMesh* GetInstance();
		WireFrame* ParseFile(const std::string& file_path);

	private:

		FileMesh() : log("FileMesh") {};
		FileMesh(const FileMesh& copy) : log("FileMesh") {};
		~FileMesh() {};

		void ConstrFace(Polygon& polygon, std::vector<vec_2x>& normals, vec_3x& normal_idx,
										  std::vector<vec_2x>& textures, vec_3x& texture_idx);

	private:

		Logging log;
};


#endif