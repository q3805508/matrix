#pragma once
#include "rendererdef.h"
#include "hwresource.h"

namespace renderer {

	class HWTexture : public HWResource {
	public:
		virtual ~HWTexture();

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;

		virtual TextureType getTextureType() = 0;
		virtual TextureFormat getTextureFormat() = 0;

		virtual void* lock(int face,int lod) = 0;
		virtual void unlock() = 0;
	};
}