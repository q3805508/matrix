#pragma once
#include <qobject.h>
#include <qvector.h>
#include <QExplicitlySharedDataPointer>
#include "texture.h"

namespace renderer {
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

	class IHWTexture;
	class SubMatData;
	class SubMaterial : public QObject {
		Q_OBJECT
	public:
		SubMaterial();
		~SubMaterial();

		void setTexture(TEX_SLOT slot,Texture texture);
		void setTextureInfo(TEX_SLOT slot,TexInfo info);

		void setParameter(QString name,math::vector4 data);
		
		//shader generation
		void setShaderFlag(QString name,bool enabled);
		int GetCurrentGenerationFlag();
		
	private:
		QExplicitlySharedDataPointer<SubMatData> d;
	};

	class Material : public QObject {
		Q_OBJECT
	public:
		Material();
		Material(const Material& src);
		~Material();

		void detach();

		void setSubMatCount(int n);
		void setSubMaterial(int i,const SubMaterial& subMat);

		const QVector<SubMaterial>& getSubMaterials();

	private:
		QVector<SubMaterial> subMats;
	};
}