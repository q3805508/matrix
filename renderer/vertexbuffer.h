#pragma once
#include "renderer_global.h"
#include "rendererdef.h"
#include <QExplicitlySharedDataPointer>

namespace renderer {
	class IHWVertexBuffer;
	class VertexBufferData;
	class RENDERER_EXPORT VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		void createVertexBuffer(VertexFormat format,int count,bool dynamic);

		IHWVertexBuffer* getHardWaterVertexBuffer();

		VertexFormat getVertexFormat();
		int getCount();

		void* lock();
		void unlock();

	private:
		QExplicitlySharedDataPointer<VertexBufferData> d;
	};
}