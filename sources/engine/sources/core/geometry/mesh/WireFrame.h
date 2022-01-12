#ifndef MESH_H
#define MESH_H

#include "../Polygon.h"
#include <vector>
#include <memory>

class WireFrame
{
	public:

		WireFrame();
		~WireFrame();

		WireFrame& operator=(WireFrame& copy);

		void SetNormalsNr(unsigned int normalsNr) { m_normalsNr = normalsNr; }
		unsigned int GetNormalsNr() const { return m_normalsNr; }
		void SetTexcoordNr(unsigned int texcoordNr) { m_texcoordNr = texcoordNr; }
		unsigned int GetTexcoordNr() const { return m_texcoordNr; }
		void SetPolyNr(unsigned int polyNr);
		unsigned int GetPolyNr() const { return m_polyNr; }
		unsigned int GetGeometryCount() const { return m_geometryCount; }
		unsigned short* GetIndices() const  { return m_indices.get(); }
		void SetVBOVert(unsigned int vboVert) { m_vboVert = vboVert; }
		unsigned int GetVBOVert() const { return m_vboVert; }
		void SetVBOIndx(unsigned int vboIndx) { m_vboIndx = vboIndx; }
		unsigned int GetVBOIndx() const { return m_vboIndx; }
		void SetGeometryInGPU(bool geometryInGPU) { m_isGeometryInGpu = geometryInGPU; }
		bool IsGeometryInGPU() const { return m_isGeometryInGpu; }
		void AddPolygon(Polygon& poly) { m_polygons.push_back(poly); }
		const float* GetModelStartData() const { return &(m_polygons[0].vertex[0].normals.elem[0]); }
		const Polygon* GetPolygonAtIndex(int index) const;

	private:

		unsigned int m_normalsNr;		// Number of normals
		unsigned int m_texcoordNr;		// Number of texture coordinates
		unsigned int m_polyNr;			// Number of polygons //TODO this needs to be removed from here because he can take this info from m_polygons
		unsigned int m_geometryCount;	// Total size of vertices in each face	
		std::unique_ptr<unsigned short[]>  m_indices; // Model indices
		unsigned int m_vboVert;			// VBO for mesh vertices
		unsigned int m_vboIndx;			// VBO for mesh indices
		bool m_isGeometryInGpu;

		std::vector<Polygon>  m_polygons;
};

#endif