#include "FileMesh.h"
#include <tinyxml2.h>

FileMesh* FileMesh::GetInstance()
{
	static FileMesh instance;
	return &instance;
}

WireFrame* FileMesh::ParseFile(const std::string& file_path)
{
	WireFrame* mesh = nullptr;

	/* Open the file */
	if (Open(file_path, std::ios::in | std::ios::binary))
	{
		mesh = new WireFrame;

		/* Read the whole file into memory */
		std::string model_buffer(m_file_size, ' ');
		Read(&model_buffer[0], m_file_size);

		/* Close the file stream */
		Close();

		/* Parse the xml document */
		tinyxml2::XMLDocument stream_doc;
		int result = stream_doc.Parse(model_buffer.c_str());

		if (result != tinyxml2::XML_SUCCESS)
			return nullptr;

		tinyxml2::XMLElement* ModelMapping_elem = stream_doc.FirstChildElement("ModelMapping");

		if (ModelMapping_elem)
		{
			vec_2x elem_attribs;
			std::vector<vec_2x> normals, textures;

			tinyxml2::XMLElement* MeshCoords_elem = ModelMapping_elem->FirstChildElement("MeshCoords");

			if (MeshCoords_elem)
			{
				int normals_nr = 0;
				if (MeshCoords_elem->QueryIntAttribute("number", &normals_nr) != tinyxml2::XML_SUCCESS)
					return nullptr;

				normals.reserve(normals_nr);
				mesh->SetNormalsNr(normals_nr);

				for (tinyxml2::XMLElement* e = MeshCoords_elem->FirstChildElement("MeshCoord"); e != nullptr; e = e->NextSiblingElement("MeshCoord"))
				{
					/* Get the normal values */
					result = e->QueryFloatAttribute("X", &elem_attribs.elem[0]);
					result += e->QueryFloatAttribute("Y", &elem_attribs.elem[1]);

					if (result != tinyxml2::XML_SUCCESS)
						return nullptr;

					normals.push_back(elem_attribs);
				}
			}
			else
				return nullptr;

			tinyxml2::XMLElement* Textures_elem = ModelMapping_elem->FirstChildElement("Textures");

			if (Textures_elem)
			{
				int texcoord_nr =0;
				if (Textures_elem->QueryIntAttribute("number", &texcoord_nr) != tinyxml2::XML_SUCCESS)
					return nullptr;

				textures.reserve(texcoord_nr);
				mesh->SetTexcoordNr(texcoord_nr);

				for (tinyxml2::XMLElement* e = Textures_elem->FirstChildElement("Texcoord"); e != nullptr; e = e->NextSiblingElement("Texcoord"))
				{
					/* Get the normal values */
					result = e->QueryFloatAttribute("U", &elem_attribs.elem[0]);
					result += e->QueryFloatAttribute("V", &elem_attribs.elem[1]);

					if (result != tinyxml2::XML_SUCCESS)
						return nullptr;

					textures.push_back(elem_attribs);
				}
			}
			else
				return nullptr;

			tinyxml2::XMLElement* Polygons_elem = ModelMapping_elem->FirstChildElement("Polygons");

			if (Polygons_elem)
			{
				int poly_nr = 0;
				if (Polygons_elem->QueryIntAttribute("number", &poly_nr) != tinyxml2::XML_SUCCESS)
					return nullptr;

				mesh->SetPolyNr(poly_nr);

				vec_3x normal_idx, texture_idx;
				Polygon polygon;

				for (tinyxml2::XMLElement* e = Polygons_elem->FirstChildElement("Polygon"); e != nullptr; e = e->NextSiblingElement("Polygon"))
				{
					/* Get the polygon indices */
					result += e->QueryFloatAttribute("TexA", &texture_idx.elem[0]);
					result += e->QueryFloatAttribute("NormA", &normal_idx.elem[0]);

					result += e->QueryFloatAttribute("TexB", &texture_idx.elem[1]);
					result += e->QueryFloatAttribute("NormB", &normal_idx.elem[1]);

					result += e->QueryFloatAttribute("TexC", &texture_idx.elem[2]);
					result += e->QueryFloatAttribute("NormC", &normal_idx.elem[2]);

					if (result != tinyxml2::XML_SUCCESS)
						return nullptr;

					ConstrFace(polygon, normals, normal_idx, textures, texture_idx);
					mesh->AddPolygon(polygon);
				}
			}
			else
				return nullptr;
		}
	}

	return mesh;
}

void FileMesh::ConstrFace(Polygon& polygon, std::vector<vec_2x>& normals, vec_3x& normal_idx,
								            std::vector<vec_2x>& textures, vec_3x& texture_idx)
{
	const int faceCoordCount = 3;

	// We want to construct the face only 
	// if mesh and texture coords are valid
	if (!normals.empty() && normals.size() >= faceCoordCount && 
		!textures.empty() && textures.size() >= faceCoordCount)
	{
		for (int i = 0; i < faceCoordCount; ++i)
		{
			polygon.vertex[i].texture.elem[0] = textures[texture_idx.elem[i] - 1].elem[0];
			polygon.vertex[i].normals.elem[0] = normals[normal_idx.elem[i] - 1].elem[0];

			polygon.vertex[i].texture.elem[1] = textures[texture_idx.elem[i] - 1].elem[1];
			polygon.vertex[i].normals.elem[1] = normals[normal_idx.elem[i] - 1].elem[1];
		}
	}
	else
	{
		log.message("Can't construct the face because either the mesh or texture coordonates are invalid.", Logging::MSG_ERROR);
	}
}