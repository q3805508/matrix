#pragma once
#include "renderer_global.h"
#include "rendererdef.h"
#include <QString>
#include <QExplicitlySharedDataPointer>

namespace renderer {
	class HWTexture;
	class TextureData;
	enum TextureFlag {TFLAG_RENDERTARGET,TFLAG_SRGB};
	class RENDERER_EXPORT Texture {
	public:
		Texture();
		~Texture();


		void loadTexture(QString textureID);
		bool createTexture(int width,int height,TextureType type,
			int nlod,TextureFormat format,int FLAGS);

		QString getTextureID();
		bool isSRGBTexture();
		void setSRGBTexture(bool srgb);

		int getWidth();
		int getHeight();

		TextureType getTextureType();
		TextureFormat getTextureFormat();

		HWTexture* getHardWareTexture();

		void* lock(int face,int lod);
		void unlock();

	private:
		//QExplicitlySharedDataPointer<TextureData> d; 
	};
}