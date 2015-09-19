#pragma once
#include "renderer_global.h"
#include <qobject.h>
#include <qstringlist.h>
#include <qvector.h>
#include <qmap.h>
#include <QtXml/qdom.h>
#include <QExplicitlySharedDataPointer>
#include "rendererdef.h"
#include "..\math\vector.h"
//#include "shader.h"

namespace renderer {
	class HWShader;
	class EffectData;


	class RENDERER_EXPORT Pass
	{//: public QObject {
		//Q_OBJECT
	public:
		Pass();
		~Pass();

		QString getPassName();

		int getStateMask();
		int getStateFlag();


		//Shader getShader();

		bool loadPassFromXML(QDomElement* node);

	private:
		//Shader shader;
		int stateMask;
		int stateFlag;
		QString name;
	};

	class RENDERER_EXPORT Technique {//: public QObject {
		//Q_OBJECT
	public:
		Technique();
		~Technique();

		QString getTechName();

		int getPassCount();
		Pass* getPass(QString name);
		Pass* getPass(int index);

		bool loadTechniqueFromXML(QDomElement* node);
	private:
		QString name;
		//QVector<Pass> pass;
	};



	class RENDERER_EXPORT Effect {//: public QObject {
		//Q_OBJECT

	public:
		Effect(QString name);
		~Effect();

		int getTechniqueCount();
		Technique* getTechnique(QString name);
		Technique* getTechnique(int index);

		QString getEffectName();

		//const QVector<CustomEffectParam>& getCustomParameters() const;
		//math::vector4 getCustomParameterValue(QString name) const;
		//ShaderParamType getCustomParameterType(QString name) const;
		//void setCustomParameterValue(math::vector4 data);

		//const QVector<GenFlag>& getGenerageFlags() const;

	public://
		bool loadEffectFromXML(QDomElement* node);

	private:
		//QExplicitlySharedDataPointer<EffectData> d;
	};
}