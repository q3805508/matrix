#include <qshareddata.h>
//#include "../src/texturedata.h"
#include "texture.h"

namespace renderer {


	/*TextureData::TextureData()
	{

	}

	Texture::Texture()
	{

	}

	TextureData(const TextureData& src)
	{

	}*/

	Texture::~Texture()
	{

	}


	void Texture::loadTexture(QString textureID)
	{

	}

	bool Texture::createTexture(int width,int height,TextureType type, int nlod,TextureFormat format,int FLAGS)
	{
		return false;
	}

	QString Texture::getTextureID()
	{
		return QString();
	}

	bool Texture::isSRGBTexture()
	{
		return false;
	}

	void Texture::setSRGBTexture(bool srgb)
	{

	}

	int Texture::getWidth()
	{
		return -1;
	}

	int Texture::getHeight()
	{
		return -1;
	}

	TextureType Texture::getTextureType()
	{
		return TT_END;
	}

	TextureFormat Texture::getTextureFormat()
	{
		return TF_END;
	}

	HWTexture* Texture::getHardWareTexture()
	{
		return NULL;
	}

	void* Texture::lock(int face,int lod)
	{
		return NULL;
	}

	void Texture::unlock()
	{

	}
}