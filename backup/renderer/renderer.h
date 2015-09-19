#pragma once
#include "module.h"
#include <qobject.h>

namespace renderer {

	class RENDERER_EXPORT Renderer : public QObject {
		Q_OBJECT
	public:
		Renderer(){}
		~Renderer(){}
	};

}