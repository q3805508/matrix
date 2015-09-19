#pragma once
#include "rendererdef.h"
#include "hwresource.h"

namespace renderer {
	class HWVertexBuffer : public HWResource{
	public:
		virtual ~HWVertexBuffer(){}

		virtual VertexFormat getVertexFormat() = 0;
		virtual int getCount() = 0;

		virtual void* lock() = 0;
		virtual void unlock() = 0;	

	protected:
		virtual void releaseResource() = 0;

	};
}