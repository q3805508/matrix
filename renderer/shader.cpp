#include "shader.h"
#include <qvector.h>
#include <qshareddata.h>
#include <QtXml/QDomDocument>
#include "../resmgr/resmgr.h"
#include "renderer.h"
#include "hwshader.h"
#include "rendermgr.h"
#include "../common/strutility.h"
#include "shaderdata.h"

namespace renderer {
	
	static const char* XML_PARAM_LIST_NAME = "CParams";
	static const char* XML_PARAM_NODE_NAME = "CParam";
	static const char* XML_FLAG_LIST_NAME = "ShaderFlags";
	static const char* XML_FLAG_NODE_NAME = "ShaderFlag";
	static const char* XML_TEXTURE_LIST_NAME = "Textures";
	static const char* XML_TEXTURE_NODE_NAME = "Texture";
	//static const char* XML_INPUT_NODE_NAME = "Input";
	//static const char* XML_OUTPUT_NODE_NAME = "Output";
	static const char* XML_VSCODE_NAME = "VSCode";
	static const char* XML_PSCODE_NAME = "PSCode";

	static const char* XML_ATTR_NAME = "name";
	static const char* XML_ATTR_SHADERTYPE = "shaderType";
	static const char* XML_ATTR_DEFVALUE = "default";
	static const char* XML_ATTR_SLOT = "slot";
	static const char* XML_ATTR_TEXTUERTYPE = "type";

	ShaderParamType getShaderParamTypeFromStr(const char* str)
	{
		if (strcmp(str,"float") == 0)
		{
			return ST_FLOAT;
		}
		if (strcmp(str,"float2") == 0)
		{
			return ST_FLOAT2;
		}
		if (strcmp(str,"float3") == 0)
		{
			return ST_FLOAT3;
		}
		if (strcmp(str,"float4") == 0)
		{
			return ST_FLOAT4;
		}
		if (strcmp(str,"float3x3") == 0)
		{
			return ST_FLOAT3x3;
		}
		if (strcmp(str,"float4x4") == 0)
		{
			return ST_FLOAT4x4;
		}
		if (strcmp(str,"float4x3") == 0)
		{
			return ST_FLOAT4x3;
		}
		return ST_END;
	}
	CustomShaderParam loadCustomShaderParamFormXML(const QDomElement* pElement)
	{
		QString name = pElement->attribute(XML_ATTR_NAME);
		QString shaderType = pElement->attribute(XML_ATTR_SHADERTYPE);
		ShaderParamType type = getShaderParamTypeFromStr(shaderType.toAscii());
		if (type != ST_FLOAT || type != ST_FLOAT2
			|| type != ST_FLOAT3 || type != ST_FLOAT4)
			return CustomShaderParam();

		QString defaultValue = pElement->attribute(XML_ATTR_DEFVALUE);
		if (!defaultValue.length())
			return CustomShaderParam();
		math::vector4 defvalue = cn::getVector4FromStr(defaultValue.toAscii());
		CustomShaderParam cparam;
		cparam.name = name;
		cparam.type = type;
		cparam.default = defvalue;
		return cparam;
	}

	bool Shader::loadShader(const QString resID)
	{
		QSharedPointer<cn::Futrure<QByteArray>> pData 
			= resmgr::theResMgr->getResource(resID);
		QByteArray* data = pData->getResult().data();
		if (!data->length())
			return false;


		QDomDocument shaderDoc(*data);
		//do not care about shader flags yet

		QVector<CustomShaderParam> paramsVec;
		QDomElement paramsList = shaderDoc.firstChildElement(XML_PARAM_LIST_NAME);
		if (!paramsList.isNull())
		{
			//load all params
			QDomNodeList params = paramsList.elementsByTagName(XML_PARAM_NODE_NAME);

			for (int i = 0 ; i < params.length(); i++)
			{
				QDomElement paramElement = params.item(i).toElement();
				CustomShaderParam param = loadCustomShaderParamFormXML(&paramElement);
				paramsVec.push_back(param);
			}
		}
		QDomElement textureList = shaderDoc.firstChildElement(XML_TEXTURE_LIST_NAME);
		//if (!textureList.isNull())
		//{
		//	QDomNodeList textures = textureList.elementsByTagName(XML_TEXTURE_NODE_NAME);
		//}

		QDomElement vsCode = shaderDoc.firstChildElement(XML_VSCODE_NAME);
		QDomElement psCode = shaderDoc.firstChildElement(XML_PSCODE_NAME);

		QString shaderStrVS = vsCode.text();
		QString shaderStrPS = psCode.text();

		IRenderer* pRenderer = theRenderMgr->getRenderer();
		QVector<QString> macro;
		this->d->vsShader = pRenderer->createHardWareShader(shaderStrVS.toAscii(),shaderStrVS.length(),"vs_main",macro,renderer::SHADER_VS);
		this->d->psShader = pRenderer->createHardWareShader(shaderStrPS.toAscii(),shaderStrPS.length(),"ps_main",macro,renderer::SHADER_PS);
		this->d->customParams = paramsVec;
		return true;
	}

	Shader::Shader()
	{

	}

	Shader::~Shader()
	{

	}

	HWShader* Shader::getVSShader()
	{
		return NULL;
	}

	HWShader* Shader::getPSShader()
	{
		return NULL;
	}

	const QVector<CustomShaderParam>& Shader::getCustomParameters() const
	{
		return this->d->customParams;
	}

	math::vector4 Shader::getCustomParameterValue(QString name) const
	{
		return math::vector4(0,0,0,0);
	}

	ShaderParamType Shader::getCustomParameterType(QString name) const
	{
		return ST_FLOAT;
	}

	void setCustomParameterValue(math::vector4 data)
	{

	}

	const QVector<GenFlag>& Shader::getGenerageFlags() const
	{
		return this->d->genFlags;
	}


}

