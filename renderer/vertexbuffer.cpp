#pragma once
#include "vertexbuffer.h"
#include <QSharedData>
#include "hwvertexbuffer.h"

namespace renderer {
	

	VertexBuffer::VertexBuffer()
	{

	}

	VertexBuffer::~VertexBuffer()
	{

	}

	HWVertexBuffer* VertexBuffer::getHardWaterVertexBuffer()
	{
		return NULL;
	}

	VertexFormat VertexBuffer::getVertexFormat()
	{
		return VF_UNKNOWN;
	}

	int VertexBuffer::getCount()
	{
		return 0;
	}

	void* VertexBuffer::lock()
	{
		return NULL;
	}

	void VertexBuffer::unlock()
	{

	}
}
