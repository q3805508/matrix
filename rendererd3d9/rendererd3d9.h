#ifndef RENDERERD3D9_H
#define RENDERERD3D9_H

#include "rendererd3d9_global.h"
#include "../renderer/renderer.h"
#include <d3d9.h>


class IDirect3DDevice9;

namespace d3d9 {
	class HWIndexBufferD3D9;
	class HWVertexBufferD3D9;
	class HWShaderD3D9;
	class RENDERERD3D9_EXPORT RendererD3D9 : public renderer::IRenderer
	{
	public:
		RendererD3D9();
		~RendererD3D9();

		///////////interface IRenderer/////////////////////////////////
		bool init(QWidget* outputWnd,int height,int width,bool windowed);
		void shutdown();
		void beginFrame();
		void endFrame();
		void present();

		renderer::RenderElement* createRenderElement(renderer::RENDERELEMENT_TYPE type);
		void drawElement(renderer::RenderElement* pElement,renderer::ShaderItem* pShaderItem);

		renderer::HWTexture* createHardWareTexture(
			int width,int height,renderer::TextureType type,
			int nlod,renderer::TextureFormat format,int FLAGS);

		renderer::HWIndexBuffer* createHardWareIndexBuffer(int count,bool dynamic);
		renderer::HWVertexBuffer* createHardWareVertexBuffer(int count,renderer::VertexFormat fmt,bool dynamic);

		renderer::HWShader* createHardWareShader(const char * shaderString,int strLen,
			const char* functionName,QVector<QString> macro,renderer::ShaderType type);
		void setBackGround(int r,int b,int g,int a);

		void resize(int height,int width);
		void setFullScreen(bool fullScreen);
		//////////////////////////////////////////////////////////////

		/////////////functions of rendererd3d9////////////////////////
		void releaseHardWareShader(d3d9::HWShaderD3D9* pShader);
		void releaseHardWareVertexBuffer(HWVertexBufferD3D9* pVB);
		void releaseHardWareIndexBuffer(HWIndexBufferD3D9* pIB);


	private:
		RendererD3D9(const RendererD3D9& src);
		RendererD3D9& operator = (const RendererD3D9& src);

		IDirect3DDevice9* pDeviceD3D9;
		D3DCOLOR backGround;
	};
}

#endif // RENDERERD3D9_H
