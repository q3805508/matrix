#pragma once
#include "renderer_global.h"
#include "rendererdef.h"
#include <qvector.h>
#include <qstring.h>
#include "QExplicitlySharedDataPointer"
#include "hwshader.h"

namespace renderer {
	class ShaderData;
	class HWShader;

	struct CustomShaderParam {
		QString name;
		ShaderParamType type;
		math::vector4 default;
	};

	struct GenFlag {
		QString name;
		QString desc;
		int mask;
	};

	class RENDERER_EXPORT Shader {
	public:
		Shader();
		~Shader();

		HWShader* getVSShader();
		HWShader* getPSShader();


		const QVector<CustomShaderParam>& getCustomParameters() const;
		math::vector4 getCustomParameterValue(QString name) const;
		ShaderParamType getCustomParameterType(QString name) const;
		void setCustomParameterValue(math::vector4 data);

		const QVector<GenFlag>& getGenerageFlags() const;

		bool loadShader(const QString resID);

	private:
		QExplicitlySharedDataPointer<ShaderData> d;
	};

	class ShaderData : public QSharedData{
	public:
		ShaderData()
			:vsShader(NULL)
			,psShader(NULL)
		{

		}
		ShaderData(const ShaderData & src)
		{
			this->customParams = src.customParams;
			this->genFlags = src.genFlags;
			this->vsShader = src.vsShader;
			this->psShader = src.psShader;
			this->vsShader->addReference();
			this->psShader->addReference();
		}
		~ShaderData()
		{
			this->vsShader->removeReference();
			this->psShader->removeReference();
			this->vsShader = NULL;
			this->psShader = NULL;
		}

		QVector<CustomShaderParam> customParams;
		QVector<GenFlag> genFlags;
		HWShader* vsShader;
		HWShader* psShader;
	};
}