#include "effect.h"
#include <QSharedData>

namespace renderer {
	class EffectData : public QSharedData {

	public:

		EffectData();
		~EffectData();
		EffectData(const EffectData& src);

		QString name;
		QVector<Technique> techs;
		//QVector<CustomShaderParam> customParams;
		//QVector<GenFlag> genFlags;
	};



	bool Effect::loadEffectFromXML(QDomElement* node)
	{
		return true;
	}
}