#pragma once
#include "rendererdef.h"


namespace renderer {

	class IHWTexture {
	public:
		virtual ~IHWTexture();

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;

		virtual TextureType getTextureType() = 0;
		virtual TextureFormat getTextureFormat() = 0;

		virtual void* lock(int face,int lod) = 0;
		virtual void unlock() = 0;
	};
}