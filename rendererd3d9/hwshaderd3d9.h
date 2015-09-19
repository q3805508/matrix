#pragma once
#include "../renderer/hwshader.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace d3d9 {

	class HWShaderD3D9 : public renderer::HWShader {
	public:
		HWShaderD3D9();
		~HWShaderD3D9();

		virtual renderer::ShaderType getShaderType();

		virtual void releaseResource();

	private:
		void initShader(renderer::ShaderType type,
			IDirect3DVertexShader9* pVS,IDirect3DPixelShader9* pPS,ID3DXConstantTable* cTable);


	private:
		renderer::ShaderType sType;
		IDirect3DVertexShader9* pVS;
		IDirect3DPixelShader9* pPS;
		ID3DXConstantTable* pCTable;
		

		friend class RendererD3D9;
	};
}