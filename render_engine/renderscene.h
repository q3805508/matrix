#pragma once
#include <qobject.h>

namespace render_engine {
	class RenderSceneObj;

	class RenderScene : public QObject {
		Q_OBJECT
	public:
		RenderScene();
		~RenderScene();

		void attachObj(RenderSceneObj *pObj);
		void dettachObj(RenderSceneObj *pObj);

		void update();

		void render();
	};

}

