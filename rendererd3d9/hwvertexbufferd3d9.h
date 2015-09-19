#pragma once
#include "../renderer/hwvertexbuffer.h"
#include <d3d9.h>

namespace d3d9{
	class RendererD3D9;

	class HWVertexBufferD3D9 : public renderer::HWVertexBuffer {
	public:
		HWVertexBufferD3D9();
		~HWVertexBufferD3D9();

		virtual renderer::VertexFormat getVertexFormat();
		virtual int getCount();
		
		virtual void* lock();
		virtual void unlock();	
	
	protected:
		virtual void releaseResource();

	private:

		void initVertexBuffer(renderer::VertexFormat fmt,int nCount,IDirect3DVertexBuffer9* pVB);

		friend class RendererD3D9;

		IDirect3DVertexBuffer9* pVertexBuffer;
		renderer::VertexFormat format;
		int nCount;
	};
}