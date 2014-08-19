#pragma once
#include "rendererdef.h"

namespace renderer {
	class IHWVertexBuffer {
	public:
		virtual ~IHWVertexBuffer();

		virtual VertexFormat getVertexFormat() = 0;
		virtual int getCount() = 0;

		virtual void* lock() = 0;
		virtual void unlock() = 0;

	};
}