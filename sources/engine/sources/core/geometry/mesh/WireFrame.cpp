#include "WireFrame.h"


WireFrame::WireFrame() : m_normalsNr(0), 
						 m_texcoordNr(0),
						 m_polyNr(0), 
						 m_geometryCount(0), 
						 m_indices(NULL), 
						 m_vboVert(0), 
						 m_vboIndx(0),
						 m_isGeometryInGpu(false)
{

}

WireFrame::~WireFrame()
{
	delete[] m_indices;
	m_polygons.clear();
}

WireFrame& WireFrame::operator = (WireFrame& copy)
{
	this->m_normalsNr	  = copy.m_normalsNr;
	this->m_texcoordNr	  = copy.m_texcoordNr;
	this->m_polyNr		  = copy.m_polyNr;
	this->m_geometryCount = copy.m_geometryCount;

	delete[] this->m_indices;
	this->m_indices = new unsigned short[m_geometryCount];
	for (int i = 0; i < m_geometryCount; i++)
		this->m_indices[i] = copy.m_indices[i];

	this->m_vboVert			= copy.m_vboVert;
	this->m_vboIndx			= copy.m_vboIndx;
	this->m_isGeometryInGpu = copy.m_isGeometryInGpu;

	this->m_polygons.clear();
	this->m_polygons = copy.m_polygons;

	return *this;
}

void WireFrame::SetPolyNr(unsigned int polyNr)
{
	m_polyNr = polyNr;
	m_geometryCount = TRIANGLE_FACE * m_polyNr;

	if (m_indices)
		delete[] m_indices;

	m_indices = (unsigned short*) new unsigned short[m_geometryCount];

	for (int i = 0; i < m_geometryCount; ++i)
		m_indices[i] = i;
}

const Polygon* WireFrame::GetPolygonAtIndex(int index) const
{
	const Polygon* poly = NULL;

	if (index >= 0 && index < GetPolyNr())
		poly = &m_polygons[index];

	return poly;
}