#pragma once
#include <qobject.h>

namespace renderer {
	class RenderSceneObj : public QObject {
		Q_OBJECT
	public:
		RenderSceneObj();
		~RenderSceneObj();


	};
}