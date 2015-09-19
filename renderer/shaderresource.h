#pragma once
#include "renderer_global.h"
#include "rendererdef.h"
#include "../math/vector.h"
//#include "skyinfo.h"
//#include "camera.h"

namespace renderer {
	class HWTexture;
	struct SkyInfo;
	struct Camera;
	enum TEX_SLOT {
		SLOT_DIFFUSE,
		SLOT_NORMAL,
		SLOT_SPECULAR,
		SLOT_ENV,
		SLOT_DETAIL,
		SLOT_DECAL,
		SLOT_CUSTOM0,
		SLOT_CUSTOM1,
		SLOT_CUSTOM2,
		SLOT_CUSTOM3,
		SLOT_CUSTOM4,
		SLOT_CUSTOM5,
		SLOT_CUSTOM6,
		SLOT_CUSTOM7,
		SLOT_CUSTOM8,
		SLOT_CUSTOM9,
		SLOT_MAX,
	};

	enum ADDR_MODE {
		ADDR_WRAP,
		ADDR_MIRROR,
		ADDR_CLAMP,
		ADDR_BORDER
	};

	enum SAMPLER_MODE {
		SAMPLER_POINT,
		SAMPLER_LINEAR,
		SAMPLER_ANISOTROPIC
	};

	struct TexInfo {
		ADDR_MODE addrMode;
		SAMPLER_MODE samplerMode;
		float tilingU;
		float tilingV;
	};

	struct TexResource {
		HWTexture* texture;
		TexInfo texInfo;
	};

	class RENDERER_EXPORT ShaderResource 
	{
	public:
		virtual ~ShaderResource();
		virtual TexResource getTexture(TEX_SLOT slot) = 0;
		virtual math::vector4 getDiffuse() = 0;
		virtual math::vector4 getSpecular() = 0;
		virtual math::vector4 getEmissive() = 0;
		virtual float getGrow() = 0;
		virtual float getAlpha() = 0;
		virtual float getSpecularShininess() = 0;
		virtual SkyInfo* getSkyInfo() = 0;
		virtual Camera* getCamera() = 0;
		virtual void setSkyInfo(SkyInfo* pInfo) = 0;
		virtual void setCamera(Camera* pCamera) = 0;
	};
}