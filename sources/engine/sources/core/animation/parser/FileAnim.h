#ifndef FILE_ANIM_H
#define FILE_ANIM_H

#include "stream/Stream.h"
#include "../AnimData.h"

class FileAnim : private Stream
{
	public:

		static FileAnim* GetInstance();
		AnimData* ParseFile(const std::string& file_path);

	private:

		FileAnim() {};
		FileAnim(const FileAnim& copy) {};
		~FileAnim() {};

		void ConstrFace(Polygon& polygon, std::vector<vec_2x>& normals, vec_3x& normal_idx,
										  std::vector<vec_2x>& textures, vec_3x& texture_idx);
};


#endif