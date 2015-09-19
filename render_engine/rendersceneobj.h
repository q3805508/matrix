#pragma once
#include <qobject.h>
#include "../math/aabb.h"
#include "../math/matrix.h"

namespace render_engine {
	class RenderSceneObj : public QObject {
		Q_OBJECT
	public:
		RenderSceneObj();
		virtual ~RenderSceneObj();

		enum RenderObjType{Light,Camera,Mesh,Water,Terrain};

		const math::AABB& getAABB();

		RenderObjType getType();

		//void setWorldTransform(const math::matrix4x4& transform);
		const math::matrix4x4& getWorldTransform();

		virtual void update();

	protected:
		math::AABB aabb;
		RenderObjType type;
		math::matrix4x4 worldTM;
	};
}