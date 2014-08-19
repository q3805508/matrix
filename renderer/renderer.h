#ifndef RENDERER_H
#define RENDERER_H

#include "renderer_global.h"
#include <qobject.h>

namespace renderer {
	class RENDERER_EXPORT IRenderer : public QObject
	{
		Q_OBJECT
	public:
		virtual ~IRenderer() {}

		virtual bool init() = 0;
		virtual bool shutdown() = 0;
		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;
		virtual void drawPrimitive() = 0;

		virtual IHWTexture* createHardWareTexture(
			int width,int height,TextureType type,
			nlod,TextureFormat format,int FLAGS) = 0;
		virtual void destroyHardWareTexture(IHWTexture* texture) = 0;

		virtual IHWIndexBuffer* createHardWareIndexBuffer(int count,bool dynamic) = 0;
		virtual void destroyHardWareIndexBuffer(IHWIndexBuffer* indexBuffer);
	private:

	};
}

#endif // RENDERER_H
