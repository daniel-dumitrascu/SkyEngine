#include "FileAnim.h"
#include <tinyxml2.h>
#include "math/Vector.h"
#include "geometry/Polygon.h"

FileAnim* FileAnim::GetInstance()
{
	static FileAnim instance;
	return &instance;
}

AnimData* FileAnim::ParseFile(const std::string& file_path)
{
	AnimData* data = NULL;

	/* Open the file */
	Open(file_path, std::ios::in | std::ios::binary);

	/* Read the whole file into memory */
	std::string model_buffer(m_file_size, ' ');
	Read(&model_buffer[0], m_file_size);

	/* Close the file stream */
	Close();

	/* Parse the xml document */
	tinyxml2::XMLDocument stream_doc;
	int result = stream_doc.Parse(model_buffer.c_str());

	if (result != tinyxml2::XML_SUCCESS)
		return NULL;

	tinyxml2::XMLElement* Animation_elem = stream_doc.FirstChildElement("Animation");

	if (Animation_elem)
	{
		int frames_timer = 0;

		result += Animation_elem->QueryIntAttribute("timer", &frames_timer);

		if (result != tinyxml2::XML_SUCCESS)
			return NULL;

		data = new AnimData;
		data->SetTimmer(frames_timer);

		vec_2x elem_attribs;
		std::vector<vec_2x> normals, textures;

		tinyxml2::XMLElement* Frame_elem = Animation_elem->FirstChildElement("Frame");

		while (Frame_elem != NULL)
		{
			if (Frame_elem)
			{
				WireFrame* frame = new WireFrame;
				tinyxml2::XMLElement* Normals_elem = Frame_elem->FirstChildElement("Normals");

				if (Normals_elem)
				{
					int normals_nr = 0;
					if (Normals_elem->QueryIntAttribute("number", &normals_nr) != tinyxml2::XML_SUCCESS)
						return NULL;

					normals.reserve(normals_nr);
					frame->SetNormalsNr(normals_nr);

					for (tinyxml2::XMLElement* e = Normals_elem->FirstChildElement("Normal"); e != NULL; e = e->NextSiblingElement("Normal"))
					{
						/* Get the normal values */
						result  = e->QueryFloatAttribute("X", &elem_attribs.elem[0]);
						result += e->QueryFloatAttribute("Y", &elem_attribs.elem[1]);

						if (result != tinyxml2::XML_SUCCESS)
							return NULL;

						normals.push_back(elem_attribs);
					}
				}
				else
					return NULL;

				tinyxml2::XMLElement* Textures_elem = Frame_elem->FirstChildElement("Textures");

				if (Textures_elem)
				{
					int texcoord_nr = 0;
					if (Textures_elem->QueryIntAttribute("number", &texcoord_nr) != tinyxml2::XML_SUCCESS)
						return NULL;

					textures.reserve(texcoord_nr);
					frame->SetTexcoordNr(texcoord_nr);

					for (tinyxml2::XMLElement* e = Textures_elem->FirstChildElement("Texcoord"); e != NULL; e = e->NextSiblingElement("Texcoord"))
					{
						/* Get the normal values */
						result  = e->QueryFloatAttribute("U", &elem_attribs.elem[0]);
						result += e->QueryFloatAttribute("V", &elem_attribs.elem[1]);

						if (result != tinyxml2::XML_SUCCESS)
							return NULL;

						textures.push_back(elem_attribs);
					}
				}
				else
					return NULL;

				tinyxml2::XMLElement* Polygons_elem = Frame_elem->FirstChildElement("Polygons");

				if (Polygons_elem)
				{
					int poly = 0;
					if (Polygons_elem->QueryIntAttribute("number", &poly) != tinyxml2::XML_SUCCESS)
						return NULL;

					frame->SetPolyNr(poly);

					vec_3x normal_idx, texture_idx;
					Polygon polygon;

					for (tinyxml2::XMLElement* e = Polygons_elem->FirstChildElement("Polygon"); e != NULL; e = e->NextSiblingElement("Polygon"))
					{
						/* Get the polygon indices */
						result += e->QueryFloatAttribute("TexA", &texture_idx.elem[0]);
						result += e->QueryFloatAttribute("NormA", &normal_idx.elem[0]);
						result += e->QueryFloatAttribute("TexB", &texture_idx.elem[1]);
						result += e->QueryFloatAttribute("NormB", &normal_idx.elem[1]);
						result += e->QueryFloatAttribute("TexC", &texture_idx.elem[2]);
						result += e->QueryFloatAttribute("NormC", &normal_idx.elem[2]);

						if (result != tinyxml2::XML_SUCCESS)
							return NULL;

						ConstrFace(polygon, normals, normal_idx, textures, texture_idx);
						frame->AddPolygon(polygon);
					}
				}
				else
					return NULL;

				data->PushFrame(frame);
 
				normals.clear(); 
				textures.clear();
			}
			else
				return NULL;

			Frame_elem = Frame_elem->NextSiblingElement("Frame");
		}

		tinyxml2::XMLElement* States_elem = Animation_elem->NextSiblingElement("States");

		if (States_elem)
		{
			int result = 0;
			int start, end;

			tinyxml2::XMLElement* State_elem = States_elem->FirstChildElement("State");

			while (State_elem != NULL)
			{
				result += State_elem->QueryIntAttribute("start", &start);
				result += State_elem->QueryIntAttribute("end", &end);

				data->PushStateLimit(start, end);

				State_elem = State_elem->NextSiblingElement("State");
			}
		}
	}
	
	return data;
}

void FileAnim::ConstrFace(Polygon& polygon, std::vector<vec_2x>& normals, vec_3x& normal_idx,
											std::vector<vec_2x>& textures, vec_3x& texture_idx)
{
	for (int i = 0; i < 3; ++i)
	{
		polygon.vertex[i].texture.elem[0] = textures[texture_idx.elem[i] - 1].elem[0];
		polygon.vertex[i].normals.elem[0] = normals[normal_idx.elem[i] - 1].elem[0];

		polygon.vertex[i].texture.elem[1] = textures[texture_idx.elem[i] - 1].elem[1];
		polygon.vertex[i].normals.elem[1] = normals[normal_idx.elem[i] - 1].elem[1];
	}
}