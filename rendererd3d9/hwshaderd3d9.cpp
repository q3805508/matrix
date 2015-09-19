#include "hwshaderd3d9.h"
#include <QDebug>

namespace d3d9 {
	HWShaderD3D9::HWShaderD3D9()
		:sType(renderer::SHADER_END)
	{

	}

	HWShaderD3D9::~HWShaderD3D9()
	{
		Q_ASSERT(!this->pVS&&!this->pPS&&!this->pCTable);
	}

	renderer::ShaderType HWShaderD3D9::getShaderType()
	{
		return this->sType;
	}

	void HWShaderD3D9::releaseResource()
	{

	}

	void HWShaderD3D9::initShader(renderer::ShaderType type, IDirect3DVertexShader9* pVS,
		IDirect3DPixelShader9* pPS,ID3DXConstantTable* cTable)
	{
		this->sType = type;
		this->pVS = pVS;
		this->pPS = pPS;
		this->pCTable = cTable;
	}


}