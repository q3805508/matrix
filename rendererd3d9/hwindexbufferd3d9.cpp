#include "hwindexbufferd3d9.h"
#include "../renderer/rendermgr.h"
#include "rendererd3d9.h"
#include <QDebug>

namespace d3d9{
	HWIndexBufferD3D9::HWIndexBufferD3D9()
	{
		this->pIB = NULL;
		this->count = 0;
	}

	HWIndexBufferD3D9::~HWIndexBufferD3D9()
	{
		Q_ASSERT(!this->pIB);
	}

	int HWIndexBufferD3D9::getCount()
	{
		return this->count;
	}

	unsigned short* HWIndexBufferD3D9::lock()
	{
		return NULL;
	}

	void HWIndexBufferD3D9::unlock()
	{

	}

	void HWIndexBufferD3D9::initIndexBuffer(int count,IDirect3DIndexBuffer9* pBuffer)
	{
		this->pIB = pBuffer;
		this->count = count;
	}

	void HWIndexBufferD3D9::releaseResource()
	{
		RendererD3D9* pRenderer = (RendererD3D9*)renderer::theRenderMgr->getRenderer();
		pRenderer->releaseHardWareIndexBuffer(this);
	}
}