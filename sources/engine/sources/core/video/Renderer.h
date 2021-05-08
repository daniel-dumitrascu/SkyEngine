#ifndef SUPPORTED_RENDERER
#define SUPPORTED_RENDERER

#include "global/GlobalData.h"

class Renderer
{
	public:

		Renderer();
		virtual ~Renderer();

		virtual void InitRenderer(void* screen_handle,
			                      const AspectRatio& aspect_ratio,
			                      const DisplayResolution& resolution) = 0;
		virtual void Render() = 0;

	protected:
	 
		static Renderer* m_handle;
};

#endif