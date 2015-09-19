#include "hwvertexbufferd3d9.h"
#include "../renderer/rendermgr.h"
#include "rendererd3d9.h"

namespace d3d9 {
	HWVertexBufferD3D9::HWVertexBufferD3D9()
		:pVertexBuffer(NULL)
		,format(renderer::VF_UNKNOWN)
		,nCount(0)
	{
	}

	HWVertexBufferD3D9::~HWVertexBufferD3D9()
	{
		Q_ASSERT(this->pVertexBuffer);
	}

	renderer::VertexFormat HWVertexBufferD3D9::getVertexFormat()
	{
		return this->format;
	}

	int HWVertexBufferD3D9::getCount()
	{
		return this->nCount;
	}

	void* HWVertexBufferD3D9::lock()
	{
		return NULL;
	}

	void HWVertexBufferD3D9::unlock()
	{

	}

	void HWVertexBufferD3D9::initVertexBuffer(renderer::VertexFormat fmt,int nCount,IDirect3DVertexBuffer9* pVB)
	{
		this->pVertexBuffer = pVB;
		this->format = fmt;
		this->nCount = nCount;
	}

	void HWVertexBufferD3D9::releaseResource()
	{
		RendererD3D9* pRenderer = (RendererD3D9*)renderer::theRenderMgr->getRenderer();
		pRenderer->releaseHardWareVertexBuffer(this);
	}
}