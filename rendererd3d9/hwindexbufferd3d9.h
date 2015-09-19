#pragma once
#include "../renderer/hwindexbuffer.h"
#include <d3d9.h>

namespace d3d9 {
	class RendererD3D9;
	class HWIndexBufferD3D9 : public renderer::HWIndexBuffer {
	public:
		HWIndexBufferD3D9();
		~HWIndexBufferD3D9();

		//bool createIndexBuffer(int count,bool dynamic);

		int getCount();

		unsigned short* lock();
		void unlock();

	private:
		void initIndexBuffer(int count,IDirect3DIndexBuffer9* pBuffer);

	protected:
		virtual void releaseResource();

	private:
		friend class RendererD3D9;
		IDirect3DIndexBuffer9* pIB;
		int count;
	};
}