#pragma once
#include "renderer_global.h"
#include "rendererdef.h"
#include <QExplicitlySharedDataPointer>

namespace renderer {
	class HWVertexBuffer;
	class VertexBufferData;
	class RENDERER_EXPORT VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		void createVertexBuffer(VertexFormat format,int count,bool dynamic);

		HWVertexBuffer* getHardWaterVertexBuffer();

		VertexFormat getVertexFormat();
		int getCount();

		void* lock();
		void unlock();

	private:
		QExplicitlySharedDataPointer<VertexBufferData> d;
	};
	class VertexBufferData : public QSharedData {
	public:
		VertexBufferData()
		{

		}
		VertexBufferData(const VertexBufferData& src)
		{

		}
	};
}