#include "material.h"
#include "../renderer/shaderdata.h"
#include "../renderer/shader.h"
#include "qshareddata.h"
#include "../renderer/texture.h"
//#include "effect.h"

namespace renderer {
	

	class CShaderResource : public ShaderResource {
	public:
		CShaderResource(SubMatData* pSubMatData);

		TexResource getTexture(TEX_SLOT slot);
		math::vector4 getDiffuse();
		math::vector4 getSpecular();
		math::vector4 getEmissive();
		float getGrow();
		float getAlpha();
		float getSpecularShininess();
		SkyInfo* getSkyInfo();
		Camera* getCamera();

		void setSkyInfo(SkyInfo* pInfo);
		void setCamera(Camera* pCamera);

	private:
		SubMatData* pSubMatData;
		SkyInfo* pSkyInfo;
		Camera* pCamera;
	};

	class SubMatData : public QSharedData {
	public:
		SubMatData()
			:shaderResource(this)
		{}
		SubMatData(const SubMatData& src)
			:shaderResource(this)
		{}
		~SubMatData()
		{}

		TexResource getTexture(TEX_SLOT slot);
		math::vector4 getDiffuse();
		math::vector4 getSpecular();
		math::vector4 getEmissive();
		float getGrow();
		float getAlpha();
		float getSpecularShininess();

		CShaderResource shaderResource;
		Texture texture[renderer::SLOT_MAX];
		TexInfo texInfo[renderer::SLOT_MAX];
		math::vector4 diffuse;
		math::vector4 specular;
		math::vector4 emissive;
		float grow;
		float alpha;
		float shininess;
		friend class SubMaterial;
		renderer::Shader shader;
	};

	TexResource SubMatData::getTexture(TEX_SLOT slot)
	{
		TexResource res;
		res.texInfo = this->texInfo[slot];
		res.texture = this->texture[slot].getHardWareTexture();
		return res;
	}
	math::vector4 SubMatData::getDiffuse()
	{
		return this->diffuse;
	}

	math::vector4 SubMatData::getSpecular()
	{
		return this->specular;
	}

	math::vector4 SubMatData::getEmissive()
	{
		return this->emissive;
	}

	float SubMatData::getGrow()
	{
		return this->grow;
	}

	float SubMatData::getAlpha()
	{
		return this->alpha;
	}

	float SubMatData::getSpecularShininess()
	{
		return this->shininess;
	}

	SubMaterial::SubMaterial()
	{

	}
	SubMaterial::~SubMaterial()
	{

	}

	void SubMaterial::setTexture(TEX_SLOT slot,Texture& texture)
	{
		this->d->texture[slot] = texture;
	}

	void SubMaterial::setTextureInfo(TEX_SLOT slot,TexInfo info)
	{
		this->d->texInfo[slot] = info;
	}

	void SubMaterial::setParameter(QString name,math::vector4 data)
	{
		static QString DiffuseName = "diffuse";
		static QString SpecularName = "specular";
		static QString EmissiveName = "emissive";
		static QString GrowName = "grow";
		static QString AlphaName = "alpha";
		if (name == DiffuseName)
		{
			this->d->diffuse = data;
		} else if (name == SpecularName)
		{
			this->d->specular = data;
		}else if (name == EmissiveName)
		{
			this->d->emissive = data;
		}else if (name == GrowName)
		{
			this->d->grow = data.x;
		}else if (name == AlphaName)
		{
			this->d->alpha = data.x;
		}
	}

	Shader SubMaterial::getShader()
	{
		return this->d->shader;
	}

	ShaderResource* SubMaterial::getShaderResource()
	{
		return &this->d->shaderResource;
	}


	TexResource CShaderResource::getTexture(TEX_SLOT slot)
	{
		return this->pSubMatData->getTexture(slot);
	}
	math::vector4 CShaderResource::getDiffuse()
	{
		return this->pSubMatData->getDiffuse();
	}

	math::vector4 CShaderResource::getSpecular()
	{
		return this->pSubMatData->getSpecular();
	}

	math::vector4 CShaderResource::getEmissive()
	{
		return this->pSubMatData->getEmissive();
	}

	float CShaderResource::getGrow()
	{
		return this->pSubMatData->getGrow();
	}

	float CShaderResource::getAlpha()
	{
		return this->pSubMatData->getAlpha();
	}

	float CShaderResource::getSpecularShininess()
	{
		return this->pSubMatData->getSpecularShininess();
	}

	SkyInfo* CShaderResource::getSkyInfo()
	{
		return this->pSkyInfo;
	}

	Camera* CShaderResource::getCamera()
	{
		return this->pCamera;
	}

	void CShaderResource::setSkyInfo(SkyInfo* pInfo)
	{
		this->pSkyInfo = pInfo;
	}

	void CShaderResource::setCamera(Camera* pCamera)
	{
		this->pCamera = pCamera;
	}
}