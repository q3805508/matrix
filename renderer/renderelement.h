#pragma once
#include "rendererdef.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "effect.h"

namespace renderer {
	enum RENDERELEMENT_TYPE {RE_MESH,RE_TERRAIN,RE_SKY,RE_END};
	class RENDERER_EXPORT RenderElement {
	public:
		RenderElement()
		{
			ref = 0;
		}
		virtual ~RenderElement() {}
		virtual void preDraw() = 0;
		virtual void draw() = 0;
		virtual void postDraw() = 0;

		virtual RENDERELEMENT_TYPE getRenderElementType ()
		{
			return RE_END;
		}

		void addRef()
		{
			ref ++;
		}
		void release()
		{
			ref --;
			if (ref == 0)
				this->freeRenderElement();
		}

		int getRef() const
		{
			return this->ref;
		}

	protected:
		virtual void freeRenderElement() = 0;
	private:
		int ref;
	};
}