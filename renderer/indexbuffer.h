#pragma once
#include "renderer_global.h"
#include <QExplicitlySharedDataPointer>

namespace renderer {
	class IHWIndexBuffer;
	class IndexBufferData;
	class RENDERER_EXPORT IndexBuffer {
	public:
		IndexBuffer();
		~IndexBuffer();

		void createIndexBuffer(int count,bool dynamic);

		int getCount();

		IHWIndexBuffer* getHWIndexBuffer();

	private:
		QExplicitlySharedDataPointer<IndexBufferData> d;
	};

	class IndexBufferData: public QSharedData {
		IndexBufferData()
		{

		}

		IndexBufferData(const IndexBufferData& src)
		{

		}
	};
}