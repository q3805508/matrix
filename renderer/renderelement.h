#pragma once
#include "rendererdef.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "effect.h"

namespace renderer {

	class IRenderElement {
		virtual ~IRenderElement() {}
		virtual void preDraw() = 0;
		virtual void draw() = 0;
		virtual void postDraw() = 0;
	};
}