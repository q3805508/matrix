#pragma once
#include <qobject.h>
#include <qstringlist.h>
#include "rendererdef.h"
#include <qvector.h>
#include "..\math\vector.h"

namespace renderer {
	class IHWShader;

	struct GenFlag {
		QString name;
		QString desc;
		int mask;
	};

	class Pass {//: public QObject {
		//Q_OBJECT
	public:
		Pass();
		~Pass();

		QString name();

		int getStateMask();
		int getStateFlag();


		IHWShader* getVSShader(int flags);
		IHWShader* getPSShader(int flags);
	};

	class Technique {//: public QObject {
		//Q_OBJECT
	public:
		Technique();
		~Technique();

		QString name();


		int getPassCount();
		Pass* getPass(QString name);
		Pass* getPass(int index);

	};

	class Effect {//: public QObject {
		//Q_OBJECT

	public:
		Effect();
		~Effect();

		struct CustomParameter {
			QString name;
			ShaderType type;
			math::vector4 default;
		};

		int getTechniqueCount();
		Technique* getTechnique(QString name);
		Technique* getTechnique(int index);

		QString name();

		const QVector<CustomParameter>& getCustomParameters() const;
		math::vector4 getCustomParameterValue(QString name) const;
		ShaderType getCustomParameterType(QString name) const;
		void setCustomParameterValue(math::vector4 data);

		const QVector<GenFlag>& getGenerageFlags() const;

	};
}