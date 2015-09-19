#pragma once
#include <qobject.h>
#include <qvector.h>
#include <QExplicitlySharedDataPointer>
#include "../math/vector.h"
#include "shaderresource.h"
#include "shader.h"
//#include "texture.h"

namespace renderer {
	class ShaderResource;
	class HWTexture;
	class SubMatData;
	class Texture;
	class CShaderResource;
	class RENDERER_EXPORT SubMaterial : public QObject {
		Q_OBJECT
	public:
		SubMaterial();
		~SubMaterial();

		void setTexture(TEX_SLOT slot,Texture& texture);
		void setTextureInfo(TEX_SLOT slot,TexInfo info);

		void setParameter(QString name,math::vector4 data);
		
		//shader generation
		//void setShaderFlag(QString name,bool enabled);
		//int GetCurrentGenerationFlag();
		Shader getShader();

		ShaderResource* getShaderResource();
		
	private:
		QExplicitlySharedDataPointer<SubMatData> d;
	};

	class RENDERER_EXPORT Material : public QObject {
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